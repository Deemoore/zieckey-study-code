#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>

#include <gflags/gflags.h>

int main(int argc, char* argv[])
{
    ::google::ParseCommandLineFlags(&argc, &argv, true);
    return 0;
}

