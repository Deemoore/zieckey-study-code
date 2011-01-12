#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	char temp[] = "tempfile_XXXXXX";
	char content[] = "This is written by the program.";
	int fd;
	fd = mkstemp( temp );
	write( fd, content, sizeof(content) );
	printf( "The template file name is %s\n", temp );
	close( fd );
	return 0;	
}
