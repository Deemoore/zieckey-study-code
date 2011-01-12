JSP	学习

Tomcat JSP配置实例手记


今天以Tomcat软件配置了JSP的开发环境，开始走了很多弯路，
不过通过我的不懈努力终于解决了。
下面将我的经历介绍如下。

一、开发环境配置
　　
　　第一步：下载j2sdk和tomcat：
到sun官方站（http://java.sun.com/j2se/1.5.0/download.jsp）下载j2sdk，
注意下载版本为Windows Offline Installation的SDK，同时最好下载J2SE Documentation，
然后到tomcat官方站点（http://jakarta.apache.org/site/downloads/downloads_tomcat-5.cgi）下载tomcat；
这里我下载的是jdk-1_5_0_08-windows-i586-p.exe和apache-tomcat-5.5.20.exe

　　第二步：安装和配置你的j2sdk和tomcat：
执行j2sdk和tomcat的安装程序，然后按默认设置进行安装即可。
　　
　　1.安装j2sdk以后，需要配置一下环境变量，在我的电脑-＞属性-＞高级-＞环境变量-＞系统变量中添加以下环境变量(假定你的j2sdk安装在C:\Program Files\Java\jdk1.5.0_08）：
　　
JAVA_HOME=C:\Program Files\Java\jdk1.5.0_08
CLASSPATH=.;%JAVA_HOME%\lib;%JAVA_HOME%\lib\dt.jar;%JAVA_HOME%\lib\tools.jar;（.;一定不能少，因为它代表当前路径)
PATH变量的设置:在当前的PATH变量的后面再添加以下内容:
;%JAVA_HOME%\bin (注意不要将原来的内容删除了)

　　接着可以写一个简单的java程序来测试J2SDK是否已安装成功：
　　
public class Hello
{
	public static void main(String[] args)
	{
		System.out.println( "Hello world! My Java!" );
	}

}
　　
　　将上面的这段程序保存为文件名为 Hello.java 的文件。
　　
　　然后打开命令提示符窗口，cd到你的Test.java所在目录，然后键入下面的命令
　　
javac Hello.java
java Hello
　
　　此时如果看到打印出来 Hello world! My Java! 的话说明安装成功了，如果没有打印出这句话，你需要仔细检查一下你的配置情况。
　　
　　2.安装Tomcat
一般的软件安装一样的,这里我安装在C:\Program Files\tomcat5.5
创建环境变量：
依次"我的电脑->属性->高级->环境变量(N)->新建"
变量名为：TOMCAT_HOME，变量值为 C:\Program Files\tomcat5.5
　　
　　然后修改环境变量中的CLASSPATH，把tomat安装目录下的 common\lib 下的(可以根据实际追加)servlet.jar追加到CLASSPATH中去，修改后的CLASSPATH如下：
　　
.;%JAVA_HOME%\lib;%JAVA_HOME%\lib\dt.jar;%JAVA_HOME%\lib\tools.jar;%TOMCAT_HOME%\common\lib\servlet.jar;
　　
　　接着可以启动tomcat，运行Tomcat,C:\Program Files\tomcat5.5\bin\tomcat5.exe
之后可以在浏览器中输入：http://localhost:8080 就可以看到Tomcat的缺省页面了.
编写第一个JSP程序

<%@ page contentType="text/html;charset=gb2312"%>
<%@ page language="java"%>
<html>
<title>第一个JSP程序</title>
<body>
<%out.println("Hello world!");%>
</body>
</html>

将其保存到C:\Program Files\tomcat5.5\webapps\ROOT\hello.jsp

然后再浏览器中输入 http://localhost:8080/hello.jsp 就可以到一个网页，
该网页上输出：
Hello world！

如果不行的话,可以尝试:http://127.0.0.1:8080/hello.jsp,
这样应该就可以了.

下面再给一个显示当前系统时间的例子：

<%@ page contentType="text/html;charset=gb2312"%>
<%@ page language="java"%>
<html>
<title>当前系统时间</title>
<body>
<h3>Today is:
<%= new java.util.Date() %>
</body>
</html>

总结:
这里我详细的纪录了我的正确配置过程.
中途当然也出现很多不愉快的事情。
比如设置环境变量，CLASSPATH等一定要设置正确。
JSP程序也要写对，即使是最简单的这个hello.jsp程序，我也也错了好几次，
首先<%@ page language="java"%>要放到程序开始，
<%@ page contentType="text/html;charset=gb2312"%>
这个也要添加上，不然会出现乱码。
还有就是程序中中英文字符不分也会出现莫名其妙的问题。
好的，祝你JSP之旅一帆风顺。



什么是Tomcat？
Tomcat是一个开放源代码、运行servlet和JSP Web应用软件的基于Java的Web应用软件容器。Tomcat由Apache-Jakarta子项目支持并由来自开放性源代码Java社区的志愿者进行维护。Tomcat Server是根据servlet和JSP规范进行执行的，因此我们就可以说Tomcat Server也实行了Apache-Jakarta规范且比绝大多数商业应用软件服务器要好。

安装Tomcat 5
要开始使用Tomcat 5，你至少要下载Java Development Kit (JDK) 1.4版和Tomcat 5安装包，他们分别是ZIP文件和Windows安装数据包。一旦你安装了这两个数据包，你必须加入两个环境变量：JAVA_HOME和TOMCAT_HOME。JDK将安装在JAVA_HOME目录之中，而Tomcat 5则将安装在TOMCAT_HOME目录之中。


Eclipse3.2中 Java Web 开发环境的搭建之LOMBOZ+TOMCAT 安装

Tomcat安装
点击apache-tomcat-5.0.28安装文件，安装过程同一般的软件安装类似。在这里我采用系统默认的安装路径，在C:\Program Files\Apache Software Foundation\Tomcat 5.0 目录下。

Tomcat的安装采用普通安装的方式。
解压tomcatPluginV3.zip然后把释放出来的com.sysdeo.eclipse.tomcat_3.0.0文件夹复制到eclipse的plugins目录下，这样插件安装完毕。



Lomboz的安装：

After installing Eclipse (but before unzipping the Lomboz plugin), be sure to start up

Eclipse
to complete the installation process.
在装Lomboz插件之前，安装Eclipse，一定要确认运行一次Eclipse来真正完成Eclipse的安装。

After you start eclipse, visit the Java preferences and edit your classpath variables,

making
sure that they are all correct. To do this, on the Eclipse menu bar, select Window ->
Preferences, then open the "Java" node and highlight the "Classpath Variables" node in the
tree on the left side of the dialog. Be sure to remove classpath variables that may appear

to
be incorrect.(Window ->Preferences->Java->Build Path->Classpath Variables)
Shut down Eclipse before starting an eclipse or Lombozinstallation.

Lomboz v3.0 uses models based on eclipse EMF project. If you do not have it
installed already, You will need to download and install EMF runtime builds release
2.0.0 or later.
EMF MUST BE INSTALLED PRIOR TO USING LOMBOZ.

Lomboz需要Eclipse的EMF项目，所以在用Lomboz之前要装好EMF runtime。



Eclipse3.2.1+MyEclipse5.0GA+Tomcat5.5配置JSP开发环境详解

By zieckey (zieckey@yahoo.com.cn)
All Rights Reserved!

	第一步：准备开发工具：
	JDK：jdk-6-windows-i586.exe
	Tomcat：apache-tomcat-5.5.20.exe
	MyEclipse：EnterpriseWorkbenchInstaller_5.0GA_E3.2.exe

　　第二步：安装和配置你的j2sdk和tomcat：
执行j2sdk和tomcat的安装程序，然后按默认设置进行安装即可。
　　
　　1.安装j2sdk以后，需要配置一下环境变量，在我的电脑-＞属性-＞高级-＞环境变量-＞系统变量中添加以下环境变量(假定你的j2sdk安装在M:\Java\jdk1.6.0）：
　　
JAVA_HOME=M:\Java\jdk1.6.0
CLASSPATH=.;%JAVA_HOME%\lib;%JAVA_HOME%\lib\dt.jar;%JAVA_HOME%\lib\tools.jar;（.;一定不能少，因为它代表当前路径)
PATH变量的设置:在当前的PATH变量的后面再添加以下内容:
;%JAVA_HOME%\bin (注意不要将原来的内容删除了)

　　接着可以写一个简单的java程序来测试J2SDK是否已安装成功：
　　
public class Hello
{
 public static void main(String[] args)
 {
  System.out.println( "Hello world! My Java!" );
 }

}
　　
　　将上面的这段程序保存为文件名为 Hello.java 的文件。
　　
　　然后打开命令提示符窗口，cd到你的Test.java所在目录，然后键入下面的命令
　　
javac Hello.java
java Hello
　
　　此时如果看到打印出来 Hello world! My Java! 的话说明安装成功了，如果没有打印出这句话，你需要仔细检查一下你的配置情况。
　　
　　2.安装Tomcat
一般的软件安装一样的,这里我安装在M:\Tomcat5.5
创建环境变量：
依次"我的电脑->属性->高级->环境变量(N)->新建"
变量名为：TOMCAT_HOME，变量值为 M:\Tomcat5.5
　　
　　然后修改环境变量中的CLASSPATH，把tomat安装目录下的 common\lib 下的(可以根据实际追加)servlet.jar追加到CLASSPATH中去，修改后的CLASSPATH如下：
　　
.;%JAVA_HOME%\lib;%JAVA_HOME%\lib\dt.jar;%JAVA_HOME%\lib\tools.jar;%TOMCAT_HOME%\common\lib\servlet.jar;
　　
　　接着可以启动tomcat，运行Tomcat,M:\Tomcat5.5\bin\tomcat5.exe
之后可以在浏览器中输入：http://localhost:8080 就可以看到Tomcat的缺省页面了.
编写第一个JSP程序

<%@ page contentType="text/html;charset=gb2312"%>
<%@ page language="java"%>
<html>
<title>第一个JSP程序</title>
<body>
<%out.println("Hello world!");%>
</body>
</html>

将其保存到M:\Tomcat5.5\webapps\ROOT\hello.jsp

然后再浏览器中输入 http://localhost:8080/hello.jsp 就可以到一个网页，
该网页上输出：
Hello world！

如果不行的话,可以尝试:http://127.0.0.1:8080/hello.jsp,
这样应该就可以了.

	第二步：安装和配置MyEclipse

安装过程很简单，下面着重说明一下配置：
在Eclipse工具栏现在有一个电脑机箱样的图标(左下方还带有一个绿色的箭头),
点击下,会发现出现"No Enable Servers available-Select to View MyEclipse preferences"
这就是说现在MyEclipse还没有可以引用的Web服务器,
刚刚我们装了Tomcat5.5,这就正好可以被用到此次.
继续点击"No Enable Servers available-Select to View MyEclipse preferences",
在弹出来的对话窗中一次选择:
MyEclipse->Application Servers->Tomcat5
选择右边的Enable来激活Tomcat,另外还要选择Tomcat的home路径:M:\Tomcat5.5
选择好后,在点击MyEclipse->Application Servers->Tomcat5->JDK
在右边选择Add...按钮,选择正确的JDK(注意:不是JRE).
这一切做好后,就可以编写JSP程序了.
File->New->Project...->Web Project
(File->New->Project...->MyEclipse->J2EE Projects->Web Project)
输入工程名,这里假设是:HelloJSP
然后在右边的HelloJSP->WebRoot上右键点击,然后选择JSP新建一个JSP文件。
这里就采用Eclipse为我们生成的默认的MyJsp.jsp文件名。
最后还要将我们这个工程部署到一个Server服务器上：
依次右键选择：HelloJSP->MyEclipse->Add and Remove Project Deployments
点击Add按钮，在Server处选择Tomcat5，Finish，OK

可以直接从Eclipse工具栏启动Tomcat，
在浏览器下输入：http://127.0.0.1:8080/HelloJSP/MyJsp.jsp
来查看刚刚那个MyJsp.jsp程序，网页输出：
This is my JSP page.

到此我们的JSP完美开发环境就建立起来了。


2007/1/17
JSP入门初级教程之JSP指令

http://www.webjx.com  更新日期：2005-03-04 10:33  出处：网页教学网  作者：



＜JSP directive mso-hansi-font-family:""＞影响servlet 类的整体结构。它常用以下形式：

＜%@ directive attribute=”value”%＞
　　
　　而且，您可以将多个属性写在一个语句中：

　　＜%@ directive attribute1="value1" attribute2="value2" attributeN="valueN" %＞

　　有两种主要的directive:

　　page,允许您做一些类似import classes的事，定义servlet的超类（Superclass），
mso-hansi-font-family:""＞等；

　　include,允许您将文件插入servlet类中（当JSP文件翻译为servlet时）。

　　一、JSP page Directive

　　语法：

＜%@ page
[ language="java" ]
[ extends="package .class" ]
[ import="{package .class | .*}, ..." ]
[ session="true|false" ]
[ buffer="none|8kb|sizekb" ]
[ autoFlush="true|false" ]
[ isThreadSafe="true|false" ]
[ info="text" ]
[ errorPage="relativeURL" ]
[ contentType="mimeType [ ;charset=characterSet ]" |
"text/html ; charset=ISO-8859-1" ]
[ isErrorPage="true|false" ]

%＞

　　Page directive mso-hansi-font-family:""＞允许您定义一些区分大小写的属性：

　　(1)import = “package.class”或 import = “package.class1,..,package.classN”。
mso-hansi-font-family:""＞

　　您可以定想要import的packages。例如：

＜%@ page import="java.util.*" %＞

　　import属性是这几个属性中唯一一个可以在一个JSP中出现多次的。

　　(2)contenType = “MIME=Type” 或contentType=“MIME-Type;charset=Character-Set”mso-hansi-font-family:""＞

　　它指定输出的MIME类型。缺省为“text/html”。例如:

＜%@ page contentType="text/plain" %＞"

　　在scriptlet中等价于：

＜% response.setContentType("text/plain"); %＞

　　(3)isThreadSafe = “true | false”.如果值为“true”（缺省）表示：将进行普通的servlet处理，多个请求将被一个servlet实例并行处理，在这种情况下，编程人员同步访问多个实例变量。值为“false”时表示：servlet将实现单线程模式（SingleThreadModel）,不管请求是顺序提交还是并发出现，都将提供不同的分离的servlet实例。

　　（4）session=”true | false”。 如果值为“true”（缺省）表示：预定义变量session（继承HttpSession）应该绑定到一个已存在的session，否则就应该创建一个并将之绑定。值为“false”时表示：将不使用session变量，如果试图使用，将在JSP向servlet转化时出现错误。

　　（5）buffer = “sizekb | none”。为JspWriter输出确定缓冲的大小。缺省由服务器而定，但至少要有8kb。

　　（6）autoflush=”true | false”。 如果值为“true mso-hansi-font-family:""＞”（缺省）表示：当缓冲满时将自动清空，值为“false mso-hansi-font-family:""＞”时表示：当缓冲满时递出一个异常，这很少使用。当buffer=”none”是若用false mso-hansi-font-family:""＞值是不合法的。

　　(7)extends=”package.class”。这将为servlet产生一个超类。请特别谨慎的使用这一功能，因为，服务器也许已经定义了一个。

　　(8)info = “message”。定义一个可以通过调用getServletInfo方法得到的串。

　　(9)errorPage = “URL”。指定一个JSP mso-hansi-font-family:""＞页面来处理任何一个可抛出的但当前页面并未处理的意外错误。

　　(10)isErrorPage = “true | false”。指定当前页面是否可以处理来自另一个页面的错误，缺省为“false”。

　　(11)language = “java” mso-hansi-font-family:""＞。指出以下将使用的语言。不过，不必为这一属性费心，因为，“java mso-hansi-font-family:""＞”既是缺省又是唯一合法的选择。

　　二JSP include Directive 这种directive 使您可以在JSP转换为servlet时将一个文件包含进来。语法：

＜jsp:include page="{relativeURL | ＜%= expression %＞}" flush="true" /＞mso-hansi-font-family:";mso-font-kerning: 0pt"＞或
＜jsp:include page="{relativeURL | ＜%= expression %＞}" flush="true" ＞
＜jsp:param name="parameterName"
value="{parameterValue | ＜%=expression %＞}" /＞+
＜/jsp:include＞

　　URL mso-hansi-font-family:""＞通常相对于指向它的JSP页面，但是，普遍使用相对“URL”，您可以使用一个斜杠“/”作为URL的开始来告知系统URL mso-hansi-font-family:""＞相对的Web server的主路径。被包含的文件将以规则的JSP形式来解析，因此，您可以在其中使用静态HTML,scripting elements,directives,和 actions。

　　让我们来看一个例子，许多站点在每一个页面上包含一个小型的导航条。它通常出现在页面的顶部或左右侧，并包含在每一个页面里。这用include directive 来实现是很自然的，若用规则的HTML mso-hansi-font-family:""＞来把这些语句拷到每一个页面无疑是个梦魇。请看下列代码：

＜HTML＞
＜HEAD＞
＜TITLE＞ JSP教程＜/TITLE＞
＜/HEAD＞
＜BODY＞
＜%@ include file="/navbar.html" %＞
＜!— 本页面的其他部分... --＞
＜/BODY＞
＜/HTML＞

　　因为文件是在页面被转换时插入的，因此，如果导航条改变了，您需要将所有指向它的JSP mso-hansi-font-family:""＞页面全部重新编译一次。如果您的导航条并不常改变这样做无疑是高效的，但是，如果您的被包含文件更改频繁，则建议您使用jsp:include action（后面将谈到）来替代，它在页面被请求时才包含文件。


安装MySQL
Enable TCP/IP Networking
	port 3306
测试MySQL
	运行MySQL Server

	M:\Documents and Settings\apple>mysqld-nt --help
mysqld-nt  Ver 5.0.22-community-nt for Win32 on ia32 (MySQL Community Edition (G
PL))
Copyright (C) 2000 MySQL AB, by Monty and others
This software comes with ABSOLUTELY NO WARRANTY. This is free software,
and you are welcome to modify and redistribute it under the GPL license

Starts the MySQL database server

Usage: mysqld-nt [OPTIONS]

For more help options (several pages), use mysqld --verbose --help

	这里可以看到mysqld-nt.exe是MySQL database server
我们再运行客户端进行连接:
一、连接MYSQL。
格式： mysql -h主机地址 -u用户名 －p用户密码
1、例1：连接到本机上的MYSQL。
   首先在打开DOS窗口，然后进入目录 mysqlbin，再键入命令mysql -uroot -p，回车后提示你输密码，如果刚安装好MYSQL，超级用户root是没有密码的，故直接回车即可进入到MYSQL中了，MYSQL的提示符是：mysql>

   	M:\Documents and Settings\apple>mysql -uroot -p
	Enter password:
	Welcome to the MySQL monitor.  Commands end with ; or \g.
	Your MySQL connection id is 1 to server version: 5.0.22-community-nt

	Type 'help;' or '\h' for help. Type '\c' to clear the buffer.

	mysql>

2、例2：连接到远程主机上的MYSQL。假设远程主机的IP为：110.110.110.110，用户名为root,密码为abcd123。则键入以下命令：
  mysql -h110.110.110.110 -uroot -pabcd123
  （注:u与root可以不用加空格，其它也一样）

3、退出MYSQL命令： exit （回车）
mysql> exit
Bye

M:\Documents and Settings\apple>

二、修改密码。
格式：mysqladmin -u用户名 -p旧密码  password 新密码
1、例1：给root加个密码ab12。首先在DOS下进入目录mysqlbin，然后键入以下命令
   mysqladmin -uroot -password ab12
  注：因为开始时root没有密码，所以-p旧密码一项就可以省略了。
2、例2：再将root的密码改为djg345。
   	mysqladmin -uroot -pab12 password djg345

	M:\Documents and Settings\apple>mysqladmin -uroot password ab12

	M:\Documents and Settings\apple>mysqladmin -uroot -pab12 password djg345

	M:\Documents and Settings\apple>mysql -uroot -p
	Enter password: ******
	Welcome to the MySQL monitor.  Commands end with ; or \g.
	Your MySQL connection id is 6 to server version: 5.0.22-community-nt

	Type 'help;' or '\h' for help. Type '\c' to clear the buffer.

	mysql>

三、增加新用户。（注意：和上面不同，下面的因为是MYSQL环境中的命令，所以后面都带一个分号作为命令结束符）
格式：grant select on 数据库.* to 用户名@登录主机 identified by "密码"
例1、增加一个用户test1密码为abc，让他可以在任何主机上登录，并对所有数据库有查询、插入、修改、删除的权限。首先用以root用户连入MYSQL，然后键入以下命令：
  grant select,insert,update,delete on *.* to test1@"%" Identified by "abc";
但例1增加的用户是十分危险的，你想如某个人知道test1的密码，那么他就可以在internet上的任何一台电脑上登录你的mysql数据库并对你的数据可以为所欲为了，解决办法见例2。
例2、增加一个用户test2密码为abc,让他只可以在localhost上登录，并可以对数据库mydb进行查询、插入、修改、删除的操作（localhost指本地主机，即MYSQL数据库所在的那台主机），这样用户即使用知道test2的密码，他也无法从internet上直接访问数据库，只能通过MYSQL主机上的web页来访问了。
  grant select,insert,update,delete on mydb.* to test2@localhost identified by "abc";
  如果你不想test2有密码，可以再打一个命令将密码消掉。
  grant select,insert,update,delete on mydb.* to test2@localhost identified by "";

创建一个LearnJSP数据库:
M:\Documents and Settings\apple>mysql -uroot -p
Enter password: ******
Welcome to the MySQL monitor.  Commands end with ; or \g.
Your MySQL connection id is 6 to server version: 5.0.22-community-nt

Type 'help;' or '\h' for help. Type '\c' to clear the buffer.

mysql> create database LearnJSP;
Query OK, 1 row affected (0.02 sec)

创建UserInfo表格:
mysql> use LearnJSP;
Database changed
mysql> create table UserInfo(
    -> UserName varchar (20) not null,
    -> UserPwd varchar (20) not null
    -> );
Query OK, 0 rows affected (0.06 sec)

mysql>
插入一条数据:
mysql> insert into UserInfo values ('zieckey','123456');
Query OK, 1 row affected (0.03 sec)

mysql>



设定 ClassPath

   在下载的JDBC驱动的压缩文件中有mysql-connector-java-3.1.12-bin.jarmysql-connector-java-3.1.12-bin-g.jar两个jar文件。把它们拷贝到JDK的lib目录下，并把其加入ClassPath中。例如，我的是这样的，原来的为.;%JAVA_HOME%\lib;%JAVA_HOME%\lib\tools.jar;然后加入两个jar的路径.;%JAVA_HOME%\lib;%JAVA_HOME%\lib\tools.jar;C:\j2sdk1.4.2\lib\mysql-connector-java-3.1.12-bin.jar;C:\j2sdk1.4.2\lib\mysql-connector-java-3.1.12-bin-g.jar

这样准备工作就做好了，下面是我的测试程序。其中在Eclipse中建立普通java Project时，我们可以在建立时添加外部JARS，选中在\lib下的驱动jar就可以了。如果Project是建立好的的话可以通过Java Build Path选项再在Libraries中添加外部JARs即可。下面是一个很简单的登录窗口测试程序





JSP使用MySQL数据库:从安装、配置到实际程序测试详解

                   By zieckey(http://zieckey.cublog.cn)
                          All Rights Reserved!

这里假设你的 JSP+Tomcat 开发环境和已经搭建好了
(详细配置见:http://blog.chinaunix.net/u/16292/showart_227534.html)

一、准备工作：

下载MySQL：mysql-5.0.27-win32.zip
下载MySQL的JDBC jar包：mysql-connector-java-5.0.3-bin.jar

二、安装和测试MySQL
 MySQL在Windows下的安装很简单，注意在选择配置的有一项是将MySQL的配置导入系统环境变量中，
为了后面的方便这个选项要选项。
 安装完后，下面测试下：
1. 运行MySQL Server
M:\Documents and Settings\apple>mysqld-nt --help
mysqld-nt  Ver 5.0.22-community-nt for Win32 on ia32 (MySQL Community Edition (G
PL))
Copyright (C) 2000 MySQL AB, by Monty and others
This software comes with ABSOLUTELY NO WARRANTY. This is free software,
and you are welcome to modify and redistribute it under the GPL license
Starts the MySQL database server
Usage: mysqld-nt [OPTIONS]
For more help options (several pages), use mysqld --verbose --help
 这里可以看到mysqld-nt.exe是MySQL database server
我们再运行客户端进行连接:
如果这里说系统没有这个mysqld-nt命令，那么很可能是MySQL的配置信息没有导入系统环境变量中。这个时候可以将MySQL的安装目录下bin目录导入到系统PATH环境变量中，例如：
M:\WINDOWS\system32;M:\WINDOWS;M:\WINDOWS\System32\Wbem;M:\Program Files\MySQL\MySQL Server 5.0\bin
再运行 mysqld-nt 应该就没有问题了。
M:\Documents and Settings\apple>mysqld-nt
2.连接MYSQL。
格式： mysql -h主机地址 -u用户名 －p用户密码
例1：连接到本机上的MYSQL。
   首先在打开DOS窗口，然后进入目录 mysqlbin，再键入命令mysql -uroot -p，回车后提示你输密码，如果刚安装好MYSQL，超级用户root是没有密码的，故直接回车即可进入到MYSQL中了，MYSQL的提示符是：mysql>
    M:\Documents and Settings\apple>mysql -uroot -p
 Enter password:
 Welcome to the MySQL monitor.  Commands end with ; or \g.
 Your MySQL connection id is 1 to server version: 5.0.22-community-nt
 Type 'help;' or '\h' for help. Type '\c' to clear the buffer.
 mysql>
例2：连接到远程主机上的MYSQL。假设远程主机的IP为：110.110.110.110，用户名为root,密码为abcd123。则键入以下命令：
  mysql -h110.110.110.110 -uroot -pabcd123
  （注:u与root可以不用加空格，其它也一样）
3、退出MYSQL命令： exit （回车）
mysql> exit
Bye
M:\Documents and Settings\apple>

三、在Java中使用MySQL数据库

1. 准数据库文件
创建一个LearnJava数据库:
M:\Documents and Settings\apple>mysql -uroot -p
Enter password: ******
Welcome to the MySQL monitor.  Commands end with ; or \g.
Your MySQL connection id is 6 to server version: 5.0.22-community-nt
Type 'help;' or '\h' for help. Type '\c' to clear the buffer.
mysql> create database LearnJava;
Query OK, 1 row affected (0.02 sec)
创建UserInfo表格:
mysql> use LearnJava;
Database changed
mysql> create table UserInfo(
    -> UserName varchar (20) not null,
    -> UserPwd varchar (20) not null
    -> );
Query OK, 0 rows affected (0.06 sec)
mysql>
插入一条数据:
mysql> insert into UserInfo values ('zieckey','123456');
Query OK, 1 row affected (0.03 sec)
mysql>

2. 将MySQL的JDBC jar包导入系统环境中
这里我是将mysql-connector-java-5.0.3-bin.jar放在java的安装目录下，
然后导入到CLASSPATH环境变量中，例如：
.;%JAVA_HOME%\lib\tools.jar;%JAVA_HOME%\lib\mysql-connector-java-5.0.3-bin.jar;%JAVA_HOME%\lib\dt.jar;

3. 新建 Java 程序 zieckey.jsp

<%@ page contentType="text/html;charset=gb2312"%>
<%@ page language="java"%>
<%@ page import="java.sql.*"%>

<html>
<body>
	<%
		Class.forName("org.gjt.mm.mysql.Driver").newInstance();
		//连接参数与Access不同
		String url = "jdbc:mysql://localhost/LearnJava";
		//建立连接
		Connection con = DriverManager.getConnection ( url, "root", "123456" );

		Statement stmt = con.createStatement ( );
		//返回查询结果
		ResultSet rs = stmt.executeQuery ( "select * from userinfo" );

		while(rs.next()) {%>
			数据库“userinfo”表中字段1: <%=rs.getString(1)%><br />
			数据库“userinfo”表中字段2: <%=rs.getString(2)%><br />
		<%}%>
	<%out.print("数据库操作成功，恭喜你");%><br />

	<%
		//关闭相关操作
		rs.close();
		stmt.close();
		con.close();
	%>
</body>
</html>

将其保存到 %TOMCAT%\webapps\ROOT\zieckey.jsp
然后再浏览器中输入 http://localhost:8080/zieckey.jsp 就可以到一个网页，
该网页上输出：

数据库“userinfo”表中字段1: zieckey
数据库“userinfo”表中字段2: 123456
数据库操作成功，恭喜你

总结:
这里我们知道了JSP+tomcat+mysql+JDBC实现了简单的网站数据库管理,
下面的工作将顺利多了.
祝你的JSP之旅一路顺风!


一个简单的登陆网页设计:

前台login.html和后台verifylogin.jsp两个页面组成:
login.html内容:

<html>
  <head>
    <title>登录</title>

    <meta http-equiv="content-type" content="text/html; charset=UTF-8">
    <meta http-equiv="Content-Language" content="ch-cn">
  </head>

  <body>
  <!-- Form 用来提取用户填入并提交的信息-->
  <form method="post" name="frmLogin" action="verifylogin.jsp">
  <h1 align="center">用户登录</h1><br>
  <div align="center">用户名：
  		<input type="text" name="txtUserName" value="Your name"
  			onfocus="if(this.value=='Your name')this.value='';"><br>密码：
  		<input type="password" name="txtPassword" value="Your password"
  			onfocus="if(this.value=='Your password')this.value='';"><br>
  		<input type="submit" name="Submit"　value="提交"> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
  		<input type="reset" name="Reset" value="重置"><br>
  </div></form></body>
</html>

verifylogin.jsp内容:
<%@ page language="java" contentType="text/html;charset=gb2312"
	pageEncoding="UTF-8"%>

<%@ page import="java.sql.*"%>
<%@ page import="java.util.*"%>


<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
	<head>
		<title>登录</title>

		<meta http-equiv="pragma" content="no-cache">
		<meta http-equiv="cache-control" content="no-cache">
		<meta http-equiv="expires" content="0">
		<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
		<meta http-equiv="description" content="This is my page">
		<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->

	</head>

	<body>
		<div align=center>
		<%
			//获取用户名
			String sUserName = request.getParameter ( "txtUserName" );
			//获取密码
			String sPasswd = request.getParameter ( "txtPassword" );

			//登记JDBC驱动程序
			Class.forName ( "org.gjt.mm.mysql.Driver" ).newInstance ( );
			//连接参数与Access不同
			String url = "jdbc:mysql://localhost/LearnJSP";
			//建立连接
			Connection connection = DriverManager.getConnection ( url, "root",
					"011124" );
			//SQL语句
			String sql = "select * from userinfo where username='" + sUserName
					+ "' and userpwd = '" + sPasswd + "'";

			Statement stmt = connection.createStatement ( );
			ResultSet rs = stmt.executeQuery ( sql ); //返回查询结果

			//如果记录集非空，表明有匹配的用户名和密码，登陆成功
			if ( rs.next ( ) )
			{
				out.println ( "登录成功！" );
			} else
			//否则登录失败
			{
				out.println ( "用户名不存在或密码错误！" );
			}

			rs.close ( );
			stmt.close ( );
			connection.close ( );
		%>
	</body>
</html>

下面为客户端添加代码验证功能:
<html>
  <head>
    <title>登录</title>

    <meta http-equiv="content-type" content="text/html; charset=UTF-8">
    <meta http-equiv="Content-Language" content="ch-cn">

  </head>
  <body>
	<!-- Form 用来提取用户填入并提交的信息-->
	<form method="post" name="frmLogin" action="verifylogin.jsp">
		 <h1 align="center">用户登录</h1><br>
		 <div align="center">用户名：
		  		<input type="text" name="txtUserName" value="Your name"
		  			onfocus="if(this.value=='Your name')this.value='';"><br>密码：
		  		<input type="password" name="txtPassword" value="Your password"
		  			onfocus="if(this.value=='Your password')this.value='';"><br>
		  		<input type="submit" name="Submit"　value="提交" onClick="validateLogin();" >
		  			&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
		  		<input type="reset" name="Reset" value="重置"><br>
		 </div>
	</form>
	<!-- javaScript 函数 validateLogin(),用来验证用户名和密码是否为空 -->
    <script language="javaScript">
    	function validateLogin()
    	{
    		var sUserName = document.frmLogin.txtUserName.value;
    		var sPassword = document.frmLogin.txtPassword.value;
    		if( sUserName=="" )
    		{
    			alert("请输入用户名！");
    			return false;
    		}
    		if( sPassword=="" )
    		{
    			alert("请输入密码！");
    			return false;
    		}
    	}
    </script>
  </body>
</html>


为服务器端添加代码验证功能:
<%@ page language="java" contentType="text/html;charset=gb2312"
	pageEncoding="UTF-8"%>

<%@ page import="java.sql.*"%>
<%@ page import="java.util.*"%>


<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
	<head>
		<title>登录</title>

		<meta http-equiv="pragma" content="no-cache">
		<meta http-equiv="cache-control" content="no-cache">
		<meta http-equiv="expires" content="0">
		<meta http-equiv="keywords" content="zieckey,jsp">
		<meta http-equiv="description" content="Test JSP using MySQL">

	</head>
	<body>
		<div align=center>
			<%
				//获取用户名
				String sUserName = request.getParameter ( "txtUserName" );
				if ( sUserName == "" || sUserName == null || sUserName.length()>20 )
				{
					try
					{
						response.sendRedirect ( "login.html" );
					} catch ( Exception e )
					{
					}
				}

				//获取密码
				String sPasswd = request.getParameter ( "txtPassword" );
				if ( sPasswd == "" || sPasswd == null || sPasswd.length()>20 )
				{
					try
					{
						response.sendRedirect ( "login.html" );
					} catch ( Exception e )
					{
					}
				}

				//登记JDBC驱动程序
				Class.forName ( "org.gjt.mm.mysql.Driver" ).newInstance ( );
				//连接参数与Access不同
				String url = "jdbc:mysql://localhost/LearnJSP";
				//建立连接
				Connection connection = DriverManager.getConnection ( url, "root",
						"011124" );
				//SQL语句
				String sql = "select * from userinfo where username='" + sUserName
						+ "' and userpwd = '" + sPasswd + "'";

				Statement stmt = connection.createStatement ( );
				ResultSet rs = stmt.executeQuery ( sql ); //返回查询结果

				//如果记录集非空，表明有匹配的用户名和密码，登陆成功
				if ( rs.next ( ) )
				{
					//登录成功后将sUserName设置为session变量的UserName
					//这样在后面就可以通过 session.getAttribute("UserName") 来获取用户名，
					//同时这样还可以作为用户登录与否的判断依据
					session.setAttribute ( "UserName", sUserName );
					out.print (  "登录成功！" );
					out.print ( session.getAttribute ( "UserName" ) + " 欢迎您！" );
				} else
				//否则登录失败
				{
					out.println ( "用户名不存在或密码错误！" );
				}

				rs.close ( );
				stmt.close ( );
				connection.close ( );
			%>

	</body>
</html>


数据库中所有表的字段长度的设计标准是应该是足够用,但不浪费存储空间.
我们可以发现,上面数据库中字段限制在20个字符以内,那么程序中也应该作一个限制,
否则可能给网站出现严重的问题.
将上面源码修改如下:
				.....
				<input type="text" name="txtUserName" value="Your name"
		  			size="20" maxlength="20"
		  			onfocus="if(this.value=='Your name')this.value='';"><br>密码：
		  		<input type="password" name="txtPassword" value="Your password"
		  			size="20" maxlength="20"
		  			onfocus="if(this.value=='Your password')this.value='';"><br>
				.....

				.....
				if ( sUserName == "" || sUserName == null || sUserName.length()>20 )
				....
				if ( sPasswd == "" || sPasswd == null || sPasswd.length()>20 )
				......

这样问题就彻底解决了.






将上面的JSP+JavaBean模式开发的登录界面改用JSP+Servlet+JavaBean模式重新实现

这次涉及到四个文件:
登录页面:login.html
登录成功欢迎页面:login_success.jsp
登录失败页面:login_failure.jsp
Servlet处理文件:LoginServlet.java

其实还涉及到一个文件:web.xml,这个后面再说:

下面分别介绍这几个文件:
登录页面:login.html
<!-- 该Login页面是一个简单的登录界面 -->
<!--
	该JSP程序是用来测试与MySQL数据库的连接，
	需要一个数据库：LearnJSP，和其中一个表：userinfo
	表中有两个字段分别为：UserName varchar (20) not null,UserPwd varchar (20) not null
-->
<html>
  <head>
    <title>登录</title>
    <meta http-equiv="content-type" content="text/html; charset=UTF-8">
    <meta http-equiv="Content-Language" content="ch-cn">
  </head>
  <body>
	<!-- Form 用来提取用户填入并提交的信息-->
	<form method="post" name="frmLogin" action="LoginServlet">
		 <h1 align="center">用户登录</h1><br>
		 <div align="center">用户名：
		  		<input type="text" name="txtUserName" value="Your name"
		  			size="20" maxlength="20"
		  			onfocus="if(this.value=='Your name')this.value='';"><br>密码：
		  		<input type="password" name="txtPassword" value="Your password"
		  			size="20" maxlength="20"
		  			onfocus="if(this.value=='Your password')this.value='';"><br>
		  		<input type="submit" name="Submit"　value="提交" onClick="validateLogin();" >
		  			&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
		  		<input type="reset" name="Reset" value="重置"><br>
		 </div>
	</form>

	<!-- javaScript 函数 validateLogin(),用来验证用户名和密码是否为空 -->
    <script language="javaScript">
    	function validateLogin()
    	{
    		var sUserName = document.frmLogin.txtUserName.value;
    		var sPassword = document.frmLogin.txtPassword.value;
    		if( sUserName=="" )
    		{
    			alert("请输入用户名！");
    			return false;
    		}
    		if( sPassword=="" )
    		{
    			alert("请输入密码！");
    			return false;
    		}
    	}
    </script>

  </body>
</html>

登录成功欢迎页面:login_success.jsp
<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
	<head>
		<title>My JSP 'login_failure.jsp' starting page</title>
		<meta http-equiv="content-type" content="text/html; charset=UTF-8">
		<meta http-equiv="pragma" content="no-cache">
		<meta http-equiv="cache-control" content="no-cache">
		<meta http-equiv="expires" content="0">
		<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
		<meta http-equiv="description" content="This is my page">
		<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->

	</head>

	<body>
		<%
			String userName = (String)session.getAttribute ( "UserName" );
		%>
		<div align=center>
			<%=userName%>
			欢迎您，登录成功！
		</div>
	</body>
</html>



登录失败页面:login_failure.jsp
<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
	<head>
		<title>My JSP 'login_failure.jsp' starting page</title>
		<meta http-equiv="content-type" content="text/html; charset=UTF-8">
		<meta http-equiv="pragma" content="no-cache">
		<meta http-equiv="cache-control" content="no-cache">
		<meta http-equiv="expires" content="0">
		<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
		<meta http-equiv="description" content="This is my page">
		<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->

	</head>

	<body>
		<%
		String userName = (String)session.getAttribute ( "UserName" );
		%>
		<div align=center>
			<%=userName%>
			对不起，登录失败！
		</div>
	</body>
</html>


Servlet处理文件:LoginServlet.java
/**
 * 该JSP程序是用来测试与MySQL数据库的连接，
 * 需要一个数据库：LearnJSP，和其中一个表：userinfo
 * 表中有两个字段分别为：UserName varchar (20) not null,UserPwd varchar (20) not null
 */
package zieckey.login.servlet;

import java.sql.Statement;
import java.io.IOException;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;

import javax.servlet.Servlet;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class LoginServlet extends HttpServlet implements Servlet
{

	public LoginServlet ()
	{
		// TODO Auto-generated constructor stub
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see javax.servlet.http.HttpServlet#doGet(javax.servlet.http.HttpServletRequest,
	 *      javax.servlet.http.HttpServletResponse)
	 */
	@Override
	protected void doGet ( HttpServletRequest arg0, HttpServletResponse arg1 )
			throws ServletException, IOException
	{
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see javax.servlet.http.HttpServlet#doPost(javax.servlet.http.HttpServletRequest,
	 *      javax.servlet.http.HttpServletResponse)
	 */
	@Override
	protected void doPost ( HttpServletRequest request, HttpServletResponse response )
			throws ServletException, IOException
	{
		response.setContentType ( "text/html" );

		String result = "";

		// 获取用户名
		String sUserName = request.getParameter ( "txtUserName" );
		if ( sUserName == "" || sUserName == null || sUserName.length ( ) > 20 )
		{
			try
			{
				result = "请输入用户名（不超过20字符）！";
				request.setAttribute ( "ErrorUserName", result );
				response.sendRedirect ( "login.html" );
			} catch ( Exception e )
			{
			}
		}

		// 获取密码
		String sPasswd = request.getParameter ( "txtPassword" );
		if ( sPasswd == "" || sPasswd == null || sPasswd.length ( ) > 20 )
		{
			try
			{
				result = "请输入密码（不超过20字符）！";
				request.setAttribute ( "ErrorPassword", result );
				response.sendRedirect ( "login.html" );
			} catch ( Exception e )
			{
			}
		}

		// 登记JDBC驱动程序
		try
		{
			Class.forName ( "org.gjt.mm.mysql.Driver" ).newInstance ( );
		} catch ( InstantiationException e )
		{
			// TODO Auto-generated catch block
			e.printStackTrace ( );
			System.out.println ("InstantiationException");
		} catch ( IllegalAccessException e )
		{
			// TODO Auto-generated catch block
			e.printStackTrace ( );
			System.out.println ("IllegalAccessException");
		} catch ( ClassNotFoundException e )
		{
			// TODO Auto-generated catch block
			e.printStackTrace ( );
			System.out.println ("ClassNotFoundException");
		}

		// 连接参数与Access不同
		String url = "jdbc:mysql://localhost/LearnJSP";
		// 建立连接
		java.sql.Connection connection = null;

		Statement stmt = null;
		ResultSet rs = null;
		try
		{
			connection = DriverManager.getConnection ( url, "root", "011124" );
			stmt = connection.createStatement ( );

			// SQL语句
			String sql = "select * from userinfo where username='" + sUserName
					+ "' and userpwd = '" + sPasswd + "'";
			rs = stmt.executeQuery ( sql );// 返回查询结果
		} catch ( SQLException e )
		{
			// TODO Auto-generated catch block
			e.printStackTrace ( );
		}

		try
		{
			if ( rs.next ( ) )// 如果记录集非空，表明有匹配的用户名和密码，登陆成功
			{
				// 登录成功后将sUserName设置为session变量的UserName
				// 这样在后面就可以通过 session.getAttribute("UserName") 来获取用户名，
				// 同时这样还可以作为用户登录与否的判断依据
				request.getSession ( ).setAttribute ( "UserName", sUserName );
				response.sendRedirect ( "login_success.jsp" );
			} else
			{
				// 否则登录失败
				//response.sendRedirect ( "MyJsp.jsp" );
				response.sendRedirect ( "login_failure.jsp" );

			}
		} catch ( SQLException e )
		{
			// TODO Auto-generated catch block
			e.printStackTrace ( );
		}

		try
		{
			if ( null!=rs )
			{
				rs.close ( );
			}
			if ( null!=stmt )
			{
				stmt.close ( );
			}
			if ( null!=connection )
			{
				connection.close ( );
			}
		} catch ( SQLException e )
		{
			// TODO Auto-generated catch block
			e.printStackTrace ( );
		}

	}

	/**
	 *
	 */
	private static final long	serialVersionUID	= 1L;
}



为了让这个网站正常运行还要到web.xml中注册一下,
现该文件内容修改如下:
<?xml version="1.0" encoding="UTF-8"?>
<web-app xmlns="http://java.sun.com/xml/ns/j2ee" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" version="2.4" xsi:schemaLocation="http://java.sun.com/xml/ns/j2ee   http://java.sun.com/xml/ns/j2ee/web-app_2_4.xsd">
  <servlet>
   	<display-name>LoginServlet</display-name>
    <servlet-name>LoginServlet</servlet-name>
    <servlet-class>zieckey.login.servlet.LoginServlet</servlet-class>
  </servlet>
  <servlet-mapping>
    <servlet-name>LoginServlet</servlet-name>
    <url-pattern>/LoginServlet</url-pattern>
  </servlet-mapping>
</web-app>

好了,这几个文件就可以构成我们的这个登录界面了.
注意事项:
1. 文件目录形式
login.html,login_success.html,login_failure.html这三个文件放在同一目录,
LoginServlet.java该文件的字节码文件LoginServlet.class放在WEB-INF\classes目录下(注意jar包顺序)

现在整个工程的目录形式是:
M:\Tomcat5.5\webapps\JSP_Servlet_JavaBean_Login 的目录
007-01-18  15:16    <DIR>          META-INF
007-01-18  15:16    <DIR>          WEB-INF
007-01-18  16:17             1,801 login.html
007-01-18  15:48               858 login_failure.jsp
007-01-18  15:40               234 login_success.html
007-01-18  15:46               781 MyJsp.jsp
007-01-18  16:12               859 login_success.jsp

M:\Tomcat5.5\webapps\JSP_Servlet_JavaBean_Login\WEB-INF 的目录
007-01-18  15:16    <DIR>          classes
007-01-18  15:16    <DIR>          lib
007-01-18  16:21               606 web.xml

M:\Tomcat5.5\webapps\JSP_Servlet_JavaBean_Login\WEB-INF\classes\zieckey\login\servlet 的目录
2007-01-18  16:18             3,900 LoginServlet.class

2. 其他注意事项
数据库MySQL服务器程序要先启动起来.














 <br>或<br />的意思是换行
    我们一般建议您使用标准的格式<br /> (中间有空格)

　　在编写HTML文件时，我们不必考虑太细的设置，也不必理会段落过长的部分会被浏览器切掉。因为，在HTML语言规范里，每当浏览器窗口被缩小时，浏览器会自动将右边的文字转折至下一行。所以，编写者对于自己需要断行的地方，应加上<br />标签。

<html>
<head>
<title>无换行示例</title>
</head>
<body>
登鹳雀楼　白日依山尽，黄河入海流。欲穷千里目，更上一层楼。
</body>
</html>
<html>
<head>
<title>换行示例</title>
</head>
<body>
登鹳雀楼<br />白日依山尽，<br />黄河入海流。<br />欲穷千里目，<br />更上一层楼。
</body>
</html>

 META标签，是HTML语言head区的一个辅助性标签。在几乎所有的page里，我们都可以看
  到类似下面这段html代码：

  -----------------------------------------------
  <head>
  <meta   http-equiv="Content-Type"   content="text/html;   charset=gb2312">
  </head>
  -----------------------------------------------

  这就是meta标签的典型运用。meta标签有多少参数，有什么作用，为什么我们要特别重
  视它呢？让我们一起来发掘meta标签的奥妙!

  根据HTML语言标准注释：meta标签是对网站发展非常重要的标签，它可以用于鉴别作者，
  设定页面格式，标注内容提要和关键字，以及刷新页面等等。

  meta标签分两大部分：HTTP-EQUIV和NAME变量。

  ●HTTP-EQUIV类似于HTTP的头部协议，它回应给浏览器一些有用的信息，以帮助正确和精确
  地显示网页内容。常用的HTTP-EQUIV类型有：

  1.expires(期限)
  说明：可以用于设定网页的到期时间。一旦网页过期，必须到服务器上重新调阅。
  用法：<META   HTTP-EQUIV="expires"   CONTENT="Wed,   26   Feb   1997   08:21:57   GMT">
  注意：必须使用GMT的时间格式。

  2.Pragma(cach模式)
  说明：禁止浏览器从本地机的缓存中调阅页面内容。
  用法：<META   HTTP-EQUIV="Pragma"   CONTENT="no-cache">
  注意：这样设定，访问者将无法脱机浏览。

  3.Refresh(刷新)
  说明：需要定时让网页自动链接到其它网页的话，就用这句了。
  用法：<META   HTTP-EQUIV="Refresh"   CONTENT="5;URL=http://www.yahoo.com">
  注意：其中的5是指停留5秒钟后自动刷新到URL网址。

  4.Set-Cookie(cookie设定)
  说明：如果网页过期，那么存盘的cookie将被删除。
  用法：<META   HTTP-EQUIV="Set-Cookie"   CONTENT="cookievalue=xxx;
  expires=Wednesday,   21-Oct-98   16:14:21   GMT;   path=/">
  注意：必须使用GMT的时间格式。

  5.Window-target(显示窗口的设定)
  说明：强制页面在当前窗口以独立页面显示。
  用法：<META   HTTP-EQUIV="Window-target"   CONTENT="_top">
  注意：用来防止别人在框架里调用你的页面。

  5.Content-Type(显示字符集的设定)
  说明：设定页面使用的字符集。(我们在前面字体设计中已经介绍过它的作用)
  用法：<meta   http-equiv="Content-Type"   content="text/html;   charset=gb2312">


  ●meat标签的NAME变量语法格式是：
  <META   NAME="xxx"   CONTENT="xxxxxxxxxxxxxxxxxx">
  其中xxx主要有下面几种参数：

  1.Keywords(关键字)
  说明：keywords用来告诉搜索引擎你网页的关键字是什么。
  举例：<META   NAME   ="keywords"   CONTENT="life,   universe,   mankind,   plants,
  relationships,   the   meaning   of   life,   science">

  2.description(简介)
  说明：description用来告诉搜索引擎你的网站主要内容。
  举例：<META   NAME="description"   CONTENT="This   page   is   about   the   meaning   of
  life,   the   universe,   mankind   and   plants.">

  3.robots(机器人向导)
  说明：robots用来告诉搜索机器人哪些页面需要索引，哪些页面不需要索引。
  CONTENT的参数有all,none,index,noindex,follow,nofollow。默认是all。
  举例：<META   NAME="robots"   CONTENT="none">

  4.author(作者)
  说明：标注网页的作者
  举例：<META   name="AUTHOR"   content="ajie,ajie@netease.com">

  以上是meta标签的一些基本用法，其中最重要的就是:Keywords和description的设定。

  为什么呢？道理很简单，这两个语句可以让搜索引擎能准确的发现你，吸引更多的人访问
  你的站点!

  根据现在流行搜索引擎(Lycos，AltaVista等)的工作原理,搜索引擎首先派出机器人自动
  在www上搜索，当发现新的网站时，便检索页面中的keywords和decription，并将其加入到自
  己的数据库，然后再根据关键词的密度将网站排序。

  也就是说：
  1.   如果你的页面中根本没有Keywords和description的meta标签，那么机器人是
  无法将你的站点加入数据库，网友也就不可能搜索到你的站点。

  2.   如果你的关键字选的不好，关键字的密度不高，被排列在几十甚至几百万个站点的后面
  被点击的可能性也是非常小的。

  所以,我们必须记住添加keywords和description的meta标签，并尽可能写好关键字和简介。

  写keywords的禁忌是：
  1.不要用常见词汇。例如www,homepage,net,web等。
  2.不要用形容词，副词。例如最好的，最大的等。
  3.不要用笼统的词汇，要尽量精确。例如不用"摩托罗拉手机",改用"V998"等

  寻找合适的关键词的一个技巧是：到lycos,Alta,infoseek等搜索引擎，搜索与你内容相仿
  的网站，查看排名前十位的网站的meta关键字，copy下来用到自己的站点上。

  这里，我们举一段微软多媒体网站的关键字供你参考：
  <meta   name="keywords"   content="joke,   music,   MP3,   media,   audio,
  joke   of   the   day,   downloads,   free   music,   horoscope,   radio,   video,
  music   downloads,   movies,   radio   station,   media   player,   free,
  download,   weather,   horoscopes,   windows   media   technologies,
  online,   radio   station   guide,   free   download">

  小资源:人们最常用的一些搜索词(即关键词)可以到
  http://www.searchterms.com/
  http://eyescream.com/yahootop200.html
  两个网址一看，那里有每个月网上最流行搜索词的排行榜.

  另外为了提高搜索点击率，这里还有一些"邪门歪道"：
  1.为了增加关键词的密度，将关键字隐藏在页面里(将文字颜色定义成与背景颜色一样)。
  2.在图象的alt注释语句中加入关键字。
  如：<IMG   SRC="xxx.gif"   Alt="keywords">
  3.利用HTML的注释语句，在页面代码里加入大量关键字。
  用法：   <!---   这里插入关键字   --->




赋值操作：<%= userName %>
这里的 <%= userName %> 必须写为<%= userName %>，
而不能将 % 和 = 分开写了，例如不能写为这样：<% = userName %>

	<%
		String userName = (String)session.getAttribute("UserName");
    %>
这里也是要注意的一定要加上强制转换(String)，不然也会运行出错。



注册页面设计
准备数据库:
create table user_register_info(
	UserName varchar(20) not null default '',
	Password varchar(20) not null default '',
	RealName varchar(50) not null default '',
	Gender	 varchar(1) not null default '0',
	TelNumber varchar(20) not null default '',
	EmailAdd varchar(50) not null default '',
	HomePage varchar(50) not null default '',
	PRIMARY KEY (UserName)
);
readonly
任何一个Servlet都要到web.xml中登记，否则就会找不到，登记项目如下：
	  <servlet>
	  	<servlet-name>RegisterServlet</servlet-name>
	  	<servlet-class>zieckey.register.servlet.RegisterServlet</servlet-class>
	  </servlet>
	  <servlet-mapping>
	    <servlet-name>RegisterServlet</servlet-name>
	    <url-pattern>/RegisterServlet</url-pattern>
	  </servlet-mapping>


在Java Servlet中使用Java的
request.getRequestDispatcher ("/messageboard/browsemessageboard.jsp").
													forward (request,response);
语句转发页面时，工程目录名就不要加上，
但是在JSP页面中使用时,就要带上目录路径,例如:
href="/BohaoWeb/messageboard/index.jsp"

2007-01-28 15:04:26



网页按钮大本营
---- 一、按钮的基本使用

---- 一般的可视性网页制作工具中，都有方便的按钮填加工具，可直接在网页的合适位置填加按钮，如果你使用手工的网页制作方法，那么可用下面的源代码制作按钮，其中onclick决定按下按钮的动作：

< form method="POST" >
< p >< input type="button" name="B1" value=
"按钮" >< /p >
onclick > < /p >
< /form >

---- 如果只使用单独的按钮，那么可省略form标签，只使用单纯的按钮代码，将节省按钮所占的网页空间：
< p >< input type="button" name="B1" value=
"按钮" >< /p >
onclick > < /p >

---- 二、按钮的前景与背景控制
---- 绝大多数的人使用按钮时，都直接使用缺省的灰白色按钮有黑色的文字说明，其实按钮的背景和前景是可以随意改变的，请看下面的代码：

< form name="highlight" >
< p align="center" >< input type=
"button" value="变色按钮"
style="background-color: rgb(255,0,0);
color: rgb(255,2550,0)"
onclick > < /p >
< /form >

---- 其中background-color控制背景色，color按钮前景色；
---- 三、按钮的图片背景

---- 按钮不仅可以修改前景色和背景颜色，而且可以使用图片背景，下面的代码分别演示了固定的背景图片效果和动态的图片背景效果，动态的效果即在鼠标放到按钮上时，按钮的背景是另外一种图像背景，而鼠标离开时则恢复原来的图片背景，下面代码中的mainbb1.jpg和mainbb2.jpg 分别为两个图像文件：


< script >
< !--
if (document.images){
after=new Image()
after.src="mainbb1.jpg"}
function change2(image){
var el=event.srcElement
if (el.tagName=="INPUT"&&el.type=="button")
event.srcElement.style.backgroundImage=
"url"+"(''"+image+"'')"}
//-- >
< /script >

< form onmouseover="change2(''mainbb1.jpg'')"
onmouseout="change2(''mainbb2.jpg'')" >
< p align="center" >< input type="
button" name="frme2"
value="变化背景"
style="background-color: rgb(192,192,192);
FONT-FAMILY: 宋体;
FONT-SIZE: 12pt;background-image: url(''mainbb2.jpg'')"
class="initial" onclick="(h1.htm'')"
< br > < input type="submit"
name="B1" value="固定背景"
style="FONT-SIZE: 12pt; background-image:
url(''mainbb1.jpg'')" >< /p >
< /form >

---- 四、按钮字号和字型控制
---- 按钮上显示的文字也可以随意改变风格，可以设置字体的字型和字号，请看以下代码：

< form name="highlight" >
< p align="center" >
< input type="button" value="变化字号"
style="background-color: rgb(192,192,192);
FONT-FAMILY: 宋体; FONT-SIZE: 9pt"
color: rgb(255,2550,0)"); onclick >
< input type="button" value="变化字号"
style="background-color: rgb(192,192,192);
FONT-FAMILY: 宋体; FONT-SIZE: 12pt"
color: rgb(255,2550,0)"); onclick >
< /p >
< /form >

---- 五、按钮鼠标移动变色
---- 上面已经介绍了按钮的颜色控制方法，加上鼠标事件的参与即可实现鼠标移动变色，下面是完整的代码：

< html >
< head >
< meta http-equiv="Content-Type"
content="text/html; charset=gb_2312-80" >
< meta name="GENERATOR" content=
"Microsoft FrontPage Express 2.0" >
< title >变色按钮< /title >
< style >
.bigChange {color:blue; font-weight:bolder;
font-size:175%;letter-spacing:4px;
text-transform: uppercase; background:yellow}
.start
.over
< /style >
< /head >
< body bgcolor="#83E09C" >
< p >
< script language="JAVASCRIPT" >
function highlightButton(s) {
if ("INPUT"==event.srcElement.tagName)
event.srcElement.className=s }
< /script > < /p >
< form name="highlight" onmouseover=
"highlightButton(''start'')"
onmouseout="highlightButton(''over'')" >
< p align="center" >< input type=
"button" value="变色按钮"); onclick > < /p >
< /form >
< /body >
< /html >
---- 六、鼠标移动按钮变字号
---- 利用同样的方法，也可以使按钮在鼠标移动时变换字号，其实字号的变化也引起了按钮尺寸的变化，这一效果能够引起游览者的注意力，当然也可以合起来使字号和颜色同时发生变化：

< html >
< head >
< meta http-equiv="Content-Type"
content="text/html; charset=gb_2312-80" >
< title >变号按钮< /title >
< style >
.bigChange {color:blue; letter-spacing:4px;
text-transform: uppercase; background:yellow}
.start
.over
< /style >
< /head >
< body bgcolor="#83E09C" >
< script language="JAVASCRIPT" >
function highlightButton(s) {
if ("INPUT"==event.srcElement.tagName)
event.srcElement.className=s }
< /script >
< form name="highlight" onmouseover=
"highlightButton('start')"
onmouseout="highlightButton('over')" >
< p align="center" >< input type=
"button" value="变号按钮"); onclick > < /p >
< /form >
< /body >
< /html >

---- 七、按钮上显示时钟
---- 按钮上显示的信息不仅可以事先定义成固定的字符串，而且可以随时更改，当然你也可以把一些动态的信息送到按钮上，下面是在按钮上显示走动的时钟的例子，效果非常好：

< script LANGUAGE="JavaScript" >
day = new Date();
miVisit = day.getTime();
function clock() {
dayTwo = new Date();
hrNow = dayTwo.getHours();
mnNow = dayTwo.getMinutes();
scNow = dayTwo.getSeconds();
miNow = dayTwo.getTime();
if (hrNow == 0) {hour = 12;ap = " AM";
} else if(hrNow < = 11) {ap = "
AM";hour = hrNow;
} else if(hrNow == 12) {ap = " PM";hour = 12;
} else if (hrNow >= 13) {hour =
(hrNow - 12);ap = " PM";}
if (hrNow >= 13)
if (mnNow < = 9)
else (min = mnNow)
if (scNow < = 9) {
secs = "0" + scNow;} else
time = hour + ":" + min + ":" + secs + ap;
document.form.button.value = time;
self.status = time;
setTimeout('clock()', 1000);}
document.write("< form name=\"form\" >"
+ "< input type=button value=\"Click for info!\""
+ " name=button >< /form >");
onError = null;
clock();
< /script >

---- 八、按钮控制显示源文件
---- 为了方便别人学习你的网页设计方法，在主页上放置一个按钮，按下该按钮后即自动显示源文件，是不是非常实用？代码如下，放到主页的正文区：

< form method="POST" >
< p align="center" >< input type=
"button" name="B1"
value="显示源文件"
onclick="window.location="
view-source:" +window.location.href" >
< /p >
< /form >

---- 九、按钮链接站点
---- 这是按钮的一种最简单使用方法，按下按钮后转到一个站点：

< form >
< p >< input type="button"
value="进入酷站 > > >"
onclick="parent.location='http:
//jyt.yeah.net'" >< /p >
< /form >
---- 十、按钮改变页面背景
---- 通过按钮可以实时修改页面的颜色，如果让其自动在两种颜色之间快速切换背景颜色，就形成了闪烁效果，下面的代码设置了两个按钮，分别演示修改背景和闪烁效果，代码放到主页的正文区：

< form >
< p >< input type="button" value="背景色变换"
onclick="BgButton()" >< /p >
< /form >
< script >function BgButton(){
if (document.bgColor=='#00ffff')

else }
< /script >

< FORM >< INPUT TYPE="BUTTON" VALUE="闪烁"
onClick="blinkit(self)" >< /FORM >
< SCRIPT LANGUAGE="JavaScript" >
function blinkOn(){
theWin.document.bgColor = "0000ff"
nTimes++
JSCTimeOutID = window.setTimeout
("blinkOff()",50);}
function blinkOff(){
theWin.document.bgColor = "FFFFFF"
if (nTimes < 3)
JSCTimeOutID = window.setTimeout("blinkOn()",50);
else theWin.history.go(0)}
function blinkit(aWin){
nTimes = 0
theWin = aWin
JSCTimeOutID = window.setTimeout("blinkOn()",50);}
< /SCRIPT >

---- 十一、按钮刷新页面
---- 尽管浏览器上都有刷新按钮，但在主页中设置上则显得页面更为完善，尤其是那些经常需要刷新的场合，实现刷新有两种方法，代码分别如下，请放到主页的正文区：

代码一：
< form >
< p >< input type="button" value="刷新按钮"
onclick="history.go(0)" > < /p >
< /form >
代码二：
< form >
< p >< input type="button" value="刷新按钮一"
onclick="ReloadButton()" >< /p >
< /form >
< script language="JavaScript" >< !--
function ReloadButton()
// -- >< /script >

---- 十二、滚屏按钮
---- 按下按钮后，屏幕内容开始向上滚动，代码如下，但一页长度必须超出一屏，否则将看不到滚动效果：

< form >
< div align="center" >
< center >< p >< input type="button" value=
"向下滚屏" onClick="scrollit()" > < /p >
< /center >< /div >
< /form >

< script Language="JavaScript" >
< !--
function scrollit(){
for (I=1; I< =500; I++){
parent.scroll(1,I) }}
//-- >
< /script >

---- 十三、加入书签按钮
---- 利用文字链接也可以实现加入书签功能，但使用按钮则更为醒目和直观，按下按钮后，则可把指定的站点加到游览器的书签中，代码如下：

< form >
< p >< input type="button"
value="把本站加入书签"
onclick="window.external.addFavorite
('http://jyt.yeah.net/','肥肥之家')" >< /p >
< /form >

---- 十四、按钮字幕
---- 移动的字幕并不少见，比如在FRONTPAGE 中有现成的字幕生成器，而利用JAVA实现的走马灯效果更是花样百出，其实使用按钮制作字幕效果更为独特，按钮会随着字符的数量而发生尺寸变化，动态很强，以下为完成的代码，请放到网页的正文区：

< form name=form2 >
< p >< input type="submit" name="banner" VALUE="Submit"
onClick="alert('你可以加上链接！')" > < br >
< script language="JavaScript" >
var id,pause=0,position=0;
function banner() {
var i,k,msg="欢迎访问HXUN的网站";// increase msg
k=(30/msg.length)+1;
for(i=0;i< =k;i++) msg+=" "+msg;
document.form2.banner.value=msg.substring(position,position-30);
if(position++==msg.length) position=0;
id=setTimeout("banner()",60); }
banner();
< /script >< /p >
< /form >




今天遇到JSP困难了，问题如下：

这是在一个Servlet中的语句
{
	....
	request.getSession (true).setAttribute ( "BohaoStudentMenber", bs );// 语句1* bs是一个类
	response.sendRedirect ( "bohaoadmin.jsp" );// 语句2*
	....
}
在跟踪调试中，执行文“语句1*”后，可以看到:
bs有值：#3919
request的值：request.Inherited.request.request.session.attribute下有值 "BohaoStudentMenber"=>#3919
这说明这一步已经成功，

在bohaoadmin.jsp文件中用如下语句提取属性的时候：
BohaoStudentMenber bs = (BohaoStudentMenber)session.getAttribute ("BohaoStudentMenber");
就不能提取到“BohaoStudentMenber”的属性值，只能是空值，
可以跟踪发现这个时候的session属性中没有“BohaoStudentMenber”这一条，
这是为什么呢？

但是后来，不知道怎么的又可以提取到“BohaoStudentMenber”这个属性值，
奇怪！奇怪！


今天在写 Java 数据库程序的时候，碰到一个问题，说出来，更大家分享下。
是这样的，请先开下面程序片断：

	//程序片断1
	void func()
	{
		.......
		ResultSet rs = stmt.executeQuery (sql);
		if ( rs.next () )//表明找到记录
		{
			......
			try
		    {
		        bs.setId (rs.getInt ("id"));
		    } catch (SQLException ex)
		    {
		        ex.printStackTrace();
		    }
		    try
		    {
		        bs.setStrAddress (rs.getString ("address"));
		    } catch (SQLException ex1)
		    {
		        ex1.printStackTrace();
		    }
		    .....
		}
		..........
	}

因为 “//程序片断1”中的if语句太长，我将其抽取为一个独立的函数，如下：

	//程序片断2
	void func()
	{
		.......
		ResultSet rs = stmt.executeQuery (sql);
		setBohaoStudentField(bs,rs);
		..........
	}

	//程序片断3
	private void setBohaoStudentField (final BohaoStudentMenber bs, final ResultSet rs) throws 		SQLException
    {
    	if ( rs.next () )//表明找到记录
    	{
            ......
			try
		    {
		        bs.setId (rs.getInt ("id"));
		    } catch (SQLException ex)
		    {
		        ex.printStackTrace();
		    }
		    try
		    {
		        bs.setStrAddress (rs.getString ("address"));
		    } catch (SQLException ex1)
		    {
		        ex1.printStackTrace();
		    }
		    .....
     	}
	}

这样本没有错误，而且使得程序逻辑更清晰了。
好的下面我们继续向后看。
在后面的某个时候，我需要对rs.next()为空的情况进行处理，好的我自然想到按如下方式进行：

	//程序片断4
	void func()
	{
		.......
		ResultSet rs = stmt.executeQuery (sql);
		if ( rs.next () )//表明找到记录
		{
			setBohaoStudentField(bs,rs);
		}else
		{
			....
		}
		..........
	}

	//程序片断5
	private void setBohaoStudentField (final BohaoStudentMenber bs, final ResultSet rs) throws 		SQLException
    {
    	if ( rs.next () )//表明找到记录
    	{
            ......
			try
		    {
		        bs.setId (rs.getInt ("id"));
		    } catch (SQLException ex)
		    {
		        ex.printStackTrace();
		    }
		    try
		    {
		        bs.setStrAddress (rs.getString ("address"));
		    } catch (SQLException ex1)
		    {
		        ex1.printStackTrace();
		    }
		    .....
     	}
	}

这样做了之后，程序出现了错误，我不知道错在哪里，
但是我知道在我这样改了之后，程序就出错了，
好的，我就在我更改的地方进行断点跟踪，
最后发现是“//程序片断4”	和“//程序片断5”的调用出现错误了，
为什么呢？我并没有更改他们的调用方式阿，为什么错误了呢？
为什么在“//程序片断4”中的if ( rs.next () ) 判断为真，
但是在“//程序片断5”中的if ( rs.next () ) 判断为假了呢？
查看帮助文档，发现 ResultSet.next() 的说明是这样的:
boolean next()
          Moves the cursor down one row from its current position.
我突然意识到我犯了一个致命的错误,在我调用
	setBohaoStudentField(bs,rs);
函数之前,我作了一次
    if ( rs.next () )
判断,之后在
	setBohaoStudentField
函数体内部我又再次做了一次
	if ( rs.next () )
判断,
到这里就明白了,这个时候的判断,
记录集 rs 的游标已经因为在调用之前的那次判断而向下移动了一个,
也就是说当前的记录改变了,
这就是所有的症结所在.
这真是让人很郁闷的事情啊,还好,我及时发现了,
要是等到后面的某个时候去调试,那还不知道要跟踪到什么时候呢!!


用 Collection 类时，要用到 Iterator，
通过 Iterator 来去Collection中的对象，
那么 Iterator.next() 前一定要加上强制转换，
例如：News news = (News) iterator.next ();











mysql> select * from bohaodb.news where topic like '%余%';
+----+----------------------------+------------------------------+------+-------
-----+-----------------------------+---------------------+-------------+
| id | topic                      | content                      | hits | catego
ryid | picture                     | publishtime         | publishuser |
+----+----------------------------+------------------------------+------+-------
-----+-----------------------------+---------------------+-------------+
|  1 | 余总一行到鄂州陈玲娟家视察 | 余总一行到鄂州陈玲娟家视察。 |    3 |
   0 | /upload/images/陈玲娟家.jpg | 2007-02-04 00:00:00 |             |
+----+----------------------------+------------------------------+------+-------
-----+-----------------------------+---------------------+-------------+
1 row in set (0.00 sec)



2007.11.13
netbean使用问题：

NetBeans web app deployment problem (to Apache Tomcat) solved!
If you get the following error in NetBeans when you try to deploy your web app to Apache Tomcat:
 
Access to Tomcat server has not been authorized. Set the correct username and password with the "manager" role in the Tomcat customizer in the Server Manager.
 
Try configuring the "tomcat-users.xml" file so the "manager" role is present - file should be in "%CATALINA_HOME%\conf\tomcat-users.xml" (don't forget to change the username and password!):

<?xml version='1.0' encoding='utf-8'?>
<tomcat-users>
  <role rolename="tomcat"/>
  <role rolename="role1"/>
  <user username="tomcat" password="tomcat" roles="tomcat"/>
  <user username="role1" password="tomcat" roles="role1"/>
  <user username="both" password="tomcat" roles="tomcat,role1"/>
</tomcat-users>


Then configure NetBeans to use the same credentials (Tools > Servers):
在Netbeans此处输入上面的用户名和密码.


使用NetBeans6.0开始JSP之旅
下载地址：
NetBeans6.0二进制包：
Tomcat5.5二进制包：

Tomcat5.5安装，在命令行里运行 bin\startup.bat install


2008/1/19
tomcatPlugin下载
http://www.eclipsetotale.com/tomcatPlugin.html

struts下载
http://struts.apache.org/
http://struts.apache.org/download.cgi#struts2011






2008/2/24
Hibernate学习











2008/01/15

项目编号
http://10.64.11.8/devwiki/TaskCategory

1. JIRA
Account: zili.wei
PWD: aaa123
URL: http://10.64.19.11:8000
2. WIKI
Account: zili.wei
PWD: aaa123
URL: http://10.64.11.8/devwiki
3. Bugzilla
Account: c-zili.wei@accessmedia.com.cn
PWD: aaa123
URL: http://10.64.19.11/bugzilla
Any questions are welcome.


杨丛宇Cindy
邓覃丽Chery
王平


孙览江（Stephen Sun）: 北邮研二学生 
TEAM：Product
联系电话：13810724580
公司邮箱： c-lanjiang.sun@accessmedia.com.cn
MSN：lanjiangsun@gmail.com

 

魏自立：北邮研一学生 
TEAM：SERVER
联系电话：15801463655
公司邮箱：c-zili.wei@accessmedia.com.cn
MSN：zieckey@hotmail.com
 

柴可：软通动力 
TEAM：SERVER
联系电话：NA
公司邮箱：c-ke.chai@accessmedia.com.cn
MSN：NA 


 
mysql> source melodeo_smartone_20080115.sql


修改文件：
D:\tools\jakarta-tomcat-5.0.28-MD\binstartup.bat
 set CATALINA_OPTS="-Djava.security.auth.login.config=D:\workspace\PROJ-S001_SmarTone_MD_Backend\conf\md_jaas_realm.config"
 
 
D:\tools\jakarta-tomcat-5.0.28-MD\conf\Catalina\localhost\md.xml 
 		<parameter>
			<name>password</name>
			<value>123456</value>
		</parameter>
		
		<parameter>
			<name>url</name>
			<value>
				jdbc:mysql://10.64.20.110:3306/melodeo?useUnicode=true&amp;characterEncoding=utf-8
			</value>
		</parameter>		
 
 		另外,Hibernate里的数据库url要与上面的一致
				
D:\tools\jakarta-tomcat-5.0.28-MD\conf\Catalina\localhost\md.xml				
<Context path="/md" docBase="D:\\workspace\\PROJ-S001_SmarTone_MD_Backend\\web"
	debug="0" reloadable="true" privileged="true">				
				
配置Tomcat
	添加路径，添加JDK，添加参数: -Djava.security.auth.login.config="D:\workspace\PROJ-S001_SmarTone_MD_Backend\conf\md_jaas_realm.config"		
				
				
			
				
2008/1/16
svn
http://10.64.19.11/svn/database
http://10.64.19.11/svn/MDBackend
http://10.64.19.11/svn/musicServer

svn username and password
 weizili @ weizili		
 
 weizili @ weizili123						
 
 
server:
10.64.20.110
root & ams@md


backend md testing server
http://10.64.20.110/md
username and password



project document
\\10.64.19.11\archive\ProjectDocument\SmarTone_MD















2008/1/17
ant1.7下载：http://ant.apache.org/bindownload.cgi
hibernate下载：http://sourceforge.net/project/showfiles.php?group_id=40712
注意下载：Hibernate、Hibernate-Extension和Middlegen-Hibernate软件包的最新版本



    <property name="connection.datasource">java:comp/env/jdbc/MDDS</property>
     <property name="dialect">net.sf.hibernate.dialect.MySQLDialect</property>
     <property name="show_sql">false</property>
	 <property name="connection.url">jdbc:mysql://localhost:3306/melodeo?useUnicode=true&amp;characterEncoding=UTF-8</property>


下载的 Ant 软件包，解压缩（如C:\ant\）。并将其bin目录（如c:\ant\bin）添加到系统
PATH 中。

1． POJO
POJO 在Hibernate 语义中理解为数据库表所对应的Domain Object。这里的POJO
就是所谓的“Plain Ordinary Java Object”，字面上来讲就是无格式普通Java 对象，简
单的可以理解为一个不包含逻辑代码的值对象（Value Object 简称VO）。
一个典型的POJO：

import java.io.Serializable;

public class TUser implements Serializable {
	/**
	 * 
	 */
	private static final long serialVersionUID = 6489358110949344062L;
	private String name;

	public TUser(String name) {
		this.name = name;
	}

	/** default constructor */
	public TUser() {
	}

	public String getName() {
		return this.name;
	}

	public void setName(String name) {
		this.name = name;
	}
}


2． Hibernate 映射文件
Hibernate 从本质上来讲是一种“对象－关系型数据映射”（Object Relational
Mapping 简称ORM）。前面的POJO在这里体现的就是ORM中Object层的语义，
而映射（Mapping）文件则是将对象（Object）与关系型数据（Relational）相关联
的纽带，在Hibernate中，映射文件通常以“.hbm.xml”作为后缀。
构建Hibernate基础代码通常有以下途径：
1． 手工编写
2． 直接从数据库中导出表结构，并生成对应的ORM文件和Java 代码。
这是实际开发中最常用的方式，也是这里所推荐的方式。
通过直接从目标数据库中导出数据结构，最小化了手工编码和调整的可能性，从而
最大程度上保证了ORM文件和Java 代码与实际数据库结构相一致。
3． 根据现有的Java 代码生成对应的映射文件，将Java 代码与数据库表相绑定。
通过预先编写好的POJO 生成映射文件，这种方式在实际开发中也经常使用，特别
是结合了xdoclet 之后显得尤为灵活，其潜在问题就是与实际数据库结构之间可能
出现的同步上的障碍，由于需要手工调整代码，往往调整的过程中由于手工操作的
疏漏，导致最后生成的配置文件错误，这点需要在开发中特别注意。
结合xdoclet，由POJO 生成映射文件的技术我们将在“高级特性”章节中进行探讨。
由数据库产生基础代码
通过Hibernate官方提供的MiddleGen for Hibernate 和Hibernate_Extension工具包，我
们可以很方便的根据现有数据库，导出数据库表结构，生成ORM和POJO。
1) 首先，将Middlegen-Hibernate软件包解压缩（ 如解压缩到C:\Middlegen\ ）。
2) 配置目标数据库参数
进入MiddleGen 目录下的\config\database 子目录，根据我们实际采用的数据库打开
对应的配置文件。如这里我们用的是mysql数据库，对应的就是mysql.xml文件。

主要对以下几行作出更改

   <property name="database.driver"                value="org.gjt.mm.mysql.Driver"/>
   <property name="database.url"                   value="jdbc:mysql://localhost:3306/melodeo?useUnicode=true&amp;characterEncoding=UTF-8"/>
   <property name="database.userid"                value="root"/>
   <property name="database.password"              value="123456"/>
   
   
3) 修改Build.xml
修改MiddleGen 根目录下的build.xml 文件，此文件是Middlegen-Hibernate 的Ant
构建配置。Middlegen-Hibernate将根据build.xml文件中的具体参数生成数据库表映射
文件。可配置的项目包括：
a) 目标数据库配置文件地址
查找关键字 ”!ENTITY”，得到：
<!DOCTYPE project [
<!ENTITY database SYSTEM
"file:./config/database/hsqldb.xml">
]>
默认情况下，MiddleGen 采用的是hsqldb.xml，将其修改为我们所用的数据
库配置文件（mysql.xml）：
<!DOCTYPE project [
<!ENTITY database SYSTEM
"file:./config/database/mysql.xml">
]>
b) Application name
查找：
<property name="name" value="airline"/>
“aireline”是MiddleGen原始配置中默认的 Application Name，将其修改为我们
所希望的名称，如“HibernateSample”：
<property name="name" value="HibernateSample"/>
c) 输出目录
查找关键字“name="build.gen-src.dir"”，得到：
<property name="build.gen-src.dir"
value="${build.dir}/gen-src"/>
修改value="${build.dir}/gen-src"使其指向我们所期望的输出目录，
这里我们修改为：
<property name="build.gen-src.dir"
value="C:\sample"/>
d) 对应代码的Package name
查找关键字“destination”，得到：
<hibernate
destination="${build.gen-src.dir}"
package="${name}.hibernate"
genXDocletTags="false"
genIntergratedCompositeKeys="false"
javaTypeMapper=
"middlegen.plugins.hibernate.HibernateJavaTypeMapper"
/>
可以看到，hibernate 节点package 属性的默认设置实际上是由前面的
Application Name （${name}）和“.hibernate”组合而成，根据我们的需要，
将其改为：
<hibernate
destination="${build.gen-src.dir}"
package="org.hibernate.sample"
genXDocletTags="true"
genIntergratedCompositeKeys="false"
javaTypeMapper=
"middlegen.plugins.hibernate.HibernateJavaTypeMapper"

mysql> desc wapaccesslog;
+-----------+--------------+------+-----+---------+----------------+
| Field     | Type         | Null | Key | Default | Extra          |
+-----------+--------------+------+-----+---------+----------------+
| logId     | int(11)      | NO   | PRI | NULL    | auto_increment |
| userAgent | varchar(255) | YES  |     | NULL    |                |
| msisdn    | varchar(255) | YES  |     | NULL    |                |
| pageUrl   | varchar(255) | YES  |     | NULL    |                |
| logDate   | datetime     | YES  | MUL | NULL    |                |
| areaId    | int(11)      | YES  | MUL | 0       |                |
+-----------+--------------+------+-----+---------+----------------+
6 rows in set (0.11 sec)


数据库备份恢复：mysql -u 用户名 -p 数据库名 < .dump
C:\Documents and Settings\Administrator>mysql -uroot -p123456 test < D:\a.dmp

C:\Documents and Settings\Administrator>


数据库备份：
C:\Documents and Settings\Administrator>mysqldump -uroot -p123456 test > d:\a.sql




Character Description 
% Matches any number of characters, even zero characters 
_ Matches exactly one character 




数据库测试:

1、新增用户数月报	python	y	new user monthly report
查询subscribers表，条件：dateRegistered（注册时间）

查看某一月的新增用户数
SELECT count(clientId) from subscribers WHERE month(dateRegistered)=1 and year(dateRegistered)=2008

查看某一天的新增用户数
SELECT count(clientId) from subscribers WHERE month(dateRegistered)=12 and year(dateRegistered)=2007 and day(dateRegistered)=9

2、下载客户端但未激活用户量月报表	Java	y	unactivated user monthly report

3、推荐客户端用户日报	Java	y	successful client refer daily report
4、客户端下载量日报表	Java	y	client download daily report


5、激活用户数月报	python	y	registered user monthly report 累计
2007-12
SELECT count(clientId) from subscribers 
where (subscribers.connectionStatus="NORMAL" or subscribers.connectionStatus="RESYNCHING")
and ( (subscribers.status="ACTIVE" and subscribers.deactivateDate is null) or DATEDIFF(subscribers.deactivateDate,'2008-1-1')>0 )
and DATEDIFF(subscribers.dateRegistered, '2008-1-1 00:00:00')<0


2008-1
SELECT count(clientId) from subscribers 
where (subscribers.connectionStatus="NORMAL" or subscribers.connectionStatus="RESYNCHING")
and ( (subscribers.status="ACTIVE" and subscribers.deactivateDate is null) or DATEDIFF(subscribers.deactivateDate,'2008-2-1 00:00:00')>0 )
and DATEDIFF(subscribers.dateRegistered, '2008-2-1 00:00:00')<0


6、	按歌手音乐下载量月报表	Java	y	song purchase monthly report (by artist)
7、	按歌手音乐试听量月报表	Java	y	song preview monthly report (by artist)
8、	按歌名音乐下载量月报表	Java	y	song purchase monthly report
9、	按歌名音乐试听量月报表	Java	y	song preview monthly report 
10、按风格音乐下载量月报表	Java	y	song download monthly report (by genre)
11、按风格音乐试听量月报表	Java	y	song preview monthly report (by genre)
12、按唱片公司试听量月报表	Java	y	song preview monthly report (by label)
13、WAP访问用户数日报表	Java	y	WAP link visitor daily report
14、WAP访问量日报表	Java	y	WAP link hits daily report
15、活跃用户数月报表			Total Active User Monthly Report

16、歌曲购买记录表			Song Purchase Transaction Report







<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE struts-config PUBLIC
"-//Apache Software Foundation//DTD Struts Configuration 1.1//EN"
"http://jakarta.apache.org/struts/dtds/struts-config.dtd"><!-- struts-config.xml中的元素必须按照上述doc指令中的dtd文档定义顺序书写，本例即遵从了dtd定义顺序 --><!-- struts-config是整个xml的根元素，其他元素必须被包含其内 -->
<struts-config>
	<!--
		名称:data-sources
		描述：data-sources元素定义了web App所需要使用的数据源
		数量：最多一个
		子元素:data-source
	-->
	<data-sources>
		<!--
			名称：data-source
			描述：data-source元素定义了具体的数据源
			数量：任意多个
			属性：
			@key：当需要配置多个数据源时，相当于数据源的名称，用来数据源彼此间进行区别
			@type：可以使用的数据源实现的类，一般来自如下四个库
			Poolman，开放源代码软件
			Expresso，Jcorporate
			JDBC Pool，开放源代码软件
			DBCP，Jakarta
		-->
		<data-source key="firstOne"
			type="org.apache.commons.dbcp.BasicDataSource">
			<!--
				名称：set-property
				描述：用来设定数据源的属性
				属性：
				@autoCommit:是否自动提交 可选值：true/false
				@description:数据源描述
				@driverClass:数据源使用的类
				@maxCount:最大数据源连接数
				@minCount:最小数据源连接数
				@user:数据库用户
				@password:数据库密码
				@url:数据库url
			-->
			<set-property property="autoCommit" value="true" />
			<set-property property="description" value="Hello!" />
			<set-property property="driverClass"
				value="com.mysql.jdbc.Driver" />
			<set-property property="maxCount" value="10" />
			<set-property property="minCount" value="2" />
			<set-property property="user" value="root" />
			<set-property property="password" value="" />
			<set-property property="url"
				value="jdbc:mysql://localhost:3306/helloAdmin" />
		</data-source>
	</data-sources>

	<!--
		名称：form-beans
		描述：用来配置多个ActionForm Bean
		数量：最多一个
		子元素：form-bean
	-->
	<form-beans>
		<!--
			名称：form-bean
			描述：用来配置ActionForm Bean
			数量：任意多个
			子元素：form-property
			属性：
			@className：指定与form-bean元素相对应的配置类，一般默认使用org.apaceh.struts.config.FormBeanConfig，如果自定义，则必须继承 FormBeanConfig
			@name：必备属性！为当前form-bean制定一个全局唯一的标识符，使得在整个Struts框架内，可以通过该标识符来引用这个ActionForm Bean。
			@type：必备属性！指明实现当前ActionForm Bean的完整类名。
		-->
		<form-bean name="Hello" type="myPack.Hello">
			<!--
				名称：form-property
				描述：用来设定ActionForm Bean的属性
				数量：根据实际需求而定，例如，ActionForm Bean对应的一个登陆Form中有两个文本框，name和password，ActionForm Bean中也有这两个字段，则此处编写两个form-property来设定属性
				属性：
				@className：指定与form-property相对应的配置类，默认是org.apache.struts.config.FormPropertyConfig，如果自定义，则必须继承FormPropertyConfig类
				@name：所要设定的ActionForm Bean的属性名称
				@type：所要设定的ActionForm Bean的属性值的类
				@initial：当前属性的初值
			-->
			<form-property name="name" type="java.lang.String" />
			<form-property name="number" type="java.lang.Iteger"
				initial="18" />
		</form-bean>
	</form-beans>

	<!--
		名称：global-exceptions
		描述：处理异常
		数量：最多一个
		子元素：exception
	-->
	<global-exceptions>
		<!--
			名称：exception
			描述：具体定义一个异常及其处理
			数量：任意多个
			属性：
			@className:指定对应exception的配置类，默认为org.apache.struts.config.ExceptionConfig
			@handler:指定异常处理类，默认为org.apache.struts.action.ExceptionHandler
			@key:指定在Resource Bundle种描述该异常的消息key
			@path:指定当发生异常时，进行转发的路径
			@scope:指定ActionMessage实例存放的范围，默认为request，另外一个可选值是session
			@type:必须要有！指定所需要处理异常类的名字。
			@bundle:指定资源绑定
		-->
		<exception key="hello.error"  path="/error.jsp" scope="session"
			type="hello.HandleError" />
	</global-exceptions>

	<!--
		名称：global-forwards
		描述：定义全局转发
		数量：最多一个
		子元素：forward
	-->
	<global-forwards>
		<!--
			名称：forward
			描述：定义一个具体的转发
			数量：任意多个
			属性：
			@className:指定和forward元素对应的配置类，默认为org.apache.struts.action.ActionForward
			@contextRelative:如果为true，则指明使用当前上下文，路径以“/”开头，默认为false
			@name:必须配有！指明转发路径的唯一标识符
			@path:必须配有！指明转发或者重定向的URI。必须以"/"开头。具体配置要与contextRelative相应。
			@redirect:为true时，执行重定向操作，否则执行请求转发。默认为false
		-->
		<forward name="A" path="/a.jsp" />
		<forward name="B" path="/hello/b.do" />
	</global-forwards>

	<!--
		名称：action-mappings
		描述：定义action集合
		数量：最多一个
		子元素：action
	-->
	<action-mappings>
		<!--
			名称：action
			描述：定义了从特定的请求路径到相应的Action类的映射。每个action元素接收path属性定义的请求，
				并映射到type属性所定义的具体action对象。在映射过程中将name属性定义的ActionForm内容一并传送过去
			数量：任意多个
			子元素：exception,forward（二者均为局部量）
			属性：
			@attribute:制定与当前Action相关联的ActionForm Bean在request和session范围内的名称（key）
			@className:与Action元素对应的配置类。默认为org.apache.struts.action.ActionMapping
			@forward:指名转发的URL路径
			@include:指名包含的URL路径
			@input:指名包含输入表单的URL路径，表单验证失败时，请求会被转发到该URL中
			@name:指定和当前Acion关联的ActionForm Bean的名字。该名称必须在form-bean元素中定义过。
			@path:指定访问Action的路径，以"/"开头，没有扩展名
			@parameter:为当前的Action配置参数，可以在Action的execute()方法中，通过调用ActionMapping的getParameter()方法来获取参数
			@roles:指定允许调用该Aciton的安全角色。多个角色之间用逗号分割。处理请求时，RequestProcessor会根据该配置项来决定用户是否有调用该Action的权限
			@scope:指定ActionForm Bean的存在范围，可选值为request和session。默认为session
			@type:指定Action类的完整类名
			@unknown:值为true时，表示可以处理用户发出的所有无效的Action URL。默认为false
			@validate:指定是否要先调用ActionForm Bean的validate()方法。默认为true
			注意：如上属性中，forward/include/type三者相斥，即三者在同一Action配置中只能存在一个。
		-->
		<action path="/search" type="addressbook.actions.SearchAction"
			name="searchForm" scope="request" validate="true"
			input="/search.jsp">
			<forward name="success" path="/display.jsp" />
		</action>
	</action-mappings>

	<!--
		名称：controller
		描述：用于配置ActionServlet
		数量：最多一个
		属性：
		@bufferSize:指定上传文件的输入缓冲的大小.默认为4096
		@className:指定当前控制器的配置类.默认为org.apache.struts.config.ControllerConfig
		@contentType:指定相应结果的内容类型和字符编码
		@locale:指定是否把Locale对象保存到当前用户的session中,默认为false
		@processorClass:指定负责处理请求的Java类的完整类名.默认org.apache.struts.action.RequestProcessor
		@tempDir:指定文件上传时的临时工作目录.如果没有设置,将才用Servlet容器为web应用分配的临时工作目录.
		@nochache:true时,在相应结果中加入特定的头参数:Pragma ,Cache-Control,Expires防止页面被存储在可数浏览器的缓存中,默认为false
	-->
	<controller contentType="text/html;charset=UTF-8" locale="true"
		processorClass="CustomRequestProcessor">
	</controller>
	
	
	<!--
		名称:message-resources
		描述:配置Resource Bundle.
		数量:任意多个
		属性:
		@className:指定和message-resources对应的配置类.默认为org.apache.struts.config.MessageResourcesConfig
		@factory:指定资源的工厂类,默认为org.apache.struts.util.PropertyMessageResourcesFactory
		@key:
		@null:
		@parameter:
	-->
	<message-resources null="false" parameter="defaultResource" />
	<message-resources key="images" null="false"
		parameter="ImageResources" />

	<!--
		名称:plug-in
		描述:用于配置Struts的插件
		数量:任意多个
		子元素:set-property
		属性:
		@className:指定Struts插件类.此类必须实现org.apache.struts.action.PlugIn接口
	-->
	<plug-in className="org.apache.struts.validator.ValidatorPlugIn">
		<!--
			名称:set-property
			描述:配置插件的属性
			数量:任意多个
			属性:
			@property:插件的属性名称
			@value:该名称所配置的值
		-->
		<set-property property="pathnames"
			value="/WEB-INF/validator-rules.xml,/WEB-INF/vlaidation.xml" />
	</plug-in>

</struts-config>









2008/2/15
displaytag

十、分页
　　
　　实现分页非常的简单，增加一个pagesize属性指定一次想显示的行数即可
　　
　　<display:table name="sessionScope.test" pagesize="10">
　　<display:column property="id" title="ID" />
　　<display:column property="name" />
　　<display:column property="email" />
　　<display:column property="status" />
　　</display:table>









displaytag分页 使用
1.下载displaytag的几个库文件,和辅助包apache的commons-lang-2.1，其中要求是2.1版本的。
2.修改web.xml,加上：
 <servlet>
        <servlet-name>DisplaySource</servlet-name>
        <display-name>DisplaySource</display-name>
        <description>display source of sample jsp pages</description>
        <servlet-class>org.displaytag.sample.DisplaySourceServlet</servlet-class>
    </servlet>

    <servlet-mapping>
        <servlet-name>DisplaySource</servlet-name>
        <url-pattern>*.source</url-pattern>
    </servlet-mapping>

    <mime-mapping>
        <extension>css</extension>
        <mime-type>text/css</mime-type>
    </mime-mapping>
3.The prefix identifies the tags in the tag library within the JSP page.
  <%@ taglib uri="http://displaytag.sf.net" prefix="display" %>
不用在web.xml中定义，并加载。因为displaytag.tld已经在jar文件包括好了。
The declaration, if you are using a JSP XML syntax, looks like:
  <jsp:root version="1.2" xmlns:jsp="http://java.sun.com/JSP/Page"
     xmlns:display="urn:jsptld:http://displaytag.sf.net">


4.然后在页面中取出数据
<%
List<President> list=new com.PagedData().getData();
request.setAttribute("test",list);
%>
最简单的形式：    <display:table name="test" />
    display tag会自动生成一个table,显示所有数据

5.
<display:table name="sessionScope.test"  cellspacing="0" cellpadding="0" pagesize="10"  defaultsort="1" defaultorder="descending">
  <display:column property="term"   sortable="true"/>
  <display:column property="firstName"  url="/aa.jsp" paramId="term" paramProperty="term" sortable="true"/>
  <display:column property="lastName" title="aaaa"  sortable="true"/>
</display:table>
如果数据有中文，只要在jsp中加上：
<%@ page language="java" contentType="text/html;charset=GBK"%>
6.
标签取得数据的数据源
  有四种范围
   pageScope
   requestScope (默认)  <display:table name="test2" >
   sessionScope  <display:table name="sessionScope.holder.list" > 注意，这里要指定范围，非默认
   applicationScope 


存在的问题：
1.当使用sessionScope.test，可以排序，但导出的数据为空。
2.当使用的默认的requestScope，可以导出数据，而不可排序。
不知是什么原因？？？？














DisplayTag七宗罪
[2007年7月6日 发布]
最近比较乱,很长时间没更新空间了,正好今天有话题,准备更新下^_^
 
Display Tag Lib是一个标签库,主要用来处理jsp网页上的Table,功能非常强,可以对的Table进行分页、数据导出、分组、对列排序等等,而且使用起来非常的方便,能够大大减少代码量.
 
记得有N多朋友问过分页问题如何可以更加方便、快速的处理,我的回答好象每次都是"DisplayTag",然后步骤相同的向朋友讲它有什么功能、能减少多少编码量、发文档、如何看war例子.以至于当时都想把操作过程录下来,来降低我的口水消耗量.
 
俗话说得好"路遥知马力",经过不断的使用,感觉DisplayTag"肾虚"了,问题与缺陷越来越多.现在还在使用它的朋友,如果已经放弃不用,那么就别浪费时间看这个了;如果还在使用的朋友,最好能看看我总结的DisplayTag罪状,倒能弥补些缺陷,不至于问题出现时记恨在下.呵呵.
 
1.中文翻页、排序问题:对于中文无法翻页、排序,最简单的办法是修改Tomcat下的server.xml文件.找到HTTP的Connector标签,在里面添加一项URIEncoding="...",引号里面的内容取决于你的页面编码,比如可以是GBK,UTF-8等.
 
2.分页数据加载问题:DisplayTag的分页机制是这样的,它把所有的数据放入集合中,然后再进行分页处理.这样在数据量比较大的情况下,很容易造成性能下降或者内存超支等问题.目前解决方法有两个,一是在<displaytag>中增加两个属性：partialList="true"size="resultSize",每次只加再当前页数据.还有就是实现 org.displaytag.pagination.PaginatedList接口,自定义分页算法.个人推荐第二种,详细的实现方法可参考DisplayTag 1.1所带的例子.
PS:第二种方法还不完善,DisplayTag中仍存在一些Bug.
 
3.导出中文Excel问题:当导出中文列表名和中文表格数据Excel时,会产生乱码现象.
解决:
更改配置文件displaytag.properties,使用displaytag-export-poi.jar包.更改export.excel.class=org.displaytag.export.ExcelView为export.excel.class=org.displaytag.excel.ExcelHssfView,这样可以解决中文表格数据的问题.对于中文列表名乱码的问题,必须更改org.displaytag.excel.ExcelHssfView源代码:
 
old:
HSSFCell cell = xlsRow.createCell((short) colNum++);
cell.setCellValue(columnHeader);
cell.setCellStyle(headerStyle);
cell.setEncoding(HSSFCell.ENCODING_UTF_16);
 
new:
HSSFCell cell = xlsRow.createCell((short) colNum++);
cell.setEncoding(HSSFCell.ENCODING_UTF_16);
cell.setCellValue(columnHeader);
cell.setCellStyle(headerStyle);
 
还有一种通过修改编码方式来支持中文的方法,那就是将org.displaytag.export.ExcelView.java中的getMimeType()方法内容修改为return "application/vnd.ms-excel;charset=GB2312";但是这样修改后,导出速度将会非常慢,呵呵.
 
4.decorator内容无法导出问题和Html标签导出问题:如果对table进行了decorator,那么decorator后的内容将无法导出.目前此问题无法解决.所以最好不用decorator.如果显示的内容使用了html标签进行了修饰,那么它会将html标签一起导出.也是没有什么好的解决方法.
 
5.导出Excel兼容性问题:有时会出现兼容性问题,导出的Excel在Office 2003下打不开.
PS:导出问题不少,尤其是Excel.建议使用Apache POI自己实现Excel的导出.
 
6.同页面使用多个displayTag翻页问题.DisplayTag翻页时,页面上所有的displayTag元素都翻页.解决办法:对页面中的每个表格,先判断它的记录是否为0,如果为0则不使用DisplayTag.
 
7.未知Bug比较多:正式发布版本总是存在很多Bug.在1.1版本发布时,居然分页算法出现了明显Bug,无语.






















2008/02/18
CVS

eclipse下CVS

添加CVS Repositories
选择 Windows->Show View->Other->CVS Repositories
在右下方的 CVS Repositories 视图中 右键->New->Repository Location...


CVS共享

eclipse
在 Packet Explorer 中右键点击项目名称，Team->Share Project ->Create a new repository location

Host:localhost (或者IP)
repository path: /CVS

user: 
password





   在Windows上安装Subversion和CVS服务器软件[ZT]     2006-02-26 21:36:15 
大 中 小 
在Windows上安装Subversion和CVS服务器软件
.....................................

   Subversion和CVS是两个比较重要的开源版本控制软件，通常我们会将其安装在Unix-like系统上，由于实际的一些需要，我们需要将其安装在Windows环境下，下面就是这两款软件在Windows系统下的安装说明。
 
安装Subversion 
 
首先下载Subversion Windows版本的服务器软件，下载地址如下：
http://subversion.tigris.org/servlets/ProjectDocumentList?folderID=91
如svn-1.2.1-setup.exe，然后执行安装，安装目录如：d:\develop\subversion，然后这是一下系统的环境变量Path，将Subversion的bin路径加入到系统的path中。
创建Subersion库：首先建立一个目录存放所有的Subversion库，这里我们可以称之为Data Directory，就如同数据库软件的Data目录一样，如D:\repository\subversion。
创建一个新的Subversion库，这里名称为repo1，将来我们需要将一些项目存放在这个库种。只需执行： svnadmin create D:\repository\subversion\repo1
下面需要设置库的用户信息，只需打开repo1库目录下的conf子目录，在passwd文件添加新的用户即可，如
[users]
admin = mypassword
接下来是设置库的一些其他信息，打开conf目录下的svnserve.conf文件，然后进行如下设置即可：
[general]
anon-access = read
auth-access = write
password-db = passwd
realm = repo1
启动Subversion，这里可以通过命令行启动，最好使用SVN Service Wrapper，你可以通过以下地址下载：http://dark.clansoft.dk/~mbn/svnservice，将 SVNService.exe拷贝到Subversion安装主目录的bin目录下即可，然后执行以下命令，就可以将Subversion以 windows服务方式启动啦。
SVNService -install -d -r D:\repository\subversion
向Subversion 中导入项目：现在我们需要将项目导入到Subversion的库中，只需执行一下命令： svn import d:\demo svn://localhost/repo1/demo -m "initial import" --username admin --password abc123
这样项目就导入到subversion库中啦。
将项目导出：从Subversion项目中导出项目也很简单，只需执行以下操作：
svn co svn://localhost/repo1/demo --username admin --password mypassword
 
安装CVSNT
 
首先从www.cvsnt.org下载CVS服务器软件，文件名为cvsnt-2.5.01.1976.msi，CVSNT需要使用NTFS的文件格式，所以确保CVSNT和库安装在NTFS上，然后将CVSNT的主目录下的bin目录添见到系统的path路径中。
CVSNT的设置。打开CVSNT Control Panel，点击“Server Settings”，这里我们需要设置一下“Run as”和“Default”，分别是运行CVSNT程序的用户和计算机名称，这里可以设置系统的administrator即可。
接下来我们需要设置CVS库，只需在设置面板中选择“Repositories”，然后创建相关的库即可。然后我们就可以通过:pserver:username@localhost:/reposname去引用这个库。
设置库的权限。下面我们需要设置访问CVS库的用户信息，这里我们需要添加新的用户。在服务器端，设置一下CVSROOT，这里CVSROOT为库所在的目录，如d:\respository\cvs\respo1，然后执行cvs passwd命令即可，如下：
> cvs passwd –a –r administrator username
这样就添加了一个新的访问特定库的新用户，这个新用户将映射为adminstrator（安全方面你需要自行考虑）。如果不设置CVSROOT，可以通过 cvs –d d:\respository\cvs\respo1 直接访问库目录。关于cvs的passwd的命令，请参考 cvs passwd –help
创建CVS 库的管理员，只需将CVS的用户名称写入CVSROOT/admin文件中即可（一行一个用户名称，最后一个用户后添见一个空白行）。其他设置读取或写入权限，只需设置 readers 和 writers文件即可。
其他相关的设置，请参考CVSNT的配置文档。





首先从www.cvsnt.org下载CVS服务器软件，文件名为cvsnt-2.5.01.1976.msi，CVSNT需要使用NTFS的文件格式，所以确保CVSNT和库安装在NTFS上，然后将CVSNT的主目录下的bin目录添见到系统的path路径中。
CVSNT的设置。打开CVSNT Control Panel，点击“Server Settings”，这里我们需要设置一下“Run as”和“Default”，分别是运行CVSNT程序的用户和计算机名称，这里可以设置系统的administrator即可。
接下来我们需要设置CVS库，只需在设置面板中选择“Repositories”，然后创建相关的库即可。然后我们就可以通过:pserver:username@localhost:/reposname去引用这个库。
设置库的权限。下面我们需要设置访问CVS库的用户信息，这里我们需要添加新的用户。在服务器端，设置一下环境变量CVSROOT，这里CVSROOT为库所在的目录，如d:\CVS，然后执行cvs passwd命令即可，如下：
> cvs passwd –a –r administrator username

C:\Documents and Settings\Administrator>cvs passwd -a -r administrator root
Adding user root
New Password:
Verify Password:

这样就添加了一个新的访问特定库的新用户，这个新用户将映射为adminstrator（安全方面你需要自行考虑）。





 

总结：我们的开发环境通常都是Windows的，所以了解Subversion和CVS在Windows下的安装对我们使用VCS系统非常有帮助。安装完毕版本控制以后，你最好使用一款IDE工具做日常开发，如果你的工具对版本控制系统支持的不好的话，那会浪费你很多的时间。事实上，我们只需IDEA即可，它可以浏览Subversion或CVS库、导入项目、Check Out项目、开发集成等等，你不需要任何客户端软件就可以投入开发，而那些服务端的配置，交给SCM管理员就可以啦。

//注：原文出处：http://www.jetmaven.net/documents/j_installSubversionCVS_win.php

文章引用自： 
分类：工具软件的安装评论(0) 引用 阅读(33) 圈子 编辑 打印 有奖举报 
前一篇：Java数组
后一篇：在Windows平台上设置CVS服务器[ZT]











2008.02.21
login.jsp

<%@ page language="java" pageEncoding="ISO-8859-1"%>
<%@ taglib uri="http://struts.apache.org/tags-bean" prefix="bean"%>
<%@ taglib uri="http://struts.apache.org/tags-html" prefix="html"%>

<html>
	<head>
		<title>JSP for LoginForm form</title>
	</head>
	<body>
		<html:form action="/login">
			loginId : <html:text property="loginId" />
			
			<html:errors property="loginId" />
			
			<br />
			password : <html:password property="password" />
			<html:errors property="password" />
			<br />
			<html:submit /> 
			<input type="reset" value="Reset" name="reset"> 
		</html:form>
	</body>
</html>




package com.accessmedia.managerimpl;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

import com.accessmedia.manager.ITrans;

public class TransString2Date implements ITrans {

	public Date tans(String activeDate) {
		Date result= new Date();
		SimpleDateFormat sdf=new SimpleDateFormat("yyyy-MM-dd");
        try {
			result=sdf.parse(activeDate);
		} catch (ParseException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return result;
	}

}







action 继承 org.apache.struts.actions.DispatchAction











javascript js 在一个frame中控制另一个frame跳转,
例如一个页面是一个上下页面框架，想通过上面的页面控制下面的页面在跳转。

框架文件
<frameset rows="80,*" frameborder="no" border="0" framespacing="0">
		<frame src="mainentry/topFrame.jsp" name="topFrame"
			noresize="noresize" id="topFrame" title="topFrame" scrolling="no" />
		<frame src="mainentry/mainFrame.jsp" name="mainFrame" id="mainFrame" scrolling="no" title="mainFrame" />
</frameset>

页面上：
	<TD width=90>
		<A href="javascript:void(0);" onclick="submitChange('../useragents/ListUseragent.jsp');">
			<IMG height=30 alt="" src="../images/mainentry/viewUA.gif" width=220 border=0>
		</A>
	</TD>
	
js
<SCRIPT language=javascript>
<!--
//仅仅mainFrame跳转
function submitChange(jspUrl)
{
	parent.mainFrame.location.href=jspUrl;//这里的mainFrame是框架文件中定义的
}

//整个页面都跳转
function submitExit( jspUrl )
{
	parent.location.href=jspUrl;
}

//-->


</SCRIPT>	










html中的form action
<form method="post" action="login.do">

struts标签的form action
<form method="post" action="/login">







Hibernate

Hibernate is a very popular open-source Java-based object-relational mapping (JORM) engine that is easy to get up and running. It provides a rich set of features including: 

	Multiple mapping strategies 
	Transitive persistence 
	Single object to multiple table mapping 
	Collections support 
	Polymorphic associations 
	Customizable SQL queries 




有时候出现一些错误本来应该不会发生的，却一直在发生，看看是不是编译库和运行库一致







一个简单的Hibernate入门示例：
 
	在 Java Web 开发应用中，Hibernate可以作为应用程序的数据访问层。
这里以一个简单用户注册用例来说明如何开发一个Hibernate的应用程序。
该例子的需求：把注册页面输入的用户名、密码、性别、年龄方面的信息存入数据库中。
如果采用经典的MVC模式的话，那么各层的构建如下：

	视图层：注册页面(register.jsp)、反馈信息页面(reply.jsp)
	控制层：RegisterServlet.java
	模型层/数据访问层：基础类HibernateSessionFactory.java、持久化类Register.java、
						配置文件hibernate.cfg.xml、映射文件register.hbm.xml等等
	数据库层:采用MySQL数据库，数据表t_register			
	
本例子用的是Hibernate3.1和JDK1.4
	
下面分步来构建这个Hibernate应用程序。

1、创建数据库
	
DROP TABLE IF EXISTS `t_register`;
CREATE TABLE `t_register` (
  `id` int(11) NOT NULL,
  `username` varchar(30) collate utf8_unicode_ci default NULL,
  `password` varchar(30) collate utf8_unicode_ci default NULL,
  `sex` varchar(10) collate utf8_unicode_ci default NULL,
  `age` int(10) default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;


2、创建视图层页面

清单1：register.jsp
---------------------------------------------------------------------------------------
<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>

<html>
	<head>
		<title>用户注册页面</title>
	</head>

	<body>
		<form action="RegisterServlet" method="post">
			用户名：
			<input type="text" name="username">
			<br>
			密码：
			<input type="password" name="password">
			<br>
			性别：
			<input type="text" name="sex">
			<br>
			年龄：
			<input type="text" name="age">
			<br />
			<input type="submit" name="submit" value="submit">
		</form>
	</body>
</html>
---------------------------------------------------------------------------------------

清单2:reply.jsp
---------------------------------------------------------------------------------------
<%@ page language="java" import="java.util.*" pageEncoding="ISO-8859-1"%>

<html>
  <head>
    <title>Successfully</title>
  </head>
  <body>
    Inster data into database successfully! <br>
  </body>
</html>

---------------------------------------------------------------------------------------


3、设计持久化类
对应于数据库中表项。
清单3：Register.java
---------------------------------------------------------------------------------------
package register;

public class Register {
	int id;
	Integer age;
	String username = new String();
	String password = new String();
	String sex = new String();
	
	public Integer getAge() {
		return age;
	}
	public void setAge(Integer age) {
		this.age = age;
	}
	public int getId() {
		return id;
	}
	public void setId(int id) {
		this.id = id;
	}
	public String getPassword() {
		return password;
	}
	public void setPassword(String password) {
		this.password = password;
	}
	public String getSex() {
		return sex;
	}
	public void setSex(String sex) {
		this.sex = sex;
	}
	public String getUsername() {
		return username;
	}
	public void setUsername(String username) {
		this.username = username;
	}
}
---------------------------------------------------------------------------------------


4、设计Hibernate配置文件
清单4：hibernate.cfg.xml
---------------------------------------------------------------------------------------
<?xml version='1.0' encoding='UTF-8'?>
<!DOCTYPE hibernate-configuration PUBLIC
          "-//Hibernate/Hibernate Configuration DTD 3.0//EN"
          "http://hibernate.sourceforge.net/hibernate-configuration-3.0.dtd">

<!-- Generated by MyEclipse Hibernate Tools.                   -->
<hibernate-configuration>

    <session-factory>
        <property name="connection.username">root</property>
        <property name="connection.url">jdbc:mysql://localhost:3306/study</property>
        <property name="dialect">org.hibernate.dialect.MySQLDialect</property>
        <property name="myeclipse.connection.profile">MySQL</property>
        <property name="connection.password">123456</property>
        <property name="connection.driver_class">com.mysql.jdbc.Driver</property>
    
    	<mapping resource="register.hbm.xml" />
    </session-factory>

</hibernate-configuration>
---------------------------------------------------------------------------------------

5、设计映射文件
数据库表到Java类数据项的映射
清单5：register.hbm.xml
---------------------------------------------------------------------------------------
<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE hibernate-mapping PUBLIC "-//Hibernate/Hibernate Mapping DTD 3.0//EN"
"http://hibernate.sourceforge.net/hibernate-mapping-3.0.dtd">

<hibernate-mapping package="register">
	<class name="register.Register" table="T_Register">
		<id name="id" type="java.lang.Integer">
			<column name="id" />
			<generator class="increment"></generator>
		</id>

		<property name="username" type="java.lang.String">
			<column name="username" length="30" />
		</property>
		<property name="password" type="java.lang.String">
			<column name="password" length="30" />
		</property>
		<property name="sex" type="java.lang.String">
			<column name="sex" length="10" />
		</property>
		<property name="age" type="java.lang.Integer">
			<column name="age" />
		</property>

	</class>
</hibernate-mapping>
---------------------------------------------------------------------------------------


6、设计Hibernate的基础类HibernateSessionFactory.java
	HibernateSessionFactory.java包含了Configuration实例、SessionFactory实例和Session实例的生成函数，
这样应用程序就可以直接调用HibernateSessionFactory来生成Session实例，不必再重复编写Configuration实例、
SessionFactory实例和Session实例的生成代码了。
清单6：HibernateSessionFactory.java
---------------------------------------------------------------------------------------
package register;

import org.hibernate.HibernateException;
import org.hibernate.Session;
import org.hibernate.cfg.Configuration;

public class HibernateSessionFactory {

	private static String CONFIG_FILE_LOCATION = "/hibernate.cfg.xml";
	private static final ThreadLocal threadLocal = new ThreadLocal();
	private static Configuration configuration = new Configuration();
	private static org.hibernate.SessionFactory sessionFactory;
	private static String configFile = CONFIG_FILE_LOCATION;

	private HibernateSessionFactory() {
	}

	/**
	 * Returns the ThreadLocal Session instance.  Lazy initialize
	 * the <code>SessionFactory</code> if needed.
	 *
	 *  @return Session
	 *  @throws HibernateException
	 */
	public static Session getSession() throws HibernateException {
		Session session = (Session) threadLocal.get();

		if (session == null || !session.isOpen()) {
			if (sessionFactory == null) {
				rebuildSessionFactory();
			}
			session = (sessionFactory != null) ? sessionFactory.openSession()
					: null;
			threadLocal.set(session);
		}

		return session;
	}

	/**
	 *  Rebuild hibernate session factory
	 *
	 */
	public static void rebuildSessionFactory() {
		try {
			configuration.configure(configFile);
			sessionFactory = configuration.buildSessionFactory();
		} catch (Exception e) {
			System.err.println("%%%% Error Creating SessionFactory %%%%");
			e.printStackTrace();
		}
	}

	/**
	 *  Close the single hibernate session instance.
	 *
	 *  @throws HibernateException
	 */
	public static void closeSession() throws HibernateException {
		Session session = (Session) threadLocal.get();
		threadLocal.set(null);

		if (session != null) {
			session.close();
		}
	}

	/**
	 *  return session factory
	 *
	 */
	public static org.hibernate.SessionFactory getSessionFactory() {
		return sessionFactory;
	}

	/**
	 *  return session factory
	 *
	 *	session factory will be rebuilded in the next call
	 */
	public static void setConfigFile(String configFile) {
		HibernateSessionFactory.configFile = configFile;
		sessionFactory = null;
	}

	/**
	 *  return hibernate configuration
	 *
	 */
	public static Configuration getConfiguration() {
		return configuration;
	}

}
---------------------------------------------------------------------------------------

7、设计控制类
	从页面提取数据，然后调用HibernateSessionFactory通过Hibernate机制将数据插入到数据库中。
清单7：RegisterServlet.java
---------------------------------------------------------------------------------------
package register;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import org.hibernate.*;


public class RegisterServlet extends HttpServlet{
	
	private static final String CONTENT_TYPE = "text/html; charset=GBK";
	
	protected void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		response.setContentType(CONTENT_TYPE);
		
		//从页面得到数据值
		String username = request.getParameter("username");
		String password = request.getParameter("password");
		String sex = request.getParameter("sex");
		Integer age = new Integer(request.getParameter("age"));
		
		
		//将值传递给持久类->对应的是数据库里的表
		Register rg = new Register();
		rg.setUsername(username);
		rg.setPassword(password);
		rg.setSex(sex);
		rg.setAge(age);
		
		Session session = HibernateSessionFactory.getSession();
		Transaction tx = session.beginTransaction();
		
		try {
			session.save(rg);//保存，准备提交
			tx.commit();//提交到数据库
			session.close();
			response.sendRedirect("reply.jsp");
		} catch (Exception e) {
			e.printStackTrace();
			tx.rollback();//出现异常，将刚刚提交动作回转，rollback
		}
	}
	protected void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {	
		doGet(request, response);
	}
}
---------------------------------------------------------------------------------------

8、配置web.xml

清单8：web.xml
---------------------------------------------------------------------------------------
<?xml version="1.0" encoding="UTF-8"?>
<web-app version="2.4" 
	xmlns="http://java.sun.com/xml/ns/j2ee" 
	xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" 
	xsi:schemaLocation="http://java.sun.com/xml/ns/j2ee 
	http://java.sun.com/xml/ns/j2ee/web-app_2_4.xsd">
	
	<servlet>
		<servlet-name>RegisterServlet</servlet-name>
		<servlet-class>register.RegisterServlet</servlet-class>
	</servlet>	
	
	<servlet-mapping>
		<servlet-name>RegisterServlet</servlet-name>
		<url-pattern>/RegisterServlet</url-pattern>
	</servlet-mapping>
	
</web-app>
---------------------------------------------------------------------------------------

编译运行。






Hibernate查询
	public boolean verify(String loginId, String password) {
		// TODO Auto-generated method stub

		Session session = null;
		Users user = null;
		String sql = "from Users  where loginId='" + loginId
				+ "' and password='" + password + "'";
		
		try {
			session = HibernateSessionFactory.getSession();
		} catch (HibernateException e1) {
			e1.printStackTrace();
		}
		
		try {
			user = (Users) session.createQuery(sql).uniqueResult();//如果不能确定是唯一结果，那么此处有问题，因为它会返回以List
		} catch (HibernateException e) {
			e.printStackTrace();
		} finally {
			try {
				session.close();
			} catch (HibernateException e) {
				e.printStackTrace();
			}
		}

		if (null == user) {
			return false;
		}

		return true;
	}
	
	
	
Java和C++在链表构造上的区别

下面是java中一个链表定义：


class Link
{
	public int iData;
	public double dData;
	public Link next; 
}


初看上去似乎很迷惑，把一个类型为 Link 的数据成员放在一个定义也为 Link 类型的类中。
如何去理解呢？
编译器在不知道一个 Link 对象占用多大空间的情况下，
如何能知道一个包含了相同类型的 Link 对象占用多大空间？？？？

在Java中，答案是Link对象并没有真正包含另一个Link对象，尽管看起来好像确实包含了，
类型为Link的next字段仅仅是另一个Link对象的引用，而不是一个对象。
在一个给定的计算机系统中，一个引用不论指向谁，大小都一样。


假如在C++中定义同样的一个链表：
class Link
{
	public int iData;
	public double dData;
	public Link next; 
}
结果会是什么样子呢？





String a = new String("sasdg");



在Eclipse中配置python开发环境
1.下载python 安装包.python-2.4.2.msi.
2.安装pydev插件.
在Eclipse更新管理器中.地址:http://pydev.sf.net/updates/ .
或者下载zip包安装:http://sourceforge.net/projects/pydev/ .
3.配置插件Window->Preferences 在Pydev栏目下有个Interpreter-Python
在这里指定Python的解释器,也就是安装Python时,Python.exe的位置.
指定完以后,插件会自动导入一些包.完成以后就可以新建python工程了. 




Python开发环境：

下载eclipse下的插件pydev和Pydev extensions：http://pydev.sourceforge.net/，http://www.fabioz.com/pydev/

在 Windows 上, 安装 Python 有两种选择。

ActiveState 制作了一个 Windows 上的 Python 安装程序称为 ActivePython, 它包含了一个完整的 Python 发布; 一个适用于 Python 编程的 IDE 附加了一些 Python 的 Windows 扩展, 提供了全部的访问 Windows APIs 的服务, 以及 Windows 注册表的注册信息。

虽然 ActivePython 不是开源软件, 但它可以自由下载。 ActivePython 是我曾经学习 Python 时使用过的 IDE, 除非有别的原因, 我建议您使用它。可能的一个原因是：ActiveState 通常要在新的Python 版本出来几个月以后来更新它的安装程序。如果您就需要Python 的最新版本, 并且 ActivePython 仍然落后于最新版本的话, 您应该直接跳到在 Windows 上安装 Python 的第二种选项。 

第二种选择是使用由 Python 发布的 “官方” Python 安装程序。她是可自由下载的开源软件, 并且您总是可以获得当前 Python 的最新版本。

过程 1.1. 选项 1: 安装 ActivePython
下面描述 ActivePython 的安装过程:

从 http://www.activestate.com/Products/ActivePython/ 下载 ActivePython 。

如果您正在使用 Windows 95, Windows 98 或 Windows ME, 还需要在安装 ActivePython 之前下载并安装Windows Installer 2.0 。

双击安装程序 ActivePython-2.2.2-224-win32-ix86.msi。

按照安装程序的提示信息一步步地执行。

如果磁盘空间不足, 您可以执行一个定制安装, 不选文档, 但是笔者不建议您这样做, 除非您实在是挤不出14M空间来。 

在安装完后之后, 关闭安装程序, 打开 Start->Programs->ActiveState ActivePython 2.2->PythonWin IDE。 您将看到类似如下的信息:

PythonWin 2.2.2 (#37, Nov 26 2002, 10:24:37) [MSC 32 bit (Intel)] on win32.
Portions Copyright 1994-2001 Mark Hammond (mhammond@skippinet.com.au) -
see 'Help/About PythonWin' for further copyright information.
>>> 
过程 1.2. 选项 2: 安装来自 Python.org 的 Python 
从 http://www.python.org/ftp/python/选择最新的 Python Windows 安装程序, 下载 .exe 安装文件。

双击安装程序 Python-2.xxx.yyy.exe。 文件名依赖于您所下载的 Python 安装程序文件。

按照安装程序的提示信息一步步地执行。

如果磁盘空间不足, 可以取消 HTMLHelp 文件, 实用脚本 (Tools/), 和/或 测试套件 (Lib/test/)。

如果您没有机器的管理员权限, 您可以选择, Advanced Options, 然后选择 Non-Admin Install。 这只对登记注册表和开始菜单中创建的快捷方式有影响。

在安装完成之后, 关闭安装程序, 打开 Start->Programs->Python 2.3->IDLE (Python GUI)。 您将看到类似如下的信息:

Python 2.3.2 (#49, Oct  2 2003, 20:02:00) [MSC v.1200 32 bit (Intel)] on win32
Type "copyright", "credits" or "license()" for more information.

    ****************************************************************
    Personal firewall software may warn about the connection IDLE
    makes to its subprocess using this computer's internal loopback
    interface.  This connection is not visible on any external
    interface and no data is sent to or received from the Internet.
    ****************************************************************
    
IDLE 1.0
>>> 




频道:
normal Level Channel普通频道
	下面的是歌手
		歌手对应的专辑
			专辑对应的歌曲

2 Level Channel
	下面直接是歌曲
	
3 Level Channel
	下面是子频道
		子频道对应的歌曲
		
		
		
		
		
		
logic:iterate		
2007年08月17日 星期五 14:27
<logic:iterate>标记用于在页面中创建一个循环,以此来遍历如数组、Collection、Map这样的对象。该标记的功能强大，在Struts应用的页面中经常使用到。
1、对数组进行循环遍历
使用<logic:iterate>标记可以用于遍历数组，以下是一段示例代码：

<%
String[] testArray={"str1","str2","str3"}; 
pageContext.setAttribute("test",testArray); 
%>
<logic:iterate id="show" name="test"> 
<bean:write name="show"/> 
</logic:iterate>
在上面的代码中，首先定义了一个字符串数组，并为其初始化。接着，将该数组存入pageContext对象中，命名为test1。然后使用<logic:iterate>标记的name属性指定了该数组，并使用id来引用它，同时使用<bean:write>标记来将其显示出来。其结果为：
str1 
str2 
str3 

另外，还可以通过length属性来指定输出元素的个数。如下面的代码：
<logic:iterate id="show" name="test" length="2" offset="1"> 
<bean:write name="show"/> 
</logic:iterate>

其中length属性指定了输出元素的个数，offset属性指定了从第几个元素开始输出，如此处为1，则表示从第二个元素开始输出。所以该代码的运行结果应当输出：
str2
str3

另外，该标记还有一个indexId属性，它指定一个变量存放当前集合中正被访问的元素的序号，如：


<logic:iterate id="show" name="test" length="2" offset="1" indexId="number"> 
<bean:write name="number"/>:<bean:write name="show"/> 
</logic:iterate>
其显示结果为：
1:str2 
2:str3 



2、对HashMap进行循环遍历

<%
HashMap countries=new HashMap();
countries.put("country1","中国");
countries.put("country2","美国");
countries.put("country3","英国");
countries.put("country4","法国");
countries.put("country5","德国");
pageContext.setAttribute("countries",countries); 
%>
<logic:iterate id="country" name="countries"> 
<bean:write name="country" property="key"/>:
<bean:write name="country" property="value"/> 
</logic:iterate>

在bean:write中通过property的key和value分别获得HaspMap对象的键和值。其显示结果为：
country5:德国 
country3:英国 
country2:美国 
country4:法国 
country1:中国 
由结果可看出，它并未按添加的顺序将其显示出来。这是因为HaspMap是无序存放的。

3、嵌套遍历

<%
String[] colors={"red","green","blue"};
String[] countries1={"中国","美国","法国"};
String[] persons={"乔丹","布什","克林顿"};
ArrayList list2=new ArrayList();
list2.add(colors);
list2.add(countries1);
list2.add(persons);
pageContext.setAttribute("list2",list2);
%>


<logic:iterate id="first" name="list2" indexId="numberfirst">
<bean:write name="numberfirst"/>
<logic:iterate id="second" name="first">
<bean:write name="second"/>
</logic:iterate>
<br>
</logic:iterate>


上一层的ID为下一层的name


运行效果：
0 red green blue 
1 中国 美国 法国 
2 乔丹 布什 克林顿
<logic:iterate id="it" name="list" length="2"> 
<bean write name="it"/><br/> 
</logic:iterate> 

list 是你要遍例的对象 it是list里面的元素的类型 ,还有个offset属性，是用来表示起始位置的，比如，offset＝“1”从第二位开始遍历出值，offset＝“0”是默认值 
 
 
		
		
		
		<tr class="tableListTr2">
			<td width="20%" align="center"><bean:message
				key="com.accessmedia.music.oldcatalog.Catalogversions.totalSongRecords" />
			</td>
			<td width="80%" align="left"><bean:write name="totalSongsCount" /></td>
		</tr>		
		
		
		
normal				
select count(*) from catalogviewsongs where catalogviewId = 1

zongshu
select count(*) from catalogsongs where catalogversionId = 1		





		Integer count = null;
		int count = 0;
		Session session = HibernateSession.currentSession();
		String sql = "select count(*) from catalogviewsongs where catalogviewId = " + catalogViewId;
		count = new Integer((String) session.createQuery(sql).uniqueResult());
		count = ((Integer) session.createQuery(sql).uniqueResult()).intValue();
		session.close();
		Session session = HibernateSession.currentSession();
		String sql = "select count(*) from catalogviewsongs where catalogviewId = " + catalogVersionId;
		count = new Integer(((Integer) session.createQuery(sql).uniqueResult()).intValue());
		session.close();
		return count;
		
		
		
		catalogView.songCount
		catalogView.songCount
		
		
		<bean:write name="totalSongsCount"/>
		<bean:write name="catalogVersion" property="songCount" />
		
Add a field named "songCount". By WeiZili	



	//get total song count @ weizili
	public int getSongCountFromCatalogSongsByCatalogVersionId(int catalogVersionId) throws HibernateException {
		int count = 0;
		Session session = HibernateSession.currentSession();
//		String sql = "select count(*) from CatalogSong where catalogVersionId = " + catalogVersionId;
		String hql = "select count(*) from CatalogViewSong cv1 where cv1.catalogViewId in " +
				"( select cv2.catalogViewId  from CatalogView cv2 where cv2.catalogVersionId = :catalogVersionId) ";
		Query query = session.createQuery(hql);
		query.setInteger("catalogVersionId", catalogVersionId);
		count = ((Integer) query.uniqueResult()).intValue();
		return count;
	}
	
	//get normal song count @weizili
	public int getChannelSongCountByCatalogViewId( int catalogViewId ) throws HibernateException	{
		int count = 0;
		Session session = HibernateSession.currentSession();
		String sql = "select count(*) from CatalogViewSong where catalogViewId = " + catalogViewId;
		count = ((Integer) session.createQuery(sql).uniqueResult()).intValue();
		return count;
	}	
	
	


修改页面：发布管理->目录管理->浏览旧版本->浏览发布内容	
该页面上对歌曲数进行统计，在各个Channel上进行统计，同时也给出了该版本里的总的歌曲数



Hibernate里的SQL语句里的表名要与持久化类的类名一致，即与配置文件里的一致，
这样就很可能会与数据库里的表名不一致
