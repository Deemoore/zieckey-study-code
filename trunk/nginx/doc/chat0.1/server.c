/********************************************************************************************
**	Name:server.c
**	Used to study the network programming in Linux OS.
**	Showing how to use the functions,
** like socket,bind,listen,accept and write.
**	This is the server program.
**	Author:zeickey
**	Date:2006/9/16		
**	Copyright (c) 2006,All Rights Reserved!
*********************************************************************************************/
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int sockfd,new_fd;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	int sin_size,portnumber;
	char hello[]="Hello! Are You Fine?\n";
	
	if( 2 != argc )
	{
		fprintf(stderr,"Usage:%s portnumber\a\n",argv[0]);
		return 1;
	}
	
	if( 0 > (portnumber = atoi(argv[1])) )
	{
		fprintf(stderr,"Usage:%s portnumber\a\n",argv[0]);
		return 1;
	}
	
	/* 服务器端开始建立socket描述符 */
	if( -1 == (sockfd = socket(AF_INET,SOCK_STREAM, 0)) )
	{
		fprintf(stderr,"Socket error:%s\n\a",strerror(errno));
		return 1;
	}
	
	/* 服务器端填充 sockaddr结构 */
	//bzero(&server_addr, sizeof(struct sockaddr_in));
	memset(&server_addr, 0, sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(portnumber);
	
	/* 捆绑sockfd描述符，为下面的listen函数作准备 */
	if( -1 == bind(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr)) )
	{
		fprintf(stderr,"Bind error:%s\n\a",strerror(errno));
		return 1;
	}
	
	/* 监听sockfd描述符 */
	if( -1 == listen(sockfd,5) )
	{
		fprintf(stderr,"Listen error:%s\n\a",strerror(errno));
		return 1;
	}
	
	while(1)
	{
		/* 服务器阻塞,直到客户程序建立连接 */
		sin_size=sizeof(struct sockaddr_in);
		new_fd = accept(sockfd, (struct sockaddr *)(&client_addr), &sin_size);
		if( -1 == new_fd )
		{
			fprintf(stderr,"Accept error:%s\n\a",strerror(errno));
			return 1;
		}
		
		fprintf(stderr,"Server get connection from %s\n", inet_ntoa(client_addr.sin_addr));
		if( -1 == write(new_fd,hello,strlen(hello)) )
		{
			fprintf(stderr,"Write Error:%s\n",strerror(errno));
			return 1;
		}
		/* 这个通讯已经结束 */
		close(new_fd);
		/* 循环下一个 */
	}
	close(sockfd);
	return 0;
}

