/********************************************************************************************
**	Name:pthread_exit.c
**	Used to study the multithread programming in Linux OS
**	A example showing a thread to exit and with a return code.
**	Author:zeickey
**	Date:2006/9/16		
**	Copyright (c) 2006,All Rights Reserved!
*********************************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *create(void *arg)
{
	printf("new thread is created ... \n");
	return (void *)8;
}

int main(int argc,char *argv[])
{
	pthread_t tid;
	int error;
	void *temp;

	error = pthread_create(&tid, NULL, create, NULL);

	if( error )
	{
		printf("thread is not created ... \n");
		return -1;
	}
	error = pthread_join(tid, &temp);

	if( error )
	{
		printf("thread is not exit ... \n");
		return -2;
	} 
	
	printf("thread is exit code %d \n", (int )temp);
	return 0;
}

