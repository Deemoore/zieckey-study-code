
2007/01/12
J2ME

J2ME移动开发环境配置详细教程


1.下载安装工具

所需安装工具包和本文所用的工具包名称
jdk-1_5_x:jdk-1_5_0_08-windows-i586-p.exe
j2me_wireless_toolkit-2_2-windows:j2me_wireless_toolkit-2_2-windows.exe
eclipse-SDK-3.x:eclipse-SDK-3.2.1-win32.zip
eclipseme.feature_0.9.2_site:eclipseme.feature_0.9.2_site.zip

2.安装jdk并配置环境变量

安装j2sdk以后，需要配置一下环境变量，在我的电脑-＞属性-＞高级-＞环境变量-＞系统变量中添加以下环境变量(假定你的j2sdk安装在C:\Program Files\Java\jdk1.5.0_08）：
　　
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
　
　　此时如果看到打印出来 Hello world! My Java! 的话说明安装成功了，如果没有打印出这句话，需要仔细检查一下你的配置情况。


3.安装j2me_wireless_toolkit-2_2-ml-windows(简称WTK)

J2ME WTK 安装很简单，按照提示安装即可。
这里假设安装在:M:\J2ME\WTK22


4.Eclipse安装与J2ME的插件安装

将Eclipse解压到任何位置即可.
为了确保Eclipse运行正常,最好在Eclipse下写个小Java程序测试下.
然后安装 Eclipse 与J2ME WTK 之间的调用插件.
这里可以通过Eclipse的菜单栏:Help->software updates->Find and Install...->search for new feathers to install->new archived site... 
选择你下载到本地计算机上的eclipseme插件，

也可以
Help->software updates->Find and Install...->search for new feathers to install->New Remote Site

输入
Name：EclipseME Update Site
URL：http://www.eclipseme.org/updates/

点击Finish，然后一步一步安照提示就可以完成安装了

//。。。。。。。。。。。。。。。。。
运行Eclipse,进行最后的配置：
Window->preferences->J2ME->Platform Component
然后右键选择 Wireless Toolkil，再选择弹出菜单中的 Add Wireless Toolkil，
选择刚刚安装的J2ME Toolkit的安装路径: M:\J2ME\WTK22
这样基本配置就配置好了。

//。。。。。。。。。。。。或者
运行Eclipse,进行最后的配置：
Window->preferences->J2ME->Device Management
按导入...(Import)按钮。 
在接下来的对话框中，选择一个包含无线工具包的根目录，EclipseME将从中查找已知设备定义。 

 

当你离开查找目录文本框，或按下了刷新(Refresh)按钮， EclipseME就会开始从指定的目录和其子目录中搜索设备定义。在EclipseME的1.5.0版本中，你不再需要“精确的”选择目录才能正确导入设备，只要它们位于你指定的目录中，EclipseME就应该能定位到它们。找到一个设备定义，EclipseME就会在列表中显示出一个。如果你希望停止搜索，只要按下取消(Cancel)按钮就可以。 

搜索结束以后，勾选你想导入的那些设备定义。只有导入后的设备才能被用于定义项目以及启动程序。最后，选择完成(Finish)结束导入流程。 

如果EclipseME没找到你希望导入的设备定义，那可能是EclipseME还不支持它。这种情况下，请向我们提交一个RFE(新特性需求)来要求增加对这种WTK的支持，别不好意思。具体怎么做请参见这里。 


最后，改变Eclipse的调试设定
因为无线工具包有一些奇怪的设计（尤其是Sun的），如果你想使用Eclipse来调试MIDlet，那你必须改变一些默认的调试设定。像这样： 

选择Eclipse的窗口菜单中的首选项。 

打开左边面板中的Java选项分支并点击调试项。 

确保接近对话框顶端的两项：发生未捕获的异常时暂挂执行 和在发生编译错误时暂挂执行都没有被勾选。 

把接近对话框底部的：调试器超时的值增大到最少15000毫秒。 

设定后的结果应该看上去类似这样： 
 

如果你不做这些改变，在运行MIDlet的时候就会发生错误。 



5.测试J2ME

New->Project->J2ME->J2ME Midlet Suite->Next
输入工程名字：J2METest
点击Finish.
输入以下代码:


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
    	Form form = new Form("测试J2ME");
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

运行,如果出现一个手机画面,并且在手机显示器上输出:Hello world!,
恭喜你,你的J2ME移动开发平台安装成功了!
下面赶快开始你的J2ME开始之旅吧!





/////////////////////////////////////////XXXXXXXXXXXXXXX
安装Nokia的SDK（http://www.j2medev.com/Article/Class1/Class11/200609/3178_2.html）


下载 Nokia Developer's Suite 3.0 for J2ME  

您可以从 Nokia 论坛的工具专区下载免费的 Nokia Developer's Suite for J2ME，网址是 http://www.forum.nokia.com/tools(本网站的下载专区也提供下载http://www.j2medev.com/Soft/tools/200509/117.html)。

在开始运行下载的安装程序之前，必须先卸载 所有以前安装的 Nokia Developer's Suite for J2ME 版本。然后需要输入您在 Nokia 论坛中使用的用户名和请求（并通过电子邮件接收）的序列号。在获得提示的时候，应该选择将该套件与 Eclipse 集成。还需要告诉安装程序您安装 Eclipse 的根目录。

启动 Eclipse  

现在，启动 Eclipse IDE ，您会在工具栏上看到一个新的 Tools > Nokia Developer's Suite for J2ME 菜单项和一个新的图标编号。

将 SDK 添加到 Nokia Developer's Suite 中  

您可能必须手工将新的 SDK 添加到 Nokia Developer's Suite 中。为了做到这一点，需要执行以下步骤：

选择 Tools > Nokia Developer's Suite for J2ME > Configure Emulators。 
单击 Add 将新的 SDK 添加到下拉列表中。 



与Eclipseme集成：

Window->preferences->J2ME->Device Management
按导入...(Import)按钮。 
在接下来的对话框中，选择一个Nokia SDK的根目录（D:\software\J2MESDK\NDS3.0\Devices\Nokia_Prototype_SDK_2_0\），EclipseME将从中查找已知设备定义。 
/////////////////////////////////////////XXXXXXXXXXXXXXX



nS60_jme_sdk_3rd_e_FP2_Beta.zip 





/////////////////////////////////////////XXXXXXXXXXXXXXX
在netbeans中集成Nokia SDK

安装完Nokia的SDK后，打开Netbeans
选择“Tools->Java Platforms->Add Platform...”
再选择第二项"Java ME Platform Emulator"

然后让Netbeans自己去搜索，钩选上Nokia的SDK就可以了

/////////////////////////////////////////XXXXXXXXXXXXXXX




注意：以上文字教程要配上视频教程，方能更明白.如有不明地方，请登录中国J2ME论坛进行咨询(http://www.j2meforum.cn),教程可以随意传播，但未经作者同意不得善自修改。

									教程中难免有误，还望多多指教！

									作者：James.Ming
									QQ：66171709
									MSN:trasher007@hotmail.com
									Mail:jamesming@126.com
									日期:2005/06/26



使用WTK 2.2开发J2ME应用程序
运行M:\Java\J2ME\WTK22\bin\ktoolbar.exe
File->New Project...
输入工程名字和类名。




J2ME程序开发全方位基础讲解汇总
一、J2ME中需要的Java基础知识
       现在有大部分人，都是从零开始学J2ME的，学习J2ME的时候，总是从Java基础开始学习，而且现在讲Java基础的书籍中都是以J2SE来讲基础，这就给学习造成了一些不必要的麻烦，下面将J2ME中用到的和不需要的Java基础知识做一个简单的说明。
       J2ME中使用到的Java基础知识：
　　  1、Java语法基础：包括基本数据类型、关键字、运算符等等
　　  2、面向对象的思想：类和对象的概念，继承和多态等等。
　　  3、异常处理
　　  4、多线程
　　J2ME中没有用到的Java基础知识：
　　  1、JDK中javac和java命令的使用
　　  2、Java基础中的很多类在J2ME中没有，或者类中的方法做了大量的精简。所以建议在J2ME中熟悉类库。
　　  3、Applet、AWT、Swing这些知识在J2ME中根本使用不到。
　　简单说这么多，希望学J2ME的朋友们能少走一些弯路，不足之处希望大家积极指正和补充。

二、J2ME中暂时无法完成的功能
　　列一些J2ME中暂时无法完成的功能，希望大家能积极补充：
　　  1、在手机中不更改代码实现移植，主要指游戏。
　　  2、动态修改按钮文字。
　　  3、在Canvas上接受中文输入。
　　  4、操作本地资源、例如地址本、已收短信息等。
　　  5、制作破坏性的手机病毒。
　　  6、其他等待大家来补充。

三、J2ME的跨平台性
　　J2ME技术源于Java，所以也具有JVM的优势，可以在支持Java的平台上进行移植，但是现在的J2ME技术在跨平台上却做的很糟糕，我们来简单看一下原因：
　　1、手机的屏幕尺寸不一：
　　这个主要在界面制作上。如果你使用的是高级用户界面，比如你做的是应用开发或者用户登陆、用户注册这样的通用功能时，一般没有什么问题。
　　如果你使用的是低级用户界面，比如你做的是游戏，那么你就需要考虑这个问题了。
　　2、厂商的扩展API不统一：
　　例如Nokia的扩展API类库UI系列，在别的手机上或者没有实现，或者包名不同等等。
　　3、手机平台上实现的bug：
　　例如Nokia的7650在实现双缓冲上有bug，那么在这种机型上运行的软件就不能使用双缓冲。其他NOKIA上的一些bug，可以参看：http://blog.csdn.net/Mailbomb/archive/2005/03/24/329123.aspx
　　4、手机性能问题。
　　不同手机的可用内存、最大jar文件都有要求，例如Nokia S40的大部分手机支持的最大jar文件为64K，最大可用内容为210K。
　　所以现在的手机软件，特别是游戏都提供支持的机型列表，也才有了手机游戏移植人员的存在。

四、学习J2ME可以从事的工作种类
　　现在J2ME技术可以说相当的火暴，这里介绍一些学好了J2ME之后可以从事的工作的种类：
　　1、J2ME游戏开发人员
　　根据游戏策划或者文档要求，在某种特定的机型(以Nokia S40或S60居多)开发游戏程序。
　　这是现在大部分J2ME程序员从事的工作。
　　需要熟练掌握：高级用户界面、低级用户界面、线程，如果是网络游戏，还需要熟练网络编程。
　　2、J2ME应用开发人员
　　现在的移动应用还不是很多，但是还是出现了一些，特别是移动定位以及移动商务相关的内容。
　　需要熟练掌握：高级用户界面、线程和网络编程。
　　3、J2ME游戏移植人员
　　参照源代码，将可以在一个平台上可以运行的游戏移植到其他平台上去。例如将Nokia S40的游戏移植到S60上，或者索爱的T618等等。
　　主要是控制屏幕坐标，有些可能需要替换一些API。
　　需要熟悉各平台之间的差异以及相关的技术参数，比如屏幕大小、最大jar文件尺寸等等。

五、J2ME程序设计的几个原则
　　1、使用面向对象编程。
　　虽然使用面向过程编程可以减小文件的尺寸，但是为了以后维护的方便和利于扩展，还是要使用面向对象编程。
　　2、使用MVC模式
　　将模型、界面和控制分离。现在很多的程序将三者合一，但是如果你做的程序比较大的话，还是建议你进行分离。
　　3、自动存储用户设定
　　使用RMS来存储用户的信息，例如存储用户上次输入的用户名、密码、用户对于系统的设定等，这样不仅可以减少用户的输入，而且对用户友好。很多程序甚至做了自动登陆等。
　　4、一些系统设置允许用户关闭。如背景音乐、背景灯显示等。
　　5、将低级用户界面的绘制动作放在一个独立的线程里面去。
　　6、在需要大量时间才能完成的工作时，给用户一个等待界面。

六、从模拟器到真机测试
　　对于J2ME开发者来说，模拟器给我们带来了很多方便，比如可以在模拟器中调试程序以及很方便的察看程序的效果，但是模拟器也给我们带来了一些问题，比如模拟器实现的bug等等，所以进行真机测试是必须的。
　　1、为什么要进行真机测试？
　　因为模拟器程序可能存在bug，以及真机的性能有限，所以必须进行真机测试。
　　2、如何将程序传输到机器中？
　　将程序传输到机器中有如下方式：
　　  a)　OTA下载
　　  b)　使用数据线传输
　　  c)　红外传输
　　  d)　蓝牙
　　你可以根据条件，选择合适的方式。
　　3、 真机测试主要测什么？
　　真机测试的内容很多，主要测试以下几个方面：
　　  a)　程序的功能
　　  b)　程序的操作性，是否易操作
　　  c)　程序的大小,比如Nokia S40系列的手机大部分接受的最大文件尺寸为64K
　　  d)　程序运行速度，速度是否可以忍受。

七、从WTK到厂商SDK
　　对于J2ME爱好者来说，基本上大家都是从SUN的WTK(J2ME Wireless Toolkit)开始的，但是对于实际应用来说，仅仅使用WTK是远远不够的，所以在学习过程中，必须完成从WTK到SDK的跨越。
　　1、厂商SDK的下载地址？
　　http://blog.csdn.net/Mailbomb/archive/2005/01/01/236606.aspx
　　2、厂商SDK和WTK有什么不同？
　　厂商SDK最简单的理解就是在WTK的基础上增加了自己的模拟器和自己的扩展API。
　　也就是说，你在使用厂商的SDK时，可以使用厂商的扩展类库，例如Nokia的UI类库，和厂商自己的模拟器而已。
　　每个厂商的扩展API都不多，而且不尽相同。
　　3、如何使用？
　　有些厂商SDK的使用都和WTK相同，例如SamSung。
　　Nokia提供了独立的界面来开发，但是这个界面在实际开发中使用不多。
　　4、厂商SDK的问题
　　厂商SDK实现过程中，有一些bug，而且和真机实现不一致。例如NOKIA的混音播放问题等等。

八、在J2ME中获得手机IMEI的方法
　　IMEI是Internation mobile entity identification的简称，在手机中输入*#06#可以显示该数字，长度为15位，全球唯一，永远不会冲突，所以可以作为识别用户的一个标志。
　　下面是在J2ME中获得IMEI的方法：
　　1、MOTO系列的手机可以通过读取系统的IMEI属性获得，代码如下：
　　           String imei = System.getProperty("IMEI");
　　2、SIEMENS系列的手机可以通过读取系统的com.siemens.IMEI属性获得，代码如下：
　　           String imei = System.getProperty("com.siemens.IMEI");

九、J2ME网络连接中显示问题的解决办法
　　在网络编程中，有些时候会出现一些在没有接收到网络数据就显示界面的，造成界面显示不符合要求（例如公告显示，会先显示公告的背景图片再显示公告信息），这里提一个简单的解决办法给大家：
　　解决这种情况的方法分成三个步骤：
　　1、在需要显示的界面中，调用发送网络数据的方法。每次显示时调用该构造方法，不调用Display的setCurrent方法显示。
　　2、显示等待界面(例如进度条等)，给用户提示，在进行网络连接。
　　3、在处理网络反馈的数据完以后，调用Display的setCurrent方法显示显示当前界面。

十、增强J2ME的String能力——分割字符串
　　从JDK1.4以后，String类中新增了split方法来实现字符串的分割，但是在J2ME中却没有该方法(MIDP2.0中也没有实现)，但是在实际使用过程中，有些时候的确要用到这种操作，这里将我以前实现的一段代码和大家共享：
/**
* 分割字符串，原理：检测字符串中的分割字符串，然后取子串
* @param original 需要分割的字符串
* @paran regex 分割字符串
* @return 分割后生成的字符串数组
*/

private static String[] split(String original,String regex)
{
     //取子串的起始位置
     int startIndex = 0;
     //将结果数据先放入Vector中
     Vector v = new Vector();
     //返回的结果字符串数组
     String[] str = null;
     //存储取子串时起始位置
     int index = 0;

     //获得匹配子串的位置
     startIndex = original.indexOf(regex);
     //System.out.println("0" + startIndex);
     //如果起始字符串的位置小于字符串的长度，则证明没有取到字符串末尾。
     //-1代表取到了末尾
     while(startIndex < original.length() && startIndex != -1)
     {
           String temp = original.substring(index,startIndex);
           System.out.println(" " + startIndex);
           //取子串
           v.addElement(temp);

           //设置取子串的起始位置
           index = startIndex + regex.length();

           //获得匹配子串的位置
           startIndex = original.indexOf(regex,startIndex + regex.length());
     }

     //取结束的子串
     v.addElement(original.substring(index + 1 - regex.length()));
     //将Vector对象转换成数组
     str = new String[v.size()];
     for(int i=0;i
     {
          str[i] = (String)v.elementAt(i);
     }

     //返回生成的数组
     return str;
}

十一、J2ME在低级用户界面上分行显示文字
　　在J2ME的低级用户界面开发中，经常会遇到需要在Canvas上显示大量的文字，例如关于界面、游戏说明、游戏公告等信息。如果在设计时，将文字的内容和长度都固定，既不利于修改也不利于维护。下面介绍一个简单的方法，实现一个简单、可维护性强的方式。
　　实现方法：
　　  1、将需要显示的所有信息做成一个字符串。
　　  2、编写一个将该字符串按照要求转换为字符串数组的方法。
　　  3、将转换后的数组以循环的方式显示在Canvas上。
　　通过这样三个步骤，则修改显示的信息时，只需要修改包含显示信息的字符串即可，自己书写的方法可以按照以前的标准重新分割新的字符串。如果需要修改每行显示的字符个数，则只需要修改自己书写的方法即可。
　　通过这样一种实现方式，可以很方便的实现显示一些比较长的文本信息，即使是可变长度的字符串也没有问题。

十二、J2ME中使用记录存储系统(RMS)存储信息
　　在MIDP中，没有文件的概念，所以永久存储一般只能依靠记录存储系统实现，关于记录存储系统的简介，可以参看教程：http://www-900.ibm.com/developerWorks/cn/java/j-wi-rms/index.shtml
　　下面是一些记录存储系统的常用编码介绍：
　　  1、打开记录集：
　　打开记录集使用RecordStore里面的静态方法openRecordStore，示例代码如下：
          RecordStore rs = RecordStore.openRecordStore(“username”,true);
　　这样就打开了一个名称为rs的记录集，其中username为记录集的名称，该名称可以根据需要来取，第二个参数代表是否则没有时创建新的记录集，true代表在该记录集不存在时，创建新的记录集，false代表不创建。
　　如果在打开记录集时，该记录集不存在，则抛出RecordStoreNotFoundException异常，所以检测记录集是否已创建可以使用该异常。
　　注意：记录集打开以后记得关闭。
　　  2、向记录集中写入数据
　　      2.1增加数据
　　向已经打开的记录集中添加数据，需要使用addRecord方法，示例代码：
                 byte[] bytes = {1,2,3};
　　           int id = rs. addRecord(bytes,0,bytes.length);
　　该代码将字节数组bytes的全部内容写入到记录集中，该方法的返回值为该信息的id，注意：id从1开始，而不是从0开始。
　　你可以循环使用该方法向记录集中写入多条数据。
　　      2.2修改数据
　　修改已经存在的记录集中指定id的数据，需要使用setRecord方法，示例代码：
                 byte[] bytes = {1,2,3};
　　           rs. setRecord(1,bytes,0,bytes.length);
　　以上代码的作用是将字节数组bytes的全部内容写入到id为1的记录集rs中。
　　该操作会覆盖已有的数据。
　　说明：有些时候，你需要将信息写入到记录集中的第一条记录中，则可以结合以上两个方法，则第一次时向记录集增加数据，以后来进行修改。
　　  3、从记录集中读出数据
　　从记录集中读取已有数据，需要使用getRecord方法，示例代码：
            byte[] bytes = rs. getRecord(1);
　　该代码从记录集rs中读取第一条数据，将读取到的数据放在bytes数组中。
　　在读取数据时，可以获得记录集中id的个数，可以使用getNumRecords方法获得
　　综合代码为：
       int number = rs. getNumRecords();
       int id = 1;
       if(id >0 && id < number)
       {
　　     byte[] bytes = rs. getRecord(1);
       }
　　  4、从记录集中删除记录
　　从记录集中删除记录的方法有两种：逻辑删除和物理删除。
　　逻辑删除是指给删除的记录打标记。
　　物理删除是指从物理上删除该记录，但是该记录的id不能被重用，也就是说该id不会被继续使用。例如一个记录集中有5个记录，假设你删除了id为3的数据，则剩余记录的id依然为1、2、4、5。这给便历带来了一定的麻烦。
　　  5、便历记录集
　　便历记录集，即访问记录集中的所有数据，有两个方法，详见：
http://gceclub.sun.com.cn/NASApp/sme/controller/teclist?tid=0103
　　  6、其他操作
　　删除记录集
　　删除记录集不同于删除记录，需要使用deleteRecordStore方法，示例代码：
                RecordStore. deleteRecordStore(“username”);
　　该代码删除名称为username的记录集。

十三、J2ME加密数据的一个第三方开源免费类库介绍
　　在J2ME编程中，经常遇到一些数据在存储或者传输时需要加密，下面介绍一个第三方的加密类库的一些资料：
　　加密类库的官方主页：http://www.bouncycastle.org/
　　介绍的文章：
　　中文：http://18900.motorola.com/ewa_portal/develope/jc_j2messl_5_1.jsp
　　英文：http://www.javaworld.com/javaworld/jw-12-2002/jw-1220-wireless.html
　　该文章的源代码包含使用的一些方法。
　　备注：因为该类库提供的功能比较强大，所以类库的尺寸比较大，最后在发布时需要将类库中不需要的类删除

十四、如何播放声音
　　在J2ME中，处理声音需要使用到Mobile Media API(MMAPI)，该包是MIDP1.0的可选包，在MIDP2.0中已经包含了这个包。所以如果你使用MIDP1.0的话，请确认你的运行环境是否支持。
　　一般手机支持的声音文件格式为wav、mid和mpg等。具体请查阅你的手机说明文档。
　　在声音处理中，有很多处理的方式，这里说一下最常用的情况，播放JAR文件中的wav文件。
　　播放声音文件的流程：
　　  1、按照一定的格式读取声音文件。
　　播放JAR文件中的声音文件一般是将声音文件处理成流的形式。示例代码：
             InputStream is = this.getClass().getResourceAsStream("/Autorun.wav");
       其中Autorun.wav文件位于JAR文件的根目录下，如果位于别的目录，需要加上目录名称，如/res /Autorun.wav。
　　  2、将读取到的内容传递给播放器。
　　将流信息传递给播放器，播放器按照一定的格式来进行解码操作，示例代码：
             Player player = Manager.createPlayer(is,"audio/x-wav");
　　其中第一个参数为流对象，第二个参数为声音文件的格式。
　　  3、播放声音。
　　使用Player对象的start方法，可以将声音播放出来，示例代码：
             player.start()；
　　在播放声音时也可以设定声音播放的次数，可以使用Player类中的setLoopCount方法来实现，具体可查阅API文档。
　　下面是在NOKIA S60模拟器中测试通过。代码如下：
package sound;
import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;
import javax.microedition.media.*;
import java.io.*;

public class SoundMIDlet extends MIDlet
{
　　private Player player = null;
　　/** Constructor */
　　public SoundMIDlet()
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
　　　　          player.start();
                   }
                   catch(MediaException e)
                   {
　　　　          System.out.println("4:" + e);
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

十五、J2ME 3D编程的一些资料
　　随着J2ME技术的发展，以及硬件速度的提升，3D游戏程序将慢慢的变成主流，最近想学习这一块的编程，所以收集了一些资料，和大家一起分享：
　　1、JSR184
　　JSR184是Nokia公司起草的一个关于3D API的规范，下载地址为：
　　http://www.forum.nokia.com/main/1,,1_0_10,00.html#jsr184
　　2、Nokia的3D编程资料
　　http://www.forum.nokia.com/main/1,6566,21,00.html
　　3、3D引擎
　　一个简单的开放源代码的3D游戏引擎
　　http://www.j2me.com.cn/Soft_Show.asp?SoftID=19
　　国内一个合作开发3D引擎的项目：
　　http://gceclub.sun.com.cn/NASApp/sme/jive/thread.jsp?forum=11&thread=8593
　　4、一款3D游戏产品
　　http://games.sina.com.cn/newgames/2004/04/040217696.shtml
　　5、支持3D的开发工具
　　当前一些高端的手机支持3D开发，支持3D开发的开发工具中，通用的有SUN的J2MEWTK2.2。专用的是厂商提高的支持JSR184的SDK。

十六、3D编程——第一个3D程序
　　参考WTK2.2提供的demo，完成了第一个3D程序，虽然很简单，而且有些问题还不是很清楚，还是把代码共享出来和愿意学习J2ME 3D编程的朋友一起学习。
　　关于代码的编译和运行说明如下：
　　1、以下代码在J2ME WTK2.2下面编译通过。
　　2、代码分为两个文件：First3DCanvas.java和First3DMIDlet.java。
　　3、使用J2ME WTK2.2建立新的工程，主MIDlet类为：first3d. First3DMIDlet
　　4、将代码保存在你的工程目录下的first3d目录下。
　　5、将J2ME WTK安装目录下的apps\Demo3D\res\com\superscape\m3g\wtksamples\retainedmode\content目录中的swerve.m3g文件复制到你的工程目录下的res目录下。
　　6、你的工程建立后，设置工程，通过WTK界面中的“设置”按钮打开设置窗口，在“API选择”中，设置“目标平台”为：自定义；“简档”为“MIDP2.0”；“配置”为“CLDC1.1”；选中“Mobile 3D Graphics for J2ME(JSR184)”。
　　7、这样你就可以编译和运行以下代码了。
　　源代码如下：

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
* 第一个3D程序
*/
public class First3DCanvas extends Canvas implements Runnable
{
      /**World对象*/
      private World myWorld = null;
      /**Graphics3D对象*/
      private Graphics3D g3d = Graphics3D.getInstance();
      /**Camera对象*/
      private Camera cam = null;
      private int viewport_x;
      private int viewport_y;
      private int viewport_width;
      private int viewport_height;
      private long worldStartTime = 0;
      //重绘时间
      private int validity = 0;

      public First3DCanvas()
      {
            //启动重绘界面的线程
            Thread thread = new Thread(this);
            thread.start();
            try
            {
                   //导入3D图片
                   myWorld = (World) Loader.load("/swerve.m3g")[0];
                   viewport_x = 0;
                   viewport_y = 0;
                   viewport_width = getWidth();
                   viewport_height = getHeight();
                   cam = myWorld.getActiveCamera();
                   //设置cam对象
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
            //清除背景
            g.setColor(0x00);
            g.fillRect(0, 0, getWidth(), getHeight());
            //和3D对象绑定
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
                         //重绘图形
                         repaint(viewport_x, viewport_y, viewport_width, viewport_height);
                   }
            }
            catch(Exception e){}
      }
}

十七、在J2ME网络编程中使用CMWAP代理
　　在中国移动提供的网络连接中，分为CMNET和CMWAP两种，其中CMNET可以无限制的访问互联网络，资费比较贵。CMWAP类似一个HTTP的代码，只能访问支持HTTP的应用，但是资费便宜，稳定性比较差。
　　在实际的J2ME网络编程中，一般需要提供以CMWAP代理的方式连接网络，在J2ME中，连接的代码和直接连接有所不同，代码如下：
             HttpConnection http = (HttpConnection)Connector.open(("http://10.0.0.172/"+url);
             http.setRequestProperty("X-Online-Host",ServerName);
　　例如你需要访问的地址为：http://www.test.com/login/loginServlet则上面的代码就为：
             HttpConnection http = (HttpConnection)Connector.open(("http://10.0.0.172/" + "login/loginServlet");
             http.setRequestProperty("X-Online-Host","www.test.com");
　　在实际使用过程中，只需要使用实际需要访问的地址的域名或者IP来代替ServerName，例如示例中的“www.test.com”，使用后续的地址类代替代码中的url，例如示例中的“login/loginServlet”，就可以实际的使用CMWAP代理来进行连接了。

十八、J2ME中的时间处理全攻略
　　时间处理在程序开发中相当常见，下面对于时间处理做一个简单的说明。
　　一、时间的表达方式
　　时间在J2ME中有两种表达方式：
　　1、以和GMT1970年1月1号午夜12点和现在相差的毫秒数来代表
　　这种方式适合比较两个时间之间的差值。
　　2、以对象的形式来表达
　　二、时间处理的相关类
　　时间处理在J2ME中涉及三个类：
　　1、System类
　　 long time = System. currentTimeMillis();
　　使用该方法可以获得当前时间，时间的表达方式为上面提到的第一种。
　　2、Date类
　　 Date date = new Date();
　　获得当前时间，使用对象的形式来进行表达。
　　3、Calendar类
　　 Calendar calendar = Calendar. getInstance();

三、时间处理的具体操作
　　1、以上三种表达方式的转换：
　　a)将System类获得的时间转换为Date对象
　　 Date date = new Date(System. currentTimeMillis());
　　b)将Date类型的对象转换为Calendar类型的对象
　　 Calendar calendar = Calendar. getInstance();
　　 Date date = new Date();
　　 calendar.setTime(date);
　　2、使用Calendar完成一些日期操作：
　　Calendar是时间处理中最常用也是功能最强大的类，可以用它来获得某个时间的日期、星期几等信息。
　　获得日期：
　　 Calendar calendar = Calendar. getInstance();
　　 ……
　　 int day = calendar.get(Calendar. DATE);
　　获得日期、年份、星期的操作和这个类似。
　　需要注意的是：Calendar中表示月份的数字和实际相差1，即1月用数字0表示，2月用数字1表示，……12月用数字11表示。

十九、J2ME中随机数字处理全攻略
　　在程序中生成随机数字，用处比较，如人工智能领域等等，这里对于在J2ME中生成随机数的操作进行一个简单的整理，希望对大家能有帮助。
　　J2ME和J2SE不同，不能使用Math类的random来生成随机数字，只能使用java.util包的Random类来生成随机数字。
　　1、创建Random类型的对象：
         Random random = new Random();
　　 Random random = new Random(10010010);
　　以上两种是创建Random对象的方式，第一种使用默认构造方法，和以下的代码作用完全等价：
　　 Random random = new Random(System. currentTimeMillis());
　　相当与使用当前时间作为种子数字来进行创建。
　　第二种方式通过自己来指定种子数字来进行创建。
　　大家可以根据需要使用以上两种方式的任一种。
　　2、生成随机数字：
　　创建好了随机对象以后，我们就可以来生成随机数字了：
　　生成随机整数：
         int k = random.nextInt();
       生成随机长整数：
         long l = random.nextLong();
　　3、生成指定范围的数字：
　　例如生成0-10之间的随机数字：
         int k = random.nextInt();
　　 int j = Math.abs(k % 10);
　　首先生成一个随机整数k，然后用k和10取余，最后使用Math类的abs方法取绝对值，获得0-10之间的随机数字。
　　获得0-15之间的随机数，类似：
         int k = random.nextInt();
　　 int j = Math.abs(k % 15);
　　获得10-20之间的随机数字：
         int k = random.nextInt();
　　 int j = Math.abs(k % 10) + 10;

二十、在J2ME手机编程中使用字体
　　在J2ME手机编程中，可以通过使用字体类——Font在低级用户界面中，获得更好的表现效果，那么如何使用Font类呢？
　　首先，由于手机设备的限制，手机中支持的字体类型很有限，所以在J2ME中只能使用手机支持的默认字体来构造Font类对象。下面是创建Font类的对象时使用的方法：
          getFont(int face,int style,int size);
例如：
          Font font = Font.getFont(Font.FACE_SYSTEM,Font.STYLE_BOLD,Font. SIZE_MEDIUM);
　　无论哪一个参数，都只能使用系统设置的数值，这些数值具体的大小在不同的手机上可能不同。下面对于其中的三个参数的取值做详细的介绍：
　　face参数指字体的外观，其的取值：
　　FACE_MONOSPACE——等宽字体
　　FACE_PROPORTIONAL——均衡字体
　　FACE_SYSTEM——系统字体
　　style参数指字体的样式，其的取值：
　　STYLE_BOLD——粗体
　　STYLE_ITALIC——斜体
　　STYLE_PLAIN——普通
　　STYLE_UNDERLINED——下划线
　　STYLE_BOLD | STYLE_ITALIC——粗斜体
　　STYLE_UNDERLINED | STYLE_BOLD——带下划线粗体
　　STYLE_UNDERLINED | STYLE_ITALIC——带下划线斜体
　　STYLE_UNDERLINED | STYLE_ITALIC | STYLE_BOLD——带下划线的粗斜体
　　size参数指字体的大小，其的取值：
　　SIZE_SMALL——小
　　SIZE_MEDIUM——中
　　SIZE_LARGE——大
　　通过上面的参数的值，可以组合出你需要的字体对象。
　　下面是一些常用的字体操作：
　　1. 获得系统的默认字体：
          Font font = Font.getDefaultFont();
　　2. 在panit方法内部，假设Graphics参数的名称为g，则获得当前字体的方法是：
          Font font = g.getFont();
　　3. 在panit方法内部，假设Graphics参数的名称为g，则设置当前字体的方法是：
          g.setFont(font);
　　其中font为你构造好的字体对象。
　　4. 在MIDP2.0中，List可以设置每行的字体格式，方法是：
          list.setFont(0,font);
　　则上面的代码是将list中的第一行设置为font类型的字体。

二十一、在J2ME手机程序开发中使用颜色
　　在J2ME手机开发过程中，需要经常用到颜色来进行绘制，增强程序的表现效果，下面就介绍一下如何使用颜色。
　　由于J2ME技术比较简单，所以没有实现专门的颜色类，而只是使用RGB的概念来代表颜色。这里简单介绍一下RGB的概念，颜色是由红(Red)、绿(Green)、蓝(Blue)三原色组成的，所以可以使用这三个颜色的组合来代表一种具体的颜色，其中R、G、B的每个数值都位于0-255之间。在表达颜色的时候，即可以使用三个数字来表达，也可以使用一个格式如0X00RRGGBB这样格式的十六进制来表达，下面是常见颜色的表达形式：
　　红色：(255,0,0)或0x00FF0000
　　绿色：(0,255,0)或0x0000FF00
　　蓝色：(255,255,255)或0x00FFFFFF
　　其他颜色也可以通过上面的方式组合出来。
　　知道了颜色的表达方式以后，下面来介绍一下如何在J2ME程序中使用颜色，涉及的方法均在Graphics类中，有以下几个：
　　1.getColor()：
　　获得当前使用的颜色，返回值是0x00RRGGBB格式的数字。例如：
          int color = g.getColor();
　　其中g为Graphics类型的对象。
　　2.setColor(int RGB)：
　　设置使用的颜色。例如：
          g.setColor(0x00ff0000);
　　3.setColor(int red, int green, int blue)
　　和上面的方法作用一样，例如：
          g.setColor(255,0,0);
　　在设置了Graphics使用的颜色以后，再进行绘制的时候，就可以绘制指定的颜色了。

二十二、在J2ME联网应用中获得客户端的手机号码
　　在J2ME程序开发过程中，为了一定的需要，经常需要来获得用户的手机号码，但是这个功能却在标准的J2ME类库中没有提供。
　　在使用中国移动的CMWAP方式连接网络时，中国移动会将用户的手机号码放在一个名称为x-up-calling-line-id的头信息中，可以通过读取该头信息，获得用户的手机号码，具体代码如下：
          String usermphone = http.getHeader("x-up-calling-line-id");
　　其中http是HttpConnction类型的对象。

二十三、使用J2ME发送手机短信息
　　在程序中，发送短信息的方式一般有三种：
　　1、 使用程序在网络上发送短信息，例如各大网站的短信业务。这种方式是通过程序将信息发送给运营商的网关服务器，然后通过运营商的网络发送给手机。
　　2、 在计算机中，通过数据线连接到手机，然后通过手机来发送短信息。这种方式是通过使用AT指令来实现。爱立信手机的AT指令你可以在以下地址找到：http://mobilityworld.ericsson.com.cn/development/download_hit.asp
　　3、 通过在手机中运行的程序来发送短信息。这个正是本文实现的方式。
　　在J2ME中，如果想发送短信息，需要使用WMA包，MIDP2.0中已经包含，MIDP1.0中可以通过厂商提供的扩展API实现，和WMA的类库基本一样。
       下面是使用WMA向指定手机号码发送短信息的一个方法，很简单。当然WMA也提供了其他的方式来发送更多的内容。

// SMSUtil.java
package my.util;
import javax.wireless.messaging.*;
import javax.microedition.io.*;
/**
* 发送文本短信息的方法
*/
public class SMSUtil
{
      /**
      * 给指定号码发送短信息
      * @param content 短信息内容
      * @param phoneNumber 手机号码
      * @return 发送成功返回true，否则返回false
      */
      public static boolean send(String content,String phoneNumber)
      {
            //返回值
            boolean result = true;
            try
            {
                   //地址
                   String address = "sms://+" + phoneNumber;
                   //建立连接
                   MessageConnection conn = (MessageConnection)Connector.open(address);
                   //设置短信息类型为文本，短信息有文本和二进制两种类型
                   TextMessage msg = (TextMessage)conn.newMessage(MessageConnection.TEXT_MESSAGE);
                   //设置信息内容
                   msg.setPayloadText(content);
                   //发送
                   conn.send(msg);
            }
            catch( Exception e )
            {
                   result = false;
                   //未处理
            }
            return result;
      }
}

二十四、使用简单的J2ME程序测试MIDlet的生命周期
　　在MIDlet程序学习中，生命周期是一个比较抽象的概念。其实生命周期就是一个简单的规定，规定了MIDlet中的每个方法，什么时候被系统调用。下面是一个示例代码，在每个方法的内部都输出一条语句，可以根据程序的输出结果来验证各方法被调用的顺序，具体代码如下：


//文件名：LifeCircleMIDlet.java
import javax.microedition.midlet.*;
/**
* 测试MIDlet的生命周期
*/
public class LifeCircleMIDlet extends MIDlet
{
      /**
      * 默认构造方法
      */
      public LifeCircleMIDlet()
      {
            System.out.println("默认构造方法");
      }
      /**
      * 启动方法
      */
      public void startApp()
      {
            System.out.println("startApp方法");
      }
      /**
      * 暂停方法
      */
      public void pauseApp()
      {
            System.out.println("pauseApp方法");
      }
      /**
      * 销毁方法
      * @param b
      */
      public void destroyApp(boolean b)
      {
            System.out.println("destroyApp方法");
      }
}
　　在J2WTK中运行该程序时，可以使用浏览器中的“MIDlet”菜单中的暂停和恢复菜单，模拟暂停事件。

二十五、使用OTA来发布你的程序
　　众所周知，J2ME程序发布的形式主要有：OTA、数据线传输、红外和蓝牙传输等。这里简单说说如何通过OTA来发布你的程序。
　　OTA是Over The Air的简写，也就是通过网络下载，这是主要的发布形式之一。现在的百宝箱都是采用这种形式。
　　使用OTA来发布程序，需要如下几个步骤：
　　1、在你的WEB服务器上添加对于jad和jar文件的MIME支持。
　　后缀名:jad
　　MIME类型:text/vnd.sun.j2me.app-descriptor
　　后缀名:jar
　　MIME类型:application/java-archive
　　2、发布WML页面：
　　例如你的jar文件名test.jad，则最简单的下载页面是：
　　<?xml version="1.0"?>
　　<!DOCTYPE wml PUBLIC "-//WAPFORUM//DTD WML 1.3//EN"
　　"http://www.wapforum.org/DTD/wml13.dtd">
　　<wml>
　　<card id="card1" title="Download Midlet">
　　<a href="test.jad">test</a>
　　</card>
　　</wml>
　　你可以将以上代码保存在WEB服务器上，例如保存为text.wml
　　3、修改jad文件：
　　在jad文件中增加　MIDlet-Jar-URL: http://domain/directory/test.jar
　　其中的http://domain/directory/test.jar为你的jar文件的路径。
　　经过上面的设置，你就可以将你的wml页面路径作为你的WAP下载页面发布了。用户只需要在手机上输入这个路径就可以访问和下载你的程序了。












2007/1/13
J2ME显示系统时间

J2ME程序都是从MIDlet类开始执行,MIDlet是J2ME项目文件的入口文件，也是必须的。
Display是一个系统设备显示和输入的管理中心,每一个MIDlet都必须有一个Display.
Display包含一些成员方法去提取系统属性和响应显示在系统设备的对象的请求。

下面看一个简单的例子：

/**
 * DisplayDate.java 该程序用于提取当前系统时间并显示出来
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
		display = Display.getDisplay ( this );// 提取系统设备的Display对象

		// 构造一个文本输入框TextBox组件，用于显示文本
		// 向构造函数传递了Calendar.getInstance ( ).getTime().toString ( )对象，
		// 该对象是系统时间对应的字符串
		TextBox textbox = new TextBox ( "Display data and time!", Calendar
				.getInstance ( ).getTime ( ).toString ( ), 256, TextField.ANY );

		// 将textbox设置为当前显示的组件
		display.setCurrent ( textbox );
	}

	protected void destroyApp ( boolean arg0 ) throws MIDletStateChangeException
	{
	}

	protected void pauseApp ()
	{
	}
}

需要说明的是，虽然Calendar继承自Object，也有toString()方法，
但是如果直接调用 Calendar.getInstance ( ).toString ( )
来传递一个string型参数给TextBox，并不能得到我们预想中时间字符串，
而是一些有关j2me的sun公司网站信息，这个很可能是Calendar并不提供toString方法。
这给我们一个很重要的教训：不要期望相同代码的MIDP程序会和J2SE程序表现一样。

我们再看看MIDP所支持的时区情况，情况下面代码：
/**
 * DisplayDate.java 该程序用于提取当前系统时间并显示出来
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
		display = Display.getDisplay ( this );// 提取系统设备的Display对象

		// 构造一个文本输入框TextBox组件，用于显示文本
		// 向构造函数传递了Calendar.getInstance ( ).getTime().toString ( )对象，
		// 该对象是系统时间对应的字符串
		TextBox textbox = new TextBox ( "Display data and time!",
				Calendar.getInstance ( ).getTime ( ).toString ( ), 256, TextField.ANY );

		//得到系统缺省的时区
		String[] timeZoneList = TimeZone.getAvailableIDs ( );
		for( int i=0;i<timeZoneList.length;i++)
		{	//插入到文本输入框textbox中
			textbox.insert ( "\n" + timeZoneList[i], textbox.getCaretPosition ( ) );
		}

		// 将textbox设置为当前显示的组件
		display.setCurrent ( textbox );
	}

	protected void destroyApp ( boolean arg0 ) throws MIDletStateChangeException
	{
	}

	protected void pauseApp ()
	{
	}
}

我们知道手机打开一个程序都有一个退出按钮来退出这个程序，
那么我们现在实现这个功能：

/**
 * DisplayDate.java 该程序用于实现通过一个退出按钮来关闭这个程序
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
		display = Display.getDisplay ( this );// 提取系统设备的Display对象
		cmdExit = new Command ( "Exit",Command.SCREEN, 2 );//对该菜单的相应应用到当前整个屏幕
	}

	protected void startApp () throws MIDletStateChangeException
	{

		// 构造一个文本输入框TextBox组件，用于显示文本
		// 向构造函数传递了Calendar.getInstance ( ).getTime().toString ( )对象，
		// 该对象是系统时间对应的字符串
		textbox = new TextBox ( "Display data and time!",
				Calendar.getInstance ( ).getTime ( ).toString ( ), 256, TextField.ANY );

		//得到系统缺省的时区
		String[] timeZoneList = TimeZone.getAvailableIDs ( );
		for( int i=0;i<timeZoneList.length;i++)
		{	//插入到文本输入框textbox中
			textbox.insert ( "\n" + timeZoneList[i], textbox.getCaretPosition ( ) );
		}


		textbox.addCommand ( cmdExit );
		textbox.setCommandListener ( (CommandListener)this );

		// 将textbox设置为当前显示的组件
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
		// 对该命令的响应
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

J2ME配置概述

配置将基本运行时环境定义为一组核心类和一个运行在特定类型设备上的特定 JVM。虽然还可能在将来定义其他的配置，但当前 J2ME 存在两种配置：

连接限制设备配置 (CLDC) 特别与 KVM 一起用于内存有限的 16 位或 32 位设备。这是用于开发小型 J2ME 应用程序的配置（虚拟机）。（从开发的角度来看）它的大小限制让它比 CDC 更有趣、更具挑战性。CLDC 同时还是用于开发绘图工具应用程序的配置。 Palm 电脑便是一个运行小应用程序的小型无线设备的示例。我们将在 J2ME 配置一章中深入介绍 CLDC。

连接设备配置 (CDC) 与 C 虚拟机 (CVM) 一起使用，用于要求内存超过 2 兆的 32 位体系结构。互联网电视机顶盒便是这类设备的一个示例。虽然稍后我们将在 CDC API 一章中简要介绍 CDC，但它并不在本教程的范围内。

简表概述

简表定义了您的应用程序所支持的设备类型。特别地，它向 J2ME 配置添加了特定于域的类来定义设备的某种作用。简表建立在配置的顶部。已经为 J2ME 定义了两种简表：KJava 和移动信息设备简表 (MIDP)，它们也被建立在 CDLC 上。这两种简表适用于小型设备。

有一种纲要简表，您可以在它的上面创建自己的简表，这种纲要简表也称为基础表，可供 CDC 使用。然而，在本教程中，我们只重点介绍建立在 CLDC 顶部，适用于小型设备的简表。

我们将在后面的章节中讨论上述这些简表，还会使用 KJava 和 MIDP 建立一些示例应用程序。

J2ME 目标设备

使用 CLDC 开发的 J2ME 应用程序的目标设备通常具有以下特征：

可供 Java 平台使用的 160 到 512 千字节的总内存
功率有限，常常是电池供电
网络连通性，常常是无线的、不一致的连接并且带宽有限
用户接口混乱，程度参差不齐；有时根本就没有接口
一些 CLDC 支持的设备，包括无线电话、寻呼机、主流个人数字助手 (PDA)，以及小型零售支付终端。

依照 Sun Microsystems，CDC 的目标设备通常具有以下特征：

使用 32 位处理器
2 兆字节或更多可供 Java 平台使用的总内存
设备要求的 Java 2 “蓝皮书”虚拟机的全部功能
网络连通性，常常是无线的、不一致的连接并且带宽有限
用户接口混乱，程度参差不齐；有时根本就没有接口
一些 CDC 支持的设备，包括常驻网关、智能电话和通讯器、PDA、管理器、家用电器、销售网点终端以及汽车导航系统。


设计开发小型设备应用程序要注意的事项

为小型设备开发应用程序，需要您在设计阶段制定某种策略。最好是在开始编写代码之前，战略性地为小型设备设计应用程序。由于无法考虑到所有的 "gotchas" ，在开发应用程序之前更正代码是一件很痛苦的工作。

下面是一些可以考虑的设计策略：

保持程序简单。除去不必要的功能，如果可能的话，将它们做成独立的、次要的应用程序。

程序越小越好。这一点对所有的开发者来说应该是显而易见的。越小的程序占用的设备内存越少，并且花费的安装时间越少。可考虑将您的 Java 应用程序打包，作为压缩的 Java 档案 (jar) 文件。

运行时占用最少的内存。为尽可能减少运行时占用的内存，使用标量类型代替对象类型。同时，不依赖垃圾收集程序。您应该在使用完对象时将对象引用置空，这样可有效管理内存。另外一种减少运行时所需内存的方法是使用“惰性”实例，它仅在必需时才分配对象。其它一些减少小型设备上过量和峰值内存使用的方法有快速释放资源、重新使用对象以及避免异常。



设计开发移动设备应用程序的注意事项 第 3 页（共 6 页）




开发移动设备应用程序的规则与我们前面提及的开发小型设备的相同：先设计再编码。让我们检查一下开发移动设备应用程序时可考虑的一些设计建议：

让服务器做大部分的工作。将计算性较强的任务放到服务器上，让服务器为您做这些工作。让移动设备处理界面和最少的计算工作，而让服务器做繁重的工作。当然，您为其开发应用程序的移动设备对设备连接到服务器上的难易程度和频率有重要影响。

谨慎地选择编程语言。J2ME 仍然处于成长期，可能还不是最好的选择。根据您的需要，选择其它的面向对象语言，如 C++，可能会更好。



性能注意事项 第 4 页（共 6 页）

为性能而编码。下面有一些以获得最优性能为目标的编码方法：

使用局部变量。访问局部变量比访问类成员更快。

避免字符串串联。字符串串联不仅会降低性能，而且会增加应用程序的内存峰值占用量。


使用线程，避免同步。任何运行时间超过 1/10 秒的操作都需要一个独立的线程。避免同步同样能提高性能。

使用模型视图控制器 (MVC) 分离模型。MVC 将代码中控制显示的逻辑分离出来。






编译注意事项 第 5 页（共 6 页）

同其它的 Java 应用程序一样，您在打包和部署应用程序之前要先进行编译。尽管有了 J2ME，您仍然使用 J2SE 编译器并且需要用适当的选项来进行调用。

特别的，您需要使用 -bootclasspath 选项来指示编译器使用 J2ME 类，而不是 J2SE 类。不要在编译器的 CLASSPATH 中设置配置类。这样将导致运行时错误，因为不管 CLASSPATH 中有什么，编译器将首先自动搜索 J2SE 的核心类。换句话说，编译器将无法引用特定 J2ME 配置中缺少的类或方法，结果导致在尝试运行应用程序时出现运行时错误。



打包和部署注意事项 第 6 页（共 6 页）

由于 J2ME 是为内存有限的小型设备设计的。大部分常用的 Java 提前验证已经从虚拟机中除去以形成一个较小的覆盖区域。结果，在配置之前提前验证 J2ME 应用程序就很有必要。在运行时会附加一个检查以确保这个类在提前验证之后还没有改变过。

如何严格执行提前验证或者检查类的正确性依靠的是工具包。CLDC 提供一个称为提前验证的命令行实用程序，它能够进行实际的验证并且可以把一些额外的信息插入到类文件中去。MIDP 使用无线工具包，这种工具包提供一种 GUI 工具，也可从命令行运行这种工具。

部署工作取决于您要部署的平台。应用程序必须以一种适合 J2ME 设备类型的格式进行打包和配置，就如简表定义的那样。



J2ME 配置是什么？ 第 1 页（共 5 页）

正如前面所学，配置将基本运行时环境定义为一套核心类和一个运行在特定类型设备上的特定的 JVM。您也可以学到 J2ME 的两种配置类型是 CLDC 和 CDC。

Sun 提供的 J2ME 配置是适合不同层次的市场需求的 -- CLDC 适合小型设备，而 CDC 适合大型设备。J2ME 环境可以被动态地配置为提供运行应用程序所需要的环境，而不用考虑是否为设备提供了运行该应用程序所需的所有 Java 技术库。核心平台接收应用程序代码和库。运行在网络上的服务器软件执行配置工作。

J2ME 简表是什么? 第 1 页（共 4 页）

正如我们在前面教程中提及的，一个简表定义了受支持设备的类型。例如，移动信息设备简表 (MIDP)，定义了蜂窝电话的类。它把一些特定于域的类加入J2ME 配置中来定义对类似设备的使用。已经为 J2ME 定义了两个简表：KJava 和 MIDP 。它们都构建在 CLDC 之上。KJava 和 MIDP 都和 CLDC 及小型设备相关联。

简表被构建在配置的顶部。由于简表是特定于运行应用程序的设备的大小（内存的数量），所以，某个简表是与某种特定的配置相关联的。

在纲要简表上，您可以创建自己的简表，这种纲要简表也称为基础表，它对于 CDC 也是可用的。然而，在本教程和本节中，我们将只重点学习建立在 CLDC 上的 KJava 和 MIDP 简表。

简表 1：KJava 第 2 页（共 4 页）

KJava 是归 Sun 公司所有的简表，它包含 KJava API。KJava 简表建立在 CLDC 配置的顶部。KJava 虚拟机，KVM，像标准的 J2SE 虚拟机那样接受相同的字节代码和类文件格式。

KJava 包含一个特定于 Sun 的、运行在 Palm 操作系统上的 API。这个 KJava API 和 J2SE 抽象视窗工具包 (AWT) 有很多地方都是相同。然而，由于它不是一个标准的 J2ME 软件包，它的主软件包是 com.sun.kjava。在以后的教程中开发一些示例应用程序时会学到更多关于 KJava API 的知识。



简表 2: MIDP 第 3 页（共 4 页）

MIDP 适合诸如蜂窝电话和寻呼机等移动设备。MIDP 和 KJava 一样，也是建立在 CLDC 之上的，并且提供一个标准的运行时环境，允许在终端用户设备上动态地部署新的应用程序和服务。

MIDP 是一个公共的、为移动设备设计的工业标准简表，它不依赖某个特定的商家。对于移动应用程序开发来说，它是一个完整的、受支持的基础。

MIDP 包含下列软件包，前面 3 个是核心 CLDC 软件包，另加 3 个特定于 MIDP 的软件包。我们将在后面的教程中讨论每个软件包：

java.lang
java.io
java.util
javax.microedition.io
javax.microedition.lcdui
javax.microedition.midlet
javax.microedition.rms


UI 设计注意事项 第 2 页（共 6 页）

MIDP 包括一个低级的 UI API 和一个高级的 UI API。低级的 API 允许您完全访问一个设备的显示屏，也允许访问原始键和指针事件。然而，使用低级 API 时， 没有可用的用户界面控件。应用程序必须精确地绘制出按钮和其它所有的控件。

相反，高级 API 提供简单的用户界面控件但不能直接访问原始的输入事件或显示屏。由于显示屏的尺寸和 MIDP 设备输入方法的差异，控件显得很抽象。MIDP 的实现确定了绘制控件的方法，也确定了如何管理用户输入。

MIDP API 第 3 页（共 6 页）

MIDP 包含四个核心 CLDC 软件包 (java.lang、java.io、java.util 和 javax.microedition.io)，另加下面的三个特定于 MIDP 的软件包：

javax.microedition.lcdui
javax.microedition.midlet
javax.microedition.rms
我们将在本章的后面部分详细介绍特定于 MIDP 软件包。除了上面新的软件包之外，MIDP 还向核心 CLDC 软件包添加了四个新类，如下所示。

java.util.Timer -- 用于为后台线程中将来要执行的任务确定时间。


java.util.TimerTask -- 被 java.util.Timer 类使用，用来为后台线程中稍后的执行定义任务。


javax.microedition.io.HttpConnection -- 一个接口，为 HTTP 连接定义必要的方法和常量。

java.lang.IllegalStateException -- 一个 RuntimeException， 指出在不合法或不合适的时间已经调用的一个方法。

MIDlet 介绍  第 4 页（共 6 页）

MIDlet 是一个 Java 类，它扩展了 javax.microedition.midlet.MIDlet 抽象类。实现 startApp()、pauseApp()和 destroyApp()方法，这些方法类似于 J2SE 的 java.applet.Applet 类中的 start()、stop()和 destroy()方法。

除了扩充 javax.microedition.midlet.MIDlet 的主 MIDlet 类之外，一个 MIDP 应用程序通常还包括其它一些类，这些类能随它们的资源一起被打包成为 jar 文件 -- 称之为 MIDlet 套件。一个 MIDlet 套件中的不同 MIDlet 能共享 jar 文件的资源，尽管不同套件中的 MIDlets 不能直接相互作用。

MIDlet 在应用程序生命周期中有三种可能的存在状态 -- 运行状态、暂停状态、销毁状态。运行状态，正如其名称所暗示的，意味着 MIDlet 正在运行中。这种状态始于 startApp 方法被调用时。在暂停状态中，MIDlet 持有的所有资源将被释放，但是它准备着再次被运行。调用 notifyPaused 方法时，MIDlet 处于暂停状态。在销毁状态中，MIDlet 已经永久地将其自身关闭，释放所有的资源，等待着废物清理程序的处理。它是通过 notifyDestroyed 方法来调用的。

在接下来的两页中，我们来看一个简单的 HelloWorld MIDlet。


HelloWorld MIDlet 第 5 页（共 6 页）

与使用 KJava HelloWorld 应用程序一样，这个 MIDlet 也会在 MIDP 设备的显示屏上显示 "Hello World!" 和 Exit 按钮，按下该按钮会终止应用程序。

HelloWorld.java 文件以下面的代码行开始，这些代码行导入稍后会在 HelloWorld 类中使用的类:


      import javax.microedition.midlet.MIDlet;
      import javax.microedition.lcdui.Command;
      import javax.microedition.lcdui.CommandListener;
      import javax.microedition.lcdui.Display;
      import javax.microedition.lcdui.Displayable;
      import javax.microedition.lcdui.Form;

由于 HelloWorld 类是一个 MIDP 应用程序，它扩展了 MIDlet。它也实现 CommandListener 接口来处理事件：


      public class HelloWorld extends MIDlet implements CommandListener

下面的方法是一个缺省构造程序，它创建一个新表单，在上面初始化控件，然后显示出来：


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

调用 startApp() 方法启动应用程序与小应用程序的启动方法很象。在 MIDle 的一次执行中它可能会被调用多次。如果 MIDlet 暂停，pauseApp() 将会被调用。要重新启动 MIDlet，需调用 startApp()。仅须执行一次的主初始化代码应该放置在构造程序中：


      public void startApp()
      {
         // Get a reference to the display, and show the form
         Display display = Display.getDisplay(this);
         display.setCurrent( form );
      }

pauseApp() 被调用使得 MIDlet 处于暂停状态。在此应用程序中，当进入暂停状态时，我们没执行任何操作；但是我们仍然需要在 MIDlet 中实现 pauseApp 方法，因为它是父 MIDlet 类中的抽象方法。


      public void pauseApp() { }

destroyApp() 被调用，破坏了 MIDlet 并使其处于销毁状态。在此应用程序中，我们通过将引用设为 null，释放了对表单的引用。


      public void destroyApp(boolean unconditional)
      {
         form = null;
      }

commandAction() 方法是事件处理程序，被请求实现 CommandListener 接口。目前，它破坏了应用程序并通知应用程序管理软件 MIDlet 已经完成。


      public void commandAction(Command c, Displayable d)
         {
            // Destroy this MIDlet
            destroyApp(true);

            // Notify the application management software that this MIDlet
            // has entered the destroyed state
            notifyDestroyed();
         }



J2ME类继承关系(Package javax.microedition.lcdui)
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

J2ME程序都是从MIDlet类开始执行,MIDlet是J2ME项目文件的入口文件，也是必须的。
每个MIDP应用程序运行时所有用户界面组件的表演舞台都是Display类，
而这些用户组件在这个表演舞台上都扮演“可以显示的”角色，
根据这个逻辑关系，这些用户组件就必须设计为 Displayable 类的子类，
这些用户组件类又根据不同的需求而设计为两类：Canvas类和Screen类。

Display是一个系统设备显示和输入的管理中心,每一个MIDlet都必须有一个Display.
Display包含一些成员方法去提取系统属性和响应显示在系统设备的对象的请求。
一个 Display 上仅仅只能放置一个 Displayable 对象
（一个 Displayable 对象如：Canvas、Screen以及他们的子类）。
也就是说 Display 上的 Displayable 对象只能一个一个的出现。

下面看看一个例子，察看手机所支持的色彩：
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
 * 该程序用来判断移动电话屏幕所支持的色彩， 判断后将结果显示在手机屏幕上。
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
		display = Display.getDisplay ( this );// 提取系统设备的Display对象
		exitCommand = new Command ( "Exit", Command.SCREEN, 1 );// 对该菜单的相应应用到当前整个屏幕
	}

	protected void startApp () throws MIDletStateChangeException
	{
		// 构造一个文本输入框TextBox组件，用于显示文本
		TextBox textbox = new TextBox ( "", "", 256, TextField.ANY );
		// 创建一个Ticker，该Ticker在屏幕上来回滚动显示"Color..."
		textbox.setTicker ( new Ticker ( "Color..." ) );
		textbox.addCommand ( exitCommand );
		textbox.setCommandListener ( (CommandListener)this );

		if ( display.isColor ( ) )
		{
			textbox.setTitle ( "支持彩色" );
			textbox.setString ( "共有颜色: " + display.numColors ( ) + " 种。" );
		} else
		{
			textbox.setTitle ( "不支持彩色" );
			textbox.setString ( "共有颜色: " + display.numColors ( ) + " 种。" );
		}

		// 将textbox设置为当前显示的组件
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


Alert窗体的应用：
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
 * 该程序用来学习Alert控件的用法。
 * 不同的Alert类型会发出不同的声音。
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
	 * 构造函数
	 *
	 */
	public AlertsMIDlet()
	{
		display = Display.getDisplay ( this );// 提取系统设备的Display对象
		exitCommand = new Command ( "Exit", Command.SCREEN, 1 );// 对该菜单的相应应用到当前整个屏幕

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


CostomItem类
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
 * 该程序是用来学习CostomItem类的
 * 在Form主界面上显示一个自制的表格
 *
 * @author zieckey
 *
 */

public class CustomItenMIDlet2 extends MIDlet implements CommandListener
{

	protected void startApp () throws MIDletStateChangeException
	{
		Form form = new Form("UI　Ｄemo");
		form.append ( "你最喜欢的编程语言？\n" );
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
 * 该类是一个自制的表格，
 * 并且通过构造函数的字符串数组提供的信息构造合适大小的表格
 * @author zieckey
 *
 */
class Table extends CustomItem
{
	private String[]	elements;

	//构造函数，传入参数来时初始化类成员变量
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

	// 计算最佳内容显示高度
	protected int getPrefContentHeight ( int arg0 )
	{
		return getMinContentHeight ( );
	}

	// 计算最佳内容显示宽度
	protected int getPrefContentWidth ( int arg0 )
	{
		int max = 0;
		for ( int i = 0; i < elements.length; i++ )
		{
			// 得到该行文本宽度
			int w = Font.getDefaultFont ( ).stringWidth ( elements[i] );
			if ( max < w )
			{
				max = w;// 将最大的文本宽度放到max变量中
			}
		}
		return max;
	}

	protected void paint ( Graphics g, int w, int h )
	{
		// 使用白色填充整个界面
		g.setColor ( 0xffffff );
		g.fillRect ( 0, 0, w, h );
		g.setColor ( 0 );

		Font font = Font.getDefaultFont ( );
		int fontHeight = font.getHeight ( );//字体高度
		int lineHeight = fontHeight + 1;//行距

		// 绘制表格和字符串数组
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
 * 该程序是在窗口上显示自己创建的Item，显示一幅图像
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


Form控件
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
 * 该程序用来学习Form控件的用法。
 * 并在其上添加各种Item。
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
		exitCommand = new Command ( "Exit", Command.SCREEN, 1 );// 对该菜单的相应应用到当前整个屏幕
		buttonCommand = new Command ( "BUTTON MODLE", Command.ITEM, 2 );//Command.ITEM模式将会使命令响应后选中相应的Item组件
		linkCommand = new Command ( "HYPERLINK MODLE", Command.ITEM, 2 );

		st1 = new StringItem( "1","普通模式",StringItem.PLAIN);
		st2 = new StringItem( "2","按钮模式",StringItem.BUTTON);
		st3 = new StringItem( "3","连接模式",StringItem.HYPERLINK);

		//为BUTTON和HYPERLINK模式的StringItem按钮设置默认的 Command
		st2.setDefaultCommand ( buttonCommand );
		st3.setDefaultCommand ( linkCommand );
		//注册ItemCommandListener监听器
		st2.setItemCommandListener ( this );
		st3.setItemCommandListener ( this );

		form = new Form("UI Demo");//主窗口初始化
		form.append ( st1 );//添加Item到Form上
		form.append ( st2 );
		form.append ( st3 );

		form.addCommand ( exitCommand );//添加主窗口的命令响应
		form.setCommandListener ( this );//注册 Form 的监听器

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

	//当特定的Item上的Command被激活后，此方法就会被调用
	public void commandAction ( Command cmd, Item item )
	{
		if ( buttonCommand == cmd )
		{
			if ( st2 == item )
			{
				form.append ( "\n按钮模式被选中了！" );
			}
		} else if ( linkCommand == cmd )
		{
			if ( st3 == item )
			{
				form.append ( "\n链接模式被选中了！" );
			}
		}
	}
}



活用MIDP2.0的CustomItem类，改善J2ME程序界面(续1)
2．编写一个具有滚动条的表格

       分析滚动条的算法：假设参数变量

       数据高度 ch （已知），数据显示高度vh（已知），滚动条高度 sh（未知），

滚动区域高度 ah （已知），滚动速度speed（未知），滚动满足公式：

       speed * ( ah – sh ) = ch – vh ------------- (1)

       ch/vh = ah/sh            --------------(2)

根据(1)、(2) 可以得出：speed = ch/ah



全部源码如下：



CustomTable.java

------------------------------------------------------


package com.jlw.customitem;
/***
 * @author JiangLiwen , danxy2008@163.com , 2006-11-7
 */

import javax.microedition.lcdui.*;

public class CustomTable extends CustomItem {
  /** 定义表的属性 */
  private int rows = 0;
  private int cols = 0;
  private int dx = 50;
  private int dy = 20;

  /** 定义颜色 */
  private final static int titleColor[] = { 206, 223, 239 };
  private final static int rowsColor1[] = { 230, 230, 230 };
  private final static int rowsColor2[] = { 181, 227, 231 };

  /** 表头数据 */
  private String[] titles;

  /** 表数据内容 */
  private String[][] datas;

  /** 定义显示窗口大小 */
  private final static int winX = 220;
  private final static int winY = 180;

  /** 是否有出现滚动条 */
  private boolean isscroll = false;

  /** 数据绘制起始坐标 */
  private int dataY = 0;

  /** 数据内容高度 */
  private int ch = 0;

  /** 数据显示高度 */
  private int vh = 0;

  /** 滚动条高度 */
  private int sh = 0;

  /** 滚动条区域高度 */
  private int ah = 0;

  /** 滚动的偏移量 */
  private int offset = 0;

  /** 滚动的速度 */
  private int speed = 0;

  /** 响应键盘事件 */
  boolean horz;



  /**
   * 构造函数
   * @param name , 表名
   * @param ptitle , 表头（一惟数组）
   * @param pdata , 表内容数据（二惟数组）
   */
  public CustomTable(String name, String[] ptitle, String[][] pdata) {
    super(name);
    cols = ptitle.length;
    rows = pdata.length;
    titles = ptitle;
    datas = pdata;
    //初始化滚动条信息
    ch = rows * dy;
    if (ch > (winY - 20)) {
      isscroll = true;
      vh = winY - dy - 4;
      ah = winY - 2 * dy - 4;
      sh = (int) ((ah * vh) / ch) - 10;
      speed = ch / ah;
    }
    //判断交互模式
    int interactionMode = getInteractionModes();
    horz = ((interactionMode & CustomItem.TRAVERSE_HORIZONTAL) != 0);
  }

  /**
   * 绘制函数
   */
  protected void paint(Graphics g, int w, int h) {
    int y = 0;
    int oldColor = g.getColor();

    // 设置表格数据样式
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
    // 添加表格数据
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

    // 清空
    g.setColor(255, 255, 255);
    g.fillRect(0, 0, winX, 20);
    // 绘制表头区域
    int hx = winX;
    int hy = dy;
    g.setColor(titleColor[0], titleColor[1], titleColor[2]);
    g.fillRect(0, 0, hx, hy);
    // 绘制白色线条
    int temp = 0;
    g.setColor(255, 255, 255);
    g.drawLine(0, 0, hx, 0);
    for (int i = 0; i < cols; i++) {
      temp = i * dx + 1;
      g.drawLine(temp, 0, temp, hy);
    }
    // 绘制灰色线条
    g.setColor(128, 128, 128);
    g.drawLine(0, hy - 1, hx, hy - 1);
    for (int i = 0; i < cols; i++) {
      temp = (i + 1) * dx - 1;
      g.drawLine(temp, 1, temp, hy - 1);
    }
    // 填写标题数据
    g.setColor(0);
    for (int i = 0; i < cols; i++) {
      g.drawString(titles[i], dx / 2 + i * dx, 1, Graphics.HCENTER
          | Graphics.TOP);
    }
    // 补充表头右边边框
    g.setColor(255, 255, 255);
    g.drawLine(winX - 19, 1, winX - 19, dy - 1);
    g.setColor(128, 128, 128);
    g.drawLine(winX - 1, 1, winX - 1, dy - 1);
    // 绘制表底线条
    g.setColor(titleColor[0], titleColor[1], titleColor[2]);
    if (isscroll) {
      g.fillRect(0, winY - 2, winX - 20, 2);
    } else {
      g.fillRect(0, winY - 2, winX, 2);
    }
    // 绘制滚动条
    if (isscroll) {
      // 绘制滚动条背景
      g.setColor(220, 220, 220);
      g.fillRect(winX - 19, dy + 1, winX - 20 - 1, winY - dy - 20);
      // 绘制滚动条下面方块
      g.setColor(titleColor[0], titleColor[1], titleColor[2]);
      g.fillRect(winX - 19, winY - dy - 1, 19, dy);
      g.setColor(255, 255, 255);
      g.fillRect(winX - 19, winY - dy, 19, 1);
      g.fillRect(winX - 19, winY - dy, 1, dy - 1);
      g.setColor(128, 128, 128);
      g.fillRect(winX - 1, winY - dy, 1, dy - 1);
      g.fillRect(winX - 19, winY - 1, 19, 1);
      // 绘制滚动块
      g.setColor(titleColor[0], titleColor[1], titleColor[2]);
      g.fillRect(winX - 19, dy + offset, 19, sh);
      g.setColor(255, 255, 255);
      g.fillRect(winX - 19, dy + offset, 19, 1);
      g.fillRect(winX - 19, dy + offset, 1, sh);
      g.setColor(128, 128, 128);
      g.fillRect(winX - 1, dy + offset, 1, sh);
      g.fillRect(winX - 19, dy + offset + sh, 19, 1);
      // 绘制三角形
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
 * 该程序是用来学习StringItem类的
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

		exitCommand = new Command( "退出", Command.EXIT, 2 );
		buttonCommand = new Command( "按钮模式00", Command.ITEM, 2 );
		linkCommand = new Command( "超链接模式44", Command.ITEM, 2 );

		buttonAlert = new Alert( "Alarm", "按钮模式的StringItem被选中了", null,
				AlertType.ALARM );
		linkAlert = new Alert( "Alarm", "超链接模式的StringItem被选中了", null,
				AlertType.ALARM );
		
		display = Display.getDisplay( this );
		st1 = new StringItem( "1", "普通文本", StringItem.PLAIN );
		st2 = new StringItem( "2", "按钮文本模式", StringItem.BUTTON );
		st3 = new StringItem( "3", "超链接文本模式", StringItem.HYPERLINK );
	}

	protected void startApp() throws MIDletStateChangeException
	{
		

		{ // 下面四行如果没有的话，st1、st2、st3三类外观的显示效果一样
			// 原来，还需要指定Item.BUTTON等外观的命令和命令监听器

			// 为BUTTON和HYPERLINK模式的StringItem设置默认的Command
			st2.setDefaultCommand( buttonCommand );
			st3.setDefaultCommand( linkCommand );

			// 注册监听器
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
			// System.out.print( "按钮模式的StringItem被选中了" );
			display.setCurrent( buttonAlert );
		} else if ( cmd == linkCommand && item == st3 )
		{
			System.out.print( "超链接模式的StringItem被选中了" );
			display.setCurrent( linkAlert );
		}
	}

	public void commandAction( Command cmd, Displayable arg1 )
	{
		// 对该命令的响应
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
开发应用程序下载到手机里.
开发环境是Eclipse＋EclipseMe
1、Jar文件无效。在模拟器上能正常运行应用程序，但却不能配置到智能手机上，提示Jar文件无效（在Nokia N73上）。在网上搜索资料说得比较简单，还是没有找到解决的办法，偶尔打开了jad的配置文件，发现问题出现在jad文件上。如下面所示，第一个是不能配备的jad设置，第二个是能正常配置到手机上的配置。

错误：

MIDlet-Jar-Size: 2150
MIDlet-Jar-URL: J2ME.jar
MIDlet-Name: J2ME Midlet Suite
MIDlet-Vendor: Midlet Suite Vendor
MIDlet-Version: 1.0.0
MicroEdition-Configuration: CLDC-1.1
MicroEdition-Profile: MIDP-2.0



正确：？？？？

MIDlet-1: AlertsMIDlet,,J2ME.AlertsMIDlet
MIDlet-Jar-Size: 2150
MIDlet-Jar-URL: J2ME.jar
MIDlet-Name: J2ME Midlet Suite
MIDlet-Vendor: Midlet Suite Vendor
MIDlet-Version: 1.0.0
MicroEdition-Configuration: CLDC-1.1
MicroEdition-Profile: MIDP-2.0
似乎上面的也不正确，因为安装后运行不对。

正确的应该是：

MIDlet-1: J2ME,,AlertsMIDlet
MIDlet-Jar-Size: 2150
MIDlet-Jar-URL: J2ME.jar
MIDlet-Name: J2ME Midlet Suite
MIDlet-Vendor: Midlet Suite Vendor
MIDlet-Version: 1.0.0
MicroEdition-Configuration: CLDC-1.1
MicroEdition-Profile: MIDP-2.0




说明:J2ME是项目名,AlertsMIDlet是类名
对比分析可知，这是配置文件缺少应用程序名称造成的，因此手机就不能把相应的应用程序安装，而提示Jar文件无效。

下面是一个正确的例子：
MIDlet-1: FirstJ2MEProject, FirstJ2MEProject.png, Hello
MIDlet-Jar-Size: 996
MIDlet-Jar-URL: FirstJ2MEProject.jar
MIDlet-Name: FirstJ2MEProject
MIDlet-Vendor: Unknown
MIDlet-Version: 1.0
MicroEdition-Configuration: CLDC-1.0
MicroEdition-Profile: MIDP-2.0

用WKT的KToolbar打包的程序可以运行完好。
MIDlet-1 这一行的格式:

MIDlet-1: 程序在手机上显示的名字, 手机上显示的程序图标, 类名(注意包括包名)




1.用WKT打包
运行KToolbar
点击New Project。
Project Name：任意（英文）。
MIDLet Class Name：你的j2me程序的Midlet类名（比如之前的HelloWorld例子就输入HelloWorld）。
点击Create Project。

把你写好的.java文件（比如之前的HelloWorld例子就是HelloWorld.java）拷贝到刚才创建的Project目录下的src目录里。打包：打包成功后会在project目录下的bin目录里会有两个文件一个jad和一个jar文件，这两个文件就是我们要上传到手机的文件




MMAPI

一般来讲，多媒体的处理一般可以分为两部分

处理数据传输协议
	协议处理就是指的把数据从一个源（文件、抓取装置、流媒体服务器等。）里面读到媒体处理系统里面。

处理数据内容
	内容处理一般指处理数据（例如解码）和把媒体从输出设备（喇叭，屏幕等）上展现出来。
	
	所以在这些API里面有两个高度抽象的对象，数据源、播放器，任何对象都可以分成这两个部分进行处理。
DS用来处理协议,Player用来处理内容 

	一个数据源被封装在协议处理里面。它屏蔽了数据是如何从它的源里面被读出来的，无论这个数据是从文件，流媒体还是其它的一些机制中得来得。数据源也提供了一些方法的数据集合以允许播放器从它里面读出数据并处理。

   播放器从数据源里面读出数据，处理数据，并把他妈解释到输出设备上。它提供了一些方法集用来控制媒体的回放和基本的同步。播放器也提供了一些方法以获得特定媒体的特性。

  使用工厂模式，管理器从DS里面产生Player。为了方便管理器同样也提供了方法本地和输入流里面产生Player。 

Player，是一个接口，用来处理和播放多媒体数据；一个Player的实例分析处理来自DataSource的数据，然后管理播放器的生命周期，和不同的重放特征
DataSource，是一个抽象类，封装了数据的定位和提取，代表一个协议的控制者

一个Player有五个状态: 未实例化状态、实例化状态、预获取状态、开始状态、关闭状态

eclipse调试j2me程序方法
使用EclipseMe插件，在preference 里边把Java--Debug的Debuger timeout 调到15000ms，同时确认suspend execution on uncaught exceptions 和suspend executioen on complication errors没有被选中，然后debug的时候，debug as Emulated midlet，然后就可以调试了。 


最简单的J2ME播放器

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


注意：音频文件boo.wav在res目录下

Player的VolumeControl数值为0~100


MMA可选包音乐播放功能详解(


我又一个大胆的设想，也许你可以试着先把fc读取出来的文件读成byte[]，再将byte[]->ByteArrayInputStream，然后再传递给Manager.createPlayer试一下。
如果，直接从jar包中可以的话，我觉得问题应该出现在fc api的实现上，也许这么转换一下能解决问题。
我就是这么一想，不保证成功哦



深入J2ME配置层

    * 深入J2ME配置层

      Java 2 Micro Edition (J2ME)是建立在一个由profiles，配置，虚拟机和主持操作系统等部分所组成的标准架构之上的。这些内容组成了完整的J2ME实时运行环境。图 A显示了这些部分是如何结合在一起的。J2ME提供了两种配置：Connected Limited Device Configuration (CLDC)和the Connected Device Configuration (CDC)。这两种配置以设备的内存footprint为基础面向不同的设备类型。

      配置指定了最小的功能组和相关的Java 虚拟机 (JVM)应支持的Java类库。从概念上讲，配置层在虚拟机 (VM)的顶端运行，但当你使用一个例如CLDC和CDC的配置时，你也会涉及到相关的VM，因为二者是紧密相连的。

      然而，应该注意的是在J2ME中，配置并不附属于一个特定的VM，他可以与其它的VM工作并支持所需的库。例如，CLDC也可以和应用指定基础功能的VM共同工作。关于细节，请见CLDC HotSpot应用虚拟机白页。

      为了帮助你理解J2ME配置层所扮演的角色，我将对CLDC和CDC分别地进行阐述。

      CLDC
      CLDC是针对少于512KB内存footprint的设备的配置。CLDC采用的是KVM，它是高度优化的JVM方式，他针对的是16比特或32比特的微处理器，160到512 KB内存为基础的低端，网络连接，电池驱动的设备。典型的内存要求是128KB做有来存储KVM和相关的库。更多关于KVM的信息可以从Sun公司的 KVM白页中得到。

      就网络化而言，CLDC针对的是有限的和间歇性的无线连接设备，所有在J2ME CLDC之上运行的应用软件都应能在其他任何高端的Java VM上运行。当然，这需要CLDC库的支持。CLDC配置关注于I/O，网络化，安全问题，国际化问题和核心Java库等相关的领域。

      与事件处理，用户和应用程序的互动，应用程序生存期管理等内容相关的领域是由Profile来处理的。使用界面定义（对于特定的设备，如传呼机，移动电话和PDA）也在Profile层的范围之内，它建立在顶端之上，并使用J2ME配置。Mobile Information Device Profile (MIDP)是一个J2ME profile，它定义了使用CLDC配置设备的用户界面相关的规范。

      CLDC从J2SE获得绝大多数的类，但一些针对小内存footprint设备的新类并不是从J2SE APIs获得的。关于类从J2SE 做继承和新CLDC类的具体信息，可参考CLDC规范1.0a版本的6.2和6.3中的内容。Java语言规范中的一些例外是没有浮点支持，没有类实例的完成化支持和有限的错误处理能力。

      在这里提到CLDC HotSpot应用也是具有相关性的，它相当于使用CLDC配置的设备的KVM中Java VM的替换。根据Sun公司，CLDC HotSpot执行VM是一个高性能的JVM（32位，采用CLDC v1.0规范）。他在相同的内存footprint上运行时提供比KVM高出一个数量级的更佳的性能。

      CDC：完全Java平台
      CDC是应用在具有较大内存，特别是2MB以上的设备上的，CDC针对有限和间歇的无线连接设备，CDC与CVM和Foundation profile共同定义了完全的J2ME环境。

      CVM是为用户和嵌入设备设计的完全功能性JVM，它支持所有的Java 2 v1.3 VM安全防护，JNI, JVMDI, RMI，弱引用功能和库。本质上说，CVM具有所有一个驻留桌面系统的JVM所具有的功能。

      CDC由J2SE中最小的Java数据包组成。Foundation profile由用户设备所需要的保持类库和APIs所组成。因此，如果你工作在一个以CDC为基础的J2ME环境下，你就需要更新你代码以使APIs更新换代。

      CDC是CLDC的一个扩展集，所以在两种配置之间存在着向上的兼容性。CDC和Foundation profile也提供了对使用PersonalJava实时规范开发的应用程序的完全兼容。

      总结
      J2ME模式体系使能了不同设备类别的“特别版”Java的创建。随着越来越多的设备制造商开始接受J2ME技术和J2ME设备使用范围的增大，更新的 J2ME profiles将得到应用。通过为开发以Java为基础的设备提供一个公共最小化平台，J2ME配置用结构化的方式使能了这些Java特别版本。 


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
