#include <stdlib.h>
#include <stdio.h>

void my_exit(void)
{
	printf( "Before exit....\n" );
}

int main(void)
{
	atexit( my_exit );
	return 0;
}
