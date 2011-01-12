// name£º testgbd.c
// This file is used to test how to use gdb to debug a c program .It is very simple ! Enjoy yourself!
// Author : zieckey
// data : 2006/11/13

#include <stdio.h>

int accumulate( int n )
{
	int sum = 0 , i ;
	
	for( i=1; i<=n; i++)
	{
		sum += i;
	}
	
	return sum;
}

int main( void )
{
	int i , n ;
	int result ;
	
	printf("Please input a number which you want to calculator :");
	scanf("%d",&n);
	
	result = accumulate ( n ) ;
	
	printf("The result of accumulating from 1 to %d is : %d \n" , n , result ) ;
	
	return 0;
}
