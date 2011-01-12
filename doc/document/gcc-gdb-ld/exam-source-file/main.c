// name£º main.c
// This file is used to test how to use GCC.It is very simple,ha!
// Author : zieckey
// data : 2006/11/13

#include <stdio.h>

int calcFactorial (int n);

int main (void)
{
	int n , result ;

	printf("Please input a number which you want to calculator :");
	scanf("%d",&n);
	
	result = calcFactorial ( n );
	
	if ( 0 == result )
		printf( "There something wrong with the input number!\n");
	else
		printf( "The result of calcFactorial %d is : %d \n" , n , result );
	
	return 0;
	
}
