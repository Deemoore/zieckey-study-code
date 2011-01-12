// 
// File:   main.cc
// Author: root
//
// Created on August 12, 2007, 1:08 AM
//

#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>

#define STDIN 0
#define MAX_CONTENT_SIZE 200
// 
//

void threadfunc (int* p_sockfd)
{
	int sockfd = * p_sockfd;
	char content[MAX_CONTENT_SIZE];
	size_t len;
	// get input from keyboard
	while (1)
	{
		gets (content);
		// send to server
		len = send (sockfd, (void*)content, MAX_CONTENT_SIZE, 0);
	}
}



int main(int argc, char** argv) 
{
	char user[30];
	char server_addr[10];
	int  server_port = 0;
	pthread_t thread_id;
    
	printf ("please input server ip:");
	scanf ("%s", server_addr);
	printf ("please input server port:");
	scanf ("%d", &server_port);
	printf ("please input your name:");
	scanf ("%s", user);
    
	int sockfd = socket (AF_INET, SOCK_STREAM, 0);
	if ( -1 == sockfd ) 
	{
		printf ("init socket error.\n");
		return 0;
	}
        
	// init server addr
	struct sockaddr_in addr;
	addr.sin_addr.s_addr = inet_addr(server_addr);
	addr.sin_family = AF_INET;
	addr.sin_port =  htons (server_port);
	memset (&(addr.sin_zero), 0, 8);
    
 	// connect to server
	if ( -1 == connect(sockfd, (struct sockaddr*)&addr, sizeof(struct sockaddr)) ) 
	{
		printf ("connect to server failed.\n") ;
		printf ("%s\n", strerror(errno));
		return 0;
	}
 
	// create a new thread to input message from keyboard
	if ( 0!= pthread_create (&thread_id, NULL, (void*(*)(void*))threadfunc, (void*)&sockfd) ) 
        {
		printf ("create thread failed.\n");
		return 0;
        }

	// send basic information
	send (sockfd, (void*)user, 30, 0);
    
	// start chating, init select
	char content[MAX_CONTENT_SIZE];
	while (1)
	{
		if ( 0 < recv(sockfd, (void*)content, MAX_CONTENT_SIZE, 0)) 
		{
			printf ("%s", content);				
		}
		else {
			printf ("server closed, 88\n");
			return 1;
		}
		
	}
	return (EXIT_SUCCESS);
}

