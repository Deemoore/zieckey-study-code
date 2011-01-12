/*******************************************************************************************
** Name:lseek.c
**		This program is used to show the usage of lseek() .
** Author:zieckey
** Date:2007/9/29
** All rights reserved!
*******************************************************************************************/

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int fd, i, rev;
	char buf[] = "Hello world!";

	fd = open( "temp.log", O_WRONLY|O_CREAT );//以可读写的方式打开一个文件，如果不存在则创建该文件
	
	for( i=0; i<10; i++ )
	{
		write( fd, buf, sizeof(buf) );
		lseek( fd, -5, SEEK_CUR);
	}
	
	close( fd );
	return 0;
}
