/* ----------------------------------------------
//
//	locker.cpp
//		implement a CLock class, used for multi-thread
//	operation
//
//	author: luckzj
//	time  : 31/Dec. 2008
//	platform: Fedora Core 7.0
//	compiler: g++ 4.1.2
//
// ---------------------------------------------*/

#include "locker.h"


CLock::CLock()
{
	pthread_mutex_init( &mutex, NULL );
}


int CLock::lock ()
{
 	return pthread_mutex_lock (&mutex);
}

int CLock::unlock ()
{
	return pthread_mutex_unlock (&mutex);
}

bool CLock::isLocked ()
{
	if ( 0 == pthread_mutex_trylock(&mutex) )
	{
		pthread_mutex_unlock (&mutex);
		return false;
	}
	return true;
}

int CLock::tryLock()
{
	return pthread_mutex_trylock( &mutex );
}

CLock::~CLock()
{
	pthread_mutex_destroy( &mutex );
}

/*
///////////////////////// test locker ///////////////////////
#include "iostream"
using namespace std;

CLock locker;

bool g_bFlag = true;
void* threadfunc (void* param)
{
	while (1)
	{
		cout << "in thread is locked:" << locker.isLocked() << endl;
		cout << "in thread waiting lock..." << endl;
		locker.lock ();
		cout << "in thread lock okay" << endl;
		locker.unlock ();
		cout << "in thread unlocked" << endl;
		sleep (1);
	}
}

int main ()
{
	pthread_t id;
	char buf[100];
	pthread_create (&id, NULL, threadfunc, NULL);
	cout << "press any key to lock:" << endl;
	cin >> buf;
	cout << "locking..." << endl;
	locker.lock ();
	cout << "press any key to unlock:" << endl;
	cin >> buf;
	locker.unlock ();
	sleep (2);
	return 0;
}

*/
