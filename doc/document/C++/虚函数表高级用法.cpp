#include <stdio.h>

struct i1
{
	virtual void m1(){}//所有接口均不要写成纯虚函数
	int ii1;
};

struct c1:i1//cc1中只放对i1的实现
{
	int cc1;
	virtual void m1(){printf("m1 %d ",ii1=1);}
};

struct i2d
{
	virtual void m2(){}//所有接口均不要写成纯虚函数
	int ii2;
};
struct i2:i2d,i1{};

struct c2:i2d,c1//所有实现均是这种形式,c2中只放i2中的实现，这样不妨碍调用c1d中的函数
{
	int ic2;
	virtual void m2(){printf("m2");}
};

struct i3d
{
	virtual void m3(){}//所有接口均不要写成纯虚函数
	int ii3;
};
struct i3:i3d,i2{};
struct c3:i3d,c2
{
	int ic3;
	virtual void m3(){printf("m3");}
};
void main()
{
	c3 c3test;
	i3 * t=static_cast<i3*>(static_cast<i1*>(&c3test));
		t->m1();
	t->m2();
	t->m3();
}