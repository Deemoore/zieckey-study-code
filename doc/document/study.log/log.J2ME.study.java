
2007/01/12
J2ME

J2ME�ƶ���������������ϸ�̳�


1.���ذ�װ����

���谲װ���߰��ͱ������õĹ��߰�����
jdk-1_5_x:jdk-1_5_0_08-windows-i586-p.exe
j2me_wireless_toolkit-2_2-windows:j2me_wireless_toolkit-2_2-windows.exe
eclipse-SDK-3.x:eclipse-SDK-3.2.1-win32.zip
eclipseme.feature_0.9.2_site:eclipseme.feature_0.9.2_site.zip

2.��װjdk�����û�������

��װj2sdk�Ժ���Ҫ����һ�»������������ҵĵ���-������-���߼�-����������-��ϵͳ������������»�������(�ٶ����j2sdk��װ��C:\Program Files\Java\jdk1.5.0_08����
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
������ʱ���������ӡ���� Hello world! My Java! �Ļ�˵����װ�ɹ��ˣ����û�д�ӡ����仰����Ҫ��ϸ���һ��������������


3.��װj2me_wireless_toolkit-2_2-ml-windows(���WTK)

J2ME WTK ��װ�ܼ򵥣�������ʾ��װ���ɡ�
������谲װ��:M:\J2ME\WTK22


4.Eclipse��װ��J2ME�Ĳ����װ

��Eclipse��ѹ���κ�λ�ü���.
Ϊ��ȷ��Eclipse��������,�����Eclipse��д��СJava���������.
Ȼ��װ Eclipse ��J2ME WTK ֮��ĵ��ò��.
�������ͨ��Eclipse�Ĳ˵���:Help->software updates->Find and Install...->search for new feathers to install->new archived site... 
ѡ�������ص����ؼ�����ϵ�eclipseme�����

Ҳ����
Help->software updates->Find and Install...->search for new feathers to install->New Remote Site

����
Name��EclipseME Update Site
URL��http://www.eclipseme.org/updates/

���Finish��Ȼ��һ��һ��������ʾ�Ϳ�����ɰ�װ��

//����������������������������������
����Eclipse,�����������ã�
Window->preferences->J2ME->Platform Component
Ȼ���Ҽ�ѡ�� Wireless Toolkil����ѡ�񵯳��˵��е� Add Wireless Toolkil��
ѡ��ոհ�װ��J2ME Toolkit�İ�װ·��: M:\J2ME\WTK22
�����������þ����ú��ˡ�

//����������������������������
����Eclipse,�����������ã�
Window->preferences->J2ME->Device Management
������...(Import)��ť�� 
�ڽ������ĶԻ����У�ѡ��һ���������߹��߰��ĸ�Ŀ¼��EclipseME�����в�����֪�豸���塣 

 

�����뿪����Ŀ¼�ı��򣬻�����ˢ��(Refresh)��ť�� EclipseME�ͻῪʼ��ָ����Ŀ¼������Ŀ¼�������豸���塣��EclipseME��1.5.0�汾�У��㲻����Ҫ����ȷ�ġ�ѡ��Ŀ¼������ȷ�����豸��ֻҪ����λ����ָ����Ŀ¼�У�EclipseME��Ӧ���ܶ�λ�����ǡ��ҵ�һ���豸���壬EclipseME�ͻ����б�����ʾ��һ���������ϣ��ֹͣ������ֻҪ����ȡ��(Cancel)��ť�Ϳ��ԡ� 

���������Ժ󣬹�ѡ���뵼�����Щ�豸���塣ֻ�е������豸���ܱ����ڶ�����Ŀ�Լ������������ѡ�����(Finish)�����������̡� 

���EclipseMEû�ҵ���ϣ��������豸���壬�ǿ�����EclipseME����֧��������������£����������ύһ��RFE(����������)��Ҫ�����Ӷ�����WTK��֧�֣��𲻺���˼��������ô����μ���� 


��󣬸ı�Eclipse�ĵ����趨
��Ϊ���߹��߰���һЩ��ֵ���ƣ�������Sun�ģ����������ʹ��Eclipse������MIDlet���������ı�һЩĬ�ϵĵ����趨���������� 

ѡ��Eclipse�Ĵ��ڲ˵��е���ѡ� 

���������е�Javaѡ���֧���������� 

ȷ���ӽ��Ի��򶥶˵��������δ������쳣ʱ�ݹ�ִ�� ���ڷ����������ʱ�ݹ�ִ�ж�û�б���ѡ�� 

�ѽӽ��Ի���ײ��ģ���������ʱ��ֵ��������15000���롣 

�趨��Ľ��Ӧ�ÿ���ȥ���������� 
 

����㲻����Щ�ı䣬������MIDlet��ʱ��ͻᷢ������ 



5.����J2ME

New->Project->J2ME->J2ME Midlet Suite->Next
���빤�����֣�J2METest
���Finish.
�������´���:


import javax.microedition.lcdui.Display;
import javax.microedition.lcdui.Form;
import javax.microedition.midlet.MIDlet;
import javax.microedition.midlet.MIDletStateChangeException;

public class Hello extends MIDlet
{
    private Display display;
    public Hello()
    {
    	 display = Display.getDisplay(this);
    }

    public void startApp()
    {
    	Form form = new Form("����J2ME");
    	form.append("Hello world!");
        display.setCurrent(form);
    }

	protected void destroyApp ( boolean arg0 ) throws MIDletStateChangeException
	{
		// TODO Auto-generated method stub

	}

	protected void pauseApp ()
	{
		// TODO Auto-generated method stub

	}
}

����,�������һ���ֻ�����,�������ֻ���ʾ�������:Hello world!,
��ϲ��,���J2ME�ƶ�����ƽ̨��װ�ɹ���!
����Ͽ쿪ʼ���J2ME��ʼ֮�ð�!





/////////////////////////////////////////XXXXXXXXXXXXXXX
��װNokia��SDK��http://www.j2medev.com/Article/Class1/Class11/200609/3178_2.html��


���� Nokia Developer's Suite 3.0 for J2ME  

�����Դ� Nokia ��̳�Ĺ���ר��������ѵ� Nokia Developer's Suite for J2ME����ַ�� http://www.forum.nokia.com/tools(����վ������ר��Ҳ�ṩ����http://www.j2medev.com/Soft/tools/200509/117.html)��

�ڿ�ʼ�������صİ�װ����֮ǰ��������ж�� ������ǰ��װ�� Nokia Developer's Suite for J2ME �汾��Ȼ����Ҫ�������� Nokia ��̳��ʹ�õ��û��������󣨲�ͨ�������ʼ����գ������кš��ڻ����ʾ��ʱ��Ӧ��ѡ�񽫸��׼��� Eclipse ���ɡ�����Ҫ���߰�װ��������װ Eclipse �ĸ�Ŀ¼��

���� Eclipse  

���ڣ����� Eclipse IDE �������ڹ������Ͽ���һ���µ� Tools > Nokia Developer's Suite for J2ME �˵����һ���µ�ͼ���š�

�� SDK ��ӵ� Nokia Developer's Suite ��  

�����ܱ����ֹ����µ� SDK ��ӵ� Nokia Developer's Suite �С�Ϊ��������һ�㣬��Ҫִ�����²��裺

ѡ�� Tools > Nokia Developer's Suite for J2ME > Configure Emulators�� 
���� Add ���µ� SDK ��ӵ������б��С� 



��Eclipseme���ɣ�

Window->preferences->J2ME->Device Management
������...(Import)��ť�� 
�ڽ������ĶԻ����У�ѡ��һ��Nokia SDK�ĸ�Ŀ¼��D:\software\J2MESDK\NDS3.0\Devices\Nokia_Prototype_SDK_2_0\����EclipseME�����в�����֪�豸���塣 
/////////////////////////////////////////XXXXXXXXXXXXXXX



nS60_jme_sdk_3rd_e_FP2_Beta.zip 





/////////////////////////////////////////XXXXXXXXXXXXXXX
��netbeans�м���Nokia SDK

��װ��Nokia��SDK�󣬴�Netbeans
ѡ��Tools->Java Platforms->Add Platform...��
��ѡ��ڶ���"Java ME Platform Emulator"

Ȼ����Netbeans�Լ�ȥ��������ѡ��Nokia��SDK�Ϳ�����

/////////////////////////////////////////XXXXXXXXXXXXXXX




ע�⣺�������ֽ̳�Ҫ������Ƶ�̳̣����ܸ�����.���в����ط������¼�й�J2ME��̳������ѯ(http://www.j2meforum.cn),�̳̿������⴫������δ������ͬ�ⲻ�������޸ġ�

									�̳����������󣬻������ָ�̣�

									���ߣ�James.Ming
									QQ��66171709
									MSN:trasher007@hotmail.com
									Mail:jamesming@126.com
									����:2005/06/26



ʹ��WTK 2.2����J2MEӦ�ó���
����M:\Java\J2ME\WTK22\bin\ktoolbar.exe
File->New Project...
���빤�����ֺ�������




J2ME���򿪷�ȫ��λ�����������
һ��J2ME����Ҫ��Java����֪ʶ
       �����д󲿷��ˣ����Ǵ��㿪ʼѧJ2ME�ģ�ѧϰJ2ME��ʱ�����Ǵ�Java������ʼѧϰ���������ڽ�Java�������鼮�ж�����J2SE������������͸�ѧϰ�����һЩ����Ҫ���鷳�����潫J2ME���õ��ĺͲ���Ҫ��Java����֪ʶ��һ���򵥵�˵����
       J2ME��ʹ�õ���Java����֪ʶ��
����  1��Java�﷨���������������������͡��ؼ��֡�������ȵ�
����  2����������˼�룺��Ͷ���ĸ���̳кͶ�̬�ȵȡ�
����  3���쳣����
����  4�����߳�
����J2ME��û���õ���Java����֪ʶ��
����  1��JDK��javac��java�����ʹ��
����  2��Java�����еĺܶ�����J2ME��û�У��������еķ������˴����ľ������Խ�����J2ME����Ϥ��⡣
����  3��Applet��AWT��Swing��Щ֪ʶ��J2ME�и���ʹ�ò�����
������˵��ô�࣬ϣ��ѧJ2ME��������������һЩ��·������֮��ϣ����һ���ָ���Ͳ��䡣

����J2ME����ʱ�޷���ɵĹ���
������һЩJ2ME����ʱ�޷���ɵĹ��ܣ�ϣ������ܻ������䣺
����  1�����ֻ��в����Ĵ���ʵ����ֲ����Ҫָ��Ϸ��
����  2����̬�޸İ�ť���֡�
����  3����Canvas�Ͻ����������롣
����  4������������Դ�������ַ�������ն���Ϣ�ȡ�
����  5�������ƻ��Ե��ֻ�������
����  6�������ȴ���������䡣

����J2ME�Ŀ�ƽ̨��
����J2ME����Դ��Java������Ҳ����JVM�����ƣ�������֧��Java��ƽ̨�Ͻ�����ֲ���������ڵ�J2ME�����ڿ�ƽ̨��ȴ���ĺ���⣬�������򵥿�һ��ԭ��
����1���ֻ�����Ļ�ߴ粻һ��
���������Ҫ�ڽ��������ϡ������ʹ�õ��Ǹ߼��û����棬������������Ӧ�ÿ��������û���½���û�ע��������ͨ�ù���ʱ��һ��û��ʲô���⡣
���������ʹ�õ��ǵͼ��û����棬��������������Ϸ����ô�����Ҫ������������ˡ�
����2�����̵���չAPI��ͳһ��
��������Nokia����չAPI���UIϵ�У��ڱ���ֻ��ϻ���û��ʵ�֣����߰�����ͬ�ȵȡ�
����3���ֻ�ƽ̨��ʵ�ֵ�bug��
��������Nokia��7650��ʵ��˫��������bug����ô�����ֻ��������е�����Ͳ���ʹ��˫���塣����NOKIA�ϵ�һЩbug�����Բο���http://blog.csdn.net/Mailbomb/archive/2005/03/24/329123.aspx
����4���ֻ��������⡣
������ͬ�ֻ��Ŀ����ڴ桢���jar�ļ�����Ҫ������Nokia S40�Ĵ󲿷��ֻ�֧�ֵ����jar�ļ�Ϊ64K������������Ϊ210K��
�����������ڵ��ֻ�������ر�����Ϸ���ṩ֧�ֵĻ����б�Ҳ�������ֻ���Ϸ��ֲ��Ա�Ĵ��ڡ�

�ġ�ѧϰJ2ME���Դ��µĹ�������
��������J2ME��������˵�൱�Ļ𱩣��������һЩѧ����J2ME֮����Դ��µĹ��������ࣺ
����1��J2ME��Ϸ������Ա
����������Ϸ�߻������ĵ�Ҫ����ĳ���ض��Ļ���(��Nokia S40��S60�Ӷ�)������Ϸ����
�����������ڴ󲿷�J2ME����Ա���µĹ�����
������Ҫ�������գ��߼��û����桢�ͼ��û����桢�̣߳������������Ϸ������Ҫ���������̡�
����2��J2MEӦ�ÿ�����Ա
�������ڵ��ƶ�Ӧ�û����Ǻܶ࣬���ǻ��ǳ�����һЩ���ر����ƶ���λ�Լ��ƶ�������ص����ݡ�
������Ҫ�������գ��߼��û����桢�̺߳������̡�
����3��J2ME��Ϸ��ֲ��Ա
��������Դ���룬��������һ��ƽ̨�Ͽ������е���Ϸ��ֲ������ƽ̨��ȥ�����罫Nokia S40����Ϸ��ֲ��S60�ϣ�����������T618�ȵȡ�
������Ҫ�ǿ�����Ļ���꣬��Щ������Ҫ�滻һЩAPI��
������Ҫ��Ϥ��ƽ̨֮��Ĳ����Լ���صļ���������������Ļ��С�����jar�ļ��ߴ�ȵȡ�

�塢J2ME������Ƶļ���ԭ��
����1��ʹ����������̡�
������Ȼʹ��������̱�̿��Լ�С�ļ��ĳߴ磬����Ϊ���Ժ�ά���ķ����������չ������Ҫʹ����������̡�
����2��ʹ��MVCģʽ
������ģ�͡�����Ϳ��Ʒ��롣���ںܶ�ĳ������ߺ�һ��������������ĳ���Ƚϴ�Ļ������ǽ�������з��롣
����3���Զ��洢�û��趨
����ʹ��RMS���洢�û�����Ϣ������洢�û��ϴ�������û��������롢�û�����ϵͳ���趨�ȣ������������Լ����û������룬���Ҷ��û��Ѻá��ܶ�������������Զ���½�ȡ�
����4��һЩϵͳ���������û��رա��米�����֡���������ʾ�ȡ�
����5�����ͼ��û�����Ļ��ƶ�������һ���������߳�����ȥ��
����6������Ҫ����ʱ�������ɵĹ���ʱ�����û�һ���ȴ����档

������ģ�������������
��������J2ME��������˵��ģ���������Ǵ����˺ܶ෽�㣬���������ģ�����е��Գ����Լ��ܷ���Ĳ쿴�����Ч��������ģ����Ҳ�����Ǵ�����һЩ���⣬����ģ����ʵ�ֵ�bug�ȵȣ����Խ�����������Ǳ���ġ�
����1��ΪʲôҪ����������ԣ�
������Ϊģ����������ܴ���bug���Լ�������������ޣ����Ա������������ԡ�
����2����ν������䵽�����У�
�����������䵽�����������·�ʽ��
����  a)��OTA����
����  b)��ʹ�������ߴ���
����  c)�����⴫��
����  d)������
��������Ը���������ѡ����ʵķ�ʽ��
����3�� ���������Ҫ��ʲô��
����������Ե����ݺܶ࣬��Ҫ�������¼������棺
����  a)������Ĺ���
����  b)������Ĳ����ԣ��Ƿ��ײ���
����  c)������Ĵ�С,����Nokia S40ϵ�е��ֻ��󲿷ֽ��ܵ�����ļ��ߴ�Ϊ64K
����  d)�����������ٶȣ��ٶ��Ƿ�������ܡ�

�ߡ���WTK������SDK
��������J2ME��������˵�������ϴ�Ҷ��Ǵ�SUN��WTK(J2ME Wireless Toolkit)��ʼ�ģ����Ƕ���ʵ��Ӧ����˵������ʹ��WTK��ԶԶ�����ģ�������ѧϰ�����У�������ɴ�WTK��SDK�Ŀ�Խ��
����1������SDK�����ص�ַ��
����http://blog.csdn.net/Mailbomb/archive/2005/01/01/236606.aspx
����2������SDK��WTK��ʲô��ͬ��
��������SDK��򵥵���������WTK�Ļ������������Լ���ģ�������Լ�����չAPI��
����Ҳ����˵������ʹ�ó��̵�SDKʱ������ʹ�ó��̵���չ��⣬����Nokia��UI��⣬�ͳ����Լ���ģ�������ѡ�
����ÿ�����̵���չAPI�����࣬���Ҳ�����ͬ��
����3�����ʹ�ã�
������Щ����SDK��ʹ�ö���WTK��ͬ������SamSung��
����Nokia�ṩ�˶����Ľ������������������������ʵ�ʿ�����ʹ�ò��ࡣ
����4������SDK������
��������SDKʵ�ֹ����У���һЩbug�����Һ����ʵ�ֲ�һ�¡�����NOKIA�Ļ�����������ȵȡ�

�ˡ���J2ME�л���ֻ�IMEI�ķ���
����IMEI��Internation mobile entity identification�ļ�ƣ����ֻ�������*#06#������ʾ�����֣�����Ϊ15λ��ȫ��Ψһ����Զ�����ͻ�����Կ�����Ϊʶ���û���һ����־��
������������J2ME�л��IMEI�ķ�����
����1��MOTOϵ�е��ֻ�����ͨ����ȡϵͳ��IMEI���Ի�ã��������£�
����           String imei = System.getProperty("IMEI");
����2��SIEMENSϵ�е��ֻ�����ͨ����ȡϵͳ��com.siemens.IMEI���Ի�ã��������£�
����           String imei = System.getProperty("com.siemens.IMEI");

�š�J2ME������������ʾ����Ľ���취
�������������У���Щʱ������һЩ��û�н��յ��������ݾ���ʾ����ģ���ɽ�����ʾ������Ҫ�����繫����ʾ��������ʾ����ı���ͼƬ����ʾ������Ϣ����������һ���򵥵Ľ���취����ң�
���������������ķ����ֳ��������裺
����1������Ҫ��ʾ�Ľ����У����÷����������ݵķ�����ÿ����ʾʱ���øù��췽����������Display��setCurrent������ʾ��
����2����ʾ�ȴ�����(�����������)�����û���ʾ���ڽ����������ӡ�
����3���ڴ������練�����������Ժ󣬵���Display��setCurrent������ʾ��ʾ��ǰ���档

ʮ����ǿJ2ME��String���������ָ��ַ���
������JDK1.4�Ժ�String����������split������ʵ���ַ����ķָ������J2ME��ȴû�и÷���(MIDP2.0��Ҳû��ʵ��)��������ʵ��ʹ�ù����У���Щʱ���ȷҪ�õ����ֲ��������ｫ����ǰʵ�ֵ�һ�δ���ʹ�ҹ���
/**
* �ָ��ַ�����ԭ������ַ����еķָ��ַ�����Ȼ��ȡ�Ӵ�
* @param original ��Ҫ�ָ���ַ���
* @paran regex �ָ��ַ���
* @return �ָ�����ɵ��ַ�������
*/

private static String[] split(String original,String regex)
{
     //ȡ�Ӵ�����ʼλ��
     int startIndex = 0;
     //����������ȷ���Vector��
     Vector v = new Vector();
     //���صĽ���ַ�������
     String[] str = null;
     //�洢ȡ�Ӵ�ʱ��ʼλ��
     int index = 0;

     //���ƥ���Ӵ���λ��
     startIndex = original.indexOf(regex);
     //System.out.println("0" + startIndex);
     //�����ʼ�ַ�����λ��С���ַ����ĳ��ȣ���֤��û��ȡ���ַ���ĩβ��
     //-1����ȡ����ĩβ
     while(startIndex < original.length() && startIndex != -1)
     {
           String temp = original.substring(index,startIndex);
           System.out.println(" " + startIndex);
           //ȡ�Ӵ�
           v.addElement(temp);

           //����ȡ�Ӵ�����ʼλ��
           index = startIndex + regex.length();

           //���ƥ���Ӵ���λ��
           startIndex = original.indexOf(regex,startIndex + regex.length());
     }

     //ȡ�������Ӵ�
     v.addElement(original.substring(index + 1 - regex.length()));
     //��Vector����ת��������
     str = new String[v.size()];
     for(int i=0;i
     {
          str[i] = (String)v.elementAt(i);
     }

     //�������ɵ�����
     return str;
}

ʮһ��J2ME�ڵͼ��û������Ϸ�����ʾ����
������J2ME�ĵͼ��û����濪���У�������������Ҫ��Canvas����ʾ���������֣�������ڽ��桢��Ϸ˵������Ϸ�������Ϣ����������ʱ�������ֵ����ݺͳ��ȶ��̶����Ȳ������޸�Ҳ������ά�����������һ���򵥵ķ�����ʵ��һ���򵥡���ά����ǿ�ķ�ʽ��
����ʵ�ַ�����
����  1������Ҫ��ʾ��������Ϣ����һ���ַ�����
����  2����дһ�������ַ�������Ҫ��ת��Ϊ�ַ�������ķ�����
����  3����ת�����������ѭ���ķ�ʽ��ʾ��Canvas�ϡ�
����ͨ�������������裬���޸���ʾ����Ϣʱ��ֻ��Ҫ�޸İ�����ʾ��Ϣ���ַ������ɣ��Լ���д�ķ������԰�����ǰ�ı�׼���·ָ��µ��ַ����������Ҫ�޸�ÿ����ʾ���ַ���������ֻ��Ҫ�޸��Լ���д�ķ������ɡ�
����ͨ������һ��ʵ�ַ�ʽ�����Ժܷ����ʵ����ʾһЩ�Ƚϳ����ı���Ϣ����ʹ�ǿɱ䳤�ȵ��ַ���Ҳû�����⡣

ʮ����J2ME��ʹ�ü�¼�洢ϵͳ(RMS)�洢��Ϣ
������MIDP�У�û���ļ��ĸ���������ô洢һ��ֻ��������¼�洢ϵͳʵ�֣����ڼ�¼�洢ϵͳ�ļ�飬���Բο��̳̣�http://www-900.ibm.com/developerWorks/cn/java/j-wi-rms/index.shtml
����������һЩ��¼�洢ϵͳ�ĳ��ñ�����ܣ�
����  1���򿪼�¼����
�����򿪼�¼��ʹ��RecordStore����ľ�̬����openRecordStore��ʾ���������£�
          RecordStore rs = RecordStore.openRecordStore(��username��,true);
���������ʹ���һ������Ϊrs�ļ�¼��������usernameΪ��¼�������ƣ������ƿ��Ը�����Ҫ��ȡ���ڶ������������Ƿ���û��ʱ�����µļ�¼����true�����ڸü�¼��������ʱ�������µļ�¼����false����������
��������ڴ򿪼�¼��ʱ���ü�¼�������ڣ����׳�RecordStoreNotFoundException�쳣�����Լ���¼���Ƿ��Ѵ�������ʹ�ø��쳣��
����ע�⣺��¼�����Ժ�ǵùرա�
����  2�����¼����д������
����      2.1��������
�������Ѿ��򿪵ļ�¼����������ݣ���Ҫʹ��addRecord������ʾ�����룺
                 byte[] bytes = {1,2,3};
����           int id = rs. addRecord(bytes,0,bytes.length);
�����ô��뽫�ֽ�����bytes��ȫ������д�뵽��¼���У��÷����ķ���ֵΪ����Ϣ��id��ע�⣺id��1��ʼ�������Ǵ�0��ʼ��
���������ѭ��ʹ�ø÷������¼����д��������ݡ�
����      2.2�޸�����
�����޸��Ѿ����ڵļ�¼����ָ��id�����ݣ���Ҫʹ��setRecord������ʾ�����룺
                 byte[] bytes = {1,2,3};
����           rs. setRecord(1,bytes,0,bytes.length);
�������ϴ���������ǽ��ֽ�����bytes��ȫ������д�뵽idΪ1�ļ�¼��rs�С�
�����ò����Ḳ�����е����ݡ�
����˵������Щʱ������Ҫ����Ϣд�뵽��¼���еĵ�һ����¼�У�����Խ�������������������һ��ʱ���¼���������ݣ��Ժ��������޸ġ�
����  3���Ӽ�¼���ж�������
�����Ӽ�¼���ж�ȡ�������ݣ���Ҫʹ��getRecord������ʾ�����룺
            byte[] bytes = rs. getRecord(1);
�����ô���Ӽ�¼��rs�ж�ȡ��һ�����ݣ�����ȡ�������ݷ���bytes�����С�
�����ڶ�ȡ����ʱ�����Ի�ü�¼����id�ĸ���������ʹ��getNumRecords�������
�����ۺϴ���Ϊ��
       int number = rs. getNumRecords();
       int id = 1;
       if(id >0 && id < number)
       {
����     byte[] bytes = rs. getRecord(1);
       }
����  4���Ӽ�¼����ɾ����¼
�����Ӽ�¼����ɾ����¼�ķ��������֣��߼�ɾ��������ɾ����
�����߼�ɾ����ָ��ɾ���ļ�¼���ǡ�
��������ɾ����ָ��������ɾ���ü�¼�����Ǹü�¼��id���ܱ����ã�Ҳ����˵��id���ᱻ����ʹ�á�����һ����¼������5����¼��������ɾ����idΪ3�����ݣ���ʣ���¼��id��ȻΪ1��2��4��5���������������һ�����鷳��
����  5��������¼��
����������¼���������ʼ�¼���е��������ݣ������������������
http://gceclub.sun.com.cn/NASApp/sme/controller/teclist?tid=0103
����  6����������
����ɾ����¼��
����ɾ����¼����ͬ��ɾ����¼����Ҫʹ��deleteRecordStore������ʾ�����룺
                RecordStore. deleteRecordStore(��username��);
�����ô���ɾ������Ϊusername�ļ�¼����

ʮ����J2ME�������ݵ�һ����������Դ���������
������J2ME����У���������һЩ�����ڴ洢���ߴ���ʱ��Ҫ���ܣ��������һ���������ļ�������һЩ���ϣ�
�����������Ĺٷ���ҳ��http://www.bouncycastle.org/
�������ܵ����£�
�������ģ�http://18900.motorola.com/ewa_portal/develope/jc_j2messl_5_1.jsp
����Ӣ�ģ�http://www.javaworld.com/javaworld/jw-12-2002/jw-1220-wireless.html
���������µ�Դ�������ʹ�õ�һЩ������
������ע����Ϊ������ṩ�Ĺ��ܱȽ�ǿ���������ĳߴ�Ƚϴ�����ڷ���ʱ��Ҫ������в���Ҫ����ɾ��

ʮ�ġ���β�������
������J2ME�У�����������Ҫʹ�õ�Mobile Media API(MMAPI)���ð���MIDP1.0�Ŀ�ѡ������MIDP2.0���Ѿ�����������������������ʹ��MIDP1.0�Ļ�����ȷ��������л����Ƿ�֧�֡�
����һ���ֻ�֧�ֵ������ļ���ʽΪwav��mid��mpg�ȡ��������������ֻ�˵���ĵ���
���������������У��кܶദ��ķ�ʽ������˵һ����õ����������JAR�ļ��е�wav�ļ���
�������������ļ������̣�
����  1������һ���ĸ�ʽ��ȡ�����ļ���
��������JAR�ļ��е������ļ�һ���ǽ������ļ������������ʽ��ʾ�����룺
             InputStream is = this.getClass().getResourceAsStream("/Autorun.wav");
       ����Autorun.wav�ļ�λ��JAR�ļ��ĸ�Ŀ¼�£����λ�ڱ��Ŀ¼����Ҫ����Ŀ¼���ƣ���/res /Autorun.wav��
����  2������ȡ�������ݴ��ݸ���������
����������Ϣ���ݸ�������������������һ���ĸ�ʽ�����н��������ʾ�����룺
             Player player = Manager.createPlayer(is,"audio/x-wav");
�������е�һ������Ϊ�����󣬵ڶ�������Ϊ�����ļ��ĸ�ʽ��
����  3������������
����ʹ��Player�����start���������Խ��������ų�����ʾ�����룺
             player.start()��
�����ڲ�������ʱҲ�����趨�������ŵĴ���������ʹ��Player���е�setLoopCount������ʵ�֣�����ɲ���API�ĵ���
������������NOKIA S60ģ�����в���ͨ�����������£�
package sound;
import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;
import javax.microedition.media.*;
import java.io.*;

public class SoundMIDlet extends MIDlet
{
����private Player player = null;
����/** Constructor */
����public SoundMIDlet()
       {
             try
             {
                   InputStream is = this.getClass().getResourceAsStream("/Autorun.wav");
                   player = Manager.createPlayer(is,"audio/x-wav");
             }
             catch(IOException e)
             {
                   System.out.println("1:" + e);
             }
             catch(MediaException e)
             {
                   System.out.println("2:" + e);
             }
             catch(Exception e)
             {
                   System.out.println("3:" + e);
             }
      }

      /** Main method */
      public void startApp()
      {
             if(player != null)
             {
                   try
                   {
��������          player.start();
                   }
                   catch(MediaException e)
                   {
��������          System.out.println("4:" + e);
                   }
             }
       }

       /** Handle pausing the MIDlet */
       public void pauseApp()
       {
       }

       /** Handle destroying the MIDlet */
       public void destroyApp(boolean unconditional)
       {
       }
}

ʮ�塢J2ME 3D��̵�һЩ����
��������J2ME�����ķ�չ���Լ�Ӳ���ٶȵ�������3D��Ϸ���������ı�������������ѧϰ��һ��ı�̣������ռ���һЩ���ϣ��ʹ��һ�����
����1��JSR184
����JSR184��Nokia��˾��ݵ�һ������3D API�Ĺ淶�����ص�ַΪ��
����http://www.forum.nokia.com/main/1,,1_0_10,00.html#jsr184
����2��Nokia��3D�������
����http://www.forum.nokia.com/main/1,6566,21,00.html
����3��3D����
����һ���򵥵Ŀ���Դ�����3D��Ϸ����
����http://www.j2me.com.cn/Soft_Show.asp?SoftID=19
��������һ����������3D�������Ŀ��
����http://gceclub.sun.com.cn/NASApp/sme/jive/thread.jsp?forum=11&thread=8593
����4��һ��3D��Ϸ��Ʒ
����http://games.sina.com.cn/newgames/2004/04/040217696.shtml
����5��֧��3D�Ŀ�������
������ǰһЩ�߶˵��ֻ�֧��3D������֧��3D�����Ŀ��������У�ͨ�õ���SUN��J2MEWTK2.2��ר�õ��ǳ�����ߵ�֧��JSR184��SDK��

ʮ����3D��̡�����һ��3D����
�����ο�WTK2.2�ṩ��demo������˵�һ��3D������Ȼ�ܼ򵥣�������Щ���⻹���Ǻ���������ǰѴ��빲�������Ը��ѧϰJ2ME 3D��̵�����һ��ѧϰ��
�������ڴ���ı��������˵�����£�
����1�����´�����J2ME WTK2.2�������ͨ����
����2�������Ϊ�����ļ���First3DCanvas.java��First3DMIDlet.java��
����3��ʹ��J2ME WTK2.2�����µĹ��̣���MIDlet��Ϊ��first3d. First3DMIDlet
����4�������뱣������Ĺ���Ŀ¼�µ�first3dĿ¼�¡�
����5����J2ME WTK��װĿ¼�µ�apps\Demo3D\res\com\superscape\m3g\wtksamples\retainedmode\contentĿ¼�е�swerve.m3g�ļ����Ƶ���Ĺ���Ŀ¼�µ�resĿ¼�¡�
����6����Ĺ��̽��������ù��̣�ͨ��WTK�����еġ����á���ť�����ô��ڣ��ڡ�APIѡ���У����á�Ŀ��ƽ̨��Ϊ���Զ��壻���򵵡�Ϊ��MIDP2.0���������á�Ϊ��CLDC1.1����ѡ�С�Mobile 3D Graphics for J2ME(JSR184)����
����7��������Ϳ��Ա�����������´����ˡ�
����Դ�������£�

// First3DMIDlet.java
package first3d;
import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;
public class First3DMIDlet extends MIDlet
{
      private First3DCanvas displayable = new First3DCanvas();
      public void startApp()
      {
            Display.getDisplay(this).setCurrent(displayable);
      }

      public void pauseApp() {}

      public void destroyApp(boolean unconditional) {}
}

// First3Dcanvas.java
package first3d;
import javax.microedition.lcdui.*;
import javax.microedition.m3g.*;
import java.util.*;
/**
* ��һ��3D����
*/
public class First3DCanvas extends Canvas implements Runnable
{
      /**World����*/
      private World myWorld = null;
      /**Graphics3D����*/
      private Graphics3D g3d = Graphics3D.getInstance();
      /**Camera����*/
      private Camera cam = null;
      private int viewport_x;
      private int viewport_y;
      private int viewport_width;
      private int viewport_height;
      private long worldStartTime = 0;
      //�ػ�ʱ��
      private int validity = 0;

      public First3DCanvas()
      {
            //�����ػ������߳�
            Thread thread = new Thread(this);
            thread.start();
            try
            {
                   //����3DͼƬ
                   myWorld = (World) Loader.load("/swerve.m3g")[0];
                   viewport_x = 0;
                   viewport_y = 0;
                   viewport_width = getWidth();
                   viewport_height = getHeight();
                   cam = myWorld.getActiveCamera();
                   //����cam����
                   float[] params = new float[4];
                   int type = cam.getProjection(params);
                   if (type != Camera.GENERIC)
                   {
                          //calculate window aspect ratio
                          float waspect = viewport_width / viewport_height;
                          if (waspect < params[1])
                          {
                                float height = viewport_width / params[1];
                                viewport_height = (int) height;
                                viewport_y = (getHeight() - viewport_height) / 2;
                          }
                          else
                          {
                                float width = viewport_height * params[1];
                                viewport_width = (int) width;
                                viewport_x = (getWidth() - viewport_width) / 2;
                          }
                   }
                   worldStartTime = System.currentTimeMillis();
            }
            catch (Exception e) {}
      }

      protected void paint(Graphics g)
      {
            //�������
            g.setColor(0x00);
            g.fillRect(0, 0, getWidth(), getHeight());
            //��3D�����
            g3d.bindTarget(g);
            g3d.setViewport(viewport_x, viewport_y, viewport_width, viewport_height);
            long startTime = System.currentTimeMillis() - worldStartTime;
            validity = myWorld.animate((int)startTime);
            try
            {
                   g3d.render(myWorld);
            }
            finally
            {
                   g3d.releaseTarget();
            }
      }

      public void run()
      {
            try
            {
                   while(true)
                   {
                         //�ػ�ͼ��
                         repaint(viewport_x, viewport_y, viewport_width, viewport_height);
                   }
            }
            catch(Exception e){}
      }
}

ʮ�ߡ���J2ME��������ʹ��CMWAP����
�������й��ƶ��ṩ�����������У���ΪCMNET��CMWAP���֣�����CMNET���������Ƶķ��ʻ������磬�ʷѱȽϹ�CMWAP����һ��HTTP�Ĵ��룬ֻ�ܷ���֧��HTTP��Ӧ�ã������ʷѱ��ˣ��ȶ��ԱȽϲ
������ʵ�ʵ�J2ME�������У�һ����Ҫ�ṩ��CMWAP����ķ�ʽ�������磬��J2ME�У����ӵĴ����ֱ������������ͬ���������£�
             HttpConnection http = (HttpConnection)Connector.open(("http://10.0.0.172/"+url);
             http.setRequestProperty("X-Online-Host",ServerName);
������������Ҫ���ʵĵ�ַΪ��http://www.test.com/login/loginServlet������Ĵ����Ϊ��
             HttpConnection http = (HttpConnection)Connector.open(("http://10.0.0.172/" + "login/loginServlet");
             http.setRequestProperty("X-Online-Host","www.test.com");
������ʵ��ʹ�ù����У�ֻ��Ҫʹ��ʵ����Ҫ���ʵĵ�ַ����������IP������ServerName������ʾ���еġ�www.test.com����ʹ�ú����ĵ�ַ���������е�url������ʾ���еġ�login/loginServlet�����Ϳ���ʵ�ʵ�ʹ��CMWAP���������������ˡ�

ʮ�ˡ�J2ME�е�ʱ�䴦��ȫ����
����ʱ�䴦���ڳ��򿪷����൱�������������ʱ�䴦����һ���򵥵�˵����
����һ��ʱ��ı�﷽ʽ
����ʱ����J2ME�������ֱ�﷽ʽ��
����1���Ժ�GMT1970��1��1����ҹ12����������ĺ�����������
�������ַ�ʽ�ʺϱȽ�����ʱ��֮��Ĳ�ֵ��
����2���Զ������ʽ�����
��������ʱ�䴦��������
����ʱ�䴦����J2ME���漰�����ࣺ
����1��System��
���� long time = System. currentTimeMillis();
����ʹ�ø÷������Ի�õ�ǰʱ�䣬ʱ��ı�﷽ʽΪ�����ᵽ�ĵ�һ�֡�
����2��Date��
���� Date date = new Date();
������õ�ǰʱ�䣬ʹ�ö������ʽ�����б�
����3��Calendar��
���� Calendar calendar = Calendar. getInstance();

����ʱ�䴦��ľ������
����1���������ֱ�﷽ʽ��ת����
����a)��System���õ�ʱ��ת��ΪDate����
���� Date date = new Date(System. currentTimeMillis());
����b)��Date���͵Ķ���ת��ΪCalendar���͵Ķ���
���� Calendar calendar = Calendar. getInstance();
���� Date date = new Date();
���� calendar.setTime(date);
����2��ʹ��Calendar���һЩ���ڲ�����
����Calendar��ʱ�䴦�������Ҳ�ǹ�����ǿ����࣬�������������ĳ��ʱ������ڡ����ڼ�����Ϣ��
����������ڣ�
���� Calendar calendar = Calendar. getInstance();
���� ����
���� int day = calendar.get(Calendar. DATE);
����������ڡ���ݡ����ڵĲ�����������ơ�
������Ҫע����ǣ�Calendar�б�ʾ�·ݵ����ֺ�ʵ�����1����1��������0��ʾ��2��������1��ʾ������12��������11��ʾ��

ʮ�š�J2ME��������ִ���ȫ����
�����ڳ���������������֣��ô��Ƚϣ����˹���������ȵȣ����������J2ME������������Ĳ�������һ���򵥵�����ϣ���Դ�����а�����
����J2ME��J2SE��ͬ������ʹ��Math���random������������֣�ֻ��ʹ��java.util����Random��������������֡�
����1������Random���͵Ķ���
         Random random = new Random();
���� Random random = new Random(10010010);
�������������Ǵ���Random����ķ�ʽ����һ��ʹ��Ĭ�Ϲ��췽���������µĴ���������ȫ�ȼۣ�
���� Random random = new Random(System. currentTimeMillis());
�����൱��ʹ�õ�ǰʱ����Ϊ�������������д�����
�����ڶ��ַ�ʽͨ���Լ���ָ���������������д�����
������ҿ��Ը�����Ҫʹ���������ַ�ʽ����һ�֡�
����2������������֣�
��������������������Ժ����ǾͿ�����������������ˣ�
�����������������
         int k = random.nextInt();
       ���������������
         long l = random.nextLong();
����3������ָ����Χ�����֣�
������������0-10֮���������֣�
         int k = random.nextInt();
���� int j = Math.abs(k % 10);
������������һ���������k��Ȼ����k��10ȡ�࣬���ʹ��Math���abs����ȡ����ֵ�����0-10֮���������֡�
�������0-15֮�������������ƣ�
         int k = random.nextInt();
���� int j = Math.abs(k % 15);
�������10-20֮���������֣�
         int k = random.nextInt();
���� int j = Math.abs(k % 10) + 10;

��ʮ����J2ME�ֻ������ʹ������
������J2ME�ֻ�����У�����ͨ��ʹ�������ࡪ��Font�ڵͼ��û������У���ø��õı���Ч������ô���ʹ��Font���أ�
�������ȣ������ֻ��豸�����ƣ��ֻ���֧�ֵ��������ͺ����ޣ�������J2ME��ֻ��ʹ���ֻ�֧�ֵ�Ĭ������������Font����������Ǵ���Font��Ķ���ʱʹ�õķ�����
          getFont(int face,int style,int size);
���磺
          Font font = Font.getFont(Font.FACE_SYSTEM,Font.STYLE_BOLD,Font. SIZE_MEDIUM);
����������һ����������ֻ��ʹ��ϵͳ���õ���ֵ����Щ��ֵ����Ĵ�С�ڲ�ͬ���ֻ��Ͽ��ܲ�ͬ������������е�����������ȡֵ����ϸ�Ľ��ܣ�
����face����ָ�������ۣ����ȡֵ��
����FACE_MONOSPACE�����ȿ�����
����FACE_PROPORTIONAL������������
����FACE_SYSTEM����ϵͳ����
����style����ָ�������ʽ�����ȡֵ��
����STYLE_BOLD��������
����STYLE_ITALIC����б��
����STYLE_PLAIN������ͨ
����STYLE_UNDERLINED�����»���
����STYLE_BOLD | STYLE_ITALIC������б��
����STYLE_UNDERLINED | STYLE_BOLD�������»��ߴ���
����STYLE_UNDERLINED | STYLE_ITALIC�������»���б��
����STYLE_UNDERLINED | STYLE_ITALIC | STYLE_BOLD�������»��ߵĴ�б��
����size����ָ����Ĵ�С�����ȡֵ��
����SIZE_SMALL����С
����SIZE_MEDIUM������
����SIZE_LARGE������
����ͨ������Ĳ�����ֵ��������ϳ�����Ҫ���������
����������һЩ���õ����������
����1. ���ϵͳ��Ĭ�����壺
          Font font = Font.getDefaultFont();
����2. ��panit�����ڲ�������Graphics����������Ϊg�����õ�ǰ����ķ����ǣ�
          Font font = g.getFont();
����3. ��panit�����ڲ�������Graphics����������Ϊg�������õ�ǰ����ķ����ǣ�
          g.setFont(font);
��������fontΪ�㹹��õ��������
����4. ��MIDP2.0�У�List��������ÿ�е������ʽ�������ǣ�
          list.setFont(0,font);
����������Ĵ����ǽ�list�еĵ�һ������Ϊfont���͵����塣

��ʮһ����J2ME�ֻ����򿪷���ʹ����ɫ
������J2ME�ֻ����������У���Ҫ�����õ���ɫ�����л��ƣ���ǿ����ı���Ч��������ͽ���һ�����ʹ����ɫ��
��������J2ME�����Ƚϼ򵥣�����û��ʵ��ר�ŵ���ɫ�࣬��ֻ��ʹ��RGB�ĸ�����������ɫ������򵥽���һ��RGB�ĸ����ɫ���ɺ�(Red)����(Green)����(Blue)��ԭɫ��ɵģ����Կ���ʹ����������ɫ�����������һ�־������ɫ������R��G��B��ÿ����ֵ��λ��0-255֮�䡣�ڱ����ɫ��ʱ�򣬼�����ʹ��������������Ҳ����ʹ��һ����ʽ��0X00RRGGBB������ʽ��ʮ���������������ǳ�����ɫ�ı����ʽ��
������ɫ��(255,0,0)��0x00FF0000
������ɫ��(0,255,0)��0x0000FF00
������ɫ��(255,255,255)��0x00FFFFFF
����������ɫҲ����ͨ������ķ�ʽ��ϳ�����
����֪������ɫ�ı�﷽ʽ�Ժ�����������һ�������J2ME������ʹ����ɫ���漰�ķ�������Graphics���У������¼�����
����1.getColor()��
������õ�ǰʹ�õ���ɫ������ֵ��0x00RRGGBB��ʽ�����֡����磺
          int color = g.getColor();
��������gΪGraphics���͵Ķ���
����2.setColor(int RGB)��
��������ʹ�õ���ɫ�����磺
          g.setColor(0x00ff0000);
����3.setColor(int red, int green, int blue)
����������ķ�������һ�������磺
          g.setColor(255,0,0);
������������Graphicsʹ�õ���ɫ�Ժ��ٽ��л��Ƶ�ʱ�򣬾Ϳ��Ի���ָ������ɫ�ˡ�

��ʮ������J2ME����Ӧ���л�ÿͻ��˵��ֻ�����
������J2ME���򿪷������У�Ϊ��һ������Ҫ��������Ҫ������û����ֻ����룬�����������ȴ�ڱ�׼��J2ME�����û���ṩ��
������ʹ���й��ƶ���CMWAP��ʽ��������ʱ���й��ƶ��Ὣ�û����ֻ��������һ������Ϊx-up-calling-line-id��ͷ��Ϣ�У�����ͨ����ȡ��ͷ��Ϣ������û����ֻ����룬����������£�
          String usermphone = http.getHeader("x-up-calling-line-id");
��������http��HttpConnction���͵Ķ���

��ʮ����ʹ��J2ME�����ֻ�����Ϣ
�����ڳ����У����Ͷ���Ϣ�ķ�ʽһ�������֣�
����1�� ʹ�ó����������Ϸ��Ͷ���Ϣ�����������վ�Ķ���ҵ�����ַ�ʽ��ͨ��������Ϣ���͸���Ӫ�̵����ط�������Ȼ��ͨ����Ӫ�̵����緢�͸��ֻ���
����2�� �ڼ�����У�ͨ�����������ӵ��ֻ���Ȼ��ͨ���ֻ������Ͷ���Ϣ�����ַ�ʽ��ͨ��ʹ��ATָ����ʵ�֡��������ֻ���ATָ������������µ�ַ�ҵ���http://mobilityworld.ericsson.com.cn/development/download_hit.asp
����3�� ͨ�����ֻ������еĳ��������Ͷ���Ϣ��������Ǳ���ʵ�ֵķ�ʽ��
������J2ME�У�����뷢�Ͷ���Ϣ����Ҫʹ��WMA����MIDP2.0���Ѿ�������MIDP1.0�п���ͨ�������ṩ����չAPIʵ�֣���WMA��������һ����
       ������ʹ��WMA��ָ���ֻ����뷢�Ͷ���Ϣ��һ���������ܼ򵥡���ȻWMAҲ�ṩ�������ķ�ʽ�����͸�������ݡ�

// SMSUtil.java
package my.util;
import javax.wireless.messaging.*;
import javax.microedition.io.*;
/**
* �����ı�����Ϣ�ķ���
*/
public class SMSUtil
{
      /**
      * ��ָ�����뷢�Ͷ���Ϣ
      * @param content ����Ϣ����
      * @param phoneNumber �ֻ�����
      * @return ���ͳɹ�����true�����򷵻�false
      */
      public static boolean send(String content,String phoneNumber)
      {
            //����ֵ
            boolean result = true;
            try
            {
                   //��ַ
                   String address = "sms://+" + phoneNumber;
                   //��������
                   MessageConnection conn = (MessageConnection)Connector.open(address);
                   //���ö���Ϣ����Ϊ�ı�������Ϣ���ı��Ͷ�������������
                   TextMessage msg = (TextMessage)conn.newMessage(MessageConnection.TEXT_MESSAGE);
                   //������Ϣ����
                   msg.setPayloadText(content);
                   //����
                   conn.send(msg);
            }
            catch( Exception e )
            {
                   result = false;
                   //δ����
            }
            return result;
      }
}

��ʮ�ġ�ʹ�ü򵥵�J2ME�������MIDlet����������
������MIDlet����ѧϰ�У�����������һ���Ƚϳ���ĸ����ʵ�������ھ���һ���򵥵Ĺ涨���涨��MIDlet�е�ÿ��������ʲôʱ��ϵͳ���á�������һ��ʾ�����룬��ÿ���������ڲ������һ����䣬���Ը��ݳ��������������֤�����������õ�˳�򣬾���������£�


//�ļ�����LifeCircleMIDlet.java
import javax.microedition.midlet.*;
/**
* ����MIDlet����������
*/
public class LifeCircleMIDlet extends MIDlet
{
      /**
      * Ĭ�Ϲ��췽��
      */
      public LifeCircleMIDlet()
      {
            System.out.println("Ĭ�Ϲ��췽��");
      }
      /**
      * ��������
      */
      public void startApp()
      {
            System.out.println("startApp����");
      }
      /**
      * ��ͣ����
      */
      public void pauseApp()
      {
            System.out.println("pauseApp����");
      }
      /**
      * ���ٷ���
      * @param b
      */
      public void destroyApp(boolean b)
      {
            System.out.println("destroyApp����");
      }
}
������J2WTK�����иó���ʱ������ʹ��������еġ�MIDlet���˵��е���ͣ�ͻָ��˵���ģ����ͣ�¼���

��ʮ�塢ʹ��OTA��������ĳ���
����������֪��J2ME���򷢲�����ʽ��Ҫ�У�OTA�������ߴ��䡢�������������ȡ������˵˵���ͨ��OTA��������ĳ���
����OTA��Over The Air�ļ�д��Ҳ����ͨ���������أ�������Ҫ�ķ�����ʽ֮һ�����ڵİٱ��䶼�ǲ���������ʽ��
����ʹ��OTA������������Ҫ���¼������裺
����1�������WEB����������Ӷ���jad��jar�ļ���MIME֧�֡�
������׺��:jad
����MIME����:text/vnd.sun.j2me.app-descriptor
������׺��:jar
����MIME����:application/java-archive
����2������WMLҳ�棺
�����������jar�ļ���test.jad������򵥵�����ҳ���ǣ�
����<?xml version="1.0"?>
����<!DOCTYPE wml PUBLIC "-//WAPFORUM//DTD WML 1.3//EN"
����"http://www.wapforum.org/DTD/wml13.dtd">
����<wml>
����<card id="card1" title="Download Midlet">
����<a href="test.jad">test</a>
����</card>
����</wml>
��������Խ����ϴ��뱣����WEB�������ϣ����籣��Ϊtext.wml
����3���޸�jad�ļ���
������jad�ļ������ӡ�MIDlet-Jar-URL: http://domain/directory/test.jar
�������е�http://domain/directory/test.jarΪ���jar�ļ���·����
����������������ã���Ϳ��Խ����wmlҳ��·����Ϊ���WAP����ҳ�淢���ˡ��û�ֻ��Ҫ���ֻ����������·���Ϳ��Է��ʺ�������ĳ����ˡ�












2007/1/13
J2ME��ʾϵͳʱ��

J2ME�����Ǵ�MIDlet�࿪ʼִ��,MIDlet��J2ME��Ŀ�ļ�������ļ���Ҳ�Ǳ���ġ�
Display��һ��ϵͳ�豸��ʾ������Ĺ�������,ÿһ��MIDlet��������һ��Display.
Display����һЩ��Ա����ȥ��ȡϵͳ���Ժ���Ӧ��ʾ��ϵͳ�豸�Ķ��������

���濴һ���򵥵����ӣ�

/**
 * DisplayDate.java �ó���������ȡ��ǰϵͳʱ�䲢��ʾ����
 */
package zieckey.j2me.study;

import java.util.Calendar;

import javax.microedition.lcdui.Display;
import javax.microedition.lcdui.TextBox;
import javax.microedition.lcdui.TextField;
import javax.microedition.midlet.MIDlet;
import javax.microedition.midlet.MIDletStateChangeException;

/**
 * @author zieckey
 */
public class DisplayDate extends MIDlet
{

	private Display	display;

	protected void startApp () throws MIDletStateChangeException
	{
		display = Display.getDisplay ( this );// ��ȡϵͳ�豸��Display����

		// ����һ���ı������TextBox�����������ʾ�ı�
		// ���캯��������Calendar.getInstance ( ).getTime().toString ( )����
		// �ö�����ϵͳʱ���Ӧ���ַ���
		TextBox textbox = new TextBox ( "Display data and time!", Calendar
				.getInstance ( ).getTime ( ).toString ( ), 256, TextField.ANY );

		// ��textbox����Ϊ��ǰ��ʾ�����
		display.setCurrent ( textbox );
	}

	protected void destroyApp ( boolean arg0 ) throws MIDletStateChangeException
	{
	}

	protected void pauseApp ()
	{
	}
}

��Ҫ˵�����ǣ���ȻCalendar�̳���Object��Ҳ��toString()������
�������ֱ�ӵ��� Calendar.getInstance ( ).toString ( )
������һ��string�Ͳ�����TextBox�������ܵõ�����Ԥ����ʱ���ַ�����
����һЩ�й�j2me��sun��˾��վ��Ϣ������ܿ�����Calendar�����ṩtoString������
�������һ������Ҫ�Ľ�ѵ����Ҫ������ͬ�����MIDP������J2SE�������һ����

�����ٿ���MIDP��֧�ֵ�ʱ����������������룺
/**
 * DisplayDate.java �ó���������ȡ��ǰϵͳʱ�䲢��ʾ����
 */
package zieckey;

import java.util.Calendar;
import java.util.TimeZone;

import javax.microedition.lcdui.Display;
import javax.microedition.lcdui.TextBox;
import javax.microedition.lcdui.TextField;
import javax.microedition.midlet.MIDlet;
import javax.microedition.midlet.MIDletStateChangeException;

/**
 * @author zieckey
 */
public class DisplayDate extends MIDlet
{

	private Display	display;

	protected void startApp () throws MIDletStateChangeException
	{
		display = Display.getDisplay ( this );// ��ȡϵͳ�豸��Display����

		// ����һ���ı������TextBox�����������ʾ�ı�
		// ���캯��������Calendar.getInstance ( ).getTime().toString ( )����
		// �ö�����ϵͳʱ���Ӧ���ַ���
		TextBox textbox = new TextBox ( "Display data and time!",
				Calendar.getInstance ( ).getTime ( ).toString ( ), 256, TextField.ANY );

		//�õ�ϵͳȱʡ��ʱ��
		String[] timeZoneList = TimeZone.getAvailableIDs ( );
		for( int i=0;i<timeZoneList.length;i++)
		{	//���뵽�ı������textbox��
			textbox.insert ( "\n" + timeZoneList[i], textbox.getCaretPosition ( ) );
		}

		// ��textbox����Ϊ��ǰ��ʾ�����
		display.setCurrent ( textbox );
	}

	protected void destroyApp ( boolean arg0 ) throws MIDletStateChangeException
	{
	}

	protected void pauseApp ()
	{
	}
}

����֪���ֻ���һ��������һ���˳���ť���˳��������
��ô��������ʵ��������ܣ�

/**
 * DisplayDate.java �ó�������ʵ��ͨ��һ���˳���ť���ر��������
 */
package zieckey;

import java.util.Calendar;
import java.util.TimeZone;

import javax.microedition.lcdui.Command;
import javax.microedition.lcdui.CommandListener;
import javax.microedition.lcdui.Display;
import javax.microedition.lcdui.Displayable;
import javax.microedition.lcdui.TextBox;
import javax.microedition.lcdui.TextField;
import javax.microedition.midlet.MIDlet;
import javax.microedition.midlet.MIDletStateChangeException;

/**
 * @author zieckey
 */
public class DisplayDate extends MIDlet implements CommandListener
{

	private Display	display;
	private Command cmdExit;
	private TextBox textbox;

	public DisplayDate ()
	{
		display = Display.getDisplay ( this );// ��ȡϵͳ�豸��Display����
		cmdExit = new Command ( "Exit",Command.SCREEN, 2 );//�Ըò˵�����ӦӦ�õ���ǰ������Ļ
	}

	protected void startApp () throws MIDletStateChangeException
	{

		// ����һ���ı������TextBox�����������ʾ�ı�
		// ���캯��������Calendar.getInstance ( ).getTime().toString ( )����
		// �ö�����ϵͳʱ���Ӧ���ַ���
		textbox = new TextBox ( "Display data and time!",
				Calendar.getInstance ( ).getTime ( ).toString ( ), 256, TextField.ANY );

		//�õ�ϵͳȱʡ��ʱ��
		String[] timeZoneList = TimeZone.getAvailableIDs ( );
		for( int i=0;i<timeZoneList.length;i++)
		{	//���뵽�ı������textbox��
			textbox.insert ( "\n" + timeZoneList[i], textbox.getCaretPosition ( ) );
		}


		textbox.addCommand ( cmdExit );
		textbox.setCommandListener ( (CommandListener)this );

		// ��textbox����Ϊ��ǰ��ʾ�����
		display.setCurrent ( textbox );
	}

	protected void destroyApp ( boolean arg0 ) throws MIDletStateChangeException
	{
	}

	protected void pauseApp ()
	{
	}

	public void commandAction ( Command cmd, Displayable arg1 )
	{
		// �Ը��������Ӧ
		if ( cmd == cmdExit )
		{
			try
			{
				destroyApp ( true );
			} catch ( MIDletStateChangeException e )
			{
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			notifyDestroyed ( );
		}
	}
}









2007/1/14

J2ME���ø���

���ý���������ʱ��������Ϊһ��������һ���������ض������豸�ϵ��ض� JVM����Ȼ�������ڽ����������������ã�����ǰ J2ME �����������ã�

���������豸���� (CLDC) �ر��� KVM һ�������ڴ����޵� 16 λ�� 32 λ�豸���������ڿ���С�� J2ME Ӧ�ó�������ã�������������ӿ����ĽǶ����������Ĵ�С���������� CDC ����Ȥ��������ս�ԡ�CLDC ͬʱ�������ڿ�����ͼ����Ӧ�ó�������á� Palm ���Ա���һ������СӦ�ó����С�������豸��ʾ�������ǽ��� J2ME ����һ����������� CLDC��

�����豸���� (CDC) �� C ����� (CVM) һ��ʹ�ã�����Ҫ���ڴ泬�� 2 �׵� 32 λ��ϵ�ṹ�����������ӻ����б��������豸��һ��ʾ������Ȼ�Ժ����ǽ��� CDC API һ���м�Ҫ���� CDC�����������ڱ��̵̳ķ�Χ�ڡ�

������

�����������Ӧ�ó�����֧�ֵ��豸���͡��ر�أ����� J2ME ����������ض���������������豸��ĳ�����á�����������õĶ������Ѿ�Ϊ J2ME ���������ּ��KJava ���ƶ���Ϣ�豸��� (MIDP)������Ҳ�������� CDLC �ϡ������ּ��������С���豸��

��һ�ָ�Ҫ������������������洴���Լ��ļ�����ָ�Ҫ���Ҳ��Ϊ�������ɹ� CDC ʹ�á�Ȼ�����ڱ��̳��У�����ֻ�ص���ܽ����� CLDC ������������С���豸�ļ��

���ǽ��ں�����½�������������Щ�������ʹ�� KJava �� MIDP ����һЩʾ��Ӧ�ó���

J2ME Ŀ���豸

ʹ�� CLDC ������ J2ME Ӧ�ó����Ŀ���豸ͨ����������������

�ɹ� Java ƽ̨ʹ�õ� 160 �� 512 ǧ�ֽڵ����ڴ�
�������ޣ������ǵ�ع���
������ͨ�ԣ����������ߵġ���һ�µ����Ӳ��Ҵ�������
�û��ӿڻ��ң��̶Ȳβ�룻��ʱ������û�нӿ�
һЩ CLDC ֧�ֵ��豸���������ߵ绰��Ѱ���������������������� (PDA)���Լ�С������֧���նˡ�

���� Sun Microsystems��CDC ��Ŀ���豸ͨ����������������

ʹ�� 32 λ������
2 ���ֽڻ����ɹ� Java ƽ̨ʹ�õ����ڴ�
�豸Ҫ��� Java 2 ����Ƥ�顱�������ȫ������
������ͨ�ԣ����������ߵġ���һ�µ����Ӳ��Ҵ�������
�û��ӿڻ��ң��̶Ȳβ�룻��ʱ������û�нӿ�
һЩ CDC ֧�ֵ��豸��������פ���ء����ܵ绰��ͨѶ����PDA�������������õ��������������ն��Լ���������ϵͳ��


��ƿ���С���豸Ӧ�ó���Ҫע�������

ΪС���豸����Ӧ�ó�����Ҫ������ƽ׶��ƶ�ĳ�ֲ��ԡ�������ڿ�ʼ��д����֮ǰ��ս���Ե�ΪС���豸���Ӧ�ó��������޷����ǵ����е� "gotchas" ���ڿ���Ӧ�ó���֮ǰ����������һ����ʹ��Ĺ�����

������һЩ���Կ��ǵ���Ʋ��ԣ�

���ֳ���򵥡���ȥ����Ҫ�Ĺ��ܣ�������ܵĻ������������ɶ����ġ���Ҫ��Ӧ�ó���

����ԽСԽ�á���һ������еĿ�������˵Ӧ�����Զ��׼��ġ�ԽС�ĳ���ռ�õ��豸�ڴ�Խ�٣����һ��ѵİ�װʱ��Խ�١��ɿ��ǽ����� Java Ӧ�ó���������Ϊѹ���� Java ���� (jar) �ļ���

����ʱռ�����ٵ��ڴ档Ϊ�����ܼ�������ʱռ�õ��ڴ棬ʹ�ñ������ʹ���������͡�ͬʱ�������������ռ�������Ӧ����ʹ�������ʱ�����������ÿգ���������Ч�����ڴ档����һ�ּ�������ʱ�����ڴ�ķ�����ʹ�á����ԡ�ʵ���������ڱ���ʱ�ŷ����������һЩ����С���豸�Ϲ����ͷ�ֵ�ڴ�ʹ�õķ����п����ͷ���Դ������ʹ�ö����Լ������쳣��



��ƿ����ƶ��豸Ӧ�ó����ע������ �� 3 ҳ���� 6 ҳ��




�����ƶ��豸Ӧ�ó���Ĺ���������ǰ���ἰ�Ŀ���С���豸����ͬ��������ٱ��롣�����Ǽ��һ�¿����ƶ��豸Ӧ�ó���ʱ�ɿ��ǵ�һЩ��ƽ��飺

�÷��������󲿷ֵĹ������������Խ�ǿ������ŵ��������ϣ��÷�����Ϊ������Щ���������ƶ��豸�����������ٵļ��㹤�������÷����������صĹ�������Ȼ����Ϊ�俪��Ӧ�ó�����ƶ��豸���豸���ӵ��������ϵ����׳̶Ⱥ�Ƶ������ҪӰ�졣

������ѡ�������ԡ�J2ME ��Ȼ���ڳɳ��ڣ����ܻ�������õ�ѡ�񡣸���������Ҫ��ѡ������������������ԣ��� C++�����ܻ���á�



����ע������ �� 4 ҳ���� 6 ҳ��

Ϊ���ܶ����롣������һЩ�Ի����������ΪĿ��ı��뷽����

ʹ�þֲ����������ʾֲ������ȷ������Ա���졣

�����ַ����������ַ������������ή�����ܣ����һ�����Ӧ�ó�����ڴ��ֵռ������


ʹ���̣߳�����ͬ�����κ�����ʱ�䳬�� 1/10 ��Ĳ�������Ҫһ���������̡߳�����ͬ��ͬ����������ܡ�

ʹ��ģ����ͼ������ (MVC) ����ģ�͡�MVC �������п�����ʾ���߼����������






����ע������ �� 5 ҳ���� 6 ҳ��

ͬ������ Java Ӧ�ó���һ�������ڴ���Ͳ���Ӧ�ó���֮ǰҪ�Ƚ��б��롣�������� J2ME������Ȼʹ�� J2SE ������������Ҫ���ʵ���ѡ�������е��á�

�ر�ģ�����Ҫʹ�� -bootclasspath ѡ����ָʾ������ʹ�� J2ME �࣬������ J2SE �ࡣ��Ҫ�ڱ������� CLASSPATH �����������ࡣ��������������ʱ������Ϊ���� CLASSPATH ����ʲô���������������Զ����� J2SE �ĺ����ࡣ���仰˵�����������޷������ض� J2ME ������ȱ�ٵ���򷽷�����������ڳ�������Ӧ�ó���ʱ��������ʱ����



����Ͳ���ע������ �� 6 ҳ���� 6 ҳ��

���� J2ME ��Ϊ�ڴ����޵�С���豸��Ƶġ��󲿷ֳ��õ� Java ��ǰ��֤�Ѿ���������г�ȥ���γ�һ����С�ĸ������򡣽����������֮ǰ��ǰ��֤ J2ME Ӧ�ó���ͺ��б�Ҫ��������ʱ�ḽ��һ�������ȷ�����������ǰ��֤֮��û�иı����

����ϸ�ִ����ǰ��֤���߼�������ȷ���������ǹ��߰���CLDC �ṩһ����Ϊ��ǰ��֤��������ʵ�ó������ܹ�����ʵ�ʵ���֤���ҿ��԰�һЩ�������Ϣ���뵽���ļ���ȥ��MIDP ʹ�����߹��߰������ֹ��߰��ṩһ�� GUI ���ߣ�Ҳ�ɴ��������������ֹ��ߡ�

������ȡ������Ҫ�����ƽ̨��Ӧ�ó��������һ���ʺ� J2ME �豸���͵ĸ�ʽ���д�������ã����������������



J2ME ������ʲô�� �� 1 ҳ���� 5 ҳ��

����ǰ����ѧ�����ý���������ʱ��������Ϊһ�׺������һ���������ض������豸�ϵ��ض��� JVM����Ҳ����ѧ�� J2ME ���������������� CLDC �� CDC��

Sun �ṩ�� J2ME �������ʺϲ�ͬ��ε��г������ -- CLDC �ʺ�С���豸���� CDC �ʺϴ����豸��J2ME �������Ա���̬������Ϊ�ṩ����Ӧ�ó�������Ҫ�Ļ����������ÿ����Ƿ�Ϊ�豸�ṩ�����и�Ӧ�ó������������ Java �����⡣����ƽ̨����Ӧ�ó������Ϳ⡣�����������ϵķ��������ִ�����ù�����

J2ME �����ʲô? �� 1 ҳ���� 4 ҳ��

����������ǰ��̳����ἰ�ģ�һ�����������֧���豸�����͡����磬�ƶ���Ϣ�豸��� (MIDP)�������˷��ѵ绰���ࡣ����һЩ�ض�����������J2ME ������������������豸��ʹ�á��Ѿ�Ϊ J2ME �������������KJava �� MIDP �����Ƕ������� CLDC ֮�ϡ�KJava �� MIDP ���� CLDC ��С���豸�������

������������õĶ��������ڼ�����ض�������Ӧ�ó�����豸�Ĵ�С���ڴ�������������ԣ�ĳ���������ĳ���ض�������������ġ�

�ڸ�Ҫ����ϣ������Դ����Լ��ļ�����ָ�Ҫ���Ҳ��Ϊ������������ CDC Ҳ�ǿ��õġ�Ȼ�����ڱ��̳̺ͱ����У����ǽ�ֻ�ص�ѧϰ������ CLDC �ϵ� KJava �� MIDP ���

��� 1��KJava �� 2 ҳ���� 4 ҳ��

KJava �ǹ� Sun ��˾���еļ�������� KJava API��KJava ������� CLDC ���õĶ�����KJava �������KVM�����׼�� J2SE ���������������ͬ���ֽڴ�������ļ���ʽ��

KJava ����һ���ض��� Sun �ġ������� Palm ����ϵͳ�ϵ� API����� KJava API �� J2SE �����Ӵ����߰� (AWT) �кܶ�ط�������ͬ��Ȼ��������������һ����׼�� J2ME �������������������� com.sun.kjava�����Ժ�Ľ̳��п���һЩʾ��Ӧ�ó���ʱ��ѧ��������� KJava API ��֪ʶ��



��� 2: MIDP �� 3 ҳ���� 4 ҳ��

MIDP �ʺ�������ѵ绰��Ѱ�������ƶ��豸��MIDP �� KJava һ����Ҳ�ǽ����� CLDC ֮�ϵģ������ṩһ����׼������ʱ�������������ն��û��豸�϶�̬�ز����µ�Ӧ�ó���ͷ���

MIDP ��һ�������ġ�Ϊ�ƶ��豸��ƵĹ�ҵ��׼�����������ĳ���ض����̼ҡ������ƶ�Ӧ�ó��򿪷���˵������һ�������ġ���֧�ֵĻ�����

MIDP ���������������ǰ�� 3 ���Ǻ��� CLDC ���������� 3 ���ض��� MIDP ������������ǽ��ں���Ľ̳�������ÿ���������

java.lang
java.io
java.util
javax.microedition.io
javax.microedition.lcdui
javax.microedition.midlet
javax.microedition.rms


UI ���ע������ �� 2 ҳ���� 6 ҳ��

MIDP ����һ���ͼ��� UI API ��һ���߼��� UI API���ͼ��� API ��������ȫ����һ���豸����ʾ����Ҳ�������ԭʼ����ָ���¼���Ȼ����ʹ�õͼ� API ʱ�� û�п��õ��û�����ؼ���Ӧ�ó�����뾫ȷ�ػ��Ƴ���ť���������еĿؼ���

�෴���߼� API �ṩ�򵥵��û�����ؼ�������ֱ�ӷ���ԭʼ�������¼�����ʾ����������ʾ���ĳߴ�� MIDP �豸���뷽���Ĳ��죬�ؼ��Եúܳ���MIDP ��ʵ��ȷ���˻��ƿؼ��ķ�����Ҳȷ������ι����û����롣

MIDP API �� 3 ҳ���� 6 ҳ��

MIDP �����ĸ����� CLDC ����� (java.lang��java.io��java.util �� javax.microedition.io)���������������ض��� MIDP ���������

javax.microedition.lcdui
javax.microedition.midlet
javax.microedition.rms
���ǽ��ڱ��µĺ��沿����ϸ�����ض��� MIDP ����������������µ������֮�⣬MIDP ������� CLDC �����������ĸ����࣬������ʾ��

java.util.Timer -- ����Ϊ��̨�߳��н���Ҫִ�е�����ȷ��ʱ�䡣


java.util.TimerTask -- �� java.util.Timer ��ʹ�ã�����Ϊ��̨�߳����Ժ��ִ�ж�������


javax.microedition.io.HttpConnection -- һ���ӿڣ�Ϊ HTTP ���Ӷ����Ҫ�ķ����ͳ�����

java.lang.IllegalStateException -- һ�� RuntimeException�� ָ���ڲ��Ϸ��򲻺��ʵ�ʱ���Ѿ����õ�һ��������

MIDlet ����  �� 4 ҳ���� 6 ҳ��

MIDlet ��һ�� Java �࣬����չ�� javax.microedition.midlet.MIDlet �����ࡣʵ�� startApp()��pauseApp()�� destroyApp()��������Щ���������� J2SE �� java.applet.Applet ���е� start()��stop()�� destroy()������

�������� javax.microedition.midlet.MIDlet ���� MIDlet ��֮�⣬һ�� MIDP Ӧ�ó���ͨ������������һЩ�࣬��Щ���������ǵ���Դһ�𱻴����Ϊ jar �ļ� -- ��֮Ϊ MIDlet �׼���һ�� MIDlet �׼��еĲ�ͬ MIDlet �ܹ��� jar �ļ�����Դ�����ܲ�ͬ�׼��е� MIDlets ����ֱ���໥���á�

MIDlet ��Ӧ�ó������������������ֿ��ܵĴ���״̬ -- ����״̬����ͣ״̬������״̬������״̬����������������ʾ�ģ���ζ�� MIDlet ���������С�����״̬ʼ�� startApp ����������ʱ������ͣ״̬�У�MIDlet ���е�������Դ�����ͷţ�������׼�����ٴα����С����� notifyPaused ����ʱ��MIDlet ������ͣ״̬��������״̬�У�MIDlet �Ѿ����õؽ�������رգ��ͷ����е���Դ���ȴ��ŷ����������Ĵ�������ͨ�� notifyDestroyed ���������õġ�

�ڽ���������ҳ�У���������һ���򵥵� HelloWorld MIDlet��


HelloWorld MIDlet �� 5 ҳ���� 6 ҳ��

��ʹ�� KJava HelloWorld Ӧ�ó���һ������� MIDlet Ҳ���� MIDP �豸����ʾ������ʾ "Hello World!" �� Exit ��ť�����¸ð�ť����ֹӦ�ó���

HelloWorld.java �ļ�������Ĵ����п�ʼ����Щ�����е����Ժ���� HelloWorld ����ʹ�õ���:


      import javax.microedition.midlet.MIDlet;
      import javax.microedition.lcdui.Command;
      import javax.microedition.lcdui.CommandListener;
      import javax.microedition.lcdui.Display;
      import javax.microedition.lcdui.Displayable;
      import javax.microedition.lcdui.Form;

���� HelloWorld ����һ�� MIDP Ӧ�ó�������չ�� MIDlet����Ҳʵ�� CommandListener �ӿ��������¼���


      public class HelloWorld extends MIDlet implements CommandListener

����ķ�����һ��ȱʡ�������������һ���±����������ʼ���ؼ���Ȼ����ʾ������


      private Form form;

      public HelloWorld()
      {
          // Create a new form on which to display our text
         form = new Form("Test App");

         // Add the text "Hello World!" to the form
         form.append("Hello World!");

         // Add a command button labeled "Exit"
         form.addCommand( new Command( "Exit", Command.EXIT, 1 ) );

         // Register this object as a commandListener
         form.setCommandListener( this );
      }

���� startApp() ��������Ӧ�ó�����СӦ�ó������������������ MIDle ��һ��ִ���������ܻᱻ���ö�Ρ���� MIDlet ��ͣ��pauseApp() ���ᱻ���á�Ҫ�������� MIDlet������� startApp()������ִ��һ�ε�����ʼ������Ӧ�÷����ڹ�������У�


      public void startApp()
      {
         // Get a reference to the display, and show the form
         Display display = Display.getDisplay(this);
         display.setCurrent( form );
      }

pauseApp() ������ʹ�� MIDlet ������ͣ״̬���ڴ�Ӧ�ó����У���������ͣ״̬ʱ������ûִ���κβ���������������Ȼ��Ҫ�� MIDlet ��ʵ�� pauseApp ��������Ϊ���Ǹ� MIDlet ���еĳ��󷽷���


      public void pauseApp() { }

destroyApp() �����ã��ƻ��� MIDlet ��ʹ�䴦������״̬���ڴ�Ӧ�ó����У�����ͨ����������Ϊ null���ͷ��˶Ա������á�


      public void destroyApp(boolean unconditional)
      {
         form = null;
      }

commandAction() �������¼�������򣬱�����ʵ�� CommandListener �ӿڡ�Ŀǰ�����ƻ���Ӧ�ó���֪ͨӦ�ó��������� MIDlet �Ѿ���ɡ�


      public void commandAction(Command c, Displayable d)
         {
            // Destroy this MIDlet
            destroyApp(true);

            // Notify the application management software that this MIDlet
            // has entered the destroyed state
            notifyDestroyed();
         }



J2ME��̳й�ϵ(Package javax.microedition.lcdui)
class java.lang.Object
	|-->class javax.microedition.lcdui.Displayable
		|-->class javax.microedition.lcdui.Canvas
		|-->class javax.microedition.lcdui.Screen
			|-->class javax.microedition.lcdui.Alert
			|-->class javax.microedition.lcdui.Form
			|-->class javax.microedition.lcdui.List
						(implements javax.microedition.lcdui.Choice)
			|-->class javax.microedition.lcdui.TextBox
	|-->class javax.microedition.lcdui.Font
	|-->class javax.microedition.lcdui.Graphics
	|-->class javax.microedition.lcdui.Image
	|-->class javax.microedition.lcdui.Item
		|-->class javax.microedition.lcdui.ChoiceGroup
						(implements javax.microedition.lcdui.Choice)
		|-->class javax.microedition.lcdui.CustomItem
		|-->class javax.microedition.lcdui.DateField
		|-->class javax.microedition.lcdui.Gauge
		|-->class javax.microedition.lcdui.ImageItem
		|-->class javax.microedition.lcdui.Spacer
		|-->class javax.microedition.lcdui.StringItem
		|-->class javax.microedition.lcdui.TextField
	|-->class javax.microedition.lcdui.Ticker

J2ME�����Ǵ�MIDlet�࿪ʼִ��,MIDlet��J2ME��Ŀ�ļ�������ļ���Ҳ�Ǳ���ġ�
ÿ��MIDPӦ�ó�������ʱ�����û���������ı�����̨����Display�࣬
����Щ�û���������������̨�϶����ݡ�������ʾ�ġ���ɫ��
��������߼���ϵ����Щ�û�����ͱ������Ϊ Displayable ������࣬
��Щ�û�������ָ��ݲ�ͬ����������Ϊ���ࣺCanvas���Screen�ࡣ

Display��һ��ϵͳ�豸��ʾ������Ĺ�������,ÿһ��MIDlet��������һ��Display.
Display����һЩ��Ա����ȥ��ȡϵͳ���Ժ���Ӧ��ʾ��ϵͳ�豸�Ķ��������
һ�� Display �Ͻ���ֻ�ܷ���һ�� Displayable ����
��һ�� Displayable �����磺Canvas��Screen�Լ����ǵ����ࣩ��
Ҳ����˵ Display �ϵ� Displayable ����ֻ��һ��һ���ĳ��֡�

���濴��һ�����ӣ��쿴�ֻ���֧�ֵ�ɫ�ʣ�
/*
 * @(#)ColorDetectMIDlet.java 
 */
package zieckey.uistudy;

import javax.microedition.lcdui.Command;
import javax.microedition.lcdui.CommandListener;
import javax.microedition.lcdui.Display;
import javax.microedition.lcdui.Displayable;
import javax.microedition.lcdui.TextBox;
import javax.microedition.lcdui.TextField;
import javax.microedition.lcdui.Ticker;
import javax.microedition.midlet.MIDlet;
import javax.microedition.midlet.MIDletStateChangeException;

/**
 * �ó��������ж��ƶ��绰��Ļ��֧�ֵ�ɫ�ʣ� �жϺ󽫽����ʾ���ֻ���Ļ�ϡ�
 *
 * @author Zieckey
 * @version 07/12/29
 */

public class ColorDetectMIDlet extends MIDlet implements CommandListener
{
	private Display	display;
	private Command	exitCommand;

	public ColorDetectMIDlet ()
	{
		display = Display.getDisplay ( this );// ��ȡϵͳ�豸��Display����
		exitCommand = new Command ( "Exit", Command.SCREEN, 1 );// �Ըò˵�����ӦӦ�õ���ǰ������Ļ
	}

	protected void startApp () throws MIDletStateChangeException
	{
		// ����һ���ı������TextBox�����������ʾ�ı�
		TextBox textbox = new TextBox ( "", "", 256, TextField.ANY );
		// ����һ��Ticker����Ticker����Ļ�����ع�����ʾ"Color..."
		textbox.setTicker ( new Ticker ( "Color..." ) );
		textbox.addCommand ( exitCommand );
		textbox.setCommandListener ( (CommandListener)this );

		if ( display.isColor ( ) )
		{
			textbox.setTitle ( "֧�ֲ�ɫ" );
			textbox.setString ( "������ɫ: " + display.numColors ( ) + " �֡�" );
		} else
		{
			textbox.setTitle ( "��֧�ֲ�ɫ" );
			textbox.setString ( "������ɫ: " + display.numColors ( ) + " �֡�" );
		}

		// ��textbox����Ϊ��ǰ��ʾ�����
		display.setCurrent ( textbox );
	}

	protected void destroyApp ( boolean arg0 ) throws MIDletStateChangeException
	{

	}

	protected void pauseApp ()
	{

	}

	public void commandAction ( Command cmd, Displayable arg1 )
	{
		if ( cmd == exitCommand )
		{
			try
			{
				destroyApp ( true );
			} catch ( MIDletStateChangeException e )
			{
				e.printStackTrace ( );
			}
			notifyDestroyed ( );
		}
	}
}


Alert�����Ӧ�ã�
/*
 * @(#)ColorDetectMIDlet.java 
 */
package zieckey.uistudy;

import javax.microedition.lcdui.Alert;
import javax.microedition.lcdui.AlertType;
import javax.microedition.lcdui.Command;
import javax.microedition.lcdui.CommandListener;
import javax.microedition.lcdui.Display;
import javax.microedition.lcdui.Displayable;
import javax.microedition.lcdui.TextBox;
import javax.microedition.midlet.MIDlet;
import javax.microedition.midlet.MIDletStateChangeException;

/**
 * �ó�������ѧϰAlert�ؼ����÷���
 * ��ͬ��Alert���ͻᷢ����ͬ��������
 *
 * @author Zieckey
 * @version 07/01/19
 */
public class AlertsMIDlet extends MIDlet implements CommandListener
{
	private Display	display;
	private TextBox textbox;

	private Command	exitCommand;
	private Command	alarmCommand;
	private Command	confirmCommand;
	private Command	errorCommand;
	private Command	infoCommand;
	private Command	warningCommand;

	private Alert alarmAlert;
	private Alert confirmAlert;
	private Alert errorAlert;
	private Alert infoAlert;
	private Alert warningAlert;

	/**
	 * ���캯��
	 *
	 */
	public AlertsMIDlet()
	{
		display = Display.getDisplay ( this );// ��ȡϵͳ�豸��Display����
		exitCommand = new Command ( "Exit", Command.SCREEN, 1 );// �Ըò˵�����ӦӦ�õ���ǰ������Ļ

		alarmCommand = new Command ( "Alarm", Command.SCREEN, 2 );
		confirmCommand = new Command ( "Confirm", Command.SCREEN, 2 );
		errorCommand = new Command ( "Error", Command.SCREEN, 2 );
		infoCommand = new Command ( "Information", Command.SCREEN, 2 );
		warningCommand = new Command ( "Warning", Command.SCREEN, 2 );

		textbox = new TextBox ( "Main UI",
				"Please click the soft keys to choose a Alert to run....", 256, 0 );
		textbox.addCommand ( alarmCommand );
		textbox.addCommand ( confirmCommand );
		textbox.addCommand ( errorCommand );
		textbox.addCommand ( infoCommand );
		textbox.addCommand ( warningCommand );

		textbox.setCommandListener ( this );

		alarmAlert = new Alert("Alarm","This is an \"ALARM\" alert! ",null,AlertType.ALARM);
		confirmAlert = new Alert("Confirmation","This is an \"CONFIRMATION\" alert! ",null,AlertType.CONFIRMATION);
		errorAlert = new Alert("Error","This is an \"ERROR\" alert! ",null,AlertType.ERROR);
		infoAlert = new Alert("Info","This is an \"INFORMATION\" alert! ",null,AlertType.INFO);
		warningAlert = new Alert("Warning","This is an \"WARNING\" alert! ",null,AlertType.WARNING);

		alarmAlert.setTimeout ( 3000 );
		confirmAlert.setTimeout ( 3000 );
		errorAlert.setTimeout ( 3000 );
		infoAlert.setTimeout ( 3000 );
		warningAlert.setTimeout ( 3000 );

		display.setCurrent ( textbox );
	}

	protected void startApp () throws MIDletStateChangeException
	{

	}

	protected void destroyApp ( boolean arg0 ) throws MIDletStateChangeException
	{

	}

	protected void pauseApp ()
	{

	}

	public void commandAction ( Command cmd, Displayable arg1 )
	{
		if ( cmd == exitCommand )
		{
			try
			{
				destroyApp ( true );
			} catch ( MIDletStateChangeException e )
			{
				e.printStackTrace ( );
			}
			notifyDestroyed ( );
		}else if ( cmd == infoCommand )
		{
			display.setCurrent ( infoAlert );
		} else if( cmd == errorCommand )
		{
			display.setCurrent ( errorAlert);
		} else if( cmd == alarmCommand )
		{
			display.setCurrent ( alarmAlert );
		} else if( cmd == confirmCommand )
		{
			display.setCurrent ( confirmAlert );
		} else if( cmd == warningCommand )
		{
			display.setCurrent ( warningAlert );
		}
	}
}


CostomItem��
package zieckey.uistudy.customitem;

import javax.microedition.lcdui.Command;
import javax.microedition.lcdui.CommandListener;
import javax.microedition.lcdui.CustomItem;
import javax.microedition.lcdui.Display;
import javax.microedition.lcdui.Displayable;
import javax.microedition.lcdui.Font;
import javax.microedition.lcdui.Form;
import javax.microedition.lcdui.Graphics;
import javax.microedition.midlet.MIDlet;
import javax.microedition.midlet.MIDletStateChangeException;

/**
 * �ó���������ѧϰCostomItem���
 * ��Form����������ʾһ�����Ƶı��
 *
 * @author zieckey
 *
 */

public class CustomItenMIDlet2 extends MIDlet implements CommandListener
{

	protected void startApp () throws MIDletStateChangeException
	{
		Form form = new Form("UI����emo");
		form.append ( "����ϲ���ı�����ԣ�\n" );
		String[] strs = {"C","C++","Java","Visual C++","Borland C++"};
		form.append ( new Table(strs) );

		Command exitCommand = new Command ( "Exit", Command.EXIT, 2 );
		form.addCommand ( exitCommand );
		form.setCommandListener ( this );

		Display.getDisplay ( this ).setCurrent ( form );
	}

	protected void destroyApp ( boolean arg0 ) throws MIDletStateChangeException
	{

	}

	protected void pauseApp ()
	{
	}

	public void commandAction ( Command c, Displayable arg1 )
	{
		if ( c.getCommandType ( ) == Command.EXIT )
		{
			try
			{
				destroyApp ( true );
			} catch ( MIDletStateChangeException e )
			{
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			notifyDestroyed ( );
		}
	}

}

/**
 * ������һ�����Ƶı��
 * ����ͨ�����캯�����ַ��������ṩ����Ϣ������ʴ�С�ı��
 * @author zieckey
 *
 */
class Table extends CustomItem
{
	private String[]	elements;

	//���캯�������������ʱ��ʼ�����Ա����
	public Table ( String[] elements )
	{
		super ( "" );
		if ( null == elements && 0 == elements.length )
		{
			throw new IllegalArgumentException ( );
		}
		this.elements = new String[elements.length];
		System.arraycopy ( elements, 0, this.elements, 0, elements.length );
	}

	protected int getMinContentHeight ()
	{
		return ( Font.getDefaultFont ( ).getHeight ( ) + 1 ) * elements.length + 1;
	}

	protected int getMinContentWidth ()
	{
		return Font.getDefaultFont ( ).stringWidth ( "..." ) + 4;
	}

	// �������������ʾ�߶�
	protected int getPrefContentHeight ( int arg0 )
	{
		return getMinContentHeight ( );
	}

	// �������������ʾ���
	protected int getPrefContentWidth ( int arg0 )
	{
		int max = 0;
		for ( int i = 0; i < elements.length; i++ )
		{
			// �õ������ı����
			int w = Font.getDefaultFont ( ).stringWidth ( elements[i] );
			if ( max < w )
			{
				max = w;// �������ı���ȷŵ�max������
			}
		}
		return max;
	}

	protected void paint ( Graphics g, int w, int h )
	{
		// ʹ�ð�ɫ�����������
		g.setColor ( 0xffffff );
		g.fillRect ( 0, 0, w, h );
		g.setColor ( 0 );

		Font font = Font.getDefaultFont ( );
		int fontHeight = font.getHeight ( );//����߶�
		int lineHeight = fontHeight + 1;//�о�

		// ���Ʊ����ַ�������
		for ( int i = 0; i < elements.length; i++ )
		{
			g.drawLine ( 0, lineHeight * i, w - 1, lineHeight * i );
			String s = elements[i];
			int strWidth = font.stringWidth ( s );
			if ( strWidth > w - 4 )
			{
				do
				{
					s = s.substring ( 0, s.length ( ) - 1 );
					strWidth = font.stringWidth ( s );
				} while ( strWidth > w - 4 );
			}
			g.drawString ( s, 2, lineHeight * i + 1, Graphics.LEFT | Graphics.TOP );
		}
		g.drawRect ( 0, 0, w-1, h-1 );
	}
}




package zieckey.uistudy.customitem;

import javax.microedition.lcdui.Command;
import javax.microedition.lcdui.CommandListener;
import javax.microedition.lcdui.CustomItem;
import javax.microedition.lcdui.Display;
import javax.microedition.lcdui.Displayable;
import javax.microedition.lcdui.Form;
import javax.microedition.lcdui.Graphics;
import javax.microedition.midlet.MIDlet;

/**
 * �ó������ڴ�������ʾ�Լ�������Item����ʾһ��ͼ��
 *
 * @author zieckey
 */
public class CustomItemMIDlet extends MIDlet implements CommandListener
{
	public void startApp ()
	{
		Form form = new Form ( "CustomItemMIDlet" );
		form.append ( new MyCustomItem ( "MyCustomItem" ) );

		Command exitCommand = new Command ( "Exit", Command.EXIT, 0 );
		form.addCommand ( exitCommand );
		form.setCommandListener ( this );

		Display.getDisplay ( this ).setCurrent ( form );
	}

	public void pauseApp ()
	{
	}

	public void destroyApp ( boolean unconditional )
	{
	}

	public void commandAction ( Command c, Displayable s )
	{
		if ( c.getCommandType ( ) == Command.EXIT )
		{
			destroyApp ( true );
			notifyDestroyed ( );
		}
	}
}

class MyCustomItem extends CustomItem
{
	public MyCustomItem ( String title )
	{
		super ( title );
	}

	// CustomItem abstract methods.
	public int getMinContentWidth ()
	{
		return 100;
	}

	public int getMinContentHeight ()
	{
		return 60;
	}

	public int getPrefContentWidth ( int width )
	{
		return getMinContentWidth ( );
	}

	public int getPrefContentHeight ( int height )
	{
		return getMinContentHeight ( );
	}



	public void paint ( Graphics g, int w, int h )
	{
		g.drawRect ( 0, 0, w - 1, h - 1 );
		g.setColor ( 0x000000ff );
		int offset = 0;
		for ( int y = 4; y < h; y += 12 )
		{
			offset = ( offset + 12 ) % 24;
			for ( int x = 4; x < w; x += 24 )
			{
				g.fillTriangle ( x + offset, y, x + offset - 3, y + 6, x + offset
						+ 3, y + 6 );
			}
		}
	}
}


Form�ؼ�
package zieckey.uistudy;

import javax.microedition.lcdui.Command;
import javax.microedition.lcdui.CommandListener;
import javax.microedition.lcdui.Display;
import javax.microedition.lcdui.Displayable;
import javax.microedition.lcdui.Form;
import javax.microedition.lcdui.Item;
import javax.microedition.lcdui.ItemCommandListener;
import javax.microedition.lcdui.StringItem;
import javax.microedition.midlet.MIDlet;
import javax.microedition.midlet.MIDletStateChangeException;


/**
 * �ó�������ѧϰForm�ؼ����÷���
 * ����������Ӹ���Item��
 *
 * @author Zieckey
 * @version 1.0  07/01/21
 */
public class FormAndItemMIDlet extends MIDlet implements ItemCommandListener,CommandListener
{
	private Form	form;
	private Display	display;
	private StringItem	st1, st2, st3;
	private Command	exitCommand;
	private Command	buttonCommand;
	private Command	linkCommand;

	public FormAndItemMIDlet()
	{
		exitCommand = new Command ( "Exit", Command.SCREEN, 1 );// �Ըò˵�����ӦӦ�õ���ǰ������Ļ
		buttonCommand = new Command ( "BUTTON MODLE", Command.ITEM, 2 );//Command.ITEMģʽ����ʹ������Ӧ��ѡ����Ӧ��Item���
		linkCommand = new Command ( "HYPERLINK MODLE", Command.ITEM, 2 );

		st1 = new StringItem( "1","��ͨģʽ",StringItem.PLAIN);
		st2 = new StringItem( "2","��ťģʽ",StringItem.BUTTON);
		st3 = new StringItem( "3","����ģʽ",StringItem.HYPERLINK);

		//ΪBUTTON��HYPERLINKģʽ��StringItem��ť����Ĭ�ϵ� Command
		st2.setDefaultCommand ( buttonCommand );
		st3.setDefaultCommand ( linkCommand );
		//ע��ItemCommandListener������
		st2.setItemCommandListener ( this );
		st3.setItemCommandListener ( this );

		form = new Form("UI Demo");//�����ڳ�ʼ��
		form.append ( st1 );//���Item��Form��
		form.append ( st2 );
		form.append ( st3 );

		form.addCommand ( exitCommand );//��������ڵ�������Ӧ
		form.setCommandListener ( this );//ע�� Form �ļ�����

		if ( null == display )
		{
			display = Display.getDisplay ( this );
		}
		display.setCurrent ( form );
	}

	protected void startApp () throws MIDletStateChangeException
	{
		// TODO Auto-generated method stub

	}

	protected void destroyApp ( boolean arg0 ) throws MIDletStateChangeException
	{
		// TODO Auto-generated method stub

	}

	protected void pauseApp ()
	{
		// TODO Auto-generated method stub

	}

	public void commandAction ( Command cmd, Displayable arg1 )
	{
		if ( cmd == exitCommand )
		{
			try
			{
				destroyApp ( true );
			} catch ( MIDletStateChangeException e )
			{
				e.printStackTrace ( );
			}
			notifyDestroyed ( );
		}
	}

	//���ض���Item�ϵ�Command������󣬴˷����ͻᱻ����
	public void commandAction ( Command cmd, Item item )
	{
		if ( buttonCommand == cmd )
		{
			if ( st2 == item )
			{
				form.append ( "\n��ťģʽ��ѡ���ˣ�" );
			}
		} else if ( linkCommand == cmd )
		{
			if ( st3 == item )
			{
				form.append ( "\n����ģʽ��ѡ���ˣ�" );
			}
		}
	}
}



����MIDP2.0��CustomItem�࣬����J2ME�������(��1)
2����дһ�����й������ı��

       �������������㷨�������������

       ���ݸ߶� ch ����֪����������ʾ�߶�vh����֪�����������߶� sh��δ֪����

��������߶� ah ����֪���������ٶ�speed��δ֪�����������㹫ʽ��

       speed * ( ah �C sh ) = ch �C vh ------------- (1)

       ch/vh = ah/sh            --------------(2)

����(1)��(2) ���Եó���speed = ch/ah



ȫ��Դ�����£�



CustomTable.java

------------------------------------------------------


package com.jlw.customitem;
/***
 * @author JiangLiwen , danxy2008@163.com , 2006-11-7
 */

import javax.microedition.lcdui.*;

public class CustomTable extends CustomItem {
  /** ���������� */
  private int rows = 0;
  private int cols = 0;
  private int dx = 50;
  private int dy = 20;

  /** ������ɫ */
  private final static int titleColor[] = { 206, 223, 239 };
  private final static int rowsColor1[] = { 230, 230, 230 };
  private final static int rowsColor2[] = { 181, 227, 231 };

  /** ��ͷ���� */
  private String[] titles;

  /** ���������� */
  private String[][] datas;

  /** ������ʾ���ڴ�С */
  private final static int winX = 220;
  private final static int winY = 180;

  /** �Ƿ��г��ֹ����� */
  private boolean isscroll = false;

  /** ���ݻ�����ʼ���� */
  private int dataY = 0;

  /** �������ݸ߶� */
  private int ch = 0;

  /** ������ʾ�߶� */
  private int vh = 0;

  /** �������߶� */
  private int sh = 0;

  /** ����������߶� */
  private int ah = 0;

  /** ������ƫ���� */
  private int offset = 0;

  /** �������ٶ� */
  private int speed = 0;

  /** ��Ӧ�����¼� */
  boolean horz;



  /**
   * ���캯��
   * @param name , ����
   * @param ptitle , ��ͷ��һΩ���飩
   * @param pdata , ���������ݣ���Ω���飩
   */
  public CustomTable(String name, String[] ptitle, String[][] pdata) {
    super(name);
    cols = ptitle.length;
    rows = pdata.length;
    titles = ptitle;
    datas = pdata;
    //��ʼ����������Ϣ
    ch = rows * dy;
    if (ch > (winY - 20)) {
      isscroll = true;
      vh = winY - dy - 4;
      ah = winY - 2 * dy - 4;
      sh = (int) ((ah * vh) / ch) - 10;
      speed = ch / ah;
    }
    //�жϽ���ģʽ
    int interactionMode = getInteractionModes();
    horz = ((interactionMode & CustomItem.TRAVERSE_HORIZONTAL) != 0);
  }

  /**
   * ���ƺ���
   */
  protected void paint(Graphics g, int w, int h) {
    int y = 0;
    int oldColor = g.getColor();

    // ���ñ��������ʽ
    for (int i = 0; i < rows; i++) {
      if (i % 2 == 0) {
        g.setColor(rowsColor1[0], rowsColor1[1], rowsColor1[2]);
      } else {
        g.setColor(rowsColor2[0], rowsColor2[1], rowsColor2[2]);
      }

      y = dataY + (i + 1) * dy + 1;
      if (y >= 0 || y <= winY) {
        for (int j = 0; j < cols; j++) {
          g.fillRect(j * dx + 1, y, dx - 1, dy - 1);
        }
        if (isscroll == false) {
          g.fillRect(winX - 19, y, winX, dy - 1);
        }
      }
    }
    // ��ӱ������
    g.setColor(oldColor);
    for (int i = 0; i < rows; i++) {
      if (y >= 0 || y <= winY) {
        y = dataY + (i + 1) * dy + 1;
        for (int j = 0; j < cols; j++) {
          g.drawString(datas[i][j], dx / 2 + j * dx, y,
              Graphics.HCENTER | Graphics.TOP);
        }
      }
    }

    // ���
    g.setColor(255, 255, 255);
    g.fillRect(0, 0, winX, 20);
    // ���Ʊ�ͷ����
    int hx = winX;
    int hy = dy;
    g.setColor(titleColor[0], titleColor[1], titleColor[2]);
    g.fillRect(0, 0, hx, hy);
    // ���ư�ɫ����
    int temp = 0;
    g.setColor(255, 255, 255);
    g.drawLine(0, 0, hx, 0);
    for (int i = 0; i < cols; i++) {
      temp = i * dx + 1;
      g.drawLine(temp, 0, temp, hy);
    }
    // ���ƻ�ɫ����
    g.setColor(128, 128, 128);
    g.drawLine(0, hy - 1, hx, hy - 1);
    for (int i = 0; i < cols; i++) {
      temp = (i + 1) * dx - 1;
      g.drawLine(temp, 1, temp, hy - 1);
    }
    // ��д��������
    g.setColor(0);
    for (int i = 0; i < cols; i++) {
      g.drawString(titles[i], dx / 2 + i * dx, 1, Graphics.HCENTER
          | Graphics.TOP);
    }
    // �����ͷ�ұ߱߿�
    g.setColor(255, 255, 255);
    g.drawLine(winX - 19, 1, winX - 19, dy - 1);
    g.setColor(128, 128, 128);
    g.drawLine(winX - 1, 1, winX - 1, dy - 1);
    // ���Ʊ������
    g.setColor(titleColor[0], titleColor[1], titleColor[2]);
    if (isscroll) {
      g.fillRect(0, winY - 2, winX - 20, 2);
    } else {
      g.fillRect(0, winY - 2, winX, 2);
    }
    // ���ƹ�����
    if (isscroll) {
      // ���ƹ���������
      g.setColor(220, 220, 220);
      g.fillRect(winX - 19, dy + 1, winX - 20 - 1, winY - dy - 20);
      // ���ƹ��������淽��
      g.setColor(titleColor[0], titleColor[1], titleColor[2]);
      g.fillRect(winX - 19, winY - dy - 1, 19, dy);
      g.setColor(255, 255, 255);
      g.fillRect(winX - 19, winY - dy, 19, 1);
      g.fillRect(winX - 19, winY - dy, 1, dy - 1);
      g.setColor(128, 128, 128);
      g.fillRect(winX - 1, winY - dy, 1, dy - 1);
      g.fillRect(winX - 19, winY - 1, 19, 1);
      // ���ƹ�����
      g.setColor(titleColor[0], titleColor[1], titleColor[2]);
      g.fillRect(winX - 19, dy + offset, 19, sh);
      g.setColor(255, 255, 255);
      g.fillRect(winX - 19, dy + offset, 19, 1);
      g.fillRect(winX - 19, dy + offset, 1, sh);
      g.setColor(128, 128, 128);
      g.fillRect(winX - 1, dy + offset, 1, sh);
      g.fillRect(winX - 19, dy + offset + sh, 19, 1);
      // ����������
      g.setColor(255, 255, 255);
      g.fillTriangle(210, 5, 205, 15, 215, 15);
      g.fillTriangle(205, 188, 215, 188, 210, 198);
    }
  }

  // do something ...
}






package zieckey.j2me.study;

import javax.microedition.lcdui.*;
import javax.microedition.midlet.*;

/**
 * �ó���������ѧϰStringItem���
 */
public class StringItemMIDlet extends MIDlet implements ItemCommandListener,
		CommandListener
{

	private Form		form;			
	private Display		display;
	private StringItem	st1;
	private StringItem	st2;
	private StringItem	st3;
	private Command		exitCommand;
	private Command		buttonCommand;
	private Command		linkCommand;

	private Alert		buttonAlert;
	private Alert		linkAlert;

	public StringItemMIDlet( )
	{
		super( );

		form = new Form( "Study StringItem" );

		exitCommand = new Command( "�˳�", Command.EXIT, 2 );
		buttonCommand = new Command( "��ťģʽ00", Command.ITEM, 2 );
		linkCommand = new Command( "������ģʽ44", Command.ITEM, 2 );

		buttonAlert = new Alert( "Alarm", "��ťģʽ��StringItem��ѡ����", null,
				AlertType.ALARM );
		linkAlert = new Alert( "Alarm", "������ģʽ��StringItem��ѡ����", null,
				AlertType.ALARM );
		
		display = Display.getDisplay( this );
		st1 = new StringItem( "1", "��ͨ�ı�", StringItem.PLAIN );
		st2 = new StringItem( "2", "��ť�ı�ģʽ", StringItem.BUTTON );
		st3 = new StringItem( "3", "�������ı�ģʽ", StringItem.HYPERLINK );
	}

	protected void startApp() throws MIDletStateChangeException
	{
		

		{ // �����������û�еĻ���st1��st2��st3������۵���ʾЧ��һ��
			// ԭ��������Ҫָ��Item.BUTTON����۵���������������

			// ΪBUTTON��HYPERLINKģʽ��StringItem����Ĭ�ϵ�Command
			st2.setDefaultCommand( buttonCommand );
			st3.setDefaultCommand( linkCommand );

			// ע�������
			st2.setItemCommandListener( this );
			st3.setItemCommandListener( this );
		}

		form.append( st1 );
		form.append( st2 );
		form.append( st3 );
		form.addCommand( exitCommand );
		form.setCommandListener( this );

		buttonAlert.setTimeout( 3000 );
		linkAlert.setTimeout( 3000 );

		display.setCurrent( form );

	}

	protected void destroyApp( boolean arg0 ) throws MIDletStateChangeException
	{

	}

	protected void pauseApp()
	{

	}

	public void commandAction( Command cmd, Item item )
	{
		if ( cmd == buttonCommand && item == st2 )
		{
			// System.out.print( "��ťģʽ��StringItem��ѡ����" );
			display.setCurrent( buttonAlert );
		} else if ( cmd == linkCommand && item == st3 )
		{
			System.out.print( "������ģʽ��StringItem��ѡ����" );
			display.setCurrent( linkAlert );
		}
	}

	public void commandAction( Command cmd, Displayable arg1 )
	{
		// �Ը��������Ӧ
		if ( cmd == exitCommand )
		{
			try
			{
				destroyApp( true );
			} catch ( MIDletStateChangeException e )
			{
				e.printStackTrace( );
			}
			notifyDestroyed( );
		}

	}

}









2008/3/31
����Ӧ�ó������ص��ֻ���.
����������Eclipse��EclipseMe
1��Jar�ļ���Ч����ģ����������������Ӧ�ó��򣬵�ȴ�������õ������ֻ��ϣ���ʾJar�ļ���Ч����Nokia N73�ϣ�����������������˵�ñȽϼ򵥣�����û���ҵ�����İ취��ż������jad�������ļ����������������jad�ļ��ϡ���������ʾ����һ���ǲ����䱸��jad���ã��ڶ��������������õ��ֻ��ϵ����á�

����

MIDlet-Jar-Size: 2150
MIDlet-Jar-URL: J2ME.jar
MIDlet-Name: J2ME Midlet Suite
MIDlet-Vendor: Midlet Suite Vendor
MIDlet-Version: 1.0.0
MicroEdition-Configuration: CLDC-1.1
MicroEdition-Profile: MIDP-2.0



��ȷ����������

MIDlet-1: AlertsMIDlet,,J2ME.AlertsMIDlet
MIDlet-Jar-Size: 2150
MIDlet-Jar-URL: J2ME.jar
MIDlet-Name: J2ME Midlet Suite
MIDlet-Vendor: Midlet Suite Vendor
MIDlet-Version: 1.0.0
MicroEdition-Configuration: CLDC-1.1
MicroEdition-Profile: MIDP-2.0
�ƺ������Ҳ����ȷ����Ϊ��װ�����в��ԡ�

��ȷ��Ӧ���ǣ�

MIDlet-1: J2ME,,AlertsMIDlet
MIDlet-Jar-Size: 2150
MIDlet-Jar-URL: J2ME.jar
MIDlet-Name: J2ME Midlet Suite
MIDlet-Vendor: Midlet Suite Vendor
MIDlet-Version: 1.0.0
MicroEdition-Configuration: CLDC-1.1
MicroEdition-Profile: MIDP-2.0




˵��:J2ME����Ŀ��,AlertsMIDlet������
�Աȷ�����֪�����������ļ�ȱ��Ӧ�ó���������ɵģ�����ֻ��Ͳ��ܰ���Ӧ��Ӧ�ó���װ������ʾJar�ļ���Ч��

������һ����ȷ�����ӣ�
MIDlet-1: FirstJ2MEProject, FirstJ2MEProject.png, Hello
MIDlet-Jar-Size: 996
MIDlet-Jar-URL: FirstJ2MEProject.jar
MIDlet-Name: FirstJ2MEProject
MIDlet-Vendor: Unknown
MIDlet-Version: 1.0
MicroEdition-Configuration: CLDC-1.0
MicroEdition-Profile: MIDP-2.0

��WKT��KToolbar����ĳ������������á�
MIDlet-1 ��һ�еĸ�ʽ:

MIDlet-1: �������ֻ�����ʾ������, �ֻ�����ʾ�ĳ���ͼ��, ����(ע���������)




1.��WKT���
����KToolbar
���New Project��
Project Name�����⣨Ӣ�ģ���
MIDLet Class Name�����j2me�����Midlet����������֮ǰ��HelloWorld���Ӿ�����HelloWorld����
���Create Project��

����д�õ�.java�ļ�������֮ǰ��HelloWorld���Ӿ���HelloWorld.java���������ղŴ�����ProjectĿ¼�µ�srcĿ¼����������ɹ������projectĿ¼�µ�binĿ¼����������ļ�һ��jad��һ��jar�ļ����������ļ���������Ҫ�ϴ����ֻ����ļ�




MMAPI

һ����������ý��Ĵ���һ����Է�Ϊ������

�������ݴ���Э��
	Э�鴦�����ָ�İ����ݴ�һ��Դ���ļ���ץȡװ�á���ý��������ȡ����������ý�崦��ϵͳ���档

������������
	���ݴ���һ��ָ�������ݣ�������룩�Ͱ�ý�������豸�����ȣ���Ļ�ȣ���չ�ֳ�����
	
	��������ЩAPI�����������߶ȳ���Ķ�������Դ�����������κζ��󶼿��Էֳ����������ֽ��д���
DS��������Э��,Player������������ 

	һ������Դ����װ��Э�鴦�����档����������������δ�����Դ���汻�������ģ�������������Ǵ��ļ�����ý�廹��������һЩ�����е����á�����ԴҲ�ṩ��һЩ���������ݼ���������������������������ݲ�����

   ������������Դ����������ݣ��������ݣ�����������͵�����豸�ϡ����ṩ��һЩ��������������ý��Ļطźͻ�����ͬ����������Ҳ�ṩ��һЩ�����Ի���ض�ý������ԡ�

  ʹ�ù���ģʽ����������DS�������Player��Ϊ�˷��������ͬ��Ҳ�ṩ�˷������غ��������������Player�� 

Player����һ���ӿڣ���������Ͳ��Ŷ�ý�����ݣ�һ��Player��ʵ��������������DataSource�����ݣ�Ȼ������������������ڣ��Ͳ�ͬ���ط�����
DataSource����һ�������࣬��װ�����ݵĶ�λ����ȡ������һ��Э��Ŀ�����

һ��Player�����״̬: δʵ����״̬��ʵ����״̬��Ԥ��ȡ״̬����ʼ״̬���ر�״̬

eclipse����j2me���򷽷�
ʹ��EclipseMe�������preference ��߰�Java--Debug��Debuger timeout ����15000ms��ͬʱȷ��suspend execution on uncaught exceptions ��suspend executioen on complication errorsû�б�ѡ�У�Ȼ��debug��ʱ��debug as Emulated midlet��Ȼ��Ϳ��Ե����ˡ� 


��򵥵�J2ME������

package zieckey.j2me.study.mmapi;
import javax.microedition.midlet.MIDlet;
import javax.microedition.media.Manager;
import javax.microedition.media.Player;

public class SimplePlayer extends MIDlet
{
	public void startApp()
	{

		try
		{
			Player player = Manager.createPlayer( getClass().getResourceAsStream(
					"/Boo.wav" ), "audio/x-wav" );
			player.start();
		} catch ( Exception e )
		{
			e.printStackTrace();
		}
	}

	public void pauseApp()
	{
	}

	public void destroyApp( boolean unconditional )
	{
	}
}


ע�⣺��Ƶ�ļ�boo.wav��resĿ¼��

Player��VolumeControl��ֵΪ0~100


MMA��ѡ�����ֲ��Ź������(


����һ���󵨵����룬Ҳ������������Ȱ�fc��ȡ�������ļ�����byte[]���ٽ�byte[]->ByteArrayInputStream��Ȼ���ٴ��ݸ�Manager.createPlayer��һ�¡�
�����ֱ�Ӵ�jar���п��ԵĻ����Ҿ�������Ӧ�ó�����fc api��ʵ���ϣ�Ҳ����ôת��һ���ܽ�����⡣
�Ҿ�����ôһ�룬����֤�ɹ�Ŷ



����J2ME���ò�

    * ����J2ME���ò�

      Java 2 Micro Edition (J2ME)�ǽ�����һ����profiles�����ã�����������ֲ���ϵͳ�Ȳ�������ɵı�׼�ܹ�֮�ϵġ���Щ���������������J2MEʵʱ���л�����ͼ A��ʾ����Щ��������ν����һ��ġ�J2ME�ṩ���������ã�Connected Limited Device Configuration (CLDC)��the Connected Device Configuration (CDC)���������������豸���ڴ�footprintΪ��������ͬ���豸���͡�

      ����ָ������С�Ĺ��������ص�Java ����� (JVM)Ӧ֧�ֵ�Java��⡣�Ӹ����Ͻ������ò�������� (VM)�Ķ������У�������ʹ��һ������CLDC��CDC������ʱ����Ҳ���漰����ص�VM����Ϊ�����ǽ��������ġ�

      Ȼ����Ӧ��ע�������J2ME�У����ò���������һ���ض���VM����������������VM������֧������Ŀ⡣���磬CLDCҲ���Ժ�Ӧ��ָ���������ܵ�VM��ͬ����������ϸ�ڣ����CLDC HotSpotӦ���������ҳ��

      Ϊ�˰��������J2ME���ò������ݵĽ�ɫ���ҽ���CLDC��CDC�ֱ�ؽ��в�����

      CLDC
      CLDC���������512KB�ڴ�footprint���豸�����á�CLDC���õ���KVM�����Ǹ߶��Ż���JVM��ʽ������Ե���16���ػ�32���ص�΢��������160��512 KB�ڴ�Ϊ�����ĵͶˣ��������ӣ�����������豸�����͵��ڴ�Ҫ����128KB�������洢KVM����صĿ⡣�������KVM����Ϣ���Դ�Sun��˾�� KVM��ҳ�еõ���

      �����绯���ԣ�CLDC��Ե������޵ĺͼ�Ъ�Ե����������豸��������J2ME CLDC֮�����е�Ӧ�������Ӧ���������κθ߶˵�Java VM�����С���Ȼ������ҪCLDC���֧�֡�CLDC���ù�ע��I/O�����绯����ȫ���⣬���ʻ�����ͺ���Java�����ص�����

      ���¼������û���Ӧ�ó���Ļ�����Ӧ�ó��������ڹ����������ص���������Profile������ġ�ʹ�ý��涨�壨�����ض����豸���紫�������ƶ��绰��PDA��Ҳ��Profile��ķ�Χ֮�ڣ��������ڶ���֮�ϣ���ʹ��J2ME���á�Mobile Information Device Profile (MIDP)��һ��J2ME profile����������ʹ��CLDC�����豸���û�������صĹ淶��

      CLDC��J2SE��þ���������࣬��һЩ���С�ڴ�footprint�豸�����ಢ���Ǵ�J2SE APIs��õġ��������J2SE ���̳к���CLDC��ľ�����Ϣ���ɲο�CLDC�淶1.0a�汾��6.2��6.3�е����ݡ�Java���Թ淶�е�һЩ������û�и���֧�֣�û����ʵ������ɻ�֧�ֺ����޵Ĵ�����������

      �������ᵽCLDC HotSpotӦ��Ҳ�Ǿ�������Եģ����൱��ʹ��CLDC���õ��豸��KVM��Java VM���滻������Sun��˾��CLDC HotSpotִ��VM��һ�������ܵ�JVM��32λ������CLDC v1.0�淶����������ͬ���ڴ�footprint������ʱ�ṩ��KVM�߳�һ���������ĸ��ѵ����ܡ�

      CDC����ȫJavaƽ̨
      CDC��Ӧ���ھ��нϴ��ڴ棬�ر���2MB���ϵ��豸�ϵģ�CDC������޺ͼ�Ъ�����������豸��CDC��CVM��Foundation profile��ͬ��������ȫ��J2ME������

      CVM��Ϊ�û���Ƕ���豸��Ƶ���ȫ������JVM����֧�����е�Java 2 v1.3 VM��ȫ������JNI, JVMDI, RMI�������ù��ܺͿ⡣������˵��CVM��������һ��פ������ϵͳ��JVM�����еĹ��ܡ�

      CDC��J2SE����С��Java���ݰ���ɡ�Foundation profile���û��豸����Ҫ�ı�������APIs����ɡ���ˣ�����㹤����һ����CDCΪ������J2ME�����£������Ҫ�����������ʹAPIs���»�����

      CDC��CLDC��һ����չ������������������֮����������ϵļ����ԡ�CDC��Foundation profileҲ�ṩ�˶�ʹ��PersonalJavaʵʱ�淶������Ӧ�ó������ȫ���ݡ�

      �ܽ�
      J2MEģʽ��ϵʹ���˲�ͬ�豸���ġ��ر�桱Java�Ĵ���������Խ��Խ����豸�����̿�ʼ����J2ME������J2ME�豸ʹ�÷�Χ�����󣬸��µ� J2ME profiles���õ�Ӧ�á�ͨ��Ϊ������JavaΪ�������豸�ṩһ��������С��ƽ̨��J2ME�����ýṹ���ķ�ʽʹ������ЩJava�ر�汾�� 


wrote:
> Hi,
>
> My apps ( http://heartbit.sourceforge.net ) is targeted at small
> devices ( palm, pocketPC and smartphone ).
> Its needs access to socket-based IRda communication.
>
> I know SuperWaba, altough it does not support natively irda-socket,
> allows to write JNI-style native libs. which is fine for me.
>
> Which other JVM will allow to irda sockets ( natively or through JNI )
> ?
> will J2ME include this ?
> I googled for the answer, without success...
>
> TIA,
> --Philippe
>

Hi,

As long as your device supports MIDP2.x, I would say yes, you can
access the IrDa through a Serial Emulation.
In the Connection URL, use "comm:ir0"

<javadoc-of-CommConnection>

Recommended Port Naming Convention

Logical port names can be defined to match platform naming conventions
using any combination of alphanumeric characters. However, it is
recommended that ports be named consistently among the implementations
of this class according to a proposed convention. VM implementations
should follow the following convention:
Port names contain a text abbreviation indicating port capabilities
followed by a sequential number for the port. The following device name
types should be used:

* COM#, where COM is for RS-232 ports and # is a number assigned to
the port
* IR#, where IR is for IrDA IRCOMM ports and # is a number assigned
to the port

This naming scheme allows API users to generally determine the type of
port that they would like to use. For instance, if a application desires
to "beam" a piece of data, the app could look for "IR#" ports for
opening the connection. The alternative is a trial and error approach
with all available ports.

Since:
MIDP 2.0
</javadoc-of-CommConnection>

String port1;
String ports = System.getProperty("microedition.commports");
int comma = ports.indexOf(',');
if (comma > 0) {
// Parse the first port from the available ports list.
port1 = ports.substring(0, comma);
} else {
// Only one serial port available.
port1 =ports;
}
