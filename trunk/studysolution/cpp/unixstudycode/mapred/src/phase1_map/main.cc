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

#include <gflags/gflags.h>

#include "qoslib/include/QOSLibAllExp.h"
#include "qlog.h"
#include "qlogtypes.h"
#include "constant.h"
#include "file_handler.h"

#include "command_handler.impl.h"

using namespace std;
using namespace QPub;


DEFINE_string(qlog_config, "/home/weizili/bin/etc/qlog.conf", "The path of the qlog config file.");

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

    ::google::ParseCommandLineFlags(&argc, &argv, true);

    qLogConfig(FLAGS_qlog_config.c_str());
    //qLogInfo(LOG, "Start ... ");

    osl::initializeOSLib();

    CommandHandlerImpl command_handler;
    FileHandler file_handler;

    if (!command_handler.Init(stdout) || !file_handler.Init(stdin))
    {
        //qAppError(LOG, "Failed to init CommandHandler or FileHandler.");
        exit(0);
    }

    osl::Slice command;
    while(!b_exit)
    {
        if (true == file_handler.GetLine(command))
        {
            command_handler.Work(command);
        }
        else
        {
            b_exit = true; 
        }
    }

    command_handler.LastSerialize();

    //after receive SIGINT
    int retry = 0;
    while(!command_handler.Flush(true) && retry < 10)
    {
        retry++;
        //qLogInfo(LOG, "Failed to flush command before exit, retry %d times.", retry);
        usleep(10000);
    }

    osl::uninitializeOSLib();
    //qLogInfo(LOG, "Exit...");

    return 0;
}

