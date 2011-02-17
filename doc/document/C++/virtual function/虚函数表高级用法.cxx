#include <stdio.h>
struct classhead
{
	virtual void classdummy(){}
};
struct i1
{
	virtual void m1(){}//所有接口均不要写成纯虚函数
	int ii1;
};
struct c1d
{
	int ic1;
};
struct c1:classhead,c1d,i1//cc1中只放对i1的实现
{
	virtual void m1(){printf("m1");}
};
struct i2:i1
{
	virtual void m2(){}//所有接口均不要写成纯虚函数
	int ii2;
};
struct c2d:c1d//后面还可以放一些其他要用到的结构，实现多重继承
{
	int ic2;
};
struct c2:classhead,c2d,i2//所有实现均是这种形式,c2中只放i2中的实现，这样不妨碍调用c1d中的函数
{
	virtual void m2(){printf("m2");}
};

struct i3:i2
{
	virtual void m3(){}//所有接口均不要写成纯虚函数
	int ii3;
};
struct c3d:c2d//后面还可以放一些其他要用到的结构，实现多重继承
{
	int ic3;
};
struct c3:classhead,c3d,i3//所有实现均是这种形式,c2中只放i2中的实现，这样不妨碍调用c1d中的函数
{
	virtual void m3(){printf("m3");}
};
//最后自己构造一个虚表。。。。。。。
void vcopy(void **dest,void **src)
{
	for(;*src && *(int*)*src;src++,dest++)
	{
		printf("");
		*dest=*src;
	}
}
void main()
{
	//初始化完成,这个过程完全可以通过宏来实现
	c3 c3test;
	c2 c2test;
	c1 c1test;
	void *myvtable[100]={0};

	//memset(myvtable,0,sizeof(myvtable));
	vcopy(myvtable,(void **)*(void **)static_cast<i3 *>(&c3test));
	vcopy(myvtable,(void **)*(void **)static_cast<i2 *>(&c2test));
	vcopy(myvtable,(void **)*(void **)static_cast<i1 *>(&c1test));

	size_t length3=sizeof(c3)-sizeof(void *);
	size_t offset3=((size_t)static_cast<i3*>(&c3test))-((size_t)(&c3test)-sizeof(void*));
	char *p=new char[length3];
	
	*(void ***)(p+offset3)=myvtable;

	i3 * o3=(i3*)(p+offset3);


	//好了可以使用了
	o3->m1();
	o3->m2();
	o3->m3();
}