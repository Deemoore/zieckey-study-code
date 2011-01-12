// 
// File:   main.cc
// Author: root
//
// Created on August 11, 2007, 11:36 PM
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
#include <netdb.h>
#include <errno.h>

#define MAX_CONTENT_SIZE 200
#define BACKLOG 20

typedef struct s_client_t {
    int sockfd;
    char addr[20];
    char user[30];
} client_t;

typedef struct s_socklink_t
{
	int sockfd;
	struct s_socklink_t* pnext;
} socklink_t;

static socklink_t* socklink_head = NULL;
static socklink_t* socklink_end = NULL;
static int connect_num = 0;


void threadfunc (client_t* client)
{
	int sockfd = client->sockfd;
	char user[30];
	char addr[20];

	char recvbuf[MAX_CONTENT_SIZE];
	char sendbuf[MAX_CONTENT_SIZE];	
	size_t len = 0;
	int i = 0;

	socklink_t* socklink_pcur = NULL;
	socklink_t* socklink_ppre = NULL;

	// get username and addr
	strcpy (user, client->user);
	strcpy (addr, client->addr);

	// recving data
	while (1)
	{
		len = recv (sockfd, (void*)recvbuf, MAX_CONTENT_SIZE, 0);
		// user quit
		if (0 >= len)
		{
			connect_num --;

			// delete sockfd from the socklink data structure
			socklink_ppre = socklink_head;
			if (socklink_ppre->sockfd == sockfd)
			{
				socklink_head = socklink_ppre->pnext;
				delete socklink_ppre;
				socklink_ppre = NULL;
			}
			else 
			{
				socklink_pcur = socklink_head->pnext;
				while (socklink_pcur != NULL)
				{	
					// delete from data link
					if (socklink_pcur->sockfd == sockfd)
					{
						socklink_ppre->pnext = socklink_pcur->pnext;
						delete socklink_pcur;
						socklink_pcur = NULL;
						break;
					}
	
					socklink_ppre = socklink_pcur;
					socklink_pcur = socklink_pcur->pnext;
				}
			}

			// send out quit message
			sprintf (sendbuf, "user %s quited.\n", user);
			printf (sendbuf);
			socklink_pcur = socklink_head;
			while (socklink_pcur != NULL)
			{
				send (socklink_pcur->sockfd, (void*)sendbuf, MAX_CONTENT_SIZE, 0);
				socklink_pcur = socklink_pcur->pnext;
			}
			pthread_exit (NULL);
		}
		else
		{
			sprintf (sendbuf, "%s said %s.\n", user, recvbuf);
			printf (sendbuf);
			socklink_pcur = socklink_head;
			while (socklink_pcur != NULL)
			{
				send (socklink_pcur->sockfd, (void*)sendbuf, MAX_CONTENT_SIZE, 0);
				socklink_pcur = socklink_pcur->pnext;
			}
		}
		
	}
	
}

int main(int argc, char** argv) 
{
     
    // validate params
	if ( 2 != argc ) 
	{
		printf ("wrong param num.\n");
		fprintf(stderr,"Usage:%s portnumber\a\n",argv[0]);
		return 0;
	}
   
	int myport = 0;
	myport = atoi (argv[1]);
    
	// init sock
	int sockfd = socket (AF_INET, SOCK_STREAM, 0);
	if ( -1 == sockfd ) 
	{
 		printf ("init socket error.\n");
 		return 0;
	}

	// init my addr
	struct sockaddr_in myaddr;
	myaddr.sin_addr.s_addr =  inet_addr("127.0.0.1");
	myaddr.sin_family = AF_INET;
	myaddr.sin_port =  htons (myport);
	memset (&(myaddr.sin_zero), 0, 8);
    
	// bind to server
	if ( -1 == bind(sockfd, (struct sockaddr*)&myaddr, sizeof(struct sockaddr)) ) 
	{
		printf ("%s\n", strerror(errno));
		return 0;
   	 }
    
	if ( -1 == listen(sockfd, BACKLOG) ) 
	{
		printf ("socket listen failed.\n");
 		return 0;
	}
    
	// start network service loop
	struct sockaddr_in clientaddr;
	int clientfd;
	client_t client;
	size_t size = sizeof (struct sockaddr);
   pthread_t thread_id;
   char content[MAX_CONTENT_SIZE];
  
	int i = 0;

	socklink_t* ptmp = NULL;
	// init socklink

	while (1)
	{
		printf ("waiting for new connection...\n");
		clientfd = accept (sockfd, (struct sockaddr*)&clientaddr, &size);
		printf ("new connnection detected.\n");
		if ( -1 == clientfd ) 
		{
			clientfd = 0;
			continue;
		}

		// add data into socklink
		ptmp = new socklink_t;
		ptmp->sockfd = clientfd;
		ptmp->pnext  = NULL;
		
		// if init
		if (socklink_head == NULL)
		{
			socklink_head = ptmp;
			socklink_end  = ptmp;
			socklink_end->pnext = NULL;
		}
		else
		{
			socklink_end->pnext = ptmp;
			socklink_end = ptmp;
		}
		

	
		// send out connection message and create a new thread
		client.sockfd = clientfd;
		strcpy (client.addr, inet_ntoa (clientaddr.sin_addr));
             		
		size = recv (clientfd, (void*)content, MAX_CONTENT_SIZE, 0);
		strcpy (client.user, content);

		printf ("user %s from %s connected, total connection num:%d\n", client.user, client.addr, connect_num+1);
		connect_num ++;

		// send out message
		sprintf (content, "user %s entered the chat room.\n", client.user);
		ptmp = socklink_head;
		while (ptmp != NULL)
		{
			send (ptmp->sockfd, (void*)content, MAX_CONTENT_SIZE, 0);
			ptmp = ptmp->pnext;
		}

		// create new thread
		if ( 0!= pthread_create (&thread_id, NULL, (void*(*)(void*))threadfunc, (void*)&client) ) 
		{ 
			printf ("create thread failed.\n");
			continue;
		}
            
	}

 
    return (EXIT_SUCCESS);
}




