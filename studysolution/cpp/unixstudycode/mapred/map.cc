#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>

#include <gflags/gflags.h>


DEFINE_int32(cache_count, 10, "The internal process cache count");
DEFINE_int32(line_buffer_len, 600, "The max buffer length of one line");

class Mapping
{
public:
    Mapping()
        : result_(new char*[FLAGS_cache_count]), curr_(0)
    {
        for (int i = 0; i < FLAGS_cache_count; ++i)
        {
            result_[i] = new char[FLAGS_line_buffer_len];
        }
    }

    void Process(const char* data)
    {
        if (curr_ >= FLAGS_cache_count)
        {
            Dump();
            curr_ = 0;
        }

        //TODO process data
        //TEMP
        strncpy(result_[curr_++], data, FLAGS_line_buffer_len);
    }


    void Dump()
    {
        for (int i = 0; i < curr_; ++i)
        {
            printf("%lu\t1\n", strlen(result_[i]));
        }
    }

    ~Mapping()
    {
        printf("~Mapping\n");
        Dump();

        for (int i = 0; i < FLAGS_cache_count; ++i)
        {
            delete result_[i];
        }
        delete result_;
        result_ = NULL;
    }
private:
    char** result_;//store the result of map
    int    curr_;
};

int main(int argc, char* argv[])
{
    ::google::ParseCommandLineFlags(&argc, &argv, true);

    char* line = new char[FLAGS_line_buffer_len]; //store every line

    Mapping mapping;
    while (0 == feof(stdin))
    {
        if (NULL == fgets(line, FLAGS_line_buffer_len, stdin))
        {
            break;
        }
        mapping.Process(line);
    }

    delete line;
    line = NULL;
    return 0;
}

