
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void *thread(void *str)
{
	int i;
	for (i = 0; i < 10; ++i)
	{
		sleep(1);
		printf( "This in the thread : %d\n" , i );
	}
	return NULL;
}

int main()
{
	pthread_t id = 0;
	int i;
	int ret = pthread_create(&id, NULL, thread, (void *)(i));

	sleep(3);

	pthread_cancel( id );
	printf ("After pthread_cancel the thread.\n");
	ret = pthread_kill( id, 0 );
	if (ret != 0)
	{
		printf( "pthread_kill return a nonzero value, that means : Thread is not running.\n" );
	}
	else
	{
		printf( "pthread_kill return a zero value, that means : Thread is running.\n" );
	}

	pthread_join(id, NULL);
	printf ("After the thread has really exited.\n");
	ret = pthread_kill( id, 0 );
	if (ret != 0)
	{
		printf( "pthread_kill return a nonzero value, that means : Thread is not running.\n" );
	}
	else
	{
		printf( "pthread_kill return a zero value, that means : Thread is running.\n" );
	}
	for (i = 0; i < 5; ++i)
	{
		sleep(1);
		printf( "This in the main : %d\n" , i );
	}

	return 0;
}


通过 “pthread_kill( id, 0 );” 的方式去判断线程是否在运行是一个错误

[root@localhost test]# gcc pthread_cancel.c -lpthread -g
[root@localhost test]# ./a.out
This in the thread : 0
This in the thread : 1
After pthread_cancel the thread.
pthread_kill return a zero value, that means : Thread is running.
After the thread has really exited.
pthread_kill return a nonzero value, that means : Thread is not running.
This in the main : 0
This in the main : 1
This in the main : 2
This in the main : 3
This in the main : 4
[root@localhost test]#


这段代码至少告诉我们，如果一个线程被 pthread_cancel 结束之后，再通过 “pthread_kill( id, 0 );” 的方式去判断线程是否在运行是一个错误的做法。




向线程发送信号

请使用 pthread_kill(3C) 向线程发送信号。
pthread_kill 语法

int	 pthread_kill(thread_t tid, int sig);

#include <pthread.h>

#include <signal.h>



int sig;

pthread_t tid;

int ret;



ret = pthread_kill(tid, sig);

pthread_kill() 将信号 sig 发送到由 tid 指定的线程。tid 所指定的线程必须与调用线程在同一个进程中。sig 参数必须来自 signal(5) 提供的列表。

如果 sig 为零，将执行错误检查，但并不实际发送信号。此错误检查可用来检查 tid 的有效性。

pthread_kill() 在成功完成之后返回零。其他任何返回值都表示出现了错误。如果出现以下任一情况，pthread_kill() 将失败并返回相应的值。

EINVAL
	描述:
	sig 是无效的信号量。

ESRCH
	描述:
	当前的进程中找不到 tid。

