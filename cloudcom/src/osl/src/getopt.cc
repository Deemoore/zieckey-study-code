

#if ( defined(__linux__) || defined( __gnu_linux__) || defined(__GNUC__) )
//no need to do anything
#else
//windows
#include "../include/getopt.h"

#if 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* optarg = NULL;
int optind = 0;
int opterr = 1;
int optopt = '?';

static char** prev_argv = NULL;       
static int prev_argc = 0;             
static int argv_index = 0;            
static int argv_index2 = 0;           
static int opt_offset = 0;            
static int dashdash = 0;              
static int nonopt = 0;                
static void increment_index()
{

    if(argv_index < argv_index2)
    {
        while(prev_argv[++argv_index] && prev_argv[argv_index][0] != '-'
            && argv_index < argv_index2+1);
    }
    else argv_index++;
    opt_offset = 1;
}


static int permute_argv_once()
{

    if(argv_index + nonopt >= prev_argc) return 1;

    else
    {
        char* tmp = prev_argv[argv_index];

        memmove(&prev_argv[argv_index], &prev_argv[argv_index+1],
            sizeof(char**) * (prev_argc - argv_index - 1));
        prev_argv[prev_argc - 1] = tmp;
        nonopt++;
        return 0;
    }
}

int getopt(int argc, char** argv, char* optstr)
{
    int c = 0;

    if(prev_argv != argv || prev_argc != argc)
    {

        prev_argv = argv;
        prev_argc = argc;
        argv_index = 1;
        argv_index2 = 1;
        opt_offset = 1;
        dashdash = 0;
        nonopt = 0;
    }

getopt_top:

    optarg = NULL;

    if(argv[argv_index] && !strcmp(argv[argv_index], "--"))
    {
        dashdash = 1;
        increment_index();
    }

    if(argv[argv_index] == NULL)
    {
        c = -1;
    }

    else if(dashdash || argv[argv_index][0] != '-' || !strcmp(argv[argv_index], "-"))
    {

        if(optstr[0] == '-')
        {
            c = 1;
            optarg = argv[argv_index];
            increment_index();
        }

        else if(optstr[0] == '+' || getenv("POSIXLY_CORRECT"))
        {
            c = -1;

            nonopt = argc - argv_index;
        }

        else
        {
            if(!permute_argv_once()) goto getopt_top;
            else c = -1;
        }
    }

    else
    {
        char* opt_ptr = NULL;

        c = argv[argv_index][opt_offset++];

        if(optstr[0] == '-') opt_ptr = strchr(optstr+1, c);
        else opt_ptr = strchr(optstr, c);

        if(!opt_ptr)
        {
            if(opterr)
            {
                fprintf(stderr, "%s: invalid option -- %cn", argv[0], c);
            }
            optopt = c;
            c = '?';

            increment_index();
        }

        else if(opt_ptr[1] == ':')
        {

            if(argv[argv_index][opt_offset] != ' ')
            {
                optarg = &argv[argv_index][opt_offset];
                increment_index();
            }

            else if(opt_ptr[2] != ':')
            {

                if(argv_index2 < argv_index) argv_index2 = argv_index;
                while(argv[++argv_index2] && argv[argv_index2][0] == '-');
                optarg = argv[argv_index2];

                if(argv_index2 + nonopt >= prev_argc) optarg = NULL;

                increment_index();
            }
            else
            {

                increment_index();
            }

            if(optarg == NULL && opt_ptr[2] != ':')
            {
                optopt = c;
                c = '?';
                if(opterr)
                {
                    fprintf(stderr,"%s: option requires an argument -- %cn",
                        argv[0], optopt);
                }
            }
        }

        else
        {

            if(argv[argv_index][opt_offset] == ' ')
            {
                increment_index();
            }
        }
    }

    if(c == -1)
    {
        optind = argc - nonopt;
    }
    else
    {
        optind = argv_index;
    }
    return c;
}
#endif

/**
* Licensed to the Apache Software Foundation (ASF) under one or more
* contributor license agreements.  See the NOTICE file distributed with
* this work for additional information regarding copyright ownership.
* The ASF licenses this file to You under the Apache License, Version 2.0
* (the "License"); you may not use this file except in compliance with
* the License.  You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifndef AXIS2_GET_OPT_DEFINE_MODE_NO_IMPORT
/** Required by "axutil_getopt_windows.h" */
#define AXIS2_GET_OPT_DEFINE_MODE_NO_IMPORT
#endif
//#include <platforms/windows/axutil_getopt_windows.h>

#include "../include/getopt.h"

int optind = 1;
int opterr = 1;
int optopt;
char *optarg;

#define AXIS2_OPT_ERR_NO_ARG         1
#define AXIS2_OPT_ERR_INVALID_OPTION   2
#define AXIS2_OPT_ERR_BAD_ARG         3

int
_axis2_opt_error(
                 int __optopt,
                 int __err,
                 int __showerr)
{
    switch (__err)
    {
    case AXIS2_OPT_ERR_NO_ARG:
        if (__showerr)
            fprintf(stderr, " option requires an argument -- %c\n", __optopt);
        break;
    case AXIS2_OPT_ERR_INVALID_OPTION:
        if (__showerr)
            fprintf(stderr, " illegal option -- %c\n", __optopt);
        break;
    case AXIS2_OPT_ERR_BAD_ARG:
        return (int) ':';
    default:
        if (__showerr)
            fprintf(stderr, "unknown\n");
    }
    return (int) '?';
}

int getopt(
           int __argc,
           char *const *__argv,
           const char *__shortopts)
{
    static char *pos = "";
    char *olstindex = NULL;

    if (!*pos)
    {
        /** no option or invalid option */
        if (optind >= __argc || *(pos = __argv[optind]) != '-')
        {
            pos = "";
            return -1;
        }

        /**-- option*/
        if (pos[1] && *++pos == '-')
        {
            ++optind;
            pos = "";
            return -1;
        }
    }

    if ((optopt = (int) *pos++) == (int) ':')
    {
        if (optopt == (int) '-')
            return -1;
        if (!*pos)
            ++optind;
        if (*__shortopts != ':')
            return _axis2_opt_error(optopt, AXIS2_OPT_ERR_BAD_ARG, opterr);
        _axis2_opt_error(optopt, AXIS2_OPT_ERR_INVALID_OPTION, opterr);
    }
    else
    {
        //olstindex = strchr(const_cast<char*>(__shortopts), optopt);
        olstindex = strchr((char*)(__shortopts), optopt);
        if (!olstindex)
        {
            if (optopt == (int) '-')
                return -1;
            if (!*pos)
                ++optind;
            if (*__shortopts != ':')
                return _axis2_opt_error(optopt, AXIS2_OPT_ERR_BAD_ARG, opterr);
            _axis2_opt_error(optopt, AXIS2_OPT_ERR_INVALID_OPTION, opterr);
        }
    }
    if (!olstindex || *++olstindex != ':')
    {
        optarg = NULL;
        if (!*pos)
            ++optind;
    }
    else
    {
        if (*pos)
            optarg = pos;
        else if (__argc <= ++optind)
        {
            pos = "";
            if (*__shortopts == ':')
                return _axis2_opt_error(-1, AXIS2_OPT_ERR_BAD_ARG, opterr);
            return _axis2_opt_error(optopt, AXIS2_OPT_ERR_NO_ARG, opterr);
        }
        else
            optarg = __argv[optind];
        pos = "";
        ++optind;
    }
    return optopt;
}


#endif
