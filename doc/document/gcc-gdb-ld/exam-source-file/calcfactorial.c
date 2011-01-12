// name£º calcfactorial.c
// A function is defined in this file.
// Author : zieckey
// data : 2006/11/13

#include <stdio.h>

int calcFactorial (int n)
{
	if (n <= 1)
		return 1;
		
	else if ( n > 15 )
	{
		printf("Please input a number less than 15 , try again! \n");	
		return 0;
	}	
	

	else
		return calcFactorial (n - 1) * n;
}
