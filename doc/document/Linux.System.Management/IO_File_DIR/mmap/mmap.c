/************************************************************************************************************************************
 
 本程序给出了内存映射函数 mmap 的用法。

 头文件：
 #include <sys/mman.h>
 
 函数：void *mmap(void *start,size_t length,int prot,int flags,int fd,off_t offsize);

 参数start：指向欲映射的内存起始地址，通常设为 NULL，代表让系统自动选定地址，映射成功后返回该地址。

 参数length：代表将文件中多大的部分映射到内存。

 参数prot：映射区域的保护方式。可以为以下几种方式的组合：
 PROT_EXEC 映射区域可被执行
 PROT_READ 映射区域可被读取
 PROT_WRITE 映射区域可被写入
 PROT_NONE 映射区域不能存取

 参数flags：影响映射区域的各种特性。在调用mmap()时必须要指定MAP_SHARED 或MAP_PRIVATE。
 MAP_FIXED 如果参数start所指的地址无法成功建立映射时，则放弃映射，不对地址做修正。通常不鼓励用此旗标。
 MAP_SHARED对映射区域的写入数据会复制回文件内，而且允许其他映射该文件的进程共享。
 MAP_PRIVATE 对映射区域的写入操作会产生一个映射文件的复制，即私人的“写入时复制”（copy on write）对此区域作的任何修改都不会写回原来的文件内容。
 MAP_ANONYMOUS建立匿名映射。此时会忽略参数fd，不涉及文件，而且映射区域无法和其他进程共享。
 MAP_DENYWRITE只允许对映射区域的写入操作，其他对文件直接写入的操作将会被拒绝。
 MAP_LOCKED 将映射区域锁定住，这表示该区域不会被置换（swap）。

 参数fd：要映射到内存中的文件描述符。如果使用匿名内存映射时，即flags中设置了MAP_ANONYMOUS，fd设为-1。有些系统不支持匿名内存映射，则可以使用fopen打开/dev/zero文件，然后对该文件进行映射，可以同样达到匿名内存映射的效果。

 参数offset：文件映射的偏移量，通常设置为0，代表从文件最前方开始对应，offset必须是分页大小的整数倍。

 返回值：

 若映射成功则返回映射区的内存起始地址，否则返回MAP_FAILED(－1)，错误原因存于errno 中。
 
 *************************************************************************************************************************************/
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>

//定义存放记录的结构体
typedef struct
{
	int index; //编号
	char text[10]; //内容
} RECORD;

#define SIZE (50)
#define EDIT_INDEX (10)

int main(void)
{
	RECORD record, *p_mapped_memory_addr;
	int i, fd;
	FILE *fp;

	//创建文件并写入测试数据
	fp = fopen("records.dat", "w+");
	for (i = 0; i < SIZE; i++)
	{
		record.index = i;
		sprintf(record.text, "No.%d", i);
		fwrite(&record, sizeof(record), 1, fp);//因为字节序对齐，在32位机上，sizeof(record)＝16，并不是14。
	}
	fclose(fp);
	printf("Ok, write %d records to the file: records.dat .\n", SIZE);

	//将第一30条记录编号修改为300，并相应地修改其内容。
	//采用传统方式
	fp = fopen("records.dat", "r+");
	fseek(fp, EDIT_INDEX * sizeof(record), SEEK_SET);
	fread(&record, sizeof(record), 1, fp);

	record.index = EDIT_INDEX*10;
	sprintf(record.text, "No.%d", record.index);

	fseek(fp, EDIT_INDEX * sizeof(record), SEEK_SET);
	fwrite(&record, sizeof(record), 1, fp);
	fclose(fp);
	printf("Ok, edit the file of records.dat using traditional method.\n");

	/////////////////////////////////////////
	//同样的修改，这次使用内存映射方式。
	//将记录映射到内存中
	fd = open("records.dat", O_RDWR);
	p_mapped_memory_addr = (RECORD *)mmap(0, SIZE * sizeof(record), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	//修改数据
	p_mapped_memory_addr[EDIT_INDEX].index = EDIT_INDEX*10;
	sprintf(p_mapped_memory_addr[EDIT_INDEX].text, "No.%d",
			p_mapped_memory_addr[EDIT_INDEX].index);

	/* Synchronize the region starting at ADDR and extending LEN bytes with the
	   file it maps.  Filesystem operations on a file being mapped are
	   unpredictable before this is done.  Flags are from the MS_* set.

	   This function is a cancellation point and therefore not marked with
	   __THROW.  
	   extern int msync (void *__addr, size_t __len, int __flags);
	   */
	//将修改写回映射文件中(采用异步写方式)
	msync((void *)p_mapped_memory_addr, SIZE * sizeof(record), MS_ASYNC);
	/* Deallocate any mapping for the region starting at ADDR and extending LEN
	   bytes.  Returns 0 if successful, -1 for errors (and sets errno).  
	   extern int munmap (void *__addr, size_t __len) __THROW;
	   */
	//释放内存段
	munmap((void *)p_mapped_memory_addr, SIZE * sizeof(record));
	printf("Ok, edit the file of records.dat using mmap method.\n");

	//关闭文件
	close(fd);
	
	return 0;

}


