2006/12/09
Eclipseʹ�ã�
����:www.eclipse.org/downloads
��������֧�ֲ��:
download.eclipse.org/eclipse/downloads
���ҳ���и�: Language_Packs


��װJDK,
Ȼ���ѹeclipse-SDK-3.2.1-win32.zip,��ѹ��Ϳ���ֱ������.
������֧�ֲ��Ҳ����ͬһĿ¼��,��ôȱʡ�����Ծ���������,
��ʱ������л���Ӣ��,���Է���һ����ݷ�ʽ������:
�Ҽ�ѡ��"����"�༭"Ŀ��"�ں������: -nl en ,����:
"C:\Program Files\Java\eclipse\eclipse.exe" -nl en
���⻹����ͨ�����ַ�ʽָ������Ŀ¼,���� -data �����ͺ���
"C:\Program Files\Java\eclipse\eclipse.exe" -nl en -data f:\workspace

�鿴 eclipse �Ƿ��ҵ��˵����ϰ�װ�� jre ����:
���"Windows->Preferences->Java->Installed JREs"
���û���ҵ�,����ѡ��"Add..."
Ȼ���Լ�ѡ��һ��"JRE home directory:"



�����һ��Eclipse��Java����.

File->New->Project...
ѡ�� Java Project �󣬵�� Next�����빤�����֣�hello����� Finish ���ʹ�����һ�����̡�
�����Workspace�п���hello����ַ���û��
�Ҽ��������File->New->Source Folder������src�����Finish�������ͽ�����һ��Source�ļ��С�
�Ҽ�������Ǹս����� src �ļ��� ��ѡ��New->Class,���������֣�hello����� Finish��
���ʱ����Eclipse���м�����˱༭���棬����һ�����ݣ�
public class hello {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.println( "Hello world! My Java!" );
	}

}

���棬���ڿ��Ա����ˡ�
�����Workspace�п��� hello.java ����ַ���û��
�Ҽ��������ѡ�� Run as -> 1 Java Application �����Ϳ��Ա�����
��Eclipse�����²���Console�Ի����������
Hello world! My Java!
�ǲ���


�õ�����jar����ӵ�eclipse������
Project->Properties->Java Build Path->Libraries ѡ�� Add Extenal JARs��Ȼ��Ϳ���ѡ�������jar��

Eclipse�Զ��������������Ǳ������ܿ�ľͿ�����ɣ�
������Ϊÿ�����Ǳ����ļ���ʱ��Eclipse�Ͱ������Զ������ˡ�
��Ȼ����Ҳ����ȡ������Զ��������ܣ�
ȡ�� Project->Build Automatically ǰ��Ĺ����Ϳ���ȡ���Զ����빦��

���ǻ����������������м��ļ���ѡ�� Project->Clean �Ϳ�����


Java�ĵ��ԣ�
{
	���öϵ㣺
	�ڱ༭�������߿���˫���Ϳ��Դ�����ɾ���ϵ�
	���߱༭�������߿����һ�ѡ��Toggle breakpoint�����öϵ�.
	ѡ�� Debug As �Ϳ��Ե��Գ�����

	�쿴����ֵ:
	ѡ�б���Ȼ���һ�ѡ��Watch�Ϳ�����,����ѡ�� Window->Show View->Display,
	��Display������������Ҫ�鿴�ı����Ϳ�����.

	�ӵ���״̬�ص�ԭʼ�༭״̬:��ֹͣ��������,
	Ȼ��ѡ�����Ͻǵ�Java��ǩ�Ϳ��Իص�Java Perspective

	���������ϵ㣺
	�ڶϵ����һ���ѡ�� breakpoint Properties->Enable Condition,
	Ȼ����Enable Condition�µ�����������������Ϳ����ˡ�

	�쳣�ϵ㣺
	��debug��ͼ�е�Breakpoints��������һ��Add Java Exception breakpoint��ť��
	������ӳ����쳣�Ķϵ㣬������������쳣ʱ�����ڳ����쳣�ĵط�ͣ����
}


��Eclipse��ʾ�����г��ִ�����߾����ǣ������ŵ���Ǹ���ɫ�Ĳ����ɫ��С������
�����ᵯ��һЩ���õı༭ѡ�����˫����Ӧ��ѡ�����ٰ����ǽ����Щ����򾯸档

�Զ�����set��get�����Ĺ��ܣ�
{
	��������������һ���ࣺ
	public class PersonInfo {
		String name;
		int age;
	}
	����������Ϊ�����set��get��������ô����ѡ��Source->Generate Getters and Setters...
	ѡ��󣬾Ϳ��Կ���EclipseΪ����������set��get���������£�
	public class PersonInfo {
		String name;
		int age;
		public int getAge() {
			return age;
		}
		public void setAge(int age) {
			this.age = age;
		}
		public String getName() {
			return name;
		}
		public void setName(String name) {
			this.name = name;
		}
	}

	���ﻹ����Ϊ�������ɹ��캯������ô����ѡ��Source->Generate Constructor using Fields...
	ѡ��󣬾Ϳ��Կ���EclipseΪ���������˹��췽�������£�
	public class PersonInfo {
		String name;
		int age;
		public PersonInfo(String name, int age) {
			super();
			this.name = name;
			this.age = age;
		}
		public int getAge() {
			return age;
		}
		public void setAge(int age) {
			this.age = age;
		}
		public String getName() {
			return name;
		}
		public void setName(String name) {
			this.name = name;
		}
	}

	Ҳ�����������ظ���Ĺ��캯��Source->Generate Constructor From superclass...
}

�Զ�����JavaDoc
{
	/**		ע�����ڴ˴���Enter��
	public PersonInfo(String name, int age) throws IOException {
		super();
		this.name = name;
		this.age = age;
	}

	�ͻ��Զ�����������ע�ͣ�
	/**
	 *
	 * @param name
	 * @param age
	 * @throws IOException
	 */
	public PersonInfo(String name, int age) throws IOException {
		super();
		this.name = name;
		this.age = age;
	}
}

������Զ���ɣ�Alt+/
�����ʽ�����ܣ�Ctrl+Shift+F
	��������Զ����Լ��ĸ�ʽ��window->Properties

jar������Դ���룺Attach Source
���ٴ��ļ���Navigate->Open Type...
��һ����ļ̳й�ϵ���ڱ༭����ѡ����࣬�Ҽ�ѡ��Open Type Hierarchy��
�򿪷�������,��������Щ�ط�������:�༭����ѡ��÷������Ҽ�ѡ��Open Call Hierarchy��

Eclipse�߼�����:Զ�̵���
JPDA

Eclipse����İ�װ:
1. ���߰�װ:
һ��ѡ��Help->Software Updates->..........
֮�����������ַ�Ϳ�����
2. ֱ�ӽ�ѹ��װ�����û�а�װ�ɹ����Ϳ��Խ�eclipse�İ�װĿ¼�µ�configuration\org.eclipse.updateĿ¼ɾ���ͻ���eclipseȥ���²����
3. ��link�ķ�ʽ��װ
�ȰѲ����ѹ��ͬһĿ¼�磺
d:\Myplugins
һ��������Ӧ��Ŀ¼�ṹ,��Lomboz:
Lomboz\eclipse\features
Lomboz\eclipse\plugins

��eclipse��Ŀ¼�н���һ��linksĿ¼
������һ��Lomboz.txt ��������
path=D:\\Myplugins\\Lomboz

����
path=D:/Myplugins/Lomboz
��ע�������Ƿ�б��/��������\��
˵����
	1. ������Էֱ�װ�ڶ���Զ����Ŀ¼�С�
	2. һ���Զ���Ŀ¼���԰�װ��������
	3. link�ļ����ļ�������չ������ȡ�������ƣ�����ddd.txt��myplugin�����ԡ�
	4. link�ļ���path=���¼��path·���ָ�Ҫ��\\����/
	5. ��linksĿ¼Ҳ�����ж��link�ļ���ÿ��link�ļ��е�path����������Ч��
	6. ���Ŀ¼����ʹ�����·����
	7. ������linksĿ¼�н���һ����Ŀ¼��ת����ʱ���õĲ��������Ŀ¼�У��ӿ�eclipse������
	8.  �����װ�󿴲����������eclipse Ŀ¼�µ�configurationĿ¼ɾ�����������ɡ�


���ò��:
���ݿ����:SQLExplorer
GUI:SWT-Designer
������:Jode
J2EE:Lomboz,MyEclipse
XML:XMLBuddy




public class hello {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.println( "Hello world! My Java!" );
	}

}

���棬���ڿ��Ա����ˡ�
�����Workspace�п��� hello.java ����ַ���û��
�Ҽ��������ѡ�� Run as -> 1 Java Application �����Ϳ��Ա�����
��Eclipse�����²���Console�Ի����������
Hello world! My Java!
�ǲ���









2006/12/17
����Java������---1
JDK��Java Develop Kit ����Java�������߰�
JRE��Java Runtime Environment����Java���л���

J2SE��http://java.sun.com/j2se/1.4.2/download.html
J2EE��
J2ME��

http://java.sun.com/j2se/1.4.2/download.html
������Java 2 Platform��Document����
���⣬http://java.sun.com/docs/books/tutorial/information/download.html����ָ��

����ָ�ϺͰ����ĵ��ǵ������ص�.



Java������Sun��˾��һ����Green����Ŀ����ԭ�ȵ�Ŀ����Ϊ�������ѵ��Ӳ�Ʒ����һ���ֲ�ʽ����ϵͳ���������ǿ��԰�E-mail��������䡢���ӻ��ȼ��õ����������ǽ��п��ƣ������ǽ�����Ϣ��������ʼ��׼������C++����C++̫���ӣ���ȫ�Բ������C++������һ���µ�����Oak��Java��ǰ����Oak��һ����������ľ��ɶ���ȫ�����ԣ�Sun��˾���Դ�Ͷ��һ������ʽ������Ŀ���������SGI��ܡ�������Oak�����޼ҿɹ飬ǡ����ʱMark Ardreesen������Mosaic��Netscape������Oak��Ŀ���Ա��������Java�� �� ��HotJava� �������õ���Sun��˾��ϯִ�й�Scott McNealy��֧�֣�������Java�� ��Internet�� Java��ȡ��Ҳ��һ��Ȥ�ţ���һ�죬�� λJava��Ա��Ļ�Ա�������۸�����µ�����ȡʲô���֣���ʱ�������ڿ��ȹݺ���Java(צ��)�� �ȣ���һ�������һ��˵�ͽ�Java�� �����õ��������˵����ͣ����ǣ�Java������־����������ˡ�

��ΪJava��
�򵥵�
{
	Java�����Ϊ�Լ��õ������м��ɿ��ƶ���Ƶ�һ�����ԣ��������������ˡ�Java���Եļ�����Ҫ�������������棺
	             1��Java�ķ��������C++�����C++����Ա���νӴ�Java���ԣ��ͻ�е�����Ϥ����ĳ�������Ͻ���Java������C��C++���Ե�һ�����֣���ˣ�C++����Ա���Ժܿ������Java��̼�����
	             2��Java������C++������������������һЩ���ԣ���ָ�롢�ṹ��ö���Լ��ڴ����ȡ�
	             3��Java�ṩ�˷ḻ����⣬���԰������Ǻܷ���Ŀ���Java����
}
��������
{
����������˵��Java����Ҫ�����ԣ�������֧�ּ̳С����ء���̬�������������ԡ�Java���Ե��������ȫ��������,����֧������C����������������̵ĳ�����Ƽ�����
}
��׳��
{
Java�����ڼ������ڱ��������ʱ�Ĵ���JavaҲ��һ��ǿ���͵����ԣ������ͼ���C++��Ҫ�ϸ����ͼ��������Ǽ�����࿪�����ڳ��ֵĴ���Java�Լ������ڴ�����ṩ�������ڴ���ջ��ƣ���Ч�ı�����C++����ͷ�۵��ڴ�й©���⡣

}
��ȫ��
{
Java�İ�ȫ�Կɴ���������õ���֤��һ�� �棬��Java�����ɾ����ָ����ͷ��ڴ��C++���ܣ������˷Ƿ��ڴ��������һ���棬ͨ��Java�İ�ȫ��ϵ�ܹ���ȷ��Java����İ�ȫ�ԡ������Ǵ���������Java�����ڱ���ִ��ʱ��Java�İ�ȫ�ܹ���ȷ������Ĵ��벻������������Ǳ��ؼ��������Դ�����磺ɾ���ļ������ʱ���������Դ�Ȳ������Ǳ���ֹ�ġ�
}
���͵�
{
Java�����ǽ���ִ�еģ�����ʹ��Java��������Java���������ֽ��룬����һ���м���룬Ȼ����Java����������ִ�С���C++�����Ǳ���ִ�еģ�C++������뱻����Ϊ���ػ���ָ�Ȼ��ִ�С�
}
��ƽ̨�޹ص�
{
Java��Ϊһ���������ԣ���Դ���뱻�����һ�ֽṹ�������м��ļ���ʽ��ֻҪ��Java����ϵͳ�Ļ�������ִ�������м���롣JavaԴ���򱻱����һ��������޹ص��ֽ����ʽ����Java����������С�
}
���̵߳�
{
Java���Ե�һ����Ҫ���Ծ��������Լ�֧�ֶ��̵߳ĳ�����ơ����߳̾ͺ���������һ�����ӣ������һ��������������ӡ��ͺ����̣߳���ô����Ҫ�������棬�������������4�������ȣ����������5�����������ӡ��ڳ����п���5���̣߳�����1���������棬����4���˷ֱ���4�������ȣ���ô�����ַ�ʽЧ�ʵĸߵͣ����Ŵ�Ҷ������ֳ�����
}
��̬������
{
Java�Ķ�̬�����������������Ʒ�������չ�����������̬��װ�����й���������Ҫ���࣬�������ǲ���C++���Խ�������������������޷�ʵ�ֵġ���C++������ƹ����У�ÿ������������һ��ʵ��������һ����Ա������ ���ø�����������඼�������±��룬���򽫵��³��������Java�����¼��������ȡ��ʩ�����������⡣Java���������ǽ���ʵ�������ͳ�Ա���������ñ���Ϊ��ֵ���ã����ǽ�����������Ϣ���ֽ����б������������ݸ������������ɽ���������ɶ�̬������󣬽�����������Ϣת��Ϊ��ֵƫ������һ���ڴ洢�������ɵĶ����ڱ�������о����������ӳٵ�����ʱ�ɽ�����ȷ���������������еı����ͷ������и���ʱ�Ͳ�����Ӱ���ִ�Ĵ��롣 ����ִ���ֽ���ʱ�����ַ�����Ϣ�Ĳ��Һ�ת�����̽���һ���µ����ֳ���ʱ�Ž���һ�Σ�����������ȫ��ִ�С�������ʱȷ�����õĺô��ǿ���ʹ���ѱ����µ��࣬�����ص��Ļ�Ӱ��ԭ�еĴ��롣���������������������һϵͳ�е�ĳһ�࣬�����������Ҳ�������ɵضԸ�����и��£�������ʹ�κ����ø���ĳ��������Java������ʹ��һ�������Ļ�ȫ��Э��ķ�����������ϵͳ����Java����ʱ�����˲�֪��������ĳ���Java���Զ�����������Ҫ�Ĺ��ܳ���
}

Java�Ŀ�ƽ̨��ͨ��Java�������JVM����ʵ�ֵġ�Java�Ŀ�ƽ̨��ͨ��Java�������JVM����ʵ�ֵġ�

JavaԴ�ļ��ı������
             JavaӦ�ó���Ŀ������ڰ������롢���ء����ͺ�ִ�м������֡�Java�������JavaԴ������ΪJVM��ִ�д��롪�ֽ��롣��һ�������ͬC/C++�ı�����Щ��ͬ����C��������������һ������Ĵ���ʱ���ô�����Ϊ��ĳһ�ض�Ӳ��ƽ̨���ж������ġ���ˣ��ڱ�������У��������ͨ��������жԷ��ŵ�����ת��Ϊ�ض����ڴ�ƫ�������Ա�֤�������С�Java������ȴ�����Ա����ͷ��������ñ���Ϊ��ֵ���ã�Ҳ��ȷ������ִ�й����е��ڴ沼�֣����ǽ���Щ����������Ϣ�������ֽ����У��ɽ����������й����д����ڴ沼�֣�Ȼ����ͨ�������ȷ��һ���������ڵĵ�ַ����������Ч�ı�֤��Java�Ŀ���ֲ�ԺͰ�ȫ�ԡ�

Java��������ִ�й���
              ����JVM�ֽ���Ĺ������ɽ���������ɵġ�����ִ�й��̷��������У������װ�롢�����У��ʹ����ִ�С�װ�����Ĺ����ɡ���װ��������class loader����ɡ���װ��������װ������һ��������Ҫ�����д��룬��Ҳ������������е������̳е���ͱ�����õ��ࡣ����װ����װ��һ����ʱ�����౻�����Լ������ֿռ��С�����ͨ�����������Լ����ֿռ�������࣬��֮��û�������취����Ӱ�������ࡣ�ڱ�̨������ϵ������඼��ͬһ��ַ�ռ��ڣ������д��ⲿ�������࣬����һ���Լ����������ֿռ䡣��ʹ�ñ�����ͨ��������ͬ�����ֿռ��ýϸߵ�����Ч�ʣ�ͬʱ�ֱ�֤��������ⲿ�������಻���໥Ӱ�졣��װ�������г�����Ҫ��������󣬽��������ȷ��������ִ�г�����ڴ沼�֡�������Ϊ��������ͬ�ض��ĵ�ַ�ռ佨����Ӧ��ϵ����ѯ��ͨ������һ�׶�ȷ��������ڴ沼�֣�Java�ܺõؽ�����ɳ���ı��ʹ������������⣬ͬʱҲ��ֹ�˴���Ե�ַ�ķǷ����ʡ�
              ��󣬱�װ��Ĵ������ֽ���У�������м�顣У�����ɷ��ֲ�����ջ������Ƿ���������ת���ȶ��ִ���ͨ��У��󣬴���㿪ʼִ���ˡ�


Java�ֽ��������ִ�з�ʽ
            1����ʱ���뷽ʽ���������Ƚ��ֽ������ɻ����룬Ȼ����ִ�иû����롣         2������ִ�з�ʽ��������ͨ��ÿ�ν��Ͳ�ִ��һС�δ��������Java�ֽ���� ������в����� ����ͨ�����õ��ǵڶ��ַ���������JVM������������㹻������ԣ���ʹ�ý��ֽ��뷭��Ϊ��������Ĺ������нϸߵ�Ч�ʡ�������Щ�������ٶ�Ҫ��ϸߵ�Ӧ�ó��򣬽������ɽ�Java�ֽ��뼴ʱ����Ϊ�����룬�Ӷ��ܺõر�֤��Java����Ŀ���ֲ�Ժ͸����ܡ�


JVM�������
             JVM�����Ŀ�����ṩһ�����ڳ����������ļ����ģ�ͣ�Ϊ���ͳ��򿪷���Ա�ṩ�ܺõ�����ԣ�ͬʱҲȷ��Java������ڷ��ϸù淶���κ�ϵͳ�����С�JVM����ʵ�ֵ�ĳЩ��������˾���Ķ��壬�ر��Ƕ�Java��ִ�д��룬���ֽ���(Bytecode)�ĸ�ʽ��������ȷ�Ĺ����һ������������Ͳ��������﷨����ֵ����ʶ������ֵ��ʾ��ʽ���Լ�Java���ļ��е�Java���󡢳����������JVM�Ĵ洢ӳ����Щ����ΪJVM������������Ա�ṩ���������Ϣ�Ϳ���������Java�������ϣ����������Ա����������ʹ��Java�����ɡ�
            JVM��ΪJava�ֽ��붨���һ�ֶ����ھ���ƽ̨�Ĺ����������Javaƽ̨�����ԵĻ�����



Java����ִ����C/C++����ִ�еĶԱȷ���
             �����JavaԴ������������ǵ�C++Դ����JavaԴ�����������ɵ��ֽ�����൱��C++Դ���������80x86�Ļ����루�����Ƴ����ļ�����JVM������൱��80x86�����ϵͳ��Java�������൱��80x86CPU����80x86CPU�����е��ǻ����룬��Java�����������е���Java�ֽ��롣
             Java�������൱������Java�ֽ���ġ�CPU�������á�CPU������ͨ��Ӳ��ʵ�ֵģ����������ʵ�ֵġ�Java������ʵ���Ͼ����ض���ƽ̨�µ�һ��Ӧ�ó���ֻҪʵ�����ض�ƽ̨�µĽ���������Java�ֽ������ͨ�������������ڸ�ƽ̨�����У�����Java��ƽ̨�ĸ�������ǰ�������������е�ƽ̨�¶�����ӦJava������������Ҳ��Java�����������е�ƽ̨�¶������е�ԭ����ֻ������ʵ����Java�����������ƽ̨�����С�




javac����Java������
java����Java������



D:\workspace\Java>cd lesson1

D:\workspace\Java\lesson1>dir
 ������ D �еľ��� LOCAL
 ������к��� CB30-2D7F

 D:\workspace\Java\lesson1 ��Ŀ¼

2006-12-17  19:49    <DIR>          .
2006-12-17  19:49    <DIR>          ..
2006-12-17  19:50                 7 hello.java.bak
2006-12-17  19:53                20 hello.java
               2 ���ļ�             27 �ֽ�
               2 ��Ŀ¼  1,304,494,080 �����ֽ�

D:\workspace\Java\lesson1>javac hello.java

D:\workspace\Java\lesson1>dir
 ������ D �еľ��� LOCAL
 ������к��� CB30-2D7F

 D:\workspace\Java\lesson1 ��Ŀ¼

2006-12-17  19:49    <DIR>          .
2006-12-17  19:49    <DIR>          ..
2006-12-17  19:50                 7 hello.java.bak
2006-12-17  19:53                20 hello.java
2006-12-17  19:54               184 hello.class
               3 ���ļ�            211 �ֽ�
               2 ��Ŀ¼  1,304,477,696 �����ֽ�

D:\workspace\Java\lesson1>java hello.class
Exception in thread "main" java.lang.NoClassDefFoundError: hello/class

D:\workspace\Java\lesson1>

���û�������:
����"�ҵĵ���->����->�߼�->��������(N)->����"�������и�path����,
�����ǿ�ִ�г���Ļ���·��,
������������ʾ��������:path�鿴ϵͳ��path��������
D:\workspace\Java\lesson1>path
PATH=M:\WINDOWS\system32;M:\WINDOWS;M:\WINDOWS\System32\Wbem;M:\Program Files\Mi
crosoft Visual Studio\Common\Tools\WinNT;M:\Program Files\Microsoft Visual Studi
o\Common\MSDev98\Bin;M:\Program Files\Microsoft Visual Studio\Common\Tools;c:\Pr
ogram Files\Visual Studio\VC98\bin;C:\Program Files\Java\jdk1.5.0_08\bin


��ͬһ���ļ��п��Ա�д�����,
�ڱ����ʱ��,Ϊÿ���൥������һ��*.class�����ļ�,
���ڿ������ͳ���ʱ,������ܶ����ļ�,�����Ͳ�̫������.
Ϊ��,sun��˾�ṩ jar.exe �������,�����Խ��ܶ����ļ������һ��jar��,
����jar������ͨ��winrar���ߴ�,

D:\workspace\Java\lesson1>jar
�÷���jar {ctxu}[vfm0Mi] [jar-�ļ�] [manifest-�ļ�] [-C Ŀ¼] �ļ��� ...
ѡ�
    -c  �����µĴ浵
    -t  �г��浵���ݵ��б�
    -x  չ���浵�е������ģ������еġ��ļ�
    -u  �����Ѵ��ڵĴ浵
    -v  ������ϸ�������׼�����
    -f  ָ���浵�ļ���
    -m  �������Ա����ļ��ı�����Ϣ
    -0  ֻ�洢��ʽ��δ��ZIPѹ����ʽ
    -M  ��������������嵥��manifest���ļ�
    -i  Ϊָ����jar�ļ�����������Ϣ
    -C  �ı䵽ָ����Ŀ¼�����Ұ��������ļ���
���һ���ļ�����һ��Ŀ¼���������ݹ鴦��
�嵥��manifest���ļ����ʹ浵�ļ�������Ҫ��ָ������'m' �� 'f'��־ָ������ͬ˳��

ʾ��1��������class�ļ��浵��һ����Ϊ 'classes.jar' �Ĵ浵�ļ��У�
       jar cvf classes.jar Foo.class Bar.class
ʾ��2����һ�����ڵ��嵥��manifest���ļ� 'mymanifest' �� foo/ Ŀ¼�µ�����
           �ļ��浵��һ����Ϊ 'classes.jar' �Ĵ浵�ļ��У�
       jar cvfm classes.jar mymanifest -C foo/ .


D:\workspace\Java\lesson1>jar cvf Lesson1.jar hello.class Welcome.class
�����嵥(manifest)
���ӣ�hello.class(����= 184) (д��= 155)(ѹ���� 15%)
���ӣ�Welcome.class(����= 186) (д��= 157)(ѹ���� 15%)

D:\workspace\Java\lesson1>dir
 ������ D �еľ��� LOCAL
 ������к��� CB30-2D7F

 D:\workspace\Java\lesson1 ��Ŀ¼

2006-12-17  19:49    <DIR>          .
2006-12-17  19:49    <DIR>          ..
2006-12-17  20:04               184 hello.class
2006-12-17  20:03                20 hello.java.bak
2006-12-17  20:04                46 hello.java
2006-12-17  20:04               186 Welcome.class
2006-12-17  20:10               889 Lesson1.jar
               5 ���ļ�          1,325 �ֽ�
               2 ��Ŀ¼  1,304,428,544 �����ֽ�

D:\workspace\Java\lesson1>cd .

D:\workspace\Java\lesson1>cd ..

D:\workspace\Java>jar cvf Lesson1.jar lesson1
�����嵥(manifest)
���ӣ�lesson1/(����= 0) (д��= 0)(�洢�� 0%)
���ӣ�lesson1/hello.class(����= 184) (д��= 155)(ѹ���� 15%)
���ӣ�lesson1/hello.java.bak(����= 20) (д��= 22)(ѹ���� -10%)
���ӣ�lesson1/hello.java(����= 46) (д��= 37)(ѹ���� 19%)
���ӣ�lesson1/Welcome.class(����= 186) (д��= 157)(ѹ���� 15%)
���ӣ�lesson1/Lesson1.jar(����= 889) (д��= 475)(ѹ���� 46%)


{
	hello.java:

	class Hello
	{

	}

	public class Welcome
	{

	}


	D:\workspace\Java\lesson1>javac hello.java
	hello.java:6: �� Welcome �ǹ����ģ�Ӧ����Ϊ Welcome.java ���ļ�������
	public class Welcome
	       ^
	1 ����

	������Կ���,����������Ϊpublic������ļ�,�ļ�����Ҫ������Ϊ���������.
	ÿ���ļ���ֻ����һ������Ϊpublic����,
	�õ����ڽ��ļ�����Ϊ Welcome.java�ļ������޸�����:
	public class Welcome
	{
		/*public static void main( String[] args )
		{
		}
		*/
	}

	D:\workspace\Java\lesson1>javac Welcome.java

	D:\workspace\Java\lesson1>java Welcome.class
	Exception in thread "main" java.lang.NoClassDefFoundError: Welcome/class

		���������ʱ����ʾû��mian����,��ͺ���C/C++��һ��,����Ҫ��main����.

		�����޸�Դ�ļ����£�

	public class Welcome
	{
		public static void main( String[] args )
		{
			System.out.print("Hello world!\n");
			System.out.println("http://blog.csdn.net/zieckey");
		}
	}


	D:\workspace\Java\lesson1>javac Welcome.java

	D:\workspace\Java\lesson1>java Welcome.class
	Exception in thread "main" java.lang.NoClassDefFoundError: Welcome/class

	D:\workspace\Java\lesson1>java Welcome
	Hello world!
	http://blog.csdn.net/zieckey

	���Կ������н����
	���ﻹ���Կ���������ʱ���� java Welcome.class������java Welcome
}


Java������������
{
	public class Welcome
	{
		public static void main( String[] args )
		{
			/*
			System.out.print("Hello world!\n");
			System.out.println("http://blog.csdn.net/zieckey");
			*/
			/*
			java�ṩ��8����������
			byte 	b;
			int  	i;
			long	l;
			char   	ch;
			float 	f;
			double  d;
			boolean bool;
			*/
			byte b;//����b��һ��8λ���������Ա�ʾ��-128~127֮����κ�����
			b = 5;
			b = b*3 ;
			println( b );//�����println�����Զ�ʶ����������ĸ�ʽ��
		}
	}

	D:\workspace\Java\lesson1>javac Welcome.java
	Welcome.java:21: ������ʧ����
	�ҵ��� int
	��Ҫ�� byte
	                b = b*3 ;
	                     ^
	Welcome.java:22: �Ҳ�������
	���ţ� ���� println(byte)
	λ�ã� �� Welcome
	                println( b );//�����println�����Զ�ʶ����������ĸ�ʽ��
	                ^
	2 ����

	��������Ϊ��byte�����ڲ�������ʱ��Ϊ�˱�֤����ת��Ϊint���ͣ�
	���������C/C++��������һ�����棬��������Ǵ�������java�İ�ȫ����һ������

	�����޸�һ��Դ�ļ���
	��
	b = b*3 ;
	��Ϊ��
	b = (byte)b*3 ;
	��ȥ������,���Է���,����ͬ���Ĵ���.

	public class Welcome
	{
		public static void main( String[] args )
		{
			/*
			System.out.print("Hello world!\n");
			System.out.println("http://blog.csdn.net/zieckey");
			*/
			/*
			java�ṩ��8����������
			byte 	b;//����b��һ��8λ���������Ա�ʾ��-128~127֮����κ�����
			short 	s;//2�ֽڵ��з��ŵ�����.���Ա�ʾ��-32768~32767֮����κ�����
			int  	i;//4�ֽڵ��з��ŵ�����
			long	l;//8�ֽڵ��з��ŵ�����
			char   	c;//2���ֽڵ��޷�������,���Ա�ʾ��0~65535֮����κ�����
			float 	f;//4�ֽڵ�
			double  d;//8�ֽڵ�
			boolean bool;//ֻ���� true �� false
			*/
			byte b;//����b��һ��8λ���������Ա�ʾ��-128~127֮����κ�����
			b = 5;
			b = (byte)( b * 3 ) ;
			System.out.println( b ); //�����println�����Զ�ʶ����������ĸ�ʽ��
		}
	}

	��������:
	D:\workspace\Java\lesson1>javac Welcome.java

	D:\workspace\Java\lesson1>java Welcome
	15

	D:\workspace\Java\lesson1>

	��float����������ֵʱ:
	float f = 1.3;
	����ᱨ��:

	D:\workspace\Java\lesson1>javac Welcome.java
	Welcome.java:38: ������ʧ����
	�ҵ��� double
	��Ҫ�� float
	                float f = 1.3;
	                          ^
	1 ����

	��Java��С���ĳ�������Ϊ��һ��double����,
	����Ӧ��������float������ֵ.
	float f = 1.3f;

	��boolean������ֵʱֻ��ȡ����ֵ:
	 bool = true;���� bool = false;

	D:\workspace\Java\lesson1>javac Welcome.java
	D:\workspace\Java\lesson1>java Welcome
	true

	���������жϵ�ʱ��,Ҳֻ���� true �� false
	if ( 1 )
	{
	}
	������д��������.

	D:\workspace\Java\lesson1>javac Welcome.java
	Welcome.java:45: �����ݵ�����
	�ҵ��� int
	��Ҫ�� boolean
	                if ( 1 )
	                     ^
	1 ����
}

Java���� :
{
	�������C/C++�����������: int num[5];
	int num[5];//���ﲻ��Ԥ��д������Ŀռ��С��

	int num[];	//OK
	num = new int[5];  //�ȶ��壬�����ռ䡣

	//��Java���Ƽ�ʹ�� int[] num;	���ַ�ʽ�������飬������ֱ�����ˣ�
	//�Ƕ�����һ��int���͵����� num ��
	//���int num[];��ô����num�Ǳ����ػ�num[]�Ǳ�����
	int[] num;	//int [] num;	int []num;	//[]��λ��û�й�ϵ
	num = new int[5];  //�ȶ��壬�����ռ䡣

	//�����ڶ����ʱ���ʼ��
	int []num={1,2,3};//OK

	//����
	int []num2 = new int[]{1,2,3};//OK
	���ǲ���ָ���ռ��С
	//int []num3 = new int[3]{1,2,3};//ERROR

	������ĸ�ֵ:
	{
		int [] num3;
		num3 = new int[3];
		num3[0] = 1;
		num3[1] = 12;
		num3[2] = 13;

		System.out.println( num3[0] );
		System.out.println( num3[1] );
		System.out.println( num3[2] );
	}


	��ά����:
	/* OK
	int [][] a;
	a = new int [3][4];//3��4��
	a[0][1] = 12;
	a[2][3] = 14;
	*/

	���ڶ�ά����,Java��ÿ�е��������Բ����,��ͺ�C/C++�е�ָ�������Ϊ����
	����ڴ洢�ַ����ȽϷ��㡣

	��ά�����ʼ��
	{
		//int [][] c = new int [][]{1,2,3,4,5,6};//ERROR
		//int [][] c = new int [2][]{{1,2,3},{4,5,6}};//Error
		int [][] c = new int [][]{{1,2,3},{4,5,6}};//OK
		int [][] d = {{1,2,3},{4,5,6}};//OK
		int [][] e = {{1,2,3},{4,5},{6}};//OK

		System.out.println( e[0][2] );
		System.out.println( e[0][1] );
		System.out.println( e[0][0] );
		System.out.println( e[1][1] );
		System.out.println( e[1][0] );
		System.out.println( e[2][0] );
	}

	++ �� -- ������ͬC/C++����һ���ġ�
	{
		/*
		int i =3 ;
		int count;
		count = (i++) + (i++) + (i++);
		System.out.println( i );  //���6
		*/
		/*
		int i =3 ;
		int count;
		count = (++i) + (++i) + (++i);
		System.out.println( i );  //���6
		System.out.println( count );//���15
		*/
	}

	�������
	/*
		if(true)
		{
		}

		while(true)
		{
		}

		do
		{
		}while(true);

		for(int i=0;i<10;i++)
		{
		}

		*/
}



Lesson2
λ����
{
	class Test
	{
		public static void main(String args[])
		{
			int i = 0xffffffff;
			int c = i<<2; //����������
			System.out.println(i);
			System.out.println(Integer.toHexString(c));//��c���������16������ʽ���fffffffc

			c = i>>2;//����������
			System.out.println(Integer.toHexString(c));//��c���������16������ʽ���ffffffff
			c = i>>>2;//������������
			System.out.println(Integer.toHexString(c));//��c���������16������ʽ���3fffffff

		}
	}
}

��������̷�����
{
	//Point.java
	class Point
	{
		int x,y;
		void output()
		{
			System.out.println(x);
			System.out.println(y);
		}
		public static void main(String args[])
		{
			Point pt;
			pt = new Point();
			Point.x = 20;
			Point.y = 20;
			pt.output();
		}
	}

	��������ڱ���ʱ���ִ���
	E:\study\JAVA\Java-Study\JavaLesson\Lesson2\temp>javac Point.java
	Point.java:13: �޷��Ӿ�̬�����������÷Ǿ�̬ ���� x
	                Point.x = 20;
	                     ^
	Point.java:14: �޷��Ӿ�̬�����������÷Ǿ�̬ ���� y
	                Point.y = 20;
	                     ^
	2 ����
	�޸ĳ���

	//Point.java
	class Point
	{
		static int x,y; //ע������ĸı�
		void output()
		{
			System.out.println(x);
			System.out.println(y);
		}
		public static void main(String args[])
		{
			Point pt;
			pt = new Point();
			Point.x = 20;
			Point.y = 20;
			pt.output();
		}
	}
	�����Ͳ������

}





2006/12/20
Lesson3

Ϊ�˱��ڹ���������ϵͳ����Ŀ�ڶ���࣬�����������ͻ�����⣬Java�����˰���package����

//Test.java
package zieckey;
class Test
{
	public static void main( String[] args )
	{
		System.out.println( "zieckey test!");
	}
}

E:\study\JAVA\Java-Study\JavaLesson\Lesson3>javac Test.java

E:\study\JAVA\Java-Study\JavaLesson\Lesson3>java Test
Exception in thread "main" java.lang.NoClassDefFoundError: Test (wrong name: zieckey/Test)
        at java.lang.ClassLoader.defineClass1(Native Method)
        at java.lang.ClassLoader.defineClass(Unknown Source)
        at java.security.SecureClassLoader.defineClass(Unknown Source)
        at java.net.URLClassLoader.defineClass(Unknown Source)
        at java.net.URLClassLoader.access$100(Unknown Source)
        at java.net.URLClassLoader$1.run(Unknown Source)
        at java.security.AccessController.doPrivileged(Native Method)
        at java.net.URLClassLoader.findClass(Unknown Source)
        at java.lang.ClassLoader.loadClass(Unknown Source)
        at sun.misc.Launcher$AppClassLoader.loadClass(Unknown Source)
        at java.lang.ClassLoader.loadClass(Unknown Source)
        at java.lang.ClassLoader.loadClassInternal(Unknown Source)
����ֱ�����л�������Ǳ�����ϰ�����

E:\study\JAVA\Java-Study\JavaLesson\Lesson3>java zieckey.Test
Exception in thread "main" java.lang.NoClassDefFoundError: zieckey/Test

�������ǻ����ʵ���ϣ����������ǵ��ļ�ϵͳһ�������������ڵ�ǰĿ¼�£�
�½�һ���԰�����zieckey���������ļ��У�Ȼ��Test.class�ŵ��á�zieckey���������ļ����С�

E:\study\JAVA\Java-Study\JavaLesson\Lesson3>mkdir zieckey

E:\study\JAVA\Java-Study\JavaLesson\Lesson3>copy Test.class zieckey
�Ѹ���         1 ���ļ���

E:\study\JAVA\Java-Study\JavaLesson\Lesson3>java zieckey.Test
zieckey test!

����
E:\study\JAVA\Java-Study\JavaLesson\Lesson3>java zieckey/Test
zieckey test!

���ˣ����ھͳɹ��ˡ�

���ǻ����Ը����������޶�����
package cn.zieckey;
class Test
{
	public static void main( String[] args )
	{
		System.out.println( "zieckey test!");
	}
}
�������У�

E:\study\JAVA\Java-Study\JavaLesson\Lesson3>javac Test.java

E:\study\JAVA\Java-Study\JavaLesson\Lesson3>copy Test.class zieckey
��д zieckey\Test.class ��? (Yes/No/All): y
�Ѹ���         1 ���ļ���

E:\study\JAVA\Java-Study\JavaLesson\Lesson3>java zieckey.Test
Exception in thread "main" java.lang.NoClassDefFoundError: zieckey/Test (wrong n
ame: cn/zieckey/Test)
        at java.lang.ClassLoader.defineClass1(Native Method)
        at java.lang.ClassLoader.defineClass(Unknown Source)
        at java.security.SecureClassLoader.defineClass(Unknown Source)
        at java.net.URLClassLoader.defineClass(Unknown Source)
        at java.net.URLClassLoader.access$100(Unknown Source)
        at java.net.URLClassLoader$1.run(Unknown Source)
        at java.security.AccessController.doPrivileged(Native Method)
        at java.net.URLClassLoader.findClass(Unknown Source)
        at java.lang.ClassLoader.loadClass(Unknown Source)
        at sun.misc.Launcher$AppClassLoader.loadClass(Unknown Source)
        at java.lang.ClassLoader.loadClass(Unknown Source)
        at java.lang.ClassLoader.loadClassInternal(Unknown Source)

���Ƿ����г��������⣬��ʵһ���ģ�����ֻ��Ҫ�ٽ� zieckey �ļ��зŵ� cn �ļ����£�
E:\study\JAVA\Java-Study\JavaLesson\Lesson3>java cn.zieckey.Test
zieckey test!

package���������ļ��еĵ�һ����䡣
Ҳ����˵����package���֮ǰ�����˿հ׺�ע��֮�ⲻ�����κ���䡣
�������package��䣬��ָ��Ϊȱʡ������������
����Ӧ���ļ�ϵͳ��Ŀ¼��νṹ��
��package����У��á�.����ָ������Ŀ¼���Ĳ�Ρ�

�������ÿ�ζ�Ҫ�ֶ�����Ӱ���Ӧ���ļ��У��ǽ���һ������ô�������飬
�Һ�Java������Ϊ����׼���������ķ�����ʡȥ�����Լ��ֶ���Ӱ���Ӧ���ļ��С�


E:\study\JAVA\Java-Study\JavaLesson\Lesson3>javac
�÷���javac <ѡ��> <Դ�ļ�>
���У����ܵ�ѡ�������
  -g                         �������е�����Ϣ
  -g:none                    �������κε�����Ϣ
  -g:{lines,vars,source}     ֻ����ĳЩ������Ϣ
  -nowarn                    �������κξ���
  -verbose                   ����йر���������ִ�еĲ�������Ϣ
  -deprecation               ���ʹ���ѹ�ʱ�� API ��Դλ��
  -classpath <·��>            ָ�������û����ļ���λ��
  -cp <·��>                   ָ�������û����ļ���λ��
  -sourcepath <·��>           ָ����������Դ�ļ���λ��
  -bootclasspath <·��>        �����������ļ���λ��
  -extdirs <Ŀ¼>              ���ǰ�װ����չĿ¼��λ��
  -endorseddirs <Ŀ¼>         ����ǩ���ı�׼·����λ��
  -d <Ŀ¼>                    ָ��������ɵ����ļ���λ��
  -encoding <����>             ָ��Դ�ļ�ʹ�õ��ַ�����
  -source <�汾>               �ṩ��ָ���汾��Դ������
  -target <�汾>               �����ض� VM �汾�����ļ�
  -version                   �汾��Ϣ
  -help                      �����׼ѡ�����Ҫ
  -X                         ����Ǳ�׼ѡ�����Ҫ
  -J<��־>                     ֱ�ӽ� <��־> ���ݸ�����ʱϵͳ

-d �������԰��������Զ����ɰ���Ӧ���ļ��У�������ŵ���Ӧ���ļ����¡�
E:\study\JAVA\Java-Study\JavaLesson\Lesson3>javac -d . Test.java

E:\study\JAVA\Java-Study\JavaLesson\Lesson3>java cn/zieckey/Test
zieckey test!

���벢���ɰ�
�ڵ�ǰĿ¼�����ɰ�
    javac �Cd . Test.java
��ָ��Ŀ¼�����ɰ�
    javac �Cd E:\JavaLesson Test.java

E:\study\JAVA\Java-Study\JavaLesson\Lesson3>javac -d d:\ Test.java

E:\study\JAVA\Java-Study\JavaLesson\Lesson3>set classpath=%classpath%;d:\

E:\study\JAVA\Java-Study\JavaLesson\Lesson3>java cn/zieckey/Test
zieckey test!


�������ʵ�������������
package cn.zieckey;
class Test
{
	public static void main( String[] args )
	{
		Test t = new Test();//�����������Դ�ļ��п���ֱ��������
		cn.zieckey.Test tt = new cn.zieckey.Test();//Ҳ��������������
		System.out.println( "zieckey test!");
	}
}


import���
������е��ࡣ
    import java.io.File;
������������
    import java.io.*;
��ͬһ���е�����Ի������ã�����import��䡣

ע�⣺java.lang���е������Զ�����ģ������������øð�������Բ���import��䵼�롣

�������������е��ࣺ
package cn.zieckey;
class Test
{
	public static void main( String[] args )
	{
		Test t = new Test();//�����������Դ�ļ��п���ֱ��������
		cn.zieckey.Test tt = new cn.zieckey.Test();//Ҳ��������������
		java.io.File f ;//����������������
		System.out.println( "zieckey test!");
	}
}

���ߣ�
package cn.zieckey;
import java.io.File;
class Test
{
	public static void main( String[] args )
	{
		Test t = new Test();//�����������Դ�ļ��п���ֱ��������
		cn.zieckey.Test tt = new cn.zieckey.Test();//Ҳ��������������
		File f ;//�����ǰ��������������Ϳ���ֱ����������������
		System.out.println( "zieckey test!");
	}
}

����Ҳ����ֱ��ͨ���������а�����ʡ��:import java.io.*;
�������������Ļ�,����Ҫ������ڴ�,�����pc��˵û��ʲô,���Ƕ����ֳ�ʽǶ��ʽ�豸,�Ͳ���ô����.

������ͬһ���������½�һ����:
//Test2.java
package cn.zieckey;
class Test2
{
}

Ȼ��������Test���п���ֱ������Test2
//Test.java
package cn.zieckey;
import java.io.File;
class Test
{
	public static void main( String[] args )
	{
		/*
		Test t = new Test();//�����������Դ�ļ��п���ֱ��������
		cn.zieckey.Test tt = new cn.zieckey.Test();//Ҳ��������������
		File f ;//�����ǰ��������������Ϳ���ֱ����������������
		System.out.println( "zieckey test!");
		*/
		Test2 t2 = new Test2();
	}
}

E:\JavaLesson\Lesson3>javac -d . *.java
����û������
������ǵ�Test2.java�ļ�������д��:
//Test2.java
//package cn.zieckey;
package com.zieckey;
class Test2
{
}
E:\JavaLesson\Lesson3>javac -d . *.java
Test.java:14: �Ҳ�������
���ţ� �� Test2
λ�ã� �� cn.zieckey.Test
                Test2 t2 = new Test2();
                ^
Test.java:14: �Ҳ�������
���ţ� �� Test2
λ�ã� �� cn.zieckey.Test
                Test2 t2 = new Test2();
                               ^
2 ����
������д���,��ô����ֻ��ͨ����Test.java�е���Test2�����.
//Test.java
package cn.zieckey;
import com.zieckey.Test2;
class Test
{
	public static void main( String[] args )
	{
		Test2 t2 = new Test2();
	}
}
���Ǳ��뻹�ǳ�������:
E:\JavaLesson\Lesson3>javac -d . *.java
Test.java:4: com.zieckey.Test2 �� com.zieckey �в��ǹ����ģ��޷����ⲿ������ж�
����з���
import com.zieckey.Test2;
                   ^
Test.java:15: �Ҳ�������
���ţ� �� Test2
λ�ã� �� cn.zieckey.Test
                Test2 t2 = new Test2();
                ^
Test.java:15: �Ҳ�������
���ţ� �� Test2
λ�ã� �� cn.zieckey.Test
                Test2 t2 = new Test2();
                               ^
3 ����

������˵ com.zieckey.Test2 �� com.zieckey �в��ǹ����ģ��޷����ⲿ������ж�
����з���,����Ӧ�ð� com.zieckey.Test2 ��Ϊ���е�.
//Test2.java
//package cn.zieckey;
package com.zieckey;
public class Test2
{
}
�ٱ����û��������.
E:\JavaLesson\Lesson3>javac -d . *.java

���ǰ�һ��������Ϊ���еľ��������ܲ����е������,���������Ϊ����,
��ô������ȱʡ����,��ֻ�ܱ�ͬһ�����е������.

��ķ���˵����
 ��1��public
 ��2��default�����ӷ���˵����ʱ��
����������η�
 ��1��final,�����������Ͳ��ܱ��̳�.
 ��2��abstract


��1��final,�����������Ͳ��ܱ��̳�.
//Test2.java
package com.zieckey;
public final class Test2
{
}

//Test.java
package cn.zieckey;
class Test //extends com.zieckey.Test2
{
	public static void main( String[] args )
	{
		com.zieckey.Test2 t2 = new com.zieckey.Test2();
	}
}

E:\JavaLesson\Lesson3>javac -d . *.java
Test.java:3: �޷������� com.zieckey.Test2 ���м̳�
class Test extends com.zieckey.Test2
                              ^
1 ����


�����ķ���˵����
 ��1��public
 ��2��protected
 ��3��default(���ӷ���˵����ʱ)
 ��4��private
�������������η�
 ��1��static
 ��2��final
 ��3��abstract
 ��4��native
 ��5��synchronized


������ķ����ķ���Ȩ������:
//Test.java
package cn.zieckey;
public class Test
{
	public void publicMethod()
	{
		System.out.println( "publicMethod!" );
	}
	protected void protectedMethod()
	{
		System.out.println( "protectedMethod!" );
	}
	void defaultMethod()
	{
		System.out.println( "defaultMethod!" );
	}
	private void privateMethod()
	{
		System.out.println( "privateMethod!" );
	}

	public static void main( String[] args )
	{
		Test t = new Test();
		t.publicMethod();
		t.protectedMethod();
		t.defaultMethod();
		t.privateMethod();
	}
}

E:\JavaLesson\Lesson3>javac -d . Test.java

E:\JavaLesson\Lesson3>java cn.zieckey.Test
publicMethod!
protectedMethod!
defaultMethod!
privateMethod!

��˵����ͬһ����public,protected,default,private���඼���Է���.
���ڽ�Test2.java��Ϊ��
//Test2.java
package cn.zieckey;
public final class Test2
{
	public static void main( String[] args )
	{
		Test t = new Test();
		t.publicMethod();
		t.protectedMethod();
		t.defaultMethod();
		t.privateMethod();
	}
}
E:\JavaLesson\Lesson3>javac -d . Test2.java
Test2.java:11: privateMethod() ������ cn.zieckey.Test �з��� private
                t.privateMethod();
                 ^
1 ����

�õģ��Ͳ�������ô���ˣ��ܽ��£�

			�����ķ��ʿ��ƣ�
		public  	protected		default		private
ͬ��	��			��				��			��
ͬ��	��			��				��
����	��			��
ͨ����	��

final������
Ϊ��ȷ��ĳ����������Ϊ�ڼ̳й����б��ֲ��䣬���Ҳ��ܱ����ǣ�overridden��������ʹ��final������
Ϊ��Ч���ϵĿ��ǣ�����������Ϊfinal���ñ������Դ˷����ĵ��ý����Ż���Ҫע����ǣ������������ж�final���������жϣ��������Ƿ�����Ż���ͨ���ڷ����������С��������ȷʵ��ϣ����������ʱ���Ž�������Ϊfinal��
class�����е�private��static������Ȼ����final��

���󷽷��ͳ�����
������û�з�����ķ��������ǳ��󷽷���
���г��󷽷����࣬��Ϊ�����ࡣ
���һ������û��ʵ�ֳ�����������еĳ��󷽷���������Ҳ��Ϊһ�������ࡣ
���ǿ��Խ�һ��û���κγ��󷽷���������Ϊabstract�����������������κεĶ���
���췽������̬������˽�з�����final�������ܱ�����Ϊ����ķ�����
����:
//Test.java
package cn.zieckey;
public class Test
{
	public final void publicMethod()
	{
		System.out.println( "publicMethod!" );
	}
	protected abstract void protectedMethod();
	/*{
		System.out.println( "protectedMethod!" );
	}*/
	void defaultMethod()
	{
		System.out.println( "defaultMethod!" );
	}
	private void privateMethod()
	{
		System.out.println( "privateMethod!" );
	}

	public static void main( String[] args )
	{
		Test t = new Test();
		t.publicMethod();
		t.protectedMethod();
		t.defaultMethod();
		t.privateMethod();
	}
}

E:\JavaLesson\Lesson3>javac -d . Test.java
Test.java:3: cn.zieckey.Test ���ǳ���ģ�����δ���� cn.zieckey.Test �еĳ��󷽷�
 protectedMethod()
public class Test
       ^
1 ����

����˵�����ǳ����,����ӵ�и÷������ಢ���ǳ����.
������д���
//Test.java
package cn.zieckey;
public abstract class Test
{
	public final void publicMethod()
	{
		System.out.println( "publicMethod!" );
	}
	protected abstract void protectedMethod();
	/*{
		System.out.println( "protectedMethod!" );
	}*/
	void defaultMethod()
	{
		System.out.println( "defaultMethod!" );
	}
	private void privateMethod()
	{
		System.out.println( "privateMethod!" );
	}

	public static void main( String[] args )
	{
		Test t = new Test();
		t.publicMethod();
		t.protectedMethod();
		t.defaultMethod();
		t.privateMethod();
	}
}
E:\JavaLesson\Lesson3>javac -d . Test.java
Test.java:24: cn.zieckey.Test �ǳ���ģ��޷��������ʵ����
                Test t = new Test();
                         ^
1 ����
���޸�:
//Test.java
package cn.zieckey;
public abstract class Test
{
	public final void publicMethod()
	{
		System.out.println( "publicMethod!" );
	}
	protected abstract void protectedMethod();
	/*{
		System.out.println( "protectedMethod!" );
	}*/
	void defaultMethod()
	{
		System.out.println( "defaultMethod!" );
	}
	private void privateMethod()
	{
		System.out.println( "privateMethod!" );
	}

	public static void main( String[] args )
	{
		/*Test t = new Test();
		t.publicMethod();
		t.protectedMethod();
		t.defaultMethod();
		t.privateMethod();*/
	}
}

E:\JavaLesson\Lesson3>javac -d . Test.java
���������û��������.
�ܽ᣺������������ǳ���ģ���ô��Ӧ����ҲҪ�ǳ���ģ����ҳ�����಻��ʵ������

������Test2�̳���Test
//Test2.java
package cn.zieckey;
import cn.zieckey.Test;
public class Test2 extends Test
{

	public static void main( String[] args )
	{
	}
}
E:\JavaLesson\Lesson3>javac -d . Test2.java
Test2.java:4: cn.zieckey.Test2 ���ǳ���ģ�����δ���� cn.zieckey.Test �еĳ���
�� protectedMethod()
public class Test2 extends Test
       ^
1 ����

���޸�,������ĳ��󷽷����廯:
//Test2.java
package cn.zieckey;
import cn.zieckey.Test;
public class Test2 extends Test
{
	protected void protectedMethod()
	{
	}
	public static void main( String[] args )
	{
	}
}
E:\JavaLesson\Lesson3>javac -d . Test2.java
����û�д����ˡ�

������������ٽ�Test2.java��Ϊ���£�
//Test2.java
package cn.zieckey;
import cn.zieckey.Test;
public abstract class Test2 extends Test
{
	/*protected void protectedMethod()
	{
	}*/
	public static void main( String[] args )
	{
	}
}
E:\JavaLesson\Lesson3>javac -d . Test2.java

E:\JavaLesson\Lesson3>
�������ǽ�����Ҳ����Ϊ����ķ���������Ҳ��û�д����ˡ�

�ܽ᣺������౻�̳�ʱ��Ҫô����Ҳ����Ϊ�����࣬Ҫô��������ʵ�ָ���ĳ��󷽷�.


native����
{
	native�������û���Java�п���ʹ�ã������ܱ�д�ķ�����
	JNI(Java Native Interface)��������Java�����(JVM)�ڲ����е�Java�����ܹ�
���������������(��C��C++���������)��д��Ӧ�ó���Ϳ���л�������
	JNI���ĺô�����û�жԵײ�Java�������ʵ��ʩ���κ�����,
��ˣ�Java��������̿����ڲ�Ӱ��������������ֵ��������Ӷ�JNI��֧�֡�
����Աֻ���дһ�ְ汾�ı���(Native)Ӧ�ó���Ϳ⣬
���ܹ�������֧��JNI��Java�����Эͬ������
	JNI�������ΪJava�ͱ���Ӧ�ó���֮����н顣


����һ��native������
1. ����һ��HelloWorld.java
class HelloWorld
{
    public native void displayHelloWorld();

    static
    {
        System.loadLibrary("hello");
    }

    public static void main(String[] args) {
        new HelloWorld().displayHelloWorld();
    }
}

2. ����
E:\zieckey\Lesson3>javac HelloWorld.java

3. ����ͷ�ļ�
E:\zieckey\Lesson3>javah -jni HelloWorld

4. дʵ���ļ�HelloWorldImp.c
#include <jni.h>
#include "HelloWorld.h"
#include <stdio.h>

JNIEXPORT void JNICALL
Java_HelloWorld_displayHelloWorld(JNIEnv *env, jobject obj)
{
    printf("Hello world!\n");
    return;
}

5. ���ɶ�̬���ӿ�
��������VC��CL.exe���ߣ�
����ֱ����VC�½������������ɣ�����ע�⽫D:\Program Files\Java\jdk1.5.0_06\include��
D:\Program Files\Java\jdk1.5.0_06\include\win32������Ŀ¼���뻷���У�
E:\zieckey\Lesson3>cl -ID:\Program Files\Java\jdk1.5.0_06\include -ID:\Program Files\Java\jdk1.5.0_06\include\win32 -LDHelloWorldImp.c -Fhello.dll

6. ִ��
E:\zieckey\Lesson3>java HelloWorld







JNI

����ڹ�˾������һ���ֻ�����Ŀ����ҪJAVA�����ڷ��Ͷ��ŵ�ʱ��͵������Ķ��ŷ��������ӡ����Žӿ�����C++д�ġ���ĥ�����죬���¸㶮��JNI�����岿�֡��Ƚ��ĵ�����ϣ����λ����������·��
��������һƪ���£�����һ���򵥵�JNI�ĵ��õĹ��̡�
JAVA�����ƽ̨��������������ϲ�����������������Ŀ�ƽ̨��Ŀ�ģ�ʹ�����ͱ��ػ����ĸ����ڲ���ϵ��ú��٣�Լ�������Ĺ��ܡ����JAVA�Ա��ز�����һ�ַ�������JNI��
JAVAͨ��JNI���ñ��ط����������ط������Կ��ļ�����ʽ��ŵģ���WINDOWSƽ̨����DLL�ļ���ʽ����UNIX��������SO�ļ���ʽ����ͨ�����ñ��صĿ��ļ����ڲ�������ʹJAVA����ʵ�ֺͱ��ػ����Ľ�����ϵ������ϵͳ���ĸ��ӿڷ�����
�򵥽��ܼ�Ӧ�����£�
һ��JAVA������Ҫ���Ĺ���
��JAVA�����У�������Ҫ���������������õĿ����ƣ����£�
static {
System.loadLibrary(��goodluck��);
}

����������չ���ֿ��Բ���д������������DLL����SO����ϵͳ�Լ��жϡ�
����Ҫ�Խ�Ҫ���õķ����������������ؼ���Ϊnative������ֻ��Ҫ������������Ҫ�� ��ʵ�֡����£�
public native static void set(int i);
public native static int get();
Ȼ������JAVA�����ļ�������CLASS������JAVAH���JNI�ͻ�����C/C++��ͷ�ļ���
�������testdll.java������Ϊ��
public class testdll
{
static
{
System.loadLibrary("goodluck");
}
public native static int get();
public native static void set(int i);
public static void main(String[] args)
{
testdll test = new testdll();
test.set(10);
System.out.println(test.get());
}
}

��javac testdll.java��������������testdll.class��
����javah testdll������ڵ�ǰĿ¼������testdll.h�ļ�������ļ���Ҫ��C/C++�����������������Ŀ��ļ���
����C/C++������Ҫ���Ĺ���
���������ɵ�.hͷ�ļ���C/C++����Ҫ���ģ����ǰ����ĸ������������ʵ�֡�Ȼ��������ӳɿ��ļ����ɡ��ٰѿ��ļ�������JAVA�����·�����棬�Ϳ�����JAVA����C/C++��ʵ�ֵĹ����ˡ�
�������ӡ������ȿ�һ��testdll.h�ļ������ݣ�
/* DO NOT ED99v THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class testdll */
#ifndef _Included_testdll
#define _Included_testdll
#ifdef __cplusplus
extern "C" {
#endif
/*
* Class: testdll
* Method: get
* Signature: ()I
*/
JNIEXPORT jint JNICALL Java_testdll_get (JNIEnv *, jclass);
/*
* Class: testdll
* Method: set
* Signature: (I)V
*/
JNIEXPORT void JNICALL Java_testdll_set (JNIEnv *, jclass, jint);
#ifdef __cplusplus
}
#endif
#endif
�ھ���ʵ�ֵ�ʱ������ֻ������������ԭ��
JNIEXPORT jint JNICALL Java_testdll_get (JNIEnv *, jclass); ��
JNIEXPORT void JNICALL Java_testdll_set (JNIEnv *, jclass, jint);
����JNIEXPORT��JNICALL����JNI�Ĺؼ��֣���ʾ�˺�����Ҫ��JNI���õġ���jint����JNIΪ�н�ʹJAVA��int�����뱾�ص� int��ͨ��һ�����ͣ����ǿ����Ӷ��������͵���intʹ�á�������������JAVA_�ټ���java�����package·���ټӺ�������ɵġ������У�����Ҳֻ��Ҫ������JAVA�����д��ڵĲ���������JNIEnv*��jclass����һ��û�б�Ҫȥ������
�ã�����������testdll.cpp�ļ�����ʵ��������������
#include "testdll.h"
int i = 0;
JNIEXPORT jint JNICALL Java_testdll_get (JNIEnv *, jclass)
{
return i;
}
JNIEXPORT void JNICALL Java_testdll_set (JNIEnv *, jclass, jint j)
{
i = j;
}
�������ӳɿ��ļ�����������WINDOWS�����ģ����ɵ���DLL�ļ�����������Ҫ��JAVA����Ҫ���õ�һ�£��������goodluck.dll ����goodluck.dll������testdll.class��Ŀ¼�£�java testdll���������Ϳ��Թ۲쵽����ˡ�  











�������գ�
//Garbage.java
class Garbage
{
	int index;
	static int count;
	Garbage()
	{
		count++;
		System.out.println( "object " + count + " constructed" );
		setID( count );
	}
	void setID( int id )
	{
		index = id;
	}
	protected void finalize()
	{
		System.out.println( "object " + index + " is reclaimed");
	}

	public static void main( String[] args )
	{
		new Garbage();
		new Garbage();
		new Garbage();
		new Garbage();
	}
}
��������������п�����

E:\zieckey\Lesson3>javac Garbage.java

E:\zieckey\Lesson3>java Garbage
object 1 constructed
object 2 constructed
object 3 constructed
object 4 constructed
���Է��֣����ﲢû�л��������������������Զ�����finalize��������
������Ϊ��������Ƕ�̬���������ģ���ϵͳ�ڴ治���õ�ʱ��Ž����������գ�
�������յ��̵߳����ȼ��ܵ͡�
���ǿ�����ʾ�ĵ�����������������������
//Garbage.java
class Garbage
{
	int index;
	static int count;
	Garbage()
	{
		count++;
		System.out.println( "object " + count + " constructed" );
		setID( count );
	}
	void setID( int id )
	{
		index = id;
	}
	protected void finalize()
	{
		System.out.println( "object " + index + " is reclaimed");
	}

	public static void main( String[] args )
	{
		new Garbage();
		new Garbage();
		new Garbage();
		new Garbage();
		System.gc();//��ʾ�ĵ���������������������
	}
}
E:\zieckey\Lesson3>javac Garbage.java

E:\zieckey\Lesson3>java Garbage
object 1 constructed
object 2 constructed
object 3 constructed
object 4 constructed
object 4 is reclaimed
object 3 is reclaimed
object 2 is reclaimed
object 1 is reclaimed


�ӿڵĵ��ã�
�ӿ������еķ�������public abstract��
�ڽӿ�����������ʱ������ʹ��native��static ��final ��synchronized ��private ��protected�����η���
��public��һ����public�ӿ�Ҳ���붨������ӿ�ͬ�����ļ��С�
�ӿ��п��������ݳ�Ա����Щ��ԱĬ�϶���public static final��
һ���ӿڿ��Լ̳�����һ���ӿڡ�
Java�в�������Ķ�̳У�������ӿڵĶ�̳С�
��Java�У�һ�������ʵ�ֶ���ӿڡ�
һ�����ڼ̳�����һ�����ͬʱ������ʵ�ֶ���ӿڡ�



//Sport.java
interface Sport
{
	void run();
	void jump();
}
class Athlete implements Sport
{
	void run()
	{
		System.out.println( "����" );
	}
	void jump()
	{
		System.out.println( "����" );
	}

	public static void main( String[] args )
	{
		Athlete zhangsan = new Athlete();
		zhangsan.run();
		zhangsan.jump();
	}
}

E:\zieckey\Lesson3>javac Sport.java
Sport.java:13: Athlete �е� jump() �޷�ʵ�� Sport �е� jump()�����ڳ���ָ������
�ķ���Ȩ�ޣ�Ϊ public
        void jump()
             ^
Sport.java:9: Athlete �е� run() �޷�ʵ�� Sport �е� run()�����ڳ���ָ�����͵ķ�
��Ȩ�ޣ�Ϊ public
        void run()
             ^
2 ����

�ӿ�˵���ˣ��ӿ������еķ�������public abstract��
��ô��ʵ���оͲ��ܱȸ÷���Ȩ�޸��ͣ����Գ����������
���Ǹĸ�Դ�ļ�������
//Sport.java
interface Sport
{
	public abstract void run();
	void jump();
}
class Athlete implements Sport
{
	public void run()
	{
		System.out.println( "����" );
	}
	void jump()
	{
		System.out.println( "����" );
	}

	public static void main( String[] args )
	{
		Athlete zhangsan = new Athlete();
		zhangsan.run();
		zhangsan.jump();
	}
}

E:\zieckey\Lesson3>javac Sport.java
Sport.java:13: Athlete �е� jump() �޷�ʵ�� Sport �е� jump()�����ڳ���ָ������
�ķ���Ȩ�ޣ�Ϊ public
        void jump()
             ^
1 ����


//Sport.java
interface Sport
{
	public abstract void run();
	void jump();
}
class Athlete implements Sport
{
	public void run()
	{
		System.out.println( "����" );
	}
	public void jump()
	{
		System.out.println( "����" );
	}

	public static void main( String[] args )
	{
		Athlete zhangsan = new Athlete();
		zhangsan.run();
		zhangsan.jump();
	}
}
E:\zieckey\Lesson3>javac Sport.java

E:\zieckey\Lesson3>java Athlete
����
����

E:\zieckey\Lesson3>

��ʵ���еķ�������Ȩ�޸�Ϊ�ӿڵĵ�ͬ���߸��߾Ϳ����ˡ�
���濴��ֻʵ�ֽӿ��е�һ��������
//Sport.java
interface Sport
{
	public abstract void run();
	void jump();
}
class Athlete implements Sport
{
	public void run()
	{
		System.out.println( "����" );
	}
	/*public void jump()
	{
		System.out.println( "����" );
	}
	*/
	public static void main( String[] args )
	{
		Athlete zhangsan = new Athlete();
		zhangsan.run();
		zhangsan.jump();
	}
}
E:\zieckey\Lesson3>javac Sport.java
Sport.java:7: Athlete ���ǳ���ģ�����δ���� Sport �еĳ��󷽷� jump()
class Athlete implements Sport
^
Sport.java:22: �Ҳ�������
���ţ� ���� jump()
λ�ã� �� Athlete
                zhangsan.jump();
                        ^
2 ����

������Ϊ�ӿ��е����з�������public abstract�����Գ��ִ���

���濴��һ��ͨ���ӿ�ʵ��Эͬ���������ӣ�
����������Ҫ�����峧�̺��Կ�����֮�䶨��һ���Կ���۵Ľӿڣ�
Ȼ����������׼�ӿڣ��Կ����������Կ������峧���������塣
����ʵ�����£�

�Կ���۽ӿڣ�
//VideoCard.java
interface VideoCard
{
	void display();
	String getName();
}

�Կ��������������Կ���
//Dmeng.java
class Dmeng implements VideoCard
{
	String name;
	Dmeng()
	{
		name = "Dmeng's VideoCard" ;
	}
	public void display()
	{
		System.out.println( "Dmeng's VideoCard is working!" );
	}
	public String getName()
	{
		return name;
	}
	public void setName( String name )
	{
		this.name = name;
	}
}

��������������������
//MainBoard.java
class MainBoard
{
	String strCPU;
	VideoCard vc;
	MainBoard()
	{

	}
	void setCPU( String strCPU )
	{
		this.strCPU = strCPU;
	}

	//����ͨ���ӿ���Ϊ�βΣ��ڵ��ø÷�����ʱ��
	//�ᴫ��һ��ʵ�ָýӿڵ����ʵ������
	void setVideoCard( VideoCard vc )
	{
		this.vc = vc ;
	}
	void run()
	{
		System.out.println( strCPU );
		System.out.println( vc.getName() );
		vc.display();
		System.out.println( "MainBoard is running..." );
	}
}

���ھͿ�����װ������
//Computer.java
class Computer
{
	public static void main( String[] args )
	{
		Dmeng d = new Dmeng();
		MainBoard m = new MainBoard();

		m.setCPU( "AMD's CPU" );
		m.setVideoCard( d );

		m.run();
	}
}

���룺
E:\zieckey\Lesson3\interface>javac *.java

E:\zieckey\Lesson3\interface>java Computer
AMD's CPU
Dmeng's VideoCard
Dmeng's VideoCard is working!
MainBoard is running...


�ٿ�һ�����ӣ�
//Math.java
interface Math
{
	double PI=3.1415926;
}
class Arithmetic implements Math
{
	double roundArea(double radius)
	{
		return PI*radius*radius;
	}
}
class Student
{
	public static void main(String[] args)
	{
		Arithmetic a=new Arithmetic();
		System.out.println(a.roundArea(3));
		System.out.println(Math.PI);		//ok
		System.out.println(Arithmetic.PI);	//ok
		System.out.println(a.PI);		//ok
	}
}



//Sofa.java
interface Sittable
{
	void sit();
}
interface Lie
{
	void sleep();
}
interface Chair extends Sittable
{
}

interface Sofa extends Sittable, Lie
{
}



//Sofa.java
//ʵ�ֶ���ӿ�
interface Sittable
{
	void sit();
}
interface Lie
{
	void sleep();
}
class Sofa implements Sittable, Lie
{
	public void sit()
	{
	}
	public void sleep()
	{
	}
}


//Sofa.java
//�ڼ̳����ͬʱ��ʵ�ֶ���ӿ�
interface Sittable
{
	void sit();
}
interface Lie
{
	void sleep();
}
interface HealthCare
{
	void massage();
}
class Chair implements Sittable
{
	public void sit(){};
}
class Sofa extends Chair implements Lie, HealthCare
{
	public void sleep(){};
	public void massage(){};
}




�ڲ��ࣺ
�ڷ����ж�����ڲ��࣬���Ҫ���ʷ����ж���ı��ر����򷽷��Ĳ�������������뱻����final��
�ڲ����������Ϊprivate��protected������������Ϊabstract��final��
�ڲ����������Ϊstatic�ģ�����ʱ�Ͳ�����ʹ���ⲿ��ķ�static�ĳ�Ա�����ͷ�static�ĳ�Ա������
��static���ڲ����еĳ�Ա��������Ϊstatic�ģ�ֻ���ڶ������static���ڲ����вſ�����static��Ա��

//Outer.java
class Outer
{
	private int index = 100;
	class Inner
	{
		private int index = 50;
		void print()
		{
			int index = 30;
			System.out.println( index );	//�ֲ�����
			System.out.println( this.index );	//inner�����
			System.out.println( Outer.this.index );	//Outer�����
		}
	}
	void print()
	{
		Inner inner = new Inner();
		inner.print();
	}
}

class Test
{
	public static void main( String[] args )
	{
		Outer outer = new Outer();
		outer.print();
	}
}

���룺
E:\zieckey\Lesson4>javac Outer.java

E:\zieckey\Lesson4>java Test
30
50
100



�����ڲ���ķ�����
//Outer.java
class Outer
{
	private int index = 100;
	class Inner
	{
		private int index = 50;
		void print()
		{
			int index = 30;
			System.out.println( index );	//�ֲ�����
			System.out.println( this.index );	//inner�����
			System.out.println( Outer.this.index );	//Outer�����
		}
	}
	void print()
	{
		Inner inner = new Inner();
		inner.print();
	}

	Inner getInner() //�ṩ�����ڲ���ķ���
	{
		return new Inner();
	}
}

class Test
{
	public static void main( String[] args )
	{
		Outer outer = new Outer();
		//outer.print();
		Outer.Inner inner = outer.getInner();//����ͨ��Outer.Inner�ﵽ�����ڲ���
		inner.print();
	}
}

���main������Outer���У�
//Outer.java
class Outer
{
	private int index = 100;
	class Inner
	{
		private int index = 50;
		void print()
		{
			int index = 30;
			System.out.println( index );	//�ֲ�����
			System.out.println( this.index );	//inner�����
			System.out.println( Outer.this.index );	//Outer�����
		}
	}
	void print()
	{
		Inner inner = new Inner();
		inner.print();
	}

	Inner getInner() //��߷����ڲ���ķ���
	{
		return new Inner();
	}

	public static void main( String[] args )
	{
		Outer outer = new Outer();
		//outer.print();
		Outer.Inner inner = outer.getInner();
		inner.print();
	}
}

class Test
{
	/*public static void main( String[] args )
	{
		Outer outer = new Outer();
		//outer.print();
		Outer.Inner inner = outer.getInner();
		inner.print();
	}*/
}
����
//Outer.java
class Outer
{
	private int index = 100;
	class Inner
	{
		private int index = 50;
		void print()
		{
			int index = 30;
			System.out.println( index );	//�ֲ�����
			System.out.println( this.index );	//inner�����
			System.out.println( Outer.this.index );	//Outer�����
		}
	}
	void print()
	{
		Inner inner = new Inner();
		inner.print();
	}

	Inner getInner() //��߷����ڲ���ķ���
	{
		return new Inner();
	}

	public static void main( String[] args )
	{
		Outer outer = new Outer();
		//outer.print();
		//Outer.Inner inner = outer.getInner();
		Inner inner = outer.getInner();
		inner.print();
	}
}

class Test
{
	/*public static void main( String[] args )
	{
		Outer outer = new Outer();
		//outer.print();
		Outer.Inner inner = outer.getInner();
		inner.print();
	}*/
}


E:\zieckey\Lesson4>javac Outer.java

E:\zieckey\Lesson4>java Outer
30
50
100

E:\zieckey\Lesson4>


�ڲ�����ֱ��ͨ��new�������أ�

//Outer.java
class Outer
{
	private int index = 100;
	class Inner
	{
		private int index = 50;
		void print()
		{
			int index = 30;
			System.out.println( index );	//�ֲ�����
			System.out.println( this.index );	//inner�����
			System.out.println( Outer.this.index );	//Outer�����
		}
	}
	void print()
	{
		Inner inner = new Inner();
		inner.print();
	}

	Inner getInner() //��߷����ڲ���ķ���
	{
		return new Inner();
	}

	public static void main( String[] args )
	{
		Outer outer = new Outer();
		//outer.print();
		//Outer.Inner inner = outer.getInner();
		//Inner inner = outer.getInner();
		Inner inner = new Inner();
		inner.print();
	}
}

class Test
{
	/*public static void main( String[] args )
	{
		Outer outer = new Outer();
		//outer.print();
		Outer.Inner inner = outer.getInner();
		inner.print();
	}*/
}
E:\zieckey\Lesson4>javac Outer.java
Outer.java:33: �޷��Ӿ�̬�����������÷Ǿ�̬ ���� this
                Inner inner = new Inner();
                              ^
1 ����

���������ǲ��еģ��ڲ��಻��ֱ��ͨ��new������
���ǿ���ͨ���ⲿ�������ɣ�
//Outer.java
class Outer
{
	private int index = 100;
	class Inner
	{
		private int index = 50;
		void print()
		{
			int index = 30;
			System.out.println( index );	//�ֲ�����
			System.out.println( this.index );	//inner�����
			System.out.println( Outer.this.index );	//Outer�����
		}
	}
	void print()
	{
		Inner inner = new Inner();
		inner.print();
	}

	Inner getInner() //��߷����ڲ���ķ���
	{
		return new Inner();
	}
}

class Test
{
	public static void main( String[] args )
	{
		Outer outer = new Outer();

		//�������ֱ����new����Inner����Ļ���
		//��Inner����ڲ������ʵ�Outer������ݳ�Ա������û�г�ʼ�������ݱ�����
		//����Ȼ�ǲ��еģ�����Ҫͨ��Outer���ʵ��outer outer.new ������Inner����
		Outer.Inner inner = outer.new Inner();
		inner.print();
	}
}

�ڲ��໹���Էŵ���Ա�����У����������ж�����У�

//Outer.java
class Outer
{
	private int index = 100;
	void fn()
	{
		if( true )
		{
			class Middle
			{
				private int index = 70;
				class Inner
				{
					private int index = 50;
					void print()
					{
						int index = 30;
						System.out.println( index );	//�ֲ�����
						System.out.println( this.index );	//inner�����
						System.out.println( Middle.this.index );	//Middle�����
						System.out.println( Outer.this.index );	//Outer�����
					}
				}
			}//class Middle
		}//end if
	}//end fn

}

class Test
{
	public static void main( String[] args )
	{
		Outer outer = new Outer();
	}
}
Ҳ����˵�����ڲ���Ƕ���ж����������������ⲿ��ĳ�Ա��


//Outer.java
class Outer
{
	private int index = 100;
	void fn( int a )
	{
		int b;
		if( true )
		{
			class Middle
			{
				private int index = 70;
				class Inner
				{
					private int index = 50;
					void print()
					{
						int index = 30;
						System.out.println( index );	//�ֲ�����
						System.out.println( this.index );	//inner�����
						System.out.println( Middle.this.index );	//Middle�����
						System.out.println( Outer.this.index );	//Outer�����
						a = 5;
						b = 6;
					}
				}
			}//class Middle
		}//end if
	}//end fn

}

class Test
{
	public static void main( String[] args )
	{
		Outer outer = new Outer();
	}
}

E:\zieckey\Lesson4>javac Outer.java
Outer.java:23: ���ڲ����з��ʾֲ����� a����Ҫ������Ϊ��������
                                                a = 5;
                                                ^
Outer.java:24: ���ڲ����з��ʾֲ����� b����Ҫ������Ϊ��������
                                                b = 6;
                                                ^
2 ����

����������ʾ�ˣ����ǽ�a��b����Ϊfinal���ͣ�
//Outer.java
class Outer
{
	private int index = 100;
	void fn( final int a )
	{
		final int b = 10;
		if( true )
		{
			class Middle
			{
				private int index = 70;
				class Inner
				{
					private int index = 50;
					void print()
					{
						int index = 30;
						System.out.println( index );	//�ֲ�����
						System.out.println( this.index );	//inner�����
						System.out.println( Middle.this.index );	//Middle�����
						System.out.println( Outer.this.index );	//Outer�����
						System.out.println( a );
						System.out.println( b );
					}
				}
			}//class Middle
		}//end if
	}//end fn

}

class Test
{
	public static void main( String[] args )
	{
		Outer outer = new Outer();
	}
}
���������û�����⣬


���ڲ�����������÷�:
//Car.java
class Car
{
	class Wheel
	{
	}
}
class PanelWheel extends Car.Wheel
{
	public static void main( String[] args )
	{
		PanelWheel pw = new PanelWheel();
	}
}
E:\zieckey\Lesson4>javac Car.java
Car.java:8: ��Ҫ���� Car.Wheel �ķ��ʵ��
class PanelWheel extends Car.Wheel
^
1 ����
��������Ϊ,�ⲿ�ڻ�û�в���ʵ������,�ڲ���Ͳ����ܴ���,�Ǻ�̸��ʼ����?

��ʱ��������Ҫ������ķ����������ڲ���������:

//Car.java
class Car
{
	class Wheel
	{
	}
}
class PanelWheel extends Car.Wheel
{
	PanelWheel( Car car )
	{
		car.super();
	}
	public static void main( String[] args )
	{
		Car car = new Car();
		PanelWheel pw = new PanelWheel( car );
	}
}

����ͨ���ڲ���ʵ�ֽӿ�:
//Animal.java
interface Animal
{
	void eat();
	void sleep();
}

class Zoo
{
	private class Tiger implements Animal
	{
		public void eat()
		{
			System.out.println("tiger eat");
		}
		public void sleep()
		{
			System.out.println("tiger sleep");
		}
	}
	Animal getAnimal()
	{
		return new Tiger();
	}
}

class Test
{
	public static void main(String[] args)
	{
		Zoo z=new Zoo();
		Animal an=z.getAnimal();
		an.eat();
		an.sleep();
	}
}
E:\zieckey\Lesson4>javac Animal.java

E:\zieckey\Lesson4>java Test
tiger eat
tiger sleep

E:\zieckey\Lesson4>

�������ǻ���������ʵ�ֽӿ�:
//Animal.java
interface Animal
{
	void eat();
	void sleep();
}

class Zoo
{
	private class Tiger implements Animal
	{
		public void eat()
		{
			System.out.println("tiger eat");
		}
		public void sleep()
		{
			System.out.println("tiger sleep");
		}
	}
	/*Animal getAnimal()
	{
		return new Tiger();
	}*/
	Animal getAnimal()
	{
		return new Animal()//����Ͷ�����һ����,ֻ�������û������,������������ڲ���
		{
			public void eat()
			{
				System.out.println("animal eat");
			}
			public void sleep()
			{
				System.out.println("animal sleep");
			}
		};//����ط��ķֺŲ�����,��Ϊ����һ��return���
	}
}

class Test
{
	public static void main(String[] args)
	{
		Zoo z=new Zoo();
		Animal an=z.getAnimal();
		an.eat();
		an.sleep();
	}
}
E:\zieckey\Lesson4>javac Animal.java

E:\zieckey\Lesson4>java Test
animal eat
animal sleep

E:\zieckey\Lesson4>

����Ϊʲôʹ���ڲ���
1�����ڲ��ࣨinner class���У���������ķ����ⲿ��ĳ�Ա������������Ǹ��õ���֯�������ǵĴ��룬��ǿ����Ŀɶ��ԡ�
2���ڲ���������ڴ����������࣬��������������ʵ�ֽӿڵ��ࡣʹ���ڲ�����ʵ�ֽӿڣ����Ը��õض�λ��ӿڹ����ķ����ڴ����е�λ�á�
3���ڲ���ĸ����÷���
�ڲ�����������û�ʵ�ֽӿڵ�ϸ��,
//Animal.java
interface Animal
{
	void eat();
	void sleep();
}
class Zoo
{
	private class Tiger implements Animal
	{
		public void eat()
		{
			System.out.println("tiger eat");
		}
		public void sleep()
		{
			System.out.println("tiger sleep");
		}
	}
	Animal getAnimal()
	{
		return new Tiger();
	}
}
class Test
{
	public static void main(String[] args)
	{
		Zoo z=new Zoo();
		Animal an=z.getAnimal();
		an.eat();
		an.sleep();
	}
}


��������������һ����ͬʱʵ��һ���ӿ�,�����ڸ�������һ�������ͽӿ��з���ͬ��,
���ʱ��,���ǾͿ���ͨ���ڲ���ʵ��:
//Machine.java
interface Machine
{
	void run();
}
class Person
{
	void run()
	{
		System.out.println( "Person is running..." );
	}
}
//Robot��̳���Person��,ͬʱҪʵ��һ��Machine�ӿ�
//������ӿڷ�����Person��ĳ�Ա����ͬ��,���ʱ��Ϳ���ͨ���ڲ���ʵ��
class Robot extends Person
{
	private class MachineHeart implements Machine
	{
		public void run()
		{
			System.out.println( "Machine's heart is running..." );
		}
	}
	Machine getMachine()
	{
		return new MachineHeart();
	}
}

class Test
{
	public static void main(String[] args)
	{
		Robot robot = new Robot();
		Machine m = robot.getMachine();
		m.run();
		robot.run();
	}
}

�ڲ��������ؼ̳е�����:
//A.java
class A
{
	void fn1()
	{
	}
}

abstract class B
{
	abstract void fn2();
}

class C extends A
{
	B getB()
	{
		return new B()//B�ǳ����,���Ա���ʵ�����ĳ��󷽷�
		{
			public void fn2()
			{
			}
		};
	}
}

class Test
{
	static void method1(A a)
	{
		a.fn1();
	}
	static void method2(B b)
	{
		b.fn2();
	}
	public static void main(String[] args)
	{
		C c=new C();
		method1(c);
		method2(c.getB());
	}
}




Java�е��쳣����:
Java������ִ�й�����������쳣�����Զ�����һ���쳣����󣬸��쳣���󽫱��ύ��Java����ʱϵͳ��������̳�Ϊ�׳�(throw)�쳣��
��Java����ʱϵͳ���յ��쳣����ʱ����Ѱ���ܴ�����һ�쳣�Ĵ��벢�ѵ�ǰ�쳣���󽻸��䴦����һ���̳�Ϊ����(catch)�쳣��
���Java����ʱϵͳ�Ҳ������Բ����쳣�ķ�����������ʱϵͳ����ֹ����Ӧ��Java����Ҳ���˳���
try/catch/finally��䡣

����RuntimeException��ͨ������Ҫ����ȥ���������쳣��Java����ϵͳ�Զ��׳����Զ�����
��������еķ����׳�����쳣���������еĸ��Ƿ���Ҫô�׳���ͬ���쳣��Ҫô�׳��쳣�����࣬�������׳��µ��쳣��ע�����췽�����⣩��
���ǿ����ڷ�������ʱ������һ�������׳����쳣��Java�������ͻ�ǿ�ȷ�����ʹ���߶��쳣���д������ַ�ʽͨ��Ӧ����abstract base class��interface�С�



//Excep.java
class Excep
{
	public int division(int a,int b)
	{
		return a/b;
	}
}

class ExcepTest
{
	public static void main(String[] args) //throws Exception
	{
		Excep excep = new Excep();
		excep.division( 5, 0 );
		System.out.println( "Finish" );//�������ǲ���ִ�е�
	}
}
E:\zieckey\Lesson4>java ExcepTest
Exception in thread "main" java.lang.ArithmeticException: / by zero
        at Excep.division(Excep.java:6)
        at ExcepTest.main(Excep.java:15)
�����Ǹ��쳣����,��0��

//Excep.java
class Excep
{
	public int division(int a,int b)
	{
		return a/b;
	}
}

class ExcepTest
{
	public static void main(String[] args) //throws Exception
	{
		Excep excep = new Excep();
		try
		{
			excep.division(5,0);
		}
		catch(Exception e)
		{
			System.out.println( "Can't divide by zero!" );
		}
		System.out.println( "Finish" );
	}
}

E:\zieckey\Lesson4>java ExcepTest
Can't divide by zero!
Finish


try�����е�����ڷ����쳣ʱ����ת��catch���

//Excep.java
class Excep
{
	public int division(int a,int b)
	{
		return a/b;
	}
}

class ExcepTest
{
	public static void main(String[] args) //throws Exception
	{
		Excep excep = new Excep();
		try
		{
			excep.division(5,0);//try�����е�����ڷ����쳣ʱ����ת��catch���
			System.out.println( "Exception" );//������ǲ���ִ�е�
		}
		catch(Exception e)
		{
			System.out.println( "Can't divide by zero!" );
		}
		System.out.println( "Finish" );
	}
}
E:\zieckey\Lesson4>javac Excep.java

E:\zieckey\Lesson4>java ExcepTest
Can't divide by zero!
Finish

��ӡ�쳣��Ϣ:
	catch(Exception e)
	{
		//�����ַ���������
		System.out.println(e.getMessage());
		System.out.println(e.toString());
		e.printStackTrace();
	}
������д�����ʱ��,�����д�Ĵ�����������쳣,��ô�ڱ�д��ʱ��ͽ����쳣����,
��������� a/b ��:
		try
		{
			return a/b;
		}
		catch(Exception e)
		{

			e.printStackTrace();
			return 0;
		}
��ô�ں�����õ�ʱ��Ͳ���Ҫ�����쳣������.
����ڱ�д�����ʱ�����Լ������쳣,��ô�����׳�һ���쳣,���û����õ�ʱ���Լ�����.
�����������,����:
//Excep.java
class Excep
{
	public int division(int a,int b) throws Exception
	{
		return a/b;
	}
}

class ExcepTest
{
	public static void main(String[] args) //throws Exception
	{
		Excep excep = new Excep();
		excep.division(5,0);
		System.out.println( "Finish" );
	}
}
E:\zieckey\Lesson4>javac Excep.java
Excep.java:15: δ������쳣 java.lang.Exception�����������в�׽�������Ա��׳�
                excep.division(5,0);
                              ^
1 ����
����͸����û��ڵ����׳��쳣�ĺ����򷽷�ʱ,��������쳣����.

����д���catch���

���ǻ������׳��Լ����쳣:
//Excep.java
class Excep
{
	public int division(int a,int b) throws Exception
	{
		try
		{
			return a/b;
		}
		catch(Exception e)
		{

			e.printStackTrace();
			throw new Exception( "Can't be divided by zero" );
		}
	}
}

class ExcepTest
{
	public static void main(String[] args) //throws Exception
	{
		Excep excep = new Excep();
		try
		{
			excep.division(5,0);
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		System.out.println( "Finish" );
	}
}
E:\zieckey\Lesson4>javac Excep.java

E:\zieckey\Lesson4>java ExcepTest
java.lang.ArithmeticException: / by zero
        at Excep.division(Excep.java:8)
        at ExcepTest.main(Excep.java:26)
java.lang.Exception: Can't be divided by zero
        at Excep.division(Excep.java:14)
        at ExcepTest.main(Excep.java:26)
Finish

E:\zieckey\Lesson4>


����,����Ҳ�����Զ����쳣:
//Excep.java
class Excep
{
	public int division(int a,int b) throws ArithmeticException,DivisorIsMinusException
	{
		//try
		//{
			if(b<0)
				throw new DivisorIsMinusException("Divisor can't be minus");
			return a/b;
		/*}
		catch(Exception e)
		{

			e.printStackTrace();
			throw new Exception( "Can't be divided by zero" );
		}*/
	}
}
class DivisorIsMinusException extends Exception
{
	DivisorIsMinusException(String str)
	{
		super(str);
	}
}

class ExcepTest
{
	public static void main(String[] args) //throws Exception
	{
		Excep excep = new Excep();
		try
		{
			excep.division(5,0);
		}
		catch(ArithmeticException e)
		{
			System.out.println(e.toString());
		}
		catch(DivisorIsMinusException ex)
		{
			System.out.println(ex.toString());
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		System.out.println( "Finish" );
	}
}
E:\zieckey\Lesson4>javac Excep.java

E:\zieckey\Lesson4>java ExcepTest
java.lang.ArithmeticException: / by zero
Finish
�����excep.division(5,-1);
��ô
E:\zieckey\Lesson4>javac Excep.java

E:\zieckey\Lesson4>java ExcepTest
DivisorIsMinusException: Divisor can't be minus
Finish


//Excep.java
class Excep
{
	public int division(int a,int b) throws ArithmeticException,DivisorIsMinusException
	{
		//try
		//{
			if(b<0)
				throw new DivisorIsMinusException("Divisor can't be minus");
			return a/b;
		/*}
		catch(Exception e)
		{

			e.printStackTrace();
			throw new Exception( "Can't be divided by zero" );
		}*/
	}
}
class DivisorIsMinusException extends Exception
{
	DivisorIsMinusException(String str)
	{
		super(str);
	}
}

class ExcepTest
{
	public static void main(String[] args) //throws Exception
	{
		Excep excep = new Excep();
		try
		{
			excep.division(5,-1);
			return;
		}
		catch(ArithmeticException e)
		{
			System.out.println(e.toString());
		}
		catch(DivisorIsMinusException ex)
		{
			System.out.println(ex.toString());
			return;
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		finally//�����쳣�������,�������䶼Ҫִ��
		{
			System.out.println("Finally");
		}
		System.out.println( "Finish" );
	}
}
E:\zieckey\Lesson4>javac Excep.java

E:\zieckey\Lesson4>java ExcepTest
DivisorIsMinusException: Divisor can't be minus
Finally

�����˵�������쳣�������,finally��䶼Ҫִ��,��ʹ����try��catch����return���.
������һ����ֹ����ķ��� System.exit ���Բ���finally���ִ��.



��������еķ����׳�����쳣���������еĸ��Ƿ���Ҫô�׳���ͬ���쳣��Ҫô�׳��쳣�����࣬�������׳��µ��쳣��ע�����췽�����⣩��

//Excep.java
class Excep
{
	public int division(int a,int b) throws ArithmeticException,DivisorIsMinusException
	{
		if(b<0)
			throw new DivisorIsMinusException("Divisor can't be minus");
		return a/b;
	}
}
class ChildExcep extends Excep
{
	public int division(int a,int b) throws FileNotFoundException
	{
		return a/b;
	}
}

class DivisorIsMinusException extends Exception
{
	DivisorIsMinusException(String str)
	{
		super(str);
	}
}

class ExcepTest
{
	public static void main(String[] args) //throws Exception
	{
		Excep excep = new Excep();
		try
		{
			excep.division(5,-1);
			return;
		}
		catch(ArithmeticException e)
		{
			System.out.println(e.toString());
		}
		catch(DivisorIsMinusException ex)
		{
			System.out.println(ex.toString());
			System.exit(-1);
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		finally//�����쳣�������,�������䶼Ҫִ��
		{
			System.out.println("Finally");
		}
		System.out.println( "Finish" );
	}
}
E:\zieckey\Lesson4>javac Excep.java
Excep.java:13: �Ҳ�������
���ţ� �� FileNotFoundException
λ�ã� �� ChildExcep
        public int division(int a,int b) throws FileNotFoundException
                                                ^
1 ����

���췽������,�����׳��������쳣.
//Excep.java
import java.io.*;
class Excep
{
	public int division(int a,int b) throws ArithmeticException,DivisorIsMinusException
	{
		if(b<0)
			throw new DivisorIsMinusException("Divisor can't be minus");
		return a/b;
	}
}
class ChildExcep extends Excep
{
	ChildExcep() throws FileNotFoundException
	{
	}
	public int division(int a,int b) throws ArithmeticException,DivisorIsMinusException
	{
		return a/b;
	}
}

class DivisorIsMinusException extends Exception
{
	DivisorIsMinusException(String str)
	{
		super(str);
	}
}

class ExcepTest
{
	public static void main(String[] args) //throws Exception
	{
		Excep excep = new Excep();
		try
		{
			excep.division(5,-1);
			return;
		}
		catch(ArithmeticException e)
		{
			System.out.println(e.toString());
		}
		catch(DivisorIsMinusException ex)
		{
			System.out.println(ex.toString());
			System.exit(-1);
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		finally//�����쳣�������,�������䶼Ҫִ��
		{
			System.out.println("Finally");
		}
		System.out.println( "Finish" );
	}
}


Ϊʲô�������е��׳��쳣ҪС�ڵ��ڸ����е��쳣�أ�
����Ϊ�˽�������������ʱ���������ͼ̳��õģ�
������Ĵ��룺
//Excep.java
import java.io.*;
class Excep
{
	public int division(int a,int b) throws ArithmeticException,DivisorIsMinusException
	{
		if(b<0)
			throw new DivisorIsMinusException("Divisor can't be minus");
		return a/b;
	}
}
class ChildExcep extends Excep
{
	ChildExcep() throws FileNotFoundException
	{
	}
	public int division(int a,int b) throws ArithmeticException,DivisorIsMinusException
	{
		return a/b;
	}
}

class DivisorIsMinusException extends Exception
{
	DivisorIsMinusException(String str)
	{
		super(str);
	}
}

class ExcepTest
{
	public static int method1(Excep excep)
	{
		try
		{
			return excep.division(5,0);
		}
		catch(ArithmeticException e)
		{
			System.out.println(e.toString());
		}
		catch(DivisorIsMinusException ex)
		{
			System.out.println(ex.toString());
		}
		return 0;
	}
	public static void main(String[] args) //throws Exception
	{
		ChildExcep ce=new ChildExcep();
		method1(ce);//����������������׳�������û�е��쳣��
					//��ô�̳����ķ�����û�ж����еĴ����꣬��������̳��ǲ���ȫ�ġ�
		Excep excep = new Excep();
		try
		{
			excep.division(5,-1);
			return;
		}
		catch(ArithmeticException e)
		{
			System.out.println(e.toString());
		}
		catch(DivisorIsMinusException ex)
		{
			System.out.println(ex.toString());
			System.exit(-1);
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		finally//�����쳣�������,�������䶼Ҫִ��
		{
			System.out.println("Finally");
		}
		System.out.println( "Finish" );
	}
}




Java��̹淶
1. package������ package ��������ȫ��Сд����ĸ��ɣ����磺cn.mybole��
2. class��interface������ class��interface�������ɴ�д��ĸ��ͷ��������ĸ��Сд�ĵ�����ɣ����磺Person��RuntimeException��
3. class���������� ������������һ��Сд��ĸ��ͷ������ĵ����ô�д��ĸ��ͷ,���磺index��currentImage��
4. class����������
   ������������һ��Сд��ĸ��ͷ������ĵ����ô�д��ĸ��ͷ,���磺run()��getBalance()��
5. static final���������� static final����������������ĸ����д�������ܱ�ʾ�������塣���磺PI��PASSWORD��
6. ���������� ���������ֺͱ����������淶һ�¡�
7. ��������� ����Ӧ�������������ķ�ʽ��������byte[] buffer��



Lesson4��
Java�ĳ��ð���
java.applet������һЩ���ڴ���JavaСӦ�ó�����ࡣ
java.awt������һЩ���ڱ�д��ƽ̨�޹ص�ͼ�ν���(GUI)Ӧ�ó�����ࡣ
java.io������һЩ�����������(I/O)������ࡣ
java.lang������һЩJava���ԵĻ�����������࣬��String��Math��Integer��System��Runtime���ṩ���õĹ��ܣ�������е��������Ǳ���ʽ����ġ�
java.net���������ڽ����������ӵ��࣬��java.ioͬʱʹ������������йصĶ�д��
java.util������һЩʵ�ù���������ݽṹ�ࡣ


��==���͡�equals�����÷�
��Java�У�boolean��byte��short��int��long��char��float��double������ǻ����������ͣ�����Ķ����������͡�
��==���ǱȽ�����������ֵ�Ƿ���ȣ���equals���ǱȽ������������������Ķ���������Ƿ���ȡ�


//StringTest.java
public class StringTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		String str1 = "abc";
		String str2 = "abc";
		if ( str1 == str2 ){
			System.out.println( "str1 == str2" );
		}
		else{
			System.out.println( "str1 != str2" );
		}
	}
}

E:\JavaLesson\Lesson5>javac StringTest.java
E:\JavaLesson\Lesson5>java StringTest
str1 == str2

//StringTest.java
public class StringTest {
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		String str1 = new String("abc");
		String str2 = new String("abc");
		if ( str1 == str2 ){
			System.out.println( "str1 == str2" );
		}
		else{
			System.out.println( "str1 != str2" );
		}
	}
}
E:\JavaLesson\Lesson5>javac StringTest.java
E:\JavaLesson\Lesson5>java StringTest
str1 != str2

//StringTest.java
/**
 * @author apple
 *
 */
public class StringTest {
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		String str1 = new String("abc");
		String str2 = new String("abc");
		if ( str1.equals(str2) ) {
			System.out.println( "str1 equals str2" );
		}
		else{
			System.out.println( "str1 don't equals str2" );
		}
	}
}
E:\JavaLesson\Lesson5>javac StringTest.java
E:\JavaLesson\Lesson5>java StringTest
str1 equals str2

�ַ����ġ�+����+=�����ز�����
//StringTest.java
/**
 * @author apple
 *
 */
public class StringTest {
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		String str1 = new String("abc");
		/*String str2 = new String("abc");
		if ( str1.equals(str2) ) {
			System.out.println( "str1 equals str2" );
		}
		else{
			System.out.println( "str1 don't equals str2" );
		}*/
		int i = 9;
		float f=5.6f;
		char ch = 'a';
		System.out.println( str1 + i + f + ch );
	}
}
E:\JavaLesson\Lesson5>javac StringTest.java
E:\JavaLesson\Lesson5>java StringTest
abc95.6a

String��StringBuffer
	String str=��abc��;
    int i=3;
    float f=4.5f;
    char ch='a';
    boolean b=true;
    System.out.println(str + i + f + ch + b);

    String�����һ����������
    String str=��abc��;
    str=��def��;
�ڴ�������ַ����ĳ����У�����ͨ����StringBuffer�����String��
���String�ġ�+���͡�+=������Java��Ψһ�����صĲ���������Java�У����������Ա���ز�������


//StringTest.java
/**
 * @author apple
 *
 */
public class StringTest {
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		String str1 = new String("abc");
		/*String str2 = new String("abc");
		if ( str1.equals(str2) ) {
			System.out.println( "str1 equals str2" );
		}
		else{
			System.out.println( "str1 don't equals str2" );
		}*/
		int i = 9;
		float f=5.6f;
		char ch = 'a';
		boolean b = false;
		//System.out.println( str1 + i + f + ch );
		StringBuffer sb=new StringBuffer();
		sb.append(str1).append(i).append(f).append(ch).append(b);
		System.out.println(sb.toString());
	}
}
E:\JavaLesson\Lesson5>javac StringTest.java
E:\JavaLesson\Lesson5>java StringTest
abc95.6afalse


���飺
//StringTest.java
/**
 * @author apple
 *
 */
public class StringTest
{
	/**
	 * @param args
	 */
	public static void main(String[] args)
	{
		// TODO Auto-generated method stub
		int[] num=new int[3];
		for(int i=0;i<num.length;i++)
		{
			System.out.println(num[i]);
		}
		num=null;//�øö����Ϊ�����ڴ棬֮��java������ͻ�����Ҫ��ʱ���������ڴ�
	}
}
E:\JavaLesson\Lesson5>javac StringTest.java
E:\JavaLesson\Lesson5>java StringTest
0
0
0


//StringTest.java
/**
 * @author apple
 *
 */
public class StringTest
{
	/**
	 * @param args
	 */
	public static void main(String[] args)
	{
		// TODO Auto-generated method stub
		Student[] students;
		students=new Student[3];
		for(int i=0;i<students.length;i++)
		{
			System.out.println(students[i]);
		}
	}
}

class Student
{
	String name;
	int age;
	Student( String name,int age )
	{
		this.name=name;
		this.age=age;
	}
}
E:\JavaLesson\Lesson5>javac StringTest.java
E:\JavaLesson\Lesson5>java StringTest
null
null
null

//StringTest.java
/**
 * @author apple
 *
 */
public class StringTest
{
	/**
	 * @param args
	 */
	public static void main(String[] args)
	{
		// TODO Auto-generated method stub
		Student[] students;
		students=new Student[3];//�˴���������������Student�����Ӧ�ã�����û�з����ڴ�ռ�
		System.out.println( students );
		for(int i=0;i<students.length;i++)
		{
			System.out.println(students[i]);
		}
		students[0] = new Student( "LiSi", 19 );//�˴��ſ�ʼ�����ڴ�ռ�
		students[1] = new Student( "ZhangSan", 21 );//students�����������ջ�ڴ�,
		students[2] = new Student( "WangMazi", 20 );//students[i]�������ڶ��ڴ�,
													//students[i]�ľ���ֵҲ�ڶ��ڴ�,
		for(int i=0;i<students.length;i++)
		{
			System.out.println(students[i]);
		}
	}
}
class Student
{
	String name;
	int age;
	Student( String name,int age )
	{
		this.name=name;
		this.age=age;
	}
}
E:\JavaLesson\Lesson5>javac StringTest.java

E:\JavaLesson\Lesson5>java StringTest
[LStudent;@757aef
null
null
null
Student@d9f9c3
Student@9cab16
Student@1a46e30

��ӡ�����в���:
		if(args.length>0)
		{
			for(int i=0;i<args.length;i++)
			{
				System.out.println(args[i]);
			}
		}

�����ĵ���:
��Java�У�����ʱ�������Դ�ֵ�ķ�ʽ���С�
���ڻ����������ͣ����ݵ������ݵĿ����������������ͣ����ݵ����õĿ�����
//StringTest.java
/**
 * @author apple
 *
 */
public class StringTest
{
	/**
	 * @param args
	 */
	public static void change(int x,int y)
	{
		x=x+y;
		y=x-y;
		x=x-y;
	}
	public static void change(int[] num)
	{
		num[0]=num[0]+num[1];
		num[1]=num[0]-num[1];
		num[0]=num[0]-num[1];
	}
	public static void change(Point pt)
	{
		pt.x=pt.x+pt.y;
		pt.y=pt.x-pt.y;
		pt.x=pt.x-pt.y;
	}
	public static void main(String[] args)
	{
		int x=3;
		int y=4;
		change(x,y);
		System.out.println("change(int x,int y)"+"x="+x+","+"y="+y);//���ﲻ�ύ��
		int[] num=new int[]{3,4};
		change(num);
		System.out.println("change(int[] num)"+"x="+num[0]+","+"y="+num[1]);
		Point pt=new Point();
		pt.x=3;
		pt.y=4;
		change(pt);
		System.out.println("change(Point pt)"+"x="+pt.x+","+"y="+pt.y);
	}
}
class Student
{
	String name;
	int age;
	Student( String name,int age )
	{
		this.name=name;
		this.age=age;
	}
}
class Point
{
	int x,y;
}
E:\JavaLesson\Lesson5>javac StringTest.java

E:\JavaLesson\Lesson5>java StringTest
change(int x,int y)x=3,y=4
change(int[] num)x=4,y=3
change(Point pt)x=4,y=3



class StringTest
{
	public static void change(Point pt)
	{
		pt.x=pt.x+pt.y;
		pt.y=pt.x-pt.y;
		pt.x=pt.x-pt.y;
	}
	public static void main(String[] args)
	{
		Point pt=new Point();
		pt.x=3;
		pt.y=4;
		change(pt);
		System.out.println("x="+pt.x);
		System.out.println("y="+pt.y);
	}
}
class Point{int x, y;}


�ڴ�ӡһ��������ʱ��,����:
	class Point{int x, y;}
	Point pt=new Point();
	System.out.println(pt);//�����ӡ�ĺܿ����ǣ���Point@9cab16��֮�����Ϣ

�������Զ�����Object:toString()����,ȥ��ӡһ�������������Ϣ,
����������Object:toString()�÷�����ʱ�򣬾Ϳ��Դ�ӡ�����Լ��������Ϣ�����磺
	class Point
	{
		int x, y;
		public String toString()
		{
			return "x="+x+","+"y="+y;
		}
	}
	Point pt=new Point();
	System.out.println(pt);//�����ӡ�ĺܿ����ǣ���x=3,y=6��֮�����Ϣ��


����Ŀ�¡(clone)
Ϊ�˻�ȡ�����һ�ݿ��������ǿ�������Object���clone()������
���������и��ǻ����clone()������������Ϊpublic��
���������clone()�����У�����super.clone()��
����������ʵ��Cloneable�ӿڡ�

Ϊʲô�������������и���Object��clone()����ʱ��һ��Ҫ����super.clone()�أ�
������ʱ�̣�Object�е�clone()ʶ�����Ҫ���Ƶ�����һ������
Ȼ��Ϊ�˶������ռ䣬�����ж���ĸ��ƣ���ԭʼ���������һһ���Ƶ��¶���Ĵ洢�ռ��С�

//StringTest.java
public class StringTest
{
	public static void main(String[] args)
	{
		Student s1=new Student("zhangsan",18 );
		Student s2=(Student)s1.clone();
		s2.name="lisi";
		s2.age=20;
		System.out.println("name="+s1.name+","+"age="+s1.age);
	}
}
class Student implements Cloneable
{
	String name;
	int age;
	Student( String name,int age )
	{
		this.name=name;
		this.age=age;
	}
	public Object clone()
	{
		Object o=null;
		try
		{
			o=(Object)super.clone();
		}
		catch(CloneNotSupportedException e)
		{
			System.out.println(e.toString());
		}
		return o;
	}
}
E:\JavaLesson\Lesson5>javac StringTest.java

E:\JavaLesson\Lesson5>java StringTest
name=zhangsan,age=18
���˵����û�иı�ԭ���Ķ����ֵ



//StringTest.java
public class StringTest
{
	public static void main(String[] args)
	{
		Professor p=new Professor("wangwu",50);
		Student s1=new Student("zhangsan",18,p);
		Student s2=(Student)s1.clone();
		s2.p.name="lisi";
		s2.p.age=30;
		//System.out.println("name="+s1.name+","+"age="+s1.age);
		System.out.println("name="+s1.p.name+","+"age="+s1.p.age);
	}
}

class Professor
{
	String name;
	int age;
	Professor(String name,int age)
	{
		this.name=name;
		this.age=age;
	}
}

class Student implements Cloneable
{
	String name;
	int age;
	Professor p;
	Student( String name,int age, Professor p)
	{
		this.name = name;
		this.age = age;
		this.p = p;
	}
	public Object clone()
	{
		Object o=null;
		try
		{
			o=(Object)super.clone();
		}
		catch(CloneNotSupportedException e)
		{
			System.out.println(e.toString());
		}
		return o;
	}
}
�������к�name=lisi,age=30
�����˵���˶�s2���޸�Ӱ�쵽��s1��Professor����p��ֵ��
����Ϊʲô�أ�
�������룬clone�����Ƕ��������б���ֵ������һ�ο�����
ǰ�����ǵ�����age�����ǻ������ͱ��������Կ����������ݣ�
�����ǵ�Professor����p���������ͣ����Կ����������ã�������û�п�����
���������޸ĵ�ʱ�򣬽�Professor�����p��ֵҲ�޸��ˡ�
�����������뵽��ΪʲôString�Ķ���nameҲ�����ã�Ϊʲôû�б��޸��أ�
�ǲ���StringҲ������clone�����أ�
û�У�����ȥ����String��İ����ĵ���
��������Ϊ��һ��String������һ����������
String str = ��Zhangsan�����������൱����������һ��Zhangsan�Ķ���
Ȼ�������ø�ֵ��str��������clone��ʱ���û��Ӱ�쵽ԭ���ı�����

��ô������ν�Professor��ͬ��ĸ���һ���أ�


//StringTest.java
public class StringTest
{
	public static void main(String[] args)
	{
		Professor p=new Professor("wangwu",50);
		Student s1=new Student("zhangsan",18,p);
		Student s2=(Student)s1.clone();
		s2.p.name="lisi";
		s2.p.age=30;
		System.out.println("name="+s1.p.name+","+"age="+s1.p.age);
	}
}

class Professor implements Cloneable
{
	String name;
	int age;
	Professor(String name,int age)
	{
		this.name=name;
		this.age=age;
	}
	public Object clone()
	{
		Object o=null;
		try
		{
			o=super.clone();
		}
		catch(CloneNotSupportedException e)
		{
			System.out.println(e.toString());
		}
		return o;
	}
}
class Student implements Cloneable
{
	String name;
	int age;
	Professor p;
	Student(String name,int age,Professor p)
	{
		this.name=name;
		this.age=age;
		this.p=p;
	}
	public Object clone()
	{
		Student o=null;
		try
		{
			o=(Student)super.clone();
		}
		catch(CloneNotSupportedException e)
		{
			System.out.println(e.toString());
		}
		o.p=(Professor)p.clone();
		return o;
	}
}
�������к�name=wangwu,age=50

Ϊʲô�������������и���Object��clone()����ʱ��һ��Ҫ����super.clone()�أ�
������ʱ�̣�Object�е�clone()ʶ�����Ҫ���Ƶ�����һ������
Ȼ��Ϊ�˶������ռ䣬�����ж���ĸ��ƣ���ԭʼ���������һһ���Ƶ��¶���Ĵ洢�ռ��С�


Lesson6

����Թط�����

����Ŀ�����System.arraycopy
//ArrayTest.java
public class ArrayTest
{
	public static void main(String[] args)
	{
		int[] num1=new int[]{1,2,3};
		int[] num2=new int[10];
		System.arraycopy(num1,0,num2,8,2);
		for(int i=0;i<num2.length;i++)
		{
			System.out.println(num2[i]);
		}
	}
}

�����������ĸ��ƣ�
//ArrayTest.java
public class ArrayTest
{
	public static void main(String[] args)
	{
		Point[] pts1=new Point[]{new Point(1,1),new Point(2,2),new Point(3,3)};
		Point[] pts2=new Point[3];
		System.arraycopy(pts1,0,pts2,0,pts1.length);
		for(int i=0;i<pts2.length;i++)
		{
			System.out.println("x="+pts2[i].x+","+"y="+pts2[i].y);
		}
		pts2[1].x=5;
		pts2[1].y=5;
		System.out.println("x="+pts1[1].x+","+"y="+pts1[1].y);//���������Ƕ��������
	}
}
class Point
{
	int x,y;
	Point(int x,int y)
	{
		this.x=x;
		this.y=y;
	}
}
���н����
x=1,y=1
x=2,y=2
x=3,y=3
x=5,y=5
�ӽ���Ϳ��Կ�����������Ŀ���ʱ�ǿ����Ķ�������ã�
�����󣬶Կ����Ķ�����в����ᷴӳ��ԭ�����ϡ�

���������
//ArrayTest.java
import java.util.Arrays;
public class ArrayTest
{
	public static void main(String[] args)
	{
		int[] num=new int[]{3,1,2};
		Arrays.sort(num);
		for(int i=0;i<num.length;i++)
		{
			System.out.println(num[i]);
		}
		int index=Arrays.binarySearch(num,3);
		System.out.println("index="+index);
		System.out.println("element="+num[index]);
	}
}
���н��
1
2
3
index=2
element=3


����Ҫ��һ����������������򣬾�Ҫʵ��һ�� compareTo�ӿ�
���磺
//ArrayTest.java
import java.util.Arrays;
public class ArrayTest
{
	public static void main(String[] args)
	{
		Student[] ss=new Student[]{new Student(3,"zhangsan"),
				   new Student(2,"lisi"),
				   new Student(4,"wangwu"),
				   new Student(4,"mybole")};
		Arrays.sort(ss);
		for(int i=0;i<ss.length;i++)
		{
			System.out.println(ss[i]);
		}
		}
}
class Student implements Comparable
{
	int num;
	String name;
	Student(int num,String name)
	{
		this.num=num;
		this.name=name;
	}
	public String toString()
	{
		return "number="+num+","+"name="+name;
	}
	public int compareTo(Object o)
	{
		Student s=(Student)o;
		int result=num>s.num ? 1 : (num==s.num ? 0 : -1);
		if(0==result)
		{
			result=name.compareTo(s.name);//
		}
		return result;
	}
}
���н����
number=2,name=lisi
number=3,name=zhangsan
number=4,name=mybole
number=4,name=wangwu

ͬ������Ҳ����ͨ��Arrays.binarySearch������������������
		int index=Arrays.binarySearch(ss,new Student(2,"lisi"));
		System.out.println("index="+index);
		System.out.println(ss[index]);




��԰��ֻ����������Ͷ������Ӧ���������ͣ���װ�ࡣ
������������	��װ��
	boolean	Boolean
	byte	Byte
	short	Short
	int		Integer
	long	Long
	char	Character
	float	Float
	double	Double


class Test
{
	public static void main(String[] args)
	{
		int i=3;
		Integer in=new Integer(i);
		int j=in.intValue();
		System.out.println("j="+j);
		String str=in.toString();
		System.out.println("str="+str);

		String str2="134";
		System.out.println(Integer.valueOf(str2));
	}
}




��Class
//ClassTest.java
public class ClassTest
{
	public static void main(String[] args)
	{
		Point pt=new Point();
		Class c1=pt.getClass();
		System.out.println(c1.getName());

		try
		{
			Class c2=Class.forName("Point");
			System.out.println(c2.getName());
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}

		Class c3=Point.class;
		System.out.println(c3.getName());

		Class c4=int.class;
		System.out.println(c4.getName());

		Class c5=Integer.TYPE;
		System.out.println(c5.getName());

		Class c6=Integer.class;
		System.out.println(c6.getName());
	}
}

class Point
{
	int x,y;
}





//ClassTest.java
public class ClassTest
{
	public static void main(String[] args)
	{
		System.out.println( "Before new point" );
		new Point();
		System.out.println( "After new point" );


		try
		{
			Class c2=Class.forName("Line");
			System.out.println(c2.getName());
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
	}
}

class Point
{
	static
	{
		System.out.println( "Loading Point...." );
	}
	int x,y;
}
class Line
{
	static
	{
		System.out.println( "Loading Line...." );
	}
}
//���ǿ���������
E:\zieckey\Lesson6>javac ClassTest.java

E:\zieckey\Lesson6>java ClassTest
Before new point
Loading Point....
After new point
Loading Line....
Line
�ɿ��Կ���ֻ�����౻���õ�ʱ�򣬲�ִ��static�еĴ����

Class��
�������ڼ䣬�������Ҫ����ĳ����Ķ���Java�����(JVM)��������͵�Class�����Ƿ��ѱ����ء����û�б����أ�JVM�������������ҵ�.class�ļ�����������һ��ĳ�����͵�Class�����ѱ����ص��ڴ棬�Ϳ������������������͵����ж���
newInstance() ��������ȱʡ�Ĺ��췽����
//ClassTest.java
public class ClassTest
{
	public static void main(String[] args)
	{
		if(args.length!=1)
		{
			return;
		}
		try
		{
			Class c=Class.forName(args[0]);
			Point pt=(Point)c.newInstance();//����һ��c��������ʵ��
			pt.output();
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		finally
		{
			System.out.println( "Finish" );
		}
	}
}

class Point
{
	static
	{
		System.out.println( "Loading Point...." );
	}
	int x,y;
	void output()
	{
		System.out.println("x="+x+","+"y="+y);
	}
}
class Line
{
	static
	{
		System.out.println( "Loading Line...." );
	}
}

E:\zieckey\Lesson6>javac ClassTest.java

E:\zieckey\Lesson6>java ClassTest abc
java.lang.ClassNotFoundException: abc
        at java.net.URLClassLoader$1.run(URLClassLoader.java:200)
        at java.security.AccessController.doPrivileged(Native Method)
        at java.net.URLClassLoader.findClass(URLClassLoader.java:188)
        at java.lang.ClassLoader.loadClass(ClassLoader.java:306)
        at sun.misc.Launcher$AppClassLoader.loadClass(Launcher.java:268)
        at java.lang.ClassLoader.loadClass(ClassLoader.java:251)
        at java.lang.ClassLoader.loadClassInternal(ClassLoader.java:319)
        at java.lang.Class.forName0(Native Method)
        at java.lang.Class.forName(Class.java:164)
        at ClassTest.main(ClassTest.java:12)
Finish

E:\zieckey\Lesson6>java ClassTest Point
Loading Point....
x=0,y=0
Finish


//ClassTest.java
public class ClassTest
{
	public static void main(String[] args)
	{
		if(args.length!=1)
		{
			return;
		}
		try
		{
			Class c=Class.forName(args[0]);
			Point pt=(Point)c.newInstance();//����һ��c��������ʵ��
			pt.output();
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		finally
		{
			System.out.println( "Finish" );
		}
	}
}

class Point
{
	static
	{
		System.out.println( "Loading Point...." );
	}
	int x,y;
	void output()
	{
		System.out.println("x="+x+","+"y="+y);
	}
	Point(int x,int y)
	{
		this.x=x;
		this.y=y;
	}
}
class Line
{
	static
	{
		System.out.println( "Loading Line...." );
	}
}
E:\zieckey\Lesson6>javac ClassTest.java

E:\zieckey\Lesson6>java ClassTest

E:\zieckey\Lesson6>java ClassTest Point
Loading Point....
java.lang.InstantiationException: Point
        at java.lang.Class.newInstance0(Class.java:335)
        at java.lang.Class.newInstance(Class.java:303)
        at ClassTest.main(ClassTest.java:13)
Finish
��������Ϊ��newInstance���õ������ȱʡ���캯����
�������ǵ�Point���Ѿ��ṩ�˹��캯���������ڵ��õ�ʱ��ͳ����ˡ�
��ô������ν���أ�
//ClassTest.java
public class ClassTest
{
	public static void main(String[] args)
	{
		if(args.length!=1)
		{
			return;
		}
		try
		{
			Class c=Class.forName(args[0]);
			Constructor[] cons=c.getDeclaredConstructors();//�õ����캯������
			for(int i=0;i<cons.length;i++)
			{
				System.out.println(cons[i]);
			}
			Method[] ms=c.getDeclaredMethods();//�õ���ķ�������
			for(int i=0;i<ms.length;i++)
			{
				System.out.println(ms[i]);
			}
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		finally
		{
			System.out.println( "Finish" );
		}
	}
}
E:\zieckey\Lesson6>javac ClassTest.java
ClassTest.java:13: �Ҳ�������
���ţ� �� Constructor
λ�ã� �� ClassTest
                        Constructor[] cons=c.getDeclaredConstructors();//�õ���
�캯������
                        ^
ClassTest.java:18: �Ҳ�������
���ţ� �� Method
λ�ã� �� ClassTest
                        Method[] ms=c.getDeclaredMethods();//�õ���ķ�������
                        ^
2 ����

getDeclaredConstructors()����java.lang.reflect���ж���ģ�����Ҫ����ð���


//ClassTest.java
import java.lang.reflect.*;
public class ClassTest
{
	public static void main(String[] args)
	{
		if(args.length!=1)
		{
			return;
		}
		try
		{
			Class c=Class.forName(args[0]);
			Constructor[] cons=c.getDeclaredConstructors();//�õ����캯������
			for(int i=0;i<cons.length;i++)
			{
				System.out.println(cons[i]);
			}
			Method[] ms=c.getDeclaredMethods();//�õ���ķ�������
			for(int i=0;i<ms.length;i++)
			{
				System.out.println(ms[i]);
			}
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		finally
		{
			System.out.println( "Finish" );
		}
	}
}

class Point
{
	static
	{
		System.out.println( "Loading Point...." );
	}
	int x,y;
	void output()
	{
		System.out.println("x="+x+","+"y="+y);
	}
	void func()
	{
		System.out.println( "func....." );
	}

	Point(int x,int y)
	{
		this.x=x;
		this.y=y;
	}
}
class Line
{
	static
	{
		System.out.println( "Loading Line...." );
	}
}

E:\zieckey\Lesson6>javac ClassTest.java

E:\zieckey\Lesson6>java ClassTest Point
Loading Point....
Point(int,int)
void Point.func()
void Point.output()
Finish

E:\zieckey\Lesson6>java abv
Exception in thread "main" java.lang.NoClassDefFoundError: abv

E:\zieckey\Lesson6>java ClassTest jdaj
java.lang.ClassNotFoundException: jdaj
        at java.net.URLClassLoader$1.run(URLClassLoader.java:200)
        at java.security.AccessController.doPrivileged(Native Method)
        at java.net.URLClassLoader.findClass(URLClassLoader.java:188)
        at java.lang.ClassLoader.loadClass(ClassLoader.java:306)
        at sun.misc.Launcher$AppClassLoader.loadClass(Launcher.java:268)
        at java.lang.ClassLoader.loadClass(ClassLoader.java:251)
        at java.lang.ClassLoader.loadClassInternal(ClassLoader.java:319)
        at java.lang.Class.forName0(Native Method)
        at java.lang.Class.forName(Class.java:164)
        at ClassTest.main(ClassTest.java:13)
Finish

���濴����ô��̬����һ����֪���������ĳ�Ա����,ͨ��������ʵ��
//ClassTest.java
import java.lang.reflect.*;
public class ClassTest
{
	public static void main(String[] args)
	{
		if(args.length!=1)
		{
			return;
		}
		try
		{
			Class c=Class.forName(args[0]);
			Constructor[] cons=c.getDeclaredConstructors();//�õ����캯������
			Class[] params=cons[0].getParameterTypes();
			Object[] paramValues=new Object[params.length];
			for(int i=0;i<params.length;i++)
			{
				if(params[i].isPrimitive())
				{
					paramValues[i]=new Integer(i+3);
				}
			}
			Object o=cons[0].newInstance(paramValues);
			Method[] ms=c.getDeclaredMethods();
			ms[0].invoke(o);

		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		finally
		{
			System.out.println( "Finish" );
		}
	}
}

class Point
{
	static
	{
		System.out.println( "Loading Point...." );
	}
	int x,y;
	void output()
	{
		System.out.println("x="+x+","+"y="+y);
	}
	Point(int x,int y)
	{
		this.x=x;
		this.y=y;
	}
}
class Line
{
	static
	{
		System.out.println( "Loading Line...." );
	}
}

E:\zieckey\Lesson6>javac ClassTest.java

E:\zieckey\Lesson6>java ClassTest

E:\zieckey\Lesson6>java ClassTest Point
Loading Point....
x=3,y=4
Finish


Runtime���Process��
ÿһ��Java������һ��Runtime��ĵ�һʵ����
���ʵ�����Եõ����иó���Ļ�����һЩ������Ϣ�������ڴ�ʹ�����ȵȣ�
���ṩ��Ӧ�ó���ͻ���֮��Ľӿڡ�
ͨ��Runtime.getRuntime()��ȡRuntime���ʵ����
Runtime����ʹ�õ���ģʽ��һ�����ӡ�


//RuntimeTest.java
class RuntimeTest
{
	public static void main(String[] args)
	{
		Runtime rt=Runtime.getRuntime();
		System.out.println( "freeMemory:" + rt.freeMemory());
		System.out.println( "totalMemory:" + rt.totalMemory());
	}
}
E:\zieckey\Lesson6>javac RuntimeTest.java

E:\zieckey\Lesson6>java RuntimeTest
freeMemory:1836224
totalMemory:2031616

���Runtime�໹����ִ��һ���ⲿ�ĳ������磺
//RuntimeTest.java
class RuntimeTest
{
	public static void main(String[] args)
	{
		Runtime rt=Runtime.getRuntime();
		try
		{
			rt.exec("notepad");
			System.out.println("Notepad is running...");
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}

	}
}
E:\zieckey\Lesson6>javac RuntimeTest.java

E:\zieckey\Lesson6>java RuntimeTest
Notepad is running...
���ʱ�򣬼��±������Ѿ�����������

//RuntimeTest.java
import java.io.*;
class RuntimeTest
{
	public static void main(String[] args)
	{

		try
		{
			Runtime rt1=Runtime.getRuntime();
			rt1.exec("javac Test.java");	//����
			Runtime rt2=Runtime.getRuntime();
			Process p = rt2.exec("java Test");	//���У�
			InputStream is=p.getInputStream();//��ȡ������"java Test"������������
			int data;
			while((data=is.read())!=-1)
			{
				System.out.print((char)data);
			}
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
	}
}

E:\zieckey\Lesson6>javac RuntimeTest.java

E:\zieckey\Lesson6>java RuntimeTest
j=3
str=3
134

E:\zieckey\Lesson6>java Test
j=3
str=3
134

���Կ������ǻ������ڴ˱������Ȼ�����г��򣬲�����ӡ��Ϣ��ӡ������
�ߺ͵�������Test.java����һ��


���ģʽ
�����ǽ��г������ʱ�����γ���һЩ�������������Ľ����������������ģʽ��
ÿһ��ģʽ������һ�������ǳ�������о������������⣬�Լ�������Ľ��������
����������ģʽ�����������⣬�Ϳ���ֱ������Ӧ�Ľ������ȥ���������⣬��������ģʽ��

������Singleton��ģʽ
   ��1��һ����ֻ��һ��ʵ������������ʵ������������ϵͳ�ṩ���ʵ����������Ϊ�����ࡣ
   ��2���������һ������Ҫ���ص�����Ĺ��췽����˽�еģ��Ӷ��������ⲿ���ù��췽��ֱ�Ӵ������ʵ����
class Singleton
{
	private static final Singleton st=new Singleton();
	private Singleton(){}
	public static Singleton getInstance()
	{
		return st;
	}
}

���ģʽ�ο��鼮��
�� Java��ģʽ��
  ���ߣ��ֺ�
  ���ӹ�ҵ���������


Lesson7
���߳�

���򡢽��̺��߳�
	�����Ǽ����ָ��ļ��ϣ������ļ�����ʽ�洢�ڴ����ϡ�
	���̣���һ��������������ĵ�ַ�ռ��е�һ��ִ�л��
	��������Դ���롢���ȺͶ������еĵ�λ����ˣ���ʹ��ϵͳ�е�������Դ��
������������ϵͳ��Դ�����ܱ�ϵͳ���ȣ�Ҳ������Ϊ�������еĵ�λ��
��ˣ�����ռ��ϵͳ��������Դ��
	�̣߳��ǽ����е�һ����һ�������������̡�һ�����̿���ӵ�ж���̡߳�
�߳��ֳ�Ϊ���������̣����ͽ���һ��ӵ�ж�����ִ�п��ƣ�
�ɲ���ϵͳ������ȣ����������߳�û�ж����Ĵ洢�ռ䣬
���Ǻ����������е������̹߳���һ���洢�ռ䣬��ʹ���̼߳��ͨ��Զ�Ͻ��̼򵥡�

Java�Զ��̵߳�֧��
Java�����Լ��ṩ�˶Զ��̳߳�����Ƶ�֧�֡�
ʵ�ֶ��̳߳�������ַ�ʽ��
    ��1����Thread��̳У�
    ��2��ʵ��Runnable�ӿڡ�
Java����ʱϵͳʵ����һ�����ڵ����߳�ִ�е��̵߳�����������ȷ��ĳһʱ������һ���߳���CPU�����С�
��java�����У��߳�ͨ������ռʽ�Ķ�����Ҫʱ��Ƭ������̣������ÿ���߳���ȵ�CPUʱ��Ľ��̣�����ռʽ����ģ�;�������̴߳��ڿ�������״̬���ȴ�״̬������ʵ����ֻ��һ���߳������С����߳�һֱ���е�����ֹ���������״̬���ȴ�״̬����������һ�����и������ȼ����̱߳�ɿ�����״̬���ں�һ������£������ȼ����̱߳������ȼ����߳���ռ�������ȼ����̻߳�����еĻ��ᡣ
Java�̵߳�����֧�ֲ�ͬ���ȼ��̵߳����ȷ�ʽ�����䱾��֧����ͬ���ȼ��̵߳�ʱ��Ƭ�ֻ���
Java����ʱϵͳ���ڵĲ���ϵͳ�����磺Windows2000��֧��ʱ��Ƭ���ֻ������̵߳�������֧����ͬ���ȼ��̵߳�ʱ��Ƭ�ֻ���
There are two ways to create a new thread of execution. One is to declare a class to be a subclass of Thread. This subclass should override the run method of class Thread. An instance of the subclass can then be allocated and started. For example, a thread that computes primes larger than a stated value could be written as follows:



--------------------------------------------------------------------------------

     class PrimeThread extends Thread {
         long minPrime;
         PrimeThread(long minPrime) {
             this.minPrime = minPrime;
         }

         public void run() {
             // compute primes larger than minPrime
              . . .
         }
     }

--------------------------------------------------------------------------------

The following code would then create a thread and start it running:


     PrimeThread p = new PrimeThread(143);
     p.start();
 The other way to create a thread is to declare a class that implements the Runnable interface. That class then implements the run method. An instance of the class can then be allocated, passed as an argument when creating Thread, and started. The same example in this other style looks like the following:



--------------------------------------------------------------------------------

     class PrimeRun implements Runnable {
         long minPrime;
         PrimeRun(long minPrime) {
             this.minPrime = minPrime;
         }

         public void run() {
             // compute primes larger than minPrime
              . . .
         }
     }

--------------------------------------------------------------------------------

The following code would then create a thread and start it running:


     PrimeRun p = new PrimeRun(143);
     new Thread(p).start();
 Every thread has a name for identification purposes. More than one thread may have the same name. If a name is not specified when a thread is created, a new name is generated for it.





//MutiThread.java
class MutiThread
{
	public static void main( String[]args )
	{
		MyThread mt=new MyThread();//����һ���߳�
		mt.start();//���߳̿�ʼ����
		System.out.println("main:"+Thread.currentThread().getName());
	}
}

class MyThread extends Thread//����һ���߳�
{
	public void run()
	{
		System.out.println( getName() );
	}
}
E:\zieckey\Lesson7>javac MutiThread.java

E:\zieckey\Lesson7>java MutiThread
main:main
Thread-0

Thread-0�����jvm�����Ƿ����һ������
����Ӧ�ÿ������ȴ�ӡmain�������߳����֣�����Ŵ�ӡ�����Զ�����̡߳�

�������߳�ѭ��������CPU�������߳�֮����л���
//MutiThread.java
class MutiThread
{
	public static void main( String[]args )
	{
		MyThread mt=new MyThread();//����һ���߳�
		mt.start();//���߳̿�ʼ����
		while ( true )
		{
			System.out.println("main:"+Thread.currentThread().getName());
		}
	}
}

class MyThread extends Thread//����һ���߳�
{
	public void run()
	{
		while ( true )
		{
			System.out.println( getName() );
		}
	}
}
E:\zieckey\Lesson7>javac MutiThread.java

E:\zieckey\Lesson7>java MutiThread
main:main
main:main
main:main
main:main
main:main
main:main
main:main
main:main
main:main
main:main
main:main
main:main
main:main
main:main
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
main:main
main:main
main:main
main:main
main:main
main:main
main:main
main:main
main:main
main:main
main:main
main:main
main:main
main:main
main:main
main:main
main:main
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
main:main
main:main
main:main
main:main
main:main
main:main
main:main
main:main
main:main
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
main:main
main:main
main:main
main:main
main:main
main:main
main:main
main:main
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
main:main
main:main
main:main
main:main
main:main
main:main
main:main
main:main
main:main
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
main:main
main:main
main:main
main:main
main:main
main:main
main:main
main:main
main:main
main:main
main:main
main:main
main:main
......


���ú�̨�̣߳�setDaemon
//MutiThread.java
class MutiThread
{
	public static void main( String[]args )
	{
		MyThread mt=new MyThread();//����һ���߳�
		mt.setDaemon(true);//���ú�̨�߳�,����������߳�����֮ǰ����
		mt.start();//���߳̿�ʼ����
		int i=0;
		while ( true )
		{
			if ( i++ == 5 )
				break;
			System.out.println("main:"+Thread.currentThread().getName());
		}
	}
}

class MyThread extends Thread//����һ���߳�
{
	public void run()
	{
		while ( true )
		{
			System.out.println( getName() );
		}
	}
}

E:\zieckey\Lesson7>javac MutiThread.java

E:\zieckey\Lesson7>java MutiThread
main:main
main:main
main:main
main:main
main:main
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
����Ϳ��Կ���main���������󣬺�̨�߳�Ҳ�����ˡ�

�������ͨ��yield();����ʹ�̷߳���ִ�ж��������߳�ִ�У�
//MutiThread.java
class MutiThread
{
	public static void main( String[]args )
	{
		MyThread mt=new MyThread();//����һ���߳�
		mt.setDaemon(true);//���ú�̨�߳�,����������߳�����֮ǰ����
		mt.start();//���߳̿�ʼ����
		int i=0;
		while ( true )
		{
			if ( i++ == 500 )
				break;
			System.out.println("main:"+Thread.currentThread().getName());
		}
	}
}

class MyThread extends Thread//����һ���߳�
{
	public void run()
	{
		while ( true )
		{
			System.out.println( getName() );
			yield();
		}
	}
}
E:\zieckey\Lesson7>javac MutiThread.java

E:\zieckey\Lesson7>java MutiThread
main:main
main:main
main:main
main:main
main:main
main:main
main:main
main:main
main:main
Thread-0
main:main
main:main
main:main
main:main
main:main
main:main
main:main
main:main
main:main
Thread-0
main:main
main:main
main:main
main:main
main:main
main:main
main:main
main:main
main:main
Thread-0
main:main
main:main
main:main
main:main
main:main
main:main
main:main
main:main
main:main
Thread-0
main:main
main:main
main:main
main:main
main:main
main:main
main:main
main:main
main:main
Thread-0
main:main
main:main
main:main
main:main
main:main
main:main
main:main
���￴�Կ���ÿ��MyThreadִ��һ�Σ�����ӡ�����ֺ�����ִֹͣ���ˣ�
Ȼ��CPUת��main�̣߳���main�̵߳�ʱ��Ƭ������лص�MyThread

�̻߳������������ȼ���setPriority( int )         getPriority
//MutiThread.java
class MutiThread
{
	public static void main( String[]args )
	{
		MyThread mt=new MyThread();//����һ���߳�
		mt.start();//���߳̿�ʼ����
		mt.setPriority(Thread.MAX_PRIORITY);
		int i=0;
		while ( true )
		{
			if ( i++ == 5000 )
				break;
			System.out.println("main:"+Thread.currentThread().getName());
		}
	}
}

class MyThread extends Thread//����һ���߳�
{
	public void run()
	{
		while ( true )
		{
			System.out.println( getName() );
			yield();
		}
	}
}
E:\zieckey\Lesson7>javac MutiThread.java

E:\zieckey\Lesson7>java MutiThread
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
main:main
main:main
main:main
main:main

������Կ��������ȼ��� MyThread �߳�ʼ�ջ��CPU��ִ�У�ֻ�е������û���ֹ��ʱ��
main�̲߳Ż��һ���CPUִ�С�

Java����ʱϵͳʵ����һ�����ڵ����߳�ִ�е��̵߳�������
����ȷ��ĳһʱ������һ���߳���CPU�����С�
��java�����У��߳�ͨ������ռʽ�Ķ�����Ҫʱ��Ƭ�������
�������ÿ���߳���ȵ�CPUʱ��Ľ��̣���
��ռʽ����ģ�;�������̴߳��ڿ�������״̬���ȴ�״̬����
��ʵ����ֻ��һ���߳������С����߳�һֱ���е�����ֹ���������״̬���ȴ�״̬����
������һ�����и������ȼ����̱߳�ɿ�����״̬���ں�һ������£�
�����ȼ����̱߳������ȼ����߳���ռ�������ȼ����̻߳�����еĻ��ᡣ
Java�̵߳�����֧�ֲ�ͬ���ȼ��̵߳����ȷ�ʽ��
���䱾��֧����ͬ���ȼ��̵߳�ʱ��Ƭ�ֻ���
Java����ʱϵͳ���ڵĲ���ϵͳ�����磺Windows2000��֧��ʱ��Ƭ���ֻ���
���̵߳�������֧����ͬ���ȼ��̵߳�ʱ��Ƭ�ֻ���

������ͨ���̳�Thread���������̣߳�
�������ǿ������ͨ��ʵ��Runnable�ӿ��������̡߳�
//MutiThread.java
class MutiThread
{
	public static void main( String[]args )
	{
		MyThread mt=new MyThread();//����һ���߳�
		new Thread( mt ).start();
		int i=0;
		while ( true )
		{
			if ( i++ == 5000 )
				break;
			System.out.println( "main:"+Thread.currentThread().getName() );
		}
	}
}

class MyThread implements Runnable//extends Thread//����һ���߳�
{
	public void run()
	{
		while ( true )
		{
			System.out.println( Thread.currentThread().getName() );
		}
	}
}
E:\zieckey\Lesson7>javac MutiThread.java

E:\zieckey\Lesson7>java MutiThread
main:main
main:main
main:main
main:main
main:main
main:main
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
main:main
main:main
main:main
main:main

ʵ��Runnable�ӿ��������̵߳��ŵ㣺
��1������ͬʱ�������һ����̳���
��2�����Ժܷ����ʵ���ڴ�Ĺ������磺
//MutiThread.java
class MutiThread
{
	public static void main( String[]args )
	{
		MyThread mt=new MyThread();//����һ���߳�
		new Thread(mt).start();
		new Thread(mt).start();
		new Thread(mt).start();
		new Thread(mt).start();
		new Thread(mt).start();
		new Thread(mt).start();
		new Thread(mt).start();
		new Thread(mt).start();
		int i=0;
		while ( true )
		{
			if ( i++ == 5000 )
				break;
			System.out.println( "main:"+Thread.currentThread().getName() );
		}
	}
}

class MyThread implements Runnable//extends Thread//����һ���߳�
{
	int index=0;
	public void run()
	{
		while ( true )
		{
			System.out.println( Thread.currentThread().getName() + ":" + index++ );
		}
	}
}
E:\zieckey\Lesson7>javac MutiThread.java

E:\zieckey\Lesson7>java MutiThread
main:main
main:main
main:main
Thread-0:0
Thread-1:1
Thread-2:2
Thread-3:3
Thread-4:4
Thread-5:5
Thread-6:6
Thread-7:7
Thread-0:8
Thread-1:9
Thread-2:10
Thread-3:11
Thread-4:12
Thread-5:13
Thread-6:14
Thread-7:15
Thread-0:16
Thread-1:17
Thread-2:18
Thread-3:19
Thread-4:20
Thread-5:21
Thread-6:22
Thread-7:23
Thread-0:24
Thread-1:25
Thread-2:26
Thread-3:27
Thread-4:28
Thread-5:29
Thread-6:30
Thread-7:31
Thread-0:32
Thread-1:33
Thread-2:34
Thread-3:35
Thread-4:36
Thread-5:37
Thread-6:38
Thread-7:39
Thread-0:40
Thread-1:41
Thread-2:42
Thread-3:43
Thread-4:44
Thread-5:45
Thread-6:46
Thread-7:47
main:main
Thread-0:48
Thread-1:49
Thread-2:50
Thread-3:51
Thread-4:52
Thread-5:53
Thread-6:54
main:main
Thread-0:55
Thread-1:56
Thread-2:57

����˵�������ŵ㶼����ͨ���ڲ���ʵ�֣�
//MutiThread.java
class MutiThread
{
	public static void main( String[]args )
	{
		MyThread mt=new MyThread();//����һ���߳�
		mt.getThread().start();
		mt.getThread().start();
		mt.getThread().start();
		mt.getThread().start();
		mt.getThread().start();
		int i=0;
		while ( true )
		{
			if ( i++ == 5000 )
				break;
			System.out.println( "main:"+Thread.currentThread().getName() );
		}
	}
}

class MyThread //implements Runnable//extends Thread//����һ���߳�
{
	int index=0;
	private class InnerThread extends Thread//�������Ϊprivate��Ϊ������ʵ��ϸ��
	{
		public void run()
		{
			while ( true )
			{
				System.out.println( Thread.currentThread().getName() + ":" + index++ );
			}
		}
	}
	Thread getThread()
	{
		return new InnerThread();
	}


}
E:\zieckey\Lesson7>javac MutiThread.java

E:\zieckey\Lesson7>java MutiThread
main:main
main:main
main:main
main:main
Thread-0:0
Thread-1:1
Thread-2:2
Thread-3:3
Thread-4:4
Thread-0:5
Thread-1:6
Thread-2:7
Thread-3:8
Thread-4:9
Thread-0:10
Thread-1:11
Thread-2:12
Thread-3:13
Thread-4:14
Thread-0:15
Thread-1:16
Thread-2:17
Thread-3:18
Thread-4:19
Thread-0:20
Thread-1:21
Thread-2:22
Thread-3:23
Thread-4:24
Thread-0:25
Thread-1:26
Thread-2:27
Thread-3:28
Thread-4:29
main:main
Thread-0:30
Thread-1:31
Thread-2:32
Thread-3:33
main:main
Thread-0:34
Thread-1:35
Thread-2:36
Thread-3:37
main:main
Thread-0:38
Thread-1:39
Thread-2:40
Thread-3:41
main:main
Thread-0:42
Thread-1:43
Thread-2:44
Thread-3:45
main:main
Thread-0:46
Thread-1:47
Thread-2:48
Thread-3:49
main:main
Thread-0:50
Thread-1:51
Thread-2:52
Thread-3:53
main:main
Thread-4:54
Thread-0:55
Thread-1:56
Thread-2:57
main:main
Thread-4:58


���濴��һ��ģ�����Ʊϵͳ
//TicketsSystem.java
class TicketsSystem
{
	public static void main(String[] args)
	{
		SellThread st=new SellThread();
		new Thread(st).start();
		new Thread(st).start();
		new Thread(st).start();
		new Thread(st).start();
	}
}
class SellThread implements Runnable
{
	int tickets=100;
	public void run()
	{
		while ( true )
		{
			if ( tickets > 0 )
			{
				System.out.println( Thread.currentThread().getName() +
								"Sell tickets : " + tickets );
				tickets --;
			}
		}
	}

}
E:\zieckey\Lesson7>javac TicketsSystem.java
E:\zieckey\Lesson7>java TicketsSystem
Thread-0Sell tickets : 100
Thread-0Sell tickets : 99
Thread-0Sell tickets : 98
Thread-0Sell tickets : 97
Thread-0Sell tickets : 96
Thread-0Sell tickets : 95
Thread-0Sell tickets : 94
Thread-1Sell tickets : 94
Thread-2Sell tickets : 94
Thread-3Sell tickets : 94
Thread-1Sell tickets : 93
Thread-2Sell tickets : 92
Thread-3Sell tickets : 91
Thread-1Sell tickets : 90
Thread-2Sell tickets : 89
Thread-3Sell tickets : 88
Thread-1Sell tickets : 87
Thread-2Sell tickets : 86
Thread-3Sell tickets : 85

������������е����⣬���ǿ����۳�0��-1��������Ʊ�����ǿ�����
//TicketsSystem.java
class TicketsSystem
{
	public static void main(String[] args)
	{
		SellThread st=new SellThread();
		new Thread(st).start();
		new Thread(st).start();
		new Thread(st).start();
		new Thread(st).start();
	}
}
class SellThread implements Runnable
{
	int tickets=100;
	public void run()
	{
		while ( true )
		{
			if ( tickets > 0 )
			{
				try
				{
					Thread.sleep( 10 );
				}
				catch( Exception e )
				{
					e.printStackTrace();
				}

				System.out.println( Thread.currentThread().getName() +
								"Sell tickets : " + tickets );
				tickets --;
			}
		}
	}

}
E:\zieckey\Lesson7>javac TicketsSystem.java

E:\zieckey\Lesson7>java TicketsSystem
Thread-0Sell tickets : 100
Thread-1Sell tickets : 99
Thread-2Sell tickets : 98
Thread-3Sell tickets : 97
Thread-0Sell tickets : 96
Thread-1Sell tickets : 95
Thread-2Sell tickets : 94
Thread-3Sell tickets : 93
Thread-0Sell tickets : 92
Thread-1Sell tickets : 91
Thread-2Sell tickets : 90
Thread-3Sell tickets : 89
Thread-0Sell tickets : 88
Thread-1Sell tickets : 87
Thread-2Sell tickets : 86
Thread-3Sell tickets : 85
Thread-0Sell tickets : 84
Thread-1Sell tickets : 83
Thread-2Sell tickets : 82
Thread-3Sell tickets : 81
Thread-0Sell tickets : 80
Thread-1Sell tickets : 79
Thread-2Sell tickets : 78
Thread-3Sell tickets : 77
Thread-0Sell tickets : 76
Thread-1Sell tickets : 75
Thread-2Sell tickets : 74
Thread-3Sell tickets : 73
Thread-0Sell tickets : 72
Thread-1Sell tickets : 71
Thread-2Sell tickets : 70
Thread-3Sell tickets : 69
Thread-0Sell tickets : 68
Thread-1Sell tickets : 67
Thread-2Sell tickets : 66
Thread-3Sell tickets : 65
Thread-0Sell tickets : 64
Thread-1Sell tickets : 63
Thread-2Sell tickets : 62
Thread-3Sell tickets : 61
Thread-0Sell tickets : 60
Thread-1Sell tickets : 59
Thread-2Sell tickets : 59
Thread-3Sell tickets : 59
Thread-0Sell tickets : 59
Thread-0Sell tickets : 55
Thread-3Sell tickets : 54
Thread-2Sell tickets : 53
Thread-1Sell tickets : 52
Thread-0Sell tickets : 51
Thread-3Sell tickets : 50
Thread-2Sell tickets : 49
Thread-1Sell tickets : 48
Thread-0Sell tickets : 47
Thread-3Sell tickets : 46
Thread-2Sell tickets : 45
Thread-1Sell tickets : 44
Thread-0Sell tickets : 43
Thread-3Sell tickets : 42
Thread-2Sell tickets : 41
Thread-1Sell tickets : 40
Thread-0Sell tickets : 39
Thread-3Sell tickets : 38
Thread-2Sell tickets : 37
Thread-1Sell tickets : 36
Thread-0Sell tickets : 35
Thread-3Sell tickets : 34
Thread-2Sell tickets : 34
Thread-1Sell tickets : 34
Thread-0Sell tickets : 31
Thread-2Sell tickets : 30
Thread-3Sell tickets : 29
Thread-1Sell tickets : 28
Thread-0Sell tickets : 27
Thread-2Sell tickets : 26
Thread-3Sell tickets : 25
Thread-1Sell tickets : 24
Thread-0Sell tickets : 23
Thread-2Sell tickets : 22
Thread-3Sell tickets : 21
Thread-1Sell tickets : 20
Thread-0Sell tickets : 19
Thread-2Sell tickets : 18
Thread-3Sell tickets : 17
Thread-1Sell tickets : 16
Thread-0Sell tickets : 15
Thread-2Sell tickets : 14
Thread-3Sell tickets : 13
Thread-1Sell tickets : 12
Thread-0Sell tickets : 11
Thread-2Sell tickets : 10
Thread-3Sell tickets : 10
Thread-1Sell tickets : 10
Thread-0Sell tickets : 7
Thread-1Sell tickets : 6
Thread-3Sell tickets : 5
Thread-2Sell tickets : 4
Thread-0Sell tickets : 3
Thread-1Sell tickets : 2
Thread-3Sell tickets : 1
Thread-1Sell tickets : 0
Thread-2Sell tickets : -1
Thread-0Sell tickets : -2
��������Ȼ�ǲ��Եģ���ô����ν���أ�
���Ҫ�õ��̵߳�ͬ�����ơ�

�̵߳�ͬ��
The code segments within a program that access the same object from separate, concurrent threads are called ��critical sections����
ͬ�������ַ�ʽ��ͬ�����ͬ������
ÿһ��������һ�������������߽�������
ͬ���������õ���this������Ķ��������
ÿ��classҲ��һ�����������class����Ӧ��Class���������


ͬ����ķ�����
//TicketsSystem.java
class TicketsSystem
{
	public static void main(String[] args)
	{
		SellThread st=new SellThread();
		new Thread(st).start();
		new Thread(st).start();
		new Thread(st).start();
		new Thread(st).start();
	}
}
class SellThread implements Runnable
{
	int tickets=100;
	//Object obj = new Object();
	int criticalSections = 0;
	public void run()
	{
		while ( true )
		{
			//synchronized( obj )//�������ͬ����
			synchronized( criticalSections )//�������ͬ����
			{
				if ( tickets > 0 )
				{
					try
					{
						Thread.sleep( 10 );
					}
					catch( Exception e )
					{
						e.printStackTrace();
					}

					System.out.println( Thread.currentThread().getName() +
									"Sell tickets : " + tickets );
					tickets --;
				}
			}
		}
	}

}
E:\zieckey\Lesson7>javac TicketsSystem.java

E:\zieckey\Lesson7>java TicketsSystem
Thread-0Sell tickets : 100
Thread-1Sell tickets : 99
Thread-2Sell tickets : 98
Thread-3Sell tickets : 97
Thread-0Sell tickets : 96
Thread-1Sell tickets : 95
Thread-2Sell tickets : 94
Thread-3Sell tickets : 93
Thread-0Sell tickets : 92
Thread-1Sell tickets : 91
Thread-2Sell tickets : 90
Thread-3Sell tickets : 89
Thread-0Sell tickets : 88
Thread-1Sell tickets : 87
Thread-2Sell tickets : 86
Thread-3Sell tickets : 85
Thread-0Sell tickets : 84
Thread-1Sell tickets : 83
Thread-2Sell tickets : 82
Thread-3Sell tickets : 81
Thread-0Sell tickets : 80
Thread-1Sell tickets : 79
Thread-2Sell tickets : 78
Thread-3Sell tickets : 77
Thread-0Sell tickets : 76
Thread-1Sell tickets : 75
Thread-2Sell tickets : 74
Thread-3Sell tickets : 73
Thread-0Sell tickets : 72
Thread-1Sell tickets : 71
Thread-2Sell tickets : 70
Thread-3Sell tickets : 69
Thread-0Sell tickets : 68
Thread-1Sell tickets : 67
Thread-2Sell tickets : 66
Thread-3Sell tickets : 65
Thread-0Sell tickets : 64
Thread-1Sell tickets : 63
Thread-2Sell tickets : 62
Thread-3Sell tickets : 61
Thread-0Sell tickets : 60
Thread-1Sell tickets : 59
Thread-2Sell tickets : 58
Thread-3Sell tickets : 57
Thread-0Sell tickets : 56
Thread-1Sell tickets : 55
Thread-2Sell tickets : 54
Thread-3Sell tickets : 53
Thread-0Sell tickets : 52
Thread-1Sell tickets : 51
Thread-2Sell tickets : 50
Thread-3Sell tickets : 49
Thread-0Sell tickets : 48
Thread-1Sell tickets : 47
Thread-2Sell tickets : 46
Thread-3Sell tickets : 45
Thread-0Sell tickets : 44
Thread-1Sell tickets : 43
Thread-2Sell tickets : 42
Thread-3Sell tickets : 41
Thread-0Sell tickets : 40
Thread-1Sell tickets : 39
Thread-2Sell tickets : 38
Thread-3Sell tickets : 37
Thread-0Sell tickets : 36
Thread-1Sell tickets : 35
Thread-2Sell tickets : 34
Thread-3Sell tickets : 33
Thread-0Sell tickets : 32
Thread-1Sell tickets : 31
Thread-2Sell tickets : 30
Thread-3Sell tickets : 29
Thread-0Sell tickets : 28
Thread-1Sell tickets : 27
Thread-2Sell tickets : 26
Thread-3Sell tickets : 25
Thread-0Sell tickets : 24
Thread-1Sell tickets : 23
Thread-2Sell tickets : 22
Thread-3Sell tickets : 21
Thread-0Sell tickets : 20
Thread-1Sell tickets : 19
Thread-2Sell tickets : 18
Thread-3Sell tickets : 17
Thread-0Sell tickets : 16
Thread-1Sell tickets : 15
Thread-2Sell tickets : 14
Thread-3Sell tickets : 13
Thread-0Sell tickets : 12
Thread-1Sell tickets : 11
Thread-2Sell tickets : 10
Thread-3Sell tickets : 9
Thread-0Sell tickets : 8
Thread-1Sell tickets : 7
Thread-2Sell tickets : 6
Thread-3Sell tickets : 5
Thread-0Sell tickets : 4
Thread-1Sell tickets : 3
Thread-2Sell tickets : 2
Thread-3Sell tickets : 1
��Ͳ����ܳ�������Ĵ�����Ʊ�ˡ�
	synchronized( obj )//�������ͬ����
��仰�Ƕ�obj�����������ʵ��ͬ����

ͬ��������ʵ�֣�
//TicketsSystem.java
class TicketsSystem
{
	public static void main(String[] args)
	{
		SellThread st=new SellThread();
		new Thread(st).start();
		new Thread(st).start();
		new Thread(st).start();
		new Thread(st).start();
	}
}
class SellThread implements Runnable
{
	int tickets=100;
	Object obj = new Object();
	public void run()
	{
		while ( true )
		{
			/*synchronized( obj )//�������ͬ����
			{
				if ( tickets > 0 )
				{
					try
					{
						Thread.sleep( 10 );
					}
					catch( Exception e )
					{
						e.printStackTrace();
					}

					System.out.println( Thread.currentThread().getName() +
									"Sell tickets : " + tickets );
					tickets --;
				}
			}*/
			sell();
		}
	}
	public synchronized void sell() //ͬ���ķ��������ڷ���ǰ��������η�synchronized
	{
		synchronized(obj)
		{
			if(tickets>0)
			{
				try
				{
					Thread.sleep(10);
				}
				catch(Exception e)
				{
					e.printStackTrace();
				}
				System.out.println("sell():"+Thread.currentThread().getName()+
						" sell tickets:"+tickets);
				tickets--;
			}
		}
	}
}
E:\zieckey\Lesson7>javac TicketsSystem.java

E:\zieckey\Lesson7>java TicketsSystem
sell():Thread-0 sell tickets:100
sell():Thread-1 sell tickets:99
sell():Thread-2 sell tickets:98
sell():Thread-3 sell tickets:97
sell():Thread-0 sell tickets:96
sell():Thread-1 sell tickets:95
sell():Thread-2 sell tickets:94
sell():Thread-3 sell tickets:93
sell():Thread-0 sell tickets:92
sell():Thread-1 sell tickets:91
sell():Thread-2 sell tickets:90
sell():Thread-3 sell tickets:89
sell():Thread-0 sell tickets:88
sell():Thread-1 sell tickets:87
sell():Thread-2 sell tickets:86
sell():Thread-3 sell tickets:85
sell():Thread-0 sell tickets:84
sell():Thread-1 sell tickets:83
sell():Thread-2 sell tickets:82
sell():Thread-3 sell tickets:81
sell():Thread-0 sell tickets:80
sell():Thread-1 sell tickets:79
sell():Thread-2 sell tickets:78
sell():Thread-3 sell tickets:77
sell():Thread-0 sell tickets:76
sell():Thread-1 sell tickets:75
sell():Thread-2 sell tickets:74
sell():Thread-3 sell tickets:73
sell():Thread-0 sell tickets:72
sell():Thread-1 sell tickets:71
sell():Thread-2 sell tickets:70
sell():Thread-3 sell tickets:69
sell():Thread-0 sell tickets:68
sell():Thread-1 sell tickets:67
sell():Thread-2 sell tickets:66
sell():Thread-3 sell tickets:65
sell():Thread-0 sell tickets:64
sell():Thread-1 sell tickets:63
sell():Thread-2 sell tickets:62
sell():Thread-3 sell tickets:61
sell():Thread-0 sell tickets:60
sell():Thread-1 sell tickets:59
sell():Thread-2 sell tickets:58
sell():Thread-3 sell tickets:57
sell():Thread-0 sell tickets:56
sell():Thread-1 sell tickets:55
sell():Thread-2 sell tickets:54
sell():Thread-3 sell tickets:53
sell():Thread-0 sell tickets:52
sell():Thread-1 sell tickets:51
sell():Thread-2 sell tickets:50
sell():Thread-3 sell tickets:49
sell():Thread-0 sell tickets:48
sell():Thread-1 sell tickets:47
sell():Thread-2 sell tickets:46
sell():Thread-3 sell tickets:45
sell():Thread-0 sell tickets:44
sell():Thread-1 sell tickets:43
sell():Thread-2 sell tickets:42
sell():Thread-3 sell tickets:41
sell():Thread-0 sell tickets:40
sell():Thread-1 sell tickets:39
sell():Thread-2 sell tickets:38
sell():Thread-3 sell tickets:37
sell():Thread-0 sell tickets:36
sell():Thread-1 sell tickets:35
sell():Thread-2 sell tickets:34
sell():Thread-3 sell tickets:33
sell():Thread-0 sell tickets:32
sell():Thread-1 sell tickets:31
sell():Thread-2 sell tickets:30
sell():Thread-3 sell tickets:29
sell():Thread-0 sell tickets:28
sell():Thread-1 sell tickets:27
sell():Thread-2 sell tickets:26
sell():Thread-3 sell tickets:25
sell():Thread-0 sell tickets:24
sell():Thread-1 sell tickets:23
sell():Thread-2 sell tickets:22
sell():Thread-3 sell tickets:21
sell():Thread-0 sell tickets:20
sell():Thread-1 sell tickets:19
sell():Thread-2 sell tickets:18
sell():Thread-3 sell tickets:17
sell():Thread-0 sell tickets:16
sell():Thread-1 sell tickets:15
sell():Thread-2 sell tickets:14
sell():Thread-3 sell tickets:13
sell():Thread-0 sell tickets:12
sell():Thread-1 sell tickets:11
sell():Thread-2 sell tickets:10
sell():Thread-3 sell tickets:9
sell():Thread-0 sell tickets:8
sell():Thread-1 sell tickets:7
sell():Thread-2 sell tickets:6
sell():Thread-3 sell tickets:5
sell():Thread-0 sell tickets:4
sell():Thread-1 sell tickets:3
sell():Thread-2 sell tickets:2
sell():Thread-3 sell tickets:1
�����ʵ�� this �������������������һ�����ԣ��������ͬ����Ҳ�� this ������
��ôͬ�����ͬ�������Ƿ�ͬ����

//TicketsSystem.java
class TicketsSystem
{
	public static void main(String[] args)
	{
		SellThread st=new SellThread();
		new Thread(st).start();
		try
		{
			Thread.sleep(1);//����ȴ�1ms��Ϊ���õ�һ���߳�����������
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		st.b = true ;//��һ���߳��Ѿ�����֮�������st.b = true
		new Thread(st).start();

	}
}
class SellThread implements Runnable
{
	int tickets=100;
	Object obj = new Object();
	boolean b = false ;
	public void run()
	{
		if ( b == false )
		{
			while ( true )
			{
				sell();
			}

		}
		else
		{
			while ( true )
			{
				synchronized( obj )//�������ͬ����
				{
					if ( tickets > 0 )
					{
						try
						{
							Thread.sleep( 10 );
						}
						catch( Exception e )
						{
							e.printStackTrace();
						}

						System.out.println( Thread.currentThread().getName() +
										"Sell tickets : " + tickets );
						tickets --;
					}
				}
			}
		}

	}
	public synchronized void sell()
	{

		if(tickets>0)
		{
			try
			{
				Thread.sleep(10);
			}
			catch(Exception e)
			{
				e.printStackTrace();
			}
			System.out.println("sell():"+Thread.currentThread().getName()+
					" sell tickets:"+tickets);
			tickets--;
		}
	}
}
E:\zieckey\Lesson7>javac TicketsSystem.java

E:\zieckey\Lesson7>java TicketsSystem
sell():Thread-0 sell tickets:100
Thread-1Sell tickets : 99
sell():Thread-0 sell tickets:98
Thread-1Sell tickets : 97
sell():Thread-0 sell tickets:96
Thread-1Sell tickets : 95
sell():Thread-0 sell tickets:94
Thread-1Sell tickets : 93
sell():Thread-0 sell tickets:92
Thread-1Sell tickets : 91
sell():Thread-0 sell tickets:90
Thread-1Sell tickets : 89
sell():Thread-0 sell tickets:88
Thread-1Sell tickets : 87
sell():Thread-0 sell tickets:86
Thread-1Sell tickets : 85
sell():Thread-0 sell tickets:84
Thread-1Sell tickets : 83
sell():Thread-0 sell tickets:82
Thread-1Sell tickets : 81
sell():Thread-0 sell tickets:80
Thread-1Sell tickets : 79
sell():Thread-0 sell tickets:78
Thread-1Sell tickets : 77
sell():Thread-0 sell tickets:76
Thread-1Sell tickets : 75
sell():Thread-0 sell tickets:74
Thread-1Sell tickets : 73
sell():Thread-0 sell tickets:72
Thread-1Sell tickets : 71
sell():Thread-0 sell tickets:70
Thread-1Sell tickets : 69
sell():Thread-0 sell tickets:68
Thread-1Sell tickets : 67
sell():Thread-0 sell tickets:66
Thread-1Sell tickets : 65
sell():Thread-0 sell tickets:64
Thread-1Sell tickets : 63
sell():Thread-0 sell tickets:62
Thread-1Sell tickets : 61
sell():Thread-0 sell tickets:60
Thread-1Sell tickets : 59
sell():Thread-0 sell tickets:58
Thread-1Sell tickets : 57
sell():Thread-0 sell tickets:56
Thread-1Sell tickets : 55
sell():Thread-0 sell tickets:54
sell():Thread-0 sell tickets:53
Thread-1Sell tickets : 52
sell():Thread-0 sell tickets:51
Thread-1Sell tickets : 50
sell():Thread-0 sell tickets:49
Thread-1Sell tickets : 48
sell():Thread-0 sell tickets:47
Thread-1Sell tickets : 46
sell():Thread-0 sell tickets:45
Thread-1Sell tickets : 44
Thread-1Sell tickets : 43
sell():Thread-0 sell tickets:42
sell():Thread-0 sell tickets:41
Thread-1Sell tickets : 40
sell():Thread-0 sell tickets:39
Thread-1Sell tickets : 38
sell():Thread-0 sell tickets:37
Thread-1Sell tickets : 36
sell():Thread-0 sell tickets:35
Thread-1Sell tickets : 34
sell():Thread-0 sell tickets:33
Thread-1Sell tickets : 32
Thread-1Sell tickets : 31
sell():Thread-0 sell tickets:30
sell():Thread-0 sell tickets:29
Thread-1Sell tickets : 28
sell():Thread-0 sell tickets:27
Thread-1Sell tickets : 26
sell():Thread-0 sell tickets:25
Thread-1Sell tickets : 24
sell():Thread-0 sell tickets:23
Thread-1Sell tickets : 22
sell():Thread-0 sell tickets:21
Thread-1Sell tickets : 20
Thread-1Sell tickets : 19
sell():Thread-0 sell tickets:18
sell():Thread-0 sell tickets:17
Thread-1Sell tickets : 16
sell():Thread-0 sell tickets:15
Thread-1Sell tickets : 14
sell():Thread-0 sell tickets:13
Thread-1Sell tickets : 12
sell():Thread-0 sell tickets:11
Thread-1Sell tickets : 10
sell():Thread-0 sell tickets:9
Thread-1Sell tickets : 8
Thread-1Sell tickets : 7
sell():Thread-0 sell tickets:6
sell():Thread-0 sell tickets:5
Thread-1Sell tickets : 4
sell():Thread-0 sell tickets:3
Thread-1Sell tickets : 2
sell():Thread-0 sell tickets:1
Thread-1Sell tickets : 0

���������̼߳��ӵĶ���һ�����������۳� 0 ��Ʊ�Ĵ���
��ô���ǿ�������ͬһ�����Ч����

//TicketsSystem.java
class TicketsSystem
{
	public static void main(String[] args)
	{
		SellThread st=new SellThread();
		new Thread(st).start();
		try
		{
			Thread.sleep(1);//����ȴ�1ms��Ϊ���õ�һ���߳�����������
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		st.b = true ;//��һ���߳��Ѿ�����֮�������st.b = true
		new Thread(st).start();

	}
}
class SellThread implements Runnable
{
	int tickets=100;
	Object obj = new Object();
	boolean b = false ;
	public void run()
	{
		if ( b == false )
		{
			while ( true )
			{
				sell();
			}

		}
		else
		{
			while ( true )
			{
				synchronized( this )//�������ͬ����
				{
					if ( tickets > 0 )
					{
						try
						{
							Thread.sleep( 10 );
						}
						catch( Exception e )
						{
							e.printStackTrace();
						}

						System.out.println( Thread.currentThread().getName() +
										"Sell tickets : " + tickets );
						tickets --;
					}
				}
			}
		}

	}
	public synchronized void sell()
	{

		if(tickets>0)
		{
			try
			{
				Thread.sleep(10);
			}
			catch(Exception e)
			{
				e.printStackTrace();
			}
			System.out.println("sell():"+Thread.currentThread().getName()+
					" sell tickets:"+tickets);
			tickets--;
		}
	}
}
E:\zieckey\Lesson7>javac TicketsSystem.java

E:\zieckey\Lesson7>java TicketsSystem
sell():Thread-0 sell tickets:100
Thread-1Sell tickets : 99
sell():Thread-0 sell tickets:98
Thread-1Sell tickets : 97
sell():Thread-0 sell tickets:96
Thread-1Sell tickets : 95
sell():Thread-0 sell tickets:94
Thread-1Sell tickets : 93
sell():Thread-0 sell tickets:92
Thread-1Sell tickets : 91
sell():Thread-0 sell tickets:90
Thread-1Sell tickets : 89
sell():Thread-0 sell tickets:88
Thread-1Sell tickets : 87
sell():Thread-0 sell tickets:86
Thread-1Sell tickets : 85
sell():Thread-0 sell tickets:84
Thread-1Sell tickets : 83
sell():Thread-0 sell tickets:82
Thread-1Sell tickets : 81
sell():Thread-0 sell tickets:80
Thread-1Sell tickets : 79
sell():Thread-0 sell tickets:78
Thread-1Sell tickets : 77
sell():Thread-0 sell tickets:76
Thread-1Sell tickets : 75
sell():Thread-0 sell tickets:74
Thread-1Sell tickets : 73
sell():Thread-0 sell tickets:72
Thread-1Sell tickets : 71
sell():Thread-0 sell tickets:70
Thread-1Sell tickets : 69
sell():Thread-0 sell tickets:68
Thread-1Sell tickets : 67
sell():Thread-0 sell tickets:66
Thread-1Sell tickets : 65
sell():Thread-0 sell tickets:64
Thread-1Sell tickets : 63
sell():Thread-0 sell tickets:62
Thread-1Sell tickets : 61
sell():Thread-0 sell tickets:60
Thread-1Sell tickets : 59
sell():Thread-0 sell tickets:58
Thread-1Sell tickets : 57
sell():Thread-0 sell tickets:56
Thread-1Sell tickets : 55
sell():Thread-0 sell tickets:54
sell():Thread-0 sell tickets:53
Thread-1Sell tickets : 52
sell():Thread-0 sell tickets:51
Thread-1Sell tickets : 50
sell():Thread-0 sell tickets:49
Thread-1Sell tickets : 48
sell():Thread-0 sell tickets:47
Thread-1Sell tickets : 46
sell():Thread-0 sell tickets:45
Thread-1Sell tickets : 44
Thread-1Sell tickets : 43
sell():Thread-0 sell tickets:42
sell():Thread-0 sell tickets:41
Thread-1Sell tickets : 40
sell():Thread-0 sell tickets:39
Thread-1Sell tickets : 38
sell():Thread-0 sell tickets:37
Thread-1Sell tickets : 36
sell():Thread-0 sell tickets:35
Thread-1Sell tickets : 34
sell():Thread-0 sell tickets:33
Thread-1Sell tickets : 32
Thread-1Sell tickets : 31
sell():Thread-0 sell tickets:30
sell():Thread-0 sell tickets:29
Thread-1Sell tickets : 28
sell():Thread-0 sell tickets:27
Thread-1Sell tickets : 26
sell():Thread-0 sell tickets:25
Thread-1Sell tickets : 24
sell():Thread-0 sell tickets:23
Thread-1Sell tickets : 22
sell():Thread-0 sell tickets:21
Thread-1Sell tickets : 20
Thread-1Sell tickets : 19
sell():Thread-0 sell tickets:18
sell():Thread-0 sell tickets:17
Thread-1Sell tickets : 16
sell():Thread-0 sell tickets:15
Thread-1Sell tickets : 14
sell():Thread-0 sell tickets:13
Thread-1Sell tickets : 12
sell():Thread-0 sell tickets:11
Thread-1Sell tickets : 10
sell():Thread-0 sell tickets:9
Thread-1Sell tickets : 8
Thread-1Sell tickets : 7
sell():Thread-0 sell tickets:6
sell():Thread-0 sell tickets:5
Thread-1Sell tickets : 4
sell():Thread-0 sell tickets:3
Thread-1Sell tickets : 2
sell():Thread-0 sell tickets:1
�����ͺ��ˡ�

������˵��ͨ��ͬ������ʵ�ֵ�ͬ���������ӵ���this����
ÿһ��������һ�������������߽�������
ͬ���������õ���this������Ķ��������
ÿ��classҲ��һ�����������class����Ӧ��Class���������
��ô�Ϳ����������Class������ͬ����̬����.

����:
�߳�1��ס�˶���A�ļ��������ȴ�����B�ļ��������߳�2��ס�˶���B�ļ��������ȴ�����A�ļ��������������������
���ǿ������������:

//TicketsSystem.java
class TicketsSystem
{
	public static void main(String[] args)
	{
		SellThread st=new SellThread();
		new Thread(st).start();
		try
		{
			Thread.sleep(1);//����ȴ�1ms��Ϊ���õ�һ���߳�����������
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		st.b = true ;//��һ���߳��Ѿ�����֮�������st.b = true
		new Thread(st).start();

	}
}
class SellThread implements Runnable
{
	int tickets=100;
	Object obj = new Object();
	boolean b = false ;
	public void run()
	{
		if ( b == false )
		{
			while ( true )
			{
				sell();
			}

		}
		else
		{
			while ( true )
			{
				synchronized(obj)
				{
					try
					{
						Thread.sleep(10);
					}
					catch(Exception e)
					{
						e.printStackTrace();
					}
					synchronized(this)
					{
						if(tickets>0)
						{

							System.out.println("obj:"+Thread.currentThread().getName()+
									" sell tickets:"+tickets);
							tickets--;
						}
					}
				}
			}
		}

	}
	public synchronized void sell()
	{

		synchronized(obj)
		{
			if(tickets>0)
			{
				try
				{
					Thread.sleep(10);
				}
				catch(Exception e)
				{
					e.printStackTrace();
				}
				System.out.println("sell():"+Thread.currentThread().getName()+
						" sell tickets:"+tickets);
				tickets--;
			}
		}
	}
}
E:\zieckey\Lesson7>javac TicketsSystem.java

E:\zieckey\Lesson7>java TicketsSystem
sell():Thread-0 sell tickets:100

E:\zieckey\Lesson7>


wait��notify��notifyAll
ÿһ�����������һ����֮�⣬����һ���ȴ����У�wait set������һ������մ�����ʱ�����ĶԴ������ǿյġ�
����Ӧ���ڵ�ǰ�߳���ס���������ȥ���øö����wait������
�����ö����notify����ʱ�����Ӹö���ĵȴ�������ɾ��һ������ѡ����̣߳�����߳̽��ٴγ�Ϊ�����е��̡߳�
�����ö����notifyAll����ʱ�����Ӹö���ĵȴ�������ɾ�����еȴ����̣߳���Щ�߳̽���Ϊ�����е��̡߳�
wait��notify��Ҫ����producer-consumer���ֹ�ϵ�С�

�������������:

//TestWaitNotify.java
class TestWaitNotify
{
	public static void main(String[] args)
	{
		Queue q=new Queue();
		Producer p=new Producer(q);
		Consumer c=new Consumer(q);
		p.start();
		c.start();
	}
}

class Producer extends Thread
{
	Queue q;
	Producer(Queue q)
	{
		this.q=q;
	}
	public void run()
	{
		for(int i=0;i<10;i++)
		{
			q.put(i);
			System.out.println("Producer put "+i);
		}
	}
}
class Consumer extends Thread
{
	Queue q;
	Consumer(Queue q)
	{
		this.q=q;
	}
	public void run()
	{
		while(true)
		{
			System.out.println("Consumer get "+q.get());
		}
	}
}
class Queue
{
	int value;
	boolean bFull=false;
	public synchronized void put(int i)//��this������м���ͬ��
	{
		if(!bFull)
		{
			value=i;
			bFull=true;
			notify();
		}
		try
		{
			wait();
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}

	}
	public synchronized int get()//��this������м���ͬ��
	{
		if(!bFull)
		{
			try
			{
				wait();
			}
			catch(Exception e)
			{
				e.printStackTrace();
			}
		}
		bFull=false;
		notify();
		return value;
	}
}
E:\zieckey\Lesson7>javac TestWaitNotify.java

E:\zieckey\Lesson7>java TestWaitNotify
Producer put 0
Consumer get 0
Producer put 1
Consumer get 1
Producer put 2
Consumer get 2
Producer put 3
Consumer get 3
Producer put 4
Consumer get 4
Producer put 5
Consumer get 5
Producer put 6
Consumer get 6
Producer put 7
Consumer get 7
Consumer get 8
Producer put 8
Consumer get 9
Producer put 9


�̵߳���ֹ
���Ƽ���stop����ȥ��ֹһ���߳�,��stop�������õ�ʱ��Ὣ���е����⿪,
�����ĳЩ�ٽ���Դ��˵��������,��Ϊ��������ٽ���ԴӦ�ñ���ס,
����һ��stop��ִ��,�ͽ⿪�ˣ������߳̾Ϳ��Է����ˡ�
�̵߳���ֹ�����ֿ��еķ�����
1.����һ��flag������
2.���interrupt()������


1.����һ��flag������
//TestThreadStop.java
class TestThreadStop
{
	public static void main(String[] args)
	{
		Thread1 t1=new Thread1();
		t1.start();
		int index=0;
		while(true)
		{
			if(index++==50)
			{
				t1.stopThread();
				break;
			}
			System.out.println(Thread.currentThread().getName());
		}
		System.out.println("main() exit");
	}
}

class Thread1 extends Thread
{
	private boolean bStop=false;
	public void run()
	{
		while(!bStop)
		{
			System.out.println(getName());
		}
	}
	public void stopThread()
	{
		bStop=true;
	}
}
E:\zieckey\Lesson7>javac TestThreadStop.java

E:\zieckey\Lesson7>java TestThreadStop
main
main
main
main
main
main
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
Thread-0
main
main
main
main
main
main
main
main
main
main
main
main() exit

E:\zieckey\Lesson7>

�������������Щwait�����Ļ�����ô�Ͳ������˳��߳��ˡ�
//TestThreadStop.java
class TestThreadStop
{
	public static void main(String[] args)
	{
		Thread1 t1=new Thread1();
		t1.start();
		int index=0;
		while(true)
		{
			if(index++==50)
			{
				t1.stopThread();
				break;
			}
			System.out.println(Thread.currentThread().getName());
		}
		System.out.println("main() exit");
	}
}

class Thread1 extends Thread
{
	private boolean bStop=false;
	public synchronized void run()
	{
		while(!bStop)
		{
			try
			{
				wait();
			}
			catch(InterruptedException e)
			{
				e.printStackTrace();
			}
			System.out.println(getName());
		}
	}
	public void stopThread()
	{
		bStop=true;
	}
}
E:\zieckey\Lesson7>javac TestThreadStop.java

E:\zieckey\Lesson7>java TestThreadStop
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main
main() exit
����������н���ǿ��������ģ�
������ʵ�������У�����ͣ�������û���˳���
���ʱ�����Ǿ�Ҫ�õ�interrupt()������
class TestThread
{
	public static void main(String[] args)
	{
		Thread1 t1=new Thread1();
		t1.start();
		int index=0;
		while(true)
		{
			if(index++==50)
			{
				t1.stopThread();
				t1.interrupt();
				break;
			}
			System.out.println(Thread.currentThread().getName());
		}
		System.out.println("main() exit");
	}
}

class Thread1 extends Thread
{
	private boolean bStop=false;
	public synchronized void run()
	{
		while(!bStop)
		{
			try
			{
				System.out.println("before Wait");
				wait();
				System.out.println("after Wait");
			}
			catch(InterruptedException e)
			{
				if(bStop)
				{
					System.out.println("before thread return");
					return;
				}

			}
			System.out.println(getName());
		}
	}
	public void stopThread()
	{
		bStop=true;
	}
}
�������û����������ʦ���ε�˵�������˳����ƺ����ԣ�
�������о�����������


Lesson8
Java�еļ�����


���Ͽ���еĽӿ�
Collection�����ϲ���еĸ��ӿڣ�JDKû���ṩ����ӿ�ֱ�ӵ�ʵ���ࡣ
Set�����ܰ����ظ���Ԫ�ء�SortedSet��һ��������������Ԫ�ص�Set��
List����һ������ļ��ϣ����԰����ظ���Ԫ�ء��ṩ�˰��������ʵķ�ʽ��
Map��������key-value�ԡ�Map���ܰ����ظ���key��SortedMap��һ��������������key��Map��



ArrayList
ArrayList�����ǿ��Խ��俴�����ܹ��Զ��������������顣
����ArrayList��toArray()����һ�����顣
Arrays.asList()����һ���б�
������(Iterator) �������ṩ��һ��ͨ�õķ�ʽ�����ʼ����е�Ԫ�ء�


//ArrayListTest.java
import java.util.*;
class ArrayListTest
{
	public static void main(String[] args)
	{
		ArrayList al=new ArrayList();
		al.add("winsun");
		al.add("weixin");
		al.add("mybole");

		for(int i=0;i<al.size();i++)
		{
			System.out.println(al.get(i));
		}

	}
}
���н����
winsun
weixin
mybole



//ArrayListTest.java
import java.util.*;
class ArrayListTest
{

	public static void main(String[] args)
	{
		ArrayList al=new ArrayList();

		al.add( new Point(2,2) );
		al.add( new Point(3,3) );
		al.add( new Point(4,4) );

		System.out.println( al );
		Object[] obj = al.toArray();//�����ArrayListת��Ϊ����
		for ( int i=0; i<obj.length; i++ )
		{
			System.out.println( obj[i] );
		}
	}
}
class Point
{
	int x,y;
	Point(int x,int y)
	{
		this.x=x;
		this.y=y;
	}
	public String toString()
	{
		return "x="+x+" "+"y="+y;
	}
}
���н����
[x=2 y=2, x=3 y=3, x=4 y=4]
x=2 y=2
x=3 y=3
x=4 y=4
���ǳ��־�����Ϣ��
Severity and Description	Path	Resource	Location	Creation Time	Id
Type safety: The method add(Object) belongs to the raw type ArrayList. References to generic type ArrayList<E> should be parameterized	Lesson8	ArrayListTest.java	line 11	1167034673468	236
Type safety: The method add(Object) belongs to the raw type ArrayList. References to generic type ArrayList<E> should be parameterized	Lesson8	ArrayListTest.java	line 12	1167034673468	237
Type safety: The method add(Object) belongs to the raw type ArrayList. References to generic type ArrayList<E> should be parameterized	Lesson8	ArrayListTest.java	line 13	1167034673468	238

Tiger�ķ��͹���ʹ�ñ����������͵İ�ȫ�Խ��м�飬�ر���Java���ϣ�����������ӣ�

public void nonGenericsMethod()
{
	ArrayList al = new ArrayList(); // no typing information on the List
	al.add("zieckey"); // causes error on list addition
}
���������������ľ�����Ϣ��
Type safety: The method add(Object) belongs to the raw type List. References to generic  type List<E> should be parameterized

�������ʹ��@SuppressWarnings����ָֹ�����͵ľ�����Ϣ���磺

@SuppressWarnings(value = { "unchecked" })
public void nonGenericsMethod()
{
	ArrayList al = new ArrayList(); // no typing information on the List
	al.add("zieckey"); // causes error on list addition
}

��ô����Ĵ���Ϳ���ͨ���ⷽ����ֹ��Щ���˵ľ�����Ϣ

//ArrayListTest.java

import java.util.*;
class ArrayListTest
{
	@SuppressWarnings(value = { "unchecked" })  //���� @SuppressWarnings("unchecked")
	public static void main(String[] args)
	{

		ArrayList al = new ArrayList();
		al.add( new Point(2,2) );
		al.add( new Point(3,3) );
		al.add( new Point(4,4) );

		System.out.println( al );
		Object[] obj = al.toArray();//�����ArrayListת��Ϊ����
		for ( int i=0; i<obj.length; i++ )
		{
			System.out.println( obj[i] );
		}
	}
}
class Point
{
	int x,y;
	Point(int x,int y)
	{
		this.x=x;
		this.y=y;
	}
	public String toString()
	{
		return "x="+x+" "+"y="+y;
	}
}
�����Ϳ��Ա��벻���ִ���

������� @SuppressWarnings(value = { "unchecked" })  ���д���Ļ���
���������±������������

E:\JavaLesson\Lesson8>javac ArrayListTest.java
ע�⣺ArrayListTest.java ʹ����δ�����򲻰�ȫ�Ĳ�����
ע�⣺Ҫ�˽���ϸ��Ϣ����ʹ�� -Xlint:unchecked ���±��롣

��ô����ͨ������ -Xlint:unchecked ���±��롣

�����������ǻ���־��棬
E:\JavaLesson\Lesson8>javac ArrayListTest.java -Xlint:unchecked
ArrayListTest.java:11: ���棺[unchecked] ����Ϊ��ͨ���� java.util.ArrayList �ĳ�
Ա�� add(E) �ĵ���δ�����
                al.add( new Point(2,2) );
                      ^
ArrayListTest.java:12: ���棺[unchecked] ����Ϊ��ͨ���� java.util.ArrayList �ĳ�
Ա�� add(E) �ĵ���δ�����
                al.add( new Point(3,3) );
                      ^
ArrayListTest.java:13: ���棺[unchecked] ����Ϊ��ͨ���� java.util.ArrayList �ĳ�
Ա�� add(E) �ĵ���δ�����
                al.add( new Point(4,4) );
                      ^
3 ����

���Ի��Ǽ����Ǿ仰Ϊ�á�


ͨ��Arrays.asList()����һ���б�
//ArrayListTest.java

import java.util.*;
class ArrayListTest
{
	@SuppressWarnings(value = { "unchecked" })  //���� @SuppressWarnings("unchecked")

	public static void main(String[] args)
	{

		ArrayList al = new ArrayList();
		al.add( new Point(2,2) );
		al.add( new Point(3,3) );
		al.add( new Point(4,4) );

		System.out.println( al );
		Object[] obj = al.toArray();//�����ArrayListת��Ϊ����
		for ( int i=0; i<obj.length; i++ )
		{
			System.out.println( obj[i] );
		}

		List l = Arrays.asList( obj ); //��obj����ת��Ϊһ��List����
		System.out.println( l );
	}
}
class Point
{
	int x,y;
	Point(int x,int y)
	{
		this.x=x;
		this.y=y;
	}
	public String toString()
	{
		return "x="+x+" "+"y="+y;
	}
}
���У�
[x=2 y=2, x=3 y=3, x=4 y=4]
x=2 y=2
x=3 y=3
x=4 y=4
[x=2 y=2, x=3 y=3, x=4 y=4]




//ArrayListTest.java

import java.util.*;
class ArrayListTest
{
	@SuppressWarnings(value = { "unchecked" })  //���� @SuppressWarnings("unchecked")

	public static void main(String[] args)
	{

		ArrayList al = new ArrayList();
		al.add( new Point(2,2) );
		al.add( new Point(3,3) );
		al.add( new Point(4,4) );

		System.out.println( al );
		Object[] obj = al.toArray();//�����ArrayListת��Ϊ����
		for ( int i=0; i<obj.length; i++ )
		{
			System.out.println( obj[i] );
		}

		List l = Arrays.asList( obj ); //��obj����ת��Ϊһ��List����

		l.add( new Point(5,5) );//����ͨ��Arrays.asList()�������ص�һ���̶��ߴ��List
								//�����Ӿͻ�����쳣

		System.out.println( l );


	}
}
class Point
{
	int x,y;
	Point(int x,int y)
	{
		this.x=x;
		this.y=y;
	}
	public String toString()
	{
		return "x="+x+" "+"y="+y;
	}
}
���У�
[x=2 y=2, x=3 y=3, x=4 y=4]
x=2 y=2
x=3 y=3
x=4 y=4
Exception in thread "main" java.lang.UnsupportedOperationException
	at java.util.AbstractList.add(Unknown Source)
	at java.util.AbstractList.add(Unknown Source)
	at ArrayListTest.main(ArrayListTest.java:25)
���Բ��ܸ������ӳ�Ա�ˡ�

������(Iterator) �������ṩ��һ��ͨ�õķ�ʽ�����ʼ����е�Ԫ�ء�(List.Iterator())
//ArrayListTest.java

import java.util.*;
class ArrayListTest
{
	@SuppressWarnings(value = { "unchecked" })  //���� @SuppressWarnings("unchecked")

	public static void main(String[] args)
	{

		ArrayList al = new ArrayList();
		al.add( new Point(2,2) );
		al.add( new Point(3,3) );
		al.add( new Point(4,4) );

		System.out.println( al );
		Object[] obj = al.toArray();//�����ArrayListת��Ϊ����
		for ( int i=0; i<obj.length; i++ )
		{
			System.out.println( obj[i] );
		}

		List l = Arrays.asList( obj ); //��obj����ת��Ϊһ��List����
		System.out.println( l );

		System.out.println("Using Iterator...");

		Iterator it=l.iterator(); //����һ��������
		while(it.hasNext())
		{
			System.out.println(it.next());
		}

	}
}
class Point
{
	int x,y;
	Point(int x,int y)
	{
		this.x=x;
		this.y=y;
	}
	public String toString()
	{
		return "x="+x+" "+"y="+y;
	}
}
�������У�
[x=2 y=2, x=3 y=3, x=4 y=4]
x=2 y=2
x=3 y=3
x=4 y=4
[x=2 y=2, x=3 y=3, x=4 y=4]
Using Iterator...
x=2 y=2
x=3 y=3
x=4 y=4

ͨ��������ɾ��һ��Ԫ�أ�
//ArrayListTest.java

import java.util.*;
class ArrayListTest
{
	@SuppressWarnings(value = { "unchecked" })  //���� @SuppressWarnings("unchecked")

	public static void main(String[] args)
	{

		ArrayList al = new ArrayList();
		al.add( new Point(2,2) );
		al.add( new Point(3,3) );
		al.add( new Point(4,4) );

		System.out.println( al );
		Object[] obj = al.toArray();//�����ArrayListת��Ϊ����
		for ( int i=0; i<obj.length; i++ )
		{
			System.out.println( obj[i] );
		}

		List l = Arrays.asList( obj ); //��obj����ת��Ϊһ��List����
		System.out.println( l );

		System.out.println("Using Iterator...");

		Iterator it=l.iterator(); //����һ��������
		it.remove();//ֱ�ӵ���remove()������쳣
		while(it.hasNext())
		{
			System.out.println(it.next());
		}

	}
}
class Point
{
	int x,y;
	Point(int x,int y)
	{
		this.x=x;
		this.y=y;
	}
	public String toString()
	{
		return "x="+x+" "+"y="+y;
	}
}
���У�
[x=2 y=2, x=3 y=3, x=4 y=4]
x=2 y=2
x=3 y=3
x=4 y=4
[x=2 y=2, x=3 y=3, x=4 y=4]
Using Iterator...
Exception in thread "main" java.lang.IllegalStateException
	at java.util.AbstractList$Itr.remove(Unknown Source)
	at ArrayListTest.main(ArrayListTest.java:29)

void remove()Removes from the underlying collection the last element returned by the iterator (optional operation). This method can be called only once per call to next. The behavior of an iterator is unspecified if the underlying collection is modified while the iteration is in progress in any way other than by calling this method.

�������Ǳ�������Iterator�ƶ�����һ��Ԫ�أ�Ȼ��ִ��ɾ��������
������ɾ������Iterator����һ��Ԫ��


//ArrayListTest.java
import java.util.*;
class ArrayListTest
{
	@SuppressWarnings(value = { "unchecked" })  //���� @SuppressWarnings("unchecked")

	public static void main(String[] args)
	{

		ArrayList al = new ArrayList();
		al.add( new Point(2,2) );
		al.add( new Point(3,3) );
		al.add( new Point(4,4) );

		System.out.println( al );
		Object[] obj = al.toArray();//�����ArrayListת��Ϊ����
		for ( int i=0; i<obj.length; i++ )
		{
			System.out.println( obj[i] );
		}

		List l = Arrays.asList( obj ); //��obj����ת��Ϊһ��List����
		System.out.println( l );

		System.out.println("Using Iterator...");

		Iterator it=l.iterator(); //����һ��������
		it.next();
		it.remove();
		while(it.hasNext())
		{
			System.out.println(it.next());
		}

	}
}
class Point
{
	int x,y;
	Point(int x,int y)
	{
		this.x=x;
		this.y=y;
	}
	public String toString()
	{
		return "x="+x+" "+"y="+y;
	}
}

[x=2 y=2, x=3 y=3, x=4 y=4]
x=2 y=2
x=3 y=3
x=4 y=4
[x=2 y=2, x=3 y=3, x=4 y=4]
Using Iterator...
x=3 y=3
x=4 y=4
java.lang.UnsupportedOperationException
	at java.util.AbstractList.remove(Unknown Source)
	at java.util.AbstractList$Itr.remove(Unknown Source)
	at ArrayListTest.main(ArrayListTest.java:32)
Ȼ�����ڻ��ǳ����쳣,why?
�쳣��Ϣ�� UnsupportedOperationException ,
���������ĵ�:
void remove()Removes from the underlying collection the last element returned by the iterator (optional operation). This method can be called only once per call to next. The behavior of an iterator is unspecified if the underlying collection is modified while the iteration is in progress in any way other than by calling this method.
throws:
UnsupportedOperationException - if the remove operation is not supported by this Iterator.
IllegalStateException - if the next method has not yet been called, or the remove method has already been called after the last call to the next method.

�ǿ����������в�׽����쳣�в����أ�
//ArrayListTest.java

import java.util.*;
class ArrayListTest
{
	@SuppressWarnings(value = { "unchecked" })  //���� @SuppressWarnings("unchecked")

	public static void main(String[] args)
	{

		ArrayList al = new ArrayList();
		al.add( new Point(2,2) );
		al.add( new Point(3,3) );
		al.add( new Point(4,4) );

		System.out.println( al );
		Object[] obj = al.toArray();//�����ArrayListת��Ϊ����
		for ( int i=0; i<obj.length; i++ )
		{
			System.out.println( obj[i] );
		}

		List l = Arrays.asList( obj ); //��obj����ת��Ϊһ��List����
		System.out.println( l );

		System.out.println("Using Iterator...");

		Iterator it=l.iterator(); //����һ��������
		it.next();
		try
		{
			it.remove();
		}
		catch ( Exception e )
		{
			e.printStackTrace();
		}
		while(it.hasNext())
		{
			System.out.println(it.next());
		}

	}
}
class Point
{
	int x,y;
	Point(int x,int y)
	{
		this.x=x;
		this.y=y;
	}
	public String toString()
	{
		return "x="+x+" "+"y="+y;
	}
}


[x=2 y=2, x=3 y=3, x=4 y=4]
x=2 y=2
x=3 y=3
x=4 y=4
[x=2 y=2, x=3 y=3, x=4 y=4]
Using Iterator...
x=3 y=3
x=4 y=4
java.lang.UnsupportedOperationException
	at java.util.AbstractList.remove(Unknown Source)
	at java.util.AbstractList$Itr.remove(Unknown Source)
	at ArrayListTest.main(ArrayListTest.java:32)

����һ���Ĵ��󣬿��������������ԭ��

Ŷ,ԭ�����Ƿ������ǵĵ�������ͨ�� Arrays.asList( obj )���ص� List ����,
����List�ǹ̶����ȵģ�����ǰ�治�����Ԫ��һ��������ִ��ɾ������Ҳһ�����С�
��������Ҫ������Щ������ʱ������õ�������Arrays������������£�

//ArrayListTest.java

import java.util.*;
class ArrayListTest
{
	@SuppressWarnings(value = { "unchecked" })  //���� @SuppressWarnings("unchecked")

	public static void main(String[] args)
	{

		ArrayList al = new ArrayList();
		al.add( new Point(2,2) );
		al.add( new Point(3,3) );
		al.add( new Point(4,4) );

		System.out.println( al );
		Object[] obj = al.toArray();//�����ArrayListת��Ϊ����
		for ( int i=0; i<obj.length; i++ )
		{
			System.out.println( obj[i] );
		}

		List l = Arrays.asList( obj ); //��obj����ת��Ϊһ��List����
		System.out.println( l );

		System.out.println("Using Iterator...");

		Iterator it=al.iterator(); //����һ��������
		it.next();
		it.remove();
		while(it.hasNext())
		{
			System.out.println(it.next());
		}

	}
}
class Point
{
	int x,y;
	Point(int x,int y)
	{
		this.x=x;
		this.y=y;
	}
	public String toString()
	{
		return "x="+x+" "+"y="+y;
	}
}

[x=2 y=2, x=3 y=3, x=4 y=4]
x=2 y=2
x=3 y=3
x=4 y=4
[x=2 y=2, x=3 y=3, x=4 y=4]
Using Iterator...
x=3 y=3
x=4 y=4

�����ͺ��ˡ�

������(Iterator) �������ṩ��һ��ͨ�õķ�ʽ�����ʼ����е�Ԫ��,
�������ǿ�������ͨ�÷����ĺô���

//ArrayListTest.java

import java.util.*;
class ArrayListTest
{
	/**
	 * �����ṩ��һ���Լ�����ͨ�õķ��ʷ���������ڳ�������Ǻܷ����
	 */
	public static void printElement( Collection c )
	{
		Iterator it = c.iterator();
		while ( it.hasNext() )
		{
			System.out.println( it.next() );
		}
	}
	@SuppressWarnings(value = { "unchecked" })  //���� @SuppressWarnings("unchecked")
	public static void main(String[] args)
	{

		ArrayList al = new ArrayList();
		al.add( new Point(2,2) );
		al.add( new Point(3,3) );
		al.add( new Point(4,4) );

		System.out.println( al );
		Object[] obj = al.toArray();//�����ArrayListת��Ϊ����
		for ( int i=0; i<obj.length; i++ )
		{
			System.out.println( obj[i] );
		}
		List l = Arrays.asList( obj ); //��obj����ת��Ϊһ��List����
		System.out.println( l );
		System.out.println("A Function using iterator...");
		printElement( al );

	}
}
class Point
{
	int x,y;
	Point(int x,int y)
	{
		this.x=x;
		this.y=y;
	}
	public String toString()
	{
		return "x="+x+" "+"y="+y;
	}
}

[x=2 y=2, x=3 y=3, x=4 y=4]
x=2 y=2
x=3 y=3
x=4 y=4
[x=2 y=2, x=3 y=3, x=4 y=4]
A Function using iterator...
x=2 y=2
x=3 y=3
x=4 y=4


Collections��
����Collections.sort()
��1����Ȼ��Ѱ(natural ordering )��
��2��ʵ�ֱȽ���(Comparator)�ӿڡ�
ȡ������С��Ԫ�أ�Collections.max()��Collections.min()��
���������List������ָ����Ԫ�أ�Collectons.binarySearch()��


sort
public static <T extends Comparable<? super T>> void sort(List<T> list)����Ԫ�ص���Ȼ˳�� ��ָ���б�������������б��е�����Ԫ�ض�����ʵ�� Comparable �ӿڡ����⣬�б��е�����Ԫ�ض������ǿ��໥�Ƚϵģ�Ҳ����˵�������б��е��κ� e1 �� e2 Ԫ�أ�e1.compareTo(e2) �����׳� ClassCastException����

//ArrayListTest.java

import java.util.*;
class ArrayListTest
{

	public static void printElement( Collection c )
	{
		Iterator it = c.iterator();
		while ( it.hasNext() )
		{
			System.out.println( it.next() );
		}
	}
	@SuppressWarnings(value = { "unchecked" })  //���� @SuppressWarnings("unchecked")
	public static void main(String[] args)
	{

		ArrayList al = new ArrayList();
		al.add( new Student(2,"zhangsan") );
		al.add( new Student(3,"lisi") );
		al.add( new Student(1,"wangwu") );

		System.out.println( "Before Sorting" );
		printElement( al );
		Collections.sort( al );//����
		System.out.println( "After Sorting" );
		printElement( al );

	}
}

class Student implements Comparable
{
	int num;
	String name;

	Student(int num,String name)
	{
		this.num=num;
		this.name=name;
	}

	public int compareTo(Object o)//������Ϊ�˽���sort���������ʵ�ֵĽӿں���
	{
		Student s=(Student)o;
		return num > s.num ? 1 : (num==s.num ? 0 : -1);
	}
	public String toString()//�����Ϊ�˴�ӡ������ʵ�ֵĽӿں���
	{
		return num+":"+name;
	}
}

Before Sorting
2:zhangsan
3:lisi
1:wangwu
After Sorting
1:wangwu
2:zhangsan
3:lisi





�������ʱ�򻹿��Դ���һ���Ƚ����������Ͳ���Ҫʵ��Comparable�ӿ�
static <T> void sort(List<T> list, Comparator<? super T> c)
          ����ָ���Ƚ���������˳���ָ���б��������
//ArrayListTest.java
import java.util.*;
class ArrayListTest
{
	public static void printElement( Collection c )
	{
		Iterator it = c.iterator();
		while ( it.hasNext() )
		{
			System.out.println( it.next() );
		}
	}
	@SuppressWarnings(value = { "unchecked" })  //���� @SuppressWarnings("unchecked")
	public static void main(String[] args)
	{
		ArrayList al = new ArrayList();
		al.add( new Student(2,"zhangsan") );
		al.add( new Student(3,"lisi") );
		al.add( new Student(3,"apple") );
		al.add( new Student(1,"wangwu") );

		System.out.println( "Before Sorting" );
		printElement( al );
		Collections.sort( al, new Student.StudentComparator() );//ͨ��ָ���Ƚ�����������
		System.out.println( "After Sorting" );
		printElement( al );
	}
}
class Student// implements Comparable
{
	int num;
	String name;

	Student(int num,String name)
	{
		this.num=num;
		this.name=name;
	}

	//����һ���ڲ�����ʵ��sort������ָ���Ƚ���������˳���ָ���б��������
	static class StudentComparator implements Comparator
	{
		public int compare(Object o1,Object o2)
		{
			Student s1=(Student)o1;
			Student s2=(Student)o2;
			int result=s1.num > s2.num ? 1 : (s1.num==s2.num ? 0 : -1);
			return result;
		}
	}
	public String toString()//�����Ϊ�˴�ӡ������ʵ�ֵĽӿں���
	{
		return num+":"+name;
	}
}

Before Sorting
2:zhangsan
3:lisi
3:apple
1:wangwu
After Sorting
1:wangwu
2:zhangsan
3:lisi
3:apple

������������������ȣ��Ͱ��������ڽ������򣬾��������appleӦ������lisiǰ�棬
��Ϊ�������˱Ƚ�������ô����ʵ�������ܷ��㣬ֻ�轫compare������д���£�
		public int compare(Object o1,Object o2)
		{
			Student s1=(Student)o1;
			Student s2=(Student)o2;
			int result=s1.num > s2.num ? 1 : (s1.num==s2.num ? 0 : -1);
			if( result==0 )
			{
				result=s1.name.compareTo(s2.name);
			}
			return result;
		}

�����ĳ������£�
//ArrayListTest.java
import java.util.*;
class ArrayListTest
{
	public static void printElement( Collection c )
	{
		Iterator it = c.iterator();
		while ( it.hasNext() )
		{
			System.out.println( it.next() );
		}
	}
	@SuppressWarnings(value = { "unchecked" })  //���� @SuppressWarnings("unchecked")
	public static void main(String[] args)
	{
		ArrayList al = new ArrayList();
		al.add( new Student(2,"zhangsan") );
		al.add( new Student(3,"lisi") );
		al.add( new Student(3,"apple") );
		al.add( new Student(1,"wangwu") );

		System.out.println( "Before Sorting" );
		printElement( al );
		Collections.sort( al, new Student.StudentComparator() );//ͨ��ָ���Ƚ�����������
		System.out.println( "After Sorting" );
		printElement( al );
	}
}
class Student// implements Comparable
{
	int num;
	String name;

	Student(int num,String name)
	{
		this.num=num;
		this.name=name;
	}

	//����һ���ڲ�����ʵ��sort������ָ���Ƚ���������˳���ָ���б��������
	static class StudentComparator implements Comparator
	{
		public int compare(Object o1,Object o2)
		{
			Student s1=(Student)o1;
			Student s2=(Student)o2;
			int result=s1.num > s2.num ? 1 : (s1.num==s2.num ? 0 : -1);
			if( result==0 )
			{
				result=s1.name.compareTo(s2.name);
			}
			return result;
		}
	}
	public String toString()//�����Ϊ�˴�ӡ������ʵ�ֵĽӿں���
	{
		return num+":"+name;
	}
}
Before Sorting
2:zhangsan
3:lisi
3:apple
1:wangwu
After Sorting
1:wangwu
2:zhangsan
3:apple
3:lisi


���Ҫ�������У��Ǻܺð죬Collections������������һ������ Collections.reverseOrder()) ��
��ȫ����ʵ�֡�

//ArrayListTest.java
import java.util.*;
class ArrayListTest
{
	public static void printElement( Collection c )
	{
		Iterator it = c.iterator();
		while ( it.hasNext() )
		{
			System.out.println( it.next() );
		}
	}
	@SuppressWarnings(value = { "unchecked" })  //���� @SuppressWarnings("unchecked")
	public static void main(String[] args)
	{
		ArrayList al = new ArrayList();
		al.add( new Student(2,"zhangsan") );
		al.add( new Student(3,"apple") );
		al.add( new Student(3,"lisi") );
		al.add( new Student(1,"wangwu") );

		System.out.println( "Before Sorting" );
		printElement( al );
		Collections.sort( al, Collections.reverseOrder() );//ͨ��ָ���Ƚ�����������
		System.out.println( "After Sorting" );
		printElement( al );
	}
}
class Student// implements Comparable
{
	int num;
	String name;

	Student(int num,String name)
	{
		this.num=num;
		this.name=name;
	}

	//����һ���ڲ�����ʵ��sort������ָ���Ƚ���������˳���ָ���б��������
	static class StudentComparator implements Comparator
	{
		public int compare(Object o1,Object o2)
		{
			Student s1=(Student)o1;
			Student s2=(Student)o2;
			int result=s1.num > s2.num ? 1 : (s1.num==s2.num ? 0 : -1);
			if( result==0 )
			{
				result=s1.name.compareTo(s2.name);
			}
			return result;
		}
	}
	public String toString()//�����Ϊ�˴�ӡ������ʵ�ֵĽӿں���
	{
		return num+":"+name;
	}
}

�������������
Before Sorting
2:zhangsan
3:apple
3:lisi
1:wangwu
Exception in thread "main" java.lang.ClassCastException: Student
	at java.util.Collections$ReverseComparator.compare(Unknown Source)
	at java.util.Arrays.mergeSort(Unknown Source)
	at java.util.Arrays.sort(Unknown Source)
	at java.util.Collections.sort(Unknown Source)
	at ArrayListTest.main(ArrayListTest.java:24)
������Ϣ�������ǣ�����û��ʵ��ReverseComparator.compare()������
Ŷ������û��ʵ��compare����
����ð�����ʵ��Comparable�ӿھͺ��ˣ�
//ArrayListTest.java
import java.util.*;
class ArrayListTest
{
	public static void printElement( Collection c )
	{
		Iterator it = c.iterator();
		while ( it.hasNext() )
		{
			System.out.println( it.next() );
		}
	}
	@SuppressWarnings(value = { "unchecked" })  //���� @SuppressWarnings("unchecked")
	public static void main(String[] args)
	{
		ArrayList al = new ArrayList();
		al.add( new Student(3,"apple") );
		al.add( new Student(2,"zhangsan") );
		al.add( new Student(3,"lisi") );
		al.add( new Student(1,"wangwu") );

		System.out.println( "Before Sorting" );
		printElement( al );
		Collections.sort( al, Collections.reverseOrder() );//ͨ��ָ���Ƚ�����������
		System.out.println( "After Sorting" );
		printElement( al );
	}
}
class Student implements Comparable
{
	int num;
	String name;

	Student(int num,String name)
	{
		this.num=num;
		this.name=name;
	}

	/*//����һ���ڲ�����ʵ��sort������ָ���Ƚ���������˳���ָ���б��������
	static class StudentComparator implements Comparator
	{
		public int compare(Object o1,Object o2)
		{
			Student s1=(Student)o1;
			Student s2=(Student)o2;
			int result=s1.num > s2.num ? 1 : (s1.num==s2.num ? 0 : -1);
			if( result==0 )
			{
				result=s1.name.compareTo(s2.name);
			}
			return result;
		}
	}*/
	public int compareTo(Object o)//������Ϊ�˽���sort���������ʵ�ֵĽӿں���
	{
		Student s=(Student)o;
		return num > s.num ? 1 : (num==s.num ? 0 : -1);
	}
	public String toString()//�����Ϊ�˴�ӡ������ʵ�ֵĽӿں���
	{
		return num+":"+name;
	}
}

Before Sorting
3:lisi
2:zhangsan
3:apple
1:wangwu
After Sorting
3:apple
3:lisi
2:zhangsan
1:wangwu

���������ͬ����ŵ�������Щ��������⣬�����������ͬ�󣬼���ͨ����������
����list��apple����ô�����Ӧ��list��appleǰ.
�ö�,���������ĵ�, reverseOrder(Comparator<T> cmp) Ҳ����ͨ��ָ���ıȽ�����������,
�����ͺð����.

//ArrayListTest.java
import java.util.*;
class ArrayListTest
{
	public static void printElement( Collection c )
	{
		Iterator it = c.iterator();
		while ( it.hasNext() )
		{
			System.out.println( it.next() );
		}
	}
	@SuppressWarnings(value = { "unchecked" })  //���� @SuppressWarnings("unchecked")
	public static void main(String[] args)
	{
		ArrayList al = new ArrayList();
		al.add( new Student(3,"apple") );
		al.add( new Student(2,"zhangsan") );
		al.add( new Student(3,"lisi") );
		al.add( new Student(1,"wangwu") );

		System.out.println( "Before Sorting" );
		printElement( al );
		Collections.sort( al, Collections.reverseOrder( new Student.StudentComparator() ) );//ͨ��ָ���Ƚ�����������
		System.out.println( "After Sorting" );
		printElement( al );
	}
}
class Student
{
	int num;
	String name;

	Student(int num,String name)
	{
		this.num=num;
		this.name=name;
	}

	//����һ���ڲ�����ʵ��sort������ָ���Ƚ���������˳���ָ���б��������
	static class StudentComparator implements Comparator
	{
		public int compare(Object o1,Object o2)
		{
			Student s1=(Student)o1;
			Student s2=(Student)o2;
			int result=s1.num > s2.num ? 1 : (s1.num==s2.num ? 0 : -1);
			if( result==0 )
			{
				result=s1.name.compareTo(s2.name);
			}
			return result;
		}
	}
	public String toString()//�����Ϊ�˴�ӡ������ʵ�ֵĽӿں���
	{
		return num+":"+name;
	}
}

Before Sorting
3:apple
2:zhangsan
3:lisi
1:wangwu
After Sorting
3:lisi
3:apple
2:zhangsan
1:wangwu

ȡ������С��Ԫ�أ�Collections.max()��Collections.min()��
���������List������ָ����Ԫ�أ�Collectons.binarySearch()��

LinkedList
LinkedList�ǲ���˫��ѭ������ʵ�ֵġ�
����LinkedListʵ��ջ(stack)������(queue)��˫�����(double-ended queue )��


ջ(Stack)Ҳ��һ����������Ա���һ�ֺ���ȳ�(LIFO)�Ľṹ��
ջ���޶����ڱ�β���в����ɾ����������Ա���β��Ϊջ��(top)����ͷ��Ϊջ��(bottom)��
ջ������洢������˳��洢�ṹ��Ҳ��������ʽ�洢�ṹ��

����LinkedListʵ��ջ(stack):

//MyStack.java
import java.util.*;
public class MyStack {

	/**
	 * @param args
	 */
	private LinkedList ll=new LinkedList();
	@SuppressWarnings(value = { "unchecked" })
	public void push(Object o)//ѹ��һ��Ԫ��,�����Ǽ���һ��Ԫ�ص���ͷ
	{
		ll.addFirst( o );
	}
	public Object pop()//����һ��Ԫ��
	{
		return ll.removeFirst();
	}
	public Object peek()
	{
		return ll.getFirst();
	}
	public boolean empty()
	{
		return ll.isEmpty();
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		MyStack ms=new MyStack();
		ms.push("one");
		ms.push("two");
		ms.push("three");

		System.out.println(ms.pop());
		System.out.println(ms.peek());
		System.out.println(ms.pop());
		System.out.println(ms.empty());
	}

}

three
two
two
false


����(Queue)���޶����еĲ���ֻ���ڱ��һ�˽��У������е�ɾ�����ڱ����һ�˽��е����Ա�
������������һ�˳�Ϊ��β(Rear)������ɾ����һ�˳�Ϊ��ͷ(Front)��
���еĲ����ǰ��Ƚ��ȳ�(FIFO)��ԭ����еġ�
���е�����洢������˳��洢�ṹ��Ҳ��������ʽ�洢�ṹ��

//MyQueue.java
import java.util.*;
public class MyQueue {

	/**
	 * @param args
	 */
	private LinkedList ll=new LinkedList();
	@SuppressWarnings(value = { "unchecked" })
	public void put(Object o)
	{
		ll.addLast(o);
	}
	public Object get()
	{
		return ll.removeFirst();
	}
	public boolean empty()
	{
		return ll.isEmpty();
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		MyQueue mq=new MyQueue();
		mq.put("one");
		mq.put("two");
		mq.put("three");

		System.out.println(mq.get());
		System.out.println(mq.get());
		System.out.println(mq.get());
		System.out.println(mq.empty());
	}

}
one
two
three
true

ArrayList��LinkedList�ıȽ�
ArrayList�ײ����������ɣ���LinkedList������һ���˫������(double-linked list)��ɣ�����ÿ������������ݱ����⣬�������� ���ã��ֱ�ָ��ǰһ��Ԫ�غͺ�һ��Ԫ�ء�
������Ǿ�����List�Ŀ�ʼ������Ԫ�أ�������List�н��в����ɾ������������Ӧ��ʹ��LinkedList������Ļ���ʹ��ArrayList�����ӿ��١�


HashSet
ʵ��Set�ӿڵ�hash table(��ϣ��)������HashMap��ʵ�ֵġ�
����Ӧ��ΪҪ��ŵ�ɢ�б�ĸ���������hashCode()��equals()��
ɢ�б��ֳ�Ϊ��ϣ��ɢ�б��㷨�Ļ���˼���ǣ�
  �Խ��Ĺؼ���Ϊ�Ա�����ͨ��һ���ĺ�����ϵ��ɢ�к������������Ӧ�ĺ���ֵ�������ֵ��Ϊ�ý��洢��ɢ�б��еĵ�ַ��
��ɢ�б��е�Ԫ�ش��̫�����ͱ��������ɢ�У�������һ���µ�ɢ�б�����Ԫ�ش�ŵ��µ�ɢ�б��У�ԭ�ȵ�ɢ�б���ɾ������Java�����У�ͨ����������(load factor)��������ʱ��ɢ�б������ɢ�С����磺�������������0.75����ɢ�б����Ѿ���75%��λ���Ѿ���������ô��������ɢ�С�
��������Խ��(Խ�ӽ�1.0)���ڴ��ʹ��Ч��Խ�ߣ�Ԫ�ص�Ѱ��ʱ��Խ������������Խ��(Խ�ӽ�0.0)��Ԫ�ص�Ѱ��ʱ��Խ�̣��ڴ��˷�Խ�ࡣ
HashSet���ȱʡ����������0.75��

//HashSetTest.java
import java.util.*;
public class HashSetTest {

	/**
	 * @param args
	 */
	@SuppressWarnings(value = { "unchecked" })
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		HashSet hs=new HashSet();
		hs.add("one");
		hs.add("two");
		hs.add("three");
		hs.add("one");//HashSetʵ����Set�ӿڣ����Բ��ܳ����ظ���Ԫ�أ����ｫ�����
		Iterator it=hs.iterator();
		while(it.hasNext())
		{
			System.out.println(it.next());
		}
	}
}
��ӡ���:
one
two
three




//HashSetTest.java
import java.util.*;
public class HashSetTest {

	/**
	 * @param args
	 */
	@SuppressWarnings(value = { "unchecked" })
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		HashSet hs=new HashSet();
		hs.add(new Student(1,"zhangsan"));
		hs.add(new Student(2,"lisi"));
		hs.add(new Student(3,"wangwu"));
		hs.add(new Student(1,"zhangsan"));
		Iterator it=hs.iterator();
		while(it.hasNext())
		{
			System.out.println(it.next());
		}
	}
}
class Student
{
	int num;
	String name;
	Student(int num,String name)
	{
		this.num=num;
		this.name=name;
	}
	public String toString()
	{
		return num+":"+name;
	}
}

3:wangwu
2:lisi
1:zhangsan
1:zhangsan
�����������ͬ��Ԫ�ر���ŵ�HashSet��,Ϊʲô?
��ΪHashSet�Ǹ���Object����hashCode()�����������ϣ��������Ԫ���ڹ�ϣ���е�λ��,
����hashCode()�����Ǹ��ݶ�����ڲ���ַ�������
Ϊ�˱�����Щ����ķ��������Ǳ��뽫����ӵ�HashSet���еĶ������� hashCode() �� equals() ����.
����Ӧ��ΪҪ��ŵ�ɢ�б�ĸ���������hashCode()��equals()��
��������������һ��:
//HashSetTest.java
import java.util.*;
public class HashSetTest {

	/**
	 * @param args
	 */
	@SuppressWarnings(value = { "unchecked" })
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		HashSet hs=new HashSet();
		hs.add(new Student(1,"zhangsan"));
		hs.add(new Student(2,"lisi"));
		hs.add(new Student(3,"wangwu"));
		hs.add(new Student(1,"zhangsan"));
		Iterator it=hs.iterator();
		while( it.hasNext() ) {
			System.out.println(it.next());
		}
	}
}
class Student
{
	int num;
	String name;
	Student(int num,String name)
	{
		this.num=num;
		this.name=name;
	}
	public int hashCode()
	{
		return num*name.hashCode();
	}
	public boolean equals(Object o)
	{
		Student s=(Student)o;
		return num==s.num && name.equals(s.name);
	}
	public String toString()
	{
		return num+":"+name;
	}
}

1:zhangsan
3:wangwu
2:lisi

������û��ͬ���������.

TreeSet
TreeSet������TreeMap��ʵ�ֵġ�
TreeSet��һ�����򼯺ϣ�TreeSet��Ԫ�ؽ������������У�ȱʡ�ǰ�����Ȼ˳��������У���ζ��TreeSet��Ԫ��Ҫʵ��Comparable�ӿڡ�
���ǿ����ڹ���TreeSet����ʱ������ʵ����Comparator�ӿڵıȽ�������


//TreeSetTest.java
import java.util.*;
public class TreeSetTest
{
	@SuppressWarnings(value = { "unchecked" })
	public static void main(String[] args)
	{
		// TODO Auto-generated method stub
		TreeSet ts=new TreeSet();
		ts.add("winsun");
		ts.add("weixin");
		ts.add("mybole");

		Iterator it=ts.iterator();
		while(it.hasNext())
		{
			System.out.println(it.next());
		}
	}
}
E:\zieckey\Lesson8>javac TreeSetTest.java

E:\zieckey\Lesson8>java TreeSetTest
mybole
weixin
winsun

����Ҳ��������ʵ����Comparable�ӿڵ������
//TreeSetTest.java
import java.util.*;
public class TreeSetTest
{
	@SuppressWarnings(value = { "unchecked" })
	public static void main(String[] args)
	{
		TreeSet ts=new TreeSet();
		ts.add(new Student(2,"lisi"));
		ts.add(new Student(1,"wangwu"));
		ts.add(new Student(3,"zhangsan"));


		Iterator it=ts.iterator();
		while(it.hasNext())
		{
			System.out.println(it.next());
		}
	}
}
class Student implements Comparable
{
	int num;
	String name;

	Student(int num,String name)
	{
		this.num=num;
		this.name=name;
	}
	public int compareTo(Object o)//������Ϊ�˽���sort���������ʵ�ֵĽӿں���
	{
		Student s=(Student)o;
		return num > s.num ? 1 : (num==s.num ? 0 : -1);
	}
	public String toString()//�����Ϊ�˴�ӡ������ʵ�ֵĽӿں���
	{
		return num+":"+name;
	}
}
E:\zieckey\Lesson8>javac TreeSetTest.java

E:\zieckey\Lesson8>java TreeSetTest
1:wangwu
2:lisi
3:zhangsan

���ߴ���һ���Ƚ����Ķ���
//TreeSetTest.java
import java.util.*;
public class TreeSetTest
{
	@SuppressWarnings(value = { "unchecked" })
	public static void main(String[] args)
	{
		TreeSet ts=new TreeSet( new Student.StudentComparator() );
		ts.add(new Student(2,"lisi"));
		ts.add(new Student(1,"wangwu"));
		ts.add(new Student(3,"zhangsan"));


		Iterator it=ts.iterator();
		while(it.hasNext())
		{
			System.out.println(it.next());
		}
	}
}
class Student //implements Comparable
{
	int num;
	String name;

	Student(int num,String name)
	{
		this.num=num;
		this.name=name;
	}
	//����һ���ڲ�����ʵ��sort������ָ���Ƚ���������˳���ָ���б��������
	static class StudentComparator implements Comparator
	{
		public int compare(Object o1,Object o2)
		{
			Student s1=(Student)o1;
			Student s2=(Student)o2;
			int result=s1.num > s2.num ? 1 : (s1.num==s2.num ? 0 : -1);
			if( result==0 )
			{
				result=s1.name.compareTo(s2.name);
			}
			return result;
		}
	}
	/*public int compareTo(Object o)//������Ϊ�˽���sort���������ʵ�ֵĽӿں���
	{
		Student s=(Student)o;
		return num > s.num ? 1 : (num==s.num ? 0 : -1);
	}*/
	public String toString()//�����Ϊ�˴�ӡ������ʵ�ֵĽӿں���
	{
		return num+":"+name;
	}
}
E:\zieckey\Lesson8>javac TreeSetTest.java

E:\zieckey\Lesson8>java TreeSetTest
1:wangwu
2:lisi
3:zhangsan
HashSet��TreeSet�ıȽ�
HashSet�ǻ���Hash�㷨ʵ�ֵģ�������ͨ��������TreeSet������ͨ����Ӧ��ʹ��HashSet����������Ҫ����Ĺ���ʱ�����ǲ�ʹ��TreeSet��


HashMap
HashMap��key����ɢ�С�
keySet()��values()��entrySet()��
import java.util.*;
class HashMapTest
{
	public static void printElements(Collection c)
	{
		Iterator it=c.iterator();
		while(it.hasNext())
		{
			System.out.println(it.next());
		}
	}
	@SuppressWarnings(value = { "unchecked" })
	public static void main(String[] args)
	{
		HashMap hm=new HashMap();
		hm.put("one","zhangsan");
		hm.put("two","lisi");
		hm.put("three","wangwu");

		System.out.println(hm.get("one"));
		System.out.println(hm.get("two"));
		System.out.println(hm.get("three"));


		Set keys=hm.keySet();
		System.out.println("Key:");
		printElements(keys);

		Collection values=hm.values();
		System.out.println("Value:");
		printElements(values);

		System.out.println("EntrySet:");
		Set entry=hm.entrySet();
		printElements(entry);

		System.out.println("EntrySet");
		Iterator it=entry.iterator();
		while(it.hasNext())
		{
			Map.Entry me=(Map.Entry)it.next();
			System.out.println(me.getKey()+":"+me.getValue());
		}
	}
}
E:\zieckey\Lesson8>javac HashMapTest.java

E:\zieckey\Lesson8>java HashMapTest
zhangsan
lisi
wangwu
Key:
one
two
three
Value:
zhangsan
lisi
wangwu
EntrySet:
one=zhangsan
two=lisi
three=wangwu
EntrySet
one:zhangsan
two:lisi
three:wangwu

Properties ���ʾ��һ���־õ����Լ���Properties �ɱ��������л�����м��ء������б���ÿ���������Ӧֵ����һ���ַ�����

import java.util.*;
class PropertyTest
{
	public static void main(String[] args)
	{
		Properties pps=System.getProperties();
		pps.list(System.out);
	}
}

-- listing properties --
java.runtime.name=Java(TM) 2 Runtime Environment, Stand...
sun.boot.library.path=C:\Program Files\Java\jre1.5.0_08\bin
java.vm.version=1.5.0_08-b03
java.vm.vendor=Sun Microsystems Inc.
java.vendor.url=http://java.sun.com/
path.separator=;
java.vm.name=Java HotSpot(TM) Client VM
file.encoding.pkg=sun.io
user.country=CN
sun.os.patch.level=Service Pack 2
java.vm.specification.name=Java Virtual Machine Specification
user.dir=E:\JavaLesson\Lesson8
java.runtime.version=1.5.0_08-b03
java.awt.graphicsenv=sun.awt.Win32GraphicsEnvironment
java.endorsed.dirs=C:\Program Files\Java\jre1.5.0_08\lib...
os.arch=x86
java.io.tmpdir=M:\DOCUME~1\apple\LOCALS~1\Temp\
line.separator=

java.vm.specification.vendor=Sun Microsystems Inc.
user.variant=
os.name=Windows XP
sun.jnu.encoding=GBK
java.library.path=C:\Program Files\Java\jre1.5.0_08\bin...
java.specification.name=Java Platform API Specification
java.class.version=49.0
sun.management.compiler=HotSpot Client Compiler
os.version=5.1
user.home=M:\Documents and Settings\apple
user.timezone=
java.awt.printerjob=sun.awt.windows.WPrinterJob
file.encoding=GBK
java.specification.version=1.5
user.name=apple
java.class.path=E:\JavaLesson\Lesson8
java.vm.specification.version=1.0
sun.arch.data.model=32
java.home=C:\Program Files\Java\jre1.5.0_08
java.specification.vendor=Sun Microsystems Inc.
user.language=zh
awt.toolkit=sun.awt.windows.WToolkit
java.vm.info=mixed mode, sharing
java.version=1.5.0_08
java.ext.dirs=C:\Program Files\Java\jre1.5.0_08\lib...
sun.boot.class.path=C:\Program Files\Java\jre1.5.0_08\lib...
java.vendor=Sun Microsystems Inc.
file.separator=\
java.vendor.url.bug=http://java.sun.com/cgi-bin/bugreport...
sun.cpu.endian=little
sun.io.unicode.encoding=UnicodeLittle
sun.desktop=windows
sun.cpu.isalist=pentium_pro+mmx pentium_pro pentium+m...



����Properties���������ļ������������µģ�
company=winsun
author=sunxin
copyright=2003-2004

���ļ�������winsun.ini�У���ô�����п���������ȡ�ļ����ݣ�

import java.util.*;
import java.io.*;
class PropertyTest
{
	public static void main(String[] args)
	{
		Properties pps=new Properties();
		try
		{
			pps.load(new FileInputStream("winsun.ini"));
			Enumeration enumer=pps.propertyNames();
			while(enumer.hasMoreElements())
			{
				String strKey=(String)enumer.nextElement();
				String strValue=pps.getProperty(strKey);

				System.out.println(strKey+"="+strValue);
			}
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
	}
}
�����
company=winsun
copyright=2003-2004
author=sunxin



Lesson9
Java I/O����

File��
һ��File��Ķ��󣬱�ʾ�˴����ϵ��ļ���Ŀ¼��
File���ṩ����ƽ̨�޹صķ������Դ����ϵ��ļ���Ŀ¼���в�����


package file;
import java.io.*;
public class FileTest {
	public static void main(String[] args) {
		File f = new File( "1.txt" );
		try{
			f.createNewFile();
			f.mkdir();
		}
		catch( Exception e ){
			e.printStackTrace();
		}
	}
}
����ֻ���ڵ�ǰĿ¼�´���һ�� 1.txt �ļ��������ᴴ�� 1.txt �ļ��С�
package file;
import java.io.*;
public class FileTest {
	public static void main(String[] args) {
		File f = new File( "1.txt" );
		try{
			f.mkdir();
		}
		catch( Exception e ){
			e.printStackTrace();
		}
	}
}
�����ͻᴴ��һ���ļ��С�

Ҳ������ָ��·���������ļ���
package file;
import java.io.*;
public class FileTest {
	public static void main(String[] args) {
		File f = new File( "E:\\JavaLesson\\Lesson9\\1.txt" );
		try{
			f.createNewFile();
		}
		catch( Exception e ){
			e.printStackTrace();
		}
	}
}
����д�Ĵ��������ֲ��Linux�¾ͻ�������⣬��Ϊ·����ʽ���ԡ�
�����Ǵ���һ���ļ�������ƽ̨�޹ء�
package file;
import java.io.*;
public class FileTest {
	public static void main(String[] args) {
		//File.separator��ʾ��Ŀ¼�ָ����������������ض�����ϵͳ
		//File.separatorֱ���ÿ��Ա�ʾWindow��ǰ�̷��ĸ�Ŀ¼
		File fDir=new File(File.separator);
		String strFile="JavaLesson"+File.separator+"Lesson9"+
			File.separator+"2.txt";
		File f=new File(fDir,strFile);//�½�һ��File����
		try{
			f.createNewFile();
		}
		catch( Exception e ){
			e.printStackTrace();
		}
	}
}

ɾ���ļ���Ŀ¼��
 boolean delete()
          ɾ���˳���·������ʾ���ļ���Ŀ¼��
 void deleteOnExit()
          ���������ֹʱ������ɾ���˳���·������ʾ���ļ���Ŀ¼��

�ڳ����д�����ʱ�ļ���Ȼ���ٳ����˳�ʱɾ����ʱ�ļ���
//FileTest.java
package file;
import java.io.*;
public class FileTest {
	public static void main(String[] args) {
		for(int i=0;i<5;i++)
		{
			try{
				File f=File.createTempFile("winsun",".tmp");
				f.deleteOnExit();
			}
			catch( Exception e ){
				e.printStackTrace();
			}

		}
		try{
			Thread.sleep(5000);
		}
		catch( Exception e ){
			e.printStackTrace();
		}
	}
}


 String[] list()
          �����ɴ˳���·��������ʾ��Ŀ¼�е��ļ���Ŀ¼������������ַ������顣
//FileTest.java
package file;
import java.io.*;
public class FileTest {
	public static void main(String[] args) {
		File fDir=new File(File.separator);
		String strFile="JavaLesson"+File.separator+"Lesson9";
		File f=new File(fDir,strFile);
		String[] names=f.list();
		for(int i=0;i<names.length;i++)
		{
			System.out.println(names[i]);
		}
	}
}
�����
.project
.classpath
src
bin
1.txt
2.txt

String[] list(FilenameFilter filter)
          �����ɰ�����Ŀ¼�е��ļ���Ŀ¼����������ɵ��ַ������飬��һĿ¼��ͨ������ָ���������ĳ���·��������ʾ�ġ�
//FileTest.java
package file;
import java.io.*;
public class FileTest {
	public static void main(String[] args) {
		File fDir=new File(File.separator);
		String strFile="JavaLesson"+File.separator+"Lesson9";
		File f=new File(fDir,strFile);
		String[] names=f.list(new FilenameFilter() //����һ�������������Ǹ��ӿڣ�
		{//ͨ���������ڲ��ഴ������ӿڵ�ʵ������
			public boolean accept(File dir,String name)
			{
				return name.indexOf(".txt")!=-1;
			}
		});
		for(int i=0;i<names.length;i++)
		{
			System.out.println(names[i]);
		}
	}
}

E:\JavaLesson\Lesson9\src\file>javac FileTest.java -d .

E:\JavaLesson\Lesson9\src\file>java file.FileTest
1.txt
2.txt


��ʽI/O
��(Stream)���ֽڵ�Դ��Ŀ�ġ�
���ֻ��������ǣ�������(Input Stream)�������(Output Stream)���ɴ��ж���һϵ���ֽڵĶ����Ϊ������������������д��һϵ���ֽڵĶ����Ϊ�������

���ķ���
�ڵ��������ض��ĵط���д�����࣬���磺���̻�һ���ڴ�����
��������ʹ�ýڵ�����Ϊ������������������ʹ��һ���Ѿ����ڵ�����������������Ӵ����ġ�

InputStream
���������Ķ�����
      abstract int read() ����ȡһ���ֽ����ݣ������ض��������ݣ��������-1����ʾ��������������ĩβ��
      int read(byte[]?b) �������ݶ���һ���ֽ����飬ͬʱ����ʵ�ʶ�ȡ���ֽ������������-1����ʾ��������������ĩβ��
      int read(byte[]?b, int?off, int?len) �������ݶ���һ���ֽ����飬ͬʱ����ʵ�ʶ�ȡ���ֽ������������-1����ʾ��������������ĩβ��offָ��������b�д�����ݵ���ʼƫ��λ�ã�lenָ����ȡ������ֽ�����
��������
      long skip(long?n) ����������������n���ֽڣ�������ʵ���������ֽ�����
      int available() �������ڲ���������������£��ɶ�ȡ���ֽ�����
      void close() ���ر����������ͷź��������ص�ϵͳ��Դ��
      void mark(int?readlimit) �����������ĵ�ǰλ�÷���һ����ǣ������ȡ���ֽ�������readlimit���õ�ֵ���������������ǡ�
      void reset() �����ص���һ����ǡ�
      boolean markSupported() �����Ե�ǰ���Ƿ�֧��mark��reset���������֧�֣�����true�����򷵻�false��

OutputStream
����������д����
     abstract void write(int?b) �����������д��һ���ֽڡ�
     void write(byte[]?b) �����������д������b�е������ֽڡ�
     void write(byte[]?b, int?off, int?len) �����������д������b�д�ƫ����off��ʼ��len���ֽڵ����ݡ�
��������
     void flush() ��ˢ���������ǿ�ƻ������е�����ֽڱ�д����
     void close() ���ر���������ͷź��������ص�ϵͳ��Դ��



//StreamTest.java
package myStream;

public class StreamTest {
	public static void main(String[] args) {
		int data;
		try{
			while((data=System.in.read())!=-1)//�ӱ�׼�����豸��ȡ������
			{
				System.out.write(data);//�������׼����豸
			}
		}
		catch( Exception e ) {
			e.printStackTrace();
		}
	}
}

flaksd;fasd
flaksd;fasd
sdjfalsdkjf'asd
fsdjfalsdkjf'asd
asdjfalskdjfas
fasdjfalskdjfas
jasd;lkfja'sdf
jasd;lkfja'sdf
jalsdkfj
jalsdkfj
lksjdfa;l
lksjdfa;l
lkjafsd
lkjafsd
lkja'sdf
lkja'sdf


����������
FileInputStream��FileOutputStream
    �ڵ��������ڴ��ļ��ж�ȡ�����ļ���д���ֽ���������ڹ���FileOutputStreamʱ���ļ��Ѿ����ڣ��򸲸�����ļ���
BufferedInputStream��BufferedOutputStream
    ����������Ҫʹ���Ѿ����ڵĽڵ��������죬�ṩ������Ķ�д������˶�д��Ч�ʡ�
DataInputStream��DataOutputStream
      ����������Ҫʹ���Ѿ����ڵĽڵ��������죬�ṩ�˶�дJava�еĻ����������͵Ĺ��ܡ�
PipedInputStream��PipedOutputStream
    �ܵ����������̼߳��ͨ�š�һ���̵߳�PipedInputStream�������һ���̵߳�PipedOutputStream�����ȡ���롣Ҫʹ�ܵ������ã�����ͬʱ����ܵ��������͹ܵ��������

//StreamTest.java
package myStream;
import java.io.*;
public class StreamTest {
	public static void main(String[] args) {
		try{
			FileOutputStream fos=new FileOutputStream("1.txt");
			fos.write("http://zieckey.cubblog.cn".getBytes());
			fos.close();

			FileInputStream fis=new FileInputStream("1.txt");
			byte[] buf=new byte[100];
			int len=fis.read(buf);
			System.out.println(new String(buf,0,len));
		}
		catch( Exception e ){
			e.printStackTrace();
		}
	}
}

http://zieckey.cubblog.cn

�����ڴ滺������ʵ�֣�
//StreamTest.java
package myStream;
import java.io.*;
public class StreamTest {
	public static void main(String[] args) {
		try{
			FileOutputStream fos=new FileOutputStream("1.txt");
			BufferedOutputStream bos = new BufferedOutputStream(fos);
			bos.write("http://zieckey.cubblog.cn".getBytes());
			bos.flush();	//д��Ӳ�̣�����Ҳ��������	bos.close();�������������������
		}
		catch( Exception e ){
			e.printStackTrace();
		}
	}
}

//StreamTest.java
package myStream;
import java.io.*;
public class StreamTest {
	public static void main(String[] args) {
		try{
			FileOutputStream fos=new FileOutputStream("1.txt");
			BufferedOutputStream bos = new BufferedOutputStream(fos);
			bos.write("http://zieckey.cubblog.cn".getBytes());
			bos.flush();

			FileInputStream fis=new FileInputStream("1.txt");
			BufferedInputStream bis = new BufferedInputStream( fis );
			byte[] buf=new byte[100];
			int len=bis.read(buf);
			System.out.println(new String(buf,0,len));
			bis.close();
		}
		catch( Exception e ){
			e.printStackTrace();
		}
	}
}

DataInputStream��DataOutputStream
      ����������Ҫʹ���Ѿ����ڵĽڵ��������죬�ṩ�˶�дJava�еĻ����������͵Ĺ��ܡ�
//StreamTest.java
package myStream;
import java.io.*;
public class StreamTest {
	public static void main(String[] args) {
		try{
			FileOutputStream fos=new FileOutputStream("1.txt");
			BufferedOutputStream bos = new BufferedOutputStream(fos);
			DataOutputStream dos = new DataOutputStream( bos );
			byte b=3;
			int i=78;
			char ch='a';
			float f=4.5f;
			dos.writeByte(b);
			dos.writeInt(i);
			dos.writeChar(ch);
			dos.writeFloat(f);
			dos.close();
		}
		catch( Exception e ){
			e.printStackTrace();
		}
	}
}

//StreamTest.java
package myStream;
import java.io.*;
public class StreamTest {
	public static void main(String[] args) {
		try{
			FileOutputStream fos=new FileOutputStream("1.txt");
			BufferedOutputStream bos = new BufferedOutputStream(fos);
			DataOutputStream dos = new DataOutputStream( bos );
			byte b=3;
			int i=78;
			char ch='a';
			float f=4.5f;
			dos.writeByte(b);
			dos.writeInt(i);
			dos.writeChar(ch);
			dos.writeFloat(f);
			dos.close();

			FileInputStream fis=new FileInputStream("1.txt");
			BufferedInputStream bis=new BufferedInputStream(fis);
			DataInputStream dis=new DataInputStream(bis);
			System.out.println(dis.readByte());
			System.out.println(dis.readInt());
			System.out.println(dis.readChar());
			System.out.println(dis.readFloat());
			dis.close();

		}
		catch( Exception e ){
			e.printStackTrace();
		}
	}
}

3
78
a
4.5


PipedInputStream��PipedOutputStream
    �ܵ����������̼߳��ͨ�š�һ���̵߳�PipedInputStream�������һ���̵߳�PipedOutputStream�����ȡ���롣Ҫʹ�ܵ������ã�����ͬʱ����ܵ��������͹ܵ��������

package myPipeStream;
import java.io.*;
public class PipedStreamTest {
	public static void main(String[] args) {
		PipedOutputStream pos=new PipedOutputStream();
		PipedInputStream pis=new PipedInputStream();
		try
		{
			pos.connect(pis);
			new Producer(pos).start();
			new Consumer(pis).start();
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
	}

}

class Producer extends Thread
{
	private PipedOutputStream pos;
	public Producer(PipedOutputStream pos)
	{
		this.pos=pos;
	}
	public void run()
	{
		try
		{
			pos.write("Hello,welcome you!".getBytes());
			pos.close();
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
	}
}

class Consumer extends Thread
{
	private PipedInputStream pis;
	public Consumer(PipedInputStream pis)
	{
		this.pis=pis;
	}
	public void run()
	{
		try
		{
			byte[] buf=new byte[100];
			int len=pis.read(buf);
			System.out.println(new String(buf,0,len));
			pis.close();
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
	}
}

Java I/O������ԭ��
Java��I/O���ṩ��һ���������ӵĻ��ƣ����Խ�һ��������һ������β��ӣ��γ�һ�����ܵ������ӡ����ֻ���ʵ������һ�ֱ���ΪDecorator(װ��)���ģʽ��Ӧ�á�
ͨ���������ӣ����Զ�̬���������Ĺ��ܣ������ֹ��ܵ�������ͨ�����һЩ���Ļ������ܶ���̬��ȡ�ġ�
����Ҫ��ȡһ��I/O����������Ҫ�������I/O������Ҳ��Java I/O�ⲻ̫�������յ�ԭ�򣬵���I/O����Decoratorģʽ�����ã��������ṩ��ʵ���ϵ�����ԡ�

Reader��Writer
Java��������ʹ��Unicode����ʾ�ַ������ַ���
Reader��Writer��������������Ҫ������д�ַ�����

//StreamTest.java
package myStream;
import java.io.*;
public class StreamTest {
	public static void main(String[] args) {
		try{
			FileOutputStream fos=new FileOutputStream("1.txt");
			OutputStreamWriter osw=new OutputStreamWriter(fos);
			BufferedWriter bw=new BufferedWriter(osw);
			bw.write("http://zieckey.cublog.cn");//д������
			bw.close();

			FileInputStream fis=new FileInputStream("1.txt");
			InputStreamReader isr=new InputStreamReader(fis);
			BufferedReader br=new BufferedReader(isr);
			System.out.println(br.readLine());//��ȡ���ݲ����
			br.close();

		}
		catch( Exception e ){
			e.printStackTrace();
		}
	}
}
http://zieckey.cublog.cn


//StreamTest.java
package myStream;
import java.io.*;
public class StreamTest {
	public static void main(String[] args) {
		try{
			InputStreamReader isr=new InputStreamReader(System.in);
			BufferedReader br=new BufferedReader(isr);
			String strLine;
			while((strLine=br.readLine())!=null)
			{
				System.out.println(strLine);
			}
			br.close();
		}
		catch( Exception e ){
			e.printStackTrace();
		}
	}
}




�ַ����ı���ASCII(American Standard Code for Information Interchange��������Ϣ������׼����)��
�ǻ��ڳ��õ�Ӣ���ַ���һ�׵��Ա���ϵͳ��
����֪��Ӣ���о���ʹ�õ��ַ������ַ��ű����������ʱ�����Զ����������ʽ���ֵġ�
���ֶ�������ļ��Ͼ�����ν��ASCII�롣ÿһ��ASCII����һ��8λ��bit������������Ӧ��
�����λ��0����Ӧ��ʮ��������0-127���磬���֡�0���ı�����ʮ��������ʾ����48��
����128����չ��ASCII�룬���λ����1����һЩ�Ʊ��������������ɡ�
ASCII���ֽ���ͨ�õĵ��ֽڱ���ϵͳ��
GB2312��GB2312�����л����񹲺͹����Һ�����Ϣ�����ñ��룬ȫ�ơ���Ϣ�����ú��ֱ����ַ���������������
��Ҫ���ڸ�ÿһ�������ַ�ָ����Ӧ�����֣�Ҳ���ǽ��б��롣
һ�������ַ��������ֽڵ���������ʾ��Ϊ�˺�ASCII���������𣬽������ַ�ÿһ���ֽڵ����λ�ö���1����ʾ��
GBK��Ϊ�˶Ը�����ַ����б��룬�����ַ������µı���ϵͳGBK(GBK��K�ǡ���չ���ĺ���ƴ����һ����ĸ)��
���µı���ϵͳ�������ȫ����GB2312 �⣬���Է������ġ�һЩ�����õĺ��ֺ������Ž����˱��롣
ISO-8859-1��������������ʹ�õ��ַ����뼯����һ�ֵ��ֽڵ��ַ��� ����Ӣ��ʵ����ֻ������������С��128�Ĳ��֡�


Unicode������һ��ͨ�õ��ַ��������������Ե����ֽ�����ͳһ���룬��ÿһ���ַ�����2���ֽ�����ʾ��
����Ӣ���ַ���ȡǰ��ӡ�0���ֽڵĲ���ʵ�ֵȳ����ݡ��� ��a�� ��ASCII��Ϊ0x61��UNICODE��Ϊ0x00��0x61��
UTF-8��Eight-bit UCS Transformation Format��
(UCS��Universal Character Set��ͨ���ַ�����UCS �����������ַ�����׼��һ������)��
һ��7λ��ASCII��ֵ����Ӧ��UTF����һ���ֽڡ�
����ַ���0x0000������0x0080��0x007f֮�䣬��Ӧ��UTF���������ֽڣ�
����ַ���0x0800��0xffff֮�䣬��Ӧ��UTF���������ֽڡ�


�鿴��ǰϵͳ֧�ֵ��ַ�����
package myCharset;
import java.util.*;
import java.nio.charset.*;
public class CharsetTest {
	public static void main(String[] args) {
		Map m=Charset.availableCharsets();
		Set names=m.keySet();
		Iterator it=names.iterator();
		while(it.hasNext())
		{
			System.out.println(it.next());
		}
	}

}
Big5
Big5-HKSCS
EUC-JP
EUC-KR
GB18030
GB2312
GBK
IBM-Thai
IBM00858
IBM01140
IBM01141
IBM01142
IBM01143
IBM01144
IBM01145
IBM01146
IBM01147
IBM01148
IBM01149
IBM037
IBM1026
IBM1047
IBM273
IBM277
IBM278
IBM280
IBM284
IBM285
IBM297
IBM420
IBM424
IBM437
IBM500
IBM775
IBM850
IBM852
IBM855
IBM857
IBM860
IBM861
IBM862
IBM863
IBM864
IBM865
IBM866
IBM868
IBM869
IBM870
IBM871
IBM918
ISO-2022-CN
ISO-2022-JP
ISO-2022-KR
ISO-8859-1
ISO-8859-13
ISO-8859-15
ISO-8859-2
ISO-8859-3
ISO-8859-4
ISO-8859-5
ISO-8859-6
ISO-8859-7
ISO-8859-8
ISO-8859-9
JIS_X0201
JIS_X0212-1990
KOI8-R
Shift_JIS
TIS-620
US-ASCII
UTF-16
UTF-16BE
UTF-16LE
UTF-8
windows-1250
windows-1251
windows-1252
windows-1253
windows-1254
windows-1255
windows-1256
windows-1257
windows-1258
windows-31j
x-Big5-Solaris
x-euc-jp-linux
x-EUC-TW
x-eucJP-Open
x-IBM1006
x-IBM1025
x-IBM1046
x-IBM1097
x-IBM1098
x-IBM1112
x-IBM1122
x-IBM1123
x-IBM1124
x-IBM1381
x-IBM1383
x-IBM33722
x-IBM737
x-IBM834
x-IBM856
x-IBM874
x-IBM875
x-IBM921
x-IBM922
x-IBM930
x-IBM933
x-IBM935
x-IBM937
x-IBM939
x-IBM942
x-IBM942C
x-IBM943
x-IBM943C
x-IBM948
x-IBM949
x-IBM949C
x-IBM950
x-IBM964
x-IBM970
x-ISCII91
x-ISO-2022-CN-CNS
x-ISO-2022-CN-GB
x-iso-8859-11
x-JIS0208
x-JISAutoDetect
x-Johab
x-MacArabic
x-MacCentralEurope
x-MacCroatian
x-MacCyrillic
x-MacDingbat
x-MacGreek
x-MacHebrew
x-MacIceland
x-MacRoman
x-MacRomania
x-MacSymbol
x-MacThai
x-MacTurkish
x-MacUkraine
x-MS950-HKSCS
x-mswin-936
x-PCK
x-windows-50220
x-windows-50221
x-windows-874
x-windows-949
x-windows-950
x-windows-iso2022jp

�г���ǰϵͳ���ԣ�
//CharsetTest.java
package myCharset;
import java.util.*;
import java.nio.charset.*;
public class CharsetTest {
	public static void main(String[] args) {
		Properties pps=System.getProperties();
		pps.list(System.out);
	}
}
-- listing properties --
java.runtime.name=Java(TM) 2 Runtime Environment, Stand...
sun.boot.library.path=C:\Program Files\Java\jre1.5.0_08\bin
java.vm.version=1.5.0_08-b03
java.vm.vendor=Sun Microsystems Inc.
java.vendor.url=http://java.sun.com/
path.separator=;
java.vm.name=Java HotSpot(TM) Client VM
file.encoding.pkg=sun.io
user.country=CN
sun.os.patch.level=Service Pack 2
java.vm.specification.name=Java Virtual Machine Specification
user.dir=E:\JavaLesson\Lesson9
java.runtime.version=1.5.0_08-b03
java.awt.graphicsenv=sun.awt.Win32GraphicsEnvironment
java.endorsed.dirs=C:\Program Files\Java\jre1.5.0_08\lib...
os.arch=x86
java.io.tmpdir=M:\DOCUME~1\apple\LOCALS~1\Temp\
line.separator=

java.vm.specification.vendor=Sun Microsystems Inc.
user.variant=
os.name=Windows XP
sun.jnu.encoding=GBK
java.library.path=C:\Program Files\Java\jre1.5.0_08\bin...
java.specification.name=Java Platform API Specification
java.class.version=49.0
sun.management.compiler=HotSpot Client Compiler
os.version=5.1
user.home=M:\Documents and Settings\apple
user.timezone=
java.awt.printerjob=sun.awt.windows.WPrinterJob
file.encoding=GBK
java.specification.version=1.5
user.name=apple
java.class.path=E:\JavaLesson\Lesson9\bin
java.vm.specification.version=1.0
sun.arch.data.model=32
java.home=C:\Program Files\Java\jre1.5.0_08
java.specification.vendor=Sun Microsystems Inc.
user.language=zh
awt.toolkit=sun.awt.windows.WToolkit
java.vm.info=mixed mode, sharing
java.version=1.5.0_08
java.ext.dirs=C:\Program Files\Java\jre1.5.0_08\lib...
sun.boot.class.path=C:\Program Files\Java\jre1.5.0_08\lib...
java.vendor=Sun Microsystems Inc.
file.separator=\
java.vendor.url.bug=http://java.sun.com/cgi-bin/bugreport...
sun.cpu.endian=little
sun.io.unicode.encoding=UnicodeLittle
sun.desktop=windows
sun.cpu.isalist=pentium_pro+mmx pentium_pro pentium+m...

����� file.encoding=GBK ���ǵ�ǰϵͳ���ַ���Ĭ�ϱ���



//CharsetTest.java
package myCharset;
import java.util.*;
import java.nio.charset.*;
public class CharsetTest {
	public static void main(String[] args) throws Exception {
		Properties pps=System.getProperties();
		pps.put("file.encoding","ISO-8859-1");//�������õ�ǰ�ַ����ı����׼
		int data;
		byte[] buf=new byte[100];
		int i=0;
		while((data=System.in.read())!='q')//������ַ�����ISO-8859-1�����ֽڴ����buf��,����q����
		{
			buf[i]=(byte)data;
			i++;
		}
		String str=new String(buf,0,i);
		System.out.println(str);//������Ե�ǰϵͳĬ�ϵ��ַ�������ģ��������GBK

		//ͨ��str.getBytes("ISO-8859-1")���½��룬Ȼ����GBK����
		String strGBK=new String(str.getBytes("ISO-8859-1"),"GBK");
		System.out.println(strGBK);//�����Ĭ�ϱ����ʽ���룬�����͵õ�����ȷ�Ľ��
	}
}
��ð�q
��ð�
???

����ĳ�������Ԥ��Ĳ�һ��.��֪�������ʲô����?


InputStreamReader ���ֽ���ͨ���ַ�������������ʹ��ָ���� charset ��ȡ�ֽڲ��������Ϊ�ַ�����ʹ�õ��ַ�������������ָ������ʽ������������ܽ���ƽ̨Ĭ�ϵ��ַ�����

OutputStreamWriter ���ַ���ͨ���ֽ�����������ʹ��ָ���� charset ��Ҫ����д����ַ�����Ϊ�ֽڡ���ʹ�õ��ַ�������������ָ������ʽ������������ܽ���ƽ̨Ĭ�ϵ��ַ�����

String(byte[] bytes, int offset, int length)
          ����һ���µ� String��������ʹ��ָ�����ַ��������ֽڵ�ָ�������顣

û������ַ���������!!



RandomAccessFile ��

RandomAccessFile��ͬʱʵ����DataInput��DataOutput�ӿڣ��ṩ�˶��ļ������ȡ�Ĺ��ܣ����������������ļ����κ�λ�ö�ȡ��д�����ݡ�
RandomAccessFile���ṩ��һ���ļ�ָ�룬������־Ҫ���ж�д��������һ���ݵ�λ�á�


���ļ����ж�д���ܷ��㡣
���ļ����������ӣ�
//RandomAccessFileTest.java
import java.io.*;
class RandomAccessFileTest
{
	public static void main(String[] args) throws Exception
	{
		Student s1=new Student(200601,"zhangsan",88.5);
		Student s2=new Student(200602,"lisi",95);
		Student s3=new Student(200603,"wangwu",78);
		RandomAccessFile raf=new RandomAccessFile("student.txt","rw");//����һ���ɶ�д���ļ���������RandomAccessFile
		s1.writeStudent(raf);
		s2.writeStudent(raf);
		s3.writeStudent(raf);
		raf.close();
	}
}
class Student
{
	int num;
	String name;
	double score;
	public Student(int num,String name,double score)
	{
		this.num=num;
		this.name=name;
		this.score=score;
	}
	public void writeStudent(RandomAccessFile raf) throws IOException
	{
		raf.writeInt(num);//д��һ��int���͵����ݵ�raf��ص��ļ���
		raf.writeUTF(name);//��UTF-8��ʽд���ַ������ļ��С�
							//�ڿ�ʼд������ǰ�������ֽڼ�¼��ʵ��д������ݵ��ֽ���
		raf.writeDouble(score);
	}
}
E:\zieckey\Lesson9>javac RandomAccessFileTest.java

E:\zieckey\Lesson9>java RandomAccessFileTest

E:\zieckey\Lesson9>

���ʱ����E:\zieckey\Lesson9>Ŀ¼�¶���һ���ļ���student.txt
���������£�
 � zhangsan@V       � lisi@W�      � wangwu@S�
������UltraEdit�鿴���ļ����Աȿ���д�������.

���濴����ζ�ȡ�ļ���Ϣ:
//RandomAccessFileTest.java
import java.io.*;
class RandomAccessFileTest
{
	public static void main(String[] args) throws Exception
	{
		Student s1=new Student(200601,"zhangsan",88.5);
		Student s2=new Student(200602,"lisi",95);
		Student s3=new Student(200603,"wangwu",78);
		RandomAccessFile raf=new RandomAccessFile("student.txt","rw");//����һ���ɶ�д���ļ���������RandomAccessFile
		s1.writeStudent(raf);
		s2.writeStudent(raf);
		s3.writeStudent(raf);//�����ļ�ָ���Ѿ��ƶ����ļ�ĩβ

		Student s=new Student();
		raf.seek(0);//����Ҫ��ȡ����,��Ҫ���ļ�ָ���ƶ����ļ���ͷ
		for(long i=0;i<raf.length();i=raf.getFilePointer())
		{
			s.readStudent(raf);//ÿ��ȡ��д��һ������,�ļ�ָ��������ƶ�
			System.out.println(s.num+":"+s.name+":"+s.score);
		}
		raf.close();
	}
}
class Student
{
	int num;
	String name;
	double score;
	public Student()
	{
	}
	public Student(int num,String name,double score)
	{
		this.num=num;
		this.name=name;
		this.score=score;
	}
	public void writeStudent(RandomAccessFile raf) throws IOException
	{
		raf.writeInt(num);//д��һ��int���͵����ݵ�raf��ص��ļ���
		raf.writeUTF(name);//��UTF-8��ʽд���ַ������ļ��С�
							//�ڿ�ʼд������ǰ�������ֽڼ�¼��ʵ��д������ݵ��ֽ���
		raf.writeDouble(score);
	}
	public void readStudent(RandomAccessFile raf) throws IOException
	{
		num=raf.readInt();
		name=raf.readUTF();
		score=raf.readDouble();
	}
}

E:\zieckey\Lesson9>javac RandomAccessFileTest.java

E:\zieckey\Lesson9>java RandomAccessFileTest
200601:zhangsan:88.5
200602:lisi:95.0
200603:wangwu:78.0

������д�����Ϣ��һ����.



�������л�
������ת��Ϊ�ֽ������������������պ�ԭ����������ֻ��ƽ����������л���
��һ�����󱣴浽���ô洢�豸�ϳ�Ϊ�����ԡ�
һ������Ҫ���ܹ�ʵ�����л�������ʵ��Serializable�ӿڻ�Externalizable�ӿڡ�

��һ���������л�ʱ��ֻ�������ķǾ�̬��Ա���������ܱ����κεĳ�Ա�����;�̬�ĳ�Ա������
���һ������ĳ�Ա������һ��������ô�����������ݳ�ԱҲ�ᱻ���档
���һ�������л��Ķ��������ĳ���������л��Ķ�������ã���ô�������л���������ʧ�ܣ����һ��׳�һ��NotSerializableException�����ǿ��Խ�������ñ��Ϊtransient����ô������Ȼ�������л���
//ObjectSerialTest.java
import java.io.*;
class ObjectSerialTest
{
	public static void main(String[] args) throws Exception
	{
		Employee e1=new Employee("zhangsan",25,3000.50);
		Employee e2=new Employee("lisi",24,3200.40);
		Employee e3=new Employee("wangwu",27,3800.55);

		//д�����л�
		FileOutputStream fos=new FileOutputStream("employee.txt");
		ObjectOutputStream oos=new ObjectOutputStream(fos);
		oos.writeObject(e1);
		oos.writeObject(e2);
		oos.writeObject(e3);
		oos.close();

		//�������л�
		FileInputStream fis=new FileInputStream("employee.txt");
		ObjectInputStream ois=new ObjectInputStream(fis);
		Employee e;
		for(int i=0;i<3;i++)
		{
			e=(Employee)ois.readObject();
			System.out.println(e.name + ":" + e.age +  ":" + e.salary);
		}
		ois.close();
	}
}

class Employee implements Serializable
{
	String name;
	int age;
	double salary;
	public Employee(String name,int age,double salary)
	{
		this.name=name;
		this.age=age;
		this.salary=salary;
	}
}
E:\zieckey\Lesson9>javac ObjectSerialTest.java

E:\zieckey\Lesson9>java ObjectSerialTest
zhangsan:25:3000.5
lisi:24:3200.4
wangwu:27:3800.55

��һ���������л�ʱ��ֻ�������ķǾ�̬��Ա���������ܱ����κεĳ�Ա�����;�̬�ĳ�Ա������
���һ������ĳ�Ա������һ��������ô�����������ݳ�ԱҲ�ᱻ���档
���һ�������л��Ķ��������ĳ���������л��Ķ�������ã���ô�������л���������ʧ�ܣ����һ��׳�һ��NotSerializableException�����ǿ��Խ�������ñ��Ϊtransient����ô������Ȼ�������л���
//ObjectSerialTest.java
import java.io.*;
class ObjectSerialTest
{
	public static void main(String[] args) throws Exception
	{
		Employee e1=new Employee("zhangsan",25,3000.50);
		Employee e2=new Employee("lisi",24,3200.40);
		Employee e3=new Employee("wangwu",27,3800.55);

		FileOutputStream fos=new FileOutputStream("employee.txt");
		ObjectOutputStream oos=new ObjectOutputStream(fos);
		oos.writeObject(e1);
		oos.writeObject(e2);
		oos.writeObject(e3);
		oos.close();

		FileInputStream fis=new FileInputStream("employee.txt");
		ObjectInputStream ois=new ObjectInputStream(fis);
		Employee e;
		for(int i=0;i<3;i++)
		{
			e=(Employee)ois.readObject();
			System.out.println(e.name + ":" + e.age +  ":" + e.salary);
		}
		ois.close();
	}
}

class Employee implements Serializable
{
	String name;
	int age;
	double salary;
	Thread t=new Thread();
	public Employee(String name,int age,double salary)
	{
		this.name=name;
		this.age=age;
		this.salary=salary;
	}
}

E:\zieckey\Lesson9>javac ObjectSerialTest.java

E:\zieckey\Lesson9>java ObjectSerialTest
Exception in thread "main" java.io.NotSerializableException: java.lang.Thread
        at java.io.ObjectOutputStream.writeObject0(ObjectOutputStream.java:1075)

        at java.io.ObjectOutputStream.defaultWriteFields(ObjectOutputStream.java
:1369)
        at java.io.ObjectOutputStream.writeSerialData(ObjectOutputStream.java:13
41)
        at java.io.ObjectOutputStream.writeOrdinaryObject(ObjectOutputStream.jav
a:1284)
        at java.io.ObjectOutputStream.writeObject0(ObjectOutputStream.java:1073)

        at java.io.ObjectOutputStream.writeObject(ObjectOutputStream.java:291)
        at ObjectSerialTest.main(ObjectSerialTest.java:13)

E:\zieckey\Lesson9>

�����Thread t=new Thread();����Ϊtransient�Ͳ�����ִ���
//ObjectSerialTest.java
import java.io.*;
class ObjectSerialTest
{
	public static void main(String[] args) throws Exception
	{
		Employee e1=new Employee("zhangsan",25,3000.50);
		Employee e2=new Employee("lisi",24,3200.40);
		Employee e3=new Employee("wangwu",27,3800.55);

		FileOutputStream fos=new FileOutputStream("employee.txt");
		ObjectOutputStream oos=new ObjectOutputStream(fos);
		oos.writeObject(e1);
		oos.writeObject(e2);
		oos.writeObject(e3);
		oos.close();

		FileInputStream fis=new FileInputStream("employee.txt");
		ObjectInputStream ois=new ObjectInputStream(fis);
		Employee e;
		for(int i=0;i<3;i++)
		{
			e=(Employee)ois.readObject();
			System.out.println(e.name + ":" + e.age +  ":" + e.salary);
		}
		ois.close();
	}
}

class Employee implements Serializable
{
	String name;
	int age;
	double salary;
	transient Thread t=new Thread();
	public Employee(String name,int age,double salary)
	{
		this.name=name;
		this.age=age;
		this.salary=salary;
	}
}
E:\zieckey\Lesson9>javac ObjectSerialTest.java

E:\zieckey\Lesson9>java ObjectSerialTest
zhangsan:25:3000.5
lisi:24:3200.4
wangwu:27:3800.55

������������л�����Ϣ���ж���Ĵ���������ܵȲ���ʱ�����Ǳ���ʵ��������������
 private void writeObject(java.io.ObjectOutputStream out)
     throws IOException
 private void readObject(java.io.ObjectInputStream in)
     throws IOException, ClassNotFoundException;





import java.io.*;
class ObjectSerialTest
{
	public static void main(String[] args) throws Exception
	{
		Employee e1=new Employee("zhangsan",25,3000.50);
		Employee e2=new Employee("lisi",24,3200.40);
		Employee e3=new Employee("wangwu",27,3800.55);

		FileOutputStream fos=new FileOutputStream("employee.txt");
		ObjectOutputStream oos=new ObjectOutputStream(fos);
		oos.writeObject(e1);
		oos.writeObject(e2);
		oos.writeObject(e3);
		oos.close();

		FileInputStream fis=new FileInputStream("employee.txt");
		ObjectInputStream ois=new ObjectInputStream(fis);
		Employee e;
		for(int i=0;i<3;i++)
		{
			e=(Employee)ois.readObject();
			System.out.println(e.name+":"+e.age+":"+e.salary);
		}
		ois.close();
	}
}

class Employee implements Serializable
{
	String name;
	int age;
	double salary;
	transient Thread t=new Thread();
	public Employee(String name,int age,double salary)2007-1-4 14:07
	{
		this.name=name;
		this.age=age;
		this.salary=salary;
	}
	private void writeObject(java.io.ObjectOutputStream oos) throws IOException
	{
		//û��д��нˮֵ
		oos.writeInt(age);
		oos.writeUTF(name);
		System.out.println("Write Object");
	}
	private void readObject(java.io.ObjectInputStream ois) throws IOException
	{
		age=ois.readInt();
		name=ois.readUTF();
		System.out.println("Read Object");
	}

}

E:\zieckey\Lesson9>javac ObjectSerialTest.java

E:\zieckey\Lesson9>java ObjectSerialTest
Write Object
Write Object
Write Object
Read Object
zhangsan:25:0.0
Read Object
lisi:24:0.0
Read Object
wangwu:27:0.0

E:\zieckey\Lesson9>

�����
 private void writeObject(java.io.ObjectOutputStream out)
     throws IOException
 private void readObject(java.io.ObjectInputStream in)
     throws IOException, ClassNotFoundException;
��������̬�����Ǹ�������������ⲿ�����Ա����á�









�ܽ�
InputStream��OutputStream���ֽ��������������
Reader��Writer���ַ��������������
��������(Java I/O������ԭ��)









Lesson10
ͼ�ν��濪��
AWT
AWT(Abstract Window Toolkit)�����󴰿ڹ��߰���SUN��˾�ṩ������ͼ�ν�����(GUI)����⡣������AWT�⴦���û�����Ԫ�صķ����ǰ���ЩԪ�صĴ�������Ϊί�и�ÿ��Ŀ��ƽ̨�ϣ�Windows��Unix��Macintosh�ȣ��ı���GUI���߽��д������磺�������ʹ��AWT��һ��Java�����з���һ����ť����ôʵ����ʹ�õ���һ�����б�����ۺ͸о��İ�ť������������������˵����������д��ͼ�ν���������������κ�ƽ̨�ϣ�������ͼ�ν������Ŀ�ƽ̨���С�

���ֹ�����
�����������λ�úʹ�С���ɲ��ֹ������������ġ������Բ��ֹ��������ض�ʵ������һ�����á���������Ҫ��λһ�����ʱ���������ò��ֹ���������ɡ�������һ������Ĵ�Сʱ��Ҳ����ˡ�
��AWT�У��������ṩ�����ֲ��ֹ�������
	BorderLayout
    FlowLayout
    GridLayout
    CardLayout
    GridBagLayout

//MyFrameTest.java
package frametest;
import java.awt.*;
public class MyFrameTest {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Frame myFrame = new Frame( "zieckey" );
		myFrame.setSize( 640, 480 );//���ô��ڴ�С
		myFrame.setLocation( 100, 100 );//���ô�����ʾ��λ��Ϊ��100��100��
		myFrame.setBackground( Color.blue );//������ɫ

		//������ť,��ȷ����ť������ʾ���ַ���
	    Button btn1=new Button("zieckey North");
	    Button btn2=new Button("zieckey South");
	    Button btn3=new Button("West");
	    Button btn4=new Button("East");
	    Button btn5=new Button("Center");

	    //����ť��ӵ������ϲ�ȷ���ڴ�������ʾ��λ��
	    myFrame.add( btn1,"North" );
	    myFrame.add( btn2,"South" );
	    myFrame.add( btn3,"West" );
	    myFrame.add( btn4,"East" );
	    myFrame.add( btn5,"Center" );

	    myFrame.setVisible( true );//��ʾ����

	}
}

�ڴ����϶����ϡ����������зֱ���ʾ��5����ť��
�м�İ�Ť�����С���ɱ䣬�ϱ��ĸ߶�ʼ�ղ��䣬���ҵĿ��ʼ�ղ���
//MyFrameTest.java
package frametest;
import java.awt.*;
public class MyFrameTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Frame myFrame = new Frame( "zieckey" );
		myFrame.setSize( 640, 480 );//���ô��ڴ�С
		myFrame.setLocation( 100, 100 );//���ô�����ʾ��λ��Ϊ��100��100��
		myFrame.setBackground( Color.blue );//������ɫ

		myFrame.setLayout(new BorderLayout(10,10));//�������ò��ֹ�����

		//������ť,��ȷ����ť������ʾ���ַ���
	    Button btn1=new Button("zieckey North");
	    Button btn2=new Button("zieckey South");
	    Button btn3=new Button("West");
	    Button btn4=new Button("East");
	    Button btn5=new Button("Center");

	    //����ť��ӵ������ϲ�ȷ���ڴ�������ʾ��λ��
	    myFrame.add( btn1,"North" );
	    myFrame.add( btn2,"South" );
	    myFrame.add( btn3,"West" );
	    myFrame.add( btn4,"East" );
	    myFrame.add( btn5,"Center" );
	    myFrame.setVisible( true );//��ʾ����
	}
}


//MyFrameTest.java
package frametest;
import java.awt.*;
public class MyFrameTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Frame myFrame = new Frame( "zieckey" );
		myFrame.setSize( 640, 480 );//���ô��ڴ�С
		myFrame.setLocation( 100, 100 );//���ô�����ʾ��λ��Ϊ��100��100��
		myFrame.setBackground( Color.blue );//������ɫ

		//myFrame.setLayout(new FlowLayout(FlowLayout.LEFT));//�������ò��ֹ�����
		//myFrame.setLayout(new BorderLayout(10,10));
		myFrame.setLayout(new GridLayout(3,2,10,10));

		//������ť,��ȷ����ť������ʾ���ַ���
	    Button btn1=new Button("zieckey North");
	    Button btn2=new Button("zieckey South");
	    Button btn3=new Button("West");
	    Button btn4=new Button("East");
	    Button btn5=new Button("Center");

	    //����ť��ӵ������ϲ�ȷ���ڴ�������ʾ��λ��
	    myFrame.add( btn1,"North" );
	    myFrame.add( btn2,"South" );
	    myFrame.add( btn3,"West" );
	    myFrame.add( btn4,"East" );
	    myFrame.add( btn5,"Center" );
	    myFrame.setVisible( true );//��ʾ����
	}
}


AWT�¼�ģ��
Events(�¼�)������������ʲô�Ķ���
Event source(�¼�Դ)���¼��Ĳ�������
Event handlers(�¼�������)�������¼����󡢽����¼����󲢴����û������ķ�����
//MyFrameTest.java
package frametest;
import java.awt.*;
import java.awt.event.*;
public class MyFrameTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Frame myFrame = new Frame( "zieckey" );
		myFrame.setSize( 640, 480 );//���ô��ڴ�С
		myFrame.setLocation( 100, 100 );//���ô�����ʾ��λ��Ϊ��100��100��
		myFrame.setBackground( Color.blue );//������ɫ

		//myFrame.setLayout(new FlowLayout(FlowLayout.LEFT));//�������ò��ֹ�����
		//myFrame.setLayout(new BorderLayout(10,10));
		myFrame.setLayout(new GridLayout(3,2,10,10));

		//������ť,��ȷ����ť������ʾ���ַ���
	    Button btn1=new Button("zieckey North");
	    Button btn2=new Button("zieckey South");
	    Button btn3=new Button("West");
	    Button btn4=new Button("East");
	    Button btn5=new Button("Center");

	    //����ť��ӵ������ϲ�ȷ���ڴ�������ʾ��λ��
	    myFrame.add( btn1,"North" );
	    myFrame.add( btn2,"South" );
	    myFrame.add( btn3,"West" );
	    myFrame.add( btn4,"East" );
	    myFrame.add( btn5,"Center" );

	    myFrame.addWindowListener( new MyWindowListener() );//���һ���¼�������

	    myFrame.setVisible( true );//��ʾ����
	}
}

class MyWindowListener implements WindowListener
{
  public void windowOpened(WindowEvent e)
  {

  }
  public void windowClosing(WindowEvent e)
  {
    System.exit(0);
  }
  public void windowClosed(WindowEvent e)
  {
  }
  public void windowIconified(WindowEvent e)
  {

  }
  public void windowDeiconified(WindowEvent e)
  {

  }
  public void windowActivated(WindowEvent e)
  {

  }
  public void windowDeactivated(WindowEvent e)
  {

  }
}

����Ϊ��ʵ��һ�������˳����ܣ�Ҫʵ��WindowListener�ӿڣ�
��ĺ��鷳��

���ǿ��Դ� WindowAdapter ����һ���࣬Ȼ��ʵ��������Ҫ�Ĺ��ܾͿ����ˡ�
WindowAdapter ��ʵ��������WindowListener�ӿڵĺ������������ǿ�ʵ�֡�
//MyFrameTest.java
package frametest;
import java.awt.*;
import java.awt.event.*;
public class MyFrameTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Frame myFrame = new Frame( "zieckey" );
		myFrame.setSize( 640, 480 );//���ô��ڴ�С
		myFrame.setLocation( 100, 100 );//���ô�����ʾ��λ��Ϊ��100��100��
		myFrame.setBackground( Color.blue );//������ɫ

		//myFrame.setLayout(new FlowLayout(FlowLayout.LEFT));//�������ò��ֹ�����
		//myFrame.setLayout(new BorderLayout(10,10));
		myFrame.setLayout(new GridLayout(3,2,10,10));

		//������ť,��ȷ����ť������ʾ���ַ���
	    Button btn1=new Button("zieckey North");
	    Button btn2=new Button("zieckey South");
	    Button btn3=new Button("West");
	    Button btn4=new Button("East");
	    Button btn5=new Button("Center");

	    //����ť��ӵ������ϲ�ȷ���ڴ�������ʾ��λ��
	    myFrame.add( btn1,"North" );
	    myFrame.add( btn2,"South" );
	    myFrame.add( btn3,"West" );
	    myFrame.add( btn4,"East" );
	    myFrame.add( btn5,"Center" );

	    //myFrame.addWindowListener( new MyWindowListener() );//���һ���¼�������
	    myFrame.addWindowListener( new HisWindowListener() );//���һ���¼�������

	    myFrame.setVisible( true );//��ʾ����
	}
}

class MyWindowListener implements WindowListener
{
  public void windowOpened(WindowEvent e)
  {

  }
  public void windowClosing(WindowEvent e)
  {
    System.exit(0);
  }
  public void windowClosed(WindowEvent e)
  {
  }
  public void windowIconified(WindowEvent e)
  {

  }
  public void windowDeiconified(WindowEvent e)
  {

  }
  public void windowActivated(WindowEvent e)
  {

  }
  public void windowDeactivated(WindowEvent e)
  {

  }
}
class HisWindowListener extends WindowAdapter
{
  public void windowClosing(WindowEvent e)
  {
    System.exit(0);
  }
}

�������һ���������ڲ��ࣺ

//MyFrameTest.java
package frametest;
import java.awt.*;
import java.awt.event.*;
public class MyFrameTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Frame myFrame = new Frame( "zieckey" );
		myFrame.setSize( 640, 480 );//���ô��ڴ�С
		myFrame.setLocation( 100, 100 );//���ô�����ʾ��λ��Ϊ��100��100��
		myFrame.setBackground( Color.blue );//������ɫ

		//myFrame.setLayout(new FlowLayout(FlowLayout.LEFT));//�������ò��ֹ�����
		//myFrame.setLayout(new BorderLayout(10,10));
		myFrame.setLayout(new GridLayout(3,2,10,10));

		//������ť,��ȷ����ť������ʾ���ַ���
	    Button btn1=new Button("zieckey North");
	    Button btn2=new Button("zieckey South");
	    Button btn3=new Button("West");
	    Button btn4=new Button("East");
	    Button btn5=new Button("Center");

	    //����ť��ӵ������ϲ�ȷ���ڴ�������ʾ��λ��
	    myFrame.add( btn1,"North" );
	    myFrame.add( btn2,"South" );
	    myFrame.add( btn3,"West" );
	    myFrame.add( btn4,"East" );
	    myFrame.add( btn5,"Center" );

	    //myFrame.addWindowListener( new MyWindowListener() );//���һ���¼�������
	    //myFrame.addWindowListener( new HisWindowListener() );//���һ���¼�������
	    myFrame.addWindowListener(new WindowAdapter()
						        {
									  public void windowClosing(WindowEvent e)
									  {
									    System.exit(0);
									  }
						        });

	    myFrame.setVisible( true );//��ʾ����
	}
}

class MyWindowListener implements WindowListener
{
  public void windowOpened(WindowEvent e)
  {

  }
  public void windowClosing(WindowEvent e)
  {
    System.exit(0);
  }
  public void windowClosed(WindowEvent e)
  {
  }
  public void windowIconified(WindowEvent e)
  {

  }
  public void windowDeiconified(WindowEvent e)
  {

  }
  public void windowActivated(WindowEvent e)
  {

  }
  public void windowDeactivated(WindowEvent e)
  {

  }
}
class HisWindowListener extends WindowAdapter
{
  public void windowClosing(WindowEvent e)
  {
    System.exit(0);
  }
}






package layouttest;

import java.awt.*;
import java.awt.event.*;

public class YourFrame extends Frame
{
  private Panel borderPanel;
  private Panel flowPanel;
  private Panel gridPanel;
  private Panel cardPanel;
  public YourFrame(String title)
  {
    super(title);
    setSize(600,400);
    setLocation(100,100);
    setBorderLayoutPanel();
    setFlowLayoutPanel();
    setGridLayoutPanel();
    setCardLayoutPanel();
    setLayout(new GridLayout(2,2));
    add(borderPanel);
    add(flowPanel);
    add(gridPanel);
    add(cardPanel);
    addWindowListener(new WindowAdapter() {
      public void windowClosing(WindowEvent e) {
        System.exit(0);
      }
    });
  }

  public void setBorderLayoutPanel()
  {
    borderPanel=new Panel();
    borderPanel.setLayout(new BorderLayout());
    Button btn1=new Button("North");
    Button btn2=new Button("South");
    Button btn3=new Button("West");
    Button btn4=new Button("East");
    Button btn5=new Button("Center");
    borderPanel.add(btn1,BorderLayout.NORTH);
    borderPanel.add(btn2,BorderLayout.SOUTH);
    borderPanel.add(btn3,BorderLayout.WEST);
    borderPanel.add(btn4,BorderLayout.EAST);
    borderPanel.add(btn5,BorderLayout.CENTER);
  }
  public void setFlowLayoutPanel()
  {
    flowPanel=new Panel();
    Button btn1=new Button("mybole");
    btn1.addActionListener(new ActionListener() {//��Ӧ������¼��������ť�ı�
           public void actionPerformed(ActionEvent e) {
             ((Button)e.getSource()).setLabel("weixin");
           }
         });
    Button btn2=new Button("winsun");
    flowPanel.add(btn1);
    flowPanel.add(btn2);
  }
  public void setGridLayoutPanel()
  {
    gridPanel=new Panel();
    gridPanel.setLayout(new GridLayout(2,2));
    Button btn1=new Button("Button1");
    Button btn2=new Button("Button2");
    Button btn3=new Button("Button3");
    Button btn4=new Button("Button4");
    gridPanel.add(btn1);
    gridPanel.add(btn2);
    gridPanel.add(btn3);
    gridPanel.add(btn4);
  }
  public void setCardLayoutPanel()
  {
    final CardLayout cl=new CardLayout();
    cardPanel=new Panel();
    cardPanel.setLayout(cl);
    Button btn1=new Button("����A");
    Button btn2=new Button("����K");
    ActionListener al=new ActionListener()//ʵ��һ�����Ƶ�Ч��
        {
          public void actionPerformed(ActionEvent e)
          {
            cl.next( cardPanel );
          }
        };

    btn1.addActionListener(al);
    btn2.addActionListener(al);

    cardPanel.add(btn1,"1");
    cardPanel.add(btn2,"2");
  }
  public static void main(String[] args) throws HeadlessException
  {
    YourFrame yf = new YourFrame("http://www.mybole.com.cn");
    yf.setVisible( true );
  }

}



�˵���������
/**
 *
 */
package menutest;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

/**
 * @author apple
 */
public class MenuFrame
{

	/**
	 * @param args
	 */
	@SuppressWarnings ( "deprecation" )
	public static void main ( String[] args )
	{
		final Frame f = new Frame ( "http://zieckey.cublog.cn" );
		f.setSize ( 600 , 400 );
		f.setLocation ( 100 , 100 );

		// ��Ӧ�رհ�ť���ź�
		f.addWindowListener ( new WindowAdapter ( )
			{
				public void windowClosing ( WindowEvent e )
				{
					System.exit ( 0 );
				}
			} );

		MenuBar mb = new MenuBar ( );
		Menu m1 = new Menu ( "File" );
		Menu m2 = new Menu ( "Edit" );
		MenuItem mi1 = new MenuItem ( "New" );
		MenuItem mi2 = new MenuItem ( "Open" );
		MenuItem mi3 = new MenuItem ( "Save" );
		MenuItem mi4 = new MenuItem ( "Exit" );
		MenuItem mi5 = new MenuItem ( "Copy" );
		MenuItem mi6 = new MenuItem ( "Paste" );

		// ��Ӧ�˳��˵����¼�
		mi4.addActionListener ( new ActionListener ( )
			{
				public void actionPerformed ( ActionEvent arg0 )
				{
					System.exit ( 0 );
				}
			} );

		// ���˵�����ӵ��˵���
		m1.add ( mi1 );
		m1.add ( mi2 );
		m1.add ( mi3 );
		m1.add ( mi4 );
		m2.add ( mi5 );
		m2.add ( mi6 );

		// �������˵���ӵ��˵�����
		mb.add ( m1 );
		mb.add ( m2 );

		// ���˵�����ӵ���������
		f.setMenuBar ( mb );

		f.setVisible ( true );
	}
}

������Ҫ���ʾֲ�������Ҫ�������������Ϊfinal

��Ӧ�˵�����ļ��Ի�����ʾ�ı����༭����
/**
 *
 */
package menutest;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.FileInputStream;

/**
 * @author apple
 */
public class MenuFrame
{

	/**
	 * @param args
	 */
	@SuppressWarnings ( "deprecation" )
	public static void main ( String[] args )
	{
		final Frame f = new Frame ( "http://zieckey.cublog.cn" );
		f.setSize ( 600 , 400 );
		f.setLocation ( 100 , 100 );

		final TextArea ta = new TextArea();//����һ����������
		f.add ( ta );

		// ��Ӧ�رհ�ť���ź�
		f.addWindowListener ( new WindowAdapter ( )
			{
				public void windowClosing ( WindowEvent e )
				{
					System.exit ( 0 );
				}
			} );

		MenuBar mb = new MenuBar ( );
		Menu m1 = new Menu ( "File" );
		Menu m2 = new Menu ( "Edit" );
		MenuItem mi1 = new MenuItem ( "New" );
		MenuItem mi2 = new MenuItem ( "Open" );
		MenuItem mi3 = new MenuItem ( "Save" );
		MenuItem mi4 = new MenuItem ( "Exit" );
		MenuItem mi5 = new MenuItem ( "Copy" );
		MenuItem mi6 = new MenuItem ( "Paste" );

		// ��ӦOpen�˳��˵����¼�
		mi2.addActionListener ( new ActionListener ( )
			{
				public void actionPerformed ( ActionEvent arg0 )
				{
					//����һ�����ļ��Ի���
					FileDialog fd = new FileDialog ( f,
							"zieckey Open File Dialog", FileDialog.LOAD );
					fd.setVisible ( true );//������ʾ����

					//�õ��û�ѡ����ļ���ȫ��
					String fileName = fd.getDirectory ( ) +  fd.getFile ( ) ;
					if ( fileName != null )
					{
						try
						{
							FileInputStream fis=new FileInputStream(fileName);//����һ���ļ�������
							byte[] buf=new byte[10*1024];
							int len=fis.read(buf);//��ȡ���ݵ�buf��
							ta.append ( new String(buf,0,len) );//��buf��������ӵ��ı���������
							fis.close ( );
						}
						catch ( Exception e )
						{
							e.printStackTrace ( );
						}
					} else
					{

					}
				}

			} );

		// ��ӦExit�˳��˵����¼�
		mi4.addActionListener ( new ActionListener ( )
			{
				public void actionPerformed ( ActionEvent arg0 )
				{
					System.exit ( 0 );
				}
			} );

		// ���˵�����ӵ��˵���
		m1.add ( mi1 );
		m1.add ( mi2 );
		m1.add ( mi3 );
		m1.add ( mi4 );
		m2.add ( mi5 );
		m2.add ( mi6 );

		// �������˵���ӵ��˵�����
		mb.add ( m1 );
		mb.add ( m2 );

		// ���˵�����ӵ���������
		f.setMenuBar ( mb );

		f.setVisible ( true );
	}
}


Lesson11
Applet

Applet�ֳ�ΪJavaСӦ�ó������ܹ�Ƕ�뵽һ��HTMLҳ���У����ҿ�ͨ��Web��������غ�ִ�е�һ��Java�� ��
Applet����Ҫmain()��������Web���������Ƕ��Java���������ִ�С�

��Ϊapplet�Ǵ�Զ�˷����������ز����ڱ���ִ�У����԰�ȫ�Ծ��Եø�����Ҫ��
ͨ������applet��ɳ��(applet�����л���)�����У���֤�˶Ա���ϵͳ����applet�ǰ�ȫ�ġ�
applet��ɳ��������ʱ��
�Ų��������κα��ؿ�ִ�г���
�Ƴ��˴�����ص�applet�ķ������⣬applet���ܺ�������������ͨ�š�
�ǲ��ܶԱ����ļ�ϵͳ���ж�д��

Applet����������
init()�������������applet�����г�ʼ����ʱ����ø÷�����
start()����init()����֮����á����û�������ҳ��ת������applet��ҳ��ʱ���÷���Ҳ�����á�
stop()�����û��뿪����applet��ҳ��ʱ�����á�
destroy()����applet���ٱ�ʹ�ã���������˳���ʱ�򣬸÷��������á�

paint()����
Applet��������ͼ�η�ʽ�ģ�����Ӧ����ͼ�λ����л������ǵ���ʾ���ݡ�
���ǿ���ͨ������һ��paint()������Applet��panel�ϻ�ͼ��ֻҪApplet����ʾ��Ҫˢ�£�paint()�����ͻᱻ������������á����磬��Applet����ʾ�ߴ緢���仯��ʱ�򣬻���������ڱ���С����Ҫ����ͼ�귽ʽ��ʾʱ�����ֵ��þͻᷢ����
����Ӧ�ñ�д�Լ���paint()��������ʹ�����κ�ʱ�򱻵��ã����������ع����������ĵ������첽�����ģ�����Applet�����л��������ǳ��������� ��
paint()��������һ������������java.awt.Graphics���һ��ʵ��������������ǽ�����Applet��panel��ͼ�������ģ����ǿ��������ͼ����������Applet�л�ͼ��д���ı���


//AppletTest.java
package applettest;

import java.applet.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.net.URL;
public class AppletTest extends Applet
{
	/**
	 *
	 */
	private static final long	serialVersionUID	= 1L;
	String strFont;//����
	public void init()
	{
		strFont=getParameter("font");//����ҳ�л�ȡ�����������Ϣ
		System.out.println("init");
	}
	public void start()
	{
		System.out.println("start");
	}
	public void stop()
	{
		System.out.println("stop");
	}
	public void destroy()
	{
		System.out.println("destroy");
	}
	public void paint(Graphics g)
	{
		//Font f=new Font("����_GB2312",Font.BOLD,30);
		Font f=new Font(strFont,Font.BOLD,30);
		g.setFont(f);//��������
		g.setColor(Color.blue);//����������ɫ
		g.drawString("zieckeyѧJava",0,30);//����ҳ����ʾ��Ϣ
	}
}

/*�����ǽ���html��ҳ���в����õ�
<applet code="TestApplet.class" width=600 height=400>
<param name="font" value="����_GB2312">
</applet>
*/




//AppletTest.java
package applettest;
import java.applet.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class AppletTest extends Applet
{
	/**
	 *
	 */
	private static final long	serialVersionUID	= 1L;
	String strFont;//����
	int xOrigin,yOrigin;
	public void init()
	{
		//��Applet��ʵ����껭�߹���
		addMouseListener(new MouseAdapter()
		{
			public void mousePressed(MouseEvent e)
			{
				xOrigin=e.getX();
				yOrigin=e.getY();
			}
			public void mouseReleased(MouseEvent e)
			{
				Graphics g=getGraphics();
				g.setColor(Color.red);
				g.drawLine(xOrigin,yOrigin,e.getX(),e.getY());
			}
		});
		strFont=getParameter("font");//����ҳ�л�ȡ�����������Ϣ
		System.out.println("init");
	}
	public void start()
	{
		System.out.println("start");
	}
	public void stop()
	{
		System.out.println("stop");
	}
	public void destroy()
	{
		System.out.println("destroy");
	}
	public void paint(Graphics g)
	{
		//Font f=new Font("����_GB2312",Font.BOLD,30);
		Font f=new Font(strFont,Font.BOLD,30);
		g.setFont(f);//��������
		g.setColor(Color.blue);//����������ɫ
		g.drawString("zieckeyѧJava",0,30);//����ҳ����ʾ��Ϣ
	}
}

/*�����ǽ���html��ҳ���в����õ�
<applet code="TestApplet.class" width=600 height=400>
<param name="font" value="����_GB2312">
</applet>
*/


//AppletTest.java
package applettest;
import java.applet.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.net.URL;

public class AppletTest extends Applet
{
	/**
	 *
	 */
	private static final long	serialVersionUID	= 1L;
	String strFont;//����
	int xOrigin,yOrigin;
	public void init()
	{
		//���һ����ť
		Button btn=new Button("����");
		add(btn);
		btn.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				try
				{
					getAppletContext().showDocument(
						new URL("http://zieckey.cublog.cn"),"_blank");
				}
				catch(Exception ex)
				{
					ex.printStackTrace();
				}
			}
		});

		//��Applet��ʵ����껭�߹���
		addMouseListener(new MouseAdapter()
		{
			public void mousePressed(MouseEvent e)
			{
				xOrigin=e.getX();
				yOrigin=e.getY();
			}
			public void mouseReleased(MouseEvent e)
			{
				Graphics g=getGraphics();
				g.setColor(Color.red);
				g.drawLine(xOrigin,yOrigin,e.getX(),e.getY());
			}
		});
		strFont=getParameter("font");//����ҳ�л�ȡ�����������Ϣ
		System.out.println("init");
	}
	public void start()
	{
		System.out.println("start");
	}
	public void stop()
	{
		System.out.println("stop");
	}
	public void destroy()
	{
		System.out.println("destroy");
	}
	public void paint(Graphics g)
	{
		//Font f=new Font("����_GB2312",Font.BOLD,30);
		Font f=new Font(strFont,Font.BOLD,30);
		g.setFont(f);//��������
		g.setColor(Color.blue);//����������ɫ
		g.drawString("zieckeyѧJava",0,30);//����ҳ����ʾ��Ϣ
	}
}
����ע��Ҫ��������������ٻ��棬��Java����̨����x���Ϳ�����
��������û���������е��������ְ�ť��









Lesson12
������
����TCP��socket���
�����������д��
�ٵ���ServerSocket(int port)����һ�����������׽��֣����󶨵�ָ���˿��ϣ�
�ڵ���accept()������������������ͻ����������ӣ���������ӣ�����ͨ���׽��֡�
�۵���Socket���getOutputStream()��getInputStream��ȡ�����������������ʼ�������ݵķ��ͺͽ��ա�
�����ر�ͨ���׽��֡�
�ͻ��˳����д��
�ٵ���Socket()����һ�����׽��֣������ӵ��������ˣ� 
�ڵ���Socket���getOutputStream()��getInputStream��ȡ�����������������ʼ�������ݵķ��ͺͽ��ա�
�����ر�ͨ���׽��֡�

��Eclipse����Ӳ�������:
��run ���ϵ������ť�ٵ�run��Ȼ���new ��Ҫ���е��࣬mainѡ�ú󣬵�main���ϵ�Arguments��
Ȼ����Program arguments��д����Ҫ���Ĳ����������С�

������һ����򵥵�TCP��socketӦ�ó���:

// TestTCPConnection.java
package tcptest;

import java.net.*;
import java.io.*;

public class TestTCPConnection
{

	private static final int	PORT	= 6000;

	/**
	 * @param args
	 */
	public static void main ( String[] args )
	{
		if ( args.length > 0 ) // ����в����������������������
			server ( );
		else
			// ���������ͻ��˽���
			client ( );
	}


	public static void server ()
	{
		System.out.println ( "This is server" );
		try
		{
			ServerSocket ss = new ServerSocket ( PORT );
			Socket s = ss.accept ( );
			OutputStream os = s.getOutputStream ( );
			InputStream is = s.getInputStream ( );
			os.write ( "Hello,welcome you!".getBytes ( ) );
			byte[] buf = new byte[100];
			int len = is.read ( buf );
			System.out.println ( new String ( buf, 0, len ) );
			os.close ( );
			is.close ( );
			s.close ( );
			ss.close ( );
		} catch ( Exception ex )
		{
			ex.printStackTrace ( );
		}
	}

	public static void client ()
	{
		System.out.println ( "This is client" );
		try
		{
			Socket s = new Socket ( InetAddress.getByName ( null ), PORT );
			OutputStream os = s.getOutputStream ( );
			InputStream is = s.getInputStream ( );
			byte[] buf = new byte[100];
			int len = is.read ( buf );
			System.out.println ( new String ( buf, 0, len ) );
			os.write ( "Hello,this is wangwu".getBytes ( ) );
			os.close ( );
			is.close ( );
			s.close ( );
		} catch ( Exception ex )
		{
			ex.printStackTrace ( );
		}
	}
}


�÷������������߳�Ϊ�ͻ��˽�������:
// TestTCPConnection.java
package tcptest;

import java.net.*;
import java.io.*;

/**
 * һ���򵥵Ķ��̷߳���������
 *
 * @author apple
 */
public class TestTCPConnection extends Thread
{
	private static final int	PORT	= 6000;
	private Socket				s;

	public TestTCPConnection ( Socket s )
	{
		this.s = s;
	}

	@Override
	public void run ()
	{
		try
		{
			OutputStream os = s.getOutputStream ( );
			InputStream is = s.getInputStream ( );
			os.write ( "Hello,welcome you!".getBytes ( ) );
			byte[] buf = new byte[100];
			int len = is.read ( buf );
			System.out.println ( new String ( buf, 0, len ) );
			os.close ( );
			is.close ( );
			s.close ( );
		} catch ( Exception e )
		{
			e.printStackTrace ( );
		}

	}

	/**
	 * @param args
	 */
	public static void main ( String[] args )
	{
		if ( args.length > 0 ) // ����в����������������������
			server ( );
		else
			// ���������ͻ��˽���
			client ( );
	}

	public static void server ()
	{
		System.out.println ( "This is server" );
		try
		{
			ServerSocket ss = new ServerSocket ( PORT );
			int count = 0;
			while ( true )
			{
				// ����һ��Socket�ȴ��ͻ�������
				Socket s = ss.accept ( );
				System.out.println ( "This is the " + count++
									+ "st client connetion!" );
				new TestTCPConnection ( s ).start ( );// ����һ���߳�Ϊ����ͻ��˷���
			}
		} catch ( Exception ex )
		{
			ex.printStackTrace ( );
		}
	}

	public static void client ()
	{
		System.out.println ( "This is client" );
		try
		{
			// ����һ��Socket
			Socket s = new Socket ( InetAddress.getByName ( null ), PORT );
			OutputStream os = s.getOutputStream ( );// �����
			InputStream is = s.getInputStream ( );// ������
			byte[] buf = new byte[100];
			int len = is.read ( buf );// ���������ж�ȡ���ݵ�buf
			System.out.println ( new String ( buf, 0, len ) );
			// ���������д������
			os.write ( "Hello,this is zhangsan".getBytes ( ) );
			os.close ( );
			is.close ( );
			s.close ( );
		} catch ( Exception ex )
		{
			ex.printStackTrace ( );
		}
	}
}



���ݱ�UDP���:

// TestTCPConnection.java
package tcptest;

import java.net.*;
/**
 * һ���򵥵Ķ��̷߳���������
 *
 * @author apple
 */
public class TestUDPConnection
{
	private static final int	PORT	= 6000;

	public static void main ( String[] args )
	{
		if ( args.length > 0 )
			recv ( );
		else
			send ( );
	}

	public static void recv ()//���շ����ݷ�����
	{
		try
		{
			DatagramSocket ds = new DatagramSocket ( PORT );
			byte[] buf = new byte[100];
			DatagramPacket dp = new DatagramPacket ( buf, 100 );
			ds.receive ( dp );//�ȴ����ݵĵ���
			System.out.println ( new String ( buf, 0, dp.getLength ( ) ) );
			//���յ���Ϣ��ظ�һ�����ݸ����ͷ�
			String str = "Welcome you!";
			DatagramPacket dpSend = new DatagramPacket ( str.getBytes ( ), str
								.length ( ), dp.getAddress ( ), dp.getPort ( ) );
			ds.send ( dpSend );
			ds.close ( );
		} catch ( Exception ex )
		{
			ex.printStackTrace ( );
		}
	}

	public static void send ()
	{
		try
		{
			DatagramSocket ds = new DatagramSocket ( );
			String str = "Hello,this is zhangsan";
			DatagramPacket dp = new DatagramPacket ( str.getBytes ( ), str
								.length ( ), InetAddress
								.getByName ( "localhost" ), 6000 );
			ds.send ( dp );//�������ݵ����շ�
			byte[] buf = new byte[100];
			DatagramPacket dpRecv = new DatagramPacket ( buf, 100 );
			ds.receive ( dpRecv );//�ȴ����շ��Ļ�Ӧ��Ϣ
			System.out.println ( new String ( buf, 0, dpRecv.getLength ( ) ) );
			ds.close ( );
		} catch ( Exception ex )
		{
			ex.printStackTrace ( );
		}
	}
}



д���򵥵��������س���:
package down;

import javax.swing.*;
import java.awt.event.*;
import java.io.*;
import java.net.*;

public class Download
{
	public static void main ( String[] args )
	{
		// ����һ������
		JFrame jf = new JFrame ( "���س���" );
		jf.setSize ( 600, 400 );
		jf.setLocation ( 100, 100 );
		JPanel p = new JPanel ( );// ����һ�����
		JLabel l = new JLabel ( "Please input URL:" );
		final JTextField tf = new JTextField ( 30 );
		p.add ( l );
		p.add ( tf );
		jf.getContentPane ( ).add ( p, "North" );// �������ӵ�������
		final JTextArea ta = new JTextArea ( );
		jf.getContentPane ( ).add ( ta, "Center" );
		JButton btn = new JButton ( "Download" );
		jf.getContentPane ( ).add ( btn, "South" );
		btn.addActionListener ( new ActionListener ( )// ��Ӱ�ť��Ӧ��Ϣ
					{
						public void actionPerformed ( ActionEvent e )
						{
							String str = tf.getText ( );
							try
							{
								URL url = new URL ( str );// ��ȡ���û������URL
								// �Ը�URL����
								URLConnection urlConn = url.openConnection ( );
								// ��ȡ��ƽ̨�޹ص��зָ���
								String line = System
										.getProperty ( "line.separator" );
								// �õ������ӵ�����IP
								ta.append ( "Host: " + url.getHost ( ) );
								ta.append ( line );
								// �˿�
								ta.append ( "Port: " + url.getDefaultPort ( ) );
								ta.append ( line );
								//��ҳ����
								ta.append ( "ContentType: "
										+ urlConn.getContentType ( ) );
								ta.append ( line );
								//��ҳ���ݳ���
								ta.append ( "ContentLength: "
										+ urlConn.getContentLength ( ) );
								//����һ��������
								InputStream is = urlConn.getInputStream ( );
								//����һ�������,д�����ݵ��ļ���
								FileOutputStream fos = new FileOutputStream (
										"1.html" );

								int data;
								//���ֽ�����ȡ����
								while ( ( data = is.read ( ) ) != -1 )
								{
									fos.write ( data );
								}
								is.close ( );
								fos.close ( );
							} catch ( Exception ex )
							{
								ex.printStackTrace ( );
							}

						}
					} );
		jf.addWindowListener ( new WindowAdapter ( )
			{
				public void windowClosing ( WindowEvent e )
				{
					System.exit ( 0 );
				}
			} );
		jf.setVisible ( true );
	}
}

























































































































































Java��ʹ��MySQL�Ӱ�װ�����õ�ʵ�ʳ���������

����������Java���������Ѿ�����ˡ�

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



3. �½� Java ���� QueryJDBC.java
/**
 *	�ó�����������JDBC��MySQL����
 */
package test;

import java.sql.*;

public class QueryJDBC
{
	static
	{
		try
		{
			//������odbc��ͬ
			Class.forName ( "org.gjt.mm.mysql.Driver" );
			System.out.println ( "success loading mysql Driver...." );
		} catch ( Exception e )
		{
			System.out.println ( "Error loading mysql Driver....." );
			e.printStackTrace ( );
		}
	}

	/**
	 * @param args
	 */
	public static void main ( String agrs[] )
	{
		try
		{
			//���Ӳ�����Access��ͬ������LearnJava�����潨�������ݿ���
			String url = "jdbc:mysql://localhost/LearnJava";
			//�������ӣ�rootΪ��¼���ݿ���û�����123456Ϊ����
			Connection con = DriverManager.getConnection ( url, "root", "123456'" );
			//��������SQL�����Statement����
			Statement stmt = con.createStatement ( );
			//���ز�ѯ���
			ResultSet rs = stmt.executeQuery ( "select * from userinfo" );

			ResultSetMetaData md = rs.getMetaData ( );

			int col = md.getColumnCount ( );
			for ( int i = 1; i <= col; i++ )
			{
				System.out.println ( md.getColumnName ( i ) + "\t" );
			}
			while ( rs.next ( ) )
			{
				String strData = "";
				for ( int i = 1; i <= col; i++ )
				{
					strData = strData + rs.getString ( i ) + "\t";
				}
				System.out.println ( strData );
			}
			//�Ͽ�Connection����
			rs.close();
			stmt.close();
			con.close ( );
		} catch ( SQLException e )
		{
			e.printStackTrace ( );
		}
	}
}

E:\JavaLesson\MySQLTest\test>javac QueryJDBC.java -d .

E:\JavaLesson\MySQLTest\test>java test.QueryJDBC
success loading mysql Driver....
UserName
UserPwd
zieckey 123456

����Ҫ�ر�����һ�£������Eclipse�½������̵ģ�
�ó���ܿ������г����쳣����ʾ�Ҳ���org.gjt.mm.mysql.Driver��
�������ͨ�� Project->Properties->Java Build Path->Libraries ѡ�� Add Extenal JARs��
Ȼ��Ϳ���ѡ�������jar����mysql-connector-java-5.0.3-bin.jar
��������Ϳ������������ˡ�

�����Netbeans�¿����Ļ���ҲҪ���JAR����IDE�������У�
To use the Library Manager:
From the main menu, choose Tools > Library Manager.
In the Library Manager dialog box, click New Library.
In the New Library dialog box, name your library. Click OK.
Click Add JAR/Folder and browse to add the JAR file(s) needed for your classpath, source, or Javadoc.
In order for code completion to work properly in the IDE, you must either attach a complete set of source files as a folder or add the available source files as a Zip archive.

2007/1/18
����ʵ�����л�������ʾû�ж���serialVersionUID�� ����:Ĭ����Ŀ
�P�Eclipse����ʾ The serializable class XXXXXX does not declare a static final serialVersionUID field of type long

�����Զ��޸���Eclipse���Զ����ϣ�private static final long serialVersionUID = 1L;
������ʵ������⵹Ҳ��Ӱ���������У������ҿ���Problems�����о���Ͳ������ͬʱҲ˵������д�Ĵ��뻹�ǲ��淶�����£������л������������ô���£������ԭ�򻹾��Ǻ����л��е����serialVersionUID�йء�
����serialVersionUID ����������Ĳ�ͬ�汾��ļ�����.������޸��˴���, Ҫ�޸Ĵ�ֵ. ������ǰ���ϰ汾�������л�����ָ�ʱ�����.
������������JDK��binĿ¼�µ�serialver.exe���߲������serialVersionUID
��������Test.class,ִ����� serialver Test
����Ϊ���ڷ����л�ʱ��ȷ����汾�ļ����ԣ������ÿ��Ҫ���л������м���private static final long serialVersionUID������ԣ�������ֵ�Լ����塣��������ʹĳ��������֮��Ӧ�Ķ����Ѿ����л���ȥ�������޸ģ��ö�����Ȼ���Ա���ȷ�����л��������������ʾ��������ԣ��������ֵ����JVM������������Ϣ���㣬���޸ĺ����ļ��������޸�ǰ����ļ�����������ͬ���Ӷ���ɶ���ķ����л���Ϊ��汾�����ݶ�ʧ�ܡ�
��������ʾ�����������ֵ����һ�������ǣ������ڳ����ڲ�ͬ��JVM֮�����ֲ����Ϊ��ͬ�ı�����ʵ�ֵĸ�����ֵ�ļ�����Կ��ܲ�ͬ���Ӷ������Ȼ��û�иı䣬������ΪJVM��ͬ����Ȼ��������汾�����ݶ��޷���ȷ�����л���������֡�
������Ϊ������ϵͳ��̫�ᾭ����Ҫ���л��࣬����Ϊ��ȥ����Щ���棬���������ã�
Window��Preferences��Java����ͼ��ʾ����serializable class without serialVersionUID��������warning��ΪIgnore��Ȼ��Eclipse�����±��������Щ������ϢҲ�ͻ���ʧ�ˡ�
����С�᣺������ǿ���������Ҫ���л������ʱ��������û��ǻ�ԭΪԭ�������á��������Ա�֤ϵͳ�����ܺͽ�׳



����eclipseд��ͼƬ�ĳ���,�������治���Լ�����һ��res���ļ���ô,�����Ұ�ͼƬ��������Ͷ�ȡ����,Ҫ����\verified\classes,����,�ѵ�һ��Ҫ��class�ļ�����һ��ô??!!


Netbeansʹ��С����

netbean ��װ��ɺ����༭���ڵ�Ĭ�����忴�Ų��Ǻ����������ͨ��Tools->options->Editing->Editor Setting->Java(jsp,xml...) Editor->Fonts and Colors�޸ģ������޸�ΪDialog Input,Size=11�ͺÿ�����
netbean����༭��֧����д��������sout���Զ�ת����System.out.println("")��Ԥ����Ŀ�ݼ�����д���������Help->Keyboard Shortcuts Card�鿴��Ҳ����ͨ��Tools->options->Editing->Editor Setting->Java(jsp,xml...) Editor->Abbreviations���ӻ��޸�
netbean��java�����Զ������ʾ�����������ַ�Ĭ���Ǵ�Сд���еģ��ù�Jbuilder�Ŀ��ܺܲ����������ͨ��Tools->options->Editing->Editor Setting->Java Editor->Expert->Case Sensitive Code Completion�޸ģ��ѹ�ѡȥ���Ϳ��Բ����ִ�Сд��
netbeans�����JSPͷ����pageָ���Զ�ʶ��JSP���룬�������JSPϣ��ʹ��UTF-8����ֻ����JSP�ļ�һ��ʼ����<%@ page contentType="text/html;charset=UTF-8"%>��<%@page pageEncoding="UTF-8"%>��JSP1.2������
java�ļ�����Ĭ��ʹ��ϵͳ���룬����ͨ��java�ļ�properties���Text->Encoding�����޸ģ�Ҳ����ͨ��Tools->options->Editing->Java Sources->Expert->Default Encodingͳһ�޸�
More...

netbean�����Զ���ɵĿ�ݼ�Ĭ�ϵ��ǣ�Ctrl+\



JNI�ؼ���:
access native methods

��J2ME�����У���Զ���޷�ֱ�ӵ��ñ��ؿ⺯������ΪJava�ı��ص���ͨ�������ַ�ʽ��  
   
  һ��JNI����J2ME��ȷ�ز�֧��JNI��  
   
 ����KNI����ʹ��KNI�Ļ�����ı��غ������Ƿ��ڶ�̬���ӿ������Ҫ�ൽ��������ڲ�������һ���������û�����޸�������İɣ����ο��������õ���������п��ܲ���֧��KNI��KNI���ֻ��KVMר�õģ�������һЩ�����Ҳ�ã�������ȫ����  
   
  ������KNI����Ȥ�Ļ�����ӭ�ι�һ���ҵ�blog��Ҳ����һ�������  
  http://blog.csdn.net/fyzhao/archive/2006/08/28/1134113.aspx
  
  
J2ME/CDC applications can access native methods through the JNI (Java Native Interface) framework. The CLDC does not support JNI. For security reasons, CLDC applications are not allowed to access native methods. For CLDC, device vendors must build any native features into the runtime [3].  














http://community.polarion.com/projects/subversive/download/eclipse/2.0/builds/

http://www.pin5i.com/showtopic-23178.html

�����˺þã����ڸ㶨subversive��svn connector�İ�װ�ˣ����̺�ʹ�࣬��Ϊeclipse�����߰�װʵ����̫����......
    
    ����ҵ��ܽ���ǲ�Ҫֱ�Ӵ����ϰ�װ��̫��̫��������Ѫ�����ģ����Ѿ����������......
    
    ��ȷ�ķ������ȴӹٷ���վ�����ذ�װ����Ȼ������eclipse��software update���߰�װ�������ٶȾͺܿ졣�ҵ�1m��adsl�����ֱ�����ϰ�װ�����1k�����ٶȣ�ֱ��http���ذ�װ���������50-100k֮�䣬��𹻴�ɣ�
    
    ���岽�����£�

1. ����subversive

    
    ���������ַ http://www.eclipse.org/subversive/downloads.php�� �ҵ�Latest Release - Recommended �� Subversive plug-in - [required]���ҵ�
    
        Archived Update Site: Subversive-incubation-0.7.7.I20090224-1900.zip
    
    ���������ѱ�����߸��µ�ַ Update Site: http://download.eclipse.org/tech ... ve/0.7/update-site/��
    
    �����ӽ����Subversive-incubation-0.7.7.I20090224-1900.zip�ļ���������������ĵ�ַ�ǣ�
    
    http://www.eclipse.org/downloads ... .I20090224-1900.zip
    
    ��С�����17M��
    
2. ����svn connector

    �ڸղ�����������·�����svn connector��˵�����������ص�ַ
    
    http://www.polarion.com/products ... ?src=eclipseproject
    
    �������ҵ�Subversive Connector Archives��������ָ��װ�����������������������ַ�ǣ�
    
    http://www.polarion.org/projects ... .I20090213-1500.zip
    
    �����18M��
    
    ����������������35m���Ҳ�֪��1k���ٶ�Ҫ���ض��......
    
3. ��װsubversive

    eclispe -> software updates -> available software -> Manage Sites
    ����ȡ������site������eclipse����Ҫȥ����һЩ�����������������ص��ٶȴ����100�ֽ�ÿ�룬��ϸ�뿴�ҵ���һ�����ӡ�
    Ȼ��add -> archive��ָ��ղ����ص�Subversive-incubation-0.7.7.I20090224-1900.zip�ļ���С��add֮��software updates���߻��Զ���ѡ����eclipse��վ�㣬ǧ���ס�ٴ�ȡ�����ǣ�ֻ����subversiveһ����֮���һ·˳����װ����ɺ��Ҫ��������
    
4. ��װsvn connector

    ������ķ�ʽһ�¡�
    ע����ѡ��װ����ʱ��ȫѡ���ҿ�ʼֻѡ��һ��svn connector�����������, subversive���������޷�ѡ��connector�������ڶ��ΰ�װʱȫѡ�������ˡ�
    
5. ����svn connector
    eclipse -> windows -> preferences -> team -> svn
    ��SVN Connector��Ȼ��ѡ��һ��Ҫ�õ�connector����ѡ�����SVN Kit(SVN/1.5.5 r5428)��apply.
    
    ����������������İ�װ���Ҳ��Թ�������������subversion��������














Java NIO(New IO) ������ JDK 1.4 ������������ԡ�JDK 1.4 ����һ��Ҫ����������ʽ���Ӧ�þ����õ����� NIO �Ϳ���ʹ�������ˣ������Ե�ھ��� IO ��ϵ��Ȼ���á����� JDK1.5 ��ͷ��ͺ�ע���ˣ������ڸ���ԭ����޷�����ȥʵ�����ͺ�ע��һ�㣬NIO ����ʱ��Ҳֻ�������ǲ��ż���ѡ�����/��Ҷ��ݺ��

����� Old IO��NIO ��ĳЩ������ȷ�������֮������������������һ������ NIO �и���������ʶ��

NIO ����� API���� java.nio �У�������������ľ��Ǹ��� Channel �� Buffer����ص�Ӧ�����ڴ���ͨ���ͻ��������첽(������)�� IO���ļ����������ַ����Ĵ����ϡ�

Channel ����ͨ������ FileInputStream��FileOutputStream��RandomAccessFile��DatagramSocket�� ServerSocket �� Socket �� getChannel() ������á�Channel �е���� I/O �������� I/O �Ķ�д��������������ֱ�ӽ��У��� NIO �����ڸ��� Buffer �϶�д���ݡ�

����ʹ���˶��е�ͨ���ͻ���������Ⱦ��е� IO ����������ֽ���(�� IO)��NIO ��ʹ�õķ�ʽ�ǿ� I/O�������ڴ�����ݴ���ʱ�� I/O ���� I/O Ч��Ҫ�ߡ�NIO ��һ���̶����൱���ñ��ش����������� I/O ������

�첽 I/O ʹ�����ڽ������紫��ʱ��������ԭ������ read()/write() �������߳����ȴ����ݵĵ�����ֱ��д�����ݡ�NIO �ķ�ʽ��ע�������������ͨ���ϵ��¼�����һ���߳��Ͼ��������Ĵ��� Socket ͨ�š������ I/O ������������ѯ��������������߳���������������ӡ�

���磬���� NIO ������У�����Ӧ�ÿ�� Apache MINA��Memcached �ͻ��� XMemcached��Socket Ӧ����� xSocket������ Tomcat 6 Ҳ֧��ʹ�� NIO �� connector �ˡ�

�ļ���ʹ�� Java ����Ҳ���Զ������ļ����ļ��Ĳ��ֽ��ж�ռ(����)����Ķ���д����ֹ�˲�ͬ�Ľ��̶�ͬһ���ļ��ĸ��š������ڲ�ͬ����ϵͳ�µ���Ϊ���ܻ���ϸ΢�Ĳ��졣�ļ���(Lock)����ͨ�� Channel �� lock() �� tryLock() ��ã�Channel �� release() ������ر�ͨ��ʱ���ͷ�������

���⣬NIO ���Ը��õ�ʹ�ÿ����ַ�����

�� NIO ����һ������Ҫ�� Buffer �����ڴ�ӳ���ļ�--ͨ������ FileChannel ��� map() �����ɻ�� MappedByteBuffer�����ڴ�ӳ���ļ��� Windows �µ��ڴ�ӳ���������ԣ��ֲ���Ȼ��Windows �µ��ڴ�ӳ���ļ��������ڲ�ͬ�Ľ��̼乲�����ݣ�Java ���������Ҫϸ���¡�

���ϱ����Ƿ��������ʶ�߻����ò�֪���ƣ�Ҳ����ζ�ɽ⣬ԭ�����Ƕ� Java NIO �Ĵ������⣬���Ҷ�����

�� IBM DeveloperWorks ����һ�� Java NIO ���Ž̳̣�https://www6.software.ibm.com/developerworks/cn/education/java/j-nio/tutorial/index.html��Ϊ�˱���ѧϰ�ͷ�������������һ�� chm �ļ�������ĩ�����ء�

�ο����ϣ�
1. �����¼���NIO���̷߳�����
2. Servlet API �� NIO: ���������һ��
3. Java NIOԭ���ʹ��
4. ʹ��Java NIO��д�����ܵķ�����
5. Java NIO API���
6. nio�ļ���д






���� NIO ��˵��Channel(ͨ��) �� Buffer(������) �����������ǲ��ò���ģ���Ϊ������ NIO �ĺ��Ķ��󣬼���ÿһ�� I/O ������Ҫ���ǡ�

ͨ���Ƕ�ԭ I/O ����ģ�⣬���в�ͬ��������˫��ģ��������������� InputStream �� OutputStream��ͨ����˫���Ը��õķ�ӳ�˵ײ����ϵͳ����ʶ�����Ҳ������ԭ I/O ��������ֱ��������д������ݣ���ͨ���˴������ݱ��뾭�ɻ��������е�����ԭ I/O ��ͨ���������� BufferedInputStream �� BufferedOutputStream ����д���ݡ�

FileInputStream/FileOutputStream/RandomAccessFile/DatagramSocket/ServerSocket/Socket �� getChannel() �������Ի����Ӧ���͵� Channel��Channel �������� FileChannel/SocketChannel/SelectableChannel/DatagramChannel/ServerSocketChannel �ȡ�

��ͨ���ϵĶ�д��������ϻ��������� FileChannel.read(ByteBuffer dst)��FileChannel.write(ByteBuffer src)�����ļ�����Ҳ����ͨ���ϵĲ������� FileChannel.lock()��FileChannel.tryLock()��

Buffer �ӿڵ�ʵ������ ByteBuffer/MappedByteBuffer/CharBuffer/DoubleBuffer/FloadBuffer /IntBuffer/LongBuffer/ShortBuffer���õö�Ļ����� ByteBuffer���� Buffer ������Щ��ȡ���ݺ����ݶ�λ�Ĳ�����

������ NIO ��ԭ IO ��һЩ����Աȣ�

����: nio-oio.jpg 

�������� SocketChannel ����ͨ����δ����������� NIO ͨ���ͻ������ĸ���֮�����ǾͿ���ʹ�� NIO �����ļ����ж�д�����ˡ�����/��Ҷ��ݺ��














������ԭ�� IO ��д�ļ�Ӧ�ò���İ���ˣ�˳���ع�һ�£��������֣�

1. �� InputStream �� OutputStream �϶�д�ֽڻ��ֽ����飬�� InputStream ʱ���Ƿ񷵻� -1 ���ж��Ƿ񵽴�ĩβ��
2. ��װ�� Reader/Writer ����ֱ�Ӷ�д�ַ�������һ����װ�� BufferedReader/BufferedWriter �Ϳ��԰��ж�д�ˡ�readLine() ʱ���Ƿ񷵻� null �϶��Ƿ���������һ�С�

��������Ҫ�� NIO ����д�ļ����϶���Ҫ�õ� Channel �� Buffer �ˡ�һ�仰�������̾��Ǵ� FileInputStream �õ��� FileChannel �ж�ȡ���ݵ� Buffer �У��ٴ��� Buffer �е����ݡ������룺
01.public static void main(String[] args) throws Exception {
02.    FileInputStream fis = new FileInputStream("C:/Java/jdk1.6.0_18/LICENSE");
03.    
04.    //�õ��ļ�ͨ��
05.    FileChannel fc = fis.getChannel();
06.    
07.    //�������ļ��ߴ�ȴ�Ļ�����
08.    ByteBuffer bf = ByteBuffer.allocate((int) fc.size());
09.    
10.    //�����ļ�����ȫ���뻺�����������ڴ�ӳ���ļ�
11.    fc.read(bf);
12.    
13.    //�ѻ����е�ǰλ�ûظ�Ϊ��
14.    bf.rewind();
15.    
16.    //����������е�����
17.    while (bf.hasRemaining()) {
18.        System.out.print((char) bf.get());
19.    }
20.}
���ƴ���
�������ʹ����һ�����ļ��ߴ�ȴ�Ļ�������������һ���԰��ļ�����ȫ�������ڴ棬����ļ����ཫ��ʮ�ֺķѵ��ڴ�ģ��������ǿ������ֹ�ָ��ĳ����С(�� 1024,2048) �Ļ�������Ȼ��ֶ�ζ����ļ����ݵ��������С���ʱ�������������������ˣ�
01.public static void main(String[] args) throws Exception {
02.    FileInputStream fis = new FileInputStream("C:/Java/jdk1.6.0_18/LICENSE");
03. 
04.    // �õ��ļ�ͨ��
05.    FileChannel fc = fis.getChannel();
06. 
07.    // ָ����СΪ 1024 �Ļ�����
08.    ByteBuffer bf = ByteBuffer.allocate(1024);
09. 
10.    // ��ȡͨ���е���һ�����ݵ���������
11.    // �������� position ��Ϊ��ǰ�������������Чλ��
12.    while (fc.read(bf) != -1) {
13. 
14.        //�ѻ����е�ǰλ�ûظ�Ϊ�㣬ǰ�ѻ������� limit ����Ϊ֮ǰ position ֵ
15.        bf.flip();
16. 
17.        // ����������е�����
18.        while (bf.hasRemaining()) {
19.            System.out.print((char) bf.get());
20.        }
21. 
22.        // ����������׼���ٴζ�ȡ����
23.        bf.clear();
24.    }
25.}

����Ի������� rewind()/flip()/clear() ������������Ӱ�죬���� position/limit/mark �ȱ�־��Ӱ�졣������Ѳ�����֮��Ҫ�ر�ͨ������������

�� ByteBuffer ֪������ô���ļ�����(��Ȼ����δ�漰����������)����ӡ����Ļ���������� NIO ��ôд�ļ���

view source
print?
01.public static void main(String[] args) throws FileNotFoundException, IOException{
02.    FileOutputStream fos = new FileOutputStream("c:/nio.tst");
03. 
04.    // �õ��ļ�ͨ��
05.    FileChannel fc = fos.getChannel();
06. 
07.    // ָ����СΪ 1024 �Ļ�����
08.    ByteBuffer bf = ByteBuffer.allocate(1024);
09. 
10.    // Ҫд���ļ����ַ���
11.    String greeting = "Hello, Java NIO";
12.    
13.    //�������ַ������ַ��뻺����
14.    for (int i = 0; i < greeting.length(); i++) {
15.        bf.putChar(greeting.charAt(i));
16.    }
17.    
18.    // �ǵ�ִ�����������ʹ�� position=0, limit=30, ����д����ȷ������
19.    // ���� position Ϊ 30, limit Ϊ 1024������� 30 ֮���ȫ��������(0) ��ļ���
20.    bf.flip();
21. 
22.    // ����������д�뵽�ļ��У���ѻ������д� position �� limit ֮�������д���ļ�
23.    fc.write(bf);
24.    
25.    fc.close(); //�ر��ļ�ͨ��
26.    fos.close(); //�ر��ļ������
27.}
���ƴ���
ͬ���ģ������д���������ݣ�Ҳ��Ҫ�����ַ�������ش���ִ�к��� C �̸�Ŀ¼�²��� nio.tst �ļ������ݾ��� Hello, Java NIO���˴���Ĺؼ�֮�����ǶԻ���� flip() ���ã�������ڵ���ģʽ�¹۲쵽 flip() ��������ǰ�󣬻����� bf �� position/limit ���Եı仯������ע�͵� flip() ���룬�����������ɵ� nio.tst �ļ������ǲ��Ǵ��ྶͥ��

���ԣ�Ҫ�ú� NIO���������� mark/position/limit/capacity ����Ӧ��⣬�Լ� clear()/flip()/rewind() �ֱ����ôӰ�쵽�������ԡ�

���У���Ȼ˵ͨ����˫��ģ������ϲ�����������������ͨ���������ͨ������ʵ��ͨ��Ҳ����ֻ����ֻд�����ԣ������� FileInputStream.getChannel() ��õ�ͨ�����޷�д�����ݵģ��� FileOutputStream.getChannel() ��õ�ͨ���ǲ��ܶ��ģ�������׳���Ӧ���쳣 NonWritableChannelException �� NonReadableChannelException������ Buffer Ҳ�������Ƿ�ֻ�������ԡ�

ǰ��Ĵ���������ֻ��˵���� NIO ��д�ļ�Ӧ��δ���������˵�����þ� IO ��ʽ��д��Ч�ʾ͸����ˡ�NIO �ĸ�Ч��ֻ����������Щʱ�򣬲����κ�ʱ�����ھ� IO�����ǿ�������ֽڲ����������� NIO ʱҪС���ڴ档���־���ժ�������ò��Ű�����ӣ��ο��� IO ʵ�������������Щ��! ����/��Ҷ��ݺ��
