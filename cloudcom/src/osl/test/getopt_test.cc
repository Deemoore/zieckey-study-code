
#include "osl/include/test_common.h"
#include "osl/include/getopt.h"
#include "osl/include/platform_micros.h"

#include <iostream>

namespace
{
    void help()
    {
        printf(
            "getopt test programn"
            "Usage: test [OPTION] [INPUT]\n"
            "   INPUT           set input filename (doesn't do anything)\n"
            "   -h              help menu (this screen)\n"
            "   -i              interactive mode (doesn't do anything)\n"
            "   -f              force mode (doesn't do anything)\n"
            "   -r              recursive mode (doesn't do anything)\n"
            "   -v[level]       set verbosity level (5 is default; doesn't do anything)\n"
            "   -o filename     set output filename (doesn't do anything)\n"
            );
    }



#define FLAG_INTERACT   0x0001        
#define FLAG_FORCE      0x0002        
#define FLAG_RECURSIVE  0x0004        

    int flags = 0;                        
    int verbose = 0;                      
    //const char* in_fname = NULL;          
    const char* out_fname = NULL;         

    void getopt_test()
    {
        const char* argv[] = {
            "./test_program",
            "-f",
            "-i",
            "-r",
            "-v", 
            "3"
        };
        int argc = H_ARRAYSIZE(argv);
        
        while(1) 
        {
            int c = getopt(argc, const_cast<char**>(argv), "ifrhv::o:");
            if(c == -1) break;
            switch(c) 
            {
            case 'i': 
                flags |= FLAG_INTERACT; 
                break;
            case 'f': 
                flags |= FLAG_FORCE; 
                break;
            case 'r': 
                flags |= FLAG_RECURSIVE; 
                break;
            case 'h': 
                help(); 
                break;
            case 'v': 
                verbose = atoi(optarg); 
                break;
            case 'o': 
                out_fname = optarg; 
                break;
            default:
                printf("Option '%c' (%d) with '%s'\n", c, c, optarg);
                break;
            }
        }

        H_TEST_ASSERT((flags & FLAG_INTERACT)  == FLAG_INTERACT);
        H_TEST_ASSERT((flags & FLAG_FORCE)     == FLAG_FORCE);
        H_TEST_ASSERT((flags & FLAG_RECURSIVE) == FLAG_RECURSIVE);
        H_TEST_ASSERT(verbose == 3);
        H_TEST_ASSERT(out_fname == NULL);
    }
}

TEST_UNIT(getopt_test)
{
    getopt_test();
    //TODO
}
