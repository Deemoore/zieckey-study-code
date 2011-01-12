/********************************************************************************************
**	Name: pthread_access_mem_with_mutex.cpp
**		This program shows how to use mutex to protect memmery
**		when the different threads access the same memmery at the same time.
**	Author: zeickey
**	Date:2009/1/12		
**	Copyright (c) 2009 
*********************************************************************************************/
#include <pthread.h>
#include <iostream>
#include "locker.h"

using namespace std;

CLock locker;

struct Node {
	int data;
	struct Node* next;
	
	Node( int a, struct Node* prev) 
	{ 
		data = a; 
		next = NULL;
		if ( prev )
		{
			prev->next = this;
		}
	}
};

void* threadfunc1 (void* param);
void* threadfunc2 (void* param);

int main(int argc, char *argv[])
{
	Node* head = new Node( 100, NULL );
	new Node( 200, head );
	new Node( 300, head->next );
	
	pthread_t id1, id2;
	
	pthread_create( &id1, NULL, threadfunc1, (void*)head);
	pthread_create( &id2, NULL, threadfunc2, (void*)head);
	
	pthread_join( id1, NULL);
	pthread_join( id2, NULL);
	return 0;
}


void* threadfunc1 (void* param)
{
	::locker.lock();
	Node* p = (Node*)param;
	while ( p )
	{
		if ( 200 == p->data )	
		{
			sleep(3);
			cout << "3 seconds later, in thread1, it happened : " << endl;
			cout << "p->data = " << p->data << endl;
			p->data = p->data + 22;
			cout << "p->data = " << p->data << endl;
			break;	
		}
		p = p->next;
	}
	::locker.unlock();
}

void* threadfunc2 (void* param)
{
	Node* p = (Node*)param;
	Node* next = NULL;
	while ( p )
	{
		if ( !::locker.isLocked() )
		{	
			::locker.lock();
			next = p->next;
			cout << "The deleted node data is : " << p->data << endl;
			delete p;
			p = NULL;
			p = next;
			::locker.unlock();
		}	
		else 
		{
			cout << "Oh, no, the memmery is locked, it can not be accessed. We will try later" << endl;	
			sleep(1);
		}
	}
}

