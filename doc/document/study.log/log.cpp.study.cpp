2008.03.17
��Eclipse����C++

1����װJDK��Eclipse
����Ͳ���˵�����������http://blog.chinaunix.net/u/16292/showart_223309.html
�ҵİ�װ������jdk1.5��eclipse3.2.1

2����װC++��Ecilpse���CDT
cdt��������أ�
http://www.eclipse.org/cdt/
http://download.eclipse.org/tools/cdt/builds/

���ߣ�
4����Eclipse��ѡ��Help��Software Update��Find and Install

5��ѡ��Search new features����Next

6�����New Remote Site,��Name������CDT�����֣��������Լ�ϲ������URL������http://update.eclipse.org/tools/cdt/releases/new

3��ѡ��һ��windows��C++����������������ѡ��Cygwin
���ذ�װ��ַ��http://sourceware.org/cygwin/
�����ص�����¡�

  step1. ���غ󣬵����װ�ļ�(setup.exe)���а�װ����һ��������GNU��Ȩ˵������"��һ��(N)��>"��
���밲װģʽѡ���档

  step2. ��װģʽ��"Install from Internet"��"Download form Internet"��
"Install from Local Directory" ���֡�"Install form Internet"����ֱ�Ӵ�internet��װ�����������ٽϿ���������������һ�����ٲ��Ǻܿ죬����˵װ��֮��������صİ�װ�ļ������������´β���������ֱ�Ӱ�װ����Ӧ��ѡ��"Download form Internet"�����ذ�װ���ļ�����Լ40M���ң���
��ʵ�ϣ���ν��"���ذ�װ��"��Ҳ�Ǳ��˴���������ȫ���ļ����İ�(�������й�������^_^)
  
  step3. ��������ѡ��װĿ��·���Ͱ�װԴ�ļ����ڵ�·����֮��ͽ�����ѡ��װ�����ڵ�·����
ע���˰������������ͷϷ���ҵ�һ��װ��ʱ�����û�п�����һ�������û�а�gccװ��ȥ������û�������ļ���
   + All  Default
      + Admin Default
       ....
      + Devel   Default
      + Editors Default
      ....
����ͼ��ʾ���������TreeView��ĳ���ڵ���˫�����Ϳ��Ըı�����״̬����Default��Install��Uninstall��Reinstall����״̬��Ĭ�ϵĶ���Default״̬���ܶ๤�ߵ�Ĭ��״̬���ǲ���װ��
��������ѡ������All��һ���Ϻ����Default�ϵ�Install��ȫ����װ������󻼡���ע�⣺��������οؼ���win����Ĳ�ͬ�������Ե���All�ϵ� �� ��All��һ�к����Default�ϵ㣬���в�ͬ����Ӧ��

  step4. ����һ������װ�ɹ��������Զ�����������Ͻ���һ����ݷ�ʽ��
  
  �����������������Path����������
�����ҵģ�
Path
D:\cygwin\bin;%SystemRoot%\system32;%SystemRoot%;%SystemRoot%\System32\Wbem;%JAVA_HOME%\bin
��D:\cygwin\bin;����cygwin��װĿ¼
	
4������

���ڲ�����ı�������make�����Ƿ�������������
�½�һ��managed make C++   project���Զ�����makefile),Ȼ���½�һ��Source file���������£�
#include <iostream>  
  
using namespace std;  
  
int main()  
{  
    cout<<"Hello world!"<<endl;  
	return 0;
}

����Ŀ�����ϵ���Ҽ�ѡ��"run as -> run local C/C++ application"
���·��ǲ��ǿ����������еĽ�����أ�

	


5��������װwxWidgets
wxWidgets��ʲô��������һ����˵��wxWindows�����꣬��MS��ѹ���£�wxWindows�����ŶӲ��ò��������ΪwxWidgets��������������ԭ��һ����ɫ��
��Windows�¿������ɱ����Ҫ�漰GUI��Ƶ����ݡ������ʹ��MinGW��Win32API�ӿھ�̫�����ˡ�wxWidgets������һ���ܺõ�ѡ��
��wxWidgets ����վhttp://wxWindows.sourceforge.net�ϣ�����2.4.2��2.5.3���wxWidgets��Ȼ���ѹ����ע�⣬�� ѹ����·�����ܰ����ո��ַ���Ȼ�����docs\msw\install.txt����������Ҫ�ĳ���⡣
��ע�⣺�������Ҫ��װ�����MinGW���������wxWidgets�ı��룬��Щ������wxWidgets����վ��Ҳ�����ء���
���ڣ���Eclipse���½�һ����׼Make C++��Ŀ�����һ��wxWidgets�е����ӡ�Ȼ������Ŀѡ���У����ù���������Ϊ��make -f makefile.g95��Ȼ�󱣴档������Ŀ�����С��������Ĵ�������ˡ� 














VC_HOME=D:\softwareBackup\coding\vc98
Include=%VC_HOME%\VC98\Include;%Include%
path=%VC_HOME%\VC98\bin;%VC_HOME%\common\Tools;%path%
lib=%VC_HOME%\VC98\lib;%lib%






��������Ͷ������ڵ�ɾ���ļ���
 
ǰ���������ʢ������һ����Ŀ��������ܹ�ɾ��һ�����������е�����һ���ڵ�P��ǰ���ǲ�֪��������ı�ͷHead?

  ��������������ǰ��ʱ�俴���Ĺ���ɾ���������Ľڵ��һ���㷨��

  �������ڵ�ɾ�������������
   (1)*p��Ҷ��(�����ĺ�����Ϊ0)

    ����������*p��������ֻ�轫*p��˫��*parent��ָ��*p��ָ�����ÿռ��ɡ�

   (2)*pֻ��һ������*child
    ��ֻ�轫*child��*p��˫��ֱ�����Ӻ󣬼���ɾȥ*p��
    ע�⣺
    ��*p�ȿ�����*parent������Ҳ���������Һ��ӣ���*child������*p�����ӻ��Һ��ӣ��ʹ���4��״̬��

   (3)*p����������
    ������q=p������ɾ���ĵ�ַ������q�У�Ȼ����*q��������*p�����ڲ��ҹ���������parent��ס*p��˫��λ�á�*q��������*pһ���� *q���������������µĽ�㣬��������������ˣ����Խ�ɾȥ*q�Ĳ���ת��Ϊɾȥ��*p�Ĳ����������ͷŽ��*p֮ǰ�������ݸ��Ƶ�*q�У����൱��ɾȥ��*q.

   �������������Ҳ���ǵ�P���������ӽڵ㣬�����״����ʱ����Կ���ɾ��P�ĺ�̽ڵ㣬������̽ڵ��ֵ������P���������ɾ����������������ڵ���õķ�����ʵ��һ���ģ��ڵ��������п���ɾ��P��Next�ڵ㣬��Next�ڵ��ֵ������P�ڵ��У�ʵ��Ҳ��ɾ���˽ڵ�P�� 
 
 
 2008.4.13
 C++�У��Ѹ�����ֵ�� unsigned ��������ȫ�Ϸ��ģ������Ǹø����Ը� unsigned �����������1������ unsigned char Ϊ 255��1��ȡģ��
 ���磬����� ��1 ��ֵ��8λ�� unsigned char ���ͱ�������ô����� 255����Ϊ ��1 �� 256 ��ģ����� 255��
 
 
int ival1(1024);	//direct-initialization ֱ�ӳ�ʼ�� 
int ival2 = 1024;	//copy-initialization ���Ƴ�ʼ��
ֱ�ӳ�ʼ���﷨�������Ч�ʸ��ߡ�

ͨ����һ�������������״�ʹ�õĵط���һ���ܺõİ취��
 



2008.4.14
const�÷�:
�ļ�һ��
//const.h
extern const int BufSize = 512;

�ļ����У�
//const_test.cpp
#include <iostream>
using namespace std;
extern const int BufSize;
int main()
{
	cout<<"BufSize = "<<BufSize<<endl;
	return 0;
}

const����Ĭ��Ϊ�ļ��ľֲ���������������ļ������const������
��Ҫ��const������ʽ����Ϊextern���͡�



��class��struct�ؼ��ֶ������Ψһ�������Ĭ�Ϸ��ʼ���
Ĭ������£�struct �ĳ�ԱΪ public���� class �ĳ�ԱΪ private��
������ʾ����

#include <iostream>
using namespace std;
struct StructA
{
	StructA()
	{
		x = 100;	
	}	
	
	int x;
};
class ClassB
{
public:
	ClassB()
	{
		x = 100;	
	}	
	
	int x;
};
int main(void)
{
	StructA sa;
	cout<<"sa.x="<<sa.x<<endl;
	
	ClassB cb;
	cout<<"cb.x="<<cb.x<<endl;
	
	return 0;
}







ͷ�ļ������������������ڶ���

�����ͷ�ļ�ʱ����ס����������������Ǻ���Ҫ�ġ�����ֻ���Գ���һ�Σ�����������Գ��ֶ�Σ��� 2.3.5 �ڣ������������һЩ���壬���Բ�Ӧ�÷���ͷ�ļ��

     extern int ival = 10;      // initializer, so it's a definition
     double fica_rate;          // no extern, so it's a definition

��Ȼ ival ����Ϊ extern���������г�ʼ��ʽ���������������һ�����塣���Ƶأ�fica_rate ��������Ȼû�г�ʼ��ʽ����Ҳ��һ�����壬��Ϊû�йؼ��� extern��ͬһ�������������������ļ�����������һ�����嶼�ᵼ�¶��ض������Ӵ���

��Ϊͷ�ļ������ڶ��Դ�ļ��У����Բ�Ӧ�ú��б��������Ķ��塣
���ԣ���������һ��Ҫʹ��extern�ؼ��֣�ͬʱ���ܳ�ʼ����
����ͷ�ļ���Ӧ�ú��ж�����һ�������������⡣ͷ�ļ����Զ����ࡢֵ�ڱ���ʱ����֪���� const ����� inline ��������Щʵ����ڶ��Դ�ļ��ж��壬ֻҪÿ��Դ�ļ��еĶ�������ͬ�ġ���ͷ�ļ��ж�����Щʵ�壬����Ϊ��������Ҫ���ǵĶ��壨��ֻ�����������������롣



2008/12/31
������Ĳ���

����time�����Ϳ��������
srand(time(0));	//��������
i=rand();		//������Ĳ���
ֻҪ������һ����ͨ��rand�����������Ҳһ����

����i����һ�����������ϵ����������


ʱ����غ�����
struct   tm   *localtime(long   *clock)  
  ��������clock��ָ��ʱ��(�纯��time���ص�ʱ��)ת���ɵ��ر�׼ʱ��,����tm�ṹ��ʽ����    
  char* asctime(struct   tm   *tm)    
  ��������ָ����tm�ṹ���ʱ��ת�������и�ʽ���ַ���:    
  Mon   Nov   21   11:31:54   1983\n\0    
   
   
  ��ʱ����������ṹtm    
  ������������������������������������������������    
  ��struct   tm                                                                       ��    
  ��{                                                                                       ��    
  ��   int   tm_sec;       /*��,0-59*/                                     ��    
  ��   int   tm_min;       /*��,0-59*/                                     ��    
  ��   int   tm_hour;     /*ʱ,0-23*/                                     ��    
  ��   int   tm_mday;     /*����,1-31*/                                 ��    
  ��   int   tm_mon;       /*����,0-11*/                                 ��    
  ��   int   tm_year;     /*��1900������*/                           ��    
  ��   int   tm_wday;     /*�������յ�����0-6*/                 ��    
  ��   int   tm_yday;     /*��1��1���������,0-365*/       ��    
  ��   int   tm_isdst;   /*�Ƿ������ʱ��,����Ϊ����*/��    
  ��}                                                                                       ��    
  ������������������������������������������������    
   
  
  time_t   t;  
  struct   tm*   pt;  
  t   =   time(NULL);  
  pt   =   localtime(&t);  
   
  �ṹ   struct   tm   ��˵���μ�localtime��˵����