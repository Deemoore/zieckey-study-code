2008.03.17
用Eclipse开发C++

1、安装JDK和Eclipse
这里就不多说，具体请见：http://blog.chinaunix.net/u/16292/showart_223309.html
我的安装环境是jdk1.5，eclipse3.2.1

2、安装C++的Ecilpse插件CDT
cdt插件的下载：
http://www.eclipse.org/cdt/
http://download.eclipse.org/tools/cdt/builds/

或者：
4、打开Eclipse，选择Help、Software Update、Find and Install

5、选择Search new features，点Next

6、点击New Remote Site,在Name框输入CDT（名字，可以随自己喜欢），URL框输入http://update.eclipse.org/tools/cdt/releases/new

3、选择一个windows下C++编译器，这里我们选择Cygwin
下载安装地址：http://sourceware.org/cygwin/
这里重点介绍下。

  step1. 下载后，点击安装文件(setup.exe)进行安装，第一个画面是GNU版权说明，点"下一步(N)—>"，
进入安装模式选择画面。

  step2. 安装模式有"Install from Internet"、"Download form Internet"、
"Install from Local Directory" 三种。"Install form Internet"就是直接从internet上装，适用于网速较快的情况。如果你和我一样网速不是很快，或者说装过之后想把下载的安装文件保存起来，下次不再下载了直接安装，就应该选择"Download form Internet"，下载安装的文件（大约40M左右）。
事实上，所谓的"本地安装版"，也是别人从网上下载全部文件后打的包(适用于中国国情嘛^_^)
  
  step3. 接下来是选择安装目的路径和安装源文件所在的路径，之后就进入了选择安装包所在的路径。
注意了阿，这里可是重头戏。我第一安装的时候就是没有看清这一步，结果没有把gcc装进去，导致没法编译文件。
   + All  Default
      + Admin Default
       ....
      + Devel   Default
      + Editors Default
      ....
如上图所示，你在这个TreeView的某个节点上双击，就可以改变它的状态，如Default、Install、Uninstall、Reinstall四种状态。默认的都是Default状态，很多工具的默认状态都是不安装。
在这里我选择了在All这一行上后面的Default上点Install，全部安装，以免后患。（注意：这里的树形控件和win下面的不同，你试试点在All上点 和 在All这一行后面的Default上点，会有不同的响应）

  step4. 点下一步，安装成功。它会自动在你的桌面上建立一个快捷方式。
  
  最后别忘了设置下你的Path环境变量：
例如我的：
Path
D:\cygwin\bin;%SystemRoot%\system32;%SystemRoot%;%SystemRoot%\System32\Wbem;%JAVA_HOME%\bin
“D:\cygwin\bin;”是cygwin安装目录
	
4、测试

现在测试你的编译器和make程序是否能正常工作。
新建一个managed make C++   project（自动生成makefile),然后新建一个Source file，内容如下：
#include <iostream>  
  
using namespace std;  
  
int main()  
{  
    cout<<"Hello world!"<<endl;  
	return 0;
}

在项目名称上点击右键选择"run as -> run local C/C++ application"
在下方是不是看到程序运行的结果了呢？

	


5、其它安装wxWidgets
wxWidgets是什么？我想你一定听说过wxWindows。今年，在MS的压力下，wxWindows开发团队不得不将其更名为wxWidgets，不过它还是像原来一样出色。
在Windows下开发不可避免的要涉及GUI设计的内容。如果仅使用MinGW的Win32API接口就太落伍了。wxWidgets无疑是一个很好的选择。
到wxWidgets 的网站http://wxWindows.sourceforge.net上，下载2.4.2或2.5.3版的wxWidgets，然后解压缩，注意，解 压缩的路径不能包含空格字符。然后参照docs\msw\install.txt编译生成需要的程序库。
（注意：你可能需要安装更多的MinGW工具以完成wxWidgets的编译，这些工具在wxWidgets的网站上也有下载。）
现在，打开Eclipse，新建一个标准Make C++项目，添加一个wxWidgets中的例子。然后在项目选项中，设置构建器命令为：make -f makefile.g95，然后保存。构建项目，运行。你期望的窗体出现了。 














VC_HOME=D:\softwareBackup\coding\vc98
Include=%VC_HOME%\VC98\Include;%Include%
path=%VC_HOME%\VC98\bin;%VC_HOME%\common\Tools;%path%
lib=%VC_HOME%\VC98\lib;%lib%






关于链表和二叉树节点删除的技巧
 
前两天笔试威盛，看到一个题目，问如何能够删除一条单向链表中的任意一个节点P，前提是不知道该链表的表头Head?

  此题让我想起来前段时间看过的关于删除二叉树的节点的一个算法。

  二叉树节点删除有三种情况：
   (1)*p是叶子(即它的孩子数为0)

    　无须连接*p的子树，只需将*p的双亲*parent中指向*p的指针域置空即可。

   (2)*p只有一个孩子*child
    　只需将*child和*p的双亲直接连接后，即可删去*p。
    注意：
    　*p既可能是*parent的左孩子也可能是其右孩子，而*child可能是*p的左孩子或右孩子，故共有4种状态。

   (3)*p有两个孩子
    　先令q=p，将被删结点的地址保存在q中；然后找*q的中序后继*p，并在查找过程中仍用parent记住*p的双亲位置。*q的中序后继*p一定是 *q的右子树中最左下的结点，它无左子树。因此，可以将删去*q的操作转换为删去的*p的操作，即在释放结点*p之前将其数据复制到*q中，就相当于删去了*q.

   看第三中情况，也就是当P有两个孩子节点，不容易处理的时候可以考虑删除P的后继节点，而将后继节点的值拷贝到P中来，这跟删除单向链表中任意节点采用的方法其实是一样的，在单向链表中可以删除P的Next节点，把Next节点的值拷贝到P节点中，实质也是删除了节点P。 
 
 
 2008.4.13
 C++中，把负数赋值给 unsigned 对象是完全合法的，其结果是该负数对该 unsigned 类型最大数＋1（例如 unsigned char 为 255＋1）取模。
 例如，如果把 －1 赋值给8位的 unsigned char 类型变量，那么结果是 255。因为 －1 对 256 求模后就是 255。
 
 
int ival1(1024);	//direct-initialization 直接初始化 
int ival2 = 1024;	//copy-initialization 复制初始化
直接初始化语法更灵活且效率更高。

通常把一个对象定义在它首次使用的地方是一个很好的办法。
 



2008.4.14
const用法:
文件一：
//const.h
extern const int BufSize = 512;

文件二中：
//const_test.cpp
#include <iostream>
using namespace std;
extern const int BufSize;
int main()
{
	cout<<"BufSize = "<<BufSize<<endl;
	return 0;
}

const对象默认为文件的局部变量，如果想在文件外访问const变量，
需要将const变量显式声明为extern类型。



用class和struct关键字定义类的唯一差别在于默认访问级别：
默认情况下，struct 的成员为 public，而 class 的成员为 private。
见下面示例：

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







头文件用于声明而不是用于定义

当设计头文件时，记住定义和声明的区别是很重要的。定义只可以出现一次，而声明则可以出现多次（第 2.3.5 节）。下列语句是一些定义，所以不应该放在头文件里：

     extern int ival = 10;      // initializer, so it's a definition
     double fica_rate;          // no extern, so it's a definition

虽然 ival 声明为 extern，但是它有初始化式，代表这条语句是一个定义。类似地，fica_rate 的声明虽然没有初始化式，但也是一个定义，因为没有关键字 extern。同一个程序中有两个以上文件含有上述任一个定义都会导致多重定义链接错误。

因为头文件包含在多个源文件中，所以不应该含有变量或函数的定义。
所以，声明变量一定要使用extern关键字，同时不能初始化。
对于头文件不应该含有定义这一规则，有三个例外。头文件可以定义类、值在编译时就已知道的 const 对象和 inline 函数。这些实体可在多个源文件中定义，只要每个源文件中的定义是相同的。在头文件中定义这些实体，是因为编译器需要它们的定义（不只是声明）来产生代码。



2008/12/31
随机数的产生

加上time参数就可以嘛。。。
srand(time(0));	//设置种子
i=rand();		//随机数的产生
只要种子数一样，通过rand产生的随机数也一样。

这样i就是一个真正意义上的随机数。。


时间相关函数：
struct   tm   *localtime(long   *clock)  
  本函数把clock所指的时间(如函数time返回的时间)转换成当地标准时间,并以tm结构形式返回    
  char* asctime(struct   tm   *tm)    
  本函数把指定的tm结构类的时间转换成下列格式的字符串:    
  Mon   Nov   21   11:31:54   1983\n\0    
   
   
  总时间日期贮存结构tm    
  ┌──────────────────────┐    
  │struct   tm                                                                       │    
  │{                                                                                       │    
  │   int   tm_sec;       /*秒,0-59*/                                     │    
  │   int   tm_min;       /*分,0-59*/                                     │    
  │   int   tm_hour;     /*时,0-23*/                                     │    
  │   int   tm_mday;     /*天数,1-31*/                                 │    
  │   int   tm_mon;       /*月数,0-11*/                                 │    
  │   int   tm_year;     /*自1900的年数*/                           │    
  │   int   tm_wday;     /*自星期日的天数0-6*/                 │    
  │   int   tm_yday;     /*自1月1日起的天数,0-365*/       │    
  │   int   tm_isdst;   /*是否采用夏时制,采用为正数*/│    
  │}                                                                                       │    
  └──────────────────────┘    
   
  
  time_t   t;  
  struct   tm*   pt;  
  t   =   time(NULL);  
  pt   =   localtime(&t);  
   
  结构   struct   tm   的说明参见localtime的说明。