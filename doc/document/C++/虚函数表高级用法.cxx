#include <stdio.h>
struct classhead
{
	virtual void classdummy(){}
};
struct i1
{
	virtual void m1(){}//���нӿھ���Ҫд�ɴ��麯��
	int ii1;
};
struct c1d
{
	int ic1;
};
struct c1:classhead,c1d,i1//cc1��ֻ�Ŷ�i1��ʵ��
{
	virtual void m1(){printf("m1");}
};
struct i2:i1
{
	virtual void m2(){}//���нӿھ���Ҫд�ɴ��麯��
	int ii2;
};
struct c2d:c1d//���滹���Է�һЩ����Ҫ�õ��Ľṹ��ʵ�ֶ��ؼ̳�
{
	int ic2;
};
struct c2:classhead,c2d,i2//����ʵ�־���������ʽ,c2��ֻ��i2�е�ʵ�֣���������������c1d�еĺ���
{
	virtual void m2(){printf("m2");}
};

struct i3:i2
{
	virtual void m3(){}//���нӿھ���Ҫд�ɴ��麯��
	int ii3;
};
struct c3d:c2d//���滹���Է�һЩ����Ҫ�õ��Ľṹ��ʵ�ֶ��ؼ̳�
{
	int ic3;
};
struct c3:classhead,c3d,i3//����ʵ�־���������ʽ,c2��ֻ��i2�е�ʵ�֣���������������c1d�еĺ���
{
	virtual void m3(){printf("m3");}
};
//����Լ�����һ�����������������
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
	//��ʼ�����,���������ȫ����ͨ������ʵ��
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


	//���˿���ʹ����
	o3->m1();
	o3->m2();
	o3->m3();
}