#include <stdio.h>

struct i1
{
	virtual void m1(){}//���нӿھ���Ҫд�ɴ��麯��
	int ii1;
};

struct c1:i1//cc1��ֻ�Ŷ�i1��ʵ��
{
	int cc1;
	virtual void m1(){printf("m1 %d ",ii1=1);}
};

struct i2d
{
	virtual void m2(){}//���нӿھ���Ҫд�ɴ��麯��
	int ii2;
};
struct i2:i2d,i1{};

struct c2:i2d,c1//����ʵ�־���������ʽ,c2��ֻ��i2�е�ʵ�֣���������������c1d�еĺ���
{
	int ic2;
	virtual void m2(){printf("m2");}
};

struct i3d
{
	virtual void m3(){}//���нӿھ���Ҫд�ɴ��麯��
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