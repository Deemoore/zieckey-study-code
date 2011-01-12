#include <string.h>
#include <stdio.h>

int main(void)
{
	int i;
	
	for ( i=0; i<10; i++ )
	{
		printf( "%d:%s\n", i, strerror(i) );
	}	
	
	return 0;
}
