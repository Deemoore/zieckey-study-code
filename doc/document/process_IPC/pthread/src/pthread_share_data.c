/********************************************************************************************
**	Name:pthread_share_data.c
**	Used to study the multithread programming in Linux OS
**	A example showing a thread sharing data with main function.
**	Author:zeickey
**	Date:2006/9/16		
**	Copyright (c) 2006,All Rights Reserved!
*********************************************************************************************/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

static int a=4;
void *create(void *arg)
{
	printf("new pthread ... \n");
	printf("a=%d  \n",a);
	return (void *)0;
}

int main(int argc,char *argv[])
{
	pthread_t tidp;
	int error;
	
	a=5;

	error=pthread_create(&tidp, NULL, create, NULL);

	if(error!=0)
	{
		printf("new thread is not create ... \n");
		return -1;
	}
	
	sleep(1);
	
	printf("new thread is created ... \n");
	return 0;
}
