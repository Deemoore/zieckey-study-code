// gzipdemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../GZipHelper.h"
int _tmain(int argc, _TCHAR* argv[])
{
   /*
	FILE *ain=fopen("d:\\BigExample.txt","rb");
	fseek( ain,0,SEEK_END);
	long size=ftell(ain);
	fseek(ain,0,SEEK_SET);
    
	char* buffer=(char*)malloc(size);
	size_t count0=fread(buffer,1,size,ain);
    CA2GZIP gzip(buffer,size);

    FILE *aout=fopen("d:\\BigExample.gz","wb");
	size_t count1=fwrite(gzip.pgzip,1,gzip.Length,aout);
  */
	
	FILE *in=fopen("d:\\BigExample.gz","rb");
	FILE *out=fopen("c:\\BigExample.txt","wb");
	fseek( in,0,SEEK_END);
	long size=ftell(in);
	fseek(in,0,SEEK_SET);
    LPGZIP buffer=(LPGZIP)malloc(size);
	size_t count0=fread(buffer,1,size,in);
    
	CGZIP2A a(buffer,count0);
	size_t count=strlen(a.psz);
	size_t count1=fwrite(a.psz,1,a.Length,out);
    
	return 0;
}

