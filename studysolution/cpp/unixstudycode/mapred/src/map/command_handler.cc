#include "command_handler.h"

#include <fstream>
#include <sys/stat.h>

#include <boost/algorithm/string.hpp>

#include "mid_command_processor.h"
#include "qoslib/include/QFileUtil.h"
#include "qoslib/include/QTimer.h"
#include "qoslib/include/QMD5.h"

#include "constant.h"
#include "qlog.h"

#include <gflags/gflags.h>

DEFINE_int32(dump_time, 30, "The max interval between twice dump, measured by second.");
DEFINE_int32(dump_count, 10000, "The max count of log in one message");

DEFINE_string(memcached_sock, "", "The memcached domain socket");
DEFINE_string(memcached_host, "localhost", "The memcached server hostname");
DEFINE_string(memcached_port, "10001", "The memcached servert listening port");

DEFINE_string(output_dir, "../data/output", "The output data dir");

DECLARE_string(log_path);// some other file has a DEFINE_string(log_path)
DECLARE_int32(priority_level);// some other file has a DEFINE_int32(priority_level)

CommandHandler::CommandHandler()
  : dump_time_interval_(0), dump_count_max_(0), last_update_(time(0)), line_processor_(NULL)
{
}

bool CommandHandler::Init()
{
  dump_time_interval_ = FLAGS_dump_time;
  dump_count_max_ = FLAGS_dump_count;

  dump_vect_.reserve(dump_count_max_);

  //boost::algorithm::trim_right_if(str, boost::algorithm::is_any_of(" \n\r"));
  osl::StringA tmpstring = FLAGS_output_dir.c_str();
  osl::StringUtil::trim(tmpstring, "\n\t /", false, true);
  if (!osl::FileUtil::isFSFileExist(tmpstring))
  {
    if (!osl::FileUtil::makeFSDir(tmpstring))
    {
      qAppErrors(kLogName) << "mkdir failed : " << tmpstring.c_str();
      return false;
    }
  }

  qLogDebugs(kLogName) << "output dir: " << tmpstring.c_str();

  output_dir_ = tmpstring.c_str();

  line_processor_ = new midtag::LineProcessor(FLAGS_memcached_sock.c_str(), 
              FLAGS_memcached_host.c_str(), FLAGS_memcached_port.c_str()); 

  if (!file_id_generator_.Init())
  {
    qAppErrors(kLogName) << "FileIDGenerator init failed!!!";
    return false;
  }

  channel_ = "0";
  std::string log_path = FLAGS_log_path;
  boost::algorithm::trim_right_if(log_path, boost::algorithm::is_any_of("/ \n\r"));
  size_t pos = log_path.find_last_of('/');
  if (pos != std::string::npos && FLAGS_priority_level > 0)
  {
    channel_ = std::string(log_path.c_str() + pos + 1);
  }
  qLogTraces(kLogName) << "channel_=" << channel_;


  return true;
}

CommandHandler::~CommandHandler()
{
  delete line_processor_;
  line_processor_ = NULL;
}

bool CommandHandler::Work(const std::string& command)
{
  qLogDebugs(kLogName) 
    << "Processing command: " << command;

#ifdef TEST_PERFORMANCE
  double fbegin = s_pTimer->getImmediateSeconds();
#endif
  std::string output;
  if (line_processor_->ProcessLine(command, output))
  {
#ifdef TEST_PERFORMANCE
    double fend = s_pTimer->getImmediateSeconds();
#endif
    qLogDebugs(kLogName) 
#ifdef TEST_PERFORMANCE
      << "Process one command time cost : " << fend - fbegin << " "
#endif
      << "Processed one line: " << command << " ooooutput=" << output;
    const size_t kMinOutputLen = sizeof("set key|") - 1;
    if (output.length() >= kMinOutputLen)
    {
      dump_vect_.push_back(output);
    }
    else
    {
      qLogWarns(LOG) << command << " output=" << output;
    }

    return true;
  }

  return false;
}


bool CommandHandler::Flush(bool force)
{
  bool ret = false;
  if (CheckDumpCount()
      || CheckDumpTime()
      || force)
  {
    qLogTraces(kLogName) 
        << "Try to flush force=" << (force ? "true" : "false")
        << " CheckDumpCount()=" << (true == CheckDumpCount() ? "true" : "false")
        << " CheckDumpTime()=" << (true == CheckDumpTime() ? "true" : "false");

    if (dump_vect_.size() > 0)
    {
      if (!Dump())
      {
        return false;  
      }

      dump_vect_.clear();
      dump_vect_.reserve(dump_count_max_);
    }
    else
    {
      qLogInfos(kLogName) << "No data to dump.";
    }
    
    last_update_ = time(0);
    ret = true;
  }
  return ret;
}

bool CommandHandler::Dump()
{//{{{
#ifdef TEST_PERFORMANCE
  double fbegin = s_pTimer->getImmediateSeconds();
#endif

  AutoLock_FileIDGenerator file_id_generator_auto_lock(file_id_generator_); //auto lock the file_id_generator_
  if (!file_id_generator_.IsLocked())
  {
    qAppErrors(kLogName) << "lock failed";  
    return false;
  }

  int64_t newid = file_id_generator_.GetID();
  if (newid < 0)
  {
    qAppErrors(kLogName) << "generate new id failed";  
    return false;
  }

  std::string outfile_tmp = GetTempOutputFilePath(newid);
  std::fstream ofp(outfile_tmp.c_str(), std::ios::out|std::ios::binary);
  if(!ofp.is_open())
  {
    int myerr = errno;
    qAppErrors(kLogName) 
        << "open file \"" << outfile_tmp 
        << "\" faield. " << strerror(myerr);
    return false;
  }

  stringvector::iterator it(dump_vect_.begin());
  stringvector::iterator ite(dump_vect_.end());
  for (; it != ite; ++it)
  {
    ofp << *it;
  }
  ofp.flush();
  ofp.close();

  std::string outfile = GetOutputFilePath(newid);

  if (0 != rename(outfile_tmp.c_str(), outfile.c_str()))
  {
    int myerr = errno;
    qAppErrors(kLogName) 
        << "rename \"" << outfile_tmp 
        << "\" to \"" << outfile << "\" failed : errno=" << myerr 
        << " ," << strerror(myerr);
    unlink(outfile_tmp.c_str());
    return false;
  }

  for (int i = 0; i < 10; ++i)
  {
    if (0 == chmod(outfile.c_str(), 0644))
    {
      if (i != 0)
      {
        qLogInfos(kLogName) << "chmod \"" << outfile_tmp << "\" OK!";
      }
      break;
    }
    else
    {
      int myerr = errno;
      qAppErrors(kLogName) 
        << "chmod \"" << outfile_tmp 
        << "\" failed, but we will retry. : errno=" << myerr 
        << " ," << strerror(myerr);
    }
  }

  int i = 0;
  bool increased_ok = false;
  do
  {
    if (file_id_generator_.IncreaseID())
    {
      increased_ok = true;
      break;
    }
    qAppErrors(kLogName) << "file_id_generator_.IncreaseID() failed, we will try again later.";
    usleep(1000 * 100);//slepp 100ms 
  } while(i++ < 10);

  if (!increased_ok)
  {
    qLogFatals(kLogName) << "file_id_generator_.IncreaseID() eventually failed. Please check it!!!";
    throw std::runtime_error("file_id_generator_.IncreaseID() failed. We REALLY DONNOT known how to process this error.");
  }

#ifdef TEST_PERFORMANCE
  double fend = s_pTimer->getImmediateSeconds();
#endif
  qLogInfos(kLogName) 
#ifdef TEST_PERFORMANCE
      << "Dump file time cost : " << fend - fbegin << " "
#endif
      << "Dump file OK, total:" << dump_vect_.size() << " " << outfile;
  return true;
}//}}}

bool CommandHandler::CheckDumpTime()
{
  return last_update_ + dump_time_interval_ < time(0);
}

bool CommandHandler::CheckDumpCount()
{
  return dump_vect_.size() >= dump_count_max_; 
}

namespace
{//{{{
    //return the time string with micro second
    std::string GetUTimeString()
    {
        std::string::value_type szTime[128] = {};
        struct tm *pTime;
        time_t ctTime;
        time( &ctTime );
        pTime = localtime( &ctTime );


        long uunit = 1000 * 1000;
        snprintf( szTime, sizeof(szTime), "%4d%.2d%.2d%.2d%.2d%.2d_%.6ld", 
                    pTime->tm_year + 1900, pTime->tm_mon + 1, pTime->tm_mday,
                    pTime->tm_hour, pTime->tm_min, pTime->tm_sec, 
                    ((long)(s_pTimer->getImmediateSeconds() * uunit))%uunit);

        return std::string(szTime);
    }

    //return the time string, the last 2 chars represent second
    std::string GetTimeString()
    {
        std::string::value_type szTime[128] = {};
        struct tm *pTime;
        time_t ctTime;
        time( &ctTime );
        pTime = localtime( &ctTime );

        snprintf( szTime, sizeof(szTime), "%4d%.2d%.2d%.2d%.2d%.2d", 
                    pTime->tm_year + 1900, pTime->tm_mon + 1, pTime->tm_mday,
                    pTime->tm_hour, pTime->tm_min, pTime->tm_sec);
        return std::string(szTime);
    }
}//}}}

std::string CommandHandler::GetTempOutputFilePath(int64_t file_id)
{
  char buf[512] = {};
  snprintf(buf, sizeof(buf), "%s/Inc_%s_mid_%ld_%lu_%s.tmp", 
                output_dir_.c_str(), kLogName, file_id, dump_vect_.size(), GetUTimeString().c_str() );	

  return buf;
}

std::string CommandHandler::GetOutputFilePath(int64_t file_id)
{
  osl::MD5 md5;
  stringvector::iterator it(dump_vect_.begin());
  stringvector::iterator ite(dump_vect_.end());
  for (; it != ite; ++it)
  {
    md5.update((unsigned char*)(*it).c_str(), (unsigned int)(*it).length());
  }
  md5.finalize();
  char hexmd5[osl::MD5::MD5_HEX_DIGEST_LEN + 1];
  md5.getHexDigest(hexmd5);

  char hostname[128] = {};
  gethostname(hostname, sizeof(hostname));

  //long tid = 0;
  //thr_self(&tid);

  char buf[512] = {};
  snprintf(buf, sizeof(buf), "%s/Inc_1%.10ld_%s_%lu_%s_%s_%ld_%s_%s.xml",
                output_dir_.c_str(), file_id, hexmd5, dump_vect_.size(), kLogName, 
                hostname, (long)getpid(), channel_.c_str(), GetTimeString().c_str() );	

  return buf;
}
