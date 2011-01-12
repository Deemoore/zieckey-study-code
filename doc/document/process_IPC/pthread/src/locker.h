/* ----------------------------------------------
//
//	locker.h
//		implement a CLock class, used for multi-thread
//	operation
//
//	author: luckzj
//	time  : 31/Dec. 2008
//	platform: Fedora Core 7.0 
//	compiler: g++ 4.1.2
// 
// ---------------------------------------------*/

#ifndef LUCKZJ_LOCKER_H
#define LUCKZJ_LOCKER_H

#include "pthread.h"


class CLock
{
	// mutex
private:
	pthread_mutex_t mutex;

	// ctor & dtor
public:
	CLock();
	~CLock();
	// public interface
public:
	int lock ();
	int unlock ();
	bool isLocked ();
	int tryLock ();
	
};

#endif
