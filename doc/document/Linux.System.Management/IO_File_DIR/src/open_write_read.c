#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int fd,size;
	char s[]="This program is used to show how to use open(),write(),read() function.\nHave fun!\n   \n";
	char buffer[80];
	
	fd = open( "temp.log", O_WRONLY|O_CREAT );//以可读写的方式打开一个文件，如果不存在则创建该文件
	if ( -1 == fd )
	{
		printf("Open or create file named \"temp.log\" failed.\n");
		return -1;
	}
	write( fd, s, sizeof(s) );//向该文件中写入一个字符串
	close( fd );
	
	fd = open( "temp.log", O_RDONLY );
	if ( -1 == fd )
	{
		printf("Open file named \"temp.log\" failed.\n");
		return -1;
	}
	size = read( fd, buffer, sizeof(s) );//读取文件内容保存到buffer指定的字符串数组中，返回读取的字符个数
	close( fd );
	printf( "%s", buffer );
	
	return 0;
}
