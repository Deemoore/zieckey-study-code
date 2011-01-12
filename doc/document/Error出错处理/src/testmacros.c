/*
*	testmacros.c - Exercise the function defined in filefcn.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "filefcn.h"

int main(void)
{
	FILE *fp;
	
	if ( open_file( &fp, "test.txt", "w", __LINE__, __FILE__ ) )
	{
		return EXIT_FAILURE;
	}
	else
	{
		fputs( "This is the text proves we scribbled in the file.\n", fp );
		fclose( fp );
	}
	
	if ( open_file ( &fp, "noexitfile.txt", "r", __LINE__, __FILE__ ) )
	{
		return EXIT_FAILURE;
	}
	else
	{
		fclose( fp );
	}
	
	return 0;
}
