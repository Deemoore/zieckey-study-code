/*******************************************************************************************
** Name:fork.c
**	This program is used to show the usage of fork() .
** Author:zieckey,(zieckey@yahoo.com.cn)
** Date:2007/9/29 21:33
** All rights reserved!
*******************************************************************************************/

#include <unistd.h>
#include <stdio.h>

int main(void)
{
	pid_t pid;
	int count=0;
	/*此处，执行fork调用，创建了一个新的进程，
	这个进程共享父进程的数据和堆栈空间等，这之后的代码指令为子进程创建了一个拷贝。
	fock 调用是一个复制进程，fock 不象线程需提供一个函数做为入口， 
	fock调用后，新进程的入口就在 fock的下一条语句。*/
	pid = fork();
	
	/*此处的pid的值，可以说明fork调用后，目前执行的是那父进程还是子进程*/
	printf( "Now, the pid returned by calling fork() is %d\n", pid );
	
	if ( pid>0 )
	{				
		/*当fork在子进程中返回后，fork调用又向父进程中返回子进程的pid，
		如是该段代码被执行，但是注意的事，count仍然为0，
		因为父进程中的count始终没有被重新赋值,
		这里就可以看出子进程的数据和堆栈空间和父进程是独立的，而不是共享数据*/
		printf( "This is the parent process,the child has the pid:%d\n", pid );
		printf( "In the parent process,count = %d\n", count );
	}	
	else if ( !pid )
	{	/*在子进程中对count进行自加1的操作，但是并没有影响到父进程中的count值，父进程中的count值仍然为0*/	
		printf( "This is the child process.\n");
		printf( "Do your own things here.\n" );
		count++;
		printf( "In the child process, count = %d\n", count );
	}
	else 
	{
		printf( "fork failed.\n" );
	}
	
	return 0;
}
