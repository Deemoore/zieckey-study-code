/********************************************************************************************
**	Name:pthread_join.c
**	Used to study the multithread programming in Linux OS
**	A example showing a thread to be waited to end.
**	Author:zeickey
**	Date:2008/6/28		
**	Copyright (c) 2006,All Rights Reserved!
*********************************************************************************************/

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
//#include <malloc.h>
void *thread(void *str)
{
	int i;
	for (i = 0; i < 1; ++i)
	{
		sleep(1);
		printf( "This in the thread : %d\n" , i );
	}
	
	char* buf = (char*)malloc( sizeof(char) * 100);
	strcpy(buf, "Hello world");
	return (void*)buf;
}

int main()
{
	pthread_t pth;
	int i;
	int ret = pthread_create(&pth, NULL, thread, (void *)(i));
	
	char* buf;
	pthread_join(pth, &buf);
	printf ("thread return value: %s\n", buf);
	for (i = 0; i < 1; ++i)
	{
		sleep(1);
		printf( "This in the main : %d\n" , i );
	}
	
	return 0;
}

