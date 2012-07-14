/********************************************************************************************
**	Name:client.c
**	Used to study the network programming in Linux OS.
**	Showing how to use the functions,
** like socket,bind,listen,accept and write.
**	This is the client program.
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

int main(int argc, char *argv[])
{
	int sockfd;
	char buffer[1024];
	struct sockaddr_in server_addr;
	char *ip;
	int portnumber,nbytes;
	
	if( 3 != argc )
	{
		fprintf(stderr,"Usage:%s ip portnumber\a\n",argv[0]);
		return 1;
	}
	
	printf("agrv[1] = %s\n",argv[1]);
	if( 9 > strlen(ip=argv[1]) )
	{
		fprintf(stderr,"Get Ip address error\n");
		return 1;
	}
	
	if( 0 > (portnumber=atoi(argv[2])) )
	{
		fprintf(stderr,"Usage:%s ip portnumber\a\n",argv[0]);
		return 1;
	}
	
	/* 客户程序开始建立 sockfd描述符 */
	if( -1 == (sockfd=socket(AF_INET,SOCK_STREAM,0)))
	{
		fprintf(stderr,"Socket Error:%s\a\n",strerror(errno));
		return 1;
	}
	
	/* 客户程序填充服务端的资料 */
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(portnumber);
	server_addr.sin_addr.s_addr = inet_addr(ip);
	
	/* 客户程序发起连接请求 */
	if( -1 == connect(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr)) )
	{
		fprintf(stderr,"Connect Error:%s\a\n",strerror(errno));
		return 1;
	}
	
	/* 连接成功了 */
	if( -1 == (nbytes=read(sockfd,buffer,1024)) )
	{
		fprintf(stderr,"Read Error:%s\n",strerror(errno));
		return 1;
	}
	buffer[nbytes]='\0';
	printf("I have received:%s\n",buffer);
	/* 结束通讯 */
	close(sockfd);
	return 0;
}
