#include <stdio.h>
#include <string.h>

#define SIZE 300

int main(void)
{
	FILE * fp= NULL;
	char s[]="Hello";
	char buf[SIZE];
	memset(buf,0,SIZE);

	//打开一个文件并清空文件内容，如果不存在，就建立
	fp = fopen("records.dat", "w+");
	fwrite(s, sizeof(s),1, fp);//向文件中写入30个 “Hello“字符串s
	fclose(fp);

	//读取文件内容
	fp = fopen("records.dat", "r+");
	fread(buf, sizeof(s), 1, fp);
	printf("buf=%s", buf);
	fclose(fp);

	return 0;
}
