#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[] ) 
{
	int 			i;
	struct stat buf;
	char 			*msg;
	
	for ( i=1; i<argc; i++ )
	{
		printf( "%s:	", argv[i] );
		if ( lstat(argv[i], &buf) < 0 ) 
		{
			printf("** lstat error...\n");
			continue;
		}
	
		if ( S_ISREG(buf.st_mode) ) 
		{
			msg = "regular";
		} 
		else if ( S_ISDIR(buf.st_mode) ) 
		{
			msg = "directory";
		} 
		else if ( S_ISCHR(buf.st_mode) ) 
		{
			msg = "character special";
		} 
		else if ( S_ISBLK(buf.st_mode) ) 
		{
			msg = "block special";
		} 
		else if ( S_ISFIFO(buf.st_mode) ) 
		{
			msg = "fifo";
		} 
		else if ( S_ISLNK(buf.st_mode) ) 
		{
			msg = "symbolic link";
		} 
		else if ( S_ISSOCK(buf.st_mode) ) 
		{
			msg = "socket";
		} 
		else 
		{
			msg = " ** unknown mode";
		}
		
		printf( "%s\n", msg );
	}
	
	exit (0);
}
