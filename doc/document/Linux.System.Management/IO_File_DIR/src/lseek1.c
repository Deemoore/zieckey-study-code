
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int fd, i, rev;
	char buf1[] = "abcdefghij";
	char buf2[] = "ABCDEFGHIJ";

	fd = creat( "file.hole", O_WRONLY|O_CREAT );//以可读写的方式打开一个文件，如果不存在则创建该文件
	
	write( fd, buf1, 10 );
	
	lseek( fd, 96, SEEK_SET );
	
	write( fd, buf2, 10 );	
	
	close( fd );
	return 0;
}

