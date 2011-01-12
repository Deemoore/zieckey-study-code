
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


ͨ�� ��pthread_kill( id, 0 );�� �ķ�ʽȥ�ж��߳��Ƿ���������һ������

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


��δ������ٸ������ǣ����һ���̱߳� pthread_cancel ����֮����ͨ�� ��pthread_kill( id, 0 );�� �ķ�ʽȥ�ж��߳��Ƿ���������һ�������������




���̷߳����ź�

��ʹ�� pthread_kill(3C) ���̷߳����źš�
pthread_kill �﷨

int	 pthread_kill(thread_t tid, int sig);

#include <pthread.h>

#include <signal.h>



int sig;

pthread_t tid;

int ret;



ret = pthread_kill(tid, sig);

pthread_kill() ���ź� sig ���͵��� tid ָ�����̡߳�tid ��ָ�����̱߳���������߳���ͬһ�������С�sig ������������ signal(5) �ṩ���б�

��� sig Ϊ�㣬��ִ�д����飬������ʵ�ʷ����źš��˴������������� tid ����Ч�ԡ�

pthread_kill() �ڳɹ����֮�󷵻��㡣�����κη���ֵ����ʾ�����˴����������������һ�����pthread_kill() ��ʧ�ܲ�������Ӧ��ֵ��

EINVAL
	����:
	sig ����Ч���ź�����

ESRCH
	����:
	��ǰ�Ľ������Ҳ��� tid��

