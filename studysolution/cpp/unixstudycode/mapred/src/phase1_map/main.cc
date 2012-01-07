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
DEFINE_string(fin_path, "", "The path of the input file, if it is empty, we use the stdin as the input");
DEFINE_string(fout_path, "", "The path of the output file, if it is empty, we use the stdout the input");

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

#ifdef _DEBUG
    qLogConfig(FLAGS_qlog_config.c_str());
    qLogInfo(LOG, "Start ... ");
#endif

    osl::initializeOSLib();

    FILE* fin = stdin;
    FILE* fout = stdout;

    if (FLAGS_fin_path.size())
    {
        fin = fopen(FLAGS_fin_path.c_str(), "r");
        if (!fin)
        {
            fprintf(stderr, "cannot open file : %s\n", FLAGS_fin_path.c_str());
            return -1;
        }
    }

    if (FLAGS_fout_path.size())
    {
        fout = fopen(FLAGS_fout_path.c_str(), "r");
        if (!fout)
        {
            fprintf(stderr, "cannot open file : %s\n", FLAGS_fout_path.c_str());
            return -1;
        }
    }

    
    

    CommandHandlerImpl command_handler;
    FileHandler file_handler;

    if (!file_handler.Init(fin) || !command_handler.Init(fout))
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

    //qLogInfo(LOG, "Exit...");

    return 0;
}

