JSP	ѧϰ

Tomcat JSP����ʵ���ּ�


������Tomcat���������JSP�Ŀ�����������ʼ���˺ܶ���·��
����ͨ���ҵĲ�иŬ�����ڽ���ˡ�
���潫�ҵľ����������¡�

һ��������������
����
������һ��������j2sdk��tomcat��
��sun�ٷ�վ��http://java.sun.com/j2se/1.5.0/download.jsp������j2sdk��
ע�����ذ汾ΪWindows Offline Installation��SDK��ͬʱ�������J2SE Documentation��
Ȼ��tomcat�ٷ�վ�㣨http://jakarta.apache.org/site/downloads/downloads_tomcat-5.cgi������tomcat��
���������ص���jdk-1_5_0_08-windows-i586-p.exe��apache-tomcat-5.5.20.exe

�����ڶ�������װ���������j2sdk��tomcat��
ִ��j2sdk��tomcat�İ�װ����Ȼ��Ĭ�����ý��а�װ���ɡ�
����
����1.��װj2sdk�Ժ���Ҫ����һ�»������������ҵĵ���-������-���߼�-����������-��ϵͳ������������»�������(�ٶ����j2sdk��װ��C:\Program Files\Java\jdk1.5.0_08����
����
JAVA_HOME=C:\Program Files\Java\jdk1.5.0_08
CLASSPATH=.;%JAVA_HOME%\lib;%JAVA_HOME%\lib\dt.jar;%JAVA_HOME%\lib\tools.jar;��.;һ�������٣���Ϊ������ǰ·��)
PATH����������:�ڵ�ǰ��PATH�����ĺ����������������:
;%JAVA_HOME%\bin (ע�ⲻҪ��ԭ��������ɾ����)

�������ſ���дһ���򵥵�java����������J2SDK�Ƿ��Ѱ�װ�ɹ���
����
public class Hello
{
	public static void main(String[] args)
	{
		System.out.println( "Hello world! My Java!" );
	}

}
����
�������������γ��򱣴�Ϊ�ļ���Ϊ Hello.java ���ļ���
����
����Ȼ���������ʾ�����ڣ�cd�����Test.java����Ŀ¼��Ȼ��������������
����
javac Hello.java
java Hello
��
������ʱ���������ӡ���� Hello world! My Java! �Ļ�˵����װ�ɹ��ˣ����û�д�ӡ����仰������Ҫ��ϸ���һ��������������
����
����2.��װTomcat
һ��������װһ����,�����Ұ�װ��C:\Program Files\tomcat5.5
��������������
����"�ҵĵ���->����->�߼�->��������(N)->�½�"
������Ϊ��TOMCAT_HOME������ֵΪ C:\Program Files\tomcat5.5
����
����Ȼ���޸Ļ��������е�CLASSPATH����tomat��װĿ¼�µ� common\lib �µ�(���Ը���ʵ��׷��)servlet.jar׷�ӵ�CLASSPATH��ȥ���޸ĺ��CLASSPATH���£�
����
.;%JAVA_HOME%\lib;%JAVA_HOME%\lib\dt.jar;%JAVA_HOME%\lib\tools.jar;%TOMCAT_HOME%\common\lib\servlet.jar;
����
�������ſ�������tomcat������Tomcat,C:\Program Files\tomcat5.5\bin\tomcat5.exe
֮�����������������룺http://localhost:8080 �Ϳ��Կ���Tomcat��ȱʡҳ����.
��д��һ��JSP����

<%@ page contentType="text/html;charset=gb2312"%>
<%@ page language="java"%>
<html>
<title>��һ��JSP����</title>
<body>
<%out.println("Hello world!");%>
</body>
</html>

���䱣�浽C:\Program Files\tomcat5.5\webapps\ROOT\hello.jsp

Ȼ��������������� http://localhost:8080/hello.jsp �Ϳ��Ե�һ����ҳ��
����ҳ�������
Hello world��

������еĻ�,���Գ���:http://127.0.0.1:8080/hello.jsp,
����Ӧ�þͿ�����.

�����ٸ�һ����ʾ��ǰϵͳʱ������ӣ�

<%@ page contentType="text/html;charset=gb2312"%>
<%@ page language="java"%>
<html>
<title>��ǰϵͳʱ��</title>
<body>
<h3>Today is:
<%= new java.util.Date() %>
</body>
</html>

�ܽ�:
��������ϸ�ļ�¼���ҵ���ȷ���ù���.
��;��ȻҲ���ֺܶ಻�������顣
�������û���������CLASSPATH��һ��Ҫ������ȷ��
JSP����ҲҪд�ԣ���ʹ����򵥵����hello.jsp������ҲҲ���˺ü��Σ�
����<%@ page language="java"%>Ҫ�ŵ�����ʼ��
<%@ page contentType="text/html;charset=gb2312"%>
���ҲҪ����ϣ���Ȼ��������롣
���о��ǳ�������Ӣ���ַ�����Ҳ�����Ī����������⡣
�õģ�ף��JSP֮��һ����˳��



ʲô��Tomcat��
Tomcat��һ������Դ���롢����servlet��JSP WebӦ������Ļ���Java��WebӦ�����������Tomcat��Apache-Jakarta����Ŀ֧�ֲ������Կ�����Դ����Java������־Ը�߽���ά����Tomcat Server�Ǹ���servlet��JSP�淶����ִ�еģ�������ǾͿ���˵Tomcat ServerҲʵ����Apache-Jakarta�淶�ұȾ��������ҵӦ�����������Ҫ�á�

��װTomcat 5
Ҫ��ʼʹ��Tomcat 5��������Ҫ����Java Development Kit (JDK) 1.4���Tomcat 5��װ�������Ƿֱ���ZIP�ļ���Windows��װ���ݰ���һ���㰲װ�����������ݰ�������������������������JAVA_HOME��TOMCAT_HOME��JDK����װ��JAVA_HOMEĿ¼֮�У���Tomcat 5�򽫰�װ��TOMCAT_HOMEĿ¼֮�С�


Eclipse3.2�� Java Web ���������Ĵ֮LOMBOZ+TOMCAT ��װ

Tomcat��װ
���apache-tomcat-5.0.28��װ�ļ�����װ����ͬһ��������װ���ơ��������Ҳ���ϵͳĬ�ϵİ�װ·������C:\Program Files\Apache Software Foundation\Tomcat 5.0 Ŀ¼�¡�

Tomcat�İ�װ������ͨ��װ�ķ�ʽ��
��ѹtomcatPluginV3.zipȻ����ͷų�����com.sysdeo.eclipse.tomcat_3.0.0�ļ��и��Ƶ�eclipse��pluginsĿ¼�£����������װ��ϡ�



Lomboz�İ�װ��

After installing Eclipse (but before unzipping the Lomboz plugin), be sure to start up

Eclipse
to complete the installation process.
��װLomboz���֮ǰ����װEclipse��һ��Ҫȷ������һ��Eclipse���������Eclipse�İ�װ��

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

Lomboz��ҪEclipse��EMF��Ŀ����������Lomboz֮ǰҪװ��EMF runtime��



Eclipse3.2.1+MyEclipse5.0GA+Tomcat5.5����JSP�����������

By zieckey (zieckey@yahoo.com.cn)
All Rights Reserved!

	��һ����׼���������ߣ�
	JDK��jdk-6-windows-i586.exe
	Tomcat��apache-tomcat-5.5.20.exe
	MyEclipse��EnterpriseWorkbenchInstaller_5.0GA_E3.2.exe

�����ڶ�������װ���������j2sdk��tomcat��
ִ��j2sdk��tomcat�İ�װ����Ȼ��Ĭ�����ý��а�װ���ɡ�
����
����1.��װj2sdk�Ժ���Ҫ����һ�»������������ҵĵ���-������-���߼�-����������-��ϵͳ������������»�������(�ٶ����j2sdk��װ��M:\Java\jdk1.6.0����
����
JAVA_HOME=M:\Java\jdk1.6.0
CLASSPATH=.;%JAVA_HOME%\lib;%JAVA_HOME%\lib\dt.jar;%JAVA_HOME%\lib\tools.jar;��.;һ�������٣���Ϊ������ǰ·��)
PATH����������:�ڵ�ǰ��PATH�����ĺ����������������:
;%JAVA_HOME%\bin (ע�ⲻҪ��ԭ��������ɾ����)

�������ſ���дһ���򵥵�java����������J2SDK�Ƿ��Ѱ�װ�ɹ���
����
public class Hello
{
 public static void main(String[] args)
 {
  System.out.println( "Hello world! My Java!" );
 }

}
����
�������������γ��򱣴�Ϊ�ļ���Ϊ Hello.java ���ļ���
����
����Ȼ���������ʾ�����ڣ�cd�����Test.java����Ŀ¼��Ȼ��������������
����
javac Hello.java
java Hello
��
������ʱ���������ӡ���� Hello world! My Java! �Ļ�˵����װ�ɹ��ˣ����û�д�ӡ����仰������Ҫ��ϸ���һ��������������
����
����2.��װTomcat
һ��������װһ����,�����Ұ�װ��M:\Tomcat5.5
��������������
����"�ҵĵ���->����->�߼�->��������(N)->�½�"
������Ϊ��TOMCAT_HOME������ֵΪ M:\Tomcat5.5
����
����Ȼ���޸Ļ��������е�CLASSPATH����tomat��װĿ¼�µ� common\lib �µ�(���Ը���ʵ��׷��)servlet.jar׷�ӵ�CLASSPATH��ȥ���޸ĺ��CLASSPATH���£�
����
.;%JAVA_HOME%\lib;%JAVA_HOME%\lib\dt.jar;%JAVA_HOME%\lib\tools.jar;%TOMCAT_HOME%\common\lib\servlet.jar;
����
�������ſ�������tomcat������Tomcat,M:\Tomcat5.5\bin\tomcat5.exe
֮�����������������룺http://localhost:8080 �Ϳ��Կ���Tomcat��ȱʡҳ����.
��д��һ��JSP����

<%@ page contentType="text/html;charset=gb2312"%>
<%@ page language="java"%>
<html>
<title>��һ��JSP����</title>
<body>
<%out.println("Hello world!");%>
</body>
</html>

���䱣�浽M:\Tomcat5.5\webapps\ROOT\hello.jsp

Ȼ��������������� http://localhost:8080/hello.jsp �Ϳ��Ե�һ����ҳ��
����ҳ�������
Hello world��

������еĻ�,���Գ���:http://127.0.0.1:8080/hello.jsp,
����Ӧ�þͿ�����.

	�ڶ�������װ������MyEclipse

��װ���̺ܼ򵥣���������˵��һ�����ã�
��Eclipse������������һ�����Ի�������ͼ��(���·�������һ����ɫ�ļ�ͷ),
�����,�ᷢ�ֳ���"No Enable Servers available-Select to View MyEclipse preferences"
�����˵����MyEclipse��û�п������õ�Web������,
�ո�����װ��Tomcat5.5,������ÿ��Ա��õ��˴�.
�������"No Enable Servers available-Select to View MyEclipse preferences",
�ڵ������ĶԻ�����һ��ѡ��:
MyEclipse->Application Servers->Tomcat5
ѡ���ұߵ�Enable������Tomcat,���⻹Ҫѡ��Tomcat��home·��:M:\Tomcat5.5
ѡ��ú�,�ڵ��MyEclipse->Application Servers->Tomcat5->JDK
���ұ�ѡ��Add...��ť,ѡ����ȷ��JDK(ע��:����JRE).
��һ�����ú�,�Ϳ��Ա�дJSP������.
File->New->Project...->Web Project
(File->New->Project...->MyEclipse->J2EE Projects->Web Project)
���빤����,���������:HelloJSP
Ȼ�����ұߵ�HelloJSP->WebRoot���Ҽ����,Ȼ��ѡ��JSP�½�һ��JSP�ļ���
����Ͳ���EclipseΪ�������ɵ�Ĭ�ϵ�MyJsp.jsp�ļ�����
���Ҫ������������̲���һ��Server�������ϣ�
�����Ҽ�ѡ��HelloJSP->MyEclipse->Add and Remove Project Deployments
���Add��ť����Server��ѡ��Tomcat5��Finish��OK

����ֱ�Ӵ�Eclipse����������Tomcat��
������������룺http://127.0.0.1:8080/HelloJSP/MyJsp.jsp
���鿴�ո��Ǹ�MyJsp.jsp������ҳ�����
This is my JSP page.

�������ǵ�JSP�������������ͽ��������ˡ�


2007/1/17
JSP���ų����̳�֮JSPָ��

http://www.webjx.com  �������ڣ�2005-03-04 10:33  ��������ҳ��ѧ��  ���ߣ�



��JSP directive mso-hansi-font-family:""��Ӱ��servlet �������ṹ��������������ʽ��

��%@ directive attribute=��value��%��
����
�������ң������Խ��������д��һ������У�

������%@ directive attribute1="value1" attribute2="value2" attributeN="valueN" %��

������������Ҫ��directive:

����page,��������һЩ����import classes���£�����servlet�ĳ��ࣨSuperclass����
mso-hansi-font-family:""���ȣ�

����include,���������ļ�����servlet���У���JSP�ļ�����Ϊservletʱ����

����һ��JSP page Directive

�����﷨��

��%@ page
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

%��

����Page directive mso-hansi-font-family:""������������һЩ���ִ�Сд�����ԣ�

����(1)import = ��package.class���� import = ��package.class1,..,package.classN����
mso-hansi-font-family:""��

���������Զ���Ҫimport��packages�����磺

��%@ page import="java.util.*" %��

����import�������⼸��������Ψһһ��������һ��JSP�г��ֶ�εġ�

����(2)contenType = ��MIME=Type�� ��contentType=��MIME-Type;charset=Character-Set��mso-hansi-font-family:""��

������ָ�������MIME���͡�ȱʡΪ��text/html��������:

��%@ page contentType="text/plain" %��"

������scriptlet�еȼ��ڣ�

��% response.setContentType("text/plain"); %��

����(3)isThreadSafe = ��true | false��.���ֵΪ��true����ȱʡ����ʾ����������ͨ��servlet����������󽫱�һ��servletʵ�����д�������������£������Աͬ�����ʶ��ʵ��������ֵΪ��false��ʱ��ʾ��servlet��ʵ�ֵ��߳�ģʽ��SingleThreadModel��,����������˳���ύ���ǲ������֣������ṩ��ͬ�ķ����servletʵ����

������4��session=��true | false���� ���ֵΪ��true����ȱʡ����ʾ��Ԥ�������session���̳�HttpSession��Ӧ�ð󶨵�һ���Ѵ��ڵ�session�������Ӧ�ô���һ������֮�󶨡�ֵΪ��false��ʱ��ʾ������ʹ��session�����������ͼʹ�ã�����JSP��servletת��ʱ���ִ���

������5��buffer = ��sizekb | none����ΪJspWriter���ȷ������Ĵ�С��ȱʡ�ɷ�����������������Ҫ��8kb��

������6��autoflush=��true | false���� ���ֵΪ��true mso-hansi-font-family:""������ȱʡ����ʾ����������ʱ���Զ���գ�ֵΪ��false mso-hansi-font-family:""����ʱ��ʾ����������ʱ�ݳ�һ���쳣�������ʹ�á���buffer=��none��������false mso-hansi-font-family:""��ֵ�ǲ��Ϸ��ġ�

����(7)extends=��package.class�����⽫Ϊservlet����һ�����ࡣ���ر������ʹ����һ���ܣ���Ϊ��������Ҳ���Ѿ�������һ����

����(8)info = ��message��������һ������ͨ������getServletInfo�����õ��Ĵ���

����(9)errorPage = ��URL����ָ��һ��JSP mso-hansi-font-family:""��ҳ���������κ�һ�����׳��ĵ���ǰҳ�沢δ������������

����(10)isErrorPage = ��true | false����ָ����ǰҳ���Ƿ���Դ���������һ��ҳ��Ĵ���ȱʡΪ��false����

����(11)language = ��java�� mso-hansi-font-family:""����ָ�����½�ʹ�õ����ԡ�����������Ϊ��һ���Է��ģ���Ϊ����java mso-hansi-font-family:""��������ȱʡ����Ψһ�Ϸ���ѡ��

������JSP include Directive ����directive ʹ��������JSPת��Ϊservletʱ��һ���ļ������������﷨��

��jsp:include page="{relativeURL | ��%= expression %��}" flush="true" /��mso-hansi-font-family:";mso-font-kerning: 0pt"����
��jsp:include page="{relativeURL | ��%= expression %��}" flush="true" ��
��jsp:param name="parameterName"
value="{parameterValue | ��%=expression %��}" /��+
��/jsp:include��

����URL mso-hansi-font-family:""��ͨ�������ָ������JSPҳ�棬���ǣ��ձ�ʹ����ԡ�URL����������ʹ��һ��б�ܡ�/����ΪURL�Ŀ�ʼ����֪ϵͳURL mso-hansi-font-family:""����Ե�Web server����·�������������ļ����Թ����JSP��ʽ����������ˣ�������������ʹ�þ�̬HTML,scripting elements,directives,�� actions��

��������������һ�����ӣ����վ����ÿһ��ҳ���ϰ���һ��С�͵ĵ���������ͨ��������ҳ��Ķ��������Ҳ࣬��������ÿһ��ҳ�������include directive ��ʵ���Ǻ���Ȼ�ģ����ù����HTML mso-hansi-font-family:""��������Щ��俽��ÿһ��ҳ�������Ǹ����ʡ��뿴���д��룺

��HTML��
��HEAD��
��TITLE�� JSP�̳̣�/TITLE��
��/HEAD��
��BODY��
��%@ include file="/navbar.html" %��
��!�� ��ҳ�����������... --��
��/BODY��
��/HTML��

������Ϊ�ļ�����ҳ�汻ת��ʱ����ģ���ˣ�����������ı��ˣ�����Ҫ������ָ������JSP mso-hansi-font-family:""��ҳ��ȫ�����±���һ�Ρ�������ĵ������������ı������������Ǹ�Ч�ģ����ǣ�������ı������ļ�����Ƶ����������ʹ��jsp:include action�����潫̸���������������ҳ�汻����ʱ�Ű����ļ���


��װMySQL
Enable TCP/IP Networking
	port 3306
����MySQL
	����MySQL Server

	M:\Documents and Settings\apple>mysqld-nt --help
mysqld-nt  Ver 5.0.22-community-nt for Win32 on ia32 (MySQL Community Edition (G
PL))
Copyright (C) 2000 MySQL AB, by Monty and others
This software comes with ABSOLUTELY NO WARRANTY. This is free software,
and you are welcome to modify and redistribute it under the GPL license

Starts the MySQL database server

Usage: mysqld-nt [OPTIONS]

For more help options (several pages), use mysqld --verbose --help

	������Կ���mysqld-nt.exe��MySQL database server
���������пͻ��˽�������:
һ������MYSQL��
��ʽ�� mysql -h������ַ -u�û��� ��p�û�����
1����1�����ӵ������ϵ�MYSQL��
   �����ڴ�DOS���ڣ�Ȼ�����Ŀ¼ mysqlbin���ټ�������mysql -uroot -p���س�����ʾ�������룬����հ�װ��MYSQL�������û�root��û������ģ���ֱ�ӻس����ɽ��뵽MYSQL���ˣ�MYSQL����ʾ���ǣ�mysql>

   	M:\Documents and Settings\apple>mysql -uroot -p
	Enter password:
	Welcome to the MySQL monitor.  Commands end with ; or \g.
	Your MySQL connection id is 1 to server version: 5.0.22-community-nt

	Type 'help;' or '\h' for help. Type '\c' to clear the buffer.

	mysql>

2����2�����ӵ�Զ�������ϵ�MYSQL������Զ��������IPΪ��110.110.110.110���û���Ϊroot,����Ϊabcd123��������������
  mysql -h110.110.110.110 -uroot -pabcd123
  ��ע:u��root���Բ��üӿո�����Ҳһ����

3���˳�MYSQL��� exit ���س���
mysql> exit
Bye

M:\Documents and Settings\apple>

�����޸����롣
��ʽ��mysqladmin -u�û��� -p������  password ������
1����1����root�Ӹ�����ab12��������DOS�½���Ŀ¼mysqlbin��Ȼ�������������
   mysqladmin -uroot -password ab12
  ע����Ϊ��ʼʱrootû�����룬����-p������һ��Ϳ���ʡ���ˡ�
2����2���ٽ�root�������Ϊdjg345��
   	mysqladmin -uroot -pab12 password djg345

	M:\Documents and Settings\apple>mysqladmin -uroot password ab12

	M:\Documents and Settings\apple>mysqladmin -uroot -pab12 password djg345

	M:\Documents and Settings\apple>mysql -uroot -p
	Enter password: ******
	Welcome to the MySQL monitor.  Commands end with ; or \g.
	Your MySQL connection id is 6 to server version: 5.0.22-community-nt

	Type 'help;' or '\h' for help. Type '\c' to clear the buffer.

	mysql>

�����������û�����ע�⣺�����治ͬ���������Ϊ��MYSQL�����е�������Ժ��涼��һ���ֺ���Ϊ�����������
��ʽ��grant select on ���ݿ�.* to �û���@��¼���� identified by "����"
��1������һ���û�test1����Ϊabc�������������κ������ϵ�¼�������������ݿ��в�ѯ�����롢�޸ġ�ɾ����Ȩ�ޡ���������root�û�����MYSQL��Ȼ������������
  grant select,insert,update,delete on *.* to test1@"%" Identified by "abc";
����1���ӵ��û���ʮ��Σ�յģ�������ĳ����֪��test1�����룬��ô���Ϳ�����internet�ϵ��κ�һ̨�����ϵ�¼���mysql���ݿⲢ��������ݿ���Ϊ����Ϊ�ˣ�����취����2��
��2������һ���û�test2����Ϊabc,����ֻ������localhost�ϵ�¼�������Զ����ݿ�mydb���в�ѯ�����롢�޸ġ�ɾ���Ĳ�����localhostָ������������MYSQL���ݿ����ڵ���̨�������������û���ʹ��֪��test2�����룬��Ҳ�޷���internet��ֱ�ӷ������ݿ⣬ֻ��ͨ��MYSQL�����ϵ�webҳ�������ˡ�
  grant select,insert,update,delete on mydb.* to test2@localhost identified by "abc";
  ����㲻��test2�����룬�����ٴ�һ���������������
  grant select,insert,update,delete on mydb.* to test2@localhost identified by "";

����һ��LearnJSP���ݿ�:
M:\Documents and Settings\apple>mysql -uroot -p
Enter password: ******
Welcome to the MySQL monitor.  Commands end with ; or \g.
Your MySQL connection id is 6 to server version: 5.0.22-community-nt

Type 'help;' or '\h' for help. Type '\c' to clear the buffer.

mysql> create database LearnJSP;
Query OK, 1 row affected (0.02 sec)

����UserInfo���:
mysql> use LearnJSP;
Database changed
mysql> create table UserInfo(
    -> UserName varchar (20) not null,
    -> UserPwd varchar (20) not null
    -> );
Query OK, 0 rows affected (0.06 sec)

mysql>
����һ������:
mysql> insert into UserInfo values ('zieckey','123456');
Query OK, 1 row affected (0.03 sec)

mysql>



�趨 ClassPath

   �����ص�JDBC������ѹ���ļ�����mysql-connector-java-3.1.12-bin.jarmysql-connector-java-3.1.12-bin-g.jar����jar�ļ��������ǿ�����JDK��libĿ¼�£����������ClassPath�С����磬�ҵ��������ģ�ԭ����Ϊ.;%JAVA_HOME%\lib;%JAVA_HOME%\lib\tools.jar;Ȼ���������jar��·��.;%JAVA_HOME%\lib;%JAVA_HOME%\lib\tools.jar;C:\j2sdk1.4.2\lib\mysql-connector-java-3.1.12-bin.jar;C:\j2sdk1.4.2\lib\mysql-connector-java-3.1.12-bin-g.jar

����׼�������������ˣ��������ҵĲ��Գ���������Eclipse�н�����ͨjava Projectʱ�����ǿ����ڽ���ʱ����ⲿJARS��ѡ����\lib�µ�����jar�Ϳ����ˡ����Project�ǽ����õĵĻ�����ͨ��Java Build Pathѡ������Libraries������ⲿJARs���ɡ�������һ���ܼ򵥵ĵ�¼���ڲ��Գ���





JSPʹ��MySQL���ݿ�:�Ӱ�װ�����õ�ʵ�ʳ���������

                   By zieckey(http://zieckey.cublog.cn)
                          All Rights Reserved!

���������� JSP+Tomcat �����������Ѿ������
(��ϸ���ü�:http://blog.chinaunix.net/u/16292/showart_227534.html)

һ��׼��������

����MySQL��mysql-5.0.27-win32.zip
����MySQL��JDBC jar����mysql-connector-java-5.0.3-bin.jar

������װ�Ͳ���MySQL
 MySQL��Windows�µİ�װ�ܼ򵥣�ע����ѡ�����õ���һ���ǽ�MySQL�����õ���ϵͳ���������У�
Ϊ�˺���ķ������ѡ��Ҫѡ�
 ��װ�����������£�
1. ����MySQL Server
M:\Documents and Settings\apple>mysqld-nt --help
mysqld-nt  Ver 5.0.22-community-nt for Win32 on ia32 (MySQL Community Edition (G
PL))
Copyright (C) 2000 MySQL AB, by Monty and others
This software comes with ABSOLUTELY NO WARRANTY. This is free software,
and you are welcome to modify and redistribute it under the GPL license
Starts the MySQL database server
Usage: mysqld-nt [OPTIONS]
For more help options (several pages), use mysqld --verbose --help
 ������Կ���mysqld-nt.exe��MySQL database server
���������пͻ��˽�������:
�������˵ϵͳû�����mysqld-nt�����ô�ܿ�����MySQL��������Ϣû�е���ϵͳ���������С����ʱ����Խ�MySQL�İ�װĿ¼��binĿ¼���뵽ϵͳPATH���������У����磺
M:\WINDOWS\system32;M:\WINDOWS;M:\WINDOWS\System32\Wbem;M:\Program Files\MySQL\MySQL Server 5.0\bin
������ mysqld-nt Ӧ�þ�û�������ˡ�
M:\Documents and Settings\apple>mysqld-nt
2.����MYSQL��
��ʽ�� mysql -h������ַ -u�û��� ��p�û�����
��1�����ӵ������ϵ�MYSQL��
   �����ڴ�DOS���ڣ�Ȼ�����Ŀ¼ mysqlbin���ټ�������mysql -uroot -p���س�����ʾ�������룬����հ�װ��MYSQL�������û�root��û������ģ���ֱ�ӻس����ɽ��뵽MYSQL���ˣ�MYSQL����ʾ���ǣ�mysql>
    M:\Documents and Settings\apple>mysql -uroot -p
 Enter password:
 Welcome to the MySQL monitor.  Commands end with ; or \g.
 Your MySQL connection id is 1 to server version: 5.0.22-community-nt
 Type 'help;' or '\h' for help. Type '\c' to clear the buffer.
 mysql>
��2�����ӵ�Զ�������ϵ�MYSQL������Զ��������IPΪ��110.110.110.110���û���Ϊroot,����Ϊabcd123��������������
  mysql -h110.110.110.110 -uroot -pabcd123
  ��ע:u��root���Բ��üӿո�����Ҳһ����
3���˳�MYSQL��� exit ���س���
mysql> exit
Bye
M:\Documents and Settings\apple>

������Java��ʹ��MySQL���ݿ�

1. ׼���ݿ��ļ�
����һ��LearnJava���ݿ�:
M:\Documents and Settings\apple>mysql -uroot -p
Enter password: ******
Welcome to the MySQL monitor.  Commands end with ; or \g.
Your MySQL connection id is 6 to server version: 5.0.22-community-nt
Type 'help;' or '\h' for help. Type '\c' to clear the buffer.
mysql> create database LearnJava;
Query OK, 1 row affected (0.02 sec)
����UserInfo���:
mysql> use LearnJava;
Database changed
mysql> create table UserInfo(
    -> UserName varchar (20) not null,
    -> UserPwd varchar (20) not null
    -> );
Query OK, 0 rows affected (0.06 sec)
mysql>
����һ������:
mysql> insert into UserInfo values ('zieckey','123456');
Query OK, 1 row affected (0.03 sec)
mysql>

2. ��MySQL��JDBC jar������ϵͳ������
�������ǽ�mysql-connector-java-5.0.3-bin.jar����java�İ�װĿ¼�£�
Ȼ���뵽CLASSPATH���������У����磺
.;%JAVA_HOME%\lib\tools.jar;%JAVA_HOME%\lib\mysql-connector-java-5.0.3-bin.jar;%JAVA_HOME%\lib\dt.jar;

3. �½� Java ���� zieckey.jsp

<%@ page contentType="text/html;charset=gb2312"%>
<%@ page language="java"%>
<%@ page import="java.sql.*"%>

<html>
<body>
	<%
		Class.forName("org.gjt.mm.mysql.Driver").newInstance();
		//���Ӳ�����Access��ͬ
		String url = "jdbc:mysql://localhost/LearnJava";
		//��������
		Connection con = DriverManager.getConnection ( url, "root", "123456" );

		Statement stmt = con.createStatement ( );
		//���ز�ѯ���
		ResultSet rs = stmt.executeQuery ( "select * from userinfo" );

		while(rs.next()) {%>
			���ݿ⡰userinfo�������ֶ�1: <%=rs.getString(1)%><br />
			���ݿ⡰userinfo�������ֶ�2: <%=rs.getString(2)%><br />
		<%}%>
	<%out.print("���ݿ�����ɹ�����ϲ��");%><br />

	<%
		//�ر���ز���
		rs.close();
		stmt.close();
		con.close();
	%>
</body>
</html>

���䱣�浽 %TOMCAT%\webapps\ROOT\zieckey.jsp
Ȼ��������������� http://localhost:8080/zieckey.jsp �Ϳ��Ե�һ����ҳ��
����ҳ�������

���ݿ⡰userinfo�������ֶ�1: zieckey
���ݿ⡰userinfo�������ֶ�2: 123456
���ݿ�����ɹ�����ϲ��

�ܽ�:
��������֪����JSP+tomcat+mysql+JDBCʵ���˼򵥵���վ���ݿ����,
����Ĺ�����˳������.
ף���JSP֮��һ·˳��!


һ���򵥵ĵ�½��ҳ���:

ǰ̨login.html�ͺ�̨verifylogin.jsp����ҳ�����:
login.html����:

<html>
  <head>
    <title>��¼</title>

    <meta http-equiv="content-type" content="text/html; charset=UTF-8">
    <meta http-equiv="Content-Language" content="ch-cn">
  </head>

  <body>
  <!-- Form ������ȡ�û����벢�ύ����Ϣ-->
  <form method="post" name="frmLogin" action="verifylogin.jsp">
  <h1 align="center">�û���¼</h1><br>
  <div align="center">�û�����
  		<input type="text" name="txtUserName" value="Your name"
  			onfocus="if(this.value=='Your name')this.value='';"><br>���룺
  		<input type="password" name="txtPassword" value="Your password"
  			onfocus="if(this.value=='Your password')this.value='';"><br>
  		<input type="submit" name="Submit"��value="�ύ"> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
  		<input type="reset" name="Reset" value="����"><br>
  </div></form></body>
</html>

verifylogin.jsp����:
<%@ page language="java" contentType="text/html;charset=gb2312"
	pageEncoding="UTF-8"%>

<%@ page import="java.sql.*"%>
<%@ page import="java.util.*"%>


<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
	<head>
		<title>��¼</title>

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
			//��ȡ�û���
			String sUserName = request.getParameter ( "txtUserName" );
			//��ȡ����
			String sPasswd = request.getParameter ( "txtPassword" );

			//�Ǽ�JDBC��������
			Class.forName ( "org.gjt.mm.mysql.Driver" ).newInstance ( );
			//���Ӳ�����Access��ͬ
			String url = "jdbc:mysql://localhost/LearnJSP";
			//��������
			Connection connection = DriverManager.getConnection ( url, "root",
					"011124" );
			//SQL���
			String sql = "select * from userinfo where username='" + sUserName
					+ "' and userpwd = '" + sPasswd + "'";

			Statement stmt = connection.createStatement ( );
			ResultSet rs = stmt.executeQuery ( sql ); //���ز�ѯ���

			//�����¼���ǿգ�������ƥ����û��������룬��½�ɹ�
			if ( rs.next ( ) )
			{
				out.println ( "��¼�ɹ���" );
			} else
			//�����¼ʧ��
			{
				out.println ( "�û��������ڻ��������" );
			}

			rs.close ( );
			stmt.close ( );
			connection.close ( );
		%>
	</body>
</html>

����Ϊ�ͻ�����Ӵ�����֤����:
<html>
  <head>
    <title>��¼</title>

    <meta http-equiv="content-type" content="text/html; charset=UTF-8">
    <meta http-equiv="Content-Language" content="ch-cn">

  </head>
  <body>
	<!-- Form ������ȡ�û����벢�ύ����Ϣ-->
	<form method="post" name="frmLogin" action="verifylogin.jsp">
		 <h1 align="center">�û���¼</h1><br>
		 <div align="center">�û�����
		  		<input type="text" name="txtUserName" value="Your name"
		  			onfocus="if(this.value=='Your name')this.value='';"><br>���룺
		  		<input type="password" name="txtPassword" value="Your password"
		  			onfocus="if(this.value=='Your password')this.value='';"><br>
		  		<input type="submit" name="Submit"��value="�ύ" onClick="validateLogin();" >
		  			&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
		  		<input type="reset" name="Reset" value="����"><br>
		 </div>
	</form>
	<!-- javaScript ���� validateLogin(),������֤�û����������Ƿ�Ϊ�� -->
    <script language="javaScript">
    	function validateLogin()
    	{
    		var sUserName = document.frmLogin.txtUserName.value;
    		var sPassword = document.frmLogin.txtPassword.value;
    		if( sUserName=="" )
    		{
    			alert("�������û�����");
    			return false;
    		}
    		if( sPassword=="" )
    		{
    			alert("���������룡");
    			return false;
    		}
    	}
    </script>
  </body>
</html>


Ϊ����������Ӵ�����֤����:
<%@ page language="java" contentType="text/html;charset=gb2312"
	pageEncoding="UTF-8"%>

<%@ page import="java.sql.*"%>
<%@ page import="java.util.*"%>


<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
	<head>
		<title>��¼</title>

		<meta http-equiv="pragma" content="no-cache">
		<meta http-equiv="cache-control" content="no-cache">
		<meta http-equiv="expires" content="0">
		<meta http-equiv="keywords" content="zieckey,jsp">
		<meta http-equiv="description" content="Test JSP using MySQL">

	</head>
	<body>
		<div align=center>
			<%
				//��ȡ�û���
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

				//��ȡ����
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

				//�Ǽ�JDBC��������
				Class.forName ( "org.gjt.mm.mysql.Driver" ).newInstance ( );
				//���Ӳ�����Access��ͬ
				String url = "jdbc:mysql://localhost/LearnJSP";
				//��������
				Connection connection = DriverManager.getConnection ( url, "root",
						"011124" );
				//SQL���
				String sql = "select * from userinfo where username='" + sUserName
						+ "' and userpwd = '" + sPasswd + "'";

				Statement stmt = connection.createStatement ( );
				ResultSet rs = stmt.executeQuery ( sql ); //���ز�ѯ���

				//�����¼���ǿգ�������ƥ����û��������룬��½�ɹ�
				if ( rs.next ( ) )
				{
					//��¼�ɹ���sUserName����Ϊsession������UserName
					//�����ں���Ϳ���ͨ�� session.getAttribute("UserName") ����ȡ�û�����
					//ͬʱ������������Ϊ�û���¼�����ж�����
					session.setAttribute ( "UserName", sUserName );
					out.print (  "��¼�ɹ���" );
					out.print ( session.getAttribute ( "UserName" ) + " ��ӭ����" );
				} else
				//�����¼ʧ��
				{
					out.println ( "�û��������ڻ��������" );
				}

				rs.close ( );
				stmt.close ( );
				connection.close ( );
			%>

	</body>
</html>


���ݿ������б���ֶγ��ȵ���Ʊ�׼��Ӧ�����㹻��,�����˷Ѵ洢�ռ�.
���ǿ��Է���,�������ݿ����ֶ�������20���ַ�����,��ô������ҲӦ����һ������,
������ܸ���վ�������ص�����.
������Դ���޸�����:
				.....
				<input type="text" name="txtUserName" value="Your name"
		  			size="20" maxlength="20"
		  			onfocus="if(this.value=='Your name')this.value='';"><br>���룺
		  		<input type="password" name="txtPassword" value="Your password"
		  			size="20" maxlength="20"
		  			onfocus="if(this.value=='Your password')this.value='';"><br>
				.....

				.....
				if ( sUserName == "" || sUserName == null || sUserName.length()>20 )
				....
				if ( sPasswd == "" || sPasswd == null || sPasswd.length()>20 )
				......

��������ͳ��׽����.






�������JSP+JavaBeanģʽ�����ĵ�¼�������JSP+Servlet+JavaBeanģʽ����ʵ��

����漰���ĸ��ļ�:
��¼ҳ��:login.html
��¼�ɹ���ӭҳ��:login_success.jsp
��¼ʧ��ҳ��:login_failure.jsp
Servlet�����ļ�:LoginServlet.java

��ʵ���漰��һ���ļ�:web.xml,���������˵:

����ֱ�����⼸���ļ�:
��¼ҳ��:login.html
<!-- ��Loginҳ����һ���򵥵ĵ�¼���� -->
<!--
	��JSP����������������MySQL���ݿ�����ӣ�
	��Ҫһ�����ݿ⣺LearnJSP��������һ����userinfo
	�����������ֶηֱ�Ϊ��UserName varchar (20) not null,UserPwd varchar (20) not null
-->
<html>
  <head>
    <title>��¼</title>
    <meta http-equiv="content-type" content="text/html; charset=UTF-8">
    <meta http-equiv="Content-Language" content="ch-cn">
  </head>
  <body>
	<!-- Form ������ȡ�û����벢�ύ����Ϣ-->
	<form method="post" name="frmLogin" action="LoginServlet">
		 <h1 align="center">�û���¼</h1><br>
		 <div align="center">�û�����
		  		<input type="text" name="txtUserName" value="Your name"
		  			size="20" maxlength="20"
		  			onfocus="if(this.value=='Your name')this.value='';"><br>���룺
		  		<input type="password" name="txtPassword" value="Your password"
		  			size="20" maxlength="20"
		  			onfocus="if(this.value=='Your password')this.value='';"><br>
		  		<input type="submit" name="Submit"��value="�ύ" onClick="validateLogin();" >
		  			&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
		  		<input type="reset" name="Reset" value="����"><br>
		 </div>
	</form>

	<!-- javaScript ���� validateLogin(),������֤�û����������Ƿ�Ϊ�� -->
    <script language="javaScript">
    	function validateLogin()
    	{
    		var sUserName = document.frmLogin.txtUserName.value;
    		var sPassword = document.frmLogin.txtPassword.value;
    		if( sUserName=="" )
    		{
    			alert("�������û�����");
    			return false;
    		}
    		if( sPassword=="" )
    		{
    			alert("���������룡");
    			return false;
    		}
    	}
    </script>

  </body>
</html>

��¼�ɹ���ӭҳ��:login_success.jsp
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
			��ӭ������¼�ɹ���
		</div>
	</body>
</html>



��¼ʧ��ҳ��:login_failure.jsp
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
			�Բ��𣬵�¼ʧ�ܣ�
		</div>
	</body>
</html>


Servlet�����ļ�:LoginServlet.java
/**
 * ��JSP����������������MySQL���ݿ�����ӣ�
 * ��Ҫһ�����ݿ⣺LearnJSP��������һ����userinfo
 * �����������ֶηֱ�Ϊ��UserName varchar (20) not null,UserPwd varchar (20) not null
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

		// ��ȡ�û���
		String sUserName = request.getParameter ( "txtUserName" );
		if ( sUserName == "" || sUserName == null || sUserName.length ( ) > 20 )
		{
			try
			{
				result = "�������û�����������20�ַ�����";
				request.setAttribute ( "ErrorUserName", result );
				response.sendRedirect ( "login.html" );
			} catch ( Exception e )
			{
			}
		}

		// ��ȡ����
		String sPasswd = request.getParameter ( "txtPassword" );
		if ( sPasswd == "" || sPasswd == null || sPasswd.length ( ) > 20 )
		{
			try
			{
				result = "���������루������20�ַ�����";
				request.setAttribute ( "ErrorPassword", result );
				response.sendRedirect ( "login.html" );
			} catch ( Exception e )
			{
			}
		}

		// �Ǽ�JDBC��������
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

		// ���Ӳ�����Access��ͬ
		String url = "jdbc:mysql://localhost/LearnJSP";
		// ��������
		java.sql.Connection connection = null;

		Statement stmt = null;
		ResultSet rs = null;
		try
		{
			connection = DriverManager.getConnection ( url, "root", "011124" );
			stmt = connection.createStatement ( );

			// SQL���
			String sql = "select * from userinfo where username='" + sUserName
					+ "' and userpwd = '" + sPasswd + "'";
			rs = stmt.executeQuery ( sql );// ���ز�ѯ���
		} catch ( SQLException e )
		{
			// TODO Auto-generated catch block
			e.printStackTrace ( );
		}

		try
		{
			if ( rs.next ( ) )// �����¼���ǿգ�������ƥ����û��������룬��½�ɹ�
			{
				// ��¼�ɹ���sUserName����Ϊsession������UserName
				// �����ں���Ϳ���ͨ�� session.getAttribute("UserName") ����ȡ�û�����
				// ͬʱ������������Ϊ�û���¼�����ж�����
				request.getSession ( ).setAttribute ( "UserName", sUserName );
				response.sendRedirect ( "login_success.jsp" );
			} else
			{
				// �����¼ʧ��
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



Ϊ���������վ�������л�Ҫ��web.xml��ע��һ��,
�ָ��ļ������޸�����:
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

����,�⼸���ļ��Ϳ��Թ������ǵ������¼������.
ע������:
1. �ļ�Ŀ¼��ʽ
login.html,login_success.html,login_failure.html�������ļ�����ͬһĿ¼,
LoginServlet.java���ļ����ֽ����ļ�LoginServlet.class����WEB-INF\classesĿ¼��(ע��jar��˳��)

�����������̵�Ŀ¼��ʽ��:
M:\Tomcat5.5\webapps\JSP_Servlet_JavaBean_Login ��Ŀ¼
007-01-18  15:16    <DIR>          META-INF
007-01-18  15:16    <DIR>          WEB-INF
007-01-18  16:17             1,801 login.html
007-01-18  15:48               858 login_failure.jsp
007-01-18  15:40               234 login_success.html
007-01-18  15:46               781 MyJsp.jsp
007-01-18  16:12               859 login_success.jsp

M:\Tomcat5.5\webapps\JSP_Servlet_JavaBean_Login\WEB-INF ��Ŀ¼
007-01-18  15:16    <DIR>          classes
007-01-18  15:16    <DIR>          lib
007-01-18  16:21               606 web.xml

M:\Tomcat5.5\webapps\JSP_Servlet_JavaBean_Login\WEB-INF\classes\zieckey\login\servlet ��Ŀ¼
2007-01-18  16:18             3,900 LoginServlet.class

2. ����ע������
���ݿ�MySQL����������Ҫ����������.














 <br>��<br />����˼�ǻ���
    ����һ�㽨����ʹ�ñ�׼�ĸ�ʽ<br /> (�м��пո�)

�����ڱ�дHTML�ļ�ʱ�����ǲ��ؿ���̫ϸ�����ã�Ҳ��������������Ĳ��ֻᱻ������е�����Ϊ����HTML���Թ淶�ÿ����������ڱ���Сʱ����������Զ����ұߵ�����ת������һ�С����ԣ���д�߶����Լ���Ҫ���еĵط���Ӧ����<br />��ǩ��

<html>
<head>
<title>�޻���ʾ��</title>
</head>
<body>
����ȸ¥��������ɽ�����ƺ��뺣��������ǧ��Ŀ������һ��¥��
</body>
</html>
<html>
<head>
<title>����ʾ��</title>
</head>
<body>
����ȸ¥<br />������ɽ����<br />�ƺ��뺣����<br />����ǧ��Ŀ��<br />����һ��¥��
</body>
</html>

 META��ǩ����HTML����head����һ�������Ա�ǩ���ڼ������е�page����Ƕ����Կ�
  �������������html���룺

  -----------------------------------------------
  <head>
  <meta   http-equiv="Content-Type"   content="text/html;   charset=gb2312">
  </head>
  -----------------------------------------------

  �����meta��ǩ�ĵ������á�meta��ǩ�ж��ٲ�������ʲô���ã�Ϊʲô����Ҫ�ر���
  �����أ�������һ��������meta��ǩ�İ���!

  ����HTML���Ա�׼ע�ͣ�meta��ǩ�Ƕ���վ��չ�ǳ���Ҫ�ı�ǩ�����������ڼ������ߣ�
  �趨ҳ���ʽ����ע������Ҫ�͹ؼ��֣��Լ�ˢ��ҳ��ȵȡ�

  meta��ǩ�����󲿷֣�HTTP-EQUIV��NAME������

  ��HTTP-EQUIV������HTTP��ͷ��Э�飬����Ӧ�������һЩ���õ���Ϣ���԰�����ȷ�;�ȷ
  ����ʾ��ҳ���ݡ����õ�HTTP-EQUIV�����У�

  1.expires(����)
  ˵�������������趨��ҳ�ĵ���ʱ�䡣һ����ҳ���ڣ����뵽�����������µ��ġ�
  �÷���<META   HTTP-EQUIV="expires"   CONTENT="Wed,   26   Feb   1997   08:21:57   GMT">
  ע�⣺����ʹ��GMT��ʱ���ʽ��

  2.Pragma(cachģʽ)
  ˵������ֹ������ӱ��ػ��Ļ����е���ҳ�����ݡ�
  �÷���<META   HTTP-EQUIV="Pragma"   CONTENT="no-cache">
  ע�⣺�����趨�������߽��޷��ѻ������

  3.Refresh(ˢ��)
  ˵������Ҫ��ʱ����ҳ�Զ����ӵ�������ҳ�Ļ�����������ˡ�
  �÷���<META   HTTP-EQUIV="Refresh"   CONTENT="5;URL=http://www.yahoo.com">
  ע�⣺���е�5��ָͣ��5���Ӻ��Զ�ˢ�µ�URL��ַ��

  4.Set-Cookie(cookie�趨)
  ˵���������ҳ���ڣ���ô���̵�cookie����ɾ����
  �÷���<META   HTTP-EQUIV="Set-Cookie"   CONTENT="cookievalue=xxx;
  expires=Wednesday,   21-Oct-98   16:14:21   GMT;   path=/">
  ע�⣺����ʹ��GMT��ʱ���ʽ��

  5.Window-target(��ʾ���ڵ��趨)
  ˵����ǿ��ҳ���ڵ�ǰ�����Զ���ҳ����ʾ��
  �÷���<META   HTTP-EQUIV="Window-target"   CONTENT="_top">
  ע�⣺������ֹ�����ڿ����������ҳ�档

  5.Content-Type(��ʾ�ַ������趨)
  ˵�����趨ҳ��ʹ�õ��ַ�����(������ǰ������������Ѿ����ܹ���������)
  �÷���<meta   http-equiv="Content-Type"   content="text/html;   charset=gb2312">


  ��meat��ǩ��NAME�����﷨��ʽ�ǣ�
  <META   NAME="xxx"   CONTENT="xxxxxxxxxxxxxxxxxx">
  ����xxx��Ҫ�����漸�ֲ�����

  1.Keywords(�ؼ���)
  ˵����keywords��������������������ҳ�Ĺؼ�����ʲô��
  ������<META   NAME   ="keywords"   CONTENT="life,   universe,   mankind,   plants,
  relationships,   the   meaning   of   life,   science">

  2.description(���)
  ˵����description���������������������վ��Ҫ���ݡ�
  ������<META   NAME="description"   CONTENT="This   page   is   about   the   meaning   of
  life,   the   universe,   mankind   and   plants.">

  3.robots(��������)
  ˵����robots��������������������Щҳ����Ҫ��������Щҳ�治��Ҫ������
  CONTENT�Ĳ�����all,none,index,noindex,follow,nofollow��Ĭ����all��
  ������<META   NAME="robots"   CONTENT="none">

  4.author(����)
  ˵������ע��ҳ������
  ������<META   name="AUTHOR"   content="ajie,ajie@netease.com">

  ������meta��ǩ��һЩ�����÷�����������Ҫ�ľ���:Keywords��description���趨��

  Ϊʲô�أ�����ܼ򵥣�������������������������׼ȷ�ķ����㣬����������˷���
  ���վ��!

  ��������������������(Lycos��AltaVista��)�Ĺ���ԭ��,�������������ɳ��������Զ�
  ��www���������������µ���վʱ�������ҳ���е�keywords��decription����������뵽��
  �������ݿ⣬Ȼ���ٸ��ݹؼ��ʵ��ܶȽ���վ����

  Ҳ����˵��
  1.   ������ҳ���и���û��Keywords��description��meta��ǩ����ô��������
  �޷������վ��������ݿ⣬����Ҳ�Ͳ��������������վ�㡣

  2.   �����Ĺؼ���ѡ�Ĳ��ã��ؼ��ֵ��ܶȲ��ߣ��������ڼ�ʮ�����������վ��ĺ���
  ������Ŀ�����Ҳ�Ƿǳ�С�ġ�

  ����,���Ǳ����ס���keywords��description��meta��ǩ����������д�ùؼ��ֺͼ�顣

  дkeywords�Ľ����ǣ�
  1.��Ҫ�ó����ʻ㡣����www,homepage,net,web�ȡ�
  2.��Ҫ�����ݴʣ����ʡ�������õģ����ĵȡ�
  3.��Ҫ����ͳ�Ĵʻ㣬Ҫ������ȷ�����粻��"Ħ�������ֻ�",����"V998"��

  Ѱ�Һ��ʵĹؼ��ʵ�һ�������ǣ���lycos,Alta,infoseek���������棬���������������
  ����վ���鿴����ǰʮλ����վ��meta�ؼ��֣�copy�����õ��Լ���վ���ϡ�

  ������Ǿ�һ��΢���ý����վ�Ĺؼ��ֹ���ο���
  <meta   name="keywords"   content="joke,   music,   MP3,   media,   audio,
  joke   of   the   day,   downloads,   free   music,   horoscope,   radio,   video,
  music   downloads,   movies,   radio   station,   media   player,   free,
  download,   weather,   horoscopes,   windows   media   technologies,
  online,   radio   station   guide,   free   download">

  С��Դ:������õ�һЩ������(���ؼ���)���Ե�
  http://www.searchterms.com/
  http://eyescream.com/yahootop200.html
  ������ַһ����������ÿ�������������������ʵ����а�.

  ����Ϊ�������������ʣ����ﻹ��һЩ"а�����"��
  1.Ϊ�����ӹؼ��ʵ��ܶȣ����ؼ���������ҳ����(��������ɫ������뱳����ɫһ��)��
  2.��ͼ���altע������м���ؼ��֡�
  �磺<IMG   SRC="xxx.gif"   Alt="keywords">
  3.����HTML��ע����䣬��ҳ��������������ؼ��֡�
  �÷���   <!---   �������ؼ���   --->




��ֵ������<%= userName %>
����� <%= userName %> ����дΪ<%= userName %>��
�����ܽ� % �� = �ֿ�д�ˣ����粻��дΪ������<% = userName %>

	<%
		String userName = (String)session.getAttribute("UserName");
    %>
����Ҳ��Ҫע���һ��Ҫ����ǿ��ת��(String)����ȻҲ�����г���



ע��ҳ�����
׼�����ݿ�:
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
�κ�һ��Servlet��Ҫ��web.xml�еǼǣ�����ͻ��Ҳ������Ǽ���Ŀ���£�
	  <servlet>
	  	<servlet-name>RegisterServlet</servlet-name>
	  	<servlet-class>zieckey.register.servlet.RegisterServlet</servlet-class>
	  </servlet>
	  <servlet-mapping>
	    <servlet-name>RegisterServlet</servlet-name>
	    <url-pattern>/RegisterServlet</url-pattern>
	  </servlet-mapping>


��Java Servlet��ʹ��Java��
request.getRequestDispatcher ("/messageboard/browsemessageboard.jsp").
													forward (request,response);
���ת��ҳ��ʱ������Ŀ¼���Ͳ�Ҫ���ϣ�
������JSPҳ����ʹ��ʱ,��Ҫ����Ŀ¼·��,����:
href="/BohaoWeb/messageboard/index.jsp"

2007-01-28 15:04:26



��ҳ��ť��Ӫ
---- һ����ť�Ļ���ʹ��

---- һ��Ŀ�������ҳ���������У����з���İ�ť��ӹ��ߣ���ֱ������ҳ�ĺ���λ����Ӱ�ť�������ʹ���ֹ�����ҳ������������ô���������Դ����������ť������onclick�������°�ť�Ķ�����

< form method="POST" >
< p >< input type="button" name="B1" value=
"��ť" >< /p >
onclick > < /p >
< /form >

---- ���ֻʹ�õ����İ�ť����ô��ʡ��form��ǩ��ֻʹ�õ����İ�ť���룬����ʡ��ť��ռ����ҳ�ռ䣺
< p >< input type="button" name="B1" value=
"��ť" >< /p >
onclick > < /p >

---- ������ť��ǰ���뱳������
---- �����������ʹ�ð�ťʱ����ֱ��ʹ��ȱʡ�ĻҰ�ɫ��ť�к�ɫ������˵������ʵ��ť�ı�����ǰ���ǿ�������ı�ģ��뿴����Ĵ��룺

< form name="highlight" >
< p align="center" >< input type=
"button" value="��ɫ��ť"
style="background-color: rgb(255,0,0);
color: rgb(255,2550,0)"
onclick > < /p >
< /form >

---- ����background-color���Ʊ���ɫ��color��ťǰ��ɫ��
---- ������ť��ͼƬ����

---- ��ť���������޸�ǰ��ɫ�ͱ�����ɫ�����ҿ���ʹ��ͼƬ����������Ĵ���ֱ���ʾ�˹̶��ı���ͼƬЧ���Ͷ�̬��ͼƬ����Ч������̬��Ч���������ŵ���ť��ʱ����ť�ı���������һ��ͼ�񱳾���������뿪ʱ��ָ�ԭ����ͼƬ��������������е�mainbb1.jpg��mainbb2.jpg �ֱ�Ϊ����ͼ���ļ���


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
value="�仯����"
style="background-color: rgb(192,192,192);
FONT-FAMILY: ����;
FONT-SIZE: 12pt;background-image: url(''mainbb2.jpg'')"
class="initial" onclick="(h1.htm'')"
< br > < input type="submit"
name="B1" value="�̶�����"
style="FONT-SIZE: 12pt; background-image:
url(''mainbb1.jpg'')" >< /p >
< /form >

---- �ġ���ť�ֺź����Ϳ���
---- ��ť����ʾ������Ҳ��������ı��񣬿���������������ͺ��ֺţ��뿴���´��룺

< form name="highlight" >
< p align="center" >
< input type="button" value="�仯�ֺ�"
style="background-color: rgb(192,192,192);
FONT-FAMILY: ����; FONT-SIZE: 9pt"
color: rgb(255,2550,0)"); onclick >
< input type="button" value="�仯�ֺ�"
style="background-color: rgb(192,192,192);
FONT-FAMILY: ����; FONT-SIZE: 12pt"
color: rgb(255,2550,0)"); onclick >
< /p >
< /form >

---- �塢��ť����ƶ���ɫ
---- �����Ѿ������˰�ť����ɫ���Ʒ�������������¼��Ĳ��뼴��ʵ������ƶ���ɫ�������������Ĵ��룺

< html >
< head >
< meta http-equiv="Content-Type"
content="text/html; charset=gb_2312-80" >
< meta name="GENERATOR" content=
"Microsoft FrontPage Express 2.0" >
< title >��ɫ��ť< /title >
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
"button" value="��ɫ��ť"); onclick > < /p >
< /form >
< /body >
< /html >
---- ��������ƶ���ť���ֺ�
---- ����ͬ���ķ�����Ҳ����ʹ��ť������ƶ�ʱ�任�ֺţ���ʵ�ֺŵı仯Ҳ�����˰�ť�ߴ�ı仯����һЧ���ܹ����������ߵ�ע��������ȻҲ���Ժ�����ʹ�ֺź���ɫͬʱ�����仯��

< html >
< head >
< meta http-equiv="Content-Type"
content="text/html; charset=gb_2312-80" >
< title >��Ű�ť< /title >
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
"button" value="��Ű�ť"); onclick > < /p >
< /form >
< /body >
< /html >

---- �ߡ���ť����ʾʱ��
---- ��ť����ʾ����Ϣ�����������ȶ���ɹ̶����ַ��������ҿ�����ʱ���ģ���Ȼ��Ҳ���԰�һЩ��̬����Ϣ�͵���ť�ϣ��������ڰ�ť����ʾ�߶���ʱ�ӵ����ӣ�Ч���ǳ��ã�

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

---- �ˡ���ť������ʾԴ�ļ�
---- Ϊ�˷������ѧϰ�����ҳ��Ʒ���������ҳ�Ϸ���һ����ť�����¸ð�ť���Զ���ʾԴ�ļ����ǲ��Ƿǳ�ʵ�ã��������£��ŵ���ҳ����������

< form method="POST" >
< p align="center" >< input type=
"button" name="B1"
value="��ʾԴ�ļ�"
onclick="window.location="
view-source:" +window.location.href" >
< /p >
< /form >

---- �š���ť����վ��
---- ���ǰ�ť��һ�����ʹ�÷��������°�ť��ת��һ��վ�㣺

< form >
< p >< input type="button"
value="�����վ > > >"
onclick="parent.location='http:
//jyt.yeah.net'" >< /p >
< /form >
---- ʮ����ť�ı�ҳ�汳��
---- ͨ����ť����ʵʱ�޸�ҳ�����ɫ����������Զ���������ɫ֮������л�������ɫ�����γ�����˸Ч��������Ĵ���������������ť���ֱ���ʾ�޸ı�������˸Ч��������ŵ���ҳ����������

< form >
< p >< input type="button" value="����ɫ�任"
onclick="BgButton()" >< /p >
< /form >
< script >function BgButton(){
if (document.bgColor=='#00ffff')

else }
< /script >

< FORM >< INPUT TYPE="BUTTON" VALUE="��˸"
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

---- ʮһ����ťˢ��ҳ��
---- ����������϶���ˢ�°�ť��������ҳ�����������Ե�ҳ���Ϊ���ƣ���������Щ������Ҫˢ�µĳ��ϣ�ʵ��ˢ�������ַ���������ֱ����£���ŵ���ҳ����������

����һ��
< form >
< p >< input type="button" value="ˢ�°�ť"
onclick="history.go(0)" > < /p >
< /form >
�������
< form >
< p >< input type="button" value="ˢ�°�ťһ"
onclick="ReloadButton()" >< /p >
< /form >
< script language="JavaScript" >< !--
function ReloadButton()
// -- >< /script >

---- ʮ����������ť
---- ���°�ť����Ļ���ݿ�ʼ���Ϲ������������£���һҳ���ȱ��볬��һ�������򽫿���������Ч����

< form >
< div align="center" >
< center >< p >< input type="button" value=
"���¹���" onClick="scrollit()" > < /p >
< /center >< /div >
< /form >

< script Language="JavaScript" >
< !--
function scrollit(){
for (I=1; I< =500; I++){
parent.scroll(1,I) }}
//-- >
< /script >

---- ʮ����������ǩ��ť
---- ������������Ҳ����ʵ�ּ�����ǩ���ܣ���ʹ�ð�ť���Ϊ��Ŀ��ֱ�ۣ����°�ť����ɰ�ָ����վ��ӵ�����������ǩ�У��������£�

< form >
< p >< input type="button"
value="�ѱ�վ������ǩ"
onclick="window.external.addFavorite
('http://jyt.yeah.net/','�ʷ�֮��')" >< /p >
< /form >

---- ʮ�ġ���ť��Ļ
---- �ƶ�����Ļ�����ټ���������FRONTPAGE �����ֳɵ���Ļ��������������JAVAʵ�ֵ������Ч�����ǻ����ٳ�����ʵʹ�ð�ť������ĻЧ����Ϊ���أ���ť�������ַ��������������ߴ�仯����̬��ǿ������Ϊ��ɵĴ��룬��ŵ���ҳ����������

< form name=form2 >
< p >< input type="submit" name="banner" VALUE="Submit"
onClick="alert('����Լ������ӣ�')" > < br >
< script language="JavaScript" >
var id,pause=0,position=0;
function banner() {
var i,k,msg="��ӭ����HXUN����վ";// increase msg
k=(30/msg.length)+1;
for(i=0;i< =k;i++) msg+=" "+msg;
document.form2.banner.value=msg.substring(position,position-30);
if(position++==msg.length) position=0;
id=setTimeout("banner()",60); }
banner();
< /script >< /p >
< /form >




��������JSP�����ˣ��������£�

������һ��Servlet�е����
{
	....
	request.getSession (true).setAttribute ( "BohaoStudentMenber", bs );// ���1* bs��һ����
	response.sendRedirect ( "bohaoadmin.jsp" );// ���2*
	....
}
�ڸ��ٵ����У�ִ���ġ����1*���󣬿��Կ���:
bs��ֵ��#3919
request��ֵ��request.Inherited.request.request.session.attribute����ֵ "BohaoStudentMenber"=>#3919
��˵����һ���Ѿ��ɹ���

��bohaoadmin.jsp�ļ��������������ȡ���Ե�ʱ��
BohaoStudentMenber bs = (BohaoStudentMenber)session.getAttribute ("BohaoStudentMenber");
�Ͳ�����ȡ����BohaoStudentMenber��������ֵ��ֻ���ǿ�ֵ��
���Ը��ٷ������ʱ���session������û�С�BohaoStudentMenber����һ����
����Ϊʲô�أ�

���Ǻ�������֪����ô���ֿ�����ȡ����BohaoStudentMenber���������ֵ��
��֣���֣�


������д Java ���ݿ�����ʱ������һ�����⣬˵����������ҷ����¡�
�������ģ����ȿ��������Ƭ�ϣ�

	//����Ƭ��1
	void func()
	{
		.......
		ResultSet rs = stmt.executeQuery (sql);
		if ( rs.next () )//�����ҵ���¼
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

��Ϊ ��//����Ƭ��1���е�if���̫�����ҽ����ȡΪһ�������ĺ��������£�

	//����Ƭ��2
	void func()
	{
		.......
		ResultSet rs = stmt.executeQuery (sql);
		setBohaoStudentField(bs,rs);
		..........
	}

	//����Ƭ��3
	private void setBohaoStudentField (final BohaoStudentMenber bs, final ResultSet rs) throws 		SQLException
    {
    	if ( rs.next () )//�����ҵ���¼
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

������û�д��󣬶���ʹ�ó����߼��������ˡ�
�õ��������Ǽ�����󿴡�
�ں����ĳ��ʱ������Ҫ��rs.next()Ϊ�յ�������д����õ�����Ȼ�뵽�����·�ʽ���У�

	//����Ƭ��4
	void func()
	{
		.......
		ResultSet rs = stmt.executeQuery (sql);
		if ( rs.next () )//�����ҵ���¼
		{
			setBohaoStudentField(bs,rs);
		}else
		{
			....
		}
		..........
	}

	//����Ƭ��5
	private void setBohaoStudentField (final BohaoStudentMenber bs, final ResultSet rs) throws 		SQLException
    {
    	if ( rs.next () )//�����ҵ���¼
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

��������֮�󣬳�������˴����Ҳ�֪���������
������֪��������������֮�󣬳���ͳ����ˣ�
�õģ��Ҿ����Ҹ��ĵĵط����жϵ���٣�
������ǡ�//����Ƭ��4��	�͡�//����Ƭ��5���ĵ��ó��ִ����ˣ�
Ϊʲô�أ��Ҳ�û�и������ǵĵ��÷�ʽ����Ϊʲô�������أ�
Ϊʲô�ڡ�//����Ƭ��4���е�if ( rs.next () ) �ж�Ϊ�棬
�����ڡ�//����Ƭ��5���е�if ( rs.next () ) �ж�Ϊ�����أ�
�鿴�����ĵ������� ResultSet.next() ��˵����������:
boolean next()
          Moves the cursor down one row from its current position.
��ͻȻ��ʶ���ҷ���һ�������Ĵ���,���ҵ���
	setBohaoStudentField(bs,rs);
����֮ǰ,������һ��
    if ( rs.next () )
�ж�,֮����
	setBohaoStudentField
�������ڲ������ٴ�����һ��
	if ( rs.next () )
�ж�,
�������������,���ʱ����ж�,
��¼�� rs ���α��Ѿ���Ϊ�ڵ���֮ǰ���Ǵ��ж϶������ƶ���һ��,
Ҳ����˵��ǰ�ļ�¼�ı���,
��������е�֢������.
���������˺����Ƶ����鰡,����,�Ҽ�ʱ������,
Ҫ�ǵȵ������ĳ��ʱ��ȥ����,�ǻ���֪��Ҫ���ٵ�ʲôʱ����!!


�� Collection ��ʱ��Ҫ�õ� Iterator��
ͨ�� Iterator ��ȥCollection�еĶ���
��ô Iterator.next() ǰһ��Ҫ����ǿ��ת����
���磺News news = (News) iterator.next ();











mysql> select * from bohaodb.news where topic like '%��%';
+----+----------------------------+------------------------------+------+-------
-----+-----------------------------+---------------------+-------------+
| id | topic                      | content                      | hits | catego
ryid | picture                     | publishtime         | publishuser |
+----+----------------------------+------------------------------+------+-------
-----+-----------------------------+---------------------+-------------+
|  1 | ����һ�е����ݳ������Ӳ� | ����һ�е����ݳ������Ӳ졣 |    3 |
   0 | /upload/images/������.jpg | 2007-02-04 00:00:00 |             |
+----+----------------------------+------------------------------+------+-------
-----+-----------------------------+---------------------+-------------+
1 row in set (0.00 sec)



2007.11.13
netbeanʹ�����⣺

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
��Netbeans�˴�����������û���������.


ʹ��NetBeans6.0��ʼJSP֮��
���ص�ַ��
NetBeans6.0�����ư���
Tomcat5.5�����ư���

Tomcat5.5��װ���������������� bin\startup.bat install


2008/1/19
tomcatPlugin����
http://www.eclipsetotale.com/tomcatPlugin.html

struts����
http://struts.apache.org/
http://struts.apache.org/download.cgi#struts2011






2008/2/24
Hibernateѧϰ











2008/01/15

��Ŀ���
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


�����Cindy
������Chery
��ƽ


��������Stephen Sun��: �����ж�ѧ�� 
TEAM��Product
��ϵ�绰��13810724580
��˾���䣺 c-lanjiang.sun@accessmedia.com.cn
MSN��lanjiangsun@gmail.com

 

κ������������һѧ�� 
TEAM��SERVER
��ϵ�绰��15801463655
��˾���䣺c-zili.wei@accessmedia.com.cn
MSN��zieckey@hotmail.com
 

��ɣ���ͨ���� 
TEAM��SERVER
��ϵ�绰��NA
��˾���䣺c-ke.chai@accessmedia.com.cn
MSN��NA 


 
mysql> source melodeo_smartone_20080115.sql


�޸��ļ���
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
 
 		����,Hibernate������ݿ�urlҪ�������һ��
				
D:\tools\jakarta-tomcat-5.0.28-MD\conf\Catalina\localhost\md.xml				
<Context path="/md" docBase="D:\\workspace\\PROJ-S001_SmarTone_MD_Backend\\web"
	debug="0" reloadable="true" privileged="true">				
				
����Tomcat
	���·�������JDK����Ӳ���: -Djava.security.auth.login.config="D:\workspace\PROJ-S001_SmarTone_MD_Backend\conf\md_jaas_realm.config"		
				
				
			
				
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
ant1.7���أ�http://ant.apache.org/bindownload.cgi
hibernate���أ�http://sourceforge.net/project/showfiles.php?group_id=40712
ע�����أ�Hibernate��Hibernate-Extension��Middlegen-Hibernate����������°汾



    <property name="connection.datasource">java:comp/env/jdbc/MDDS</property>
     <property name="dialect">net.sf.hibernate.dialect.MySQLDialect</property>
     <property name="show_sql">false</property>
	 <property name="connection.url">jdbc:mysql://localhost:3306/melodeo?useUnicode=true&amp;characterEncoding=UTF-8</property>


���ص� Ant ���������ѹ������C:\ant\����������binĿ¼����c:\ant\bin����ӵ�ϵͳ
PATH �С�

1�� POJO
POJO ��Hibernate ���������Ϊ���ݿ������Ӧ��Domain Object�������POJO
������ν�ġ�Plain Ordinary Java Object�������������������޸�ʽ��ͨJava ���󣬼�
���Ŀ������Ϊһ���������߼������ֵ����Value Object ���VO����
һ�����͵�POJO��

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


2�� Hibernate ӳ���ļ�
Hibernate �ӱ�����������һ�֡����󣭹�ϵ������ӳ�䡱��Object Relational
Mapping ���ORM����ǰ���POJO���������ֵľ���ORM��Object������壬
��ӳ�䣨Mapping���ļ����ǽ�����Object�����ϵ�����ݣ�Relational�������
��Ŧ������Hibernate�У�ӳ���ļ�ͨ���ԡ�.hbm.xml����Ϊ��׺��
����Hibernate��������ͨ��������;����
1�� �ֹ���д
2�� ֱ�Ӵ����ݿ��е�����ṹ�������ɶ�Ӧ��ORM�ļ���Java ���롣
����ʵ�ʿ�������õķ�ʽ��Ҳ���������Ƽ��ķ�ʽ��
ͨ��ֱ�Ӵ�Ŀ�����ݿ��е������ݽṹ����С�����ֹ�����͵����Ŀ����ԣ��Ӷ�
���̶��ϱ�֤��ORM�ļ���Java ������ʵ�����ݿ�ṹ��һ�¡�
3�� �������е�Java �������ɶ�Ӧ��ӳ���ļ�����Java ���������ݿ����󶨡�
ͨ��Ԥ�ȱ�д�õ�POJO ����ӳ���ļ������ַ�ʽ��ʵ�ʿ�����Ҳ����ʹ�ã��ر�
�ǽ����xdoclet ֮���Ե���Ϊ����Ǳ�����������ʵ�����ݿ�ṹ֮�����
���ֵ�ͬ���ϵ��ϰ���������Ҫ�ֹ��������룬���������Ĺ����������ֹ�������
��©������������ɵ������ļ����������Ҫ�ڿ������ر�ע�⡣
���xdoclet����POJO ����ӳ���ļ��ļ������ǽ��ڡ��߼����ԡ��½��н���̽�֡�
�����ݿ������������
ͨ��Hibernate�ٷ��ṩ��MiddleGen for Hibernate ��Hibernate_Extension���߰�����
�ǿ��Ժܷ���ĸ����������ݿ⣬�������ݿ��ṹ������ORM��POJO��
1) ���ȣ���Middlegen-Hibernate�������ѹ���� ���ѹ����C:\Middlegen\ ����
2) ����Ŀ�����ݿ����
����MiddleGen Ŀ¼�µ�\config\database ��Ŀ¼����������ʵ�ʲ��õ����ݿ��
��Ӧ�������ļ��������������õ���mysql���ݿ⣬��Ӧ�ľ���mysql.xml�ļ���

��Ҫ�����¼�����������

   <property name="database.driver"                value="org.gjt.mm.mysql.Driver"/>
   <property name="database.url"                   value="jdbc:mysql://localhost:3306/melodeo?useUnicode=true&amp;characterEncoding=UTF-8"/>
   <property name="database.userid"                value="root"/>
   <property name="database.password"              value="123456"/>
   
   
3) �޸�Build.xml
�޸�MiddleGen ��Ŀ¼�µ�build.xml �ļ������ļ���Middlegen-Hibernate ��Ant
�������á�Middlegen-Hibernate������build.xml�ļ��еľ�������������ݿ��ӳ��
�ļ��������õ���Ŀ������
a) Ŀ�����ݿ������ļ���ַ
���ҹؼ��� ��!ENTITY�����õ���
<!DOCTYPE project [
<!ENTITY database SYSTEM
"file:./config/database/hsqldb.xml">
]>
Ĭ������£�MiddleGen ���õ���hsqldb.xml�������޸�Ϊ�������õ�����
�������ļ���mysql.xml����
<!DOCTYPE project [
<!ENTITY database SYSTEM
"file:./config/database/mysql.xml">
]>
b) Application name
���ң�
<property name="name" value="airline"/>
��aireline����MiddleGenԭʼ������Ĭ�ϵ� Application Name�������޸�Ϊ����
��ϣ�������ƣ��硰HibernateSample����
<property name="name" value="HibernateSample"/>
c) ���Ŀ¼
���ҹؼ��֡�name="build.gen-src.dir"�����õ���
<property name="build.gen-src.dir"
value="${build.dir}/gen-src"/>
�޸�value="${build.dir}/gen-src"ʹ��ָ�����������������Ŀ¼��
���������޸�Ϊ��
<property name="build.gen-src.dir"
value="C:\sample"/>
d) ��Ӧ�����Package name
���ҹؼ��֡�destination�����õ���
<hibernate
destination="${build.gen-src.dir}"
package="${name}.hibernate"
genXDocletTags="false"
genIntergratedCompositeKeys="false"
javaTypeMapper=
"middlegen.plugins.hibernate.HibernateJavaTypeMapper"
/>
���Կ�����hibernate �ڵ�package ���Ե�Ĭ������ʵ��������ǰ���
Application Name ��${name}���͡�.hibernate����϶��ɣ��������ǵ���Ҫ��
�����Ϊ��
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


���ݿⱸ�ݻָ���mysql -u �û��� -p ���ݿ��� < .dump
C:\Documents and Settings\Administrator>mysql -uroot -p123456 test < D:\a.dmp

C:\Documents and Settings\Administrator>


���ݿⱸ�ݣ�
C:\Documents and Settings\Administrator>mysqldump -uroot -p123456 test > d:\a.sql




Character Description 
% Matches any number of characters, even zero characters 
_ Matches exactly one character 




���ݿ����:

1�������û����±�	python	y	new user monthly report
��ѯsubscribers��������dateRegistered��ע��ʱ�䣩

�鿴ĳһ�µ������û���
SELECT count(clientId) from subscribers WHERE month(dateRegistered)=1 and year(dateRegistered)=2008

�鿴ĳһ��������û���
SELECT count(clientId) from subscribers WHERE month(dateRegistered)=12 and year(dateRegistered)=2007 and day(dateRegistered)=9

2�����ؿͻ��˵�δ�����û����±���	Java	y	unactivated user monthly report

3���Ƽ��ͻ����û��ձ�	Java	y	successful client refer daily report
4���ͻ����������ձ���	Java	y	client download daily report


5�������û����±�	python	y	registered user monthly report �ۼ�
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


6��	�����������������±���	Java	y	song purchase monthly report (by artist)
7��	�����������������±���	Java	y	song preview monthly report (by artist)
8��	�����������������±���	Java	y	song purchase monthly report
9��	�����������������±���	Java	y	song preview monthly report 
10������������������±���	Java	y	song download monthly report (by genre)
11������������������±���	Java	y	song preview monthly report (by genre)
12������Ƭ��˾�������±���	Java	y	song preview monthly report (by label)
13��WAP�����û����ձ���	Java	y	WAP link visitor daily report
14��WAP�������ձ���	Java	y	WAP link hits daily report
15����Ծ�û����±���			Total Active User Monthly Report

16�����������¼��			Song Purchase Transaction Report







<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE struts-config PUBLIC
"-//Apache Software Foundation//DTD Struts Configuration 1.1//EN"
"http://jakarta.apache.org/struts/dtds/struts-config.dtd"><!-- struts-config.xml�е�Ԫ�ر��밴������docָ���е�dtd�ĵ�����˳����д�������������dtd����˳�� --><!-- struts-config������xml�ĸ�Ԫ�أ�����Ԫ�ر��뱻�������� -->
<struts-config>
	<!--
		����:data-sources
		������data-sourcesԪ�ض�����web App����Ҫʹ�õ�����Դ
		���������һ��
		��Ԫ��:data-source
	-->
	<data-sources>
		<!--
			���ƣ�data-source
			������data-sourceԪ�ض����˾��������Դ
			������������
			���ԣ�
			@key������Ҫ���ö������Դʱ���൱������Դ�����ƣ���������Դ�˴˼��������
			@type������ʹ�õ�����Դʵ�ֵ��࣬һ�����������ĸ���
			Poolman������Դ�������
			Expresso��Jcorporate
			JDBC Pool������Դ�������
			DBCP��Jakarta
		-->
		<data-source key="firstOne"
			type="org.apache.commons.dbcp.BasicDataSource">
			<!--
				���ƣ�set-property
				�����������趨����Դ������
				���ԣ�
				@autoCommit:�Ƿ��Զ��ύ ��ѡֵ��true/false
				@description:����Դ����
				@driverClass:����Դʹ�õ���
				@maxCount:�������Դ������
				@minCount:��С����Դ������
				@user:���ݿ��û�
				@password:���ݿ�����
				@url:���ݿ�url
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
		���ƣ�form-beans
		�������������ö��ActionForm Bean
		���������һ��
		��Ԫ�أ�form-bean
	-->
	<form-beans>
		<!--
			���ƣ�form-bean
			��������������ActionForm Bean
			������������
			��Ԫ�أ�form-property
			���ԣ�
			@className��ָ����form-beanԪ�����Ӧ�������࣬һ��Ĭ��ʹ��org.apaceh.struts.config.FormBeanConfig������Զ��壬�����̳� FormBeanConfig
			@name���ر����ԣ�Ϊ��ǰform-bean�ƶ�һ��ȫ��Ψһ�ı�ʶ����ʹ��������Struts����ڣ�����ͨ���ñ�ʶ�����������ActionForm Bean��
			@type���ر����ԣ�ָ��ʵ�ֵ�ǰActionForm Bean������������
		-->
		<form-bean name="Hello" type="myPack.Hello">
			<!--
				���ƣ�form-property
				�����������趨ActionForm Bean������
				����������ʵ��������������磬ActionForm Bean��Ӧ��һ����½Form���������ı���name��password��ActionForm Bean��Ҳ���������ֶΣ���˴���д����form-property���趨����
				���ԣ�
				@className��ָ����form-property���Ӧ�������࣬Ĭ����org.apache.struts.config.FormPropertyConfig������Զ��壬�����̳�FormPropertyConfig��
				@name����Ҫ�趨��ActionForm Bean����������
				@type����Ҫ�趨��ActionForm Bean������ֵ����
				@initial����ǰ���Եĳ�ֵ
			-->
			<form-property name="name" type="java.lang.String" />
			<form-property name="number" type="java.lang.Iteger"
				initial="18" />
		</form-bean>
	</form-beans>

	<!--
		���ƣ�global-exceptions
		�����������쳣
		���������һ��
		��Ԫ�أ�exception
	-->
	<global-exceptions>
		<!--
			���ƣ�exception
			���������嶨��һ���쳣���䴦��
			������������
			���ԣ�
			@className:ָ����Ӧexception�������࣬Ĭ��Ϊorg.apache.struts.config.ExceptionConfig
			@handler:ָ���쳣�����࣬Ĭ��Ϊorg.apache.struts.action.ExceptionHandler
			@key:ָ����Resource Bundle���������쳣����Ϣkey
			@path:ָ���������쳣ʱ������ת����·��
			@scope:ָ��ActionMessageʵ����ŵķ�Χ��Ĭ��Ϊrequest������һ����ѡֵ��session
			@type:����Ҫ�У�ָ������Ҫ�����쳣������֡�
			@bundle:ָ����Դ��
		-->
		<exception key="hello.error"  path="/error.jsp" scope="session"
			type="hello.HandleError" />
	</global-exceptions>

	<!--
		���ƣ�global-forwards
		����������ȫ��ת��
		���������һ��
		��Ԫ�أ�forward
	-->
	<global-forwards>
		<!--
			���ƣ�forward
			����������һ�������ת��
			������������
			���ԣ�
			@className:ָ����forwardԪ�ض�Ӧ�������࣬Ĭ��Ϊorg.apache.struts.action.ActionForward
			@contextRelative:���Ϊtrue����ָ��ʹ�õ�ǰ�����ģ�·���ԡ�/����ͷ��Ĭ��Ϊfalse
			@name:�������У�ָ��ת��·����Ψһ��ʶ��
			@path:�������У�ָ��ת�������ض����URI��������"/"��ͷ����������Ҫ��contextRelative��Ӧ��
			@redirect:Ϊtrueʱ��ִ���ض������������ִ������ת����Ĭ��Ϊfalse
		-->
		<forward name="A" path="/a.jsp" />
		<forward name="B" path="/hello/b.do" />
	</global-forwards>

	<!--
		���ƣ�action-mappings
		����������action����
		���������һ��
		��Ԫ�أ�action
	-->
	<action-mappings>
		<!--
			���ƣ�action
			�����������˴��ض�������·������Ӧ��Action���ӳ�䡣ÿ��actionԪ�ؽ���path���Զ��������
				��ӳ�䵽type����������ľ���action������ӳ������н�name���Զ����ActionForm����һ�����͹�ȥ
			������������
			��Ԫ�أ�exception,forward�����߾�Ϊ�ֲ�����
			���ԣ�
			@attribute:�ƶ��뵱ǰAction�������ActionForm Bean��request��session��Χ�ڵ����ƣ�key��
			@className:��ActionԪ�ض�Ӧ�������ࡣĬ��Ϊorg.apache.struts.action.ActionMapping
			@forward:ָ��ת����URL·��
			@include:ָ��������URL·��
			@input:ָ�������������URL·��������֤ʧ��ʱ������ᱻת������URL��
			@name:ָ���͵�ǰAcion������ActionForm Bean�����֡������Ʊ�����form-beanԪ���ж������
			@path:ָ������Action��·������"/"��ͷ��û����չ��
			@parameter:Ϊ��ǰ��Action���ò�����������Action��execute()�����У�ͨ������ActionMapping��getParameter()��������ȡ����
			@roles:ָ��������ø�Aciton�İ�ȫ��ɫ�������ɫ֮���ö��ŷָ��������ʱ��RequestProcessor����ݸ��������������û��Ƿ��е��ø�Action��Ȩ��
			@scope:ָ��ActionForm Bean�Ĵ��ڷ�Χ����ѡֵΪrequest��session��Ĭ��Ϊsession
			@type:ָ��Action�����������
			@unknown:ֵΪtrueʱ����ʾ���Դ����û�������������Ч��Action URL��Ĭ��Ϊfalse
			@validate:ָ���Ƿ�Ҫ�ȵ���ActionForm Bean��validate()������Ĭ��Ϊtrue
			ע�⣺���������У�forward/include/type������⣬��������ͬһAction������ֻ�ܴ���һ����
		-->
		<action path="/search" type="addressbook.actions.SearchAction"
			name="searchForm" scope="request" validate="true"
			input="/search.jsp">
			<forward name="success" path="/display.jsp" />
		</action>
	</action-mappings>

	<!--
		���ƣ�controller
		��������������ActionServlet
		���������һ��
		���ԣ�
		@bufferSize:ָ���ϴ��ļ������뻺��Ĵ�С.Ĭ��Ϊ4096
		@className:ָ����ǰ��������������.Ĭ��Ϊorg.apache.struts.config.ControllerConfig
		@contentType:ָ����Ӧ������������ͺ��ַ�����
		@locale:ָ���Ƿ��Locale���󱣴浽��ǰ�û���session��,Ĭ��Ϊfalse
		@processorClass:ָ�������������Java�����������.Ĭ��org.apache.struts.action.RequestProcessor
		@tempDir:ָ���ļ��ϴ�ʱ����ʱ����Ŀ¼.���û������,������Servlet����ΪwebӦ�÷������ʱ����Ŀ¼.
		@nochache:trueʱ,����Ӧ����м����ض���ͷ����:Pragma ,Cache-Control,Expires��ֹҳ�汻�洢�ڿ���������Ļ�����,Ĭ��Ϊfalse
	-->
	<controller contentType="text/html;charset=UTF-8" locale="true"
		processorClass="CustomRequestProcessor">
	</controller>
	
	
	<!--
		����:message-resources
		����:����Resource Bundle.
		����:������
		����:
		@className:ָ����message-resources��Ӧ��������.Ĭ��Ϊorg.apache.struts.config.MessageResourcesConfig
		@factory:ָ����Դ�Ĺ�����,Ĭ��Ϊorg.apache.struts.util.PropertyMessageResourcesFactory
		@key:
		@null:
		@parameter:
	-->
	<message-resources null="false" parameter="defaultResource" />
	<message-resources key="images" null="false"
		parameter="ImageResources" />

	<!--
		����:plug-in
		����:��������Struts�Ĳ��
		����:������
		��Ԫ��:set-property
		����:
		@className:ָ��Struts�����.�������ʵ��org.apache.struts.action.PlugIn�ӿ�
	-->
	<plug-in className="org.apache.struts.validator.ValidatorPlugIn">
		<!--
			����:set-property
			����:���ò��������
			����:������
			����:
			@property:�������������
			@value:�����������õ�ֵ
		-->
		<set-property property="pathnames"
			value="/WEB-INF/validator-rules.xml,/WEB-INF/vlaidation.xml" />
	</plug-in>

</struts-config>









2008/2/15
displaytag

ʮ����ҳ
����
����ʵ�ַ�ҳ�ǳ��ļ򵥣�����һ��pagesize����ָ��һ������ʾ����������
����
����<display:table name="sessionScope.test" pagesize="10">
����<display:column property="id" title="ID" />
����<display:column property="name" />
����<display:column property="email" />
����<display:column property="status" />
����</display:table>









displaytag��ҳ ʹ��
1.����displaytag�ļ������ļ�,�͸�����apache��commons-lang-2.1������Ҫ����2.1�汾�ġ�
2.�޸�web.xml,���ϣ�
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
������web.xml�ж��壬�����ء���Ϊdisplaytag.tld�Ѿ���jar�ļ��������ˡ�
The declaration, if you are using a JSP XML syntax, looks like:
  <jsp:root version="1.2" xmlns:jsp="http://java.sun.com/JSP/Page"
     xmlns:display="urn:jsptld:http://displaytag.sf.net">


4.Ȼ����ҳ����ȡ������
<%
List<President> list=new com.PagedData().getData();
request.setAttribute("test",list);
%>
��򵥵���ʽ��    <display:table name="test" />
    display tag���Զ�����һ��table,��ʾ��������

5.
<display:table name="sessionScope.test"  cellspacing="0" cellpadding="0" pagesize="10"  defaultsort="1" defaultorder="descending">
  <display:column property="term"   sortable="true"/>
  <display:column property="firstName"  url="/aa.jsp" paramId="term" paramProperty="term" sortable="true"/>
  <display:column property="lastName" title="aaaa"  sortable="true"/>
</display:table>
������������ģ�ֻҪ��jsp�м��ϣ�
<%@ page language="java" contentType="text/html;charset=GBK"%>
6.
��ǩȡ�����ݵ�����Դ
  �����ַ�Χ
   pageScope
   requestScope (Ĭ��)  <display:table name="test2" >
   sessionScope  <display:table name="sessionScope.holder.list" > ע�⣬����Ҫָ����Χ����Ĭ��
   applicationScope 


���ڵ����⣺
1.��ʹ��sessionScope.test���������򣬵�����������Ϊ�ա�
2.��ʹ�õ�Ĭ�ϵ�requestScope�����Ե������ݣ�����������
��֪��ʲôԭ�򣿣�����














DisplayTag������
[2007��7��6�� ����]
����Ƚ���,�ܳ�ʱ��û���¿ռ���,���ý����л���,׼��������^_^
 
Display Tag Lib��һ����ǩ��,��Ҫ��������jsp��ҳ�ϵ�Table,���ܷǳ�ǿ,���ԶԵ�Table���з�ҳ�����ݵ��������顢��������ȵ�,����ʹ�������ǳ��ķ���,�ܹ������ٴ�����.
 
�ǵ���N�������ʹ���ҳ������ο��Ը��ӷ��㡢���ٵĴ���,�ҵĻش����ÿ�ζ���"DisplayTag",Ȼ������ͬ�������ѽ�����ʲô���ܡ��ܼ��ٶ��ٱ����������ĵ�����ο�war����.�����ڵ�ʱ����Ѳ�������¼����,�������ҵĿ�ˮ������.
 
�׻�˵�ú�"·ң֪����",�������ϵ�ʹ��,�о�DisplayTag"����"��,������ȱ��Խ��Խ��.���ڻ���ʹ����������,����Ѿ���������,��ô�ͱ��˷�ʱ�俴�����;�������ʹ�õ�����,����ܿ������ܽ��DisplayTag��״,�����ֲ�Щȱ��,�������������ʱ�Ǻ�����.�Ǻ�.
 
1.���ķ�ҳ����������:���������޷���ҳ������,��򵥵İ취���޸�Tomcat�µ�server.xml�ļ�.�ҵ�HTTP��Connector��ǩ,���������һ��URIEncoding="...",�������������ȡ�������ҳ�����,���������GBK,UTF-8��.
 
2.��ҳ���ݼ�������:DisplayTag�ķ�ҳ������������,�������е����ݷ��뼯����,Ȼ���ٽ��з�ҳ����.�������������Ƚϴ�������,��������������½������ڴ泬֧������.Ŀǰ�������������,һ����<displaytag>�������������ԣ�partialList="true"size="resultSize",ÿ��ֻ���ٵ�ǰҳ����.���о���ʵ�� org.displaytag.pagination.PaginatedList�ӿ�,�Զ����ҳ�㷨.�����Ƽ��ڶ���,��ϸ��ʵ�ַ����ɲο�DisplayTag 1.1����������.
PS:�ڶ��ַ�����������,DisplayTag���Դ���һЩBug.
 
3.��������Excel����:�����������б��������ı������Excelʱ,�������������.
���:
���������ļ�displaytag.properties,ʹ��displaytag-export-poi.jar��.����export.excel.class=org.displaytag.export.ExcelViewΪexport.excel.class=org.displaytag.excel.ExcelHssfView,�������Խ�����ı�����ݵ�����.���������б������������,�������org.displaytag.excel.ExcelHssfViewԴ����:
 
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
 
����һ��ͨ���޸ı��뷽ʽ��֧�����ĵķ���,�Ǿ��ǽ�org.displaytag.export.ExcelView.java�е�getMimeType()���������޸�Ϊreturn "application/vnd.ms-excel;charset=GB2312";���������޸ĺ�,�����ٶȽ���ǳ���,�Ǻ�.
 
4.decorator�����޷����������Html��ǩ��������:�����table������decorator,��ôdecorator������ݽ��޷�����.Ŀǰ�������޷����.������ò���decorator.�����ʾ������ʹ����html��ǩ����������,��ô���Ὣhtml��ǩһ�𵼳�.Ҳ��û��ʲô�õĽ������.
 
5.����Excel����������:��ʱ����ּ���������,������Excel��Office 2003�´򲻿�.
PS:�������ⲻ��,������Excel.����ʹ��Apache POI�Լ�ʵ��Excel�ĵ���.
 
6.ͬҳ��ʹ�ö��displayTag��ҳ����.DisplayTag��ҳʱ,ҳ�������е�displayTagԪ�ض���ҳ.����취:��ҳ���е�ÿ�����,���ж����ļ�¼�Ƿ�Ϊ0,���Ϊ0��ʹ��DisplayTag.
 
7.δ֪Bug�Ƚ϶�:��ʽ�����汾���Ǵ��ںܶ�Bug.��1.1�汾����ʱ,��Ȼ��ҳ�㷨����������Bug,����.






















2008/02/18
CVS

eclipse��CVS

���CVS Repositories
ѡ�� Windows->Show View->Other->CVS Repositories
�����·��� CVS Repositories ��ͼ�� �Ҽ�->New->Repository Location...


CVS����

eclipse
�� Packet Explorer ���Ҽ������Ŀ���ƣ�Team->Share Project ->Create a new repository location

Host:localhost (����IP)
repository path: /CVS

user: 
password





   ��Windows�ϰ�װSubversion��CVS���������[ZT]     2006-02-26 21:36:15 
�� �� С 
��Windows�ϰ�װSubversion��CVS���������
.....................................

   Subversion��CVS�������Ƚ���Ҫ�Ŀ�Դ�汾���������ͨ�����ǻὫ�䰲װ��Unix-likeϵͳ�ϣ�����ʵ�ʵ�һЩ��Ҫ��������Ҫ���䰲װ��Windows�����£�������������������Windowsϵͳ�µİ�װ˵����
 
��װSubversion 
 
��������Subversion Windows�汾�ķ�������������ص�ַ���£�
http://subversion.tigris.org/servlets/ProjectDocumentList?folderID=91
��svn-1.2.1-setup.exe��Ȼ��ִ�а�װ����װĿ¼�磺d:\develop\subversion��Ȼ������һ��ϵͳ�Ļ�������Path����Subversion��bin·�����뵽ϵͳ��path�С�
����Subersion�⣺���Ƚ���һ��Ŀ¼������е�Subversion�⣬�������ǿ��Գ�֮ΪData Directory������ͬ���ݿ������DataĿ¼һ������D:\repository\subversion��
����һ���µ�Subversion�⣬��������Ϊrepo1������������Ҫ��һЩ��Ŀ�����������֡�ֻ��ִ�У� svnadmin create D:\repository\subversion\repo1
������Ҫ���ÿ���û���Ϣ��ֻ���repo1��Ŀ¼�µ�conf��Ŀ¼����passwd�ļ�����µ��û����ɣ���
[users]
admin = mypassword
�����������ÿ��һЩ������Ϣ����confĿ¼�µ�svnserve.conf�ļ���Ȼ������������ü��ɣ�
[general]
anon-access = read
auth-access = write
password-db = passwd
realm = repo1
����Subversion���������ͨ�����������������ʹ��SVN Service Wrapper�������ͨ�����µ�ַ���أ�http://dark.clansoft.dk/~mbn/svnservice���� SVNService.exe������Subversion��װ��Ŀ¼��binĿ¼�¼��ɣ�Ȼ��ִ����������Ϳ��Խ�Subversion�� windows����ʽ��������
SVNService -install -d -r D:\repository\subversion
��Subversion �е�����Ŀ������������Ҫ����Ŀ���뵽Subversion�Ŀ��У�ֻ��ִ��һ����� svn import d:\demo svn://localhost/repo1/demo -m "initial import" --username admin --password abc123
������Ŀ�͵��뵽subversion��������
����Ŀ��������Subversion��Ŀ�е�����ĿҲ�ܼ򵥣�ֻ��ִ�����²�����
svn co svn://localhost/repo1/demo --username admin --password mypassword
 
��װCVSNT
 
���ȴ�www.cvsnt.org����CVS������������ļ���Ϊcvsnt-2.5.01.1976.msi��CVSNT��Ҫʹ��NTFS���ļ���ʽ������ȷ��CVSNT�Ϳⰲװ��NTFS�ϣ�Ȼ��CVSNT����Ŀ¼�µ�binĿ¼�����ϵͳ��path·���С�
CVSNT�����á���CVSNT Control Panel�������Server Settings��������������Ҫ����һ�¡�Run as���͡�Default�����ֱ�������CVSNT������û��ͼ�������ƣ������������ϵͳ��administrator���ɡ�
������������Ҫ����CVS�⣬ֻ�������������ѡ��Repositories����Ȼ�󴴽���صĿ⼴�ɡ�Ȼ�����ǾͿ���ͨ��:pserver:username@localhost:/reposnameȥ��������⡣
���ÿ��Ȩ�ޡ�����������Ҫ���÷���CVS����û���Ϣ������������Ҫ����µ��û����ڷ������ˣ�����һ��CVSROOT������CVSROOTΪ�����ڵ�Ŀ¼����d:\respository\cvs\respo1��Ȼ��ִ��cvs passwd����ɣ����£�
> cvs passwd �Ca �Cr administrator username
�����������һ���µķ����ض�������û���������û���ӳ��Ϊadminstrator����ȫ��������Ҫ���п��ǣ������������CVSROOT������ͨ�� cvs �Cd d:\respository\cvs\respo1 ֱ�ӷ��ʿ�Ŀ¼������cvs��passwd�������ο� cvs passwd �Chelp
����CVS ��Ĺ���Ա��ֻ�轫CVS���û�����д��CVSROOT/admin�ļ��м��ɣ�һ��һ���û����ƣ����һ���û������һ���հ��У����������ö�ȡ��д��Ȩ�ޣ�ֻ������ readers �� writers�ļ����ɡ�
������ص����ã���ο�CVSNT�������ĵ���





���ȴ�www.cvsnt.org����CVS������������ļ���Ϊcvsnt-2.5.01.1976.msi��CVSNT��Ҫʹ��NTFS���ļ���ʽ������ȷ��CVSNT�Ϳⰲװ��NTFS�ϣ�Ȼ��CVSNT����Ŀ¼�µ�binĿ¼�����ϵͳ��path·���С�
CVSNT�����á���CVSNT Control Panel�������Server Settings��������������Ҫ����һ�¡�Run as���͡�Default�����ֱ�������CVSNT������û��ͼ�������ƣ������������ϵͳ��administrator���ɡ�
������������Ҫ����CVS�⣬ֻ�������������ѡ��Repositories����Ȼ�󴴽���صĿ⼴�ɡ�Ȼ�����ǾͿ���ͨ��:pserver:username@localhost:/reposnameȥ��������⡣
���ÿ��Ȩ�ޡ�����������Ҫ���÷���CVS����û���Ϣ������������Ҫ����µ��û����ڷ������ˣ�����һ�»�������CVSROOT������CVSROOTΪ�����ڵ�Ŀ¼����d:\CVS��Ȼ��ִ��cvs passwd����ɣ����£�
> cvs passwd �Ca �Cr administrator username

C:\Documents and Settings\Administrator>cvs passwd -a -r administrator root
Adding user root
New Password:
Verify Password:

�����������һ���µķ����ض�������û���������û���ӳ��Ϊadminstrator����ȫ��������Ҫ���п��ǣ���





 

�ܽ᣺���ǵĿ�������ͨ������Windows�ģ������˽�Subversion��CVS��Windows�µİ�װ������ʹ��VCSϵͳ�ǳ��а�������װ��ϰ汾�����Ժ������ʹ��һ��IDE�������ճ������������Ĺ��߶԰汾����ϵͳ֧�ֵĲ��õĻ����ǻ��˷���ܶ��ʱ�䡣��ʵ�ϣ�����ֻ��IDEA���ɣ����������Subversion��CVS�⡢������Ŀ��Check Out��Ŀ���������ɵȵȣ��㲻��Ҫ�κοͻ�������Ϳ���Ͷ�뿪��������Щ����˵����ã�����SCM����Ա�Ϳ�������

//ע��ԭ�ĳ�����http://www.jetmaven.net/documents/j_installSubversionCVS_win.php

���������ԣ� 
���ࣺ��������İ�װ����(0) ���� �Ķ�(33) Ȧ�� �༭ ��ӡ �н��ٱ� 
ǰһƪ��Java����
��һƪ����Windowsƽ̨������CVS������[ZT]











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







action �̳� org.apache.struts.actions.DispatchAction











javascript js ��һ��frame�п�����һ��frame��ת,
����һ��ҳ����һ������ҳ���ܣ���ͨ�������ҳ����������ҳ������ת��

����ļ�
<frameset rows="80,*" frameborder="no" border="0" framespacing="0">
		<frame src="mainentry/topFrame.jsp" name="topFrame"
			noresize="noresize" id="topFrame" title="topFrame" scrolling="no" />
		<frame src="mainentry/mainFrame.jsp" name="mainFrame" id="mainFrame" scrolling="no" title="mainFrame" />
</frameset>

ҳ���ϣ�
	<TD width=90>
		<A href="javascript:void(0);" onclick="submitChange('../useragents/ListUseragent.jsp');">
			<IMG height=30 alt="" src="../images/mainentry/viewUA.gif" width=220 border=0>
		</A>
	</TD>
	
js
<SCRIPT language=javascript>
<!--
//����mainFrame��ת
function submitChange(jspUrl)
{
	parent.mainFrame.location.href=jspUrl;//�����mainFrame�ǿ���ļ��ж����
}

//����ҳ�涼��ת
function submitExit( jspUrl )
{
	parent.location.href=jspUrl;
}

//-->


</SCRIPT>	










html�е�form action
<form method="post" action="login.do">

struts��ǩ��form action
<form method="post" action="/login">







Hibernate

Hibernate is a very popular open-source Java-based object-relational mapping (JORM) engine that is easy to get up and running. It provides a rich set of features including: 

	Multiple mapping strategies 
	Transitive persistence 
	Single object to multiple table mapping 
	Collections support 
	Polymorphic associations 
	Customizable SQL queries 




��ʱ�����һЩ������Ӧ�ò��ᷢ���ģ�ȴһֱ�ڷ����������ǲ��Ǳ��������п�һ��







һ���򵥵�Hibernate����ʾ����
 
	�� Java Web ����Ӧ���У�Hibernate������ΪӦ�ó�������ݷ��ʲ㡣
������һ�����û�ע��������˵����ο���һ��Hibernate��Ӧ�ó���
�����ӵ����󣺰�ע��ҳ��������û��������롢�Ա����䷽�����Ϣ�������ݿ��С�
������þ����MVCģʽ�Ļ�����ô����Ĺ������£�

	��ͼ�㣺ע��ҳ��(register.jsp)��������Ϣҳ��(reply.jsp)
	���Ʋ㣺RegisterServlet.java
	ģ�Ͳ�/���ݷ��ʲ㣺������HibernateSessionFactory.java���־û���Register.java��
						�����ļ�hibernate.cfg.xml��ӳ���ļ�register.hbm.xml�ȵ�
	���ݿ��:����MySQL���ݿ⣬���ݱ�t_register			
	
�������õ���Hibernate3.1��JDK1.4
	
����ֲ����������HibernateӦ�ó���

1���������ݿ�
	
DROP TABLE IF EXISTS `t_register`;
CREATE TABLE `t_register` (
  `id` int(11) NOT NULL,
  `username` varchar(30) collate utf8_unicode_ci default NULL,
  `password` varchar(30) collate utf8_unicode_ci default NULL,
  `sex` varchar(10) collate utf8_unicode_ci default NULL,
  `age` int(10) default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;


2��������ͼ��ҳ��

�嵥1��register.jsp
---------------------------------------------------------------------------------------
<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>

<html>
	<head>
		<title>�û�ע��ҳ��</title>
	</head>

	<body>
		<form action="RegisterServlet" method="post">
			�û�����
			<input type="text" name="username">
			<br>
			���룺
			<input type="password" name="password">
			<br>
			�Ա�
			<input type="text" name="sex">
			<br>
			���䣺
			<input type="text" name="age">
			<br />
			<input type="submit" name="submit" value="submit">
		</form>
	</body>
</html>
---------------------------------------------------------------------------------------

�嵥2:reply.jsp
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


3����Ƴ־û���
��Ӧ�����ݿ��б��
�嵥3��Register.java
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


4�����Hibernate�����ļ�
�嵥4��hibernate.cfg.xml
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

5�����ӳ���ļ�
���ݿ��Java���������ӳ��
�嵥5��register.hbm.xml
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


6�����Hibernate�Ļ�����HibernateSessionFactory.java
	HibernateSessionFactory.java������Configurationʵ����SessionFactoryʵ����Sessionʵ�������ɺ�����
����Ӧ�ó���Ϳ���ֱ�ӵ���HibernateSessionFactory������Sessionʵ�����������ظ���дConfigurationʵ����
SessionFactoryʵ����Sessionʵ�������ɴ����ˡ�
�嵥6��HibernateSessionFactory.java
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

7����ƿ�����
	��ҳ����ȡ���ݣ�Ȼ�����HibernateSessionFactoryͨ��Hibernate���ƽ����ݲ��뵽���ݿ��С�
�嵥7��RegisterServlet.java
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
		
		//��ҳ��õ�����ֵ
		String username = request.getParameter("username");
		String password = request.getParameter("password");
		String sex = request.getParameter("sex");
		Integer age = new Integer(request.getParameter("age"));
		
		
		//��ֵ���ݸ��־���->��Ӧ�������ݿ���ı�
		Register rg = new Register();
		rg.setUsername(username);
		rg.setPassword(password);
		rg.setSex(sex);
		rg.setAge(age);
		
		Session session = HibernateSessionFactory.getSession();
		Transaction tx = session.beginTransaction();
		
		try {
			session.save(rg);//���棬׼���ύ
			tx.commit();//�ύ�����ݿ�
			session.close();
			response.sendRedirect("reply.jsp");
		} catch (Exception e) {
			e.printStackTrace();
			tx.rollback();//�����쳣�����ո��ύ������ת��rollback
		}
	}
	protected void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {	
		doGet(request, response);
	}
}
---------------------------------------------------------------------------------------

8������web.xml

�嵥8��web.xml
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

�������С�






Hibernate��ѯ
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
			user = (Users) session.createQuery(sql).uniqueResult();//�������ȷ����Ψһ�������ô�˴������⣬��Ϊ���᷵����List
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
	
	
	
Java��C++���������ϵ�����

������java��һ�������壺


class Link
{
	public int iData;
	public double dData;
	public Link next; 
}


������ȥ�ƺ����Ի󣬰�һ������Ϊ Link �����ݳ�Ա����һ������ҲΪ Link ���͵����С�
���ȥ����أ�
�������ڲ�֪��һ�� Link ����ռ�ö��ռ������£�
�����֪��һ����������ͬ���͵� Link ����ռ�ö��ռ䣿������

��Java�У�����Link����û������������һ��Link���󣬾��ܿ���������ȷʵ�����ˣ�
����ΪLink��next�ֶν�������һ��Link��������ã�������һ������
��һ�������ļ����ϵͳ�У�һ�����ò���ָ��˭����С��һ����


������C++�ж���ͬ����һ������
class Link
{
	public int iData;
	public double dData;
	public Link next; 
}
�������ʲô�����أ�





String a = new String("sasdg");



��Eclipse������python��������
1.����python ��װ��.python-2.4.2.msi.
2.��װpydev���.
��Eclipse���¹�������.��ַ:http://pydev.sf.net/updates/ .
��������zip����װ:http://sourceforge.net/projects/pydev/ .
3.���ò��Window->Preferences ��Pydev��Ŀ���и�Interpreter-Python
������ָ��Python�Ľ�����,Ҳ���ǰ�װPythonʱ,Python.exe��λ��.
ָ�����Ժ�,������Զ�����һЩ��.����Ժ�Ϳ����½�python������. 




Python����������

����eclipse�µĲ��pydev��Pydev extensions��http://pydev.sourceforge.net/��http://www.fabioz.com/pydev/

�� Windows ��, ��װ Python ������ѡ��

ActiveState ������һ�� Windows �ϵ� Python ��װ�����Ϊ ActivePython, ��������һ�������� Python ����; һ�������� Python ��̵� IDE ������һЩ Python �� Windows ��չ, �ṩ��ȫ���ķ��� Windows APIs �ķ���, �Լ� Windows ע����ע����Ϣ��

��Ȼ ActivePython ���ǿ�Դ���, ���������������ء� ActivePython ��������ѧϰ Python ʱʹ�ù��� IDE, �����б��ԭ��, �ҽ�����ʹ���������ܵ�һ��ԭ���ǣ�ActiveState ͨ��Ҫ���µ�Python �汾�����������Ժ����������İ�װ�������������ҪPython �����°汾, ���� ActivePython ��Ȼ��������°汾�Ļ�, ��Ӧ��ֱ�������� Windows �ϰ�װ Python �ĵڶ���ѡ� 

�ڶ���ѡ����ʹ���� Python ������ ���ٷ��� Python ��װ�������ǿ��������صĿ�Դ���, ���������ǿ��Ի�õ�ǰ Python �����°汾��

���� 1.1. ѡ�� 1: ��װ ActivePython
�������� ActivePython �İ�װ����:

�� http://www.activestate.com/Products/ActivePython/ ���� ActivePython ��

���������ʹ�� Windows 95, Windows 98 �� Windows ME, ����Ҫ�ڰ�װ ActivePython ֮ǰ���ز���װWindows Installer 2.0 ��

˫����װ���� ActivePython-2.2.2-224-win32-ix86.msi��

���հ�װ�������ʾ��Ϣһ������ִ�С�

������̿ռ䲻��, ������ִ��һ�����ư�װ, ��ѡ�ĵ�, ���Ǳ��߲�������������, ������ʵ���Ǽ�����14M�ռ����� 

�ڰ�װ���֮��, �رհ�װ����, �� Start->Programs->ActiveState ActivePython 2.2->PythonWin IDE�� ���������������µ���Ϣ:

PythonWin 2.2.2 (#37, Nov 26 2002, 10:24:37) [MSC 32 bit (Intel)] on win32.
Portions Copyright 1994-2001 Mark Hammond (mhammond@skippinet.com.au) -
see 'Help/About PythonWin' for further copyright information.
>>> 
���� 1.2. ѡ�� 2: ��װ���� Python.org �� Python 
�� http://www.python.org/ftp/python/ѡ�����µ� Python Windows ��װ����, ���� .exe ��װ�ļ���

˫����װ���� Python-2.xxx.yyy.exe�� �ļ����������������ص� Python ��װ�����ļ���

���հ�װ�������ʾ��Ϣһ������ִ�С�

������̿ռ䲻��, ����ȡ�� HTMLHelp �ļ�, ʵ�ýű� (Tools/), ��/�� �����׼� (Lib/test/)��

�����û�л����Ĺ���ԱȨ��, ������ѡ��, Advanced Options, Ȼ��ѡ�� Non-Admin Install�� ��ֻ�ԵǼ�ע���Ϳ�ʼ�˵��д����Ŀ�ݷ�ʽ��Ӱ�졣

�ڰ�װ���֮��, �رհ�װ����, �� Start->Programs->Python 2.3->IDLE (Python GUI)�� ���������������µ���Ϣ:

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




Ƶ��:
normal Level Channel��ͨƵ��
	������Ǹ���
		���ֶ�Ӧ��ר��
			ר����Ӧ�ĸ���

2 Level Channel
	����ֱ���Ǹ���
	
3 Level Channel
	��������Ƶ��
		��Ƶ����Ӧ�ĸ���
		
		
		
		
		
		
logic:iterate		
2007��08��17�� ������ 14:27
<logic:iterate>���������ҳ���д���һ��ѭ��,�Դ������������顢Collection��Map�����Ķ��󡣸ñ�ǵĹ���ǿ����StrutsӦ�õ�ҳ���о���ʹ�õ���
1�����������ѭ������
ʹ��<logic:iterate>��ǿ������ڱ������飬������һ��ʾ�����룺

<%
String[] testArray={"str1","str2","str3"}; 
pageContext.setAttribute("test",testArray); 
%>
<logic:iterate id="show" name="test"> 
<bean:write name="show"/> 
</logic:iterate>
������Ĵ����У����ȶ�����һ���ַ������飬��Ϊ���ʼ�������ţ������������pageContext�����У�����Ϊtest1��Ȼ��ʹ��<logic:iterate>��ǵ�name����ָ���˸����飬��ʹ��id����������ͬʱʹ��<bean:write>�����������ʾ����������Ϊ��
str1 
str2 
str3 

���⣬������ͨ��length������ָ�����Ԫ�صĸ�����������Ĵ��룺
<logic:iterate id="show" name="test" length="2" offset="1"> 
<bean:write name="show"/> 
</logic:iterate>

����length����ָ�������Ԫ�صĸ�����offset����ָ���˴ӵڼ���Ԫ�ؿ�ʼ�������˴�Ϊ1�����ʾ�ӵڶ���Ԫ�ؿ�ʼ��������Ըô�������н��Ӧ�������
str2
str3

���⣬�ñ�ǻ���һ��indexId���ԣ���ָ��һ��������ŵ�ǰ�������������ʵ�Ԫ�ص���ţ��磺


<logic:iterate id="show" name="test" length="2" offset="1" indexId="number"> 
<bean:write name="number"/>:<bean:write name="show"/> 
</logic:iterate>
����ʾ���Ϊ��
1:str2 
2:str3 



2����HashMap����ѭ������

<%
HashMap countries=new HashMap();
countries.put("country1","�й�");
countries.put("country2","����");
countries.put("country3","Ӣ��");
countries.put("country4","����");
countries.put("country5","�¹�");
pageContext.setAttribute("countries",countries); 
%>
<logic:iterate id="country" name="countries"> 
<bean:write name="country" property="key"/>:
<bean:write name="country" property="value"/> 
</logic:iterate>

��bean:write��ͨ��property��key��value�ֱ���HaspMap����ļ���ֵ������ʾ���Ϊ��
country5:�¹� 
country3:Ӣ�� 
country2:���� 
country4:���� 
country1:�й� 
�ɽ���ɿ���������δ����ӵ�˳������ʾ������������ΪHaspMap�������ŵġ�

3��Ƕ�ױ���

<%
String[] colors={"red","green","blue"};
String[] countries1={"�й�","����","����"};
String[] persons={"�ǵ�","��ʲ","���ֶ�"};
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


��һ���IDΪ��һ���name


����Ч����
0 red green blue 
1 �й� ���� ���� 
2 �ǵ� ��ʲ ���ֶ�
<logic:iterate id="it" name="list" length="2"> 
<bean write name="it"/><br/> 
</logic:iterate> 

list ����Ҫ�����Ķ��� it��list�����Ԫ�ص����� ,���и�offset���ԣ���������ʾ��ʼλ�õģ����磬offset����1���ӵڶ�λ��ʼ������ֵ��offset����0����Ĭ��ֵ 
 
 
		
		
		
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
	
	


�޸�ҳ�棺��������->Ŀ¼����->����ɰ汾->�����������	
��ҳ���϶Ը���������ͳ�ƣ��ڸ���Channel�Ͻ���ͳ�ƣ�ͬʱҲ�����˸ð汾����ܵĸ�����



Hibernate���SQL�����ı���Ҫ��־û��������һ�£����������ļ����һ�£�
�����ͺܿ��ܻ������ݿ���ı�����һ��
