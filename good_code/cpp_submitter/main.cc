#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <signal.h>
#include <vector>
#include <sys/wait.h>
#include <fcntl.h>
#include <limits.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

//#include <boost/algorithm/string.hpp>
#include <gflags/gflags.h>

#include "qlog.h"
#include "qlogtypes.h"
#include "daemonize.h"
#include "check_worker.h"
#include "constant.h"
#include "command_handler.h"
#include "file_handler.h"

using namespace std;
using namespace QPub;


DEFINE_string(qlog_config, "./etc/qlog.conf", "The path of the qlog config file.");

static bool b_exit =false;

void exitHandler(int _i)
{
  b_exit = true;
}

int main (int argc, char** argv)
{
  signal(SIGINT, exitHandler); 
  signal(SIGTERM, exitHandler);
  signal(SIGPIPE, SIG_IGN);

  //MUST put the constructor of CheckWorkerFile before ParseCommandLineFlags to get the correct arguments
  CheckWorkerFile pid_file(argc, argv);
  Daemonize daemonize;

  ::google::ParseCommandLineFlags(&argc, &argv, true);

  daemonize.Init();
  pid_file.Init();

  qLogConfig(FLAGS_qlog_config.c_str());
  qLogInfo(LOG, "Start ... ");

  CommandHandler command_handler;
  FileHandler file_handler;

  if (!command_handler.Init() || !file_handler.Init())
  {
    qAppError(LOG, "Failed to init CommandHandler or FileHandler.");
    exit(0);
  }


  string command;
  while(!b_exit)
  {
    if (true == file_handler.GetLine(command))
    {
      if (false == command_handler.Work(command))
      {
        qAppError(LOG, "Failed to work on the command: %s", command.c_str());
      }
    }
    else
    {
      usleep(1000);
    }

    if (true == command_handler.Flush(false))
    {
      file_handler.RecordPos();
    }
  }

  //after receive SIGINT
  int retry = 0;
  while(!command_handler.Flush(true) && retry < 10)
  {
    retry++;
    qLogInfo(LOG, "Failed to flush command before exit, retry %d times.", retry);
    usleep(10000);
  }

  qLogInfo(LOG, "Exit...");
  return 0;
}
