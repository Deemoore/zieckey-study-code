/*
*	filefcn.c - A function to open files,using __LINE__ and __FILE__
*/

#include <stdio.h>
#include "filefcn.h"

int open_file( FILE **fp, char *fname, char *mode, int line, char *file )
{
	if ( NULL == (*fp = fopen(fname, mode)) )
	{
		fprintf( stderr, "[%s:%d] open_file() failed.\n", file ,line );
		return 1;
	}
	
	return 0;
}
