#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int retval;
	
	retval = system( "ls -l -t" );
	if ( 127 == retval )
	{
		fprintf( stderr, "/bin/sh not available\n" );
		exit(127);
	}
	else if ( -1 == retval )
	{
		perror( "system" );
		exit(EXIT_FAILURE);
	}
	else if ( 0 != retval )
	{
		fprintf( stderr, "command returned %d \n", retval );
		perror( "ls" );
	}
	else
	{
		puts( "command successfully executed" );
	}
	
	return 0;
}
