#include "test/file_test.h"
//#include "amop/MockObject.h"

#include <boost/filesystem.hpp>
#include "file_handler.h"
#include <gflags/gflags.h>

CPPUNIT_TEST_SUITE_REGISTRATION(FileTest);

using namespace std;
//using namespace amop;
const std::string FileTest::test_command[8] = {"xcvk  l;j eioth;2h", 
  "zcv5cv\t4c47j", 
  "woery   \tshfj\tnfiuywfywer", 
  "901  274y75jhjxc8902hsud", 
  "asdfowr23  9o752352n5252 8sdkj\thr9", 
  "789014uioqerjkldfbjfvy8", 
  "dfhke\trquio",
  "]12-94 2\t3iopuio 1v53907 59u"
};

void FileTest::setUp()
{
  boost::filesystem::remove_all("testdata");
  boost::filesystem::create_directories("testdata/data");

  boost::filesystem::create_directories("testdata/data/0");
  boost::filesystem::create_directories("testdata/data/1");
  boost::filesystem::create_directories("testdata/data/2");
  boost::filesystem::create_directories("testdata/data/3");
}

void FileTest::tearDown()
{
  boost::filesystem::remove_all("testdata");
}

void FileTest::testSingleDirectoryMultipleSmallFile()
{
  string receive_command;

  ::google::SetCommandLineOption("priority_level", "0");
  ::google::SetCommandLineOption("log_prefix", "mytest_");

  ofstream ofs;
  ofs.open("testdata/data/mytest_001.xml");
  ofs <<test_command[0] <<endl
    <<test_command[1] <<endl;
  ofs.close();
  FileHandler handler;
  handler.Init();

  ofs.open("testdata/data/mytest_002.xml");
  ofs <<test_command[2] <<endl
    <<test_command[3] <<endl;
  ofs.close();

  ofs.open("testdata/data/mytest_003.xml");
  ofs <<test_command[4] <<endl
    <<test_command[5] <<endl;
  ofs.close();

  ofs.open("testdata/data/mytest_004.xml");
  ofs <<test_command[6] <<endl
    <<test_command[7] <<endl;
  ofs.close();

  CPPUNIT_ASSERT(handler.GetLine(receive_command));
  CPPUNIT_ASSERT_EQUAL(test_command[0], receive_command);
  CPPUNIT_ASSERT(handler.GetLine(receive_command));
  CPPUNIT_ASSERT_EQUAL(test_command[1], receive_command);
  CPPUNIT_ASSERT(handler.GetLine(receive_command));
  CPPUNIT_ASSERT_EQUAL(test_command[2], receive_command);
  CPPUNIT_ASSERT(handler.GetLine(receive_command));
  CPPUNIT_ASSERT_EQUAL(test_command[3], receive_command);
  CPPUNIT_ASSERT(handler.GetLine(receive_command));
  CPPUNIT_ASSERT_EQUAL(test_command[4], receive_command);
  CPPUNIT_ASSERT(handler.GetLine(receive_command));
  CPPUNIT_ASSERT_EQUAL(test_command[5], receive_command);
  CPPUNIT_ASSERT(handler.RecordPos());
  CPPUNIT_ASSERT(handler.GetLine(receive_command));
  CPPUNIT_ASSERT_EQUAL(test_command[6], receive_command);
}

void FileTest::testSingleDirectoryDeletePos()
{
  string receive_command;

  ::google::SetCommandLineOption("log_path", "testdata/data/");
  ::google::SetCommandLineOption("priority_level", "0");
  ::google::SetCommandLineOption("log_prefix", "mytest_");
  ofstream ofs("testdata/data/pos.mytest_000.xml");
  ofs << 0;
  ofs.close();

  ofs.open("testdata/data/mytest_001.xml");
  ofs <<test_command[0] <<endl
    <<test_command[1] <<endl
    <<test_command[2] <<endl;
  FileHandler handler;
  handler.Init();

  CPPUNIT_ASSERT(handler.GetLine(receive_command));
  CPPUNIT_ASSERT_EQUAL(test_command[0], receive_command);

  CPPUNIT_ASSERT(handler.GetLine(receive_command));
  CPPUNIT_ASSERT_EQUAL(test_command[1], receive_command);

  CPPUNIT_ASSERT(handler.GetLine(receive_command));
  CPPUNIT_ASSERT_EQUAL(test_command[2], receive_command);
}

void FileTest::testSingleDirectory()
{
  ::google::SetCommandLineOption("log_path", "testdata/data/");
  ::google::SetCommandLineOption("priority_level", "0");
  ::google::SetCommandLineOption("log_prefix", "mytest_");
  FileHandler handler;
  handler.Init();

  string test_command1 = "test command 1";
  string test_command2 = "test command test --------------------------";
  string test_command3 = "test command testttttttttt";
  string untest_command = "untest command 2";
  ofstream ofs("testdata/data/mytest_1.xml");
  ofs <<test_command1 <<endl
      <<test_command2 <<endl;
  ofs.flush();

  string receive_command;
  CPPUNIT_ASSERT(handler.GetLine(receive_command));
  CPPUNIT_ASSERT_EQUAL(test_command1, receive_command);

  receive_command.clear();
  CPPUNIT_ASSERT(handler.GetLine(receive_command));
  CPPUNIT_ASSERT_EQUAL(test_command2, receive_command);

  ofs <<untest_command;
  ofs.flush();

  CPPUNIT_ASSERT(!handler.GetLine(receive_command));
  CPPUNIT_ASSERT_EQUAL(untest_command, receive_command);
  CPPUNIT_ASSERT(!boost::filesystem::exists("testdata/data/pos.mytest_1.xml"));
  CPPUNIT_ASSERT(handler.RecordPos());
  CPPUNIT_ASSERT(boost::filesystem::exists("testdata/data/pos.mytest_1.xml"));
  ifstream ifs("testdata/data/pos.mytest_1.xml");
  size_t pos_content = 0;
  ifs >> pos_content;
  ifs.close();
  size_t fsize = test_command1.length() + test_command2.length() + 2;
  CPPUNIT_ASSERT_EQUAL(fsize, pos_content);

  receive_command.clear();
  CPPUNIT_ASSERT(!handler.GetLine(receive_command));
  CPPUNIT_ASSERT_EQUAL(untest_command, receive_command);
  
  ofs <<endl;
  ofs.flush();
  ofs.close();

  receive_command.clear();
  CPPUNIT_ASSERT(handler.GetLine(receive_command));
  CPPUNIT_ASSERT_EQUAL(untest_command, receive_command);

  CPPUNIT_ASSERT(handler.RecordPos());
  CPPUNIT_ASSERT(boost::filesystem::exists("testdata/data/pos.mytest_1.xml"));
  ifs.open("testdata/data/pos.mytest_1.xml");
  pos_content = 0;
  ifs >> pos_content;
  ifs.close();
  fsize = boost::filesystem::file_size("testdata/data/mytest_1.xml");
  CPPUNIT_ASSERT_EQUAL(fsize, pos_content);

  ofs.open("testdata/data/mytest_2.xml");
  ofs <<test_command3;
  ofs.flush();

  CPPUNIT_ASSERT(!handler.GetLine(receive_command));
  CPPUNIT_ASSERT(boost::filesystem::exists("testdata/data/pos.mytest_1.xml"));
  CPPUNIT_ASSERT(!boost::filesystem::exists("testdata/data/bak.mytest_1.xml"));

  ofs <<endl;
  CPPUNIT_ASSERT(handler.GetLine(receive_command));
  CPPUNIT_ASSERT_EQUAL(test_command3, receive_command);

  CPPUNIT_ASSERT(!boost::filesystem::exists("testdata/data/pos.mytest_2.xml"));
  CPPUNIT_ASSERT(boost::filesystem::exists("testdata/data/pos.mytest_1.xml"));
  CPPUNIT_ASSERT(handler.RecordPos());
  CPPUNIT_ASSERT(boost::filesystem::exists("testdata/data/pos.mytest_2.xml"));
  CPPUNIT_ASSERT(!boost::filesystem::exists("testdata/data/pos.mytest_1.xml"));
  CPPUNIT_ASSERT(boost::filesystem::exists("testdata/data/bak.mytest_1.xml"));
}

void FileTest::testMultipleDirectory()
{
  ::google::SetCommandLineOption("log_path", "testdata/data/");
  ::google::SetCommandLineOption("priority_level", "4");
  ::google::SetCommandLineOption("log_prefix", "mytest_");
  FileHandler handler;
  handler.Init();

  ofstream ofs0, ofs1, ofs2, ofs3;
  ofs0.open("testdata/data/0/mytest_a.xml");
  ofs1.open("testdata/data/1/mytest_a.xml");
  ofs2.open("testdata/data/2/mytest_a.xml");
  ofs3.open("testdata/data/3/mytest_a.xml");
  

  string receive_command;

  ofs0 <<test_command[0] <<endl;
  ofs1 <<test_command[1] <<endl;
  ofs2 <<test_command[2] <<endl;
  ofs3 <<test_command[3] <<endl;

  ofs0.flush();
  ofs1.flush();
  ofs2.flush();
  ofs3.flush();

  CPPUNIT_ASSERT(handler.GetLine(receive_command));
  CPPUNIT_ASSERT_EQUAL(test_command[0], receive_command);
  CPPUNIT_ASSERT(!handler.GetLine(receive_command));

  CPPUNIT_ASSERT(handler.RecordPos());
  CPPUNIT_ASSERT(handler.GetLine(receive_command));
  CPPUNIT_ASSERT_EQUAL(test_command[1], receive_command);
  CPPUNIT_ASSERT(!handler.GetLine(receive_command));

  CPPUNIT_ASSERT(handler.RecordPos());
  CPPUNIT_ASSERT(handler.GetLine(receive_command));
  CPPUNIT_ASSERT_EQUAL(test_command[2], receive_command);
  CPPUNIT_ASSERT(!handler.GetLine(receive_command));

  CPPUNIT_ASSERT(handler.RecordPos());
  CPPUNIT_ASSERT(handler.GetLine(receive_command));
  CPPUNIT_ASSERT_EQUAL(test_command[3], receive_command);
  CPPUNIT_ASSERT(!handler.GetLine(receive_command));

  ofs1 <<test_command[4] <<endl;
  ofs1 <<test_command[5] <<endl;
  ofs1.flush();
  CPPUNIT_ASSERT(handler.RecordPos());
  CPPUNIT_ASSERT(handler.GetLine(receive_command));
  CPPUNIT_ASSERT_EQUAL(test_command[4], receive_command);

  ofs0 <<test_command[6] <<endl;
  ofs0.flush();

  CPPUNIT_ASSERT(handler.GetLine(receive_command));
  CPPUNIT_ASSERT_EQUAL(test_command[5], receive_command);
  CPPUNIT_ASSERT(!handler.GetLine(receive_command));

  CPPUNIT_ASSERT(handler.RecordPos());
  CPPUNIT_ASSERT(handler.GetLine(receive_command));
  CPPUNIT_ASSERT_EQUAL(test_command[6], receive_command);
  CPPUNIT_ASSERT(!handler.GetLine(receive_command));

  ofs2 <<test_command[7] <<endl;
  ofs2.flush();


  CPPUNIT_ASSERT(handler.RecordPos());
  CPPUNIT_ASSERT(handler.GetLine(receive_command));
  CPPUNIT_ASSERT_EQUAL(test_command[7], receive_command);
  CPPUNIT_ASSERT(!handler.GetLine(receive_command));
}
