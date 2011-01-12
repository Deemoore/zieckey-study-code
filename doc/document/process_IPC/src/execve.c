/****************************************************************************
**
**	execve.c--Illustrate the usage of execve
**
*****************************************************************************/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main( void )
{
	char* args[] = { "/bin/ls", NULL };

	if ( -1 == (execve("/bin/ls", args, NULL)) )
	{
		perror( "execve" );
		exit( EXIT_FAILURE);
	}
	
	puts( "shouldn't get here" );
	exit( EXIT_SUCCESS );
}
