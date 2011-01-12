2006/12/09
EclipseÊ¹ÓÃ£º
ÏÂÔØ:www.eclipse.org/downloads
ÏÂÔØÖĞÎÄÖ§³Ö²å¼ş:
download.eclipse.org/eclipse/downloads
Õâ¸öÒ³ÃæÓĞ¸ö: Language_Packs


°²×°JDK,
È»ºó½âÑ¹eclipse-SDK-3.2.1-win32.zip,½âÑ¹ºó¾Í¿ÉÒÔÖ±½ÓÓÃÁË.
ÈçÖĞÎÄÖ§³Ö²å¼şÒ²·ÅÔÚÍ¬Ò»Ä¿Â¼ÖĞ,ÄÇÃ´È±Ê¡µÄÓïÑÔ¾ÍÊÇÖĞÎÄÁË,
ÕâÊ±Èç¹ûÏëÇĞ»»»ØÓ¢ÎÄ,¿ÉÒÔ·¢ËÍÒ»¸ö¿ì½İ·½Ê½µ½×ÀÃæ:
ÓÒ¼üÑ¡Ôñ"ÊôĞÔ"±à¼­"Ä¿±ê"ÔÚºóÃæÌí¼Ó: -nl en ,ÈçÏÂ:
"C:\Program Files\Java\eclipse\eclipse.exe" -nl en
ÁíÍâ»¹¿ÉÒÔÍ¨¹ıÕâÖÖ·½Ê½Ö¸¶¨¹¤×÷Ä¿Â¼,¼ÓÉÏ -data ²ÎÊı¾ÍºÃÁË
"C:\Program Files\Java\eclipse\eclipse.exe" -nl en -data f:\workspace

²é¿´ eclipse ÊÇ·ñÕÒµ½ÁËµçÄÔÉÏ°²×°µÄ jre »·¾³:
µã»÷"Windows->Preferences->Java->Installed JREs"
Èç¹ûÃ»ÓĞÕÒµ½,¿ÉÒÔÑ¡Ôñ"Add..."
È»ºó×Ô¼ºÑ¡ÔñÒ»¸ö"JRE home directory:"



±àÒëµÚÒ»¸öEclipseµÄJava³ÌĞò.

File->New->Project...
Ñ¡Ôñ Java Project ºó£¬µã»÷ Next£¬ÊäÈë¹¤³ÌÃû×Ö£ºhello£¬µã»÷ Finish £¬¾Í´´½¨À­Ò»¸ö¹¤³Ì¡£
ÔÚ×ó±ßWorkspaceÖĞ¿´µ½helloÕâ¸ö×Ö·û´®Ã»£¿
ÓÒ¼üµã»÷Ëü£¬File->New->Source Folder£¬ÊäÈësrc£¬µã»÷Finish£¬ÕâÑù¾Í½¨Á¢ÁËÒ»¸öSourceÎÄ¼ş¼Ğ¡£
ÓÒ¼üµã»÷ÎÒÃÇ¸Õ½¨Á¢µÄ src ÎÄ¼şÃû £¬Ñ¡ÔñNew->Class,ÊäÈëÀàÃû×Ö£ºhello£¬µã»÷ Finish¡£
Õâ¸öÊ±ºòÔÚEclipseµÄÖĞ¼ä³öÏÖÁË±à¼­½çÃæ£¬ÊäÈëÒ»ÏÂÄÚÈİ£º
public class hello {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.println( "Hello world! My Java!" );
	}

}

±£´æ£¬ÏÖÔÚ¿ÉÒÔ±àÒëÁË¡£
ÔÚ×ó±ßWorkspaceÖĞ¿´µ½ hello.java Õâ¸ö×Ö·û´®Ã»£¿
ÓÒ¼üµã»÷Ëü£¬Ñ¡Ôñ Run as -> 1 Java Application ÕâÑù¾Í¿ÉÒÔ±àÒëÀ­
ÔÚEclipseµÄÖĞÏÂ²¿µÄConsole¶Ô»°¿òÖĞÊä³ö£º
Hello world! My Java!
ÊÇ²»£¿


ÈÃµÚÈı·½jar°üÌí¼Óµ½eclipse»·¾³ÖĞ
Project->Properties->Java Build Path->Libraries Ñ¡Ôñ Add Extenal JARs£¬È»ºó¾Í¿ÉÒÔÑ¡ÔñµÚÈı·½jar°ü

Eclipse×Ô¶¯¹¹½¨¹¦ÄÜÈÃÎÒÃÇ±àÒë³ÌĞòºÜ¿ìµÄ¾Í¿ÉÒÔÍê³É£¬
ÕâÊÇÒòÎªÃ¿´ÎÎÒÃÇ±£´æÎÄ¼şµÄÊ±ºò£¬Eclipse¾Í°ïÎÒÃÇ×Ô¶¯±àÒëÁË¡£
µ±È»ÎÒÃÇÒ²¿ÉÒÔÈ¡ÏûÕâ¸ö×Ô¶¯¹¹½¨¹¦ÄÜ£º
È¡Ïû Project->Build Automatically Ç°ÃæµÄ¹´£¬¾Í¿ÉÒÔÈ¡Ïû×Ô¶¯±àÒë¹¦ÄÜ

ÎÒÃÇ»¹¿ÉÒÔÇåÀí±àÒë¹ıµÄÖĞ¼äÎÄ¼ş£¬Ñ¡Ôñ Project->Clean ¾Í¿ÉÒÔÁË


JavaµÄµ÷ÊÔ£º
{
	ÉèÖÃ¶Ïµã£º
	ÔÚ±à¼­ÇøÓòµÄ×ó±ß¿òÉÏË«»÷¾Í¿ÉÒÔ´´½¨»òÉ¾³ı¶Ïµã
	»òÕß±à¼­ÇøÓòµÄ×ó±ß¿òÉÏÓÒ»÷Ñ¡ÔñToggle breakpointÀ´ÉèÖÃ¶Ïµã.
	Ñ¡Ôñ Debug As ¾Í¿ÉÒÔµ÷ÊÔ³ÌĞòÁË

	²ì¿´±äÁ¿Öµ:
	Ñ¡ÖĞ±äÁ¿È»ºóÓÒ»÷Ñ¡ÔñWatch¾Í¿ÉÒÔÁË,»òÕßÑ¡Ôñ Window->Show View->Display,
	ÔÚDisplay´°¿ÚÖĞÊäÈëÏëÒª²é¿´µÄ±äÁ¿¾Í¿ÉÒÔÁË.

	´Óµ÷ÊÔ×´Ì¬»Øµ½Ô­Ê¼±à¼­×´Ì¬:ÏÈÍ£Ö¹µ÷ÊÔÔËĞĞ,
	È»ºóÑ¡ÔñÓÒÉÏ½ÇµÄJava±êÇ©¾Í¿ÉÒÔ»Øµ½Java Perspective

	ÉèÖÃÌõ¼ş¶Ïµã£º
	ÔÚ¶ÏµãÉÏÓÒ»÷£¬Ñ¡Ôñ breakpoint Properties->Enable Condition,
	È»ºóÔÚEnable ConditionÏÂµÄÊäÈë¿òÖĞÊäÈëÌõ¼ş¾Í¿ÉÒÔÁË¡£

	Òì³£¶Ïµã£º
	ÔÚdebugÊÓÍ¼ÖĞµÄBreakpoints½çÃæÉÏÓĞÒ»¸öAdd Java Exception breakpoint°´Å¥£¬
	¿ÉÒÔÌí¼Ó³öÏÖÒì³£µÄ¶Ïµã£¬ÕâÑù³ÌĞò³öÏÖÒì³£Ê±£¬»áÔÚ³ÌĞòÒì³£µÄµØ·½Í£ÏÂÀ´
}


µ±EclipseÌáÊ¾´úÂëÖĞ³öÏÖ´íÎó»òÕß¾¯¸æÊÇ£¬³¢ÊÔ×Åµç»÷ÄÇ¸öºìÉ«µÄ²æ²æ»ò»ÆÉ«µÄĞ¡¶«Î÷£¬
ÕâÑù»áµ¯³öÒ»Ğ©ÓĞÓÃµÄ±à¼­Ñ¡Ïî£¬ÎÒÃÇË«»÷ÏàÓ¦µÄÑ¡Ïî»á¿ìËÙ°ïÎÒÃÇ½â¾öÕâĞ©´íÎó»ò¾¯¸æ¡£

×Ô¶¯Éú³Éset¡¢get·½·¨µÄ¹¦ÄÜ£º
{
	¼ÙÈçÎÒÃÇÓĞÕâÑùÒ»¸öÀà£º
	public class PersonInfo {
		String name;
		int age;
	}
	ÏÖÔÚÎÒÃÇÏëÎªËüÌí¼Óset¡¢get·½·¨£¬ÄÇÃ´¿ÉÒÔÑ¡Ôñ£ºSource->Generate Getters and Setters...
	Ñ¡Ôñºó£¬¾Í¿ÉÒÔ¿´µ½EclipseÎªÎÒÃÇÉú³ÉÁËset¡¢get·½·¨£¬ÈçÏÂ£º
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

	ÕâÀï»¹¿ÉÒÔÎªÎÒÃÇÉú³É¹¹Ôìº¯Êı£¬ÄÇÃ´¿ÉÒÔÑ¡Ôñ£ºSource->Generate Constructor using Fields...
	Ñ¡Ôñºó£¬¾Í¿ÉÒÔ¿´µ½EclipseÎªÎÒÃÇÉú³ÉÁË¹¹Ôì·½·¨£¬ÈçÏÂ£º
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

	Ò²¿ÉÒÔÉú³ÉÖØÔØ¸¸ÀàµÄ¹¹Ôìº¯ÊıSource->Generate Constructor From superclass...
}

×Ô¶¯Éú³ÉJavaDoc
{
	/**		×¢Ã÷£ºÔÚ´Ë´¦°´Enter¼ü
	public PersonInfo(String name, int age) throws IOException {
		super();
		this.name = name;
		this.age = age;
	}

	¾Í»á×Ô¶¯°ïÎÒÃÇÉú³É×¢ÊÍ£º
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

´úÂëµÄ×Ô¶¯Íê³É£ºAlt+/
´úÂë¸ñÊ½»¯¹¦ÄÜ£ºCtrl+Shift+F
	ÕâÀï¿ÉÒÔ×Ô¶¨Òå×Ô¼ºµÄ¸ñÊ½£ºwindow->Properties

jar°ü¹ØÁªÔ´´úÂë£ºAttach Source
¿ìËÙ´ò¿ªÎÄ¼ş£ºNavigate->Open Type...
´ò¿ªÒ»¸öÀàµÄ¼Ì³Ğ¹ØÏµ£ºÔÚ±à¼­Æ÷ÖĞÑ¡Ôñ¸ÃÀà£¬ÓÒ¼üÑ¡Ôñ¡°Open Type Hierarchy¡±
´ò¿ª·½·¨µ÷ÓÃ,·½·¨±»ÄÇĞ©µØ·½µ÷ÓÃÁË:±à¼­Æ÷ÖĞÑ¡Ôñ¸Ã·½·¨£¬ÓÒ¼üÑ¡Ôñ¡°Open Call Hierarchy¡±

Eclipse¸ß¼¶²Ù×÷:Ô¶³Ìµ÷ÊÔ
JPDA

Eclipse²å¼şµÄ°²×°:
1. ÔÚÏß°²×°:
Ò»´ÎÑ¡ÔñHelp->Software Updates->..........
Ö®ºó¾ÍÊÇÊäÈëÍøÖ·¾Í¿ÉÒÔÁË
2. Ö±½Ó½âÑ¹°²×°£¬Èç¹ûÃ»ÓĞ°²×°³É¹¦£¬¾Í¿ÉÒÔ½«eclipseµÄ°²×°Ä¿Â¼ÏÂµÄconfiguration\org.eclipse.updateÄ¿Â¼É¾³ı¾Í»áÈÃeclipseÈ¥¸üĞÂ²å¼ş¡£
3. ÓÃlinkµÄ·½Ê½°²×°
ÏÈ°Ñ²å¼ş½âÑ¹µ½Í¬Ò»Ä¿Â¼Èç£º
d:\Myplugins
Ò»¶¨±£³ÖÏìÓ¦µÄÄ¿Â¼½á¹¹,ÈçLomboz:
Lomboz\eclipse\features
Lomboz\eclipse\plugins

ÔÚeclipseµÄÄ¿Â¼ÖĞ½¨Á¢Ò»¸ölinksÄ¿Â¼
²¢½¨Á¢Ò»¸öLomboz.txt ÄÚÈİÈçÏÂ
path=D:\\Myplugins\\Lomboz

»òÕß
path=D:/Myplugins/Lomboz
£¨×¢ÒâÕâÀïÊÇ·´Ğ±¸Ü/£¬¶ø²»ÊÇ\£©
ËµÃ÷£º
	1. ²å¼ş¿ÉÒÔ·Ö±ğ°²×°ÔÚ¶à¸ö×Ô¶¨ÒåµÄÄ¿Â¼ÖĞ¡£
	2. Ò»¸ö×Ô¶¨ÒåÄ¿Â¼¿ÉÒÔ°²×°¶à¸ö²å¼ş¡£
	3. linkÎÄ¼şµÄÎÄ¼şÃû¼°À©Õ¹Ãû¿ÉÒÔÈ¡ÈÎÒâÃû³Æ£¬±ÈÈçddd.txt£¬myplugin¶¼¿ÉÒÔ¡£
	4. linkÎÄ¼şÖĞpath=²å¼şÂ¼µÄpathÂ·¾¶·Ö¸ôÒªÓÃ\\»òÊÇ/
	5. ÔÚlinksÄ¿Â¼Ò²¿ÉÒÔÓĞ¶à¸ölinkÎÄ¼ş£¬Ã¿¸ölinkÎÄ¼şÖĞµÄpath²ÎÊı¶¼½«ÉúĞ§¡£
	6. ²å¼şÄ¿Â¼¿ÉÒÔÊ¹ÓÃÏà¶ÔÂ·¾¶¡£
	7. ¿ÉÒÔÔÚlinksÄ¿Â¼ÖĞ½¨Á¢Ò»¸ö×ÓÄ¿Â¼£¬×ªÒÆÔİÊ±²»ÓÃµÄ²å¼şµ½´Ë×ÓÄ¿Â¼ÖĞ£¬¼Ó¿ìeclipseÆô¶¯¡£
	8.  Èç¹û°²×°ºó¿´²»µ½²å¼ş£¬°Ñeclipse Ä¿Â¼ÏÂµÄconfigurationÄ¿Â¼É¾³ı£¬ÖØÆô¼´¿É¡£


³£ÓÃ²å¼ş:
Êı¾İ¿â¹ÜÀí:SQLExplorer
GUI:SWT-Designer
·´±àÒë:Jode
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

±£´æ£¬ÏÖÔÚ¿ÉÒÔ±àÒëÁË¡£
ÔÚ×ó±ßWorkspaceÖĞ¿´µ½ hello.java Õâ¸ö×Ö·û´®Ã»£¿
ÓÒ¼üµã»÷Ëü£¬Ñ¡Ôñ Run as -> 1 Java Application ÕâÑù¾Í¿ÉÒÔ±àÒëÀ­
ÔÚEclipseµÄÖĞÏÂ²¿µÄConsole¶Ô»°¿òÖĞÊä³ö£º
Hello world! My Java!
ÊÇ²»£¿









2006/12/17
ËïöÎJavaÎŞÄÑÊÂ---1
JDK£ºJava Develop Kit £¬¼´Java¿ª·¢¹¤¾ß°ü
JRE£ºJava Runtime Environment£¬¼´JavaÔËĞĞ»·¾³

J2SE£ºhttp://java.sun.com/j2se/1.4.2/download.html
J2EE£º
J2ME£º

http://java.sun.com/j2se/1.4.2/download.html
ÏÂÃæÓĞJava 2 Platform¡¢DocumentÏÂÔØ
ÁíÍâ£¬http://java.sun.com/docs/books/tutorial/information/download.html¿ª·¢Ö¸ÄÏ

¿ª·¢Ö¸ÄÏºÍ°ïÖúÎÄµµÊÇµ¥¶ÀÏÂÔØµÄ.



JavaÀ´×ÔÓÚSun¹«Ë¾µÄÒ»¸ö½ĞGreenµÄÏîÄ¿£¬ÆäÔ­ÏÈµÄÄ¿µÄÊÇÎª¼ÒÓÃÏû·Ñµç×Ó²úÆ·¿ª·¢Ò»¸ö·Ö²¼Ê½´úÂëÏµÍ³£¬ÕâÑùÎÒÃÇ¿ÉÒÔ°ÑE-mail·¢¸øµç±ùÏä¡¢µçÊÓ»úµÈ¼ÒÓÃµçÆ÷£¬¶ÔËüÃÇ½øĞĞ¿ØÖÆ£¬ºÍËüÃÇ½øĞĞĞÅÏ¢½»Á÷¡£¿ªÊ¼£¬×¼±¸²ÉÓÃC++£¬µ«C++Ì«¸´ÔÓ£¬°²È«ĞÔ²î£¬×îºó»ùÓÚC++¿ª·¢ÁËÒ»ÖÖĞÂµÄÓïÑÔOak£¨JavaµÄÇ°Éí£©£¬OakÊÇÒ»ÖÖÓÃÓÚÍøÂçµÄ¾«ÇÉ¶ø°²È«µÄÓïÑÔ£¬Sun¹«Ë¾ÔøÒÔ´ËÍ¶±êÒ»¸ö½»»¥Ê½µçÊÓÏîÄ¿£¬µ«½á¹û±»SGI´ò°Ü¡£¿ÉÁ¯µÄOak¼¸ºõÎŞ¼Ò¿É¹é£¬Ç¡ÇÉÕâÊ±Mark Ardreesen¿ª·¢µÄMosaicºÍNetscapeÆô·¢ÁËOakÏîÄ¿×é³ÉÔ±£¬ËûÃÇÓÃJava±à ÖÆ ÁËHotJavaä¯ ÀÀÆ÷£¬µÃµ½ÁËSun¹«Ë¾Ê×Ï¯Ö´ĞĞ¹ÙScott McNealyµÄÖ§³Ö£¬´¥·¢ÁËJava½ø ¾üInternet¡£ JavaµÄÈ¡ÃûÒ²ÓĞÒ»ÔòÈ¤ÎÅ£¬ÓĞÒ»Ìì£¬¼¸ Î»Java³ÉÔ±×éµÄ»áÔ±ÕıÔÚÌÖÂÛ¸øÕâ¸öĞÂµÄÓïÑÔÈ¡Ê²Ã´Ãû×Ö£¬µ±Ê±ËûÃÇÕıÔÚ¿§·È¹İºÈ×ÅJava(×¦ÍÛ)¿§ ·È£¬ÓĞÒ»¸öÈËÁé»úÒ»¶¯Ëµ¾Í½ĞJavaÔõ Ñù£¬µÃµ½ÁËÆäËûÈËµÄÔŞÉÍ£¬ÓÚÊÇ£¬JavaÕâ¸öÃû×Ö¾ÍÕâÑù´«¿ªÁË¡£

ÒòÎªJavaÊÇ
¼òµ¥µÄ
{
	Java×î³õÊÇÎª¶Ô¼ÒÓÃµçÆ÷½øĞĞ¼¯³É¿ØÖÆ¶øÉè¼ÆµÄÒ»ÖÖÓïÑÔ£¬Òò´ËËü±ØĞë¼òµ¥Ã÷ÁË¡£JavaÓïÑÔµÄ¼òµ¥ĞÔÖ÷ÒªÌåÏÖÔÚÈı¸ö·½Ãæ£º
	             1¡¢JavaµÄ·ç¸ñÀàËÆÓÚC++£¬Òò¶øC++³ÌĞòÔ±³õ´Î½Ó´¥JavaÓïÑÔ£¬¾Í»á¸Ğµ½ºÜÊìÏ¤¡£´ÓÄ³ÖÖÒâÒåÉÏ½²£¬JavaÓïÑÔÊÇC¼°C++ÓïÑÔµÄÒ»¸ö±äÖÖ£¬Òò´Ë£¬C++³ÌĞòÔ±¿ÉÒÔºÜ¿ìµØÕÆÎÕJava±à³Ì¼¼Êõ¡£
	             2¡¢JavaŞğÆúÁËC++ÖĞÈİÒ×Òı·¢³ÌĞò´íÎóµÄÒ»Ğ©ÌØĞÔ£¬ÈçÖ¸Õë¡¢½á¹¹¡¢Ã¶¾ÙÒÔ¼°ÄÚ´æ¹ÜÀíµÈ¡£
	             3¡¢JavaÌá¹©ÁË·á¸»µÄÀà¿â£¬¿ÉÒÔ°ïÖúÎÒÃÇºÜ·½±ãµÄ¿ª·¢Java³ÌĞò¡£
}
ÃæÏò¶ÔÏóµÄ
{
ÃæÏò¶ÔÏó¿ÉÒÔËµÊÇJava×îÖØÒªµÄÌØĞÔ£¬ËùÒÔËüÖ§³Ö¼Ì³Ğ¡¢ÖØÔØ¡¢¶àÌ¬µÈÃæÏò¶ÔÏóµÄÌØĞÔ¡£JavaÓïÑÔµÄÉè¼ÆÊÇÍêÈ«ÃæÏò¶ÔÏóµÄ,Ëü²»Ö§³ÖÀàËÆCÓïÑÔÄÇÑùµÄÃæÏò¹ı³ÌµÄ³ÌĞòÉè¼Æ¼¼Êõ¡£
}
½¡×³µÄ
{
JavaÖÂÁ¦ÓÚ¼ì²é³ÌĞòÔÚ±àÒëºÍÔËĞĞÊ±µÄ´íÎó¡£JavaÒ²ÊÇÒ»ÖÖÇ¿ÀàĞÍµÄÓïÑÔ£¬ÆäÀàĞÍ¼ì²é±ÈC++»¹ÒªÑÏ¸ñ¡£ÀàĞÍ¼ì²é°ïÖúÎÒÃÇ¼ì²é³öĞí¶à¿ª·¢ÔçÆÚ³öÏÖµÄ´íÎó¡£Java×Ô¼º¸ºÔğÄÚ´æ¹ÜÀí£¬Ìá¹©ÁËÀ¬»øÄÚ´æ»ØÊÕ»úÖÆ£¬ÓĞĞ§µÄ±ÜÃâÁËC++ÖĞ×îÍ·ÌÛµÄÄÚ´æĞ¹Â©ÎÊÌâ¡£

}
°²È«µÄ
{
JavaµÄ°²È«ĞÔ¿É´ÓÁ½¸ö·½ÃæµÃµ½±£Ö¤¡£Ò»·½ Ãæ£¬ÔÚJavaÓïÑÔÀï£¬É¾³ıÁËÖ¸ÕëºÍÊÍ·ÅÄÚ´æµÈC++¹¦ÄÜ£¬±ÜÃâÁË·Ç·¨ÄÚ´æ²Ù×÷¡£ÁíÒ»·½Ãæ£¬Í¨¹ıJavaµÄ°²È«ÌåÏµ¼Ü¹¹À´È·±£Java´úÂëµÄ°²È«ĞÔ¡£µ±ÎÒÃÇ´ÓÍøÉÏÏÂÔØJava´úÂëÔÚ±¾µØÖ´ĞĞÊ±£¬JavaµÄ°²È«¼Ü¹¹ÄÜÈ·±£¶ñÒâµÄ´úÂë²»ÄÜËæÒâ·ÃÎÊÎÒÃÇ±¾µØ¼ÆËã»úµÄ×ÊÔ´£¬ÀıÈç£ºÉ¾³ıÎÄ¼ş£¬·ÃÎÊ±¾µØÍøÂç×ÊÔ´µÈ²Ù×÷¶¼ÊÇ±»½ûÖ¹µÄ¡£
}
½âÊÍµÄ
{
Java´úÂëÊÇ½âÊÍÖ´ĞĞµÄ£¬ÎÒÃÇÊ¹ÓÃJava±àÒëÆ÷½«Java´úÂë±àÒë³É×Ö½ÚÂë£¬ÕâÊÇÒ»ÖÖÖĞ¼ä´úÂë£¬È»ºóÓÉJava½âÊÍÆ÷½âÊÍÖ´ĞĞ¡£¶øC++³ÌĞòÊÇ±àÒëÖ´ĞĞµÄ£¬C++³ÌĞò´úÂë±»±àÒëÎª±¾µØ»úÆ÷Ö¸Áî£¬È»ºóÖ´ĞĞ¡£
}
ÓëÆ½Ì¨ÎŞ¹ØµÄ
{
Java×÷ÎªÒ»ÖÖÍøÂçÓïÑÔ£¬ÆäÔ´´úÂë±»±àÒë³ÉÒ»ÖÖ½á¹¹ÖĞÁ¢µÄÖĞ¼äÎÄ¼ş¸ñÊ½¡£Ö»ÒªÓĞJavaÔËĞĞÏµÍ³µÄ»úÆ÷¶¼ÄÜÖ´ĞĞÕâÖÖÖĞ¼ä´úÂë¡£JavaÔ´³ÌĞò±»±àÒë³ÉÒ»ÖÖÓë»úÆ÷ÎŞ¹ØµÄ×Ö½ÚÂë¸ñÊ½£¬ÔÚJavaĞéÄâ»úÉÏÔËĞĞ¡£
}
¶àÏß³ÌµÄ
{
JavaÓïÑÔµÄÒ»¸öÖØÒªÌØĞÔ¾ÍÊÇÔÚÓïÑÔ¼¶Ö§³Ö¶àÏß³ÌµÄ³ÌĞòÉè¼Æ¡£¶àÏß³Ì¾ÍºÃÏñÎÒÃÇ×öÒ»ÕÅ×À×Ó£¬Èç¹ûÄãÒ»¸öÈËÍê³ÉÕâÕÅ×À×Ó¡ª¾ÍºÃÏñµ¥Ïß³Ì£¬ÄÇÃ´ÄãĞèÒªÏÈ×ö×ÀÃæ£¬×öÍê×ÀÃæºó£¬ÔÙ×ö4¸ö×À×ÓÍÈ£¬Èç¹ûÏÖÔÚÓĞ5¸öÈËÀ´×ö×À×Ó¡ªÔÚ³ÌĞòÖĞ¿ª±Ù5¸öÏß³Ì£¬ÆäÖĞ1¸öÈË×ö×ÀÃæ£¬ÁíÍâ4¸öÈË·Ö±ğ×ö4¸ö×À×ÓÍÈ£¬ÄÇÃ´ÕâÁ½ÖÖ·½Ê½Ğ§ÂÊµÄ¸ßµÍ£¬ÏàĞÅ´ó¼Ò¶¼ÄÜÇø·Ö³öÀ´¡£
}
¶¯Ì¬µÄÓïÑÔ
{
JavaµÄ¶¯Ì¬ÌØĞÔÊÇÆäÃæÏò¶ÔÏóÉè¼Æ·½·¨µÄÀ©Õ¹¡£ËüÔÊĞí³ÌĞò¶¯Ì¬µØ×°ÈëÔËĞĞ¹ı³ÌÖĞËùĞèÒªµÄÀà£¬ÕâÊÇÎÒÃÇ²ÉÓÃC++ÓïÑÔ½øĞĞÃæÏò¶ÔÏó³ÌĞòÉè¼ÆËùÎŞ·¨ÊµÏÖµÄ¡£ÔÚC++³ÌĞòÉè¼Æ¹ı³ÌÖĞ£¬Ã¿µ±ÔÚÀàÖĞÔö¼ÓÒ»¸öÊµÀı±äÁ¿»òÒ»¸ö³ÉÔ±º¯Êıºó£¬ ÒıÓÃ¸ÃÀàµÄËùÓĞ×ÓÀà¶¼±ØĞëÖØĞÂ±àÒë£¬·ñÔò½«µ¼ÖÂ³ÌĞò±ÀÀ£¡£Java´ÓÒÔÏÂ¼¸¸ö·½Ãæ²ÉÈ¡´ëÊ©À´½â¾öÕâ¸öÎÊÌâ¡£Java±àÒëÆ÷²»ÊÇ½«¶ÔÊµÀı±äÁ¿ºÍ³ÉÔ±º¯ÊıµÄÒıÓÃ±àÒëÎªÊıÖµÒıÓÃ£¬¶øÊÇ½«·ûºÅÒıÓÃĞÅÏ¢ÔÚ×Ö½ÚÂëÖĞ±£´æÏÂÀ´£¬´«µİ¸ø½âÊÍÆ÷£¬ÔÙÓÉ½âÊÍÆ÷ÔÚÍê³É¶¯Ì¬Á¬½ÓÀàºó£¬½«·ûºÅÒıÓÃĞÅÏ¢×ª»»ÎªÊıÖµÆ«ÒÆÁ¿¡£Ò»¸öÔÚ´æ´¢Æ÷ÖĞÉú³ÉµÄ¶ÔÏó²»ÔÚ±àÒë¹ı³ÌÖĞ¾ö¶¨£¬¶øÊÇÑÓ³Ùµ½ÔËĞĞÊ±ÓÉ½âÊÍÆ÷È·¶¨¡£ÕâÑù£¬¶ÔÀàÖĞµÄ±äÁ¿ºÍ·½·¨½øĞĞ¸üĞÂÊ±¾Í²»ÖÁÓÚÓ°ÏìÏÖ´æµÄ´úÂë¡£ ½âÊÍÖ´ĞĞ×Ö½ÚÂëÊ±£¬ÕâÖÖ·ûºÅĞÅÏ¢µÄ²éÕÒºÍ×ª»»¹ı³Ì½öÔÚÒ»¸öĞÂµÄÃû×Ö³öÏÖÊ±²Å½øĞĞÒ»´Î£¬Ëæºó´úÂë±ã¿ÉÒÔÈ«ËÙÖ´ĞĞ¡£ÔÚÔËĞĞÊ±È·¶¨ÒıÓÃµÄºÃ´¦ÊÇ¿ÉÒÔÊ¹ÓÃÒÑ±»¸üĞÂµÄÀà£¬¶ø²»±Øµ£ĞÄ»áÓ°ÏìÔ­ÓĞµÄ´úÂë¡£Èç¹û³ÌĞòÁ¬½ÓÁËÍøÂçÖĞÁíÒ»ÏµÍ³ÖĞµÄÄ³Ò»Àà£¬¸ÃÀàµÄËùÓĞÕßÒ²¿ÉÒÔ×ÔÓÉµØ¶Ô¸ÃÀà½øĞĞ¸üĞÂ£¬¶ø²»»áÊ¹ÈÎºÎÒıÓÃ¸ÃÀàµÄ³ÌĞò±ÀÀ£¡£Java»¹¼ò»¯ÁËÊ¹ÓÃÒ»¸öÉı¼¶µÄ»òÈ«ĞÂĞ­ÒéµÄ·½·¨¡£Èç¹ûÄãµÄÏµÍ³ÔËĞĞJava³ÌĞòÊ±Óöµ½ÁË²»ÖªÔõÑù´¦ÀíµÄ³ÌĞò£¬JavaÄÜ×Ô¶¯ÏÂÔØÄãËùĞèÒªµÄ¹¦ÄÜ³ÌĞò¡£
}

JavaµÄ¿çÆ½Ì¨ÊÇÍ¨¹ıJavaĞéÄâ»ú£¨JVM£©À´ÊµÏÖµÄ¡£JavaµÄ¿çÆ½Ì¨ÊÇÍ¨¹ıJavaĞéÄâ»ú£¨JVM£©À´ÊµÏÖµÄ¡£

JavaÔ´ÎÄ¼şµÄ±àÒë¹ı³Ì
             JavaÓ¦ÓÃ³ÌĞòµÄ¿ª·¢ÖÜÆÚ°üÀ¨±àÒë¡¢ÏÂÔØ¡¢½âÊÍºÍÖ´ĞĞ¼¸¸ö²¿·Ö¡£Java±àÒë³ÌĞò½«JavaÔ´³ÌĞò·­ÒëÎªJVM¿ÉÖ´ĞĞ´úÂë¡ª×Ö½ÚÂë¡£ÕâÒ»±àÒë¹ı³ÌÍ¬C/C++µÄ±àÒëÓĞĞ©²»Í¬¡£µ±C±àÒëÆ÷±àÒëÉú³ÉÒ»¸ö¶ÔÏóµÄ´úÂëÊ±£¬¸Ã´úÂëÊÇÎªÔÚÄ³Ò»ÌØ¶¨Ó²¼şÆ½Ì¨ÔËĞĞ¶ø²úÉúµÄ¡£Òò´Ë£¬ÔÚ±àÒë¹ı³ÌÖĞ£¬±àÒë³ÌĞòÍ¨¹ı²é±í½«ËùÓĞ¶Ô·ûºÅµÄÒıÓÃ×ª»»ÎªÌØ¶¨µÄÄÚ´æÆ«ÒÆÁ¿£¬ÒÔ±£Ö¤³ÌĞòÔËĞĞ¡£Java±àÒëÆ÷È´²»½«¶Ô±äÁ¿ºÍ·½·¨µÄÒıÓÃ±àÒëÎªÊıÖµÒıÓÃ£¬Ò²²»È·¶¨³ÌĞòÖ´ĞĞ¹ı³ÌÖĞµÄÄÚ´æ²¼¾Ö£¬¶øÊÇ½«ÕâĞ©·ûºÅÒıÓÃĞÅÏ¢±£ÁôÔÚ×Ö½ÚÂëÖĞ£¬ÓÉ½âÊÍÆ÷ÔÚÔËĞĞ¹ı³ÌÖĞ´´½¨ÄÚ´æ²¼¾Ö£¬È»ºóÔÙÍ¨¹ı²é±íÀ´È·¶¨Ò»¸ö·½·¨ËùÔÚµÄµØÖ·¡£ÕâÑù¾ÍÓĞĞ§µÄ±£Ö¤ÁËJavaµÄ¿ÉÒÆÖ²ĞÔºÍ°²È«ĞÔ¡£

Java½âÊÍÆ÷µÄÖ´ĞĞ¹ı³Ì
              ÔËĞĞJVM×Ö½ÚÂëµÄ¹¤×÷ÊÇÓÉ½âÊÍÆ÷À´Íê³ÉµÄ¡£½âÊÍÖ´ĞĞ¹ı³Ì·ÖÈı²½½øĞĞ£º´úÂëµÄ×°Èë¡¢´úÂëµÄĞ£ÑéºÍ´úÂëµÄÖ´ĞĞ¡£×°Èë´úÂëµÄ¹¤×÷ÓÉ¡°Àà×°ÔØÆ÷¡±£¨class loader£©Íê³É¡£Àà×°ÔØÆ÷¸ºÔğ×°ÈëÔËĞĞÒ»¸ö³ÌĞòĞèÒªµÄËùÓĞ´úÂë£¬ÕâÒ²°üÀ¨³ÌĞò´úÂëÖĞµÄÀàËù¼Ì³ĞµÄÀàºÍ±»Æäµ÷ÓÃµÄÀà¡£µ±Àà×°ÔØÆ÷×°ÈëÒ»¸öÀàÊ±£¬¸ÃÀà±»·ÅÔÚ×Ô¼ºµÄÃû×Ö¿Õ¼äÖĞ¡£³ıÁËÍ¨¹ı·ûºÅÒıÓÃ×Ô¼ºÃû×Ö¿Õ¼äÒÔÍâµÄÀà£¬ÀàÖ®¼äÃ»ÓĞÆäËû°ì·¨¿ÉÒÔÓ°ÏìÆäËüÀà¡£ÔÚ±¾Ì¨¼ÆËã»úÉÏµÄËùÓĞÀà¶¼ÔÚÍ¬Ò»µØÖ·¿Õ¼äÄÚ£¬¶øËùÓĞ´ÓÍâ²¿Òı½øµÄÀà£¬¶¼ÓĞÒ»¸ö×Ô¼º¶ÀÁ¢µÄÃû×Ö¿Õ¼ä¡£ÕâÊ¹µÃ±¾µØÀàÍ¨¹ı¹²ÏíÏàÍ¬µÄÃû×Ö¿Õ¼ä»ñµÃ½Ï¸ßµÄÔËĞĞĞ§ÂÊ£¬Í¬Ê±ÓÖ±£Ö¤ËüÃÇÓë´ÓÍâ²¿Òı½øµÄÀà²»»áÏà»¥Ó°Ïì¡£µ±×°ÈëÁËÔËĞĞ³ÌĞòĞèÒªµÄËùÓĞÀàºó£¬½âÊÍÆ÷±ã¿ÉÈ·¶¨Õû¸ö¿ÉÖ´ĞĞ³ÌĞòµÄÄÚ´æ²¼¾Ö¡£½âÊÍÆ÷Îª·ûºÅÒıÓÃÍ¬ÌØ¶¨µÄµØÖ·¿Õ¼ä½¨Á¢¶ÔÓ¦¹ØÏµ¼°²éÑ¯±í¡£Í¨¹ıÔÚÕâÒ»½×¶ÎÈ·¶¨´úÂëµÄÄÚ´æ²¼¾Ö£¬JavaºÜºÃµØ½â¾öÁËÓÉ³¬Àà¸Ä±ä¶øÊ¹×ÓÀà±ÀÀ£µÄÎÊÌâ£¬Í¬Ê±Ò²·ÀÖ¹ÁË´úÂë¶ÔµØÖ·µÄ·Ç·¨·ÃÎÊ¡£
              Ëæºó£¬±»×°ÈëµÄ´úÂëÓÉ×Ö½ÚÂëĞ£ÑéÆ÷½øĞĞ¼ì²é¡£Ğ£ÑéÆ÷¿É·¢ÏÖ²Ù×÷ÊıÕ»Òç³ö£¬·Ç·¨Êı¾İÀàĞÍ×ª»»µÈ¶àÖÖ´íÎó¡£Í¨¹ıĞ£Ñéºó£¬´úÂë±ã¿ªÊ¼Ö´ĞĞÁË¡£


Java×Ö½ÚÂëµÄÁ½ÖÖÖ´ĞĞ·½Ê½
            1¡¢¼´Ê±±àÒë·½Ê½£º½âÊÍÆ÷ÏÈ½«×Ö½ÚÂë±àÒë³É»úÆ÷Âë£¬È»ºóÔÙÖ´ĞĞ¸Ã»úÆ÷Âë¡£         2¡¢½âÊÍÖ´ĞĞ·½Ê½£º½âÊÍÆ÷Í¨¹ıÃ¿´Î½âÊÍ²¢Ö´ĞĞÒ»Ğ¡¶Î´úÂëÀ´Íê³ÉJava×Ö½ÚÂë³Ì ĞòµÄËùÓĞ²Ù×÷¡£ ¡¡¡¡Í¨³£²ÉÓÃµÄÊÇµÚ¶şÖÖ·½·¨¡£ÓÉÓÚJVM¹æ¸ñÃèÊö¾ßÓĞ×ã¹»µÄÁé»îĞÔ£¬ÕâÊ¹µÃ½«×Ö½ÚÂë·­ÒëÎª»úÆ÷´úÂëµÄ¹¤×÷¾ßÓĞ½Ï¸ßµÄĞ§ÂÊ¡£¶ÔÓÚÄÇĞ©¶ÔÔËĞĞËÙ¶ÈÒªÇó½Ï¸ßµÄÓ¦ÓÃ³ÌĞò£¬½âÊÍÆ÷¿É½«Java×Ö½ÚÂë¼´Ê±±àÒëÎª»úÆ÷Âë£¬´Ó¶øºÜºÃµØ±£Ö¤ÁËJava´úÂëµÄ¿ÉÒÆÖ²ĞÔºÍ¸ßĞÔÄÜ¡£


JVM¹æ¸ñÃèÊö
             JVMµÄÉè¼ÆÄ¿±êÊÇÌá¹©Ò»¸ö»ùÓÚ³éÏó¹æ¸ñÃèÊöµÄ¼ÆËã»úÄ£ĞÍ£¬Îª½âÊÍ³ÌĞò¿ª·¢ÈËÔ±Ìá¹©ºÜºÃµÄÁé»îĞÔ£¬Í¬Ê±Ò²È·±£Java´úÂë¿ÉÔÚ·ûºÏ¸Ã¹æ·¶µÄÈÎºÎÏµÍ³ÉÏÔËĞĞ¡£JVM¶ÔÆäÊµÏÖµÄÄ³Ğ©·½Ãæ¸ø³öÁË¾ßÌåµÄ¶¨Òå£¬ÌØ±ğÊÇ¶ÔJava¿ÉÖ´ĞĞ´úÂë£¬¼´×Ö½ÚÂë(Bytecode)µÄ¸ñÊ½¸ø³öÁËÃ÷È·µÄ¹æ¸ñ¡£ÕâÒ»¹æ¸ñ°üÀ¨²Ù×÷ÂëºÍ²Ù×÷ÊıµÄÓï·¨ºÍÊıÖµ¡¢±êÊ¶·ûµÄÊıÖµ±íÊ¾·½Ê½¡¢ÒÔ¼°JavaÀàÎÄ¼şÖĞµÄJava¶ÔÏó¡¢³£Á¿»º³å³ØÔÚJVMµÄ´æ´¢Ó³Ïó¡£ÕâĞ©¶¨ÒåÎªJVM½âÊÍÆ÷¿ª·¢ÈËÔ±Ìá¹©ÁËËùĞèµÄĞÅÏ¢ºÍ¿ª·¢»·¾³¡£JavaµÄÉè¼ÆÕßÏ£Íû¸ø¿ª·¢ÈËÔ±ÒÔËæĞÄËùÓûÊ¹ÓÃJavaµÄ×ÔÓÉ¡£
            JVMÊÇÎªJava×Ö½ÚÂë¶¨ÒåµÄÒ»ÖÖ¶ÀÁ¢ÓÚ¾ßÌåÆ½Ì¨µÄ¹æ¸ñÃèÊö£¬ÊÇJavaÆ½Ì¨¶ÀÁ¢ĞÔµÄ»ù´¡¡£



Java³ÌĞòÖ´ĞĞÓëC/C++³ÌĞòÖ´ĞĞµÄ¶Ô±È·ÖÎö
             Èç¹û°ÑJavaÔ´³ÌĞòÏëÏó³ÉÎÒÃÇµÄC++Ô´³ÌĞò£¬JavaÔ´³ÌĞò±àÒëºóÉú³ÉµÄ×Ö½ÚÂë¾ÍÏàµ±ÓÚC++Ô´³ÌĞò±àÒëºóµÄ80x86µÄ»úÆ÷Âë£¨¶ş½øÖÆ³ÌĞòÎÄ¼ş£©£¬JVMĞéÄâ»úÏàµ±ÓÚ80x86¼ÆËã»úÏµÍ³£¬Java½âÊÍÆ÷Ïàµ±ÓÚ80x86CPU¡£ÔÚ80x86CPUÉÏÔËĞĞµÄÊÇ»úÆ÷Âë£¬ÔÚJava½âÊÍÆ÷ÉÏÔËĞĞµÄÊÇJava×Ö½ÚÂë¡£
             Java½âÊÍÆ÷Ïàµ±ÓÚÔËĞĞJava×Ö½ÚÂëµÄ¡°CPU¡±£¬µ«¸Ã¡°CPU¡±²»ÊÇÍ¨¹ıÓ²¼şÊµÏÖµÄ£¬¶øÊÇÓÃÈí¼şÊµÏÖµÄ¡£Java½âÊÍÆ÷Êµ¼ÊÉÏ¾ÍÊÇÌØ¶¨µÄÆ½Ì¨ÏÂµÄÒ»¸öÓ¦ÓÃ³ÌĞò¡£Ö»ÒªÊµÏÖÁËÌØ¶¨Æ½Ì¨ÏÂµÄ½âÊÍÆ÷³ÌĞò£¬Java×Ö½ÚÂë¾ÍÄÜÍ¨¹ı½âÊÍÆ÷³ÌĞòÔÚ¸ÃÆ½Ì¨ÏÂÔËĞĞ£¬ÕâÊÇJava¿çÆ½Ì¨µÄ¸ù±¾¡£µ±Ç°£¬²¢²»ÊÇÔÚËùÓĞµÄÆ½Ì¨ÏÂ¶¼ÓĞÏàÓ¦Java½âÊÍÆ÷³ÌĞò£¬ÕâÒ²ÊÇJava²¢²»ÄÜÔÚËùÓĞµÄÆ½Ì¨ÏÂ¶¼ÄÜÔËĞĞµÄÔ­Òò£¬ËüÖ»ÄÜÔÚÒÑÊµÏÖÁËJava½âÊÍÆ÷³ÌĞòµÄÆ½Ì¨ÏÂÔËĞĞ¡£




javac¾ÍÊÇJava±àÒëÆ÷
java¾ÍÊÇJava½âÊÍÆ÷



D:\workspace\Java>cd lesson1

D:\workspace\Java\lesson1>dir
 Çı¶¯Æ÷ D ÖĞµÄ¾íÊÇ LOCAL
 ¾íµÄĞòÁĞºÅÊÇ CB30-2D7F

 D:\workspace\Java\lesson1 µÄÄ¿Â¼

2006-12-17  19:49    <DIR>          .
2006-12-17  19:49    <DIR>          ..
2006-12-17  19:50                 7 hello.java.bak
2006-12-17  19:53                20 hello.java
               2 ¸öÎÄ¼ş             27 ×Ö½Ú
               2 ¸öÄ¿Â¼  1,304,494,080 ¿ÉÓÃ×Ö½Ú

D:\workspace\Java\lesson1>javac hello.java

D:\workspace\Java\lesson1>dir
 Çı¶¯Æ÷ D ÖĞµÄ¾íÊÇ LOCAL
 ¾íµÄĞòÁĞºÅÊÇ CB30-2D7F

 D:\workspace\Java\lesson1 µÄÄ¿Â¼

2006-12-17  19:49    <DIR>          .
2006-12-17  19:49    <DIR>          ..
2006-12-17  19:50                 7 hello.java.bak
2006-12-17  19:53                20 hello.java
2006-12-17  19:54               184 hello.class
               3 ¸öÎÄ¼ş            211 ×Ö½Ú
               2 ¸öÄ¿Â¼  1,304,477,696 ¿ÉÓÃ×Ö½Ú

D:\workspace\Java\lesson1>java hello.class
Exception in thread "main" java.lang.NoClassDefFoundError: hello/class

D:\workspace\Java\lesson1>

ÅäÖÃ»·¾³±äÁ¿:
ÒÀ´Î"ÎÒµÄµçÄÔ->ÊôĞÔ->¸ß¼¶->»·¾³±äÁ¿(N)->±äÁ¿"ÔÚÕâÀïÓĞ¸öpath±äÁ¿,
Ëü¾ÍÊÇ¿ÉÖ´ĞĞ³ÌĞòµÄ»·¾³Â·¾¶,
¿ÉÒÔÔÚÃüÁîÌáÊ¾·ûÏÂÊäÈë:path²é¿´ÏµÍ³µÄpath»·¾³±äÁ¿
D:\workspace\Java\lesson1>path
PATH=M:\WINDOWS\system32;M:\WINDOWS;M:\WINDOWS\System32\Wbem;M:\Program Files\Mi
crosoft Visual Studio\Common\Tools\WinNT;M:\Program Files\Microsoft Visual Studi
o\Common\MSDev98\Bin;M:\Program Files\Microsoft Visual Studio\Common\Tools;c:\Pr
ogram Files\Visual Studio\VC98\bin;C:\Program Files\Java\jdk1.5.0_08\bin


ÔÚÍ¬Ò»¸öÎÄ¼şÖĞ¿ÉÒÔ±àĞ´¶à¸öÀà,
ÔÚ±àÒëµÄÊ±ºò,ÎªÃ¿¸öÀàµ¥¶ÀÉú³ÉÒ»¸ö*.classµÄÀàÎÄ¼ş,
ÕâÔÚ¿ª·¢´óĞÍ³ÌĞòÊ±,»á²úÉúºÜ¶àÀàÎÄ¼ş,ÕâÑù¾Í²»Ì«·½±ãÁË.
Îª´Ë,sun¹«Ë¾Ìá¹© jar.exe ´ò°ü¹¤¾ß,Ëü¿ÉÒÔ½«ºÜ¶àÀàÎÄ¼ş´ò°ü³ÉÒ»¸öjar°ü,
ÕâÖÖjar°ü¿ÉÒÔÍ¨¹ıwinrar¹¤¾ß´ò¿ª,

D:\workspace\Java\lesson1>jar
ÓÃ·¨£ºjar {ctxu}[vfm0Mi] [jar-ÎÄ¼ş] [manifest-ÎÄ¼ş] [-C Ä¿Â¼] ÎÄ¼şÃû ...
Ñ¡Ïî£º
    -c  ´´½¨ĞÂµÄ´æµµ
    -t  ÁĞ³ö´æµµÄÚÈİµÄÁĞ±í
    -x  Õ¹¿ª´æµµÖĞµÄÃüÃûµÄ£¨»òËùÓĞµÄ¡³ÎÄ¼ş
    -u  ¸üĞÂÒÑ´æÔÚµÄ´æµµ
    -v  Éú³ÉÏêÏ¸Êä³öµ½±ê×¼Êä³öÉÏ
    -f  Ö¸¶¨´æµµÎÄ¼şÃû
    -m  °üº¬À´×Ô±êÃ÷ÎÄ¼şµÄ±êÃ÷ĞÅÏ¢
    -0  Ö»´æ´¢·½Ê½£»Î´ÓÃZIPÑ¹Ëõ¸ñÊ½
    -M  ²»²úÉúËùÓĞÏîµÄÇåµ¥£¨manifest¡³ÎÄ¼ş
    -i  ÎªÖ¸¶¨µÄjarÎÄ¼ş²úÉúË÷ÒıĞÅÏ¢
    -C  ¸Ä±äµ½Ö¸¶¨µÄÄ¿Â¼£¬²¢ÇÒ°üº¬ÏÂÁĞÎÄ¼ş£º
Èç¹ûÒ»¸öÎÄ¼şÃûÊÇÒ»¸öÄ¿Â¼£¬Ëü½«±»µİ¹é´¦Àí¡£
Çåµ¥£¨manifest¡³ÎÄ¼şÃûºÍ´æµµÎÄ¼şÃû¶¼ĞèÒª±»Ö¸¶¨£¬°´'m' ºÍ 'f'±êÖ¾Ö¸¶¨µÄÏàÍ¬Ë³Ğò¡£

Ê¾Àı1£º½«Á½¸öclassÎÄ¼ş´æµµµ½Ò»¸öÃûÎª 'classes.jar' µÄ´æµµÎÄ¼şÖĞ£º
       jar cvf classes.jar Foo.class Bar.class
Ê¾Àı2£ºÓÃÒ»¸ö´æÔÚµÄÇåµ¥£¨manifest£©ÎÄ¼ş 'mymanifest' ½« foo/ Ä¿Â¼ÏÂµÄËùÓĞ
           ÎÄ¼ş´æµµµ½Ò»¸öÃûÎª 'classes.jar' µÄ´æµµÎÄ¼şÖĞ£º
       jar cvfm classes.jar mymanifest -C foo/ .


D:\workspace\Java\lesson1>jar cvf Lesson1.jar hello.class Welcome.class
±êÃ÷Çåµ¥(manifest)
Ôö¼Ó£ºhello.class(¶ÁÈë= 184) (Ğ´³ö= 155)(Ñ¹ËõÁË 15%)
Ôö¼Ó£ºWelcome.class(¶ÁÈë= 186) (Ğ´³ö= 157)(Ñ¹ËõÁË 15%)

D:\workspace\Java\lesson1>dir
 Çı¶¯Æ÷ D ÖĞµÄ¾íÊÇ LOCAL
 ¾íµÄĞòÁĞºÅÊÇ CB30-2D7F

 D:\workspace\Java\lesson1 µÄÄ¿Â¼

2006-12-17  19:49    <DIR>          .
2006-12-17  19:49    <DIR>          ..
2006-12-17  20:04               184 hello.class
2006-12-17  20:03                20 hello.java.bak
2006-12-17  20:04                46 hello.java
2006-12-17  20:04               186 Welcome.class
2006-12-17  20:10               889 Lesson1.jar
               5 ¸öÎÄ¼ş          1,325 ×Ö½Ú
               2 ¸öÄ¿Â¼  1,304,428,544 ¿ÉÓÃ×Ö½Ú

D:\workspace\Java\lesson1>cd .

D:\workspace\Java\lesson1>cd ..

D:\workspace\Java>jar cvf Lesson1.jar lesson1
±êÃ÷Çåµ¥(manifest)
Ôö¼Ó£ºlesson1/(¶ÁÈë= 0) (Ğ´³ö= 0)(´æ´¢ÁË 0%)
Ôö¼Ó£ºlesson1/hello.class(¶ÁÈë= 184) (Ğ´³ö= 155)(Ñ¹ËõÁË 15%)
Ôö¼Ó£ºlesson1/hello.java.bak(¶ÁÈë= 20) (Ğ´³ö= 22)(Ñ¹ËõÁË -10%)
Ôö¼Ó£ºlesson1/hello.java(¶ÁÈë= 46) (Ğ´³ö= 37)(Ñ¹ËõÁË 19%)
Ôö¼Ó£ºlesson1/Welcome.class(¶ÁÈë= 186) (Ğ´³ö= 157)(Ñ¹ËõÁË 15%)
Ôö¼Ó£ºlesson1/Lesson1.jar(¶ÁÈë= 889) (Ğ´³ö= 475)(Ñ¹ËõÁË 46%)


{
	hello.java:

	class Hello
	{

	}

	public class Welcome
	{

	}


	D:\workspace\Java\lesson1>javac hello.java
	hello.java:6: Àà Welcome ÊÇ¹«¹²µÄ£¬Ó¦ÔÚÃûÎª Welcome.java µÄÎÄ¼şÖĞÉùÃ÷
	public class Welcome
	       ^
	1 ´íÎó

	ÕâÀï¿ÉÒÔ¿´µ½,°üº¬ÓĞÉùÃ÷ÎªpublicµÄÀàµÄÎÄ¼ş,ÎÄ¼şÃû³ÆÒª±»ÃüÃûÎª¸ÃÀàµÄÀàÃû.
	Ã¿¸öÎÄ¼şÀïÖ»ÄÜÓĞÒ»¸öÉùÃ÷ÎªpublicµÄÀà,
	ºÃµÄÏÖÔÚ½«ÎÄ¼şÃû¸ÃÎª Welcome.javaÎÄ¼şÄÚÈİĞŞ¸ÄÈçÏÂ:
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

		±àÒëºóÔËĞĞÊ±¾ÍÌáÊ¾Ã»ÓĞmian·½·¨,Õâ¾ÍºÃÏñC/C++ÖĞÒ»Ñù,±ØĞëÒªÓĞmainº¯Êı.

		ÏÖÔÚĞŞ¸ÄÔ´ÎÄ¼şÈçÏÂ£º

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

	¿ÉÒÔ¿´µ½ÔËĞĞ½á¹û¡£
	ÕâÀï»¹¿ÉÒÔ¿´µ½£¬ÔËĞĞÊ±²»ÊÇ java Welcome.class£¬¶øÊÇjava Welcome
}


Java»ù±¾Êı¾İÀàĞÍ
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
			javaÌá¹©ÁË8ÖÖÊı¾İÀàĞÍ
			byte 	b;
			int  	i;
			long	l;
			char   	ch;
			float 	f;
			double  d;
			boolean bool;
			*/
			byte b;//ÕâÀïbÊÇÒ»¸ö8Î»µÄÊı£¬¿ÉÒÔ±íÊ¾£º-128~127Ö®¼äµÄÈÎºÎÊı¡£
			b = 5;
			b = b*3 ;
			println( b );//ÕâÀïµÄprintln¿ÉÒÔ×Ô¶¯Ê¶±ğÊä³ö±äÁ¿µÄ¸ñÊ½¡£
		}
	}

	D:\workspace\Java\lesson1>javac Welcome.java
	Welcome.java:21: ¿ÉÄÜËğÊ§¾«¶È
	ÕÒµ½£º int
	ĞèÒª£º byte
	                b = b*3 ;
	                     ^
	Welcome.java:22: ÕÒ²»µ½·ûºÅ
	·ûºÅ£º ·½·¨ println(byte)
	Î»ÖÃ£º Àà Welcome
	                println( b );//ÕâÀïµÄprintln¿ÉÒÔ×Ô¶¯Ê¶±ğÊä³ö±äÁ¿µÄ¸ñÊ½¡£
	                ^
	2 ´íÎó

	ÕâÀïÊÇÒòÎª£¬byteÀàĞÍÔÚ²ÎÈëÔËËãÊ±£¬ÎªÁË±£Ö¤¾«¶È×ª»»ÎªintÀàĞÍ£¬
	Õâ¸ö´íÎóÔÚC/C++ÖĞÍùÍùÊÇÒ»¸ö¾¯¸æ£¬¶øÕâÀï¾ÍÊÇ´íÎó£¬ÕâÊÇjavaµÄ°²È«»úÖÆÒ»¸öÌåÏÖ

	ÏÂÃæĞŞ¸ÄÒ»ÏÂÔ´ÎÄ¼ş£º
	½«
	b = b*3 ;
	¸ÄÎª£º
	b = (byte)b*3 ;
	ÔÙÈ¥±àÒëÏÂ,¿ÉÒÔ·¢ÏÖ,³öÏÖÍ¬ÑùµÄ´íÎó.

	public class Welcome
	{
		public static void main( String[] args )
		{
			/*
			System.out.print("Hello world!\n");
			System.out.println("http://blog.csdn.net/zieckey");
			*/
			/*
			javaÌá¹©ÁË8ÖÖÊı¾İÀàĞÍ
			byte 	b;//ÕâÀïbÊÇÒ»¸ö8Î»µÄÊı£¬¿ÉÒÔ±íÊ¾£º-128~127Ö®¼äµÄÈÎºÎÊı¡£
			short 	s;//2×Ö½ÚµÄÓĞ·ûºÅµÄÕûÊı.¿ÉÒÔ±íÊ¾£º-32768~32767Ö®¼äµÄÈÎºÎÊı¡£
			int  	i;//4×Ö½ÚµÄÓĞ·ûºÅµÄÕûÊı
			long	l;//8×Ö½ÚµÄÓĞ·ûºÅµÄÕûÊı
			char   	c;//2¸ö×Ö½ÚµÄÎŞ·ûºÅÕûÊı,¿ÉÒÔ±íÊ¾£º0~65535Ö®¼äµÄÈÎºÎÊı¡£
			float 	f;//4×Ö½ÚµÄ
			double  d;//8×Ö½ÚµÄ
			boolean bool;//Ö»ÄÜÓÃ true ºÍ false
			*/
			byte b;//ÕâÀïbÊÇÒ»¸ö8Î»µÄÊı£¬¿ÉÒÔ±íÊ¾£º-128~127Ö®¼äµÄÈÎºÎÊı¡£
			b = 5;
			b = (byte)( b * 3 ) ;
			System.out.println( b ); //ÕâÀïµÄprintln¿ÉÒÔ×Ô¶¯Ê¶±ğÊä³ö±äÁ¿µÄ¸ñÊ½¡£
		}
	}

	±àÒëÔËĞĞ:
	D:\workspace\Java\lesson1>javac Welcome.java

	D:\workspace\Java\lesson1>java Welcome
	15

	D:\workspace\Java\lesson1>

	¸øfloat±äÁ¿ÕâÑù¸³ÖµÊ±:
	float f = 1.3;
	±àÒë»á±¨´í:

	D:\workspace\Java\lesson1>javac Welcome.java
	Welcome.java:38: ¿ÉÄÜËğÊ§¾«¶È
	ÕÒµ½£º double
	ĞèÒª£º float
	                float f = 1.3;
	                          ^
	1 ´íÎó

	ÔÚJavaÖĞĞ¡ÊıµÄ³£Á¿±»ÈÏÎªÊÇÒ»¸ödoubleÀàĞÍ,
	ËùÒÔÓ¦¸ÃÕâÑù¸øfloat±äÁ¿¸³Öµ.
	float f = 1.3f;

	¸øboolean±äÁ¿¸³ÖµÊ±Ö»ÄÜÈ¡Á½¸öÖµ:
	 bool = true;»òÕß bool = false;

	D:\workspace\Java\lesson1>javac Welcome.java
	D:\workspace\Java\lesson1>java Welcome
	true

	ÔÚ×öÌõ¼şÅĞ¶ÏµÄÊ±ºò,Ò²Ö»ÄÜÓÃ true ºÍ false
	if ( 1 )
	{
	}
	ÕâÑùµÄĞ´·¨»á³ö´íµÄ.

	D:\workspace\Java\lesson1>javac Welcome.java
	Welcome.java:45: ²»¼æÈİµÄÀàĞÍ
	ÕÒµ½£º int
	ĞèÒª£º boolean
	                if ( 1 )
	                     ^
	1 ´íÎó
}

JavaÊı×é :
{
	Èç¹ûÏëÔÚC/C++ÖĞÄÇÑù¶¨ÒåµÄ: int num[5];
	int num[5];//ÕâÀï²»ÄÜÔ¤ÏÈĞ´³öÊı×éµÄ¿Õ¼ä´óĞ¡¡£

	int num[];	//OK
	num = new int[5];  //ÏÈ¶¨Òå£¬ºó·ÖÅä¿Õ¼ä¡£

	//ÔÚJavaÖĞÍÆ¼öÊ¹ÓÃ int[] num;	ÕâÖÖ·½Ê½¶¨ÒåÊı×é£¬ÕâÑù¾ÍÖ±°×Ã÷ÁË£¬
	//ÊÇ¶¨ÒåÁËÒ»¸öintÀàĞÍµÄÊı×é num £¬
	//Èç¹ûint num[];ÄÇÃ´µ½µ×numÊÇ±äÁ¿ÄØ»¹num[]ÊÇ±äÁ¿£¿
	int[] num;	//int [] num;	int []num;	//[]µÄÎ»ÖÃÃ»ÓĞ¹ØÏµ
	num = new int[5];  //ÏÈ¶¨Òå£¬ºó·ÖÅä¿Õ¼ä¡£

	//¿ÉÒÔÔÚ¶¨ÒåµÄÊ±ºò³õÊ¼»¯
	int []num={1,2,3};//OK

	//»òÕß
	int []num2 = new int[]{1,2,3};//OK
	µ«ÊÇ²»ÄÜÖ¸¶¨¿Õ¼ä´óĞ¡
	//int []num3 = new int[3]{1,2,3};//ERROR

	¶ÔÊı×éµÄ¸³Öµ:
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


	¶şÎ¬Êı×é:
	/* OK
	int [][] a;
	a = new int [3][4];//3ĞĞ4ÁĞ
	a[0][1] = 12;
	a[2][3] = 14;
	*/

	¶ÔÓÚ¶şÎ¬Êı×é,JavaÖĞÃ¿ĞĞµÄÁĞÊı¿ÉÒÔ²»ÏàµÈ,Õâ¾ÍºÍC/C++ÖĞµÄÖ¸ÕëÊı×é½ÏÎªÏàÏñ
	Õâ¶ÔÓÚ´æ´¢×Ö·û´®±È½Ï·½±ã¡£

	¶şÎ¬Êı×é³õÊ¼»¯
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

	++ ºÍ -- ²Ù×÷·ûÍ¬C/C++ÖĞÊÇÒ»ÑùµÄ¡£
	{
		/*
		int i =3 ;
		int count;
		count = (i++) + (i++) + (i++);
		System.out.println( i );  //Êä³ö6
		*/
		/*
		int i =3 ;
		int count;
		count = (++i) + (++i) + (++i);
		System.out.println( i );  //Êä³ö6
		System.out.println( count );//Êä³ö15
		*/
	}

	¹ı³ÌÓï¾ä
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
Î»²Ù×÷
{
	class Test
	{
		public static void main(String args[])
		{
			int i = 0xffffffff;
			int c = i<<2; //´ø·ûºÅ×óÒÆ
			System.out.println(i);
			System.out.println(Integer.toHexString(c));//½«c´ú±íµÄÊıÒÔ16½øÖÆĞÎÊ½Êä³öfffffffc

			c = i>>2;//´ø·ûºÅÓÒÒÆ
			System.out.println(Integer.toHexString(c));//½«c´ú±íµÄÊıÒÔ16½øÖÆĞÎÊ½Êä³öffffffff
			c = i>>>2;//²»´ø·ûºÅÓÒÒÆ
			System.out.println(Integer.toHexString(c));//½«c´ú±íµÄÊıÒÔ16½øÖÆĞÎÊ½Êä³ö3fffffff

		}
	}
}

ÃæÏò¶ÔÏó±à³Ì·½·¨£º
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

	Õâ¸ö³ÌĞòÔÚ±àÒëÊ±³öÏÖ´íÎó£º
	E:\study\JAVA\Java-Study\JavaLesson\Lesson2\temp>javac Point.java
	Point.java:13: ÎŞ·¨´Ó¾²Ì¬ÉÏÏÂÎÄÖĞÒıÓÃ·Ç¾²Ì¬ ±äÁ¿ x
	                Point.x = 20;
	                     ^
	Point.java:14: ÎŞ·¨´Ó¾²Ì¬ÉÏÏÂÎÄÖĞÒıÓÃ·Ç¾²Ì¬ ±äÁ¿ y
	                Point.y = 20;
	                     ^
	2 ´íÎó
	ĞŞ¸Ä³ÌĞò£º

	//Point.java
	class Point
	{
		static int x,y; //×¢ÒâÕâÀïµÄ¸Ä±ä
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
	ÕâÑù¾Í²»»á³ö´í

}





2006/12/20
Lesson3

ÎªÁË±ãÓÚ¹ÜÀí´óĞÍÈí¼şÏµÍ³ÖĞÊıÄ¿ÖÚ¶àµÄÀà£¬½â¾öÀàÃüÃû³åÍ»µÄÎÊÌâ£¬JavaÒıÈëÁË°ü£¨package£©¡£

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
ÕâÑùÖ±½ÓÔËĞĞ»á³ö´í£¬ÎÒÃÇ±ØĞë´øÉÏ°üÃû£º

E:\study\JAVA\Java-Study\JavaLesson\Lesson3>java zieckey.Test
Exception in thread "main" java.lang.NoClassDefFoundError: zieckey/Test

ÕâÑù»¹ÊÇ»á³ö´í£¬Êµ¼ÊÉÏ£¬°ü¾ÍÏñÎÒÃÇµÄÎÄ¼şÏµÍ³Ò»Ñù£¬ÎÒÃÇÏÖÔÚÔÚµ±Ç°Ä¿Â¼ÏÂ£¬
ĞÂ½¨Ò»¸öÒÔ°üÃû¡°zieckey¡±ÃüÃûµÄÎÄ¼ş¼Ğ£¬È»ºó½«Test.class·Åµ½¸Ã¡°zieckey¡±ÃüÃûµÄÎÄ¼ş¼ĞÖĞ¡£

E:\study\JAVA\Java-Study\JavaLesson\Lesson3>mkdir zieckey

E:\study\JAVA\Java-Study\JavaLesson\Lesson3>copy Test.class zieckey
ÒÑ¸´ÖÆ         1 ¸öÎÄ¼ş¡£

E:\study\JAVA\Java-Study\JavaLesson\Lesson3>java zieckey.Test
zieckey test!

»òÕß
E:\study\JAVA\Java-Study\JavaLesson\Lesson3>java zieckey/Test
zieckey test!

ºÃÁË£¬ÏÖÔÚ¾Í³É¹¦ÁË¡£

ÎÒÃÇ»¹¿ÉÒÔ¸ø°üÃû¼ÓÉÏÏŞ¶¨Ãû£º
package cn.zieckey;
class Test
{
	public static void main( String[] args )
	{
		System.out.println( "zieckey test!");
	}
}
±àÒëÔËĞĞ£º

E:\study\JAVA\Java-Study\JavaLesson\Lesson3>javac Test.java

E:\study\JAVA\Java-Study\JavaLesson\Lesson3>copy Test.class zieckey
¸ÄĞ´ zieckey\Test.class Âğ? (Yes/No/All): y
ÒÑ¸´ÖÆ         1 ¸öÎÄ¼ş¡£

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

ÎÒÃÇ·¢ÏÖÓĞ³öÏÖÁËÎÊÌâ£¬ÆäÊµÒ»ÑùµÄ£¬ÎÒÃÇÖ»ĞèÒªÔÙ½« zieckey ÎÄ¼ş¼Ğ·Åµ½ cn ÎÄ¼ş¼ĞÏÂ£º
E:\study\JAVA\Java-Study\JavaLesson\Lesson3>java cn.zieckey.Test
zieckey test!

packageÓï¾ä±ØĞëÊÇÎÄ¼şÖĞµÄµÚÒ»ÌõÓï¾ä¡£
Ò²¾ÍÊÇËµ£¬ÔÚpackageÓï¾äÖ®Ç°£¬³ıÁË¿Õ°×ºÍ×¢ÊÍÖ®Íâ²»ÄÜÓĞÈÎºÎÓï¾ä¡£
Èç¹û²»¼ÓpackageÓï¾ä£¬ÔòÖ¸¶¨ÎªÈ±Ê¡°ü»òÎŞÃû°ü¡£
°ü¶ÔÓ¦×ÅÎÄ¼şÏµÍ³µÄÄ¿Â¼²ã´Î½á¹¹¡£
ÔÚpackageÓï¾äÖĞ£¬ÓÃ¡°.¡±À´Ö¸Ã÷°ü£¨Ä¿Â¼£©µÄ²ã´Î¡£

ÎÒÃÇÈç¹ûÃ¿´Î¶¼ÒªÊÖ¶¯µÄÌí¼Ó°ü¶ÔÓ¦µÄÎÄ¼ş¼Ğ£¬ÄÇ½«ÊÇÒ»¼ş²»ÄÇÃ´Óä¿ìµÄÊÂÇé£¬
ĞÒºÃJava±àÒëÆ÷ÎªÎÒÃÇ×¼±¸ÁËÕâÑùµÄ·½·¨£¬Ê¡È¥ÎÒÃÇ×Ô¼ºÊÖ¶¯Ìí¼Ó°ü¶ÔÓ¦µÄÎÄ¼ş¼Ğ¡£


E:\study\JAVA\Java-Study\JavaLesson\Lesson3>javac
ÓÃ·¨£ºjavac <Ñ¡Ïî> <Ô´ÎÄ¼ş>
ÆäÖĞ£¬¿ÉÄÜµÄÑ¡Ïî°üÀ¨£º
  -g                         Éú³ÉËùÓĞµ÷ÊÔĞÅÏ¢
  -g:none                    ²»Éú³ÉÈÎºÎµ÷ÊÔĞÅÏ¢
  -g:{lines,vars,source}     Ö»Éú³ÉÄ³Ğ©µ÷ÊÔĞÅÏ¢
  -nowarn                    ²»Éú³ÉÈÎºÎ¾¯¸æ
  -verbose                   Êä³öÓĞ¹Ø±àÒëÆ÷ÕıÔÚÖ´ĞĞµÄ²Ù×÷µÄÏûÏ¢
  -deprecation               Êä³öÊ¹ÓÃÒÑ¹ıÊ±µÄ API µÄÔ´Î»ÖÃ
  -classpath <Â·¾¶>            Ö¸¶¨²éÕÒÓÃ»§ÀàÎÄ¼şµÄÎ»ÖÃ
  -cp <Â·¾¶>                   Ö¸¶¨²éÕÒÓÃ»§ÀàÎÄ¼şµÄÎ»ÖÃ
  -sourcepath <Â·¾¶>           Ö¸¶¨²éÕÒÊäÈëÔ´ÎÄ¼şµÄÎ»ÖÃ
  -bootclasspath <Â·¾¶>        ¸²¸ÇÒıµ¼ÀàÎÄ¼şµÄÎ»ÖÃ
  -extdirs <Ä¿Â¼>              ¸²¸Ç°²×°µÄÀ©Õ¹Ä¿Â¼µÄÎ»ÖÃ
  -endorseddirs <Ä¿Â¼>         ¸²¸ÇÇ©ÃûµÄ±ê×¼Â·¾¶µÄÎ»ÖÃ
  -d <Ä¿Â¼>                    Ö¸¶¨´æ·ÅÉú³ÉµÄÀàÎÄ¼şµÄÎ»ÖÃ
  -encoding <±àÂë>             Ö¸¶¨Ô´ÎÄ¼şÊ¹ÓÃµÄ×Ö·û±àÂë
  -source <°æ±¾>               Ìá¹©ÓëÖ¸¶¨°æ±¾µÄÔ´¼æÈİĞÔ
  -target <°æ±¾>               Éú³ÉÌØ¶¨ VM °æ±¾µÄÀàÎÄ¼ş
  -version                   °æ±¾ĞÅÏ¢
  -help                      Êä³ö±ê×¼Ñ¡ÏîµÄÌáÒª
  -X                         Êä³ö·Ç±ê×¼Ñ¡ÏîµÄÌáÒª
  -J<±êÖ¾>                     Ö±½Ó½« <±êÖ¾> ´«µİ¸øÔËĞĞÊ±ÏµÍ³

-d ²ÎÊı¿ÉÒÔ°ïÖúÎÒÃÇ×Ô¶¯Éú³É°ü¶ÔÓ¦µÄÎÄ¼ş¼Ğ£¬²¢°ÑÀà·Åµ½ÏàÓ¦µÄÎÄ¼ş¼ĞÏÂ¡£
E:\study\JAVA\Java-Study\JavaLesson\Lesson3>javac -d . Test.java

E:\study\JAVA\Java-Study\JavaLesson\Lesson3>java cn/zieckey/Test
zieckey test!

±àÒë²¢Éú³É°ü
ÔÚµ±Ç°Ä¿Â¼ÏÂÉú³É°ü
    javac ¨Cd . Test.java
ÔÚÖ¸¶¨Ä¿Â¼ÏÂÉú³É°ü
    javac ¨Cd E:\JavaLesson Test.java

E:\study\JAVA\Java-Study\JavaLesson\Lesson3>javac -d d:\ Test.java

E:\study\JAVA\Java-Study\JavaLesson\Lesson3>set classpath=%classpath%;d:\

E:\study\JAVA\Java-Study\JavaLesson\Lesson3>java cn/zieckey/Test
zieckey test!


°üÖĞÀàµÄÊµÀı¶ÔÏóµÄÉùÃ÷£º
package cn.zieckey;
class Test
{
	public static void main( String[] args )
	{
		Test t = new Test();//ÔÚÕâ¸ö°üËùÔÚÔ´ÎÄ¼şÖĞ¿ÉÒÔÖ±½ÓÓÃÀàÃû
		cn.zieckey.Test tt = new cn.zieckey.Test();//Ò²¿ÉÒÔÓÃÍêÕûÃû³Æ
		System.out.println( "zieckey test!");
	}
}


importÓï¾ä
ÒıÈë°üÖĞµÄÀà¡£
    import java.io.File;
ÒıÈëÕû¸ö°ü¡£
    import java.io.*;
ÔÚÍ¬Ò»°üÖĞµÄÀà¿ÉÒÔ»¥ÏàÒıÓÃ£¬ÎŞĞèimportÓï¾ä¡£

×¢Òâ£ºjava.lang°üÖĞµÄÀàÊÇ×Ô¶¯µ¼ÈëµÄ£¬ËùÒÔÎÒÃÇÒıÓÃ¸Ã°üÖĞÀà¿ÉÒÔ²»ÓÃimportÓï¾äµ¼Èë¡£

µ±ÒıÓÃÆäËü°üÖĞµÄÀà£º
package cn.zieckey;
class Test
{
	public static void main( String[] args )
	{
		Test t = new Test();//ÔÚÕâ¸ö°üËùÔÚÔ´ÎÄ¼şÖĞ¿ÉÒÔÖ±½ÓÓÃÀàÃû
		cn.zieckey.Test tt = new cn.zieckey.Test();//Ò²¿ÉÒÔÓÃÍêÕûÃû³Æ
		java.io.File f ;//ÓÃÍêÕûÃû³ÆÒıÓÃÀà
		System.out.println( "zieckey test!");
	}
}

»òÕß£º
package cn.zieckey;
import java.io.File;
class Test
{
	public static void main( String[] args )
	{
		Test t = new Test();//ÔÚÕâ¸ö°üËùÔÚÔ´ÎÄ¼şÖĞ¿ÉÒÔÖ±½ÓÓÃÀàÃû
		cn.zieckey.Test tt = new cn.zieckey.Test();//Ò²¿ÉÒÔÓÃÍêÕûÃû³Æ
		File f ;//Èç¹ûÌáÇ°µ¼ÈëÁËÕâ¸ö°ü£¬¾Í¿ÉÒÔÖ±½ÓÓÃÀàÃû³ÆÒıÓÃÀà
		System.out.println( "zieckey test!");
	}
}

ÎÒÃÇÒ²¿ÉÒÔÖ±½ÓÍ¨¹ıµ¼ÈëËùÓĞ°ü£¬ÒÔÊ¡ÊÂ:import java.io.*;
µ«ÊÇÎÒÃÇÕâÑùµÄ»°,»áĞèÒª¸ü¶àµÄÄÚ´æ,Õâ¶ÔÓÚpcÀ´ËµÃ»ÓĞÊ²Ã´,µ«ÊÇ¶ÔÓÚÊÖ³ÖÊ½Ç¶ÈëÊ½Éè±¸,¾Í²»ÄÇÃ´ºÃÁË.

ÎÒÃÇÔÚÍ¬Ò»¸ö°üÖĞÔÙĞÂ½¨Ò»¸öÀà:
//Test2.java
package cn.zieckey;
class Test2
{
}

È»ºóÎÒÃÇÔÚTestÀàÖĞ¿ÉÒÔÖ±½ÓÒıÓÃTest2
//Test.java
package cn.zieckey;
import java.io.File;
class Test
{
	public static void main( String[] args )
	{
		/*
		Test t = new Test();//ÔÚÕâ¸ö°üËùÔÚÔ´ÎÄ¼şÖĞ¿ÉÒÔÖ±½ÓÓÃÀàÃû
		cn.zieckey.Test tt = new cn.zieckey.Test();//Ò²¿ÉÒÔÓÃÍêÕûÃû³Æ
		File f ;//Èç¹ûÌáÇ°µ¼ÈëÁËÕâ¸ö°ü£¬¾Í¿ÉÒÔÖ±½ÓÓÃÀàÃû³ÆÒıÓÃÀà
		System.out.println( "zieckey test!");
		*/
		Test2 t2 = new Test2();
	}
}

E:\JavaLesson\Lesson3>javac -d . *.java
±àÒëÃ»ÓĞÎÊÌâ
Èç¹ûÎÒÃÇµÄTest2.javaÎÄ¼şÊÇÕâÑùĞ´µÄ:
//Test2.java
//package cn.zieckey;
package com.zieckey;
class Test2
{
}
E:\JavaLesson\Lesson3>javac -d . *.java
Test.java:14: ÕÒ²»µ½·ûºÅ
·ûºÅ£º Àà Test2
Î»ÖÃ£º Àà cn.zieckey.Test
                Test2 t2 = new Test2();
                ^
Test.java:14: ÕÒ²»µ½·ûºÅ
·ûºÅ£º Àà Test2
Î»ÖÃ£º Àà cn.zieckey.Test
                Test2 t2 = new Test2();
                               ^
2 ´íÎó
±àÒë¾ÍÓĞ´íÎó,ÄÇÃ´ÎÒÃÇÖ»ÄÜÍ¨¹ıÔÚTest.javaÖĞµ¼ÈëTest2Õâ¸öÀà.
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
µ«ÊÇ±àÒë»¹ÊÇ³öÏÖÎÊÌâ:
E:\JavaLesson\Lesson3>javac -d . *.java
Test.java:4: com.zieckey.Test2 ÔÚ com.zieckey ÖĞ²»ÊÇ¹«¹²µÄ£»ÎŞ·¨´ÓÍâ²¿Èí¼ş°üÖĞ¶Ô
Æä½øĞĞ·ÃÎÊ
import com.zieckey.Test2;
                   ^
Test.java:15: ÕÒ²»µ½·ûºÅ
·ûºÅ£º Àà Test2
Î»ÖÃ£º Àà cn.zieckey.Test
                Test2 t2 = new Test2();
                ^
Test.java:15: ÕÒ²»µ½·ûºÅ
·ûºÅ£º Àà Test2
Î»ÖÃ£º Àà cn.zieckey.Test
                Test2 t2 = new Test2();
                               ^
3 ´íÎó

ÕâÀïÊÇËµ com.zieckey.Test2 ÔÚ com.zieckey ÖĞ²»ÊÇ¹«¹²µÄ£»ÎŞ·¨´ÓÍâ²¿Èí¼ş°üÖĞ¶Ô
Æä½øĞĞ·ÃÎÊ,ËùÒÔÓ¦¸Ã°Ñ com.zieckey.Test2 ¸ÄÎª¹²ÓĞµÄ.
//Test2.java
//package cn.zieckey;
package com.zieckey;
public class Test2
{
}
ÔÙ±àÒë¾ÍÃ»ÓĞÎÊÌâÁË.
E:\JavaLesson\Lesson3>javac -d . *.java

ÎÒÃÇ°ÑÒ»¸öÀàÉùÃ÷Îª¹²ÓĞµÄ¾ÍÊÇÈÃËüÄÜ²»ËùÓĞµÄÀàµ÷ÓÃ,Èç¹û²»ÉùÃ÷Îª¹²ÓĞ,
ÄÇÃ´Ëü¾ÍÊÇÈ±Ê¡µÄÀà,¾ÍÖ»ÄÜ±»Í¬Ò»¸ö°üÖĞµÄÀàµ÷ÓÃ.

ÀàµÄ·ÃÎÊËµÃ÷·û
 £¨1£©public
 £¨2£©default£¨²»¼Ó·ÃÎÊËµÃ÷·ûÊ±£©
ÀàµÄÆäËüĞŞÊÎ·û
 £¨1£©final,ÓÃËü¶¨ÒåµÄÀà¾Í²»ÄÜ±»¼Ì³Ğ.
 £¨2£©abstract


£¨1£©final,ÓÃËü¶¨ÒåµÄÀà¾Í²»ÄÜ±»¼Ì³Ğ.
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
Test.java:3: ÎŞ·¨´Ó×îÖÕ com.zieckey.Test2 ½øĞĞ¼Ì³Ğ
class Test extends com.zieckey.Test2
                              ^
1 ´íÎó


·½·¨µÄ·ÃÎÊËµÃ÷·û
 £¨1£©public
 £¨2£©protected
 £¨3£©default(²»¼Ó·ÃÎÊËµÃ÷·ûÊ±)
 £¨4£©private
·½·¨µÄÆäËüĞŞÊÎ·û
 £¨1£©static
 £¨2£©final
 £¨3£©abstract
 £¨4£©native
 £¨5£©synchronized


²âÊÔÀàµÄ·½·¨µÄ·ÃÎÊÈ¨ÏŞÎÊÌâ:
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

ÕâËµÃ÷ÔÚÍ¬Ò»ÀàÖĞpublic,protected,default,privateËÄÀà¶¼¿ÉÒÔ·ÃÎÊ.
ÏÖÔÚ½«Test2.java¸ÄÎª£º
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
Test2.java:11: privateMethod() ¿ÉÒÔÔÚ cn.zieckey.Test ÖĞ·ÃÎÊ private
                t.privateMethod();
                 ^
1 ´íÎó

ºÃµÄ£¬¾Í²»²âÊÔÄÇÃ´¶àÁË£¬×Ü½áÏÂ£º

			·½·¨µÄ·ÃÎÊ¿ØÖÆ£º
		public  	protected		default		private
Í¬Àà	ÊÇ			ÊÇ				ÊÇ			ÊÇ
Í¬°ü	ÊÇ			ÊÇ				ÊÇ
×ÓÀà	ÊÇ			ÊÇ
Í¨ÓÃĞÔ	ÊÇ

final·½·¨£º
ÎªÁËÈ·±£Ä³¸öº¯ÊıµÄĞĞÎªÔÚ¼Ì³Ğ¹ı³ÌÖĞ±£³Ö²»±ä£¬²¢ÇÒ²»ÄÜ±»¸²¸Ç£¨overridden£©£¬¿ÉÒÔÊ¹ÓÃfinal·½·¨¡£
ÎªÁËĞ§ÂÊÉÏµÄ¿¼ÂÇ£¬½«·½·¨ÉùÃ÷Îªfinal£¬ÈÃ±àÒëÆ÷¶Ô´Ë·½·¨µÄµ÷ÓÃ½øĞĞÓÅ»¯¡£Òª×¢ÒâµÄÊÇ£º±àÒëÆ÷»á×ÔĞĞ¶Ôfinal·½·¨½øĞĞÅĞ¶Ï£¬²¢¾ö¶¨ÊÇ·ñ½øĞĞÓÅ»¯¡£Í¨³£ÔÚ·½·¨µÄÌå»ıºÜĞ¡£¬¶øÎÒÃÇÈ·Êµ²»Ï£ÍûËü±»¸²¸ÇÊ±£¬²Å½«ËüÉùÃ÷Îªfinal¡£
classÖĞËùÓĞµÄprivateºÍstatic·½·¨×ÔÈ»¾ÍÊÇfinal¡£

³éÏó·½·¨ºÍ³éÏóÀà
ÔÚÀàÖĞÃ»ÓĞ·½·¨ÌåµÄ·½·¨£¬¾ÍÊÇ³éÏó·½·¨¡£
º¬ÓĞ³éÏó·½·¨µÄÀà£¬¼´Îª³éÏóÀà¡£
Èç¹ûÒ»¸ö×ÓÀàÃ»ÓĞÊµÏÖ³éÏó»ùÀàÖĞËùÓĞµÄ³éÏó·½·¨£¬Ôò×ÓÀàÒ²³ÉÎªÒ»¸ö³éÏóÀà¡£
ÎÒÃÇ¿ÉÒÔ½«Ò»¸öÃ»ÓĞÈÎºÎ³éÏó·½·¨µÄÀàÉùÃ÷Îªabstract£¬±ÜÃâÓÉÕâ¸öÀà²úÉúÈÎºÎµÄ¶ÔÏó¡£
¹¹Ôì·½·¨¡¢¾²Ì¬·½·¨¡¢Ë½ÓĞ·½·¨¡¢final·½·¨²»ÄÜ±»ÉùÃ÷Îª³éÏóµÄ·½·¨¡£
Àı×Ó:
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
Test.java:3: cn.zieckey.Test ²»ÊÇ³éÏóµÄ£¬²¢ÇÒÎ´¸²¸Ç cn.zieckey.Test ÖĞµÄ³éÏó·½·¨
 protectedMethod()
public class Test
       ^
1 ´íÎó

¾ÍÊÇËµ·½·¨ÊÇ³éÏóµÄ,µ«ÊÇÓµÓĞ¸Ã·½·¨µÄÀà²¢²»ÊÇ³éÏóµÄ.
±àÒë¾ÍÓĞ´íÎó¡£
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
Test.java:24: cn.zieckey.Test ÊÇ³éÏóµÄ£»ÎŞ·¨¶ÔÆä½øĞĞÊµÀı»¯
                Test t = new Test();
                         ^
1 ´íÎó
ÔÙĞŞ¸Ä:
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
ÕâÑù±àÒë¾ÍÃ»ÓĞÎÊÌâÁË.
×Ü½á£ºËùÒÔÈç¹û·½·¨ÊÇ³éÏóµÄ£¬ÄÇÃ´ÏàÓ¦µÄÀàÒ²ÒªÊÇ³éÏóµÄ£¬²¢ÇÒ³éÏóµÄÀà²»ÄÜÊµÀı»¯¡£

ÏÖÔÚÈÃTest2¼Ì³Ğ×ÔTest
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
Test2.java:4: cn.zieckey.Test2 ²»ÊÇ³éÏóµÄ£¬²¢ÇÒÎ´¸²¸Ç cn.zieckey.Test ÖĞµÄ³éÏó·½
·¨ protectedMethod()
public class Test2 extends Test
       ^
1 ´íÎó

ÔÙĞŞ¸Ä,½«ÉÏÃæµÄ³éÏó·½·¨¾ßÌå»¯:
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
±àÒëÃ»ÓĞ´íÎóÁË¡£

µ«ÊÇÈç¹ûÎÒÃÇÔÙ½«Test2.java¸ÄÎªÈçÏÂ£º
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
ÕâÑùÎÒÃÇ½«×ÓÀàÒ²ÉùÃ÷Îª³éÏóµÄ·½·¨£¬±àÒëÒ²¾ÍÃ»ÓĞ´íÎóÁË¡£

×Ü½á£º³éÏóµÄÀà±»¼Ì³ĞÊ±£¬ÒªÃ´×ÓÀàÒ²ÉùÃ÷Îª³éÏóÀà£¬ÒªÃ´ÔÚ×ÓÀàÖĞÊµÏÖ¸¸ÀàµÄ³éÏó·½·¨.


native·½·¨
{
	native·½·¨ÊÇÓÃ»§ÔÚJavaÖĞ¿ÉÒÔÊ¹ÓÃ£¬µ«²»ÄÜ±àĞ´µÄ·½·¨¡£
	JNI(Java Native Interface)£¬ËüÔÊĞíJavaĞéÄâ»ú(JVM)ÄÚ²¿ÔËĞĞµÄJava´úÂëÄÜ¹»
ÓëÓÃÆäËü±à³ÌÓïÑÔ(ÈçC¡¢C++¡¢»ã±àÓïÑÔ)±àĞ´µÄÓ¦ÓÃ³ÌĞòºÍ¿â½øĞĞ»¥²Ù×÷¡£
	JNI×î´óµÄºÃ´¦ÊÇËüÃ»ÓĞ¶Ôµ×²ãJavaĞéÄâ»úµÄÊµÏÖÊ©¼ÓÈÎºÎÏŞÖÆ,
Òò´Ë£¬JavaĞéÄâ»ú³§ÉÌ¿ÉÒÔÔÚ²»Ó°ÏìĞéÄâ»úÆäËü²¿·ÖµÄÇé¿öÏÂÌí¼Ó¶ÔJNIµÄÖ§³Ö¡£
³ÌĞòÔ±Ö»Ğè±àĞ´Ò»ÖÖ°æ±¾µÄ±¾µØ(Native)Ó¦ÓÃ³ÌĞòºÍ¿â£¬
¾ÍÄÜ¹»ÓëËùÓĞÖ§³ÖJNIµÄJavaĞéÄâ»úĞ­Í¬¹¤×÷¡£
	JNI¿ÉÒÔÀí½âÎªJavaºÍ±¾µØÓ¦ÓÃ³ÌĞòÖ®¼äµÄÖĞ½é¡£


´´½¨Ò»¸önative·½·¨£º
1. ´´½¨Ò»¸öHelloWorld.java
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

2. ±àÒë
E:\zieckey\Lesson3>javac HelloWorld.java

3. Éú³ÉÍ·ÎÄ¼ş
E:\zieckey\Lesson3>javah -jni HelloWorld

4. Ğ´ÊµÏÖÎÄ¼şHelloWorldImp.c
#include <jni.h>
#include "HelloWorld.h"
#include <stdio.h>

JNIEXPORT void JNICALL
Java_HelloWorld_displayHelloWorld(JNIEnv *env, jobject obj)
{
    printf("Hello world!\n");
    return;
}

5. Éú³É¶¯Ì¬Á¬½Ó¿â
ÕâÀïÔËÓÃVCµÄCL.exe¹¤¾ß£¬
»òÕßÖ±½ÓÔÚVCÏÂ½¨Á¢¹¤³ÌÀ´Éú³É£¨ÕâÀï×¢Òâ½«D:\Program Files\Java\jdk1.5.0_06\include£¬
D:\Program Files\Java\jdk1.5.0_06\include\win32ÕâÁ½¸öÄ¿Â¼¼ÓÈë»·¾³ÖĞ£©
E:\zieckey\Lesson3>cl -ID:\Program Files\Java\jdk1.5.0_06\include -ID:\Program Files\Java\jdk1.5.0_06\include\win32 -LDHelloWorldImp.c -Fhello.dll

6. Ö´ĞĞ
E:\zieckey\Lesson3>java HelloWorld







JNI

×î½üÔÚ¹«Ë¾Àï×öÁËÒ»¸öÊÖ»úµÄÏîÄ¿£¬ĞèÒªJAVA³ÌĞòÔÚ·¢ËÍ¶ÌĞÅµÄÊ±ºòºÍµÚÈı·½µÄ¶ÌĞÅ·şÎñÆ÷Á¬½Ó¡£¶ÌĞÅ½Ó¿ÚÊÇÓÃC++Ğ´µÄ¡£×ÁÄ¥ÁËÈıÌì£¬´óÖÂ¸ã¶®ÁËJNIµÄÖ÷Ìå²¿·Ö¡£ÏÈ½«ĞÄµÃÕûÀí£¬Ï£Íû¸÷Î»ÅóÓÑÉÙ×ßÍäÂ·¡£
Ê×ÏÈÒıÓÃÒ»ÆªÎÄÕÂ£¬½éÉÜÒ»¸ö¼òµ¥µÄJNIµÄµ÷ÓÃµÄ¹ı³Ì¡£
JAVAÒÔÆä¿çÆ½Ì¨µÄÌØĞÔÉîÊÜÈËÃÇÏ²°®£¬¶øÓÖÕıÓÉÓÚËüµÄ¿çÆ½Ì¨µÄÄ¿µÄ£¬Ê¹µÃËüºÍ±¾µØ»úÆ÷µÄ¸÷ÖÖÄÚ²¿ÁªÏµ±äµÃºÜÉÙ£¬Ô¼ÊøÁËËüµÄ¹¦ÄÜ¡£½â¾öJAVA¶Ô±¾µØ²Ù×÷µÄÒ»ÖÖ·½·¨¾ÍÊÇJNI¡£
JAVAÍ¨¹ıJNIµ÷ÓÃ±¾µØ·½·¨£¬¶ø±¾µØ·½·¨ÊÇÒÔ¿âÎÄ¼şµÄĞÎÊ½´æ·ÅµÄ£¨ÔÚWINDOWSÆ½Ì¨ÉÏÊÇDLLÎÄ¼şĞÎÊ½£¬ÔÚUNIX»úÆ÷ÉÏÊÇSOÎÄ¼şĞÎÊ½£©¡£Í¨¹ıµ÷ÓÃ±¾µØµÄ¿âÎÄ¼şµÄÄÚ²¿·½·¨£¬Ê¹JAVA¿ÉÒÔÊµÏÖºÍ±¾µØ»úÆ÷µÄ½ôÃÜÁªÏµ£¬µ÷ÓÃÏµÍ³¼¶µÄ¸÷½Ó¿Ú·½·¨¡£
¼òµ¥½éÉÜ¼°Ó¦ÓÃÈçÏÂ£º
Ò»¡¢JAVAÖĞËùĞèÒª×öµÄ¹¤×÷
ÔÚJAVA³ÌĞòÖĞ£¬Ê×ÏÈĞèÒªÔÚÀàÖĞÉùÃ÷Ëùµ÷ÓÃµÄ¿âÃû³Æ£¬ÈçÏÂ£º
static {
System.loadLibrary(¡°goodluck¡±);
}

ÔÚÕâÀï£¬¿âµÄÀ©Õ¹Ãû×Ö¿ÉÒÔ²»ÓÃĞ´³öÀ´£¬¾¿¾¹ÊÇDLL»¹ÊÇSO£¬ÓÉÏµÍ³×Ô¼ºÅĞ¶Ï¡£
»¹ĞèÒª¶Ô½«Òªµ÷ÓÃµÄ·½·¨×ö±¾µØÉùÃ÷£¬¹Ø¼ü×ÖÎªnative¡£²¢ÇÒÖ»ĞèÒªÉùÃ÷£¬¶ø²»ĞèÒª¾ß ÌåÊµÏÖ¡£ÈçÏÂ£º
public native static void set(int i);
public native static int get();
È»ºó±àÒë¸ÃJAVA³ÌĞòÎÄ¼ş£¬Éú³ÉCLASS£¬ÔÙÓÃJAVAHÃüÁî£¬JNI¾Í»áÉú³ÉC/C++µÄÍ·ÎÄ¼ş¡£
ÀıÈç³ÌĞòtestdll.java£¬ÄÚÈİÎª£º
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

ÓÃjavac testdll.java±àÒëËü£¬»áÉú³Étestdll.class¡£
ÔÙÓÃjavah testdll£¬Ôò»áÔÚµ±Ç°Ä¿Â¼ÏÂÉú³Étestdll.hÎÄ¼ş£¬Õâ¸öÎÄ¼şĞèÒª±»C/C++³ÌĞòµ÷ÓÃÀ´Éú³ÉËùĞèµÄ¿âÎÄ¼ş¡£
¶ş¡¢C/C++ÖĞËùĞèÒª×öµÄ¹¤×÷
¶ÔÓÚÒÑÉú³ÉµÄ.hÍ·ÎÄ¼ş£¬C/C++ËùĞèÒª×öµÄ£¬¾ÍÊÇ°ÑËüµÄ¸÷¸ö·½·¨¾ßÌåµÄÊµÏÖ¡£È»ºó±àÒëÁ¬½Ó³É¿âÎÄ¼ş¼´¿É¡£ÔÙ°Ñ¿âÎÄ¼ş¿½±´µ½JAVA³ÌĞòµÄÂ·¾¶ÏÂÃæ£¬¾Í¿ÉÒÔÓÃJAVAµ÷ÓÃC/C++ËùÊµÏÖµÄ¹¦ÄÜÁË¡£
½ÓÉÏÀı×Ó¡£ÎÒÃÇÏÈ¿´Ò»ÏÂtestdll.hÎÄ¼şµÄÄÚÈİ£º
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
ÔÚ¾ßÌåÊµÏÖµÄÊ±ºò£¬ÎÒÃÇÖ»¹ØĞÄÁ½¸öº¯ÊıÔ­ĞÍ
JNIEXPORT jint JNICALL Java_testdll_get (JNIEnv *, jclass); ºÍ
JNIEXPORT void JNICALL Java_testdll_set (JNIEnv *, jclass, jint);
ÕâÀïJNIEXPORTºÍJNICALL¶¼ÊÇJNIµÄ¹Ø¼ü×Ö£¬±íÊ¾´Ëº¯ÊıÊÇÒª±»JNIµ÷ÓÃµÄ¡£¶øjintÊÇÒÔJNIÎªÖĞ½éÊ¹JAVAµÄintÀàĞÍÓë±¾µØµÄ int¹µÍ¨µÄÒ»ÖÖÀàĞÍ£¬ÎÒÃÇ¿ÉÒÔÊÓ¶ø²»¼û£¬¾Íµ±×öintÊ¹ÓÃ¡£º¯ÊıµÄÃû³ÆÊÇJAVA_ÔÙ¼ÓÉÏjava³ÌĞòµÄpackageÂ·¾¶ÔÙ¼Óº¯ÊıÃû×é³ÉµÄ¡£²ÎÊıÖĞ£¬ÎÒÃÇÒ²Ö»ĞèÒª¹ØĞÄÔÚJAVA³ÌĞòÖĞ´æÔÚµÄ²ÎÊı£¬ÖÁÓÚJNIEnv*ºÍjclassÎÒÃÇÒ»°ãÃ»ÓĞ±ØÒªÈ¥ÅöËü¡£
ºÃ£¬ÏÂÃæÎÒÃÇÓÃtestdll.cppÎÄ¼ş¾ßÌåÊµÏÖÕâÁ½¸öº¯Êı£º
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
±àÒëÁ¬½Ó³É¿âÎÄ¼ş£¬±¾ÀıÊÇÔÚWINDOWSÏÂ×öµÄ£¬Éú³ÉµÄÊÇDLLÎÄ¼ş¡£²¢ÇÒÃû³ÆÒªÓëJAVAÖĞĞèÒªµ÷ÓÃµÄÒ»ÖÂ£¬ÕâÀï¾ÍÊÇgoodluck.dll ¡£°Ñgoodluck.dll¿½±´µ½testdll.classµÄÄ¿Â¼ÏÂ£¬java testdllÔËĞĞËü£¬¾Í¿ÉÒÔ¹Û²ìµ½½á¹ûÁË¡£  











À¬»ø»ØÊÕ£º
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
¿´¿´ÉÏÃæ³ÌĞòÔËĞĞ¿´¿´£º

E:\zieckey\Lesson3>javac Garbage.java

E:\zieckey\Lesson3>java Garbage
object 1 constructed
object 2 constructed
object 3 constructed
object 4 constructed
¿ÉÒÔ·¢ÏÖ£¬ÕâÀï²¢Ã»ÓĞ»ØÊÕÀ¬»ø£¨»ØÊÕÀ¬»ø»á×Ô¶¯µ÷ÓÃfinalize·½·¨£©£¬
ÕâÊÇÒòÎª£¬ĞéÄâ»úÊÇ¶¯Ì¬»ØÊÕÀ¬»øµÄ£¬µ±ÏµÍ³ÄÚ´æ²»¹»ÓÃµÄÊ±ºò²Å½øĞĞÀ¬»ø»ØÊÕ£¬
À¬»ø»ØÊÕµÄÏß³ÌµÄÓÅÏÈ¼¶ºÜµÍ¡£
ÎÒÃÇ¿ÉÒÔÏÔÊ¾µÄµ÷ÓÃÀ¬»ø»ØÊÕÆ÷»ØÊÕÀ¬»ø£º
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
		System.gc();//ÏÔÊ¾µÄµ÷ÓÃÀ¬»ø»ØÊÕÆ÷»ØÊÕÀ¬»ø
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


½Ó¿ÚµÄµ÷ÓÃ£º
½Ó¿ÚÖĞËùÓĞµÄ·½·¨¶¼ÊÇpublic abstract¡£
ÔÚ½Ó¿ÚÖĞÉùÃ÷·½·¨Ê±£¬²»ÄÜÊ¹ÓÃnative¡¢static ¡¢final ¡¢synchronized ¡¢private ¡¢protectedµÈĞŞÊÎ·û¡£
ºÍpublicÀàÒ»Ñù£¬public½Ó¿ÚÒ²±ØĞë¶¨ÒåÔÚÓë½Ó¿ÚÍ¬ÃûµÄÎÄ¼şÖĞ¡£
½Ó¿ÚÖĞ¿ÉÒÔÓĞÊı¾İ³ÉÔ±£¬ÕâĞ©³ÉÔ±Ä¬ÈÏ¶¼ÊÇpublic static final¡£
Ò»¸ö½Ó¿Ú¿ÉÒÔ¼Ì³Ğ×ÔÁíÒ»¸ö½Ó¿Ú¡£
JavaÖĞ²»ÔÊĞíÀàµÄ¶à¼Ì³Ğ£¬µ«ÔÊĞí½Ó¿ÚµÄ¶à¼Ì³Ğ¡£
ÔÚJavaÖĞ£¬Ò»¸öÀà¿ÉÒÔÊµÏÖ¶à¸ö½Ó¿Ú¡£
Ò»¸öÀàÔÚ¼Ì³ĞÁíÍâÒ»¸öÀàµÄÍ¬Ê±£¬¿ÉÒÔÊµÏÖ¶à¸ö½Ó¿Ú¡£



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
		System.out.println( "¶ÌÅÜ" );
	}
	void jump()
	{
		System.out.println( "Ìø¸ß" );
	}

	public static void main( String[] args )
	{
		Athlete zhangsan = new Athlete();
		zhangsan.run();
		zhangsan.jump();
	}
}

E:\zieckey\Lesson3>javac Sport.java
Sport.java:13: Athlete ÖĞµÄ jump() ÎŞ·¨ÊµÏÖ Sport ÖĞµÄ jump()£»ÕıÔÚ³¢ÊÔÖ¸¶¨¸üµÍ
µÄ·ÃÎÊÈ¨ÏŞ£»Îª public
        void jump()
             ^
Sport.java:9: Athlete ÖĞµÄ run() ÎŞ·¨ÊµÏÖ Sport ÖĞµÄ run()£»ÕıÔÚ³¢ÊÔÖ¸¶¨¸üµÍµÄ·Ã
ÎÊÈ¨ÏŞ£»Îª public
        void run()
             ^
2 ´íÎó

½Ó¿ÚËµÃ÷ÁË£¬½Ó¿ÚÖĞËùÓĞµÄ·½·¨¶¼ÊÇpublic abstract£¬
ÄÇÃ´ÔÚÊµÏÖÖĞ¾Í²»ÄÜ±È¸Ã·ÃÎÊÈ¨ÏŞ¸üµÍ£¬ËùÒÔ³öÏÖÉÏÃæ´íÎó£¬
ÎÒÃÇ¸Ä¸ÄÔ´ÎÄ¼ş¿´¿´£º
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
		System.out.println( "¶ÌÅÜ" );
	}
	void jump()
	{
		System.out.println( "Ìø¸ß" );
	}

	public static void main( String[] args )
	{
		Athlete zhangsan = new Athlete();
		zhangsan.run();
		zhangsan.jump();
	}
}

E:\zieckey\Lesson3>javac Sport.java
Sport.java:13: Athlete ÖĞµÄ jump() ÎŞ·¨ÊµÏÖ Sport ÖĞµÄ jump()£»ÕıÔÚ³¢ÊÔÖ¸¶¨¸üµÍ
µÄ·ÃÎÊÈ¨ÏŞ£»Îª public
        void jump()
             ^
1 ´íÎó


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
		System.out.println( "¶ÌÅÜ" );
	}
	public void jump()
	{
		System.out.println( "Ìø¸ß" );
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
¶ÌÅÜ
Ìø¸ß

E:\zieckey\Lesson3>

½«ÊµÏÖÖĞµÄ·½·¨·ÃÎÊÈ¨ÏŞ¸ÄÎª½Ó¿ÚµÄµÈÍ¬»òÕß¸ü¸ß¾Í¿ÉÒÔÁË¡£
ÏÂÃæ¿´¿´Ö»ÊµÏÖ½Ó¿ÚÖĞµÄÒ»¸ö·½·¨£º
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
		System.out.println( "¶ÌÅÜ" );
	}
	/*public void jump()
	{
		System.out.println( "Ìø¸ß" );
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
Sport.java:7: Athlete ²»ÊÇ³éÏóµÄ£¬²¢ÇÒÎ´¸²¸Ç Sport ÖĞµÄ³éÏó·½·¨ jump()
class Athlete implements Sport
^
Sport.java:22: ÕÒ²»µ½·ûºÅ
·ûºÅ£º ·½·¨ jump()
Î»ÖÃ£º Àà Athlete
                zhangsan.jump();
                        ^
2 ´íÎó

ÕâÊÇÒòÎª½Ó¿ÚÖĞµÄËùÓĞ·½·¨¶¼ÊÇpublic abstract£¬ËùÒÔ³öÏÖ´íÎó¡£

ÏÂÃæ¿´¿´Ò»¸öÍ¨¹ı½Ó¿ÚÊµÏÖĞ­Í¬¹¤×÷µÄÀı×Ó£º
ÏÖÔÚÎÒÃÇĞèÒªÔÚÖ÷°å³§ÉÌºÍÏÔ¿¨³§ÉÌÖ®¼ä¶¨ÒåÒ»¸öÏÔ¿¨²å²ÛµÄ½Ó¿Ú£¬
È»ºó¸ù¾İÕâ¸ö±ê×¼½Ó¿Ú£¬ÏÔ¿¨³§ÉÌÉú²úÏÔ¿¨£¬Ö÷°å³§ÉÌÉú²úÖ÷°å¡£
³ÌĞòÊµÏÖÈçÏÂ£º

ÏÔ¿¨²å²Û½Ó¿Ú£º
//VideoCard.java
interface VideoCard
{
	void display();
	String getName();
}

ÏÔ¿¨Éú²ú³§ÉÌÉú²úÏÔ¿¨£º
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

Ö÷°åÉú²ú³§ÉÌÉú²úÖ÷°å
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

	//ÕâÀïÍ¨¹ı½Ó¿Ú×÷ÎªĞÎ²Î£¬ÔÚµ÷ÓÃ¸Ã·½·¨µÄÊ±ºò£¬
	//»á´«ÈëÒ»¸öÊµÏÖ¸Ã½Ó¿ÚµÄÀàµÄÊµÀı¶ÔÏó
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

ÏÖÔÚ¾Í¿ÉÒÔ×é×°µçÄÔÁË
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

±àÒë£º
E:\zieckey\Lesson3\interface>javac *.java

E:\zieckey\Lesson3\interface>java Computer
AMD's CPU
Dmeng's VideoCard
Dmeng's VideoCard is working!
MainBoard is running...


ÔÙ¿´Ò»¸öÀı×Ó£º
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
//ÊµÏÖ¶à¸ö½Ó¿Ú
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
//ÔÚ¼Ì³ĞÀàµÄÍ¬Ê±£¬ÊµÏÖ¶à¸ö½Ó¿Ú
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




ÄÚ²¿Àà£º
ÔÚ·½·¨ÖĞ¶¨ÒåµÄÄÚ²¿Àà£¬Èç¹ûÒª·ÃÎÊ·½·¨ÖĞ¶¨ÒåµÄ±¾µØ±äÁ¿»ò·½·¨µÄ²ÎÊı£¬Ôò±äÁ¿±ØĞë±»ÉùÃ÷final¡£
ÄÚ²¿Àà¿ÉÒÔÉùÃ÷Îªprivate»òprotected£»»¹¿ÉÒÔÉùÃ÷Îªabstract»òfinal¡£
ÄÚ²¿Àà¿ÉÒÔÉùÃ÷ÎªstaticµÄ£¬µ«´ËÊ±¾Í²»ÄÜÔÙÊ¹ÓÃÍâ²¿ÀàµÄ·ÇstaticµÄ³ÉÔ±±äÁ¿ºÍ·ÇstaticµÄ³ÉÔ±·½·¨£»
·ÇstaticµÄÄÚ²¿ÀàÖĞµÄ³ÉÔ±²»ÄÜÉùÃ÷ÎªstaticµÄ£¬Ö»ÓĞÔÚ¶¥²ãÀà»òstaticµÄÄÚ²¿ÀàÖĞ²Å¿ÉÉùÃ÷static³ÉÔ±¡£

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
			System.out.println( index );	//¾Ö²¿±äÁ¿
			System.out.println( this.index );	//innerÀà±äÁ¿
			System.out.println( Outer.this.index );	//OuterÀà±äÁ¿
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

±àÒë£º
E:\zieckey\Lesson4>javac Outer.java

E:\zieckey\Lesson4>java Test
30
50
100



·ÃÎÊÄÚ²¿ÀàµÄ·½·¨£º
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
			System.out.println( index );	//¾Ö²¿±äÁ¿
			System.out.println( this.index );	//innerÀà±äÁ¿
			System.out.println( Outer.this.index );	//OuterÀà±äÁ¿
		}
	}
	void print()
	{
		Inner inner = new Inner();
		inner.print();
	}

	Inner getInner() //Ìá¹©·ÃÎÊÄÚ²¿ÀàµÄ·½·¨
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
		Outer.Inner inner = outer.getInner();//ÕâÀïÍ¨¹ıOuter.Inner´ïµ½·ÃÎÊÄÚ²¿Àà
		inner.print();
	}
}

Èç¹ûmain·½·¨ÔÚOuterÀàÖĞ£º
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
			System.out.println( index );	//¾Ö²¿±äÁ¿
			System.out.println( this.index );	//innerÀà±äÁ¿
			System.out.println( Outer.this.index );	//OuterÀà±äÁ¿
		}
	}
	void print()
	{
		Inner inner = new Inner();
		inner.print();
	}

	Inner getInner() //Ìá¸ß·ÃÎÊÄÚ²¿ÀàµÄ·½·¨
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
»òÕß
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
			System.out.println( index );	//¾Ö²¿±äÁ¿
			System.out.println( this.index );	//innerÀà±äÁ¿
			System.out.println( Outer.this.index );	//OuterÀà±äÁ¿
		}
	}
	void print()
	{
		Inner inner = new Inner();
		inner.print();
	}

	Inner getInner() //Ìá¸ß·ÃÎÊÄÚ²¿ÀàµÄ·½·¨
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


ÄÚ²¿ÀàÄÜÖ±½ÓÍ¨¹ınewÀ´Éú³ÉÄØ£¿

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
			System.out.println( index );	//¾Ö²¿±äÁ¿
			System.out.println( this.index );	//innerÀà±äÁ¿
			System.out.println( Outer.this.index );	//OuterÀà±äÁ¿
		}
	}
	void print()
	{
		Inner inner = new Inner();
		inner.print();
	}

	Inner getInner() //Ìá¸ß·ÃÎÊÄÚ²¿ÀàµÄ·½·¨
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
Outer.java:33: ÎŞ·¨´Ó¾²Ì¬ÉÏÏÂÎÄÖĞÒıÓÃ·Ç¾²Ì¬ ±äÁ¿ this
                Inner inner = new Inner();
                              ^
1 ´íÎó

¿´À´ÕâÑùÊÇ²»ĞĞµÄ£¬ÄÚ²¿Àà²»ÄÜÖ±½ÓÍ¨¹ınewÀ´Éú³É
µ«ÊÇ¿ÉÒÔÍ¨¹ıÍâ²¿ÀàÀ´Éú³É£º
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
			System.out.println( index );	//¾Ö²¿±äÁ¿
			System.out.println( this.index );	//innerÀà±äÁ¿
			System.out.println( Outer.this.index );	//OuterÀà±äÁ¿
		}
	}
	void print()
	{
		Inner inner = new Inner();
		inner.print();
	}

	Inner getInner() //Ìá¸ß·ÃÎÊÄÚ²¿ÀàµÄ·½·¨
	{
		return new Inner();
	}
}

class Test
{
	public static void main( String[] args )
	{
		Outer outer = new Outer();

		//ÕâÀïÈç¹ûÖ±½ÓÓÃnewÉú³ÉInner¶ÔÏóµÄ»°£¬
		//ÔÚInnerÀàµÄÄÚ²¿Ëù·ÃÎÊµÄOuterÀàµÄÊı¾İ³ÉÔ±¾ÍÊôÓÚÃ»ÓĞ³õÊ¼»¯µÄÊı¾İ±äÁ¿£¬
		//ÕâÏÔÈ»ÊÇ²»ĞĞµÄ£¬ËùÒÔÒªÍ¨¹ıOuterÀàµÄÊµÀıouter outer.new À´Éú³ÉInner¶ÔÏó
		Outer.Inner inner = outer.new Inner();
		inner.print();
	}
}

ÄÚ²¿Àà»¹¿ÉÒÔ·Åµ½³ÉÔ±·½·¨ÖĞ£¬»òÕßÌõ¼şÅĞ¶ÏÓï¾äÖĞ£º

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
						System.out.println( index );	//¾Ö²¿±äÁ¿
						System.out.println( this.index );	//innerÀà±äÁ¿
						System.out.println( Middle.this.index );	//MiddleÀà±äÁ¿
						System.out.println( Outer.this.index );	//OuterÀà±äÁ¿
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
Ò²¾ÍÊÇËµ²»¹ÜÄÚ²¿ÀàÇ¶Ì×ÓĞ¶àÉî£¬¶¼¿ÉÒÔËæÒâ·ÃÎÊÍâ²¿ÀàµÄ³ÉÔ±¡£


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
						System.out.println( index );	//¾Ö²¿±äÁ¿
						System.out.println( this.index );	//innerÀà±äÁ¿
						System.out.println( Middle.this.index );	//MiddleÀà±äÁ¿
						System.out.println( Outer.this.index );	//OuterÀà±äÁ¿
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
Outer.java:23: ´ÓÄÚ²¿ÀàÖĞ·ÃÎÊ¾Ö²¿±äÁ¿ a£»ĞèÒª±»ÉùÃ÷Îª×îÖÕÀàĞÍ
                                                a = 5;
                                                ^
Outer.java:24: ´ÓÄÚ²¿ÀàÖĞ·ÃÎÊ¾Ö²¿±äÁ¿ b£»ĞèÒª±»ÉùÃ÷Îª×îÖÕÀàĞÍ
                                                b = 6;
                                                ^
2 ´íÎó

¿´µ½´íÎóÌáÊ¾ÁË£¬ÎÒÃÇ½«a£¬bÉùÃ÷ÎªfinalÀàĞÍ£º
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
						System.out.println( index );	//¾Ö²¿±äÁ¿
						System.out.println( this.index );	//innerÀà±äÁ¿
						System.out.println( Middle.this.index );	//MiddleÀà±äÁ¿
						System.out.println( Outer.this.index );	//OuterÀà±äÁ¿
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
ÕâÑù±àÒë¾ÍÃ»ÓĞÎÊÌâ£¬


´ÓÄÚ²¿ÀàÅÉÉúÀàµÄÓÃ·¨:
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
Car.java:8: ĞèÒª°üº¬ Car.Wheel µÄ·â±ÕÊµÀı
class PanelWheel extends Car.Wheel
^
1 ´íÎó
ÕâÀïÊÇÒòÎª,Íâ²¿ÄÚ»¹Ã»ÓĞ²úÉúÊµÀı¶ÔÏó,ÄÚ²¿Àà¾Í²»¿ÉÄÜ´æÔÚ,ÄÇºÍÌ¸³õÊ¼»¯ÄØ?

ÕâÊ±ºòÎÒÃÇĞèÒªÏñÏÂÃæµÄ·½·¨ÄÇÑù´ÓÄÚ²¿ÀàÅÉÉúÀà:

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

¿ÉÒÔÍ¨¹ıÄÚ²¿ÀàÊµÏÖ½Ó¿Ú:
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

ÁíÍâÎÒÃÇ»¹¿ÉÒÔÕâÑùÊµÏÖ½Ó¿Ú:
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
		return new Animal()//ÕâÀï¾Í¶¨ÒåÁËÒ»¸öÀà,Ö»ÊÇÕâ¸öÀàÃ»ÓĞÃû×Ö,Õâ¾ÍÊÇÄäÃûµÄÄÚ²¿Àà
		{
			public void eat()
			{
				System.out.println("animal eat");
			}
			public void sleep()
			{
				System.out.println("animal sleep");
			}
		};//Õâ¸öµØ·½µÄ·ÖºÅ²»ÄÜÉÙ,ÒòÎªÕâÊÇÒ»¸öreturnÓï¾ä
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

ÎÒÃÇÎªÊ²Ã´Ê¹ÓÃÄÚ²¿Àà
1¡¢ÔÚÄÚ²¿Àà£¨inner class£©ÖĞ£¬¿ÉÒÔËæÒâµÄ·ÃÎÊÍâ²¿ÀàµÄ³ÉÔ±£¬Õâ¿ÉÒÔÈÃÎÒÃÇ¸üºÃµØ×éÖ¯¹ÜÀíÎÒÃÇµÄ´úÂë£¬ÔöÇ¿´úÂëµÄ¿É¶ÁĞÔ¡£
2¡¢ÄÚ²¿Àà¿ÉÒÔÓÃÓÚ´´½¨ÊÊÅäÆ÷Àà£¬ÊÊÅäÆ÷ÀàÊÇÓÃÓÚÊµÏÖ½Ó¿ÚµÄÀà¡£Ê¹ÓÃÄÚ²¿ÀàÀ´ÊµÏÖ½Ó¿Ú£¬¿ÉÒÔ¸üºÃµØ¶¨Î»Óë½Ó¿Ú¹ØÁªµÄ·½·¨ÔÚ´úÂëÖĞµÄÎ»ÖÃ¡£
3¡¢ÄÚ²¿ÀàµÄ¸ü¶àÓÃ·¨¡£
ÄÚ²¿Àà¿ÉÒÔÒş²ØÓÃ»§ÊµÏÖ½Ó¿ÚµÄÏ¸½Ú,
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


¼ÙÈçÎÒÃÇÏëÅÉÉúÒ»¸öÀàÍ¬Ê±ÊµÏÖÒ»¸ö½Ó¿Ú,µ«ÊÇÔÚ¸¸ÀàÖĞÓĞÒ»¸ö·½·¨ºÍ½Ó¿ÚÖĞ·½·¨Í¬Ãû,
Õâ¸öÊ±ºò,ÎÒÃÇ¾Í¿ÉÒÔÍ¨¹ıÄÚ²¿ÀàÊµÏÖ:
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
//RobotÀà¼Ì³Ğ×ÔPersonÀà,Í¬Ê±ÒªÊµÏÖÒ»¸öMachine½Ó¿Ú
//¶øÕâ¸ö½Ó¿Ú·½·¨ºÍPersonÀàµÄ³ÉÔ±·½·¨Í¬Ãû,Õâ¸öÊ±ºò¾Í¿ÉÒÔÍ¨¹ıÄÚ²¿ÀàÊµÏÖ
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

ÄÚ²¿Àà½â¾ö¶àÖØ¼Ì³ĞµÄÎÊÌâ:
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
		return new B()//BÊÇ³éÏóµÄ,ËùÒÔ±ØĞëÊµÏÖËüµÄ³éÏó·½·¨
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




JavaÖĞµÄÒì³£´¦Àí:
Java³ÌĞòÔÚÖ´ĞĞ¹ı³ÌÖĞÈç³öÏÖÒì³££¬»á×Ô¶¯Éú³ÉÒ»¸öÒì³£Àà¶ÔÏó£¬¸ÃÒì³£¶ÔÏó½«±»Ìá½»¸øJavaÔËĞĞÊ±ÏµÍ³£¬Õâ¸ö¹ı³Ì³ÆÎªÅ×³ö(throw)Òì³£¡£
µ±JavaÔËĞĞÊ±ÏµÍ³½ÓÊÕµ½Òì³£¶ÔÏóÊ±£¬»áÑ°ÕÒÄÜ´¦ÀíÕâÒ»Òì³£µÄ´úÂë²¢°Ñµ±Ç°Òì³£¶ÔÏó½»¸øÆä´¦Àí£¬ÕâÒ»¹ı³Ì³ÆÎª²¶»ñ(catch)Òì³£¡£
Èç¹ûJavaÔËĞĞÊ±ÏµÍ³ÕÒ²»µ½¿ÉÒÔ²¶»ñÒì³£µÄ·½·¨£¬ÔòÔËĞĞÊ±ÏµÍ³½«ÖÕÖ¹£¬ÏàÓ¦µÄJava³ÌĞòÒ²½«ÍË³ö¡£
try/catch/finallyÓï¾ä¡£

¶ÔÓÚRuntimeException£¬Í¨³£²»ĞèÒªÎÒÃÇÈ¥²¶»ñ£¬ÕâÀàÒì³£ÓÉJavaÔËĞĞÏµÍ³×Ô¶¯Å×³ö²¢×Ô¶¯´¦Àí¡£
Èç¹û¸¸ÀàÖĞµÄ·½·¨Å×³ö¶à¸öÒì³££¬Ôò×ÓÀàÖĞµÄ¸²¸Ç·½·¨ÒªÃ´Å×³öÏàÍ¬µÄÒì³££¬ÒªÃ´Å×³öÒì³£µÄ×ÓÀà£¬µ«²»ÄÜÅ×³öĞÂµÄÒì³££¨×¢£º¹¹Ôì·½·¨³ıÍâ£©¡£
ÎÒÃÇ¿ÉÒÔÔÚ·½·¨ÉùÃ÷Ê±£¬ÉùÃ÷Ò»¸ö²»»áÅ×³öµÄÒì³££¬Java±àÒëÆ÷¾Í»áÇ¿ÆÈ·½·¨µÄÊ¹ÓÃÕß¶ÔÒì³£½øĞĞ´¦Àí¡£ÕâÖÖ·½Ê½Í¨³£Ó¦ÓÃÓÚabstract base classºÍinterfaceÖĞ¡£



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
		System.out.println( "Finish" );//Õâ¸öÓï¾äÊÇ²»±»Ö´ĞĞµÄ
	}
}
E:\zieckey\Lesson4>java ExcepTest
Exception in thread "main" java.lang.ArithmeticException: / by zero
        at Excep.division(Excep.java:6)
        at ExcepTest.main(Excep.java:15)
ÕâÀïÊÇ¸öÒì³£´¦Àí,±»0³ı

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


tryÓï¾ä¿éÖĞµÄÓï¾äÔÚ·¢ÉúÒì³£Ê±¾ÍÌø×ªµ½catchÓï¾ä

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
			excep.division(5,0);//tryÓï¾ä¿éÖĞµÄÓï¾äÔÚ·¢ÉúÒì³£Ê±¾ÍÌø×ªµ½catchÓï¾ä
			System.out.println( "Exception" );//¸ÃÓï¾äÊÇ²»±»Ö´ĞĞµÄ
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

´òÓ¡Òì³£ĞÅÏ¢:
	catch(Exception e)
	{
		//ÕâÈıÖÖ·½·¨¶¼¿ÉÒÔ
		System.out.println(e.getMessage());
		System.out.println(e.toString());
		e.printStackTrace();
	}
ÎÒÃÇÔÚĞ´³ÌĞòµÄÊ±ºò,Èç¹û±àĞ´µÄ´úÂë¿ÉÄÜÒı·¢Òì³£,ÄÇÃ´ÔÚ±àĞ´µÄÊ±ºò¾Í½øĞĞÒì³£²¶»ñ,
ÀıÈçÕâÀïµÄ a/b ´¦:
		try
		{
			return a/b;
		}
		catch(Exception e)
		{

			e.printStackTrace();
			return 0;
		}
ÄÇÃ´ÔÚºóÃæµ÷ÓÃµÄÊ±ºò¾Í²»ĞèÒª½øĞĞÒì³£´¦ÀíÁË.
Èç¹ûÔÚ±àĞ´´úÂëµÄÊ±ºò²»Ïë×Ô¼º´¦ÀíÒì³£,ÄÇÃ´¿ÉÒÔÅ×³öÒ»¸öÒì³£,ÈÃÓÃ»§µ÷ÓÃµÄÊ±ºò×Ô¼º´¦Àí.
ÕâÀï¿ÉÒÔÕâÑù,ÀıÈç:
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
Excep.java:15: Î´±¨¸æµÄÒì³£ java.lang.Exception£»±ØĞë¶ÔÆä½øĞĞ²¶×½»òÉùÃ÷ÒÔ±ãÅ×³ö
                excep.division(5,0);
                              ^
1 ´íÎó
ÕâÀï¾Í¸æËßÓÃ»§ÔÚµ÷ÓÃÅ×³öÒì³£µÄº¯Êı»ò·½·¨Ê±,±ØĞë½øĞĞÒì³£´¦Àí.

¿ÉÒÔĞ´¶à¸öcatchÓï¾ä

ÎÒÃÇ»¹¿ÉÒÔÅ×³ö×Ô¼ºµÄÒì³£:
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


ÁíÍâ,ÎÒÃÇÒ²¿ÉÒÔ×Ô¶¨ÒåÒì³£:
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
Èç¹ûÊÇexcep.division(5,-1);
ÄÇÃ´
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
		finally//ÎŞÂÛÒì³£²úÉúÓë·ñ,ÕâÀïµÄÓï¾ä¶¼ÒªÖ´ĞĞ
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

ÕâÀï¾ÍËµÃ÷ÎŞÂÛÒì³£²úÉúÓë·ñ,finallyÓï¾ä¶¼ÒªÖ´ĞĞ,¼´Ê¹ÊÇÔÚtry»òcatchÖĞÓĞreturnÓï¾ä.
µ«ÊÇÓĞÒ»¸öÖÕÖ¹³ÌĞòµÄ·½·¨ System.exit ¿ÉÒÔ²»ÈÃfinallyÓï¾äÖ´ĞĞ.



Èç¹û¸¸ÀàÖĞµÄ·½·¨Å×³ö¶à¸öÒì³££¬Ôò×ÓÀàÖĞµÄ¸²¸Ç·½·¨ÒªÃ´Å×³öÏàÍ¬µÄÒì³££¬ÒªÃ´Å×³öÒì³£µÄ×ÓÀà£¬µ«²»ÄÜÅ×³öĞÂµÄÒì³££¨×¢£º¹¹Ôì·½·¨³ıÍâ£©¡£

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
		finally//ÎŞÂÛÒì³£²úÉúÓë·ñ,ÕâÀïµÄÓï¾ä¶¼ÒªÖ´ĞĞ
		{
			System.out.println("Finally");
		}
		System.out.println( "Finish" );
	}
}
E:\zieckey\Lesson4>javac Excep.java
Excep.java:13: ÕÒ²»µ½·ûºÅ
·ûºÅ£º Àà FileNotFoundException
Î»ÖÃ£º Àà ChildExcep
        public int division(int a,int b) throws FileNotFoundException
                                                ^
1 ´íÎó

¹¹Ôì·½·¨³ıÍâ,¿ÉÒÔÅ×³öÆäËûµÄÒì³£.
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
		finally//ÎŞÂÛÒì³£²úÉúÓë·ñ,ÕâÀïµÄÓï¾ä¶¼ÒªÖ´ĞĞ
		{
			System.out.println("Finally");
		}
		System.out.println( "Finish" );
	}
}


ÎªÊ²Ã´ÔÚ×ÓÀàÖĞµÄÅ×³öÒì³£ÒªĞ¡ÓÚµÈÓÚ¸¸ÀàÖĞµÄÒì³£ÄØ£¿
ÕâÊÇÎªÁË½øĞĞÃæÏò¶ÔÏóÉè¼ÆÊ±µÄÀàÅÉÉúºÍ¼Ì³ĞÓÃµÄ£®
¿´ÏÂÃæµÄ´úÂë£º
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
		method1(ce);//ÕâÀïÈç¹û×ÓÀàÔÊĞíÅ×³ö¸¸ÀàÖĞÃ»ÓĞµÄÒì³££¬
					//ÄÇÃ´¼Ì³ĞÀ´µÄ·½·¨¾ÍÃ»ÓĞ¶ÔËùÓĞµÄ´¦ÀíÍê£¬ÕâÑùµÄÀà¼Ì³ĞÊÇ²»°²È«µÄ¡¡
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
		finally//ÎŞÂÛÒì³£²úÉúÓë·ñ,ÕâÀïµÄÓï¾ä¶¼ÒªÖ´ĞĞ
		{
			System.out.println("Finally");
		}
		System.out.println( "Finish" );
	}
}




Java±à³Ì¹æ·¶
1. packageµÄÃüÃû package µÄÃû×ÖÓÉÈ«²¿Ğ¡Ğ´µÄ×ÖÄ¸×é³É£¬ÀıÈç£ºcn.mybole¡£
2. classºÍinterfaceµÄÃüÃû classºÍinterfaceµÄÃû×ÖÓÉ´óĞ´×ÖÄ¸¿ªÍ·¶øÆäËû×ÖÄ¸¶¼Ğ¡Ğ´µÄµ¥´Ê×é³É£¬ÀıÈç£ºPerson£¬RuntimeException¡£
3. class±äÁ¿µÄÃüÃû ±äÁ¿µÄÃû×ÖÓÃÒ»¸öĞ¡Ğ´×ÖÄ¸¿ªÍ·£¬ºóÃæµÄµ¥´ÊÓÃ´óĞ´×ÖÄ¸¿ªÍ·,ÀıÈç£ºindex£¬currentImage¡£
4. class·½·¨µÄÃüÃû
   ·½·¨µÄÃû×ÖÓÃÒ»¸öĞ¡Ğ´×ÖÄ¸¿ªÍ·£¬ºóÃæµÄµ¥´ÊÓÃ´óĞ´×ÖÄ¸¿ªÍ·,ÀıÈç£ºrun()£¬getBalance()¡£
5. static final±äÁ¿µÄÃüÃû static final±äÁ¿µÄÃû×ÖËùÓĞ×ÖÄ¸¶¼´óĞ´£¬²¢ÇÒÄÜ±íÊ¾ÍêÕûº¬Òå¡£ÀıÈç£ºPI£¬PASSWORD¡£
6. ²ÎÊıµÄÃüÃû ²ÎÊıµÄÃû×ÖºÍ±äÁ¿µÄÃüÃû¹æ·¶Ò»ÖÂ¡£
7. Êı×éµÄÃüÃû Êı×éÓ¦¸Ã×ÜÊÇÓÃÕâÑùµÄ·½Ê½À´ÃüÃû£ºbyte[] buffer¡£



Lesson4ÉÏ
JavaµÄ³£ÓÃ°ü£º
java.applet£º°üº¬Ò»Ğ©ÓÃÓÚ´´½¨JavaĞ¡Ó¦ÓÃ³ÌĞòµÄÀà¡£
java.awt£º°üº¬Ò»Ğ©ÓÃÓÚ±àĞ´ÓëÆ½Ì¨ÎŞ¹ØµÄÍ¼ĞÎ½çÃæ(GUI)Ó¦ÓÃ³ÌĞòµÄÀà¡£
java.io£º°üº¬Ò»Ğ©ÓÃ×÷ÊäÈëÊä³ö(I/O)´¦ÀíµÄÀà¡£
java.lang£º°üº¬Ò»Ğ©JavaÓïÑÔµÄ»ù±¾ÀàÓëºËĞÄÀà£¬ÈçString¡¢Math¡¢Integer¡¢SystemºÍRuntime£¬Ìá¹©³£ÓÃµÄ¹¦ÄÜ£¬Õâ¸ö°üÖĞµÄËùÓĞÀàÊÇ±»ÒşÊ½µ¼ÈëµÄ¡£
java.net£º°üº¬ÓÃÓÚ½¨Á¢ÍøÂçÁ¬½ÓµÄÀà£¬Óëjava.ioÍ¬Ê±Ê¹ÓÃÍê³ÉÓëÍøÂçÓĞ¹ØµÄ¶ÁĞ´¡£
java.util£º°üº¬Ò»Ğ©ÊµÓÃ¹¤¾ßÀàºÍÊı¾İ½á¹¹Àà¡£


¡°==¡±ºÍ¡°equals¡±µÄÓÃ·¨
ÔÚJavaÖĞ£¬boolean¡¢byte¡¢short¡¢int¡¢long¡¢char¡¢float¡¢doubleÕâ°ËÖÖÊÇ»ù±¾Êı¾İÀàĞÍ£¬ÆäÓàµÄ¶¼ÊÇÒıÓÃÀàĞÍ¡£
¡°==¡±ÊÇ±È½ÏÁ½¸ö±äÁ¿µÄÖµÊÇ·ñÏàµÈ£¬¡°equals¡±ÊÇ±È½ÏÁ½¸ö¶ÔÏó±äÁ¿Ëù´ú±íµÄ¶ÔÏóµÄÄÚÈİÊÇ·ñÏàµÈ¡£


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

×Ö·û´®µÄ¡°+¡±¡°+=¡±ÖØÔØ²Ù×÷·û
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

StringºÍStringBuffer
	String str=¡°abc¡±;
    int i=3;
    float f=4.5f;
    char ch='a';
    boolean b=true;
    System.out.println(str + i + f + ch + b);

    StringÀà¶ÔÏóÒ»¸ö³£Á¿¶ÔÏó¡£
    String str=¡°abc¡±;
    str=¡°def¡±;
ÔÚ´¦Àí´óÁ¿×Ö·û´®µÄ³ÌĞòÖĞ£¬ÎÒÃÇÍ¨³£ÓÃStringBufferÀ´Ìæ´úString¡£
Õë¶ÔStringµÄ¡°+¡±ºÍ¡°+=¡±£¬ÊÇJavaÖĞÎ¨Ò»±»ÖØÔØµÄ²Ù×÷·û£»ÔÚJavaÖĞ£¬²»ÔÊĞí³ÌĞòÔ±ÖØÔØ²Ù×÷·û¡£


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


Êı×é£º
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
		num=null;//ÈÃ¸Ã¶ÔÏó³ÉÎªÀ¬»øÄÚ´æ£¬Ö®ºójavaĞéÄâ»ú¾Í»áÔÚĞèÒªµÄÊ±ºò»ØÊÕÕâ¿éÄÚ´æ
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
		students=new Student[3];//´Ë´¦½ö½ö¶¨ÒåÁËÈı¸öStudent¶ÔÏóµÄÓ¦ÓÃ£¬µ«»¹Ã»ÓĞ·ÖÅäÄÚ´æ¿Õ¼ä
		System.out.println( students );
		for(int i=0;i<students.length;i++)
		{
			System.out.println(students[i]);
		}
		students[0] = new Student( "LiSi", 19 );//´Ë´¦²Å¿ªÊ¼·ÖÅäÄÚ´æ¿Õ¼ä
		students[1] = new Student( "ZhangSan", 21 );//students¶ÔÏóµÄÒıÓÃÔÚÕ»ÄÚ´æ,
		students[2] = new Student( "WangMazi", 20 );//students[i]µÄÒıÓÃÔÚ¶ÑÄÚ´æ,
													//students[i]µÄ¾ßÌåÖµÒ²ÔÚ¶ÑÄÚ´æ,
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

´òÓ¡ÃüÁîĞĞ²ÎÊı:
		if(args.length>0)
		{
			for(int i=0;i<args.length;i++)
			{
				System.out.println(args[i]);
			}
		}

º¯ÊıµÄµ÷ÓÃ:
ÔÚJavaÖĞ£¬´«²ÎÊ±£¬¶¼ÊÇÒÔ´«ÖµµÄ·½Ê½½øĞĞ¡£
¶ÔÓÚ»ù±¾Êı¾İÀàĞÍ£¬´«µİµÄÊÇÊı¾İµÄ¿½±´£»¶ÔÓÚÒıÓÃÀàĞÍ£¬´«µİµÄÒıÓÃµÄ¿½±´¡£
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
		System.out.println("change(int x,int y)"+"x="+x+","+"y="+y);//ÕâÀï²»»á½»»»
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


ÔÚ´òÓ¡Ò»¸öÀà¶ÔÏóµÄÊ±ºò,ÀıÈç:
	class Point{int x, y;}
	Point pt=new Point();
	System.out.println(pt);//ÕâÀï´òÓ¡µÄºÜ¿ÉÄÜÊÇ£º¡°Point@9cab16¡±Ö®ÀàµÄĞÅÏ¢

ÕâÑù»á×Ô¶¯µ÷ÓÃObject:toString()·½·¨,È¥´òÓ¡Ò»¸öÀà¶ÔÏóµÄÏà¹ØĞÅÏ¢,
µ±ÎÒÃÇÖØÔØObject:toString()¸Ã·½·¨µÄÊ±ºò£¬¾Í¿ÉÒÔ´òÓ¡ÎÒÃÇ×Ô¼º¶¨ÒåµÄĞÅÏ¢£¬ÀıÈç£º
	class Point
	{
		int x, y;
		public String toString()
		{
			return "x="+x+","+"y="+y;
		}
	}
	Point pt=new Point();
	System.out.println(pt);//ÕâÀï´òÓ¡µÄºÜ¿ÉÄÜÊÇ£º¡°x=3,y=6¡±Ö®ÀàµÄĞÅÏ¢ÁË


¶ÔÏóµÄ¿ËÂ¡(clone)
ÎªÁË»ñÈ¡¶ÔÏóµÄÒ»·İ¿½±´£¬ÎÒÃÇ¿ÉÒÔÀûÓÃObjectÀàµÄclone()·½·¨¡£
ÔÚÅÉÉúÀàÖĞ¸²¸Ç»ùÀàµÄclone()·½·¨£¬²¢ÉùÃ÷Îªpublic¡£
ÔÚÅÉÉúÀàµÄclone()·½·¨ÖĞ£¬µ÷ÓÃsuper.clone()¡£
ÔÚÅÉÉúÀàÖĞÊµÏÖCloneable½Ó¿Ú¡£

ÎªÊ²Ã´ÎÒÃÇÔÚÅÉÉúÀàÖĞ¸²¸ÇObjectµÄclone()·½·¨Ê±£¬Ò»¶¨Òªµ÷ÓÃsuper.clone()ÄØ£¿
ÔÚÔËĞĞÊ±¿Ì£¬ObjectÖĞµÄclone()Ê¶±ğ³öÄãÒª¸´ÖÆµÄÊÇÄÄÒ»¸ö¶ÔÏó£¬
È»ºóÎª´Ë¶ÔÏó·ÖÅä¿Õ¼ä£¬²¢½øĞĞ¶ÔÏóµÄ¸´ÖÆ£¬½«Ô­Ê¼¶ÔÏóµÄÄÚÈİÒ»Ò»¸´ÖÆµ½ĞÂ¶ÔÏóµÄ´æ´¢¿Õ¼äÖĞ¡£

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
Õâ¾ÍËµÃ÷ÁËÃ»ÓĞ¸Ä±äÔ­À´µÄ¶ÔÏóµÄÖµ



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
±àÒëÔËĞĞºó£ºname=lisi,age=30
ÕâÀï¾ÍËµÃ÷ÁË¶Ôs2µÄĞŞ¸ÄÓ°Ïìµ½ÁËs1ÖĞProfessor¶ÔÏópµÄÖµ£¬
ÕâÊÇÎªÊ²Ã´ÄØ£¿
ÎÒÃÇÏëÏë£¬clone·½·¨ÊÇ¶ÔÀàÖĞËùÓĞ±äÁ¿Öµ½øĞĞÁËÒ»´Î¿½±´£¬
Ç°ÃæÎÒÃÇµÄÄêÁäage±äÁ¿ÊÇ»ù±¾ÀàĞÍ±äÁ¿£¬ËùÒÔ¿½±´µÄÊÇÊı¾İ£¬
¶øÎÒÃÇµÄProfessor±äÁ¿pÊÇÒıÓÃÀàĞÍ£¬ËùÒÔ¿½±´µÄÊÇÒıÓÃ£¬¶øÊı¾İÃ»ÓĞ¿½±´£¬
ËùÒÔÎÒÃÇĞŞ¸ÄµÄÊ±ºò£¬½«ProfessorÀà¶ÔÏópµÄÖµÒ²ĞŞ¸ÄÁË¡£
µ«ÊÇÎÒÃÇÓÖÏëµ½£¬ÎªÊ²Ã´StringµÄ¶ÔÏónameÒ²ÊÇÒıÓÃ£¬ÎªÊ²Ã´Ã»ÓĞ±»ĞŞ¸ÄÄØ£¿
ÊÇ²»ÊÇStringÒ²ÖØÔØÁËclone·½·¨ÄØ£¿
Ã»ÓĞ£¬¿ÉÒÔÈ¥¿´¿´StringÀàµÄ°ïÖúÎÄµµ¡£
ÕâÀïÊÇÒòÎª£¬Ò»¸öString¶ÔÏóÊÇÒ»¸ö³£Á¿¶ÔÏó£¬
String str = ¡°Zhangsan¡±£»Õâ¸öÓï¾äÏàµ±ÓÚÏÈÉùÃûÁËÒ»¸öZhangsanµÄ¶ÔÏó£¬
È»ºó½«ÆäÒıÓÃ¸³Öµ¸østr£¬ËùÒÔÔÚcloneµÄÊ±ºò¾ÍÃ»ÓĞÓ°Ïìµ½Ô­À´µÄ±äÁ¿¡£

ÄÇÃ´ÎÒÃÇÈçºÎ½«ProfessorÀàÍ¬ÑîµÄ¸´ÖÆÒ»·İÄØ£¿


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
±àÒëÔËĞĞºó£ºname=wangwu,age=50

ÎªÊ²Ã´ÎÒÃÇÔÚÅÉÉúÀàÖĞ¸²¸ÇObjectµÄclone()·½·¨Ê±£¬Ò»¶¨Òªµ÷ÓÃsuper.clone()ÄØ£¿
ÔÚÔËĞĞÊ±¿Ì£¬ObjectÖĞµÄclone()Ê¶±ğ³öÄãÒª¸´ÖÆµÄÊÇÄÄÒ»¸ö¶ÔÏó£¬
È»ºóÎª´Ë¶ÔÏó·ÖÅä¿Õ¼ä£¬²¢½øĞĞ¶ÔÏóµÄ¸´ÖÆ£¬½«Ô­Ê¼¶ÔÏóµÄÄÚÈİÒ»Ò»¸´ÖÆµ½ĞÂ¶ÔÏóµÄ´æ´¢¿Õ¼äÖĞ¡£


Lesson6

Êı×é¶Ô¹Ø·½·¨£º

Êı×éµÄ¿½±´£ºSystem.arraycopy
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

ÏÂÃæ¶ÔÏóÊı×éµÄ¸´ÖÆ£º
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
		System.out.println("x="+pts1[1].x+","+"y="+pts1[1].y);//ÕâÀï¿½±´µÄÊÇ¶ÔÏóµÄÒıÓÃ
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
ÔËĞĞ½á¹û£º
x=1,y=1
x=2,y=2
x=3,y=3
x=5,y=5
´Ó½á¹û¾Í¿ÉÒÔ¿´³ö¶ÔÀàÊı×éµÄ¿½±´Ê±ÊÇ¿½±´µÄ¶ÔÏóµÄÒıÓÃ£¬
¿½±´ºó£¬¶Ô¿½±´µÄ¶ÔÏó½øĞĞ²Ù×÷»á·´Ó³µ½Ô­¶ÔÏóÉÏ¡£

Êı×éµÄÅÅĞò£º
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
ÔËĞĞ½á¹û
1
2
3
index=2
element=3


µ«ÊÇÒª¶ÔÒ»¸ö¶ÔÏóÊı×é½øĞĞÅÅĞò£¬¾ÍÒªÊµÏÖÒ»¸ö compareTo½Ó¿Ú
ÀıÈç£º
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
ÔËĞĞ½á¹û£º
number=2,name=lisi
number=3,name=zhangsan
number=4,name=mybole
number=4,name=wangwu

Í¬ÑùÎÒÃÇÒ²¿ÉÒÔÍ¨¹ıArrays.binarySearchËÑË÷¶ÔÏóÊı×éÖĞÊı¾İ
		int index=Arrays.binarySearch(ss,new Student(2,"lisi"));
		System.out.println("index="+index);
		System.out.println(ss[index]);




Õë¶Ô°ËÖÖ»ù±¾Êı¾İÀàĞÍ¶¨ÒåµÄÏàÓ¦µÄÒıÓÃÀàĞÍ£­·â×°Àà¡£
»ù±¾Êı¾İÀàĞÍ	·â×°Àà
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




ÀàClass
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
//ÎÒÃÇ¿´¿´±àÒë½á¹û
E:\zieckey\Lesson6>javac ClassTest.java

E:\zieckey\Lesson6>java ClassTest
Before new point
Loading Point....
After new point
Loading Line....
Line
¿É¿ÉÒÔ¿´µ½Ö»ÓĞÔÚÀà±»µ÷ÓÃµÄÊ±ºò£¬²ÅÖ´ĞĞstaticÖĞµÄ´úÂë¶Î

ClassÀà
ÔÚÔËĞĞÆÚ¼ä£¬Èç¹ûÎÒÃÇÒª²úÉúÄ³¸öÀàµÄ¶ÔÏó£¬JavaĞéÄâ»ú(JVM)»á¼ì²é¸ÃÀàĞÍµÄClass¶ÔÏóÊÇ·ñÒÑ±»¼ÓÔØ¡£Èç¹ûÃ»ÓĞ±»¼ÓÔØ£¬JVM»á¸ù¾İÀàµÄÃû³ÆÕÒµ½.classÎÄ¼ş²¢¼ÓÔØËü¡£Ò»µ©Ä³¸öÀàĞÍµÄClass¶ÔÏóÒÑ±»¼ÓÔØµ½ÄÚ´æ£¬¾Í¿ÉÒÔÓÃËüÀ´²úÉú¸ÃÀàĞÍµÄËùÓĞ¶ÔÏó¡£
newInstance() µ÷ÓÃÀàÖĞÈ±Ê¡µÄ¹¹Ôì·½·¨¡£
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
			Point pt=(Point)c.newInstance();//´´½¨Ò»¸öc´ú±íµÄÀàµÄÊµÀı
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
			Point pt=(Point)c.newInstance();//´´½¨Ò»¸öc´ú±íµÄÀàµÄÊµÀı
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
ÕâÀïÊÇÒòÎª£¬newInstanceµ÷ÓÃµÄÊÇÀàµÄÈ±Ê¡¹¹Ôìº¯Êı£¬
µ«ÊÇÎÒÃÇµÄPointÀàÒÑ¾­Ìá¹©ÁË¹¹Ôìº¯Êı£¬ÈçÊÇÔÚµ÷ÓÃµÄÊ±ºò¾Í³ö´íÁË¡£
ÄÇÃ´ÎÒÃÇÈçºÎ½â¾öÄØ£¿
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
			Constructor[] cons=c.getDeclaredConstructors();//µÃµ½¹¹Ôìº¯ÊıÊı×é
			for(int i=0;i<cons.length;i++)
			{
				System.out.println(cons[i]);
			}
			Method[] ms=c.getDeclaredMethods();//µÃµ½ÀàµÄ·½·¨Êı×é
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
ClassTest.java:13: ÕÒ²»µ½·ûºÅ
·ûºÅ£º Àà Constructor
Î»ÖÃ£º Àà ClassTest
                        Constructor[] cons=c.getDeclaredConstructors();//µÃµ½¹¹
Ôìº¯ÊıÊı×é
                        ^
ClassTest.java:18: ÕÒ²»µ½·ûºÅ
·ûºÅ£º Àà Method
Î»ÖÃ£º Àà ClassTest
                        Method[] ms=c.getDeclaredMethods();//µÃµ½ÀàµÄ·½·¨Êı×é
                        ^
2 ´íÎó

getDeclaredConstructors()ÊÇÔÚjava.lang.reflect°üÖĞ¶¨ÒåµÄ£¬ËùÒÔÒªµ¼Èë¸Ã°ü£º


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
			Constructor[] cons=c.getDeclaredConstructors();//µÃµ½¹¹Ôìº¯ÊıÊı×é
			for(int i=0;i<cons.length;i++)
			{
				System.out.println(cons[i]);
			}
			Method[] ms=c.getDeclaredMethods();//µÃµ½ÀàµÄ·½·¨Êı×é
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

ÏÂÃæ¿´¿´ÔõÃ´¶¯Ì¬µ÷ÓÃÒ»¸ö²»ÖªÃûµÄÀà¶ÔÏóµÄ³ÉÔ±·½·¨,Í¨¹ı·´ÉäÀ´ÊµÏÖ
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
			Constructor[] cons=c.getDeclaredConstructors();//µÃµ½¹¹Ôìº¯ÊıÊı×é
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


RuntimeÀàºÍProcessÀà
Ã¿Ò»¸öJava³ÌĞò¶¼ÓĞÒ»¸öRuntimeÀàµÄµ¥Ò»ÊµÀı£¬
Õâ¸öÊµÀı¿ÉÒÔµÃµ½ÔËĞĞ¸Ã³ÌĞòµÄ»·¾³µÄÒ»Ğ©»·¾³ĞÅÏ¢£¬ÀıÈçÄÚ´æÊ¹ÓÃÁ¿µÈµÈ£¬
ËüÌá¹©ÁËÓ¦ÓÃ³ÌĞòºÍ»·¾³Ö®¼äµÄ½Ó¿Ú¡£
Í¨¹ıRuntime.getRuntime()»ñÈ¡RuntimeÀàµÄÊµÀı¡£
RuntimeÀàÊÇÊ¹ÓÃµ¥ÀıÄ£Ê½µÄÒ»¸öÀı×Ó¡£


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

Õâ¸öRuntimeÀà»¹¿ÉÒÔÖ´ĞĞÒ»¸öÍâ²¿µÄ³ÌĞò£¬ÀıÈç£º
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
Õâ¸öÊ±ºò£¬¼ÇÊÂ±¾³ÌĞòÒÑ¾­ÔËĞĞÆğÀ´ÁË

//RuntimeTest.java
import java.io.*;
class RuntimeTest
{
	public static void main(String[] args)
	{

		try
		{
			Runtime rt1=Runtime.getRuntime();
			rt1.exec("javac Test.java");	//±àÒë
			Runtime rt2=Runtime.getRuntime();
			Process p = rt2.exec("java Test");	//ÔËĞĞ£¬
			InputStream is=p.getInputStream();//»ñÈ¡µ½ÔËĞĞ"java Test"³ÌĞòµÄÊä³öÊı¾İ
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

¿ÉÒÔ¿´µ½ÎÒÃÇ»¹¿ÉÒÔÔÚ´Ë±àÒë³ÌĞò£¬È»ºóÔËĞĞ³ÌĞò£¬²¢½«´òÓ¡ĞÅÏ¢´òÓ¡³öÀ´¡£
ÕßºÍµ¥¶ÀÔËĞĞTest.java³ÌĞòÒ»Ñù


Éè¼ÆÄ£Ê½
ÔÚÎÒÃÇ½øĞĞ³ÌĞòÉè¼ÆÊ±£¬Öğ½¥ĞÎ³ÉÁËÒ»Ğ©µäĞÍÎÊÌâºÍÎÊÌâµÄ½â¾ö·½°¸£¬Õâ¾ÍÊÇÈí¼şÄ£Ê½¡£
Ã¿Ò»¸öÄ£Ê½ÃèÊöÁËÒ»¸öÔÚÎÒÃÇ³ÌĞòÉè¼ÆÖĞ¾­³£·¢ÉúµÄÎÊÌâ£¬ÒÔ¼°¸ÃÎÊÌâµÄ½â¾ö·½°¸¡£
µ±ÎÒÃÇÅöµ½Ä£Ê½ËùÃèÊöµÄÎÊÌâ£¬¾Í¿ÉÒÔÖ±½ÓÓÃÏàÓ¦µÄ½â¾ö·½·¨È¥½â¾öÕâ¸öÎÊÌâ£¬Õâ¾ÍÊÇÉè¼ÆÄ£Ê½¡£

µ¥Àı£¨Singleton£©Ä£Ê½
   £¨1£©Ò»¸öÀàÖ»ÓĞÒ»¸öÊµÀı£¬¶øÇÒ×ÔĞĞÊµÀı»¯²¢ÏòÕû¸öÏµÍ³Ìá¹©Õâ¸öÊµÀı£¬Õâ¸öÀà³ÆÎªµ¥ÀıÀà¡£
   £¨2£©µ¥ÀıÀàµÄÒ»¸ö×îÖØÒªµÄÌØµãÊÇÀàµÄ¹¹Ôì·½·¨ÊÇË½ÓĞµÄ£¬´Ó¶ø±ÜÃâÁËÍâ²¿ÀûÓÃ¹¹Ôì·½·¨Ö±½Ó´´½¨¶à¸öÊµÀı¡£
class Singleton
{
	private static final Singleton st=new Singleton();
	private Singleton(){}
	public static Singleton getInstance()
	{
		return st;
	}
}

Éè¼ÆÄ£Ê½²Î¿¼Êé¼®£º
¡¶ JavaÓëÄ£Ê½¡·
  ×÷Õß£ºÑÖºê
  µç×Ó¹¤Òµ³ö°æÉç³ö°æ


Lesson7
¶àÏß³Ì

³ÌĞò¡¢½ø³ÌºÍÏß³Ì
	³ÌĞòÊÇ¼ÆËã»úÖ¸ÁîµÄ¼¯ºÏ£¬ËüÒÔÎÄ¼şµÄĞÎÊ½´æ´¢ÔÚ´ÅÅÌÉÏ¡£
	½ø³Ì£ºÊÇÒ»¸ö³ÌĞòÔÚÆä×ÔÉíµÄµØÖ·¿Õ¼äÖĞµÄÒ»´ÎÖ´ĞĞ»î¶¯¡£
	½ø³ÌÊÇ×ÊÔ´ÉêÇë¡¢µ÷¶ÈºÍ¶ÀÁ¢ÔËĞĞµÄµ¥Î»£¬Òò´Ë£¬ËüÊ¹ÓÃÏµÍ³ÖĞµÄÔËĞĞ×ÊÔ´£»
¶ø³ÌĞò²»ÄÜÉêÇëÏµÍ³×ÊÔ´£¬²»ÄÜ±»ÏµÍ³µ÷¶È£¬Ò²²»ÄÜ×÷Îª¶ÀÁ¢ÔËĞĞµÄµ¥Î»£¬
Òò´Ë£¬Ëü²»Õ¼ÓÃÏµÍ³µÄÔËĞĞ×ÊÔ´¡£
	Ïß³Ì£ºÊÇ½ø³ÌÖĞµÄÒ»¸öµ¥Ò»µÄÁ¬Ğø¿ØÖÆÁ÷³Ì¡£Ò»¸ö½ø³Ì¿ÉÒÔÓµÓĞ¶à¸öÏß³Ì¡£
Ïß³ÌÓÖ³ÆÎªÇáÁ¿¼¶½ø³Ì£¬ËüºÍ½ø³ÌÒ»ÑùÓµÓĞ¶ÀÁ¢µÄÖ´ĞĞ¿ØÖÆ£¬
ÓÉ²Ù×÷ÏµÍ³¸ºÔğµ÷¶È£¬Çø±ğÔÚÓÚÏß³ÌÃ»ÓĞ¶ÀÁ¢µÄ´æ´¢¿Õ¼ä£¬
¶øÊÇºÍËùÊô½ø³ÌÖĞµÄÆäËüÏß³Ì¹²ÏíÒ»¸ö´æ´¢¿Õ¼ä£¬ÕâÊ¹µÃÏß³Ì¼äµÄÍ¨ĞÅÔ¶½Ï½ø³Ì¼òµ¥¡£

Java¶Ô¶àÏß³ÌµÄÖ§³Ö
JavaÔÚÓïÑÔ¼¶Ìá¹©ÁË¶Ô¶àÏß³Ì³ÌĞòÉè¼ÆµÄÖ§³Ö¡£
ÊµÏÖ¶àÏß³Ì³ÌĞòµÄÁ½ÖÖ·½Ê½£º
    £¨1£©´ÓThreadÀà¼Ì³Ğ£»
    £¨2£©ÊµÏÖRunnable½Ó¿Ú¡£
JavaÔËĞĞÊ±ÏµÍ³ÊµÏÖÁËÒ»¸öÓÃÓÚµ÷¶ÈÏß³ÌÖ´ĞĞµÄÏß³Ìµ÷¶ÈÆ÷£¬ÓÃÓÚÈ·¶¨Ä³Ò»Ê±¿ÌÓÉÄÄÒ»¸öÏß³ÌÔÚCPUÉÏÔËĞĞ¡£
ÔÚjava¼¼ÊõÖĞ£¬Ïß³ÌÍ¨³£ÊÇÇÀÕ¼Ê½µÄ¶ø²»ĞèÒªÊ±¼äÆ¬·ÖÅä½ø³Ì£¨·ÖÅä¸øÃ¿¸öÏß³ÌÏàµÈµÄCPUÊ±¼äµÄ½ø³Ì£©¡£ÇÀÕ¼Ê½µ÷¶ÈÄ£ĞÍ¾ÍÊÇĞí¶àÏß³Ì´¦ÓÚ¿ÉÒÔÔËĞĞ×´Ì¬£¨µÈ´ı×´Ì¬£©£¬µ«Êµ¼ÊÉÏÖ»ÓĞÒ»¸öÏß³ÌÔÚÔËĞĞ¡£¸ÃÏß³ÌÒ»Ö±ÔËĞĞµ½ËüÖÕÖ¹½øÈë¿ÉÔËĞĞ×´Ì¬£¨µÈ´ı×´Ì¬£©£¬»òÕßÁíÒ»¸ö¾ßÓĞ¸ü¸ßÓÅÏÈ¼¶µÄÏß³Ì±ä³É¿ÉÔËĞĞ×´Ì¬¡£ÔÚºóÒ»ÖÖÇé¿öÏÂ£¬µÍÓÅÏÈ¼¶µÄÏß³Ì±»¸ßÓÅÏÈ¼¶µÄÏß³ÌÇÀÕ¼£¬¸ßÓÅÏÈ¼¶µÄÏß³Ì»ñµÃÔËĞĞµÄ»ú»á¡£
JavaÏß³Ìµ÷¶ÈÆ÷Ö§³Ö²»Í¬ÓÅÏÈ¼¶Ïß³ÌµÄÇÀÏÈ·½Ê½£¬µ«Æä±¾Éí²»Ö§³ÖÏàÍ¬ÓÅÏÈ¼¶Ïß³ÌµÄÊ±¼äÆ¬ÂÖ»»¡£
JavaÔËĞĞÊ±ÏµÍ³ËùÔÚµÄ²Ù×÷ÏµÍ³£¨ÀıÈç£ºWindows2000£©Ö§³ÖÊ±¼äÆ¬µÄÂÖ»»£¬ÔòÏß³Ìµ÷¶ÈÆ÷¾ÍÖ§³ÖÏàÍ¬ÓÅÏÈ¼¶Ïß³ÌµÄÊ±¼äÆ¬ÂÖ»»¡£
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
		MyThread mt=new MyThread();//´´½¨Ò»¸öÏß³Ì
		mt.start();//ÈÃÏß³Ì¿ªÊ¼ÔËĞĞ
		System.out.println("main:"+Thread.currentThread().getName());
	}
}

class MyThread extends Thread//¶¨ÒåÒ»¸öÏß³Ì
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

Thread-0Õâ¸öÊÇjvm¸øÎÒÃÇ·ÖÅäµÄÒ»¸öÃû×Ö
ÕâÀïÓ¦¸Ã¿´¿´ÊÇÏÈ´òÓ¡main·½·¨µÄÏß³ÌÃû×Ö£¬ºóÃæ²Å´òÓ¡ÎÒÃÇ×Ô¶¨ÒåµÄÏß³Ì¡£

ÎÒÃÇÈÃÏß³ÌÑ­»·À´¿´¿´CPUÔÚÁ½¸öÏß³ÌÖ®¼äµÄÇĞ»»£º
//MutiThread.java
class MutiThread
{
	public static void main( String[]args )
	{
		MyThread mt=new MyThread();//´´½¨Ò»¸öÏß³Ì
		mt.start();//ÈÃÏß³Ì¿ªÊ¼ÔËĞĞ
		while ( true )
		{
			System.out.println("main:"+Thread.currentThread().getName());
		}
	}
}

class MyThread extends Thread//¶¨ÒåÒ»¸öÏß³Ì
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


ÉèÖÃºóÌ¨Ïß³Ì£ºsetDaemon
//MutiThread.java
class MutiThread
{
	public static void main( String[]args )
	{
		MyThread mt=new MyThread();//´´½¨Ò»¸öÏß³Ì
		mt.setDaemon(true);//ÉèÖÃºóÌ¨Ïß³Ì,Õâ¸ö±ØĞëÔÚÏß³ÌÆô¶¯Ö®Ç°¶¨Òå
		mt.start();//ÈÃÏß³Ì¿ªÊ¼ÔËĞĞ
		int i=0;
		while ( true )
		{
			if ( i++ == 5 )
				break;
			System.out.println("main:"+Thread.currentThread().getName());
		}
	}
}

class MyThread extends Thread//¶¨ÒåÒ»¸öÏß³Ì
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
ÕâÀï¾Í¿ÉÒÔ¿´µ±main·½·¨½áÊøºó£¬ºóÌ¨Ïß³ÌÒ²½áÊøÁË¡£

ÁíÍâ¿ÉÒÔÍ¨¹ıyield();·½·¨Ê¹Ïß³Ì·ÅÆúÖ´ĞĞ¶øÈÃÆäËûÏß³ÌÖ´ĞĞ£º
//MutiThread.java
class MutiThread
{
	public static void main( String[]args )
	{
		MyThread mt=new MyThread();//´´½¨Ò»¸öÏß³Ì
		mt.setDaemon(true);//ÉèÖÃºóÌ¨Ïß³Ì,Õâ¸ö±ØĞëÔÚÏß³ÌÆô¶¯Ö®Ç°¶¨Òå
		mt.start();//ÈÃÏß³Ì¿ªÊ¼ÔËĞĞ
		int i=0;
		while ( true )
		{
			if ( i++ == 500 )
				break;
			System.out.println("main:"+Thread.currentThread().getName());
		}
	}
}

class MyThread extends Thread//¶¨ÒåÒ»¸öÏß³Ì
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
ÕâÀï¿´ÒÔ¿´µ½Ã¿µ±MyThreadÖ´ĞĞÒ»´Î£¬Ëü´òÓ¡ÍêÃû×Öºó£¬Ëü¾ÍÍ£Ö¹Ö´ĞĞÁË£¬
È»ºóCPU×ªÏòmainÏß³Ì£¬µ±mainÏß³ÌµÄÊ±¼äÆ¬ÓÃÍêºó£¬ÓĞ»Øµ½MyThread

Ïß³Ì»¹¿ÉÒÔÉèÖÃÓÅÏÈ¼¶£ºsetPriority( int )         getPriority
//MutiThread.java
class MutiThread
{
	public static void main( String[]args )
	{
		MyThread mt=new MyThread();//´´½¨Ò»¸öÏß³Ì
		mt.start();//ÈÃÏß³Ì¿ªÊ¼ÔËĞĞ
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

class MyThread extends Thread//¶¨ÒåÒ»¸öÏß³Ì
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

ÕâÀï¿ÉÒÔ¿´µ½¸ßÓÅÏÈ¼¶µÄ MyThread Ïß³ÌÊ¼ÖÕ»ñµÃCPUµÄÖ´ĞĞ£¬Ö»ÓĞµ±ÎÒÃÇÓÃ»§ÖÕÖ¹µÄÊ±ºò£¬
mainÏß³Ì²Å»ñµÃÒ»»á¶ùCPUÖ´ĞĞ¡£

JavaÔËĞĞÊ±ÏµÍ³ÊµÏÖÁËÒ»¸öÓÃÓÚµ÷¶ÈÏß³ÌÖ´ĞĞµÄÏß³Ìµ÷¶ÈÆ÷£¬
ÓÃÓÚÈ·¶¨Ä³Ò»Ê±¿ÌÓÉÄÄÒ»¸öÏß³ÌÔÚCPUÉÏÔËĞĞ¡£
ÔÚjava¼¼ÊõÖĞ£¬Ïß³ÌÍ¨³£ÊÇÇÀÕ¼Ê½µÄ¶ø²»ĞèÒªÊ±¼äÆ¬·ÖÅä½ø³Ì
£¨·ÖÅä¸øÃ¿¸öÏß³ÌÏàµÈµÄCPUÊ±¼äµÄ½ø³Ì£©¡£
ÇÀÕ¼Ê½µ÷¶ÈÄ£ĞÍ¾ÍÊÇĞí¶àÏß³Ì´¦ÓÚ¿ÉÒÔÔËĞĞ×´Ì¬£¨µÈ´ı×´Ì¬£©£¬
µ«Êµ¼ÊÉÏÖ»ÓĞÒ»¸öÏß³ÌÔÚÔËĞĞ¡£¸ÃÏß³ÌÒ»Ö±ÔËĞĞµ½ËüÖÕÖ¹½øÈë¿ÉÔËĞĞ×´Ì¬£¨µÈ´ı×´Ì¬£©£¬
»òÕßÁíÒ»¸ö¾ßÓĞ¸ü¸ßÓÅÏÈ¼¶µÄÏß³Ì±ä³É¿ÉÔËĞĞ×´Ì¬¡£ÔÚºóÒ»ÖÖÇé¿öÏÂ£¬
µÍÓÅÏÈ¼¶µÄÏß³Ì±»¸ßÓÅÏÈ¼¶µÄÏß³ÌÇÀÕ¼£¬¸ßÓÅÏÈ¼¶µÄÏß³Ì»ñµÃÔËĞĞµÄ»ú»á¡£
JavaÏß³Ìµ÷¶ÈÆ÷Ö§³Ö²»Í¬ÓÅÏÈ¼¶Ïß³ÌµÄÇÀÏÈ·½Ê½£¬
µ«Æä±¾Éí²»Ö§³ÖÏàÍ¬ÓÅÏÈ¼¶Ïß³ÌµÄÊ±¼äÆ¬ÂÖ»»¡£
JavaÔËĞĞÊ±ÏµÍ³ËùÔÚµÄ²Ù×÷ÏµÍ³£¨ÀıÈç£ºWindows2000£©Ö§³ÖÊ±¼äÆ¬µÄÂÖ»»£¬
ÔòÏß³Ìµ÷¶ÈÆ÷¾ÍÖ§³ÖÏàÍ¬ÓÅÏÈ¼¶Ïß³ÌµÄÊ±¼äÆ¬ÂÖ»»¡£

ÉÏÃæÊÇÍ¨¹ı¼Ì³ĞThreadÀàÀ´´´½¨Ïß³Ì£¬
ÏÂÃæÎÒÃÇ¿´¿´ÈçºÎÍ¨¹ıÊµÏÖRunnable½Ó¿ÚÀ´´´½¨Ïß³Ì¡£
//MutiThread.java
class MutiThread
{
	public static void main( String[]args )
	{
		MyThread mt=new MyThread();//´´½¨Ò»¸öÏß³Ì
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

class MyThread implements Runnable//extends Thread//¶¨ÒåÒ»¸öÏß³Ì
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

ÊµÏÖRunnable½Ó¿ÚÀ´´´½¨Ïß³ÌµÄÓÅµã£º
£¨1£©¿ÉÒÔÍ¬Ê±´ÓÁíÍâµÄÒ»¸öÀà¼Ì³ĞÀ´
£¨2£©¿ÉÒÔºÜ·½±ãµÄÊµÏÖÄÚ´æµÄ¹²Ïí£¬ÀıÈç£º
//MutiThread.java
class MutiThread
{
	public static void main( String[]args )
	{
		MyThread mt=new MyThread();//´´½¨Ò»¸öÏß³Ì
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

class MyThread implements Runnable//extends Thread//¶¨ÒåÒ»¸öÏß³Ì
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

ÉÏÃæËµµÄÁ½ÖÖÓÅµã¶¼¿ÉÒÔÍ¨¹ıÄÚ²¿ÀàÊµÏÖ£º
//MutiThread.java
class MutiThread
{
	public static void main( String[]args )
	{
		MyThread mt=new MyThread();//´´½¨Ò»¸öÏß³Ì
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

class MyThread //implements Runnable//extends Thread//¶¨ÒåÒ»¸öÏß³Ì
{
	int index=0;
	private class InnerThread extends Thread//Õâ¸ö¶¨ÒåÎªprivateÊÇÎªÁËÒş²ØÊµÏÖÏ¸½Ú
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


ÏÂÃæ¿´¿´Ò»¸öÄ£ÄâµÄÊÛÆ±ÏµÍ³
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

µ«ÊÇÕâ¸ö³ÌĞòÓĞµãÎÊÌâ£¬¾ÍÊÇ¿ÉÄÜÊÛ³ö0£¬-1µÈÕâÑùµÄÆ±£¬ÎÒÃÇ¿´¿´£º
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
Õâ¸ö½á¹ûÏÔÈ»ÊÇ²»¶ÔµÄ£¬ÄÇÃ´ÎÒÈçºÎ½â¾öÄØ£¿
Õâ¾ÍÒªÓÃµ½Ïß³ÌµÄÍ¬²½»úÖÆ¡£

Ïß³ÌµÄÍ¬²½
The code segments within a program that access the same object from separate, concurrent threads are called ¡°critical sections¡±¡£
Í¬²½µÄÁ½ÖÖ·½Ê½£ºÍ¬²½¿éºÍÍ¬²½·½·¨
Ã¿Ò»¸ö¶ÔÏó¶¼ÓĞÒ»¸ö¼àÊÓÆ÷£¬»òÕß½Ğ×öËø¡£
Í¬²½·½·¨ÀûÓÃµÄÊÇthisËù´ú±íµÄ¶ÔÏóµÄËø¡£
Ã¿¸öclassÒ²ÓĞÒ»¸öËø£¬ÊÇÕâ¸öclassËù¶ÔÓ¦µÄClass¶ÔÏóµÄËø¡£


Í¬²½¿éµÄ·½·¨£º
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
			//synchronized( obj )//ÕâÀï¾ÍÊÇÍ¬²½¿é
			synchronized( criticalSections )//ÕâÀï¾ÍÊÇÍ¬²½¿é
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
Õâ¾Í²»¿ÉÄÜ³öÏÖÉÏÃæµÄ´íÎóÊÛÆ±ÁË¡£
	synchronized( obj )//ÕâÀï¾ÍÊÇÍ¬²½¿é
Õâ¾ä»°ÊÇ¶Ôobj¶ÔÏó¼ÓËø£¬ÒÔÊµÏÖÍ¬²½¡£

Í¬²½·½·¨µÄÊµÏÖ£º
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
			/*synchronized( obj )//ÕâÀï¾ÍÊÇÍ¬²½¿é
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
	public synchronized void sell() //Í¬²½µÄ·½·¨¾ÍÊÇÔÚ·½·¨Ç°Ãæ¼ÓÉÏĞŞÊÎ·ûsynchronized
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
ÕâÀïµÄÊµ¶Ô this ¶ÔÏó¼ÓËø£¬ÏÂÃæÎÒÃÇ×öÒ»¸ö²âÊÔ£¬¿´¿´Èç¹ûÍ¬²½¿éÒ²¶Ô this ¼ÓËø£¬
ÄÇÃ´Í¬²½¿éºÍÍ¬²½·½·¨ÊÇ·ñÍ¬²½£¿

//TicketsSystem.java
class TicketsSystem
{
	public static void main(String[] args)
	{
		SellThread st=new SellThread();
		new Thread(st).start();
		try
		{
			Thread.sleep(1);//ÕâÀïµÈ´ı1msÊÇÎªÁËÈÃµÚÒ»¸öÏß³ÌÆô¶¯ÆğÀ´£¬
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		st.b = true ;//µÚÒ»¸öÏß³ÌÒÑ¾­Æô¶¯Ö®ºó²ÅÉèÖÃst.b = true
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
				synchronized( obj )//ÕâÀï¾ÍÊÇÍ¬²½¿é
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

ÓÉÓÚÁ½¸öÏß³Ì¼àÊÓµÄ¶ÔÏó²»Ò»Ñù£¬³öÏÖÁËÊÛ³ö 0 ºÅÆ±µÄ´íÎó£¬
ÄÇÃ´ÎÒÃÇ¿´¿´¼àÊÓÍ¬Ò»¶ÔÏóµÄĞ§¹û£º

//TicketsSystem.java
class TicketsSystem
{
	public static void main(String[] args)
	{
		SellThread st=new SellThread();
		new Thread(st).start();
		try
		{
			Thread.sleep(1);//ÕâÀïµÈ´ı1msÊÇÎªÁËÈÃµÚÒ»¸öÏß³ÌÆô¶¯ÆğÀ´£¬
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		st.b = true ;//µÚÒ»¸öÏß³ÌÒÑ¾­Æô¶¯Ö®ºó²ÅÉèÖÃst.b = true
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
				synchronized( this )//ÕâÀï¾ÍÊÇÍ¬²½¿é
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
ÕâÑù¾ÍºÃÁË¡£

Õâ×ãÒÔËµÃ÷Í¨¹ıÍ¬²½·½·¨ÊµÏÖµÄÍ¬²½£¬Ëü¼àÊÓµÄÊÇthis¶ÔÏó£¬
Ã¿Ò»¸ö¶ÔÏó¶¼ÓĞÒ»¸ö¼àÊÓÆ÷£¬»òÕß½Ğ×öËø¡£
Í¬²½·½·¨ÀûÓÃµÄÊÇthisËù´ú±íµÄ¶ÔÏóµÄËø¡£
Ã¿¸öclassÒ²ÓĞÒ»¸öËø£¬ÊÇÕâ¸öclassËù¶ÔÓ¦µÄClass¶ÔÏóµÄËø¡£
ÄÇÃ´¾Í¿ÉÒÔÀûÓÃÕâ¸öClass¶ÔÏóÀ´Í¬²½¾²Ì¬±äÁ¿.

ËÀËø:
Ïß³Ì1Ëø×¡ÁË¶ÔÏóAµÄ¼àÊÓÆ÷£¬µÈ´ı¶ÔÏóBµÄ¼àÊÓÆ÷£¬Ïß³Ì2Ëø×¡ÁË¶ÔÏóBµÄ¼àÊÓÆ÷£¬µÈ´ı¶ÔÏóAµÄ¼àÊÓÆ÷£¬¾ÍÔì³ÉÁËËÀËø¡£
ÎÒÃÇ¿´¿´ÏÂÃæµÄÀı×Ó:

//TicketsSystem.java
class TicketsSystem
{
	public static void main(String[] args)
	{
		SellThread st=new SellThread();
		new Thread(st).start();
		try
		{
			Thread.sleep(1);//ÕâÀïµÈ´ı1msÊÇÎªÁËÈÃµÚÒ»¸öÏß³ÌÆô¶¯ÆğÀ´£¬
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		st.b = true ;//µÚÒ»¸öÏß³ÌÒÑ¾­Æô¶¯Ö®ºó²ÅÉèÖÃst.b = true
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


wait¡¢notify¡¢notifyAll
Ã¿Ò»¸ö¶ÔÏó³ıÁËÓĞÒ»¸öËøÖ®Íâ£¬»¹ÓĞÒ»¸öµÈ´ı¶ÓÁĞ£¨wait set£©£¬µ±Ò»¸ö¶ÔÏó¸Õ´´½¨µÄÊ±ºò£¬ËüµÄ¶Ô´ı¶ÓÁĞÊÇ¿ÕµÄ¡£
ÎÒÃÇÓ¦¸ÃÔÚµ±Ç°Ïß³ÌËø×¡¶ÔÏóµÄËøºó£¬È¥µ÷ÓÃ¸Ã¶ÔÏóµÄwait·½·¨¡£
µ±µ÷ÓÃ¶ÔÏóµÄnotify·½·¨Ê±£¬½«´Ó¸Ã¶ÔÏóµÄµÈ´ı¶ÓÁĞÖĞÉ¾³ıÒ»¸öÈÎÒâÑ¡ÔñµÄÏß³Ì£¬Õâ¸öÏß³Ì½«ÔÙ´Î³ÉÎª¿ÉÔËĞĞµÄÏß³Ì¡£
µ±µ÷ÓÃ¶ÔÏóµÄnotifyAll·½·¨Ê±£¬½«´Ó¸Ã¶ÔÏóµÄµÈ´ı¶ÓÁĞÖĞÉ¾³ıËùÓĞµÈ´ıµÄÏß³Ì£¬ÕâĞ©Ïß³Ì½«³ÉÎª¿ÉÔËĞĞµÄÏß³Ì¡£
waitºÍnotifyÖ÷ÒªÓÃÓÚproducer-consumerÕâÖÖ¹ØÏµÖĞ¡£

¿´¿´ÏÂÃæµÄÀı×Ó:

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
	public synchronized void put(int i)//¶Ôthis¶ÔÏó½øĞĞ¼ÓËøÍ¬²½
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
	public synchronized int get()//¶Ôthis¶ÔÏó½øĞĞ¼ÓËøÍ¬²½
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


Ïß³ÌµÄÖÕÖ¹
²»ÍÆ¼öÓÃstop·½·¨È¥ÖÕÖ¹Ò»¸öÏß³Ì,ÔÚstop·½·¨µ÷ÓÃµÄÊ±ºò»á½«ËùÓĞµÄËø½â¿ª,
Õâ¶ÔÓÚÄ³Ğ©ÁÙ½ç×ÊÔ´À´ËµÊÇÖÂÃüµÄ,ÒòÎª±¾À´Õâ¸öÁÙ½ç×ÊÔ´Ó¦¸Ã±»Ëø×¡,
µ«ÊÇÒ»µ©stop±»Ö´ĞĞ,¾Í½â¿ªÁË£¬ÆäËûÏß³Ì¾Í¿ÉÒÔ·ÃÎÊÁË¡£
Ïß³ÌµÄÖÕÖ¹ÓĞÁ½ÖÖ¿ÉĞĞµÄ·½·¨£º
1.ÉèÖÃÒ»¸öflag±äÁ¿¡£
2.½áºÏinterrupt()·½·¨¡£


1.ÉèÖÃÒ»¸öflag±äÁ¿¡£
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

µ«ÊÇÈç¹ûÎÒÃÇÓĞĞ©wait·½·¨µÄ»°£¬ÄÇÃ´¾Í²»ÈİÒ×ÍË³öÏß³ÌÁË¡£
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
´ÓÕâÀïµÄÔËĞĞ½á¹ûÊÇ¿´²»³öÀ´µÄ£¬
µ«ÊÇÔÚÊµ¼ÊÔËĞĞÖĞ£¬³ÌĞòÍ£ÔÚÁËÄÇÀï£¬Ã»ÓĞÍË³ö£¡
Õâ¸öÊ±ºòÎÒÃÇ¾ÍÒªÓÃµÃinterrupt()·½·¨¡£
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
Õâ¸ö³ÌĞò²¢Ã»ÓĞÏñËïöÎÀÏÊ¦½²¿ÎµÄËµµÄÄÇÑùÍË³ö£¬ËÆºõ²»¶Ô£¿
ºóÃæÔÙÑĞ¾¿¡£¡£¡£¡£¡£


Lesson8
JavaÖĞµÄ¼¯ºÏÀà


¼¯ºÏ¿ò¼ÜÖĞµÄ½Ó¿Ú
Collection£º¼¯ºÏ²ã´ÎÖĞµÄ¸ù½Ó¿Ú£¬JDKÃ»ÓĞÌá¹©Õâ¸ö½Ó¿ÚÖ±½ÓµÄÊµÏÖÀà¡£
Set£º²»ÄÜ°üº¬ÖØ¸´µÄÔªËØ¡£SortedSetÊÇÒ»¸ö°´ÕÕÉıĞòÅÅÁĞÔªËØµÄSet¡£
List£ºÊÇÒ»¸öÓĞĞòµÄ¼¯ºÏ£¬¿ÉÒÔ°üº¬ÖØ¸´µÄÔªËØ¡£Ìá¹©ÁË°´Ë÷Òı·ÃÎÊµÄ·½Ê½¡£
Map£º°üº¬ÁËkey-value¶Ô¡£Map²»ÄÜ°üº¬ÖØ¸´µÄkey¡£SortedMapÊÇÒ»¸ö°´ÕÕÉıĞòÅÅÁĞkeyµÄMap¡£



ArrayList
ArrayList£ºÎÒÃÇ¿ÉÒÔ½«Æä¿´×÷ÊÇÄÜ¹»×Ô¶¯Ôö³¤ÈİÁ¿µÄÊı×é¡£
ÀûÓÃArrayListµÄtoArray()·µ»ØÒ»¸öÊı×é¡£
Arrays.asList()·µ»ØÒ»¸öÁĞ±í¡£
µü´úÆ÷(Iterator) ¸øÎÒÃÇÌá¹©ÁËÒ»ÖÖÍ¨ÓÃµÄ·½Ê½À´·ÃÎÊ¼¯ºÏÖĞµÄÔªËØ¡£


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
ÔËĞĞ½á¹û£º
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
		Object[] obj = al.toArray();//½«Õâ¸öArrayList×ª»»ÎªÊı×é
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
ÔËĞĞ½á¹û£º
[x=2 y=2, x=3 y=3, x=4 y=4]
x=2 y=2
x=3 y=3
x=4 y=4
µ«ÊÇ³öÏÖ¾¯¸æĞÅÏ¢£º
Severity and Description	Path	Resource	Location	Creation Time	Id
Type safety: The method add(Object) belongs to the raw type ArrayList. References to generic type ArrayList<E> should be parameterized	Lesson8	ArrayListTest.java	line 11	1167034673468	236
Type safety: The method add(Object) belongs to the raw type ArrayList. References to generic type ArrayList<E> should be parameterized	Lesson8	ArrayListTest.java	line 12	1167034673468	237
Type safety: The method add(Object) belongs to the raw type ArrayList. References to generic type ArrayList<E> should be parameterized	Lesson8	ArrayListTest.java	line 13	1167034673468	238

TigerµÄ·ºĞÍ¹¦ÄÜÊ¹µÃ±àÒëÆ÷¶ÔÀàĞÍµÄ°²È«ĞÔ½øĞĞ¼ì²é£¬ÌØ±ğÊÇJava¼¯ºÏ£¬ÈçÏÂÃæµÄÀı×Ó£º

public void nonGenericsMethod()
{
	ArrayList al = new ArrayList(); // no typing information on the List
	al.add("zieckey"); // causes error on list addition
}
±àÒëÆ÷»á¸ø³öÏÂÃæµÄ¾¯¸æĞÅÏ¢£º
Type safety: The method add(Object) belongs to the raw type List. References to generic  type List<E> should be parameterized

Õâ¸ö¿ÉÒÔÊ¹ÓÃ@SuppressWarningsÀ´×èÖ¹Ö¸¶¨ÀàĞÍµÄ¾¯¸æĞÅÏ¢£¬Èç£º

@SuppressWarnings(value = { "unchecked" })
public void nonGenericsMethod()
{
	ArrayList al = new ArrayList(); // no typing information on the List
	al.add("zieckey"); // causes error on list addition
}

ÄÇÃ´ÉÏÃæµÄ´úÂë¾Í¿ÉÒÔÍ¨¹ıÕâ·½·¨×èÖ¹ÕâĞ©·³ÈËµÄ¾¯¸æĞÅÏ¢

//ArrayListTest.java

import java.util.*;
class ArrayListTest
{
	@SuppressWarnings(value = { "unchecked" })  //»òÕß @SuppressWarnings("unchecked")
	public static void main(String[] args)
	{

		ArrayList al = new ArrayList();
		al.add( new Point(2,2) );
		al.add( new Point(3,3) );
		al.add( new Point(4,4) );

		System.out.println( al );
		Object[] obj = al.toArray();//½«Õâ¸öArrayList×ª»»ÎªÊı×é
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
ÕâÑù¾Í¿ÉÒÔ±àÒë²»³öÏÖ´íÎó¡£

Èç¹û²»¼Ó @SuppressWarnings(value = { "unchecked" })  ÕâĞĞ´úÂëµÄ»°£¬
ÔÚÃüÁîĞĞÏÂ±àÒëÊÇÕâ¸öÏÖÏó£º

E:\JavaLesson\Lesson8>javac ArrayListTest.java
×¢Òâ£ºArrayListTest.java Ê¹ÓÃÁËÎ´¾­¼ì²é»ò²»°²È«µÄ²Ù×÷¡£
×¢Òâ£ºÒªÁË½âÏêÏ¸ĞÅÏ¢£¬ÇëÊ¹ÓÃ -Xlint:unchecked ÖØĞÂ±àÒë¡£

ÄÇÃ´¿ÉÒÔÍ¨¹ı¼ÓÉÏ -Xlint:unchecked ÖØĞÂ±àÒë¡£

µ«ÊÇÕâÑù»¹ÊÇ»á³öÏÖ¾¯¸æ£¬
E:\JavaLesson\Lesson8>javac ArrayListTest.java -Xlint:unchecked
ArrayListTest.java:11: ¾¯¸æ£º[unchecked] ¶Ô×÷ÎªÆÕÍ¨ÀàĞÍ java.util.ArrayList µÄ³É
Ô±µÄ add(E) µÄµ÷ÓÃÎ´¾­¼ì²é
                al.add( new Point(2,2) );
                      ^
ArrayListTest.java:12: ¾¯¸æ£º[unchecked] ¶Ô×÷ÎªÆÕÍ¨ÀàĞÍ java.util.ArrayList µÄ³É
Ô±µÄ add(E) µÄµ÷ÓÃÎ´¾­¼ì²é
                al.add( new Point(3,3) );
                      ^
ArrayListTest.java:13: ¾¯¸æ£º[unchecked] ¶Ô×÷ÎªÆÕÍ¨ÀàĞÍ java.util.ArrayList µÄ³É
Ô±µÄ add(E) µÄµ÷ÓÃÎ´¾­¼ì²é
                al.add( new Point(4,4) );
                      ^
3 ¾¯¸æ

ËùÒÔ»¹ÊÇ¼ÓÉÏÄÇ¾ä»°ÎªºÃ¡£


Í¨¹ıArrays.asList()·µ»ØÒ»¸öÁĞ±í£º
//ArrayListTest.java

import java.util.*;
class ArrayListTest
{
	@SuppressWarnings(value = { "unchecked" })  //»òÕß @SuppressWarnings("unchecked")

	public static void main(String[] args)
	{

		ArrayList al = new ArrayList();
		al.add( new Point(2,2) );
		al.add( new Point(3,3) );
		al.add( new Point(4,4) );

		System.out.println( al );
		Object[] obj = al.toArray();//½«Õâ¸öArrayList×ª»»ÎªÊı×é
		for ( int i=0; i<obj.length; i++ )
		{
			System.out.println( obj[i] );
		}

		List l = Arrays.asList( obj ); //½«objÊı×é×ª»»ÎªÒ»¸öList¶ÔÏó
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
ÔËĞĞ£º
[x=2 y=2, x=3 y=3, x=4 y=4]
x=2 y=2
x=3 y=3
x=4 y=4
[x=2 y=2, x=3 y=3, x=4 y=4]




//ArrayListTest.java

import java.util.*;
class ArrayListTest
{
	@SuppressWarnings(value = { "unchecked" })  //»òÕß @SuppressWarnings("unchecked")

	public static void main(String[] args)
	{

		ArrayList al = new ArrayList();
		al.add( new Point(2,2) );
		al.add( new Point(3,3) );
		al.add( new Point(4,4) );

		System.out.println( al );
		Object[] obj = al.toArray();//½«Õâ¸öArrayList×ª»»ÎªÊı×é
		for ( int i=0; i<obj.length; i++ )
		{
			System.out.println( obj[i] );
		}

		List l = Arrays.asList( obj ); //½«objÊı×é×ª»»ÎªÒ»¸öList¶ÔÏó

		l.add( new Point(5,5) );//ÕâÀïÍ¨¹ıArrays.asList()·½·¨·µ»ØµÄÒ»¸ö¹Ì¶¨³ß´çµÄList
								//ÔÙÔö¼Ó¾Í»á³öÏÖÒì³£

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
ÔËĞĞ£º
[x=2 y=2, x=3 y=3, x=4 y=4]
x=2 y=2
x=3 y=3
x=4 y=4
Exception in thread "main" java.lang.UnsupportedOperationException
	at java.util.AbstractList.add(Unknown Source)
	at java.util.AbstractList.add(Unknown Source)
	at ArrayListTest.main(ArrayListTest.java:25)
ËùÒÔ²»ÄÜ¸øËüÔö¼Ó³ÉÔ±ÁË¡£

µü´úÆ÷(Iterator) ¸øÎÒÃÇÌá¹©ÁËÒ»ÖÖÍ¨ÓÃµÄ·½Ê½À´·ÃÎÊ¼¯ºÏÖĞµÄÔªËØ¡£(List.Iterator())
//ArrayListTest.java

import java.util.*;
class ArrayListTest
{
	@SuppressWarnings(value = { "unchecked" })  //»òÕß @SuppressWarnings("unchecked")

	public static void main(String[] args)
	{

		ArrayList al = new ArrayList();
		al.add( new Point(2,2) );
		al.add( new Point(3,3) );
		al.add( new Point(4,4) );

		System.out.println( al );
		Object[] obj = al.toArray();//½«Õâ¸öArrayList×ª»»ÎªÊı×é
		for ( int i=0; i<obj.length; i++ )
		{
			System.out.println( obj[i] );
		}

		List l = Arrays.asList( obj ); //½«objÊı×é×ª»»ÎªÒ»¸öList¶ÔÏó
		System.out.println( l );

		System.out.println("Using Iterator...");

		Iterator it=l.iterator(); //·µ»ØÒ»¸öµü´úÆ÷
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
±àÒëÔËĞĞ£º
[x=2 y=2, x=3 y=3, x=4 y=4]
x=2 y=2
x=3 y=3
x=4 y=4
[x=2 y=2, x=3 y=3, x=4 y=4]
Using Iterator...
x=2 y=2
x=3 y=3
x=4 y=4

Í¨¹ıµü´úÆ÷É¾³ıÒ»¸öÔªËØ£º
//ArrayListTest.java

import java.util.*;
class ArrayListTest
{
	@SuppressWarnings(value = { "unchecked" })  //»òÕß @SuppressWarnings("unchecked")

	public static void main(String[] args)
	{

		ArrayList al = new ArrayList();
		al.add( new Point(2,2) );
		al.add( new Point(3,3) );
		al.add( new Point(4,4) );

		System.out.println( al );
		Object[] obj = al.toArray();//½«Õâ¸öArrayList×ª»»ÎªÊı×é
		for ( int i=0; i<obj.length; i++ )
		{
			System.out.println( obj[i] );
		}

		List l = Arrays.asList( obj ); //½«objÊı×é×ª»»ÎªÒ»¸öList¶ÔÏó
		System.out.println( l );

		System.out.println("Using Iterator...");

		Iterator it=l.iterator(); //·µ»ØÒ»¸öµü´úÆ÷
		it.remove();//Ö±½Óµ÷ÓÃremove()»á³öÏÖÒì³£
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
ÔËĞĞ£º
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

ËùÒÔÎÒÃÇ±ØĞëÏÈÈÃIteratorÒÆ¶¯µ½ÏÂÒ»¸öÔªËØ£¬È»ºóÖ´ĞĞÉ¾³ı²Ù×÷£¬
ÕâÑù»áÉ¾³ıÏÖÔÚIteratorµÄÉÏÒ»¸öÔªËØ


//ArrayListTest.java
import java.util.*;
class ArrayListTest
{
	@SuppressWarnings(value = { "unchecked" })  //»òÕß @SuppressWarnings("unchecked")

	public static void main(String[] args)
	{

		ArrayList al = new ArrayList();
		al.add( new Point(2,2) );
		al.add( new Point(3,3) );
		al.add( new Point(4,4) );

		System.out.println( al );
		Object[] obj = al.toArray();//½«Õâ¸öArrayList×ª»»ÎªÊı×é
		for ( int i=0; i<obj.length; i++ )
		{
			System.out.println( obj[i] );
		}

		List l = Arrays.asList( obj ); //½«objÊı×é×ª»»ÎªÒ»¸öList¶ÔÏó
		System.out.println( l );

		System.out.println("Using Iterator...");

		Iterator it=l.iterator(); //·µ»ØÒ»¸öµü´úÆ÷
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
È»¶øÏÖÔÚ»¹ÊÇ³öÏÖÒì³£,why?
Òì³£ĞÅÏ¢ÊÇ UnsupportedOperationException ,
¿´¿´°ïÖúÎÄµµ:
void remove()Removes from the underlying collection the last element returned by the iterator (optional operation). This method can be called only once per call to next. The behavior of an iterator is unspecified if the underlying collection is modified while the iteration is in progress in any way other than by calling this method.
throws:
UnsupportedOperationException - if the remove operation is not supported by this Iterator.
IllegalStateException - if the next method has not yet been called, or the remove method has already been called after the last call to the next method.

ÄÇ¿´¿´ÎÒÃÇ×ÔĞĞ²¶×½Õâ¸öÒì³£ĞĞ²»ĞĞÄØ£¿
//ArrayListTest.java

import java.util.*;
class ArrayListTest
{
	@SuppressWarnings(value = { "unchecked" })  //»òÕß @SuppressWarnings("unchecked")

	public static void main(String[] args)
	{

		ArrayList al = new ArrayList();
		al.add( new Point(2,2) );
		al.add( new Point(3,3) );
		al.add( new Point(4,4) );

		System.out.println( al );
		Object[] obj = al.toArray();//½«Õâ¸öArrayList×ª»»ÎªÊı×é
		for ( int i=0; i<obj.length; i++ )
		{
			System.out.println( obj[i] );
		}

		List l = Arrays.asList( obj ); //½«objÊı×é×ª»»ÎªÒ»¸öList¶ÔÏó
		System.out.println( l );

		System.out.println("Using Iterator...");

		Iterator it=l.iterator(); //·µ»ØÒ»¸öµü´úÆ÷
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

»¹ÊÇÒ»ÑùµÄ´íÎó£¬¿´À´ÊÇÆäËû·½ÃæµÄÔ­Òò¡£

Å¶,Ô­À´ÎÒÃÇ·¢ÏÖÎÒÃÇµÄµü´úÆ÷ÊÇÍ¨¹ı Arrays.asList( obj )·µ»ØµÄ List ¶ÔÏó,
ÕâÖÖListÊÇ¹Ì¶¨³¤¶ÈµÄ£¬ÕıÈçÇ°Ãæ²»ÄÜÌí¼ÓÔªËØÒ»Ñù£¬ÏÖÔÚÖ´ĞĞÉ¾³ı²Ù×÷Ò²Ò»Ñù²»ĞĞ¡£
ËùÒÔÎÒÃÇÒª½øĞĞÕâĞ©²Ù×÷µÄÊ±ºò¿ÉÒÔÈÃµü´úÆ÷´ÓArrays¶ÔÏó²úÉú£¬ÈçÏÂ£º

//ArrayListTest.java

import java.util.*;
class ArrayListTest
{
	@SuppressWarnings(value = { "unchecked" })  //»òÕß @SuppressWarnings("unchecked")

	public static void main(String[] args)
	{

		ArrayList al = new ArrayList();
		al.add( new Point(2,2) );
		al.add( new Point(3,3) );
		al.add( new Point(4,4) );

		System.out.println( al );
		Object[] obj = al.toArray();//½«Õâ¸öArrayList×ª»»ÎªÊı×é
		for ( int i=0; i<obj.length; i++ )
		{
			System.out.println( obj[i] );
		}

		List l = Arrays.asList( obj ); //½«objÊı×é×ª»»ÎªÒ»¸öList¶ÔÏó
		System.out.println( l );

		System.out.println("Using Iterator...");

		Iterator it=al.iterator(); //·µ»ØÒ»¸öµü´úÆ÷
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

ÕâÑù¾ÍºÃÁË¡£

µü´úÆ÷(Iterator) ¸øÎÒÃÇÌá¹©ÁËÒ»ÖÖÍ¨ÓÃµÄ·½Ê½À´·ÃÎÊ¼¯ºÏÖĞµÄÔªËØ,
ÏÂÃæÎÒÃÇ¿´¿´ÕâÖÖÍ¨ÓÃ·½·¨µÄºÃ´¦£º

//ArrayListTest.java

import java.util.*;
class ArrayListTest
{
	/**
	 * ÕâÀïÌá¹©ÁËÒ»¸ö¶Ô¼¯ºÏÀàÍ¨ÓÃµÄ·ÃÎÊ·½·¨£¬Õâ¶ÔÓÚ³ÌĞò¶øÑÔÊÇºÜ·½±ãµÄ
	 */
	public static void printElement( Collection c )
	{
		Iterator it = c.iterator();
		while ( it.hasNext() )
		{
			System.out.println( it.next() );
		}
	}
	@SuppressWarnings(value = { "unchecked" })  //»òÕß @SuppressWarnings("unchecked")
	public static void main(String[] args)
	{

		ArrayList al = new ArrayList();
		al.add( new Point(2,2) );
		al.add( new Point(3,3) );
		al.add( new Point(4,4) );

		System.out.println( al );
		Object[] obj = al.toArray();//½«Õâ¸öArrayList×ª»»ÎªÊı×é
		for ( int i=0; i<obj.length; i++ )
		{
			System.out.println( obj[i] );
		}
		List l = Arrays.asList( obj ); //½«objÊı×é×ª»»ÎªÒ»¸öList¶ÔÏó
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


CollectionsÀà
ÅÅĞò£ºCollections.sort()
£¨1£©×ÔÈ»ÅÅÑ°(natural ordering )£»
£¨2£©ÊµÏÖ±È½ÏÆ÷(Comparator)½Ó¿Ú¡£
È¡×î´óºÍ×îĞ¡µÄÔªËØ£ºCollections.max()¡¢Collections.min()¡£
ÔÚÒÑÅÅĞòµÄListÖĞËÑË÷Ö¸¶¨µÄÔªËØ£ºCollectons.binarySearch()¡£


sort
public static <T extends Comparable<? super T>> void sort(List<T> list)¸ù¾İÔªËØµÄ×ÔÈ»Ë³Ğò ¶ÔÖ¸¶¨ÁĞ±í°´ÉıĞò½øĞĞÅÅĞò¡£ÁĞ±íÖĞµÄËùÓĞÔªËØ¶¼±ØĞëÊµÏÖ Comparable ½Ó¿Ú¡£´ËÍâ£¬ÁĞ±íÖĞµÄËùÓĞÔªËØ¶¼±ØĞëÊÇ¿ÉÏà»¥±È½ÏµÄ£¨Ò²¾ÍÊÇËµ£¬¶ÔÓÚÁĞ±íÖĞµÄÈÎºÎ e1 ºÍ e2 ÔªËØ£¬e1.compareTo(e2) ²»µÃÅ×³ö ClassCastException£©¡£

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
	@SuppressWarnings(value = { "unchecked" })  //»òÕß @SuppressWarnings("unchecked")
	public static void main(String[] args)
	{

		ArrayList al = new ArrayList();
		al.add( new Student(2,"zhangsan") );
		al.add( new Student(3,"lisi") );
		al.add( new Student(1,"wangwu") );

		System.out.println( "Before Sorting" );
		printElement( al );
		Collections.sort( al );//ÅÅĞò
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

	public int compareTo(Object o)//ÕâÀïÊÇÎªÁË½øĞĞsortÅÅĞò¶ø±ØĞëÊµÏÖµÄ½Ó¿Úº¯Êı
	{
		Student s=(Student)o;
		return num > s.num ? 1 : (num==s.num ? 0 : -1);
	}
	public String toString()//Õâ¸öÊÇÎªÁË´òÓ¡¶ø±ØĞëÊµÏÖµÄ½Ó¿Úº¯Êı
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





ÔÚÅÅĞòµÄÊ±ºò»¹¿ÉÒÔ´«µİÒ»¸ö±È½ÏÆ÷£¬ÕâÑù¾Í²»ĞèÒªÊµÏÖComparable½Ó¿Ú
static <T> void sort(List<T> list, Comparator<? super T> c)
          ¸ù¾İÖ¸¶¨±È½ÏÆ÷²úÉúµÄË³Ğò¶ÔÖ¸¶¨ÁĞ±í½øĞĞÅÅĞò¡£
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
	@SuppressWarnings(value = { "unchecked" })  //»òÕß @SuppressWarnings("unchecked")
	public static void main(String[] args)
	{
		ArrayList al = new ArrayList();
		al.add( new Student(2,"zhangsan") );
		al.add( new Student(3,"lisi") );
		al.add( new Student(3,"apple") );
		al.add( new Student(1,"wangwu") );

		System.out.println( "Before Sorting" );
		printElement( al );
		Collections.sort( al, new Student.StudentComparator() );//Í¨¹ıÖ¸¶¨±È½ÏÆ÷½øĞĞÅÅĞò
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

	//¹¹ÔìÒ»¸öÄÚ²¿ÀàÀ´ÊµÏÖsort·½·¨°´Ö¸¶¨±È½ÏÆ÷²úÉúµÄË³Ğò¶ÔÖ¸¶¨ÁĞ±í½øĞĞÅÅĞò¡£
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
	public String toString()//Õâ¸öÊÇÎªÁË´òÓ¡¶ø±ØĞëÊµÏÖµÄ½Ó¿Úº¯Êı
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

ÕâÀïÎÒÃÇÏëÈç¹ûĞòºÅÏàµÈ£¬¾Í°´ÕÕÃû×ÖÔÚ½øĞĞÅÅĞò£¬¾ÍÏñÉÏÃæµÄappleÓ¦¸ÃÅÅÔÚlisiÇ°Ãæ£¬
ÒòÎªÎÒÃÇÓĞÁË±È½ÏÆ÷£¬ÄÇÃ´ÕâÑùÊµÏÖÆğÀ´ºÜ·½±ã£¬Ö»Ğè½«compare·½·¨ÖØĞ´ÈçÏÂ£º
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

ÍêÕûµÄ³ÌĞòÈçÏÂ£º
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
	@SuppressWarnings(value = { "unchecked" })  //»òÕß @SuppressWarnings("unchecked")
	public static void main(String[] args)
	{
		ArrayList al = new ArrayList();
		al.add( new Student(2,"zhangsan") );
		al.add( new Student(3,"lisi") );
		al.add( new Student(3,"apple") );
		al.add( new Student(1,"wangwu") );

		System.out.println( "Before Sorting" );
		printElement( al );
		Collections.sort( al, new Student.StudentComparator() );//Í¨¹ıÖ¸¶¨±È½ÏÆ÷½øĞĞÅÅĞò
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

	//¹¹ÔìÒ»¸öÄÚ²¿ÀàÀ´ÊµÏÖsort·½·¨°´Ö¸¶¨±È½ÏÆ÷²úÉúµÄË³Ğò¶ÔÖ¸¶¨ÁĞ±í½øĞĞÅÅĞò¡£
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
	public String toString()//Õâ¸öÊÇÎªÁË´òÓ¡¶ø±ØĞëÊµÏÖµÄ½Ó¿Úº¯Êı
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


Èç¹ûÒª·´ĞòÅÅÁĞ£¬ÄÇºÜºÃ°ì£¬CollectionsÀàÖĞÓĞÕâÑùµÄÒ»¸ö·½·¨ Collections.reverseOrder()) £¬
ÍêÈ«¿ÉÒÔÊµÏÖ¡£

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
	@SuppressWarnings(value = { "unchecked" })  //»òÕß @SuppressWarnings("unchecked")
	public static void main(String[] args)
	{
		ArrayList al = new ArrayList();
		al.add( new Student(2,"zhangsan") );
		al.add( new Student(3,"apple") );
		al.add( new Student(3,"lisi") );
		al.add( new Student(1,"wangwu") );

		System.out.println( "Before Sorting" );
		printElement( al );
		Collections.sort( al, Collections.reverseOrder() );//Í¨¹ıÖ¸¶¨±È½ÏÆ÷½øĞĞÅÅĞò
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

	//¹¹ÔìÒ»¸öÄÚ²¿ÀàÀ´ÊµÏÖsort·½·¨°´Ö¸¶¨±È½ÏÆ÷²úÉúµÄË³Ğò¶ÔÖ¸¶¨ÁĞ±í½øĞĞÅÅĞò¡£
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
	public String toString()//Õâ¸öÊÇÎªÁË´òÓ¡¶ø±ØĞëÊµÏÖµÄ½Ó¿Úº¯Êı
	{
		return num+":"+name;
	}
}

µ«ÊÇÕâÑù»á³ö´í£º
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
´íÎóĞÅÏ¢¸ßËßÎÒÃÇ£¬ÎÒÃÇÃ»ÓĞÊµÏÖReverseComparator.compare()·½·¨£¬
Å¶£¬ÎÒÃÇÃ»ÓĞÊµÏÖcompare·½·¨
Õâ¸öºÃ°ìÎÒÃÇÊµÏÖComparable½Ó¿Ú¾ÍºÃÁË£¬
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
	@SuppressWarnings(value = { "unchecked" })  //»òÕß @SuppressWarnings("unchecked")
	public static void main(String[] args)
	{
		ArrayList al = new ArrayList();
		al.add( new Student(3,"apple") );
		al.add( new Student(2,"zhangsan") );
		al.add( new Student(3,"lisi") );
		al.add( new Student(1,"wangwu") );

		System.out.println( "Before Sorting" );
		printElement( al );
		Collections.sort( al, Collections.reverseOrder() );//Í¨¹ıÖ¸¶¨±È½ÏÆ÷½øĞĞÅÅĞò
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

	/*//¹¹ÔìÒ»¸öÄÚ²¿ÀàÀ´ÊµÏÖsort·½·¨°´Ö¸¶¨±È½ÏÆ÷²úÉúµÄË³Ğò¶ÔÖ¸¶¨ÁĞ±í½øĞĞÅÅĞò¡£
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
	public int compareTo(Object o)//ÕâÀïÊÇÎªÁË½øĞĞsortÅÅĞò¶ø±ØĞëÊµÏÖµÄ½Ó¿Úº¯Êı
	{
		Student s=(Student)o;
		return num > s.num ? 1 : (num==s.num ? 0 : -1);
	}
	public String toString()//Õâ¸öÊÇÎªÁË´òÓ¡¶ø±ØĞëÊµÏÖµÄ½Ó¿Úº¯Êı
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

ÕâÀï³öÏÖÁËÍ¬ÑùĞòºÅµÄÅÅĞòÓĞĞ©ÎÊÌâµÄÎÊÌâ£¬ÎÒÃÇÏëĞòºÅÏàÍ¬ºó£¬¼ÌĞøÍ¨¹ıÃû×ÖÅÅĞò£¬
¼´ÊÇlist±Èapple´ó£¬ÄÇÃ´·´Ğò¾ÍÓ¦¸ÃlistÔÚappleÇ°.
ºÃ¶à,¿´¿´°ïÖúÎÄµµ, reverseOrder(Comparator<T> cmp) Ò²¿ÉÒÔÍ¨¹ıÖ¸¶¨µÄ±È½ÏÆ÷½øĞĞÅÅĞò,
ÕâÑù¾ÍºÃ°ì¶àÁË.

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
	@SuppressWarnings(value = { "unchecked" })  //»òÕß @SuppressWarnings("unchecked")
	public static void main(String[] args)
	{
		ArrayList al = new ArrayList();
		al.add( new Student(3,"apple") );
		al.add( new Student(2,"zhangsan") );
		al.add( new Student(3,"lisi") );
		al.add( new Student(1,"wangwu") );

		System.out.println( "Before Sorting" );
		printElement( al );
		Collections.sort( al, Collections.reverseOrder( new Student.StudentComparator() ) );//Í¨¹ıÖ¸¶¨±È½ÏÆ÷½øĞĞÅÅĞò
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

	//¹¹ÔìÒ»¸öÄÚ²¿ÀàÀ´ÊµÏÖsort·½·¨°´Ö¸¶¨±È½ÏÆ÷²úÉúµÄË³Ğò¶ÔÖ¸¶¨ÁĞ±í½øĞĞÅÅĞò¡£
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
	public String toString()//Õâ¸öÊÇÎªÁË´òÓ¡¶ø±ØĞëÊµÏÖµÄ½Ó¿Úº¯Êı
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

È¡×î´óºÍ×îĞ¡µÄÔªËØ£ºCollections.max()¡¢Collections.min()¡£
ÔÚÒÑÅÅĞòµÄListÖĞËÑË÷Ö¸¶¨µÄÔªËØ£ºCollectons.binarySearch()¡£

LinkedList
LinkedListÊÇ²ÉÓÃË«ÏòÑ­»·Á´±íÊµÏÖµÄ¡£
ÀûÓÃLinkedListÊµÏÖÕ»(stack)¡¢¶ÓÁĞ(queue)¡¢Ë«Ïò¶ÓÁĞ(double-ended queue )¡£


Õ»(Stack)Ò²ÊÇÒ»ÖÖÌØÊâµÄÏßĞÔ±í£¬ÊÇÒ»ÖÖºó½øÏÈ³ö(LIFO)µÄ½á¹¹¡£
Õ»ÊÇÏŞ¶¨½öÔÚ±íÎ²½øĞĞ²åÈëºÍÉ¾³ıÔËËãµÄÏßĞÔ±í£¬±íÎ²³ÆÎªÕ»¶¥(top)£¬±íÍ·³ÆÎªÕ»µ×(bottom)¡£
Õ»µÄÎïÀí´æ´¢¿ÉÒÔÓÃË³Ğò´æ´¢½á¹¹£¬Ò²¿ÉÒÔÓÃÁ´Ê½´æ´¢½á¹¹¡£

ÀûÓÃLinkedListÊµÏÖÕ»(stack):

//MyStack.java
import java.util.*;
public class MyStack {

	/**
	 * @param args
	 */
	private LinkedList ll=new LinkedList();
	@SuppressWarnings(value = { "unchecked" })
	public void push(Object o)//Ñ¹ÈëÒ»¸öÔªËØ,ÕâÀïÊÇ¼ÓÈëÒ»¸öÔªËØµ½±íÍ·
	{
		ll.addFirst( o );
	}
	public Object pop()//µ¯³öÒ»¸öÔªËØ
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


¶ÓÁĞ(Queue)ÊÇÏŞ¶¨ËùÓĞµÄ²åÈëÖ»ÄÜÔÚ±íµÄÒ»¶Ë½øĞĞ£¬¶øËùÓĞµÄÉ¾³ı¶¼ÔÚ±íµÄÁíÒ»¶Ë½øĞĞµÄÏßĞÔ±í¡£
±íÖĞÔÊĞí²åÈëµÄÒ»¶Ë³ÆÎª¶ÓÎ²(Rear)£¬ÔÊĞíÉ¾³ıµÄÒ»¶Ë³ÆÎª¶ÓÍ·(Front)¡£
¶ÓÁĞµÄ²Ù×÷ÊÇ°´ÏÈ½øÏÈ³ö(FIFO)µÄÔ­Ôò½øĞĞµÄ¡£
¶ÓÁĞµÄÎïÀí´æ´¢¿ÉÒÔÓÃË³Ğò´æ´¢½á¹¹£¬Ò²¿ÉÒÔÓÃÁ´Ê½´æ´¢½á¹¹¡£

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

ArrayListºÍLinkedListµÄ±È½Ï
ArrayListµ×²ã²ÉÓÃÊı×éÍê³É£¬¶øLinkedListÔòÊÇÒÔÒ»°ãµÄË«ÏòÁ´±í(double-linked list)Íê³É£¬ÆäÄÚÃ¿¸ö¶ÔÏó³ıÁËÊı¾İ±¾ÉíÍâ£¬»¹ÓĞÁ½¸ö ÒıÓÃ£¬·Ö±ğÖ¸ÏòÇ°Ò»¸öÔªËØºÍºóÒ»¸öÔªËØ¡£
Èç¹ûÎÒÃÇ¾­³£ÔÚListµÄ¿ªÊ¼´¦Ôö¼ÓÔªËØ£¬»òÕßÔÚListÖĞ½øĞĞ²åÈëºÍÉ¾³ı²Ù×÷£¬ÎÒÃÇÓ¦¸ÃÊ¹ÓÃLinkedList£¬·ñÔòµÄ»°£¬Ê¹ÓÃArrayList½«¸ü¼Ó¿ìËÙ¡£


HashSet
ÊµÏÖSet½Ó¿ÚµÄhash table(¹şÏ£±í)£¬ÒÀ¿¿HashMapÀ´ÊµÏÖµÄ¡£
ÎÒÃÇÓ¦¸ÃÎªÒª´æ·Åµ½É¢ÁĞ±íµÄ¸÷¸ö¶ÔÏó¶¨ÒåhashCode()ºÍequals()¡£
É¢ÁĞ±íÓÖ³ÆÎª¹şÏ£±í¡£É¢ÁĞ±íËã·¨µÄ»ù±¾Ë¼ÏëÊÇ£º
  ÒÔ½áµãµÄ¹Ø¼ü×ÖÎª×Ô±äÁ¿£¬Í¨¹ıÒ»¶¨µÄº¯Êı¹ØÏµ£¨É¢ÁĞº¯Êı£©¼ÆËã³ö¶ÔÓ¦µÄº¯ÊıÖµ£¬ÒÔÕâ¸öÖµ×÷Îª¸Ã½áµã´æ´¢ÔÚÉ¢ÁĞ±íÖĞµÄµØÖ·¡£
µ±É¢ÁĞ±íÖĞµÄÔªËØ´æ·ÅÌ«Âú£¬¾Í±ØĞë½øĞĞÔÙÉ¢ÁĞ£¬½«²úÉúÒ»¸öĞÂµÄÉ¢ÁĞ±í£¬ËùÓĞÔªËØ´æ·Åµ½ĞÂµÄÉ¢ÁĞ±íÖĞ£¬Ô­ÏÈµÄÉ¢ÁĞ±í½«±»É¾³ı¡£ÔÚJavaÓïÑÔÖĞ£¬Í¨¹ı¸ºÔØÒò×Ó(load factor)À´¾ö¶¨ºÎÊ±¶ÔÉ¢ÁĞ±í½øĞĞÔÙÉ¢ÁĞ¡£ÀıÈç£ºÈç¹û¸ºÔØÒò×ÓÊÇ0.75£¬µ±É¢ÁĞ±íÖĞÒÑ¾­ÓĞ75%µÄÎ»ÖÃÒÑ¾­·ÅÂú£¬ÄÇÃ´½«½øĞĞÔÙÉ¢ÁĞ¡£
¸ºÔØÒò×ÓÔ½¸ß(Ô½½Ó½ü1.0)£¬ÄÚ´æµÄÊ¹ÓÃĞ§ÂÊÔ½¸ß£¬ÔªËØµÄÑ°ÕÒÊ±¼äÔ½³¤¡£¸ºÔØÒò×ÓÔ½µÍ(Ô½½Ó½ü0.0)£¬ÔªËØµÄÑ°ÕÒÊ±¼äÔ½¶Ì£¬ÄÚ´æÀË·ÑÔ½¶à¡£
HashSetÀàµÄÈ±Ê¡¸ºÔØÒò×ÓÊÇ0.75¡£

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
		hs.add("one");//HashSetÊµÏÖÁËSet½Ó¿Ú£¬ËùÒÔ²»ÄÜ³öÏÖÖØ¸´µÄÔªËØ£¬ÕâÀï½«»áºöÂÔ
		Iterator it=hs.iterator();
		while(it.hasNext())
		{
			System.out.println(it.next());
		}
	}
}
´òÓ¡Êä³ö:
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
ÕâÀï³öÏÖÁËÏàÍ¬µÄÔªËØ±»´æ·Åµ½HashSetÖĞ,ÎªÊ²Ã´?
ÒòÎªHashSetÊÇ¸ù¾İObjectÀàÖĞhashCode()º¯Êı¼ÆËã³ö¹şÏ£ÂëÀ´¾ö¶¨ÔªËØÔÚ¹şÏ£±íÖĞµÄÎ»ÖÃ,
µ«ÊÇhashCode()º¯ÊıÊÇ¸ù¾İ¶ÔÏóµÄÄÚ²¿µØÖ·À´¼ÆËãµÄ
ÎªÁË±ÜÃâÕâĞ©Çé¿öµÄ·¢Éú£¬ÎÒÃÇ±ØĞë½«´ıÌí¼Óµ½HashSet±íÖĞµÄ¶ÔÏóÖØÔØ hashCode() ºÍ equals() ·½·¨.
ÎÒÃÇÓ¦¸ÃÎªÒª´æ·Åµ½É¢ÁĞ±íµÄ¸÷¸ö¶ÔÏó¶¨ÒåhashCode()ºÍequals()¡£
ÏÂÃæÎÒÃÇÕâÑùÊÔÒ»ÊÔ:
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

ÕâÑù¾ÍÃ»ÓĞÍ¬ÑùµÄÊä³öÁË.

TreeSet
TreeSetÊÇÒÀ¿¿TreeMapÀ´ÊµÏÖµÄ¡£
TreeSetÊÇÒ»¸öÓĞĞò¼¯ºÏ£¬TreeSetÖĞÔªËØ½«°´ÕÕÉıĞòÅÅÁĞ£¬È±Ê¡ÊÇ°´ÕÕ×ÔÈ»Ë³Ğò½øĞĞÅÅÁĞ£¬ÒâÎ¶×ÅTreeSetÖĞÔªËØÒªÊµÏÖComparable½Ó¿Ú¡£
ÎÒÃÇ¿ÉÒÔÔÚ¹¹ÔìTreeSet¶ÔÏóÊ±£¬´«µİÊµÏÖÁËComparator½Ó¿ÚµÄ±È½ÏÆ÷¶ÔÏó¡£


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

ÎÒÃÇÒ²¿ÉÒÔÔö¼ÓÊµÏÖÁËComparable½Ó¿ÚµÄÀà¶ÔÏó£º
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
	public int compareTo(Object o)//ÕâÀïÊÇÎªÁË½øĞĞsortÅÅĞò¶ø±ØĞëÊµÏÖµÄ½Ó¿Úº¯Êı
	{
		Student s=(Student)o;
		return num > s.num ? 1 : (num==s.num ? 0 : -1);
	}
	public String toString()//Õâ¸öÊÇÎªÁË´òÓ¡¶ø±ØĞëÊµÏÖµÄ½Ó¿Úº¯Êı
	{
		return num+":"+name;
	}
}
E:\zieckey\Lesson8>javac TreeSetTest.java

E:\zieckey\Lesson8>java TreeSetTest
1:wangwu
2:lisi
3:zhangsan

»òÕß´«µİÒ»¸ö±È½ÏÆ÷µÄ¶ÔÏó£º
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
	//¹¹ÔìÒ»¸öÄÚ²¿ÀàÀ´ÊµÏÖsort·½·¨°´Ö¸¶¨±È½ÏÆ÷²úÉúµÄË³Ğò¶ÔÖ¸¶¨ÁĞ±í½øĞĞÅÅĞò¡£
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
	/*public int compareTo(Object o)//ÕâÀïÊÇÎªÁË½øĞĞsortÅÅĞò¶ø±ØĞëÊµÏÖµÄ½Ó¿Úº¯Êı
	{
		Student s=(Student)o;
		return num > s.num ? 1 : (num==s.num ? 0 : -1);
	}*/
	public String toString()//Õâ¸öÊÇÎªÁË´òÓ¡¶ø±ØĞëÊµÏÖµÄ½Ó¿Úº¯Êı
	{
		return num+":"+name;
	}
}
E:\zieckey\Lesson8>javac TreeSetTest.java

E:\zieckey\Lesson8>java TreeSetTest
1:wangwu
2:lisi
3:zhangsan
HashSetºÍTreeSetµÄ±È½Ï
HashSetÊÇ»ùÓÚHashËã·¨ÊµÏÖµÄ£¬ÆäĞÔÄÜÍ¨³£¶¼ÓÅÓÚTreeSet¡£ÎÒÃÇÍ¨³£¶¼Ó¦¸ÃÊ¹ÓÃHashSet£¬ÔÚÎÒÃÇĞèÒªÅÅĞòµÄ¹¦ÄÜÊ±£¬ÎÒÃÇ²ÅÊ¹ÓÃTreeSet¡£


HashMap
HashMap¶Ôkey½øĞĞÉ¢ÁĞ¡£
keySet()¡¢values()¡¢entrySet()¡£
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

Properties Àà±íÊ¾ÁËÒ»¸ö³Ö¾ÃµÄÊôĞÔ¼¯¡£Properties ¿É±£´æÔÚÁ÷ÖĞ»ò´ÓÁ÷ÖĞ¼ÓÔØ¡£ÊôĞÔÁĞ±íÖĞÃ¿¸ö¼ü¼°Æä¶ÔÓ¦Öµ¶¼ÊÇÒ»¸ö×Ö·û´®¡£

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



ÀûÓÃPropertiesÀàÀ´¼ÓÔØÎÄ¼şÄÚÈİÀàËÆÈçÏÂµÄ£º
company=winsun
author=sunxin
copyright=2003-2004

¸ÃÎÄ¼ş±£´æÔÚwinsun.iniÖĞ£¬ÄÇÃ´³ÌĞòÖĞ¿ÉÒÔÕâÑù¶ÁÈ¡ÎÄ¼şÄÚÈİ£º

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
Êä³ö£º
company=winsun
copyright=2003-2004
author=sunxin



Lesson9
Java I/O²Ù×÷

FileÀà
Ò»¸öFileÀàµÄ¶ÔÏó£¬±íÊ¾ÁË´ÅÅÌÉÏµÄÎÄ¼ş»òÄ¿Â¼¡£
FileÀàÌá¹©ÁËÓëÆ½Ì¨ÎŞ¹ØµÄ·½·¨À´¶Ô´ÅÅÌÉÏµÄÎÄ¼ş»òÄ¿Â¼½øĞĞ²Ù×÷¡£


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
ÕâÑùÖ»»áÔÚµ±Ç°Ä¿Â¼ÏÂ´´½¨Ò»¸ö 1.txt ÎÄ¼ş£¬¶ø²»»á´´½¨ 1.txt ÎÄ¼ş¼Ğ¡£
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
ÕâÑù¾Í»á´´½¨Ò»¸öÎÄ¼ş¼Ğ¡£

Ò²¿ÉÒÔÔÚÖ¸¶¨Â·¾¶´´½¨ĞÂÎÄ¼ş£¬
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
ÕâÑùĞ´µÄ´úÂëÈç¹ûÒÆÖ²µ½LinuxÏÂ¾Í»á³öÏÖÎÊÌâ£¬ÒòÎªÂ·¾¶¸ñÊ½²»¶Ô¡£
ÏÂÃæÊÇ´´½¨Ò»¸öÎÄ¼ş£¬¶øÓëÆ½Ì¨ÎŞ¹Ø¡£
package file;
import java.io.*;
public class FileTest {
	public static void main(String[] args) {
		//File.separator±íÊ¾ÁËÄ¿Â¼·Ö¸ô·û£¬Ëü²»ÒÀÀµÓÚÌØ¶¨²Ù×÷ÏµÍ³
		//File.separatorÖ±½ÓÓÃ¿ÉÒÔ±íÊ¾Windowµ±Ç°ÅÌ·ûµÄ¸ùÄ¿Â¼
		File fDir=new File(File.separator);
		String strFile="JavaLesson"+File.separator+"Lesson9"+
			File.separator+"2.txt";
		File f=new File(fDir,strFile);//ĞÂ½¨Ò»¸öFile¶ÔÏó
		try{
			f.createNewFile();
		}
		catch( Exception e ){
			e.printStackTrace();
		}
	}
}

É¾³ıÎÄ¼ş»òÄ¿Â¼£º
 boolean delete()
          É¾³ı´Ë³éÏóÂ·¾¶Ãû±íÊ¾µÄÎÄ¼ş»òÄ¿Â¼¡£
 void deleteOnExit()
          ÔÚĞéÄâ»úÖÕÖ¹Ê±£¬ÇëÇóÉ¾³ı´Ë³éÏóÂ·¾¶Ãû±íÊ¾µÄÎÄ¼ş»òÄ¿Â¼¡£

ÔÚ³ÌĞòÖĞ´´½¨ÁÙÊ±ÎÄ¼ş£¬È»ºóÔÙ³ÌĞòÍË³öÊ±É¾³ıÁÙÊ±ÎÄ¼ş¡£
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
          ·µ»ØÓÉ´Ë³éÏóÂ·¾¶ÃûËù±íÊ¾µÄÄ¿Â¼ÖĞµÄÎÄ¼şºÍÄ¿Â¼µÄÃû³ÆËù×é³É×Ö·û´®Êı×é¡£
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
Êä³ö£º
.project
.classpath
src
bin
1.txt
2.txt

String[] list(FilenameFilter filter)
          ·µ»ØÓÉ°üº¬ÔÚÄ¿Â¼ÖĞµÄÎÄ¼şºÍÄ¿Â¼µÄÃû³ÆËù×é³ÉµÄ×Ö·û´®Êı×é£¬ÕâÒ»Ä¿Â¼ÊÇÍ¨¹ıÂú×ãÖ¸¶¨¹ıÂËÆ÷µÄ³éÏóÂ·¾¶ÃûÀ´±íÊ¾µÄ¡£
//FileTest.java
package file;
import java.io.*;
public class FileTest {
	public static void main(String[] args) {
		File fDir=new File(File.separator);
		String strFile="JavaLesson"+File.separator+"Lesson9";
		File f=new File(fDir,strFile);
		String[] names=f.list(new FilenameFilter() //´´½¨Ò»¸ö¹ıÂËÆ÷£¬ËüÊÇ¸ö½Ó¿Ú£¬
		{//Í¨¹ıÄäÃûµÄÄÚ²¿Àà´´½¨Õâ¸ö½Ó¿ÚµÄÊµÀı¶ÔÏó
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


Á÷Ê½I/O
Á÷(Stream)ÊÇ×Ö½ÚµÄÔ´»òÄ¿µÄ¡£
Á½ÖÖ»ù±¾µÄÁ÷ÊÇ£ºÊäÈëÁ÷(Input Stream)ºÍÊä³öÁ÷(Output Stream)¡£¿É´ÓÖĞ¶Á³öÒ»ÏµÁĞ×Ö½ÚµÄ¶ÔÏó³ÆÎªÊäÈëÁ÷¡£¶øÄÜÏòÆäÖĞĞ´ÈëÒ»ÏµÁĞ×Ö½ÚµÄ¶ÔÏó³ÆÎªÊä³öÁ÷¡£

Á÷µÄ·ÖÀà
½ÚµãÁ÷£º´ÓÌØ¶¨µÄµØ·½¶ÁĞ´µÄÁ÷Àà£¬ÀıÈç£º´ÅÅÌ»òÒ»¿éÄÚ´æÇøÓò¡£
¹ıÂËÁ÷£ºÊ¹ÓÃ½ÚµãÁ÷×÷ÎªÊäÈë»òÊä³ö¡£¹ıÂËÁ÷ÊÇÊ¹ÓÃÒ»¸öÒÑ¾­´æÔÚµÄÊäÈëÁ÷»òÊä³öÁ÷Á¬½Ó´´½¨µÄ¡£

InputStream
Èı¸ö»ù±¾µÄ¶Á·½·¨
      abstract int read() £º¶ÁÈ¡Ò»¸ö×Ö½ÚÊı¾İ£¬²¢·µ»Ø¶Áµ½µÄÊı¾İ£¬Èç¹û·µ»Ø-1£¬±íÊ¾¶Áµ½ÁËÊäÈëÁ÷µÄÄ©Î²¡£
      int read(byte[]?b) £º½«Êı¾İ¶ÁÈëÒ»¸ö×Ö½ÚÊı×é£¬Í¬Ê±·µ»ØÊµ¼Ê¶ÁÈ¡µÄ×Ö½ÚÊı¡£Èç¹û·µ»Ø-1£¬±íÊ¾¶Áµ½ÁËÊäÈëÁ÷µÄÄ©Î²¡£
      int read(byte[]?b, int?off, int?len) £º½«Êı¾İ¶ÁÈëÒ»¸ö×Ö½ÚÊı×é£¬Í¬Ê±·µ»ØÊµ¼Ê¶ÁÈ¡µÄ×Ö½ÚÊı¡£Èç¹û·µ»Ø-1£¬±íÊ¾¶Áµ½ÁËÊäÈëÁ÷µÄÄ©Î²¡£offÖ¸¶¨ÔÚÊı×ébÖĞ´æ·ÅÊı¾İµÄÆğÊ¼Æ«ÒÆÎ»ÖÃ£»lenÖ¸¶¨¶ÁÈ¡µÄ×î´ó×Ö½ÚÊı¡£
ÆäËü·½·¨
      long skip(long?n) £ºÔÚÊäÈëÁ÷ÖĞÌø¹ın¸ö×Ö½Ú£¬²¢·µ»ØÊµ¼ÊÌø¹ıµÄ×Ö½ÚÊı¡£
      int available() £º·µ»ØÔÚ²»·¢Éú×èÈûµÄÇé¿öÏÂ£¬¿É¶ÁÈ¡µÄ×Ö½ÚÊı¡£
      void close() £º¹Ø±ÕÊäÈëÁ÷£¬ÊÍ·ÅºÍÕâ¸öÁ÷Ïà¹ØµÄÏµÍ³×ÊÔ´¡£
      void mark(int?readlimit) £ºÔÚÊäÈëÁ÷µÄµ±Ç°Î»ÖÃ·ÅÖÃÒ»¸ö±ê¼Ç£¬Èç¹û¶ÁÈ¡µÄ×Ö½ÚÊı¶àÓÚreadlimitÉèÖÃµÄÖµ£¬ÔòÁ÷ºöÂÔÕâ¸ö±ê¼Ç¡£
      void reset() £º·µ»Øµ½ÉÏÒ»¸ö±ê¼Ç¡£
      boolean markSupported() £º²âÊÔµ±Ç°Á÷ÊÇ·ñÖ§³ÖmarkºÍreset·½·¨¡£Èç¹ûÖ§³Ö£¬·µ»Øtrue£¬·ñÔò·µ»Øfalse¡£

OutputStream
Èı¸ö»ù±¾µÄĞ´·½·¨
     abstract void write(int?b) £ºÍùÊä³öÁ÷ÖĞĞ´ÈëÒ»¸ö×Ö½Ú¡£
     void write(byte[]?b) £ºÍùÊä³öÁ÷ÖĞĞ´ÈëÊı×ébÖĞµÄËùÓĞ×Ö½Ú¡£
     void write(byte[]?b, int?off, int?len) £ºÍùÊä³öÁ÷ÖĞĞ´ÈëÊı×ébÖĞ´ÓÆ«ÒÆÁ¿off¿ªÊ¼µÄlen¸ö×Ö½ÚµÄÊı¾İ¡£
ÆäËü·½·¨
     void flush() £ºË¢ĞÂÊä³öÁ÷£¬Ç¿ÖÆ»º³åÇøÖĞµÄÊä³ö×Ö½Ú±»Ğ´³ö¡£
     void close() £º¹Ø±ÕÊä³öÁ÷£¬ÊÍ·ÅºÍÕâ¸öÁ÷Ïà¹ØµÄÏµÍ³×ÊÔ´¡£



//StreamTest.java
package myStream;

public class StreamTest {
	public static void main(String[] args) {
		int data;
		try{
			while((data=System.in.read())!=-1)//´Ó±ê×¼ÊäÈëÉè±¸»ñÈ¡ÊäÈëÁ÷
			{
				System.out.write(data);//Êä³öµ½±ê×¼Êä³öÉè±¸
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


»ù±¾µÄÁ÷Àà
FileInputStreamºÍFileOutputStream
    ½ÚµãÁ÷£¬ÓÃÓÚ´ÓÎÄ¼şÖĞ¶ÁÈ¡»òÍùÎÄ¼şÖĞĞ´Èë×Ö½ÚÁ÷¡£Èç¹ûÔÚ¹¹ÔìFileOutputStreamÊ±£¬ÎÄ¼şÒÑ¾­´æÔÚ£¬Ôò¸²¸ÇÕâ¸öÎÄ¼ş¡£
BufferedInputStreamºÍBufferedOutputStream
    ¹ıÂËÁ÷£¬ĞèÒªÊ¹ÓÃÒÑ¾­´æÔÚµÄ½ÚµãÁ÷À´¹¹Ôì£¬Ìá¹©´ø»º³åµÄ¶ÁĞ´£¬Ìá¸ßÁË¶ÁĞ´µÄĞ§ÂÊ¡£
DataInputStreamºÍDataOutputStream
      ¹ıÂËÁ÷£¬ĞèÒªÊ¹ÓÃÒÑ¾­´æÔÚµÄ½ÚµãÁ÷À´¹¹Ôì£¬Ìá¹©ÁË¶ÁĞ´JavaÖĞµÄ»ù±¾Êı¾İÀàĞÍµÄ¹¦ÄÜ¡£
PipedInputStreamºÍPipedOutputStream
    ¹ÜµÀÁ÷£¬ÓÃÓÚÏß³Ì¼äµÄÍ¨ĞÅ¡£Ò»¸öÏß³ÌµÄPipedInputStream¶ÔÏó´ÓÁíÒ»¸öÏß³ÌµÄPipedOutputStream¶ÔÏó¶ÁÈ¡ÊäÈë¡£ÒªÊ¹¹ÜµÀÁ÷ÓĞÓÃ£¬±ØĞëÍ¬Ê±¹¹Ôì¹ÜµÀÊäÈëÁ÷ºÍ¹ÜµÀÊä³öÁ÷¡£

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

ÀûÓÃÄÚ´æ»º³åÇøÀ´ÊµÏÖ£º
//StreamTest.java
package myStream;
import java.io.*;
public class StreamTest {
	public static void main(String[] args) {
		try{
			FileOutputStream fos=new FileOutputStream("1.txt");
			BufferedOutputStream bos = new BufferedOutputStream(fos);
			bos.write("http://zieckey.cubblog.cn".getBytes());
			bos.flush();	//Ğ´»áÓ²ÅÌ£¬ÕâÀïÒ²¿ÉÒÔÀûÓÃ	bos.close();£¬µ«ÊÇËûÃÇÊÇÓĞÇø±ğµÄ
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

DataInputStreamºÍDataOutputStream
      ¹ıÂËÁ÷£¬ĞèÒªÊ¹ÓÃÒÑ¾­´æÔÚµÄ½ÚµãÁ÷À´¹¹Ôì£¬Ìá¹©ÁË¶ÁĞ´JavaÖĞµÄ»ù±¾Êı¾İÀàĞÍµÄ¹¦ÄÜ¡£
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


PipedInputStreamºÍPipedOutputStream
    ¹ÜµÀÁ÷£¬ÓÃÓÚÏß³Ì¼äµÄÍ¨ĞÅ¡£Ò»¸öÏß³ÌµÄPipedInputStream¶ÔÏó´ÓÁíÒ»¸öÏß³ÌµÄPipedOutputStream¶ÔÏó¶ÁÈ¡ÊäÈë¡£ÒªÊ¹¹ÜµÀÁ÷ÓĞÓÃ£¬±ØĞëÍ¬Ê±¹¹Ôì¹ÜµÀÊäÈëÁ÷ºÍ¹ÜµÀÊä³öÁ÷¡£

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

Java I/O¿âµÄÉè¼ÆÔ­Ôò
JavaµÄI/O¿âÌá¹©ÁËÒ»¸ö³Æ×öÁ´½ÓµÄ»úÖÆ£¬¿ÉÒÔ½«Ò»¸öÁ÷ÓëÁíÒ»¸öÁ÷Ê×Î²Ïà½Ó£¬ĞÎ³ÉÒ»¸öÁ÷¹ÜµÀµÄÁ´½Ó¡£ÕâÖÖ»úÖÆÊµ¼ÊÉÏÊÇÒ»ÖÖ±»³ÆÎªDecorator(×°ÊÎ)Éè¼ÆÄ£Ê½µÄÓ¦ÓÃ¡£
Í¨¹ıÁ÷µÄÁ´½Ó£¬¿ÉÒÔ¶¯Ì¬µÄÔö¼ÓÁ÷µÄ¹¦ÄÜ£¬¶øÕâÖÖ¹¦ÄÜµÄÔö¼ÓÊÇÍ¨¹ı×éºÏÒ»Ğ©Á÷µÄ»ù±¾¹¦ÄÜ¶ø¶¯Ì¬»ñÈ¡µÄ¡£
ÎÒÃÇÒª»ñÈ¡Ò»¸öI/O¶ÔÏó£¬ÍùÍùĞèÒª²úÉú¶à¸öI/O¶ÔÏó£¬ÕâÒ²ÊÇJava I/O¿â²»Ì«ÈİÒ×ÕÆÎÕµÄÔ­Òò£¬µ«ÔÚI/O¿âÖĞDecoratorÄ£Ê½µÄÔËÓÃ£¬¸øÎÒÃÇÌá¹©ÁËÊµÏÖÉÏµÄÁé»îĞÔ¡£

ReaderºÍWriter
Java³ÌĞòÓïÑÔÊ¹ÓÃUnicodeÀ´±íÊ¾×Ö·û´®ºÍ×Ö·û¡£
ReaderºÍWriterÕâÁ½¸ö³éÏóÀàÖ÷ÒªÓÃÀ´¶ÁĞ´×Ö·ûÁ÷¡£

//StreamTest.java
package myStream;
import java.io.*;
public class StreamTest {
	public static void main(String[] args) {
		try{
			FileOutputStream fos=new FileOutputStream("1.txt");
			OutputStreamWriter osw=new OutputStreamWriter(fos);
			BufferedWriter bw=new BufferedWriter(osw);
			bw.write("http://zieckey.cublog.cn");//Ğ´ÈëÊı¾İ
			bw.close();

			FileInputStream fis=new FileInputStream("1.txt");
			InputStreamReader isr=new InputStreamReader(fis);
			BufferedReader br=new BufferedReader(isr);
			System.out.println(br.readLine());//¶ÁÈ¡Êı¾İ²¢Êä³ö
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




×Ö·û¼¯µÄ±àÂëASCII(American Standard Code for Information Interchange£¬ÃÀ¹úĞÅÏ¢»¥»»±ê×¼´úÂë)£¬
ÊÇ»ùÓÚ³£ÓÃµÄÓ¢ÎÄ×Ö·ûµÄÒ»Ì×µçÄÔ±àÂëÏµÍ³¡£
ÎÒÃÇÖªµÀÓ¢ÎÄÖĞ¾­³£Ê¹ÓÃµÄ×Ö·û¡¢Êı×Ö·ûºÅ±»¼ÆËã»ú´¦ÀíÊ±¶¼ÊÇÒÔ¶ş½øÖÆÂëµÄĞÎÊ½³öÏÖµÄ¡£
ÕâÖÖ¶ş½øÖÆÂëµÄ¼¯ºÏ¾ÍÊÇËùÎ½µÄASCIIÂë¡£Ã¿Ò»¸öASCIIÂëÓëÒ»¸ö8Î»£¨bit£©¶ş½øÖÆÊı¶ÔÓ¦¡£
Æä×î¸ßÎ»ÊÇ0£¬ÏàÓ¦µÄÊ®½øÖÆÊıÊÇ0-127¡£Èç£¬Êı×Ö¡°0¡±µÄ±àÂëÓÃÊ®½øÖÆÊı±íÊ¾¾ÍÊÇ48¡£
ÁíÓĞ128¸öÀ©Õ¹µÄASCIIÂë£¬×î¸ßÎ»¶¼ÊÇ1£¬ÓÉÒ»Ğ©ÖÆ±í·ûºÍÆäËü·ûºÅ×é³É¡£
ASCIIÊÇÏÖ½ñ×îÍ¨ÓÃµÄµ¥×Ö½Ú±àÂëÏµÍ³¡£
GB2312£ºGB2312ÂëÊÇÖĞ»ªÈËÃñ¹²ºÍ¹ú¹ú¼Òºº×ÖĞÅÏ¢½»»»ÓÃ±àÂë£¬È«³Æ¡¶ĞÅÏ¢½»»»ÓÃºº×Ö±àÂë×Ö·û¼¯£­»ù±¾¼¯¡·¡£
Ö÷ÒªÓÃÓÚ¸øÃ¿Ò»¸öÖĞÎÄ×Ö·ûÖ¸¶¨ÏàÓ¦µÄÊı×Ö£¬Ò²¾ÍÊÇ½øĞĞ±àÂë¡£
Ò»¸öÖĞÎÄ×Ö·ûÓÃÁ½¸ö×Ö½ÚµÄÊı×ÖÀ´±íÊ¾£¬ÎªÁËºÍASCIIÂëÓĞËùÇø±ğ£¬½«ÖĞÎÄ×Ö·ûÃ¿Ò»¸ö×Ö½ÚµÄ×î¸ßÎ»ÖÃ¶¼ÓÃ1À´±íÊ¾¡£
GBK£ºÎªÁË¶Ô¸ü¶àµÄ×Ö·û½øĞĞ±àÂë£¬¹ú¼ÒÓÖ·¢²¼ÁËĞÂµÄ±àÂëÏµÍ³GBK(GBKµÄKÊÇ¡°À©Õ¹¡±µÄººÓïÆ´ÒôµÚÒ»¸ö×ÖÄ¸)¡£
ÔÚĞÂµÄ±àÂëÏµÍ³Àï£¬³ıÁËÍêÈ«¼æÈİGB2312 Íâ£¬»¹¶Ô·±ÌåÖĞÎÄ¡¢Ò»Ğ©²»³£ÓÃµÄºº×ÖºÍĞí¶à·ûºÅ½øĞĞÁË±àÂë¡£
ISO-8859-1£ºÊÇÎ÷·½¹ú¼ÒËùÊ¹ÓÃµÄ×Ö·û±àÂë¼¯£¬ÊÇÒ»ÖÖµ¥×Ö½ÚµÄ×Ö·û¼¯ £¬¶øÓ¢ÎÄÊµ¼ÊÉÏÖ»ÓÃÁËÆäÖĞÊı×ÖĞ¡ÓÚ128µÄ²¿·Ö¡£


Unicode£ºÕâÊÇÒ»ÖÖÍ¨ÓÃµÄ×Ö·û¼¯£¬¶ÔËùÓĞÓïÑÔµÄÎÄ×Ö½øĞĞÁËÍ³Ò»±àÂë£¬¶ÔÃ¿Ò»¸ö×Ö·û¶¼ÓÃ2¸ö×Ö½ÚÀ´±íÊ¾£¬
¶ÔÓÚÓ¢ÎÄ×Ö·û²ÉÈ¡Ç°Ãæ¼Ó¡°0¡±×Ö½ÚµÄ²ßÂÔÊµÏÖµÈ³¤¼æÈİ¡£Èç ¡°a¡± µÄASCIIÂëÎª0x61£¬UNICODE¾ÍÎª0x00£¬0x61¡£
UTF-8£ºEight-bit UCS Transformation Format£¬
(UCS£¬Universal Character Set£¬Í¨ÓÃ×Ö·û¼¯£¬UCS ÊÇËùÓĞÆäËû×Ö·û¼¯±ê×¼µÄÒ»¸ö³¬¼¯)¡£
Ò»¸ö7Î»µÄASCIIÂëÖµ£¬¶ÔÓ¦µÄUTFÂëÊÇÒ»¸ö×Ö½Ú¡£
Èç¹û×Ö·ûÊÇ0x0000£¬»òÔÚ0x0080Óë0x007fÖ®¼ä£¬¶ÔÓ¦µÄUTFÂëÊÇÁ½¸ö×Ö½Ú£¬
Èç¹û×Ö·ûÔÚ0x0800Óë0xffffÖ®¼ä£¬¶ÔÓ¦µÄUTFÂëÊÇÈı¸ö×Ö½Ú¡£


²é¿´µ±Ç°ÏµÍ³Ö§³ÖµÄ×Ö·û¼¯£º
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

ÁĞ³öµ±Ç°ÏµÍ³ÊôĞÔ£º
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

ÉÏÃæµÄ file.encoding=GBK ¾ÍÊÇµ±Ç°ÏµÍ³µÄ×Ö·û¼¯Ä¬ÈÏ±àÂë



//CharsetTest.java
package myCharset;
import java.util.*;
import java.nio.charset.*;
public class CharsetTest {
	public static void main(String[] args) throws Exception {
		Properties pps=System.getProperties();
		pps.put("file.encoding","ISO-8859-1");//ÖØĞÂÉèÖÃµ±Ç°×Ö·û¼¯µÄ±àÂë±ê×¼
		int data;
		byte[] buf=new byte[100];
		int i=0;
		while((data=System.in.read())!='q')//ÊäÈëµÄ×Ö·ûÊÇÒÔISO-8859-1±àÂë×Ö½Ú´æ·ÅÔÚbufÖĞ,ÊäÈëq½áÊø
		{
			buf[i]=(byte)data;
			i++;
		}
		String str=new String(buf,0,i);
		System.out.println(str);//Êä³öÊÇÒÔµ±Ç°ÏµÍ³Ä¬ÈÏµÄ×Ö·û¼¯½âÂëµÄ£¬ÕâÀï¾ÍÊÇGBK

		//Í¨¹ıstr.getBytes("ISO-8859-1")ÖØĞÂ½âÂë£¬È»ºóÒÔGBK±àÂë
		String strGBK=new String(str.getBytes("ISO-8859-1"),"GBK");
		System.out.println(strGBK);//×îºóÒÔÄ¬ÈÏ±àÂë¸ñÊ½½âÂë£¬ÕâÑù¾ÍµÃµ½ÁËÕıÈ·µÄ½á¹û
	}
}
ÄãºÃ°¡q
ÄãºÃ°¡
???

ÕâÀïµÄ³ÌĞò½á¹ûÓëÔ¤ÏëµÄ²»Ò»ÖÂ.²»ÖªµÀÕâ¸öÊÇÊ²Ã´ÎÊÌâ?


InputStreamReader ÊÇ×Ö½ÚÁ÷Í¨Ïò×Ö·ûÁ÷µÄÇÅÁº£ºËüÊ¹ÓÃÖ¸¶¨µÄ charset ¶ÁÈ¡×Ö½Ú²¢½«Æä½âÂëÎª×Ö·û¡£ËüÊ¹ÓÃµÄ×Ö·û¼¯¿ÉÒÔÓÉÃû³ÆÖ¸¶¨»òÏÔÊ½¸ø¶¨£¬·ñÔò¿ÉÄÜ½ÓÊÜÆ½Ì¨Ä¬ÈÏµÄ×Ö·û¼¯¡£

OutputStreamWriter ÊÇ×Ö·ûÁ÷Í¨Ïò×Ö½ÚÁ÷µÄÇÅÁº£ºÊ¹ÓÃÖ¸¶¨µÄ charset ½«ÒªÏòÆäĞ´ÈëµÄ×Ö·û±àÂëÎª×Ö½Ú¡£ËüÊ¹ÓÃµÄ×Ö·û¼¯¿ÉÒÔÓÉÃû³ÆÖ¸¶¨»òÏÔÊ½¸ø¶¨£¬·ñÔò¿ÉÄÜ½ÓÊÜÆ½Ì¨Ä¬ÈÏµÄ×Ö·û¼¯¡£

String(byte[] bytes, int offset, int length)
          ¹¹ÔìÒ»¸öĞÂµÄ String£¬·½·¨ÊÇÊ¹ÓÃÖ¸¶¨µÄ×Ö·û¼¯½âÂë×Ö½ÚµÄÖ¸¶¨×ÓÊı×é¡£

Ã»¸ãÇå³ş×Ö·û¼¯µÄÎÊÌâ!!



RandomAccessFile Àà

RandomAccessFileÀàÍ¬Ê±ÊµÏÖÁËDataInputºÍDataOutput½Ó¿Ú£¬Ìá¹©ÁË¶ÔÎÄ¼şËæ»ú´æÈ¡µÄ¹¦ÄÜ£¬ÀûÓÃÕâ¸öÀà¿ÉÒÔÔÚÎÄ¼şµÄÈÎºÎÎ»ÖÃ¶ÁÈ¡»òĞ´ÈëÊı¾İ¡£
RandomAccessFileÀàÌá¹©ÁËÒ»¸öÎÄ¼şÖ¸Õë£¬ÓÃÀ´±êÖ¾Òª½øĞĞ¶ÁĞ´²Ù×÷µÄÏÂÒ»Êı¾İµÄÎ»ÖÃ¡£


¶ÔÎÄ¼ş½øĞĞ¶ÁĞ´¶¼ºÜ·½±ã¡£
¶ÔÎÄ¼ş²Ù×÷µÄÀı×Ó£º
//RandomAccessFileTest.java
import java.io.*;
class RandomAccessFileTest
{
	public static void main(String[] args) throws Exception
	{
		Student s1=new Student(200601,"zhangsan",88.5);
		Student s2=new Student(200602,"lisi",95);
		Student s3=new Student(200603,"wangwu",78);
		RandomAccessFile raf=new RandomAccessFile("student.txt","rw");//¹¹ÔìÒ»¸ö¿É¶ÁĞ´µÄÎÄ¼ş²Ù×÷¶ÔÏóRandomAccessFile
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
		raf.writeInt(num);//Ğ´ÈëÒ»¸öintÀàĞÍµÄÊı¾İµ½rafÏà¹ØµÄÎÄ¼şÖĞ
		raf.writeUTF(name);//ÒÔUTF-8¸ñÊ½Ğ´Èë×Ö·û´®µ½ÎÄ¼şÖĞ¡£
							//ÔÚ¿ªÊ¼Ğ´ÈëÊı¾İÇ°µÄÁ½¸ö×Ö½Ú¼ÇÂ¼ÁËÊµ¼ÊĞ´ÈëµÄÊı¾İµÄ×Ö½ÚÊı
		raf.writeDouble(score);
	}
}
E:\zieckey\Lesson9>javac RandomAccessFileTest.java

E:\zieckey\Lesson9>java RandomAccessFileTest

E:\zieckey\Lesson9>

Õâ¸öÊ±ºòÔÚE:\zieckey\Lesson9>Ä¿Â¼ÏÂ¶àÁËÒ»¸öÎÄ¼ş£ºstudent.txt
ÆäÄÚÈİÈçÏÂ£º
 ™ zhangsan@V       š lisi@WÀ      › wangwu@S€
¿ÉÒÔÓÃUltraEdit²é¿´¸ÃÎÄ¼ş£¬¶Ô±È¿´¿´Ğ´ÈëµÄÊı¾İ.

ÏÂÃæ¿´¿´ÈçºÎ¶ÁÈ¡ÎÄ¼şĞÅÏ¢:
//RandomAccessFileTest.java
import java.io.*;
class RandomAccessFileTest
{
	public static void main(String[] args) throws Exception
	{
		Student s1=new Student(200601,"zhangsan",88.5);
		Student s2=new Student(200602,"lisi",95);
		Student s3=new Student(200603,"wangwu",78);
		RandomAccessFile raf=new RandomAccessFile("student.txt","rw");//¹¹ÔìÒ»¸ö¿É¶ÁĞ´µÄÎÄ¼ş²Ù×÷¶ÔÏóRandomAccessFile
		s1.writeStudent(raf);
		s2.writeStudent(raf);
		s3.writeStudent(raf);//ÕâÀïÎÄ¼şÖ¸ÕëÒÑ¾­ÒÆ¶¯µ½ÎÄ¼şÄ©Î²

		Student s=new Student();
		raf.seek(0);//ÏÂÃæÒª¶ÁÈ¡Êı¾İ,¾ÍÒª½«ÎÄ¼şÖ¸ÕëÒÆ¶¯µ½ÎÄ¼ş¿ªÍ·
		for(long i=0;i<raf.length();i=raf.getFilePointer())
		{
			s.readStudent(raf);//Ã¿¶ÁÈ¡»òĞ´ÈëÒ»´ÎÊı¾İ,ÎÄ¼şÖ¸Õë¾ÍËæ×ÅÒÆ¶¯
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
		raf.writeInt(num);//Ğ´ÈëÒ»¸öintÀàĞÍµÄÊı¾İµ½rafÏà¹ØµÄÎÄ¼şÖĞ
		raf.writeUTF(name);//ÒÔUTF-8¸ñÊ½Ğ´Èë×Ö·û´®µ½ÎÄ¼şÖĞ¡£
							//ÔÚ¿ªÊ¼Ğ´ÈëÊı¾İÇ°µÄÁ½¸ö×Ö½Ú¼ÇÂ¼ÁËÊµ¼ÊĞ´ÈëµÄÊı¾İµÄ×Ö½ÚÊı
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

ÓëÎÒÃÇĞ´ÈëµÄĞÅÏ¢ÊÇÒ»ÑùµÄ.



¶ÔÏóĞòÁĞ»¯
½«¶ÔÏó×ª»»Îª×Ö½ÚÁ÷±£´æÆğÀ´£¬²¢ÔÚÈÕºó»¹Ô­Õâ¸ö¶ÔÏó£¬ÕâÖÖ»úÖÆ½Ğ×ö¶ÔÏóĞòÁĞ»¯¡£
½«Ò»¸ö¶ÔÏó±£´æµ½ÓÀ¾Ã´æ´¢Éè±¸ÉÏ³ÆÎª³ÖĞøĞÔ¡£
Ò»¸ö¶ÔÏóÒªÏëÄÜ¹»ÊµÏÖĞòÁĞ»¯£¬±ØĞëÊµÏÖSerializable½Ó¿Ú»òExternalizable½Ó¿Ú¡£

µ±Ò»¸ö¶ÔÏó±»ĞòÁĞ»¯Ê±£¬Ö»±£´æ¶ÔÏóµÄ·Ç¾²Ì¬³ÉÔ±±äÁ¿£¬²»ÄÜ±£´æÈÎºÎµÄ³ÉÔ±·½·¨ºÍ¾²Ì¬µÄ³ÉÔ±±äÁ¿¡£
Èç¹ûÒ»¸ö¶ÔÏóµÄ³ÉÔ±±äÁ¿ÊÇÒ»¸ö¶ÔÏó£¬ÄÇÃ´Õâ¸ö¶ÔÏóµÄÊı¾İ³ÉÔ±Ò²»á±»±£´æ¡£
Èç¹ûÒ»¸ö¿ÉĞòÁĞ»¯µÄ¶ÔÏó°üº¬¶ÔÄ³¸ö²»¿ÉĞòÁĞ»¯µÄ¶ÔÏóµÄÒıÓÃ£¬ÄÇÃ´Õû¸öĞòÁĞ»¯²Ù×÷½«»áÊ§°Ü£¬²¢ÇÒ»áÅ×³öÒ»¸öNotSerializableException¡£ÎÒÃÇ¿ÉÒÔ½«Õâ¸öÒıÓÃ±ê¼ÇÎªtransient£¬ÄÇÃ´¶ÔÏóÈÔÈ»¿ÉÒÔĞòÁĞ»¯¡£
//ObjectSerialTest.java
import java.io.*;
class ObjectSerialTest
{
	public static void main(String[] args) throws Exception
	{
		Employee e1=new Employee("zhangsan",25,3000.50);
		Employee e2=new Employee("lisi",24,3200.40);
		Employee e3=new Employee("wangwu",27,3800.55);

		//Ğ´ÈëĞòÁĞ»¯
		FileOutputStream fos=new FileOutputStream("employee.txt");
		ObjectOutputStream oos=new ObjectOutputStream(fos);
		oos.writeObject(e1);
		oos.writeObject(e2);
		oos.writeObject(e3);
		oos.close();

		//¶Á³öĞòÁĞ»¯
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

µ±Ò»¸ö¶ÔÏó±»ĞòÁĞ»¯Ê±£¬Ö»±£´æ¶ÔÏóµÄ·Ç¾²Ì¬³ÉÔ±±äÁ¿£¬²»ÄÜ±£´æÈÎºÎµÄ³ÉÔ±·½·¨ºÍ¾²Ì¬µÄ³ÉÔ±±äÁ¿¡£
Èç¹ûÒ»¸ö¶ÔÏóµÄ³ÉÔ±±äÁ¿ÊÇÒ»¸ö¶ÔÏó£¬ÄÇÃ´Õâ¸ö¶ÔÏóµÄÊı¾İ³ÉÔ±Ò²»á±»±£´æ¡£
Èç¹ûÒ»¸ö¿ÉĞòÁĞ»¯µÄ¶ÔÏó°üº¬¶ÔÄ³¸ö²»¿ÉĞòÁĞ»¯µÄ¶ÔÏóµÄÒıÓÃ£¬ÄÇÃ´Õû¸öĞòÁĞ»¯²Ù×÷½«»áÊ§°Ü£¬²¢ÇÒ»áÅ×³öÒ»¸öNotSerializableException¡£ÎÒÃÇ¿ÉÒÔ½«Õâ¸öÒıÓÃ±ê¼ÇÎªtransient£¬ÄÇÃ´¶ÔÏóÈÔÈ»¿ÉÒÔĞòÁĞ»¯¡£
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

Èç¹û½«Thread t=new Thread();ÉùÃ÷Îªtransient¾Í²»»á³öÏÖ´íÎó
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

µ±ÎÒÃÇÏë¶ÔĞòÁĞ»¯µÄĞÅÏ¢½øĞĞ¶îÍâµÄ´¦ÀíÀıÈç¼ÓÃÜµÈ²Ù×÷Ê±£¬ÎÒÃÇ±ØĞëÊµÏÖÈçÏÂÁ½·½·¨£º
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
		//Ã»ÓĞĞ´ÈëĞ½Ë®Öµ
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

ÕâÀïµÄ
 private void writeObject(java.io.ObjectOutputStream out)
     throws IOException
 private void readObject(java.io.ObjectInputStream in)
     throws IOException, ClassNotFoundException;
ÕâÁ½¸ö¾²Ì¬·½·¨ÊÇ¸öÌØÀı£¬ÔÚÀàµÄÍâ²¿¶¼¿ÉÒÔ±»µ÷ÓÃ¡£









×Ü½á
InputStreamºÍOutputStream£º×Ö½ÚÁ÷µÄÊäÈëÊä³ö¡£
ReaderºÍWriter£º×Ö·ûÁ÷µÄÊäÈëÊä³ö¡£
Á÷µÄÁ´½Ó(Java I/O¿âµÄÉè¼ÆÔ­Ôò)









Lesson10
Í¼ĞÎ½çÃæ¿ª·¢
AWT
AWT(Abstract Window Toolkit)£¬³éÏó´°¿Ú¹¤¾ß°ü£¬SUN¹«Ë¾Ìá¹©µÄÓÃÓÚÍ¼ĞÎ½çÃæ±à³Ì(GUI)µÄÀà¿â¡£»ù±¾µÄAWT¿â´¦ÀíÓÃ»§½çÃæÔªËØµÄ·½·¨ÊÇ°ÑÕâĞ©ÔªËØµÄ´´½¨ºÍĞĞÎªÎ¯ÍĞ¸øÃ¿¸öÄ¿±êÆ½Ì¨ÉÏ£¨Windows¡¢Unix¡¢MacintoshµÈ£©µÄ±¾µØGUI¹¤¾ß½øĞĞ´¦Àí¡£ÀıÈç£ºÈç¹ûÎÒÃÇÊ¹ÓÃAWTÔÚÒ»¸öJava´°¿ÚÖĞ·ÅÖÃÒ»¸ö°´Å¥£¬ÄÇÃ´Êµ¼ÊÉÏÊ¹ÓÃµÄÊÇÒ»¸ö¾ßÓĞ±¾µØÍâ¹ÛºÍ¸Ğ¾õµÄ°´Å¥¡£ÕâÑù£¬´ÓÀíÂÛÉÏÀ´Ëµ£¬ÎÒÃÇËù±àĞ´µÄÍ¼ĞÎ½çÃæ³ÌĞòÄÜÔËĞĞÔÚÈÎºÎÆ½Ì¨ÉÏ£¬×öµ½ÁËÍ¼ĞÎ½çÃæ³ÌĞòµÄ¿çÆ½Ì¨ÔËĞĞ¡£

²¼¾Ö¹ÜÀíÆ÷
ÈİÆ÷Àï×é¼şµÄÎ»ÖÃºÍ´óĞ¡ÊÇÓÉ²¼¾Ö¹ÜÀíÆ÷À´¾ö¶¨µÄ¡£ÈİÆ÷¶Ô²¼¾Ö¹ÜÀíÆ÷µÄÌØ¶¨ÊµÀı±£³ÖÒ»¸öÒıÓÃ¡£µ±ÈİÆ÷ĞèÒª¶¨Î»Ò»¸ö×é¼şÊ±£¬Ëü½«µ÷ÓÃ²¼¾Ö¹ÜÀíÆ÷À´Íê³É¡£µ±¾ö¶¨Ò»¸ö×é¼şµÄ´óĞ¡Ê±£¬Ò²ÊÇÈç´Ë¡£
ÔÚAWTÖĞ£¬¸øÎÒÃÇÌá¹©ÁËÎåÖÖ²¼¾Ö¹ÜÀíÆ÷£º
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
		myFrame.setSize( 640, 480 );//ÉèÖÃ´°¿Ú´óĞ¡
		myFrame.setLocation( 100, 100 );//ÉèÖÃ´°¿ÚÏÔÊ¾µÄÎ»ÖÃÎª£¨100£¬100£©
		myFrame.setBackground( Color.blue );//ÉèÖÃÑÕÉ«

		//´´½¨°´Å¥,²¢È·¶¨°´Å¥ÉÏÃæÏÔÊ¾µÄ×Ö·û´®
	    Button btn1=new Button("zieckey North");
	    Button btn2=new Button("zieckey South");
	    Button btn3=new Button("West");
	    Button btn4=new Button("East");
	    Button btn5=new Button("Center");

	    //½«°´Å¥Ìí¼Óµ½´°¿ÚÉÏ²¢È·¶¨ÔÚ´°¿ÚÉÏÏÔÊ¾µÄÎ»ÖÃ
	    myFrame.add( btn1,"North" );
	    myFrame.add( btn2,"South" );
	    myFrame.add( btn3,"West" );
	    myFrame.add( btn4,"East" );
	    myFrame.add( btn5,"Center" );

	    myFrame.setVisible( true );//ÏÔÊ¾´°¿Ú

	}
}

ÔÚ´°¿ÚÉÏ¶«¡¢ÄÏ¡¢Î÷¡¢±±¡¢ÖĞ·Ö±ğÏÔÊ¾ÁË5¸ö°´Å¥£¬
ÖĞ¼äµÄ°²Å¤³¤¿í´óĞ¡¶¼¿É±ä£¬ÄÏ±±µÄ¸ß¶ÈÊ¼ÖÕ²»±ä£¬×óÓÒµÄ¿í¶ÈÊ¼ÖÕ²»±ä
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
		myFrame.setSize( 640, 480 );//ÉèÖÃ´°¿Ú´óĞ¡
		myFrame.setLocation( 100, 100 );//ÉèÖÃ´°¿ÚÏÔÊ¾µÄÎ»ÖÃÎª£¨100£¬100£©
		myFrame.setBackground( Color.blue );//ÉèÖÃÑÕÉ«

		myFrame.setLayout(new BorderLayout(10,10));//ÖØĞÂÉèÖÃ²¼¾Ö¹ÜÀíÆ÷

		//´´½¨°´Å¥,²¢È·¶¨°´Å¥ÉÏÃæÏÔÊ¾µÄ×Ö·û´®
	    Button btn1=new Button("zieckey North");
	    Button btn2=new Button("zieckey South");
	    Button btn3=new Button("West");
	    Button btn4=new Button("East");
	    Button btn5=new Button("Center");

	    //½«°´Å¥Ìí¼Óµ½´°¿ÚÉÏ²¢È·¶¨ÔÚ´°¿ÚÉÏÏÔÊ¾µÄÎ»ÖÃ
	    myFrame.add( btn1,"North" );
	    myFrame.add( btn2,"South" );
	    myFrame.add( btn3,"West" );
	    myFrame.add( btn4,"East" );
	    myFrame.add( btn5,"Center" );
	    myFrame.setVisible( true );//ÏÔÊ¾´°¿Ú
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
		myFrame.setSize( 640, 480 );//ÉèÖÃ´°¿Ú´óĞ¡
		myFrame.setLocation( 100, 100 );//ÉèÖÃ´°¿ÚÏÔÊ¾µÄÎ»ÖÃÎª£¨100£¬100£©
		myFrame.setBackground( Color.blue );//ÉèÖÃÑÕÉ«

		//myFrame.setLayout(new FlowLayout(FlowLayout.LEFT));//ÖØĞÂÉèÖÃ²¼¾Ö¹ÜÀíÆ÷
		//myFrame.setLayout(new BorderLayout(10,10));
		myFrame.setLayout(new GridLayout(3,2,10,10));

		//´´½¨°´Å¥,²¢È·¶¨°´Å¥ÉÏÃæÏÔÊ¾µÄ×Ö·û´®
	    Button btn1=new Button("zieckey North");
	    Button btn2=new Button("zieckey South");
	    Button btn3=new Button("West");
	    Button btn4=new Button("East");
	    Button btn5=new Button("Center");

	    //½«°´Å¥Ìí¼Óµ½´°¿ÚÉÏ²¢È·¶¨ÔÚ´°¿ÚÉÏÏÔÊ¾µÄÎ»ÖÃ
	    myFrame.add( btn1,"North" );
	    myFrame.add( btn2,"South" );
	    myFrame.add( btn3,"West" );
	    myFrame.add( btn4,"East" );
	    myFrame.add( btn5,"Center" );
	    myFrame.setVisible( true );//ÏÔÊ¾´°¿Ú
	}
}


AWTÊÂ¼şÄ£ĞÍ
Events(ÊÂ¼ş)£ºÃèÊö·¢ÉúÁËÊ²Ã´µÄ¶ÔÏó¡£
Event source(ÊÂ¼şÔ´)£ºÊÂ¼şµÄ²úÉúÆ÷¡£
Event handlers(ÊÂ¼ş´¦ÀíÆ÷)£º½ÓÊÕÊÂ¼ş¶ÔÏó¡¢½âÊÍÊÂ¼ş¶ÔÏó²¢´¦ÀíÓÃ»§½»»¥µÄ·½·¨¡£
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
		myFrame.setSize( 640, 480 );//ÉèÖÃ´°¿Ú´óĞ¡
		myFrame.setLocation( 100, 100 );//ÉèÖÃ´°¿ÚÏÔÊ¾µÄÎ»ÖÃÎª£¨100£¬100£©
		myFrame.setBackground( Color.blue );//ÉèÖÃÑÕÉ«

		//myFrame.setLayout(new FlowLayout(FlowLayout.LEFT));//ÖØĞÂÉèÖÃ²¼¾Ö¹ÜÀíÆ÷
		//myFrame.setLayout(new BorderLayout(10,10));
		myFrame.setLayout(new GridLayout(3,2,10,10));

		//´´½¨°´Å¥,²¢È·¶¨°´Å¥ÉÏÃæÏÔÊ¾µÄ×Ö·û´®
	    Button btn1=new Button("zieckey North");
	    Button btn2=new Button("zieckey South");
	    Button btn3=new Button("West");
	    Button btn4=new Button("East");
	    Button btn5=new Button("Center");

	    //½«°´Å¥Ìí¼Óµ½´°¿ÚÉÏ²¢È·¶¨ÔÚ´°¿ÚÉÏÏÔÊ¾µÄÎ»ÖÃ
	    myFrame.add( btn1,"North" );
	    myFrame.add( btn2,"South" );
	    myFrame.add( btn3,"West" );
	    myFrame.add( btn4,"East" );
	    myFrame.add( btn5,"Center" );

	    myFrame.addWindowListener( new MyWindowListener() );//Ìí¼ÓÒ»¸öÊÂ¼ş¼àÌıÆ÷

	    myFrame.setVisible( true );//ÏÔÊ¾´°¿Ú
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

ÕâÀïÎªÁËÊµÏÖÒ»¸ö³ÌĞòÍË³ö¹¦ÄÜ£¬ÒªÊµÏÖWindowListener½Ó¿Ú£¬
ÕæµÄºÜÂé·³¡£

ÎÒÃÇ¿ÉÒÔ´Ó WindowAdapter ÅÉÉúÒ»¸öÀà£¬È»ºóÊµÏÖÎÒÃÇĞèÒªµÄ¹¦ÄÜ¾Í¿ÉÒÔÁË¡£
WindowAdapter ÀàÊµÏÖÁËËùÓĞWindowListener½Ó¿ÚµÄº¯Êı£¬µ«ÊÇËüÊÇ¿ÕÊµÏÖ¡£
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
		myFrame.setSize( 640, 480 );//ÉèÖÃ´°¿Ú´óĞ¡
		myFrame.setLocation( 100, 100 );//ÉèÖÃ´°¿ÚÏÔÊ¾µÄÎ»ÖÃÎª£¨100£¬100£©
		myFrame.setBackground( Color.blue );//ÉèÖÃÑÕÉ«

		//myFrame.setLayout(new FlowLayout(FlowLayout.LEFT));//ÖØĞÂÉèÖÃ²¼¾Ö¹ÜÀíÆ÷
		//myFrame.setLayout(new BorderLayout(10,10));
		myFrame.setLayout(new GridLayout(3,2,10,10));

		//´´½¨°´Å¥,²¢È·¶¨°´Å¥ÉÏÃæÏÔÊ¾µÄ×Ö·û´®
	    Button btn1=new Button("zieckey North");
	    Button btn2=new Button("zieckey South");
	    Button btn3=new Button("West");
	    Button btn4=new Button("East");
	    Button btn5=new Button("Center");

	    //½«°´Å¥Ìí¼Óµ½´°¿ÚÉÏ²¢È·¶¨ÔÚ´°¿ÚÉÏÏÔÊ¾µÄÎ»ÖÃ
	    myFrame.add( btn1,"North" );
	    myFrame.add( btn2,"South" );
	    myFrame.add( btn3,"West" );
	    myFrame.add( btn4,"East" );
	    myFrame.add( btn5,"Center" );

	    //myFrame.addWindowListener( new MyWindowListener() );//Ìí¼ÓÒ»¸öÊÂ¼ş¼àÌıÆ÷
	    myFrame.addWindowListener( new HisWindowListener() );//Ìí¼ÓÒ»¸öÊÂ¼ş¼àÌıÆ÷

	    myFrame.setVisible( true );//ÏÔÊ¾´°¿Ú
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

»òÕßÌí¼ÓÒ»¸öÄäÃûµÄÄÚ²¿Àà£º

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
		myFrame.setSize( 640, 480 );//ÉèÖÃ´°¿Ú´óĞ¡
		myFrame.setLocation( 100, 100 );//ÉèÖÃ´°¿ÚÏÔÊ¾µÄÎ»ÖÃÎª£¨100£¬100£©
		myFrame.setBackground( Color.blue );//ÉèÖÃÑÕÉ«

		//myFrame.setLayout(new FlowLayout(FlowLayout.LEFT));//ÖØĞÂÉèÖÃ²¼¾Ö¹ÜÀíÆ÷
		//myFrame.setLayout(new BorderLayout(10,10));
		myFrame.setLayout(new GridLayout(3,2,10,10));

		//´´½¨°´Å¥,²¢È·¶¨°´Å¥ÉÏÃæÏÔÊ¾µÄ×Ö·û´®
	    Button btn1=new Button("zieckey North");
	    Button btn2=new Button("zieckey South");
	    Button btn3=new Button("West");
	    Button btn4=new Button("East");
	    Button btn5=new Button("Center");

	    //½«°´Å¥Ìí¼Óµ½´°¿ÚÉÏ²¢È·¶¨ÔÚ´°¿ÚÉÏÏÔÊ¾µÄÎ»ÖÃ
	    myFrame.add( btn1,"North" );
	    myFrame.add( btn2,"South" );
	    myFrame.add( btn3,"West" );
	    myFrame.add( btn4,"East" );
	    myFrame.add( btn5,"Center" );

	    //myFrame.addWindowListener( new MyWindowListener() );//Ìí¼ÓÒ»¸öÊÂ¼ş¼àÌıÆ÷
	    //myFrame.addWindowListener( new HisWindowListener() );//Ìí¼ÓÒ»¸öÊÂ¼ş¼àÌıÆ÷
	    myFrame.addWindowListener(new WindowAdapter()
						        {
									  public void windowClosing(WindowEvent e)
									  {
									    System.exit(0);
									  }
						        });

	    myFrame.setVisible( true );//ÏÔÊ¾´°¿Ú
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
    btn1.addActionListener(new ActionListener() {//ÏìÓ¦Êó±êµã»÷ÊÂ¼şºó¸ü»»°´Å¥ÎÄ±¾
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
    Button btn1=new Button("ºÚÌÒA");
    Button btn2=new Button("ºìÌÒK");
    ActionListener al=new ActionListener()//ÊµÏÖÒ»¸ö·­ÅÆµÄĞ§¹û
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



²Ëµ¥À¸´´½¨£º
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

		// ÏìÓ¦¹Ø±Õ°´Å¥µÄĞÅºÅ
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

		// ÏìÓ¦ÍË³ö²Ëµ¥µÄÊÂ¼ş
		mi4.addActionListener ( new ActionListener ( )
			{
				public void actionPerformed ( ActionEvent arg0 )
				{
					System.exit ( 0 );
				}
			} );

		// ½«²Ëµ¥ÏîÌí¼Óµ½²Ëµ¥ÖĞ
		m1.add ( mi1 );
		m1.add ( mi2 );
		m1.add ( mi3 );
		m1.add ( mi4 );
		m2.add ( mi5 );
		m2.add ( mi6 );

		// ½«¸÷¸ö²Ëµ¥Ìí¼Óµ½²Ëµ¥À¸ÖĞ
		mb.add ( m1 );
		mb.add ( m2 );

		// ½«²Ëµ¥À¸Ìí¼Óµ½Ö÷´°¿ÚÖĞ
		f.setMenuBar ( mb );

		f.setVisible ( true );
	}
}

ÄäÃûÀàÒª·ÃÎÊ¾Ö²¿±äÁ¿£¬Òª½«Õâ¸ö±äÁ¿ÉùÃ÷Îªfinal

ÏìÓ¦²Ëµ¥Ïî£¬´ò¿ªÎÄ¼ş¶Ô»°¿ò£¬ÏÔÊ¾ÎÄ±¾µ½±à¼­ÇøÓò
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

		final TextArea ta = new TextArea();//¹¹ÔìÒ»¸öÊäÈëÇøÓò
		f.add ( ta );

		// ÏìÓ¦¹Ø±Õ°´Å¥µÄĞÅºÅ
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

		// ÏìÓ¦OpenÍË³ö²Ëµ¥µÄÊÂ¼ş
		mi2.addActionListener ( new ActionListener ( )
			{
				public void actionPerformed ( ActionEvent arg0 )
				{
					//¹¹ÔìÒ»¸ö´ò¿ªÎÄ¼ş¶Ô»°¿ò
					FileDialog fd = new FileDialog ( f,
							"zieckey Open File Dialog", FileDialog.LOAD );
					fd.setVisible ( true );//½«ÆäÏÔÊ¾³öÀ´

					//µÃµ½ÓÃ»§Ñ¡ÔñµÄÎÄ¼şÃûÈ«³Æ
					String fileName = fd.getDirectory ( ) +  fd.getFile ( ) ;
					if ( fileName != null )
					{
						try
						{
							FileInputStream fis=new FileInputStream(fileName);//¹¹ÔìÒ»¸öÎÄ¼şÊäÈëÁ÷
							byte[] buf=new byte[10*1024];
							int len=fis.read(buf);//¶ÁÈ¡Êı¾İµ½bufÖĞ
							ta.append ( new String(buf,0,len) );//½«bufÖĞÊı¾İÌí¼Óµ½ÎÄ±¾ÊäÈëÇøÓò
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

		// ÏìÓ¦ExitÍË³ö²Ëµ¥µÄÊÂ¼ş
		mi4.addActionListener ( new ActionListener ( )
			{
				public void actionPerformed ( ActionEvent arg0 )
				{
					System.exit ( 0 );
				}
			} );

		// ½«²Ëµ¥ÏîÌí¼Óµ½²Ëµ¥ÖĞ
		m1.add ( mi1 );
		m1.add ( mi2 );
		m1.add ( mi3 );
		m1.add ( mi4 );
		m2.add ( mi5 );
		m2.add ( mi6 );

		// ½«¸÷¸ö²Ëµ¥Ìí¼Óµ½²Ëµ¥À¸ÖĞ
		mb.add ( m1 );
		mb.add ( m2 );

		// ½«²Ëµ¥À¸Ìí¼Óµ½Ö÷´°¿ÚÖĞ
		f.setMenuBar ( mb );

		f.setVisible ( true );
	}
}


Lesson11
Applet

AppletÓÖ³ÆÎªJavaĞ¡Ó¦ÓÃ³ÌĞò£¬ÊÇÄÜ¹»Ç¶Èëµ½Ò»¸öHTMLÒ³ÃæÖĞ£¬²¢ÇÒ¿ÉÍ¨¹ıWebä¯ÀÀÆ÷ÏÂÔØºÍÖ´ĞĞµÄÒ»ÖÖJavaÀà ¡£
Applet²»ĞèÒªmain()·½·¨£¬ÓÉWebä¯ÀÀÆ÷ÖĞÄÚÇ¶µÄJavaĞéÄâ»úµ÷ÓÃÖ´ĞĞ¡£

ÒòÎªappletÊÇ´ÓÔ¶¶Ë·şÎñÆ÷ÉÏÏÂÔØ²¢ÇÒÔÚ±¾µØÖ´ĞĞ£¬ËùÒÔ°²È«ĞÔ¾ÍÏÔµÃ¸ñÍâÖØÒª¡£
Í¨¹ıÏŞÖÆappletÔÚÉ³Ïä(appletµÄÔËĞĞ»·¾³)ÖĞÔËĞĞ£¬±£Ö¤ÁË¶Ô±¾µØÏµÍ³¶øÑÔappletÊÇ°²È«µÄ¡£
appletÔÚÉ³ÏäÖĞÔËĞĞÊ±£º
¢Å²»ÄÜÔËĞĞÈÎºÎ±¾µØ¿ÉÖ´ĞĞ³ÌĞò£»
¢Æ³ıÁË´æ·ÅÏÂÔØµÄappletµÄ·şÎñÆ÷Íâ£¬applet²»ÄÜºÍÆäËüÖ÷»ú½øĞĞÍ¨ĞÅ¡£
¢Ç²»ÄÜ¶Ô±¾µØÎÄ¼şÏµÍ³½øĞĞ¶ÁĞ´¡£

AppletµÄÉúÃüÖÜÆÚ
init()£ºµ±ä¯ÀÀÆ÷¼ÓÔØapplet£¬½øĞĞ³õÊ¼»¯µÄÊ±ºòµ÷ÓÃ¸Ã·½·¨¡£
start()£ºÔÚinit()·½·¨Ö®ºóµ÷ÓÃ¡£µ±ÓÃ»§´ÓÆäËüÒ³Ãæ×ªµ½°üº¬appletµÄÒ³ÃæÊ±£¬¸Ã·½·¨Ò²±»µ÷ÓÃ¡£
stop()£ºÔÚÓÃ»§Àë¿ª°üº¬appletµÄÒ³ÃæÊ±±»µ÷ÓÃ¡£
destroy()£ºµ±applet²»ÔÙ±»Ê¹ÓÃ£¬»òä¯ÀÀÆ÷ÍË³öµÄÊ±ºò£¬¸Ã·½·¨±»µ÷ÓÃ¡£

paint()·½·¨
Applet±¾ÖÊÉÏÊÇÍ¼ĞÎ·½Ê½µÄ£¬ÎÒÃÇÓ¦¸ÃÔÚÍ¼ĞÎ»·¾³ÖĞ»æÖÆÎÒÃÇµÄÏÔÊ¾ÄÚÈİ¡£
ÎÒÃÇ¿ÉÒÔÍ¨¹ı´´½¨Ò»¸öpaint()·½·¨ÔÚAppletµÄpanelÉÏ»æÍ¼¡£Ö»ÒªAppletµÄÏÔÊ¾ĞèÒªË¢ĞÂ£¬paint()·½·¨¾Í»á±»ä¯ÀÀÆ÷»·¾³µ÷ÓÃ¡£ÀıÈç£¬µ±AppletµÄÏÔÊ¾³ß´ç·¢Éú±ä»¯µÄÊ±ºò£¬»òä¯ÀÀÆ÷´°¿Ú±»×îĞ¡»¯»ò±»ÒªÇóÒÔÍ¼±ê·½Ê½ÏÔÊ¾Ê±£¬ÕâÖÖµ÷ÓÃ¾Í»á·¢Éú¡£
ÎÒÃÇÓ¦¸Ã±àĞ´×Ô¼ºµÄpaint()·½·¨£¬ÒÔÊ¹ËüÔÚÈÎºÎÊ±ºò±»µ÷ÓÃ£¬¶¼ÄÜÕı³£µØ¹¤×÷¡£¶ÔËüµÄµ÷ÓÃÊÇÒì²½²úÉúµÄ£¬ÇÒÓÉAppletµÄÔËĞĞ»·¾³¶ø²»ÊÇ³ÌĞòÀ´Çı¶¯ ¡£
paint()·½·¨´øÓĞÒ»¸ö²ÎÊı£¬ËüÊÇjava.awt.GraphicsÀàµÄÒ»¸öÊµÀı¡£Õâ¸ö²ÎÊı×ÜÊÇ½¨Á¢¸ÃAppletµÄpanelµÄÍ¼ĞÎÉÏÏÂÎÄ£¬ÎÒÃÇ¿ÉÒÔÓÃÕâ¸öÍ¼ĞÎÉÏÏÂÎÄÔÚAppletÖĞ»æÍ¼»òĞ´ÈëÎÄ±¾¡£


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
	String strFont;//×ÖÌå
	public void init()
	{
		strFont=getParameter("font");//´ÓÍøÒ³ÖĞ»ñÈ¡¶¨ÒåµÄ×ÖÌåĞÅÏ¢
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
		//Font f=new Font("¿¬Ìå_GB2312",Font.BOLD,30);
		Font f=new Font(strFont,Font.BOLD,30);
		g.setFont(f);//ÉèÖÃ×ÖÌå
		g.setColor(Color.blue);//ÉèÖÃ×ÖÌåÑÕÉ«
		g.drawString("zieckeyÑ§Java",0,30);//ÔÚÍøÒ³ÉÏÏÔÊ¾ĞÅÏ¢
	}
}

/*ÕâÀïÊÇ½øĞĞhtmlÍøÒ³½øĞĞ²âÊÔÓÃµÄ
<applet code="TestApplet.class" width=600 height=400>
<param name="font" value="¿¬Ìå_GB2312">
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
	String strFont;//×ÖÌå
	int xOrigin,yOrigin;
	public void init()
	{
		//ÔÚAppletÖĞÊµÏÖÊó±ê»­Ïß¹¦ÄÜ
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
		strFont=getParameter("font");//´ÓÍøÒ³ÖĞ»ñÈ¡¶¨ÒåµÄ×ÖÌåĞÅÏ¢
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
		//Font f=new Font("¿¬Ìå_GB2312",Font.BOLD,30);
		Font f=new Font(strFont,Font.BOLD,30);
		g.setFont(f);//ÉèÖÃ×ÖÌå
		g.setColor(Color.blue);//ÉèÖÃ×ÖÌåÑÕÉ«
		g.drawString("zieckeyÑ§Java",0,30);//ÔÚÍøÒ³ÉÏÏÔÊ¾ĞÅÏ¢
	}
}

/*ÕâÀïÊÇ½øĞĞhtmlÍøÒ³½øĞĞ²âÊÔÓÃµÄ
<applet code="TestApplet.class" width=600 height=400>
<param name="font" value="¿¬Ìå_GB2312">
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
	String strFont;//×ÖÌå
	int xOrigin,yOrigin;
	public void init()
	{
		//Ìí¼ÓÒ»¸ö°´Å¥
		Button btn=new Button("Á´½Ó");
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

		//ÔÚAppletÖĞÊµÏÖÊó±ê»­Ïß¹¦ÄÜ
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
		strFont=getParameter("font");//´ÓÍøÒ³ÖĞ»ñÈ¡¶¨ÒåµÄ×ÖÌåĞÅÏ¢
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
		//Font f=new Font("¿¬Ìå_GB2312",Font.BOLD,30);
		Font f=new Font(strFont,Font.BOLD,30);
		g.setFont(f);//ÉèÖÃ×ÖÌå
		g.setColor(Color.blue);//ÉèÖÃ×ÖÌåÑÕÉ«
		g.drawString("zieckeyÑ§Java",0,30);//ÔÚÍøÒ³ÉÏÏÔÊ¾ĞÅÏ¢
	}
}
ÕâÀï×¢ÒâÒªÇå³ıÀàÔØÈë³ÌĞò¸ßËÙ»º´æ£¬´ò¿ªJava¿ØÖÆÌ¨£¬°´x¼ü¾Í¿ÉÒÔÁË
µ«ÊÇÕâÀïÃ»ÓĞÏñÏëÏóÖĞµÄÄÇÑù³öÏÖ°´Å¥¡£









Lesson12
ÍøÂç±à³Ì
»ùÓÚTCPµÄsocket±à³Ì
·şÎñÆ÷³ÌĞò±àĞ´£º
¢Ùµ÷ÓÃServerSocket(int port)´´½¨Ò»¸ö·şÎñÆ÷¶ËÌ×½Ó×Ö£¬²¢°ó¶¨µ½Ö¸¶¨¶Ë¿ÚÉÏ£»
¢Úµ÷ÓÃaccept()£¬¼àÌıÁ¬½ÓÇëÇó£¬Èç¹û¿Í»§¶ËÇëÇóÁ¬½Ó£¬Ôò½ÓÊÜÁ¬½Ó£¬·µ»ØÍ¨ĞÅÌ×½Ó×Ö¡£
¢Ûµ÷ÓÃSocketÀàµÄgetOutputStream()ºÍgetInputStream»ñÈ¡Êä³öÁ÷ºÍÊäÈëÁ÷£¬¿ªÊ¼ÍøÂçÊı¾İµÄ·¢ËÍºÍ½ÓÊÕ¡£
¢Ü×îºó¹Ø±ÕÍ¨ĞÅÌ×½Ó×Ö¡£
¿Í»§¶Ë³ÌĞò±àĞ´£º
¢Ùµ÷ÓÃSocket()´´½¨Ò»¸öÁ÷Ì×½Ó×Ö£¬²¢Á¬½Óµ½·şÎñÆ÷¶Ë£» 
¢Úµ÷ÓÃSocketÀàµÄgetOutputStream()ºÍgetInputStream»ñÈ¡Êä³öÁ÷ºÍÊäÈëÁ÷£¬¿ªÊ¼ÍøÂçÊı¾İµÄ·¢ËÍºÍ½ÓÊÕ¡£
¢Û×îºó¹Ø±ÕÍ¨ĞÅÌ×½Ó×Ö¡£

ÔÚEclipseÖĞÌí¼Ó²ÎÊıÔËĞĞ:
µãrun ±ßÉÏµÄÏÂÀ¬ï§Å¥ÔÙµãrun£¬È»ºóµãnew ÄãÒªÔËĞĞµÄÀà£¬mainÑ¡ºÃºó£¬µãmain±ßÉÏµÄArguments£¬
È»ºóÔÚProgram argumentsÀïĞ´ÉÏÄãÒª´øµÄ²ÎÊıºóÔÙÔËĞĞ¡£

ÏÂÃæÊÇÒ»¸ö×î¼òµ¥µÄTCPµÄsocketÓ¦ÓÃ³ÌĞò:

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
		if ( args.length > 0 ) // Èç¹ûÓĞ²ÎÊıÊäÈë¾ÍÆô¶¯·şÎñÆ÷³ÌĞò
			server ( );
		else
			// ·ñÔòÆô¶¯¿Í»§¶Ë½ø³Ì
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


ÈÃ·şÎñÆ÷´´½¨¶àÏß³ÌÎª¿Í»§¶Ë½øĞĞÁ¬½Ó:
// TestTCPConnection.java
package tcptest;

import java.net.*;
import java.io.*;

/**
 * Ò»¸ö¼òµ¥µÄ¶àÏß³Ì·şÎñÆ÷³ÌĞò
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
		if ( args.length > 0 ) // Èç¹ûÓĞ²ÎÊıÊäÈë¾ÍÆô¶¯·şÎñÆ÷³ÌĞò
			server ( );
		else
			// ·ñÔòÆô¶¯¿Í»§¶Ë½ø³Ì
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
				// ´´½¨Ò»¸öSocketµÈ´ı¿Í»§¶ËÁ¬½Ó
				Socket s = ss.accept ( );
				System.out.println ( "This is the " + count++
									+ "st client connetion!" );
				new TestTCPConnection ( s ).start ( );// Æô¶¯Ò»¸öÏß³ÌÎªÕâ¸ö¿Í»§¶Ë·şÎñ
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
			// ´´½¨Ò»¸öSocket
			Socket s = new Socket ( InetAddress.getByName ( null ), PORT );
			OutputStream os = s.getOutputStream ( );// Êä³öÁ÷
			InputStream is = s.getInputStream ( );// ÊäÈëÁ÷
			byte[] buf = new byte[100];
			int len = is.read ( buf );// ´ÓÊäÈëÁ÷ÖĞ¶ÁÈ¡Êı¾İµ½buf
			System.out.println ( new String ( buf, 0, len ) );
			// ÏòÊä³öÁ÷ÖĞĞ´ÈëÊı¾İ
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



Êı¾İ±¨UDP±à³Ì:

// TestTCPConnection.java
package tcptest;

import java.net.*;
/**
 * Ò»¸ö¼òµ¥µÄ¶àÏß³Ì·şÎñÆ÷³ÌĞò
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

	public static void recv ()//½ÓÊÕ·½°çÑİ·şÎñÆ÷
	{
		try
		{
			DatagramSocket ds = new DatagramSocket ( PORT );
			byte[] buf = new byte[100];
			DatagramPacket dp = new DatagramPacket ( buf, 100 );
			ds.receive ( dp );//µÈ´ıÊı¾İµÄµ½À´
			System.out.println ( new String ( buf, 0, dp.getLength ( ) ) );
			//½ÓÊÕµ½ĞÅÏ¢ºó»Ø¸´Ò»¸öÊı¾İ¸ø·¢ËÍ·½
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
			ds.send ( dp );//·¢ËÍÊı¾İµ½½ÓÊÕ·½
			byte[] buf = new byte[100];
			DatagramPacket dpRecv = new DatagramPacket ( buf, 100 );
			ds.receive ( dpRecv );//µÈ´ı½ÓÊÕ·½µÄ»ØÓ¦ĞÅÏ¢
			System.out.println ( new String ( buf, 0, dpRecv.getLength ( ) ) );
			ds.close ( );
		} catch ( Exception ex )
		{
			ex.printStackTrace ( );
		}
	}
}



Ğ´¸ö¼òµ¥µÄÍøÂçÏÂÔØ³ÌĞò:
package down;

import javax.swing.*;
import java.awt.event.*;
import java.io.*;
import java.net.*;

public class Download
{
	public static void main ( String[] args )
	{
		// ¹¹ÔìÒ»¸ö´°¿Ú
		JFrame jf = new JFrame ( "ÏÂÔØ³ÌĞò" );
		jf.setSize ( 600, 400 );
		jf.setLocation ( 100, 100 );
		JPanel p = new JPanel ( );// ¹¹ÔìÒ»¸öÃæ°å
		JLabel l = new JLabel ( "Please input URL:" );
		final JTextField tf = new JTextField ( 30 );
		p.add ( l );
		p.add ( tf );
		jf.getContentPane ( ).add ( p, "North" );// ½«Ãæ°åÌí¼Óµ½´°¿ÚÖĞ
		final JTextArea ta = new JTextArea ( );
		jf.getContentPane ( ).add ( ta, "Center" );
		JButton btn = new JButton ( "Download" );
		jf.getContentPane ( ).add ( btn, "South" );
		btn.addActionListener ( new ActionListener ( )// Ìí¼Ó°´Å¥ÏìÓ¦ĞÅÏ¢
					{
						public void actionPerformed ( ActionEvent e )
						{
							String str = tf.getText ( );
							try
							{
								URL url = new URL ( str );// »ñÈ¡µ½ÓÃ»§ÊäÈëµÄURL
								// ¶Ô¸ÃURLÁ¬½Ó
								URLConnection urlConn = url.openConnection ( );
								// »ñÈ¡ÓëÆ½Ì¨ÎŞ¹ØµÄĞĞ·Ö¸ô·û
								String line = System
										.getProperty ( "line.separator" );
								// µÃµ½¸ÃÁ¬½ÓµÄÖ÷»úIP
								ta.append ( "Host: " + url.getHost ( ) );
								ta.append ( line );
								// ¶Ë¿Ú
								ta.append ( "Port: " + url.getDefaultPort ( ) );
								ta.append ( line );
								//ÍøÒ³ÊôĞÔ
								ta.append ( "ContentType: "
										+ urlConn.getContentType ( ) );
								ta.append ( line );
								//ÍøÒ³Êı¾İ³¤¶È
								ta.append ( "ContentLength: "
										+ urlConn.getContentLength ( ) );
								//¹¹ÔìÒ»¸öÊäÈëÁ÷
								InputStream is = urlConn.getInputStream ( );
								//¹¹ÔìÒ»¸öÊä³öÁ÷,Ğ´ÈëÊı¾İµ½ÎÄ¼şÖĞ
								FileOutputStream fos = new FileOutputStream (
										"1.html" );

								int data;
								//ÒÔ×Ö½ÚÀ´¶ÁÈ¡Êı¾İ
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

























































































































































JavaÖĞÊ¹ÓÃMySQL´Ó°²×°¡¢ÅäÖÃµ½Êµ¼Ê³ÌĞò²âÊÔÏê½â

ÕâÀï¼ÙÉèÄãµÄJava¿ª·¢»·¾³ÒÑ¾­´î½¨ºÃÁË¡£

Ò»¡¢×¼±¸¹¤×÷£º

ÏÂÔØMySQL£ºmysql-5.0.27-win32.zip
ÏÂÔØMySQLµÄJDBC jar°ü£ºmysql-connector-java-5.0.3-bin.jar

¶ş¡¢°²×°ºÍ²âÊÔMySQL

	MySQLÔÚWindowsÏÂµÄ°²×°ºÜ¼òµ¥£¬×¢ÒâÔÚÑ¡ÔñÅäÖÃµÄÓĞÒ»ÏîÊÇ½«MySQLµÄÅäÖÃµ¼ÈëÏµÍ³»·¾³±äÁ¿ÖĞ£¬
ÎªÁËºóÃæµÄ·½±ãÕâ¸öÑ¡ÏîÒªÑ¡Ïî¡£
	°²×°Íêºó£¬ÏÂÃæ²âÊÔÏÂ£º
1. ÔËĞĞMySQL Server
M:\Documents and Settings\apple>mysqld-nt --help
mysqld-nt  Ver 5.0.22-community-nt for Win32 on ia32 (MySQL Community Edition (G
PL))
Copyright (C) 2000 MySQL AB, by Monty and others
This software comes with ABSOLUTELY NO WARRANTY. This is free software,
and you are welcome to modify and redistribute it under the GPL license

Starts the MySQL database server

Usage: mysqld-nt [OPTIONS]

For more help options (several pages), use mysqld --verbose --help

	ÕâÀï¿ÉÒÔ¿´µ½mysqld-nt.exeÊÇMySQL database server
ÎÒÃÇÔÙÔËĞĞ¿Í»§¶Ë½øĞĞÁ¬½Ó:

Èç¹ûÕâÀïËµÏµÍ³Ã»ÓĞÕâ¸ömysqld-ntÃüÁî£¬ÄÇÃ´ºÜ¿ÉÄÜÊÇMySQLµÄÅäÖÃĞÅÏ¢Ã»ÓĞµ¼ÈëÏµÍ³»·¾³±äÁ¿ÖĞ¡£Õâ¸öÊ±ºò¿ÉÒÔ½«MySQLµÄ°²×°Ä¿Â¼ÏÂbinÄ¿Â¼µ¼Èëµ½ÏµÍ³PATH»·¾³±äÁ¿ÖĞ£¬ÀıÈç£º
M:\WINDOWS\system32;M:\WINDOWS;M:\WINDOWS\System32\Wbem;M:\Program Files\MySQL\MySQL Server 5.0\bin
ÔÙÔËĞĞ mysqld-nt Ó¦¸Ã¾ÍÃ»ÓĞÎÊÌâÁË¡£

M:\Documents and Settings\apple>mysqld-nt

2.Á¬½ÓMYSQL¡£
¸ñÊ½£º mysql -hÖ÷»úµØÖ· -uÓÃ»§Ãû £­pÓÃ»§ÃÜÂë
Àı1£ºÁ¬½Óµ½±¾»úÉÏµÄMYSQL¡£
   Ê×ÏÈÔÚ´ò¿ªDOS´°¿Ú£¬È»ºó½øÈëÄ¿Â¼ mysqlbin£¬ÔÙ¼üÈëÃüÁîmysql -uroot -p£¬»Ø³µºóÌáÊ¾ÄãÊäÃÜÂë£¬Èç¹û¸Õ°²×°ºÃMYSQL£¬³¬¼¶ÓÃ»§rootÊÇÃ»ÓĞÃÜÂëµÄ£¬¹ÊÖ±½Ó»Ø³µ¼´¿É½øÈëµ½MYSQLÖĞÁË£¬MYSQLµÄÌáÊ¾·ûÊÇ£ºmysql>

   	M:\Documents and Settings\apple>mysql -uroot -p
	Enter password:
	Welcome to the MySQL monitor.  Commands end with ; or \g.
	Your MySQL connection id is 1 to server version: 5.0.22-community-nt

	Type 'help;' or '\h' for help. Type '\c' to clear the buffer.

	mysql>

Àı2£ºÁ¬½Óµ½Ô¶³ÌÖ÷»úÉÏµÄMYSQL¡£¼ÙÉèÔ¶³ÌÖ÷»úµÄIPÎª£º110.110.110.110£¬ÓÃ»§ÃûÎªroot,ÃÜÂëÎªabcd123¡£Ôò¼üÈëÒÔÏÂÃüÁî£º
  mysql -h110.110.110.110 -uroot -pabcd123
  £¨×¢:uÓëroot¿ÉÒÔ²»ÓÃ¼Ó¿Õ¸ñ£¬ÆäËüÒ²Ò»Ñù£©

3¡¢ÍË³öMYSQLÃüÁî£º exit £¨»Ø³µ£©
mysql> exit
Bye

M:\Documents and Settings\apple>

Èı¡¢ÔÚJavaÖĞÊ¹ÓÃMySQLÊı¾İ¿â
1. ×¼Êı¾İ¿âÎÄ¼ş
´´½¨Ò»¸öLearnJavaÊı¾İ¿â:
M:\Documents and Settings\apple>mysql -uroot -p
Enter password: ******
Welcome to the MySQL monitor.  Commands end with ; or \g.
Your MySQL connection id is 6 to server version: 5.0.22-community-nt

Type 'help;' or '\h' for help. Type '\c' to clear the buffer.

mysql> create database LearnJava;
Query OK, 1 row affected (0.02 sec)

´´½¨UserInfo±í¸ñ:
mysql> use LearnJava;
Database changed
mysql> create table UserInfo(
    -> UserName varchar (20) not null,
    -> UserPwd varchar (20) not null
    -> );
Query OK, 0 rows affected (0.06 sec)

mysql>
²åÈëÒ»ÌõÊı¾İ:
mysql> insert into UserInfo values ('zieckey','123456');
Query OK, 1 row affected (0.03 sec)

mysql>

2. ½«MySQLµÄJDBC jar°üµ¼ÈëÏµÍ³»·¾³ÖĞ
ÕâÀïÎÒÊÇ½«mysql-connector-java-5.0.3-bin.jar·ÅÔÚjavaµÄ°²×°Ä¿Â¼ÏÂ£¬
È»ºóµ¼Èëµ½CLASSPATH»·¾³±äÁ¿ÖĞ£¬ÀıÈç£º
.;%JAVA_HOME%\lib\tools.jar;%JAVA_HOME%\lib\mysql-connector-java-5.0.3-bin.jar;%JAVA_HOME%\lib\dt.jar;



3. ĞÂ½¨ Java ³ÌĞò QueryJDBC.java
/**
 *	¸Ã³ÌĞòÓÃÀ´²âÊÔJDBCºÍMySQLÁ¬½Ó
 */
package test;

import java.sql.*;

public class QueryJDBC
{
	static
	{
		try
		{
			//Çı¶¯ºÍodbc²»Í¬
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
			//Á¬½Ó²ÎÊıÓëAccess²»Í¬£¬ÕâÀïLearnJavaÊÇÉÏÃæ½¨Á¢µÄÊı¾İ¿âÃû
			String url = "jdbc:mysql://localhost/LearnJava";
			//½¨Á¢Á¬½Ó£¬rootÎªµÇÂ¼Êı¾İ¿âµÄÓÃ»§Ãû£¬123456ÎªÃÜÂë
			Connection con = DriverManager.getConnection ( url, "root", "123456'" );
			//½¨Á¢·¢ËÍSQLÃüÁîµÄStatement¶ÔÏó
			Statement stmt = con.createStatement ( );
			//·µ»Ø²éÑ¯½á¹û
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
			//¶Ï¿ªConnectionÁ¬½Ó
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

ÕâÀïÒªÌØ±ğÌáĞÑÒ»ÏÂ£¬Èç¹ûÔÚEclipseÏÂ½¨Á¢¹¤³ÌµÄ£¬
¸Ã³ÌĞòºÜ¿ÉÄÜÔËĞĞ³öÏÖÒì³££¬ÌáÊ¾ÕÒ²»µ½org.gjt.mm.mysql.Driver£¬
Õâ¸ö¿ÉÒÔÍ¨¹ı Project->Properties->Java Build Path->Libraries Ñ¡Ôñ Add Extenal JARs£¬
È»ºó¾Í¿ÉÒÔÑ¡ÔñµÚÈı·½jar°ü£ºmysql-connector-java-5.0.3-bin.jar
ÕâÑù³ÌĞò¾Í¿ÉÒÔÕı³£ÔËĞĞÁË¡£

Èç¹ûÔÚNetbeansÏÂ¿ª·¢µÄ»°£¬Ò²ÒªÌí¼ÓJAR°üµ½IDE»·¾³²ÅĞĞ£º
To use the Library Manager:
From the main menu, choose Tools > Library Manager.
In the Library Manager dialog box, click New Library.
In the New Library dialog box, name your library. Click OK.
Click Add JAR/Folder and browse to add the JAR file(s) needed for your classpath, source, or Javadoc.
In order for code completion to work properly in the IDE, you must either attach a complete set of source files as a folder or add the available source files as a Zip archive.

2007/1/18
¹ØÓÚÊµÏÖĞòÁĞ»¯µÄÀàÌáÊ¾Ã»ÓĞ¶¨ÒåserialVersionUIDÓò ·ÖÀà:Ä¬ÈÏÀ¸Ä¿
êPì¶EclipseµÄÌáÊ¾ The serializable class XXXXXX does not declare a static final serialVersionUID field of type long

²ÉÓÃ×Ô¶¯ĞŞ¸´£¬Eclipse»á×Ô¶¯¼ÓÉÏ£ºprivate static final long serialVersionUID = 1L;
¡¡¡¡ÆäÊµÕâ¸öÎÊÌâµ¹Ò²²»Ó°Ïì³ÌĞòµÄÔËĞĞ£¬µ«ÊÇÎÒ¿´µ½ProblemsÀïÃæÓĞ¾¯¸æ¾Í²»Êæ·ş£¬Í¬Ê±Ò²ËµÃ÷ÎÒÃÇĞ´µÄ´úÂë»¹ÊÇ²»¹æ·¶¡£²»ÅÂ£¬ÎÒÃÇÓĞ»¥ÁªÍø²é²éÊÇÔõÃ´»ØÊÂ£¬¾ßÌåµÄÔ­Òò»¹¾ÍÊÇºÍĞòÁĞ»¯ÖĞµÄÕâ¸öserialVersionUIDÓĞ¹Ø¡£
¡¡¡¡serialVersionUID ÓÃÀ´±íÃ÷ÀàµÄ²»Í¬°æ±¾¼äµÄ¼æÈİĞÔ.Èç¹ûÄãĞŞ¸ÄÁË´ËÀà, ÒªĞŞ¸Ä´ËÖµ. ·ñÔòÒÔÇ°ÓÃÀÏ°æ±¾µÄÀàĞòÁĞ»¯µÄÀà»Ö¸´Ê±»á³ö´í.
¡¡¡¡¿ÉÒÔÀûÓÃJDKµÄbinÄ¿Â¼ÏÂµÄserialver.exe¹¤¾ß²úÉúÕâ¸öserialVersionUID
¡¡¡¡¶ÔÓÚTest.class,Ö´ĞĞÃüÁî£º serialver Test
¡¡¡¡ÎªÁËÔÚ·´ĞòÁĞ»¯Ê±£¬È·±£Àà°æ±¾µÄ¼æÈİĞÔ£¬×îºÃÔÚÃ¿¸öÒªĞòÁĞ»¯µÄÀàÖĞ¼ÓÈëprivate static final long serialVersionUIDÕâ¸öÊôĞÔ£¬¾ßÌåÊıÖµ×Ô¼º¶¨Òå¡£ÕâÑù£¬¼´Ê¹Ä³¸öÀàÔÚÓëÖ®¶ÔÓ¦µÄ¶ÔÏóÒÑ¾­ĞòÁĞ»¯³öÈ¥ºó×öÁËĞŞ¸Ä£¬¸Ã¶ÔÏóÒÀÈ»¿ÉÒÔ±»ÕıÈ··´ĞòÁĞ»¯¡£·ñÔò£¬Èç¹û²»ÏÔÊ¾¶¨Òå¸ÃÊôĞÔ£¬Õâ¸öÊôĞÔÖµ½«ÓÉJVM¸ù¾İÀàµÄÏà¹ØĞÅÏ¢¼ÆËã£¬¶øĞŞ¸ÄºóµÄÀàµÄ¼ÆËã½á¹ûÓëĞŞ¸ÄÇ°µÄÀàµÄ¼ÆËã½á¹ûÍùÍù²»Í¬£¬´Ó¶øÔì³É¶ÔÏóµÄ·´ĞòÁĞ»¯ÒòÎªÀà°æ±¾²»¼æÈİ¶øÊ§°Ü¡£
¡¡¡¡²»ÏÔÊ¾¶¨ÒåÕâ¸öÊôĞÔÖµµÄÁíÒ»¸ö»µ´¦ÊÇ£¬²»ÀûÓÚ³ÌĞòÔÚ²»Í¬µÄJVMÖ®¼äµÄÒÆÖ²¡£ÒòÎª²»Í¬µÄ±àÒëÆ÷ÊµÏÖµÄ¸ÃÊôĞÔÖµµÄ¼ÆËã²ßÂÔ¿ÉÄÜ²»Í¬£¬´Ó¶øÔì³ÉËäÈ»ÀàÃ»ÓĞ¸Ä±ä£¬µ«ÊÇÒòÎªJVM²»Í¬£¬ÒÀÈ»»áÓĞÒòÀà°æ±¾²»¼æÈİ¶øÎŞ·¨ÕıÈ··´ĞòÁĞ»¯µÄÏÖÏó³öÏÖ¡£
¡¡¡¡ÒòÎªÎÒ×öµÄÏµÍ³²»Ì«»á¾­³£ĞèÒªĞòÁĞ»¯Àà£¬ËùÒÔÎªÁËÈ¥µôÕâĞ©¾¯¸æ£¬×öÈçÏÂÉèÖÃ£º
Window£­Preferences£­Java£¬ÈçÍ¼ËùÊ¾£¬½«serializable class without serialVersionUIDµÄÉèÖÃÓÉwarning¸ÄÎªIgnore¡£È»ºóEclipse»áÖØĞÂ±àÒë³ÌĞò£¬ÄÇĞ©¾¯¸æĞÅÏ¢Ò²¾Í»áÏûÊ§ÁË¡£
¡¡¡¡Ğ¡½á£ºÈç¹ûÎÒÃÇ¿ª·¢´óÁ¿ĞèÒªĞòÁĞ»¯µÄÀàµÄÊ±ºò£¬ÎÒÃÇ×îºÃ»¹ÊÇ»¹Ô­ÎªÔ­À´µÄÉèÖÃ¡£ÕâÑù¿ÉÒÔ±£Ö¤ÏµÍ³µÄĞÔÄÜºÍ½¡×³



ÎÒÓÃeclipseĞ´´øÍ¼Æ¬µÄ³ÌĞò,¹¤³ÌÀïÃæ²»ÊÇ×Ô¼º´øÓĞÒ»¸öresµÄÎÄ¼ş¼ĞÃ´,µ«ÊÇÎÒ°ÑÍ¼Æ¬·ÅÔÚÀïÃæ¾Í¶ÁÈ¡²»µ½,Òª·ÅÔÚ\verified\classes,ÀïÃæ,ÄÑµÀÒ»¶¨Òª¸úclassÎÄ¼ş·ÅÔÚÒ»ÆğÃ´??!!


NetbeansÊ¹ÓÃĞ¡¼¼ÇÉ

netbean °²×°Íê³Éºó´úÂë±à¼­´°¿ÚµÄÄ¬ÈÏ×ÖÌå¿´×Å²»ÊÇºÜÊæ·ş£¬¿ÉÒÔÍ¨¹ıTools->options->Editing->Editor Setting->Java(jsp,xml...) Editor->Fonts and ColorsĞŞ¸Ä£¬×ÖÌåĞŞ¸ÄÎªDialog Input,Size=11¾ÍºÃ¿´¶àÁË
netbean´úÂë±à¼­Æ÷Ö§³ÖËõĞ´£¬ÈçÊäÈësout»á×Ô¶¯×ª»»³ÉSystem.out.println("")£¬Ô¤¶¨ÒåµÄ¿ì½İ¼üºÍËõĞ´´úÂë¿ÉÒÔÔÚHelp->Keyboard Shortcuts Card²é¿´£¬Ò²¿ÉÒÔÍ¨¹ıTools->options->Editing->Editor Setting->Java(jsp,xml...) Editor->AbbreviationsÔö¼Ó»òĞŞ¸Ä
netbeanÀïjava´úÂë×Ô¶¯Íê³ÉÌáÊ¾¹ı³ÌÖĞÊäÈë×Ö·ûÄ¬ÈÏÊÇ´óĞ¡Ğ´Ãô¸ĞµÄ£¬ÓÃ¹ßJbuilderµÄ¿ÉÄÜºÜ²»Êæ·ş£¬¿ÉÒÔÍ¨¹ıTools->options->Editing->Editor Setting->Java Editor->Expert->Case Sensitive Code CompletionĞŞ¸Ä£¬°Ñ¹´Ñ¡È¥µô¾Í¿ÉÒÔ²»Çø·Ö´óĞ¡Ğ´ÁË
netbeans»á¸ù¾İJSPÍ·²¿µÄpageÖ¸¶¨×Ô¶¯Ê¶±ğJSP±àÂë£¬ËùÒÔÈç¹ûJSPÏ£ÍûÊ¹ÓÃUTF-8±àÂëÖ»ĞèÔÚJSPÎÄ¼şÒ»¿ªÊ¼¼ÓÉÏ<%@ page contentType="text/html;charset=UTF-8"%>»ò<%@page pageEncoding="UTF-8"%>£¨JSP1.2£©¼´¿É
javaÎÄ¼ş±àÂëÄ¬ÈÏÊ¹ÓÃÏµÍ³±àÂë£¬¿ÉÒÔÍ¨¹ıjavaÎÄ¼şpropertiesÀïµÄText->Encodingµ¥¸öĞŞ¸Ä£¬Ò²¿ÉÒÔÍ¨¹ıTools->options->Editing->Java Sources->Expert->Default EncodingÍ³Ò»ĞŞ¸Ä
More...

netbean´úÂë×Ô¶¯Íê³ÉµÄ¿ì½İ¼üÄ¬ÈÏµÄÊÇ£ºCtrl+\



JNI¹Ø¼ü´Ê:
access native methods

ÔÚJ2ME³ÌĞòÖĞ£¬ÓÀÔ¶¶¼ÎŞ·¨Ö±½Óµ÷ÓÃ±¾µØ¿âº¯Êı£¬ÒòÎªJavaµÄ±¾µØµ÷ÓÃÍ¨³£ÓĞÁ½ÖÖ·½Ê½£º  
   
  Ò»ÊÇJNI£¬µ«J2MEÃ÷È·µØ²»Ö§³ÖJNI£»  
   
 ¶şÊÇKNI£¬µ«Ê¹ÓÃKNIµÄ»°£¬ÄãµÄ±¾µØº¯Êı²»ÊÇ·ÅÔÚ¶¯Ì¬Á´½Ó¿âÀï£¬¶øÊÇÒª±àµ½ĞéÄâ»úµÄÄÚ²¿£¬ÎÒÏëÒ»°ãÇé¿öÏÂÊÇÃ»»ú»áĞŞ¸ÄĞéÄâ»úµÄ°É£¬¸üºÎ¿ö£¬ÄãËùÓÃµÄĞéÄâ»ú»¹ÓĞ¿ÉÄÜ²¢²»Ö§³ÖKNI£¬KNI×î³õÖ»ÊÇKVM×¨ÓÃµÄ£¬ºóÀ´ÓĞÒ»Ğ©ĞéÄâ»úÒ²ÓÃ£¬µ«²»ÊÇÈ«²¿¡£  
   
  Èç¹ûÄã¶ÔKNI¸ĞĞËÈ¤µÄ»°£¬»¶Ó­²Î¹ÛÒ»ÏÂÎÒµÄblog£¬Ò²ĞíÓĞÒ»µã°ïÖú£º  
  http://blog.csdn.net/fyzhao/archive/2006/08/28/1134113.aspx
  
  
J2ME/CDC applications can access native methods through the JNI (Java Native Interface) framework. The CLDC does not support JNI. For security reasons, CLDC applications are not allowed to access native methods. For CLDC, device vendors must build any native features into the runtime [3].  














http://community.polarion.com/projects/subversive/download/eclipse/2.0/builds/

http://www.pin5i.com/showtopic-23178.html

ÕÛÌÚÁËºÃ¾Ã£¬ÖÕÓÚ¸ã¶¨subversiveºÍsvn connectorµÄ°²×°ÁË£¬¹ı³ÌºÜÍ´¿à£¬ÒòÎªeclipseµÄÔÚÏß°²×°ÊµÔÚÊÇÌ«ÂıÁË......
    
    ×îºóÎÒµÄ×Ü½á¾ÍÊÇ²»ÒªÖ±½Ó´ÓÍøÉÏ°²×°£¬Ì«ÂıÌ«Âı£¬»áÍÂÑª¶øÍöµÄ£¬ÎÒÒÑ¾­Éî¿ÌÁìÂÔÁË......
    
    ÕıÈ·µÄ·½·¨ÊÇÏÈ´Ó¹Ù·½ÍøÕ¾ÉÏÏÂÔØ°²×°°ü£¬È»ºóÔÙÓÃeclipseµÄsoftware update¹¤¾ß°²×°£¬ÕâÑùËÙ¶È¾ÍºÜ¿ì¡£ÎÒµÄ1mµÄadsl£¬Èç¹ûÖ±½ÓÍøÉÏ°²×°£¬´ó¸Å1kÏÂÔØËÙ¶È£¬Ö±½ÓhttpÏÂÔØ°²×°°ü£¬´ó¸ÅÔÚ50-100kÖ®¼ä£¬²î±ğ¹»´ó°É£¿
    
    ¾ßÌå²½ÖèÈçÏÂ£º

1. ÏÂÔØsubversive

    
    ½øÈëÕâ¸öÍøÖ· http://www.eclipse.org/subversive/downloads.php£¬ ÕÒµ½Latest Release - Recommended ÔÚ Subversive plug-in - [required]ÏÂÕÒµ½
    
        Archived Update Site: Subversive-incubation-0.7.7.I20090224-1900.zip
    
    £¨ÇëÎŞÊÓÅÑ±äµÄÔÚÏß¸üĞÂµØÖ· Update Site: http://download.eclipse.org/tech ... ve/0.7/update-site/£©
    
    µãÁ´½Ó½«Õâ¸öSubversive-incubation-0.7.7.I20090224-1900.zipÎÄ¼şÏÂÔØÏÂÀ´£¬¾ßÌåµÄµØÖ·ÊÇ£º
    
    http://www.eclipse.org/downloads ... .I20090224-1900.zip
    
    ´óĞ¡´ó¸ÅÊÇ17M¡£
    
2. ÏÂÔØsvn connector

    ÔÚ¸Õ²ÅÉÏÃæµÄÁ´½ÓÏÂ·½£¬ÓĞsvn connectorµÄËµÃ÷£¬¸ø³öÏÂÔØµØÖ·
    
    http://www.polarion.com/products ... ?src=eclipseproject
    
    ÔÚÕâÀïÕÒµ½Subversive Connector Archives£¬ÓĞÁ´½ÓÖ¸Ïò°²×°°ü£¬½«ËüÏÂÔØÏÂÀ´£¬¾ßÌåµØÖ·ÊÇ£º
    
    http://www.polarion.org/projects ... .I20090213-1500.zip
    
    Õâ¸ö°ü18M¡£
    
    ÉÏÃæÁ½¸ö°ü¼ÓÆğÀ´35m£¬ÎÒ²»ÖªµÀ1kµÄËÙ¶ÈÒªÏÂÔØ¶à¾Ã......
    
3. °²×°subversive

    eclispe -> software updates -> available software -> Manage Sites
    Ê×ÏÈÈ¡ÏûËùÓĞsite£¬·ñÔòeclipse»¹ÊÇÒªÈ¥¸üĞÂÒ»Ğ©¶«Î÷£¬ÔÚÎÒÕâÀïÏÂÔØµÄËÙ¶È´ó¸ÅÊÇ100×Ö½ÚÃ¿Ãë£¬ÏêÏ¸Çë¿´ÎÒµÄÉÏÒ»¸öÌû×Ó¡£
    È»ºóadd -> archive£¬Ö¸Ïò¸Õ²ÅÏÂÔØµÄSubversive-incubation-0.7.7.I20090224-1900.zipÎÄ¼ş£¬Ğ¡ĞÄaddÖ®ºósoftware updates¹¤¾ß»á×Ô¶¯¹´Ñ¡¼¸¸öeclipseµÄÕ¾µã£¬Ç§Íò¼Ç×¡ÔÙ´ÎÈ¡ÏûËûÃÇ£¬Ö»±£ÁôsubversiveÒ»¸ö¡£Ö®ºó¾ÍÒ»Â·Ë³Àû°²×°£¬Íê³Éºó»áÒªÇóÖØÆô¡£
    
4. °²×°svn connector

    ºÍÉÏÃæµÄ·½Ê½Ò»ÖÂ¡£
    ×¢ÒâÔÚÑ¡Ôñ°²×°ÄÚÈİÊ±£¬È«Ñ¡£¬ÎÒ¿ªÊ¼Ö»Ñ¡ÁËÒ»¸ösvn connector£¬½á¹û²»ÄÜÓÃ, subversiveµÄÉèÖÃÖĞÎŞ·¨Ñ¡Ôñconnector¡£ºóÀ´µÚ¶ş´Î°²×°Ê±È«Ñ¡¾ÍÄÜÓÃÁË¡£
    
5. ÉèÖÃsvn connector
    eclipse -> windows -> preferences -> team -> svn
    µãSVN Connector£¬È»ºóÑ¡ÔñÒ»¸öÒªÓÃµÄconnector£¬ÎÒÑ¡ÔñµÄÊÇSVN Kit(SVN/1.5.5 r5428)£¬apply.
    
    ÕâÑù¾ÍÍê³ÉÁËÕû¸öµÄ°²×°£¬ÎÒ²âÊÔ¹ı¿ÉÒÔÕı³£Á¬½Ósubversion·şÎñÆ÷¡£














Java NIO(New IO) »¹ÊÇÔÚ JDK 1.4 ÖĞÒıÈëµÄĞÂÌØĞÔ¡£JDK 1.4 µÄÁíÒ»ÖØÒªÌØĞÔÕıÔò±í´ïÊ½´ó¼ÒÓ¦¸Ã¾­³£ÓÃµ½£¬µ« NIO ¾Í¿ÉÄÜÊ¹ÓÃÁÈÁÈÁË£¬´ó¸ÅÊÇÔµÓÚ¾ÉÓĞ IO ÌåÏµÈÔÈ»¹»ÓÃ¡£ÓĞÈç JDK1.5 Ôç¾Í·ºĞÍºÍ×¢½âÁË£¬µ«»ùÓÚ¸÷ÖÖÔ­Òò¶øÎŞ·¨Ç×Á¦È¥Êµ¼ù·ºĞÍºÍ×¢½âÒ»°ã£¬NIO ¶àÊıÊ±ºòÒ²Ö»ÊÇÓëÎÒÃÇ²Á×Å¼ç¶øÒÑ¡££¨ÎÄ/¸ôÒ¶»Æİº£©

Ïà±ÈÓë Old IO£¬NIO ÔÚÄ³Ğ©ÁìÓòÀïÈ·ÓĞÆä¹ıÈËÖ®´¦£¬ËùÒÔÏÖÔÚÈÃÎÒÃÇÒ»ÆğÀ´¶Ô NIO ÓĞ¸ö¸ü³şµÄÈÏÊ¶¡£

NIO µÄÏà¹Ø API£¬ÔÚ java.nio ÖĞ£¬Ëü»áÓëÄã¾À²øµÄ¾ÍÊÇ¸÷ÖÖ Channel ºÍ Buffer¡£Ïà¹ØµÄÓ¦ÓÃÔÚÓÚ´¦ÀíÍ¨µÀºÍ»º³åÇø¡¢Òì²½(·Ç×èÈû)µÄ IO¡¢ÎÄ¼şµÄËø¶¨¡¢×Ö·û¼¯µÄ´¦ÀíÉÏ¡£

Channel ¿ÉÒÔÍ¨¹ıµ÷ÓÃ FileInputStream¡¢FileOutputStream¡¢RandomAccessFile¡¢DatagramSocket¡¢ ServerSocket ºÍ Socket µÄ getChannel() ·½·¨»ñµÃ¡£Channel ÓĞµãÏñ¾É I/O µÄÁ÷£¬¾É I/O µÄ¶ÁĞ´²Ù×÷¿ÉÒÔÔÚÁ÷ÉÏÖ±½Ó½øĞĞ£¬¶ø NIO ¶¼ÊÇÔÚ¸÷ÖÖ Buffer ÉÏ¶ÁĞ´Êı¾İ¡£

ÓÉÓÚÊ¹ÓÃÁË¶ÀÓĞµÄÍ¨µÀºÍ»º³åÇø£¬Ïà±È¾ÉÓĞµÄ IO Á÷´¦ÀíµÄÊÇ×Ö½ÚÁ÷(Á÷ IO)£¬NIO ËùÊ¹ÓÃµÄ·½Ê½ÊÇ¿é I/O£¬ËùÒÔÔÚ´ó¿éÊı¾İ´¦ÀíÊ±¿é I/O ±ÈÁ÷ I/O Ğ§ÂÊÒª¸ß¡£NIO ÔÚÒ»¶¨³Ì¶ÈÉÏÏàµ±ÓÚÓÃ±¾µØ´úÂëÀ´´¦ÀíÁË I/O ²Ù×÷¡£

Òì²½ I/O Ê¹µÃÄãÔÚ½øĞĞÍøÂç´«ÊäÊ±£¬ÎŞĞèÏñÔ­À´ÄÇÑù read()/write() À´×èÈûÏß³ÌÀ´µÈ´ıÊı¾İµÄµ½À´ºÍÖ±ÖÁĞ´ÍêÊı¾İ¡£NIO µÄ·½Ê½ÊÇ×¢²á¼àÌıÆ÷À´¼àÌıÍ¨µÀÉÏµÄÊÂ¼ş£¬ÔÚÒ»¸öÏß³ÌÉÏ¾ÍÄÜÁ÷³©µÄ´¦Àí Socket Í¨ĞÅ¡£²»Ïñ¾É I/O ±ØĞëÇóÖúÓÚÂÖÑ¯²¢´´½¨ĞíĞí¶à¶àµÄÏß³ÌÀ´´¦Àí´óÁ¿µÄÁ¬½Ó¡£

ÀıÈç£¬»ùÓÚ NIO µÄ×é¼şÓĞ£¬ÍøÂçÓ¦ÓÃ¿ò¼Ü Apache MINA£¬Memcached ¿Í»§¶Ë XMemcached£¬Socket Ó¦ÓÃ×é¼ş xSocket£¬»¹ÓĞ Tomcat 6 Ò²Ö§³ÖÊ¹ÓÃ NIO µÄ connector ÁË¡£

ÎÄ¼şËøÊ¹µÃ Java ³ÌĞòÒ²¿ÉÒÔ¶ÔÕû¸öÎÄ¼ş»òÎÄ¼şµÄ²¿·Ö½øĞĞ¶ÀÕ¼(ÅÅËü)»ò¹²ÏíµÄ¶Á»òĞ´£¬·ÀÖ¹ÁË²»Í¬µÄ½ø³Ì¶ÔÍ¬Ò»¸öÎÄ¼şµÄ¸ÉÈÅ¡£²»¹ıÔÚ²»Í¬µÄ×÷ÏµÍ³ÏÂµÄĞĞÎª¿ÉÄÜ»áÓĞÏ¸Î¢µÄ²îÒì¡£ÎÄ¼şËø(Lock)¿ÉÒÔÍ¨¹ı Channel µÄ lock() »ò tryLock() »ñµÃ£¬Channel µÄ release() ·½·¨»ò¹Ø±ÕÍ¨µÀÊ±¼´ÊÍ·ÅÁËËø¡£

ÁíÍâ£¬NIO ¿ÉÒÔ¸üºÃµÄÊ¹ÓÃ¿ØÖÆ×Ö·û¼¯¡£

Óë NIO »¹ÓĞÒ»¸öºÜÖØÒªµÄ Buffer ¾ÍÊÇÄÚ´æÓ³ÉäÎÄ¼ş--Í¨¹ıµ÷ÓÃ FileChannel ÀàµÄ map() ·½·¨¿É»ñµÃ MappedByteBuffer£¬´ËÄÚ´æÓ³ÉäÎÄ¼şÓë Windows ÏÂµÄÄÚ´æÓ³ÉäÓĞÏàËÆĞÔ£¬ÓÖ²»¾¡È»£¬Windows ÏÂµÄÄÚ´æÓ³ÉäÎÄ¼ş¿ÉÓÃÀ´ÔÚ²»Í¬µÄ½ø³Ì¼ä¹²ÏíÊı¾İ£¬Java µÄÕâ¸ö¶«Î÷ÒªÏ¸¾¿ÏÂ¡£

ÒÔÉÏ±¾¾ÍÊÇ·º·º¶øÓï£¬³õÊ¶Õß»ò»á¾õµÃ²»ÖªËùÔÆ£¬Ò²ÎŞÉõÎ¶¿É½â£¬Ô­±¾¾ÍÊÇ¶Ô Java NIO µÄ´ÖáîµÄÀí½â£¬ÔÓÂÒ¶øÎŞĞò¡£

ÔÚ IBM DeveloperWorks ÉÏÓĞÒ»¸ö Java NIO ÈëÃÅ½Ì³Ì£¬https://www6.software.ibm.com/developerworks/cn/education/java/j-nio/tutorial/index.html£¬ÎªÁË±ãÓÚÑ§Ï°ºÍ·ÖÏí£¬ÌØÖÆ×÷³ÉÁËÒ»¸ö chm ÎÄ¼ş£¬ÔÚÎÄÄ©ÓĞÏÂÔØ¡£

²Î¿¼×ÊÁÏ£º
1. »ùÓÚÊÂ¼şµÄNIO¶àÏß³Ì·şÎñÆ÷
2. Servlet API ºÍ NIO: ×îÖÕ×éºÏÔÚÒ»Æğ
3. Java NIOÔ­ÀíºÍÊ¹ÓÃ
4. Ê¹ÓÃJava NIO±àĞ´¸ßĞÔÄÜµÄ·şÎñÆ÷
5. Java NIO APIÏê½â
6. nioÎÄ¼ş¶ÁĞ´






¶ÔÓÚ NIO À´Ëµ£¬Channel(Í¨µÀ) ºÍ Buffer(»º³åÇø) ÕâÁ½¸ö¶«Î÷ÊÇ²»µÃ²»ÌáµÄ£¬ÒòÎªËüÃÇÊÇ NIO µÄºËĞÄ¶ÔÏó£¬¼¸ºõÃ¿Ò»¸ö I/O ²Ù×÷¶¼ÒªËüÃÇ¡£

Í¨µÀÊÇ¶ÔÔ­ I/O Á÷µÄÄ£Äâ£¬µ«ÓĞ²»Í¬µÄÊÇËüÊÇË«ÏòµÄ£¬²»ÔÙÏñÁ÷ÄÇÑù·Ö InputStream ºÍ OutputStream£¬Í¨µÀµÄË«ÏòĞÔ¸üºÃµÄ·´Ó³ÁËµ×²ã²Ù×÷ÏµÍ³µÄÕæÊ¶Çé¿ö¡£Ò²²»ÄÜÏñÔ­ I/O ÄÇÑù¿ÉÒÔÖ±½ÓÍùÁ÷ÀïĞ´»ò¶ÁÊı¾İ£¬ÔÚÍ¨µÀÁË´«ÊäÊı¾İ±ØĞë¾­ÓÉ»º³åÇø¡£ÓĞµãÀàËÆÔ­ I/O Á÷Í¨¹ı¹ıÂËÆ÷Á÷ BufferedInputStream ºÍ BufferedOutputStream À´¶ÁĞ´Êı¾İ¡£

FileInputStream/FileOutputStream/RandomAccessFile/DatagramSocket/ServerSocket/Socket µÄ getChannel() ·½·¨¿ÉÒÔ»ñµÃÏàÓ¦ÀàĞÍµÄ Channel£¬Channel µÄÀàĞÍÓĞ FileChannel/SocketChannel/SelectableChannel/DatagramChannel/ServerSocketChannel µÈ¡£

ÔÚÍ¨µÀÉÏµÄ¶ÁĞ´¶¼»á¹ØÁªÉÏ»º³åÇø£¬Èç FileChannel.read(ByteBuffer dst)¡¢FileChannel.write(ByteBuffer src)£»¶ÔÎÄ¼şµÄËøÒ²ÊÇÔÚÍ¨µÀÉÏµÄ²Ù×÷£¬Èç FileChannel.lock()¡¢FileChannel.tryLock()¡£

Buffer ½Ó¿ÚµÄÊµÏÖÀàÓĞ ByteBuffer/MappedByteBuffer/CharBuffer/DoubleBuffer/FloadBuffer /IntBuffer/LongBuffer/ShortBuffer£¬ÓÃµÃ¶àµÄ»¹¾ÍÊÇ ByteBuffer¡£ÔÚ Buffer ÉÏÔòÊÇĞ©´æÈ¡Êı¾İºÍÊı¾İ¶¨Î»µÄ²Ù×÷¡£

ÏÂÃæÊÇ NIO ºÍÔ­ IO µÄÒ»Ğ©¸ÅÄî¶Ô±È£º

¸½¼ş: nio-oio.jpg 

ÆäËûµÄÈç SocketChannel ÍøÂçÍ¨µÀ»¹Î´Êö¼°£¬Àí½âÁË NIO Í¨µÀºÍ»º³åÇøµÄ¸ÅÄîÖ®ºó£¬ÎÒÃÇ¾Í¿ÉÒÔÊ¹ÓÃ NIO À´¶ÔÎÄ¼ş½øĞĞ¶ÁĞ´²Ù×÷ÁË¡££¨ÎÄ/¸ôÒ¶»Æİº£©














ÎÒÃÇÓÃÔ­ÓĞ IO ¶ÁĞ´ÎÄ¼şÓ¦¸Ã²»»áÄ°ÉúÁË£¬Ë³´ø»Ø¹ËÒ»ÏÂ£¬´óÖÂÁ½ÖÖ£º

1. ÔÚ InputStream »ò OutputStream ÉÏ¶ÁĞ´×Ö½Ú»ò×Ö½ÚÊı×é£¬¶Á InputStream Ê±ÓÃÊÇ·ñ·µ»Ø -1 À´ÅĞ¶ÏÊÇ·ñµ½´ïÄ©Î²¡£
2. °ü×°³É Reader/Writer ¿ÉÒÔÖ±½Ó¶ÁĞ´×Ö·û´®£¬½øÒ»²½°ü×°µ½ BufferedReader/BufferedWriter ¾Í¿ÉÒÔ°´ĞĞ¶ÁĞ´ÁË¡£readLine() Ê±¿´ÊÇ·ñ·µ»Ø null ¶Ï¶¨ÊÇ·ñ¶ÁÍêÁË×îºóÒ»ĞĞ¡£

ÏÖÔÚÎÒÃÇÒªÓÃ NIO À´¶ÁĞ´ÎÄ¼ş£¬¿Ï¶¨ÊÇÒªÓÃµ½ Channel ºÍ Buffer ÁË¡£Ò»¾ä»°ÃèÊö¹ı³Ì¾ÍÊÇ´Ó FileInputStream µÃµ½µÄ FileChannel ÖĞ¶ÁÈ¡Êı¾İµ½ Buffer ÖĞ£¬ÔÙ´¦Àí Buffer ÖĞµÄÊı¾İ¡£¿´´úÂë£º
01.public static void main(String[] args) throws Exception {
02.    FileInputStream fis = new FileInputStream("C:/Java/jdk1.6.0_18/LICENSE");
03.    
04.    //µÃµ½ÎÄ¼şÍ¨µÀ
05.    FileChannel fc = fis.getChannel();
06.    
07.    //·ÖÅäÓëÎÄ¼ş³ß´çµÈ´óµÄ»º³åÇø
08.    ByteBuffer bf = ByteBuffer.allocate((int) fc.size());
09.    
10.    //Õû¸öÎÄ¼şÄÚÈİÈ«¶ÁÈë»º³åÇø£¬¼´ÊÇÄÚ´æÓ³ÉäÎÄ¼ş
11.    fc.read(bf);
12.    
13.    //°Ñ»º³åÖĞµ±Ç°Î»ÖÃ»Ø¸´ÎªÁã
14.    bf.rewind();
15.    
16.    //Êä³ö»º³åÇøÖĞµÄÄÚÈİ
17.    while (bf.hasRemaining()) {
18.        System.out.print((char) bf.get());
19.    }
20.}
¸´ÖÆ´úÂë
ÉÏÃæ³ÌĞòÊ¹ÓÃÁËÒ»¸öÓëÎÄ¼ş³ß´çµÈ´óµÄ»º³åÇø£¬ÕıºÃÄÜÒ»´ÎĞÔ°ÑÎÄ¼şÄÚÈİÈ«²¿¶ÁÈëÄÚ´æ£¬Èç¹ûÎÄ¼ş¹ı¶à½«ÊÇÊ®·ÖºÄ·ÑµÄÄÚ´æµÄ£¬ËùÒÔÎÒÃÇ¿ÉÄÜĞëÊÖ¹¤Ö¸¶¨Ä³¸ö´óĞ¡(Èç 1024,2048) µÄ»º³åÇø£¬È»ºó·Ö¶à´Î¶ÁÈëÎÄ¼şÄÚÈİµ½»º³åÇøÖĞ¡£ÕâÊ±ºò³ÌĞò¾ÍÊÇÏÂÃæÄÇÑù×ÓÁË£º
01.public static void main(String[] args) throws Exception {
02.    FileInputStream fis = new FileInputStream("C:/Java/jdk1.6.0_18/LICENSE");
03. 
04.    // µÃµ½ÎÄ¼şÍ¨µÀ
05.    FileChannel fc = fis.getChannel();
06. 
07.    // Ö¸¶¨´óĞ¡Îª 1024 µÄ»º³åÇø
08.    ByteBuffer bf = ByteBuffer.allocate(1024);
09. 
10.    // ¶ÁÈ¡Í¨µÀÖĞµÄÏÂÒ»¿éÊı¾İµ½»º³åÇøÖĞ
11.    // »º³åÇøµÄ position ¼´Îªµ±Ç°»º³åÇøÖĞ×îºóÓĞĞ§Î»ÖÃ
12.    while (fc.read(bf) != -1) {
13. 
14.        //°Ñ»º³åÖĞµ±Ç°Î»ÖÃ»Ø¸´ÎªÁã£¬Ç°°Ñ»º³åÇøµÄ limit ÉèÖÃÎªÖ®Ç° position Öµ
15.        bf.flip();
16. 
17.        // Êä³ö»º³åÇøÖĞµÄÄÚÈİ
18.        while (bf.hasRemaining()) {
19.            System.out.print((char) bf.get());
20.        }
21. 
22.        // ÇåÀí»º³åÇø£¬×¼±¸ÔÙ´Î¶ÁÈ¡Êı¾İ
23.        bf.clear();
24.    }
25.}

ÁôÒâ¶Ô»º³åÇøµÄ rewind()/flip()/clear() ²Ù×÷Ëù²úÉúµÄÓ°Ïì£¬¼´¶Ô position/limit/mark µÈ±êÖ¾µÄÓ°Ïì¡£×îºóÌáĞÑ²Ù×÷ÍêÖ®ºó£¬Òª¹Ø±ÕÍ¨µÀºÍÊäÈëÁ÷¡£

ÓÃ ByteBuffer ÖªµÀÁËÔõÃ´¶ÁÎÄ¼şÄÚÈİ(µ±È»£¬»¹Î´Éæ¼°µ½ÖĞÎÄÄÚÈİ)²¢´òÓ¡µ½ÆÁÄ»ºó£¬ÔÙÀ´¿´¿´ NIO ÔõÃ´Ğ´ÎÄ¼ş£º

view source
print?
01.public static void main(String[] args) throws FileNotFoundException, IOException{
02.    FileOutputStream fos = new FileOutputStream("c:/nio.tst");
03. 
04.    // µÃµ½ÎÄ¼şÍ¨µÀ
05.    FileChannel fc = fos.getChannel();
06. 
07.    // Ö¸¶¨´óĞ¡Îª 1024 µÄ»º³åÇø
08.    ByteBuffer bf = ByteBuffer.allocate(1024);
09. 
10.    // ÒªĞ´ÈëÎÄ¼şµÄ×Ö·û´®
11.    String greeting = "Hello, Java NIO";
12.    
13.    //°ÑÒÔÉÏ×Ö·û´®Öğ×Ö·ÅÈë»º³åÇø
14.    for (int i = 0; i < greeting.length(); i++) {
15.        bf.putChar(greeting.charAt(i));
16.    }
17.    
18.    // ¼ÇµÃÖ´ĞĞÕâ¸ö·½·¨£¬Ê¹µÃ position=0, limit=30, ²ÅÄÜĞ´ÈëÕıÈ·µÄÊı¾İ
19.    // ·ñÔò position Îª 30, limit Îª 1024£¬½«»á°Ñ 30 Ö®ºóµÄÈ«²¿¿ÕÊı¾İ(0) Ìîµ½ÎÄ¼şÖĞ
20.    bf.flip();
21. 
22.    // »º³åÇøÊı¾İĞ´Èëµ½ÎÄ¼şÖĞ£¬»á°Ñ»º³åÇøÖĞ´Ó position µ½ limit Ö®¼äµÄÊı¾İĞ´ÈëÎÄ¼ş
23.    fc.write(bf);
24.    
25.    fc.close(); //¹Ø±ÕÎÄ¼şÍ¨µÀ
26.    fos.close(); //¹Ø±ÕÎÄ¼şÊä³öÁ÷
27.}
¸´ÖÆ´úÂë
Í¬ÑùµÄ£¬Èç¹ûÊÇĞ´ÈëÖĞÎÄÄÚÈİ£¬Ò²ĞèÒª½øĞĞ×Ö·û¼¯µÄÏà¹Ø´¦Àí¡£Ö´ĞĞºóÔÚ C ÅÌ¸ùÄ¿Â¼ÏÂ²úÉú nio.tst ÎÄ¼ş£¬ÄÚÈİ¾ÍÊÇ Hello, Java NIO¡£´Ë´úÂëµÄ¹Ø¼üÖ®´¦¾ÍÊÇ¶Ô»º³åµÄ flip() µ÷ÓÃ£¬Äã¿ÉÒÔÔÚµ÷ÊÔÄ£Ê½ÏÂ¹Û²ìµ½ flip() ·½·¨µ÷ÓÃÇ°ºó£¬»º³åÇø bf µÄ position/limit ÊôĞÔµÄ±ä»¯¡£ÊÔ×Å×¢ÊÍµô flip() ´úÂë£¬¿´¿´Á½´ÎÉú³ÉµÄ nio.tst ÎÄ¼şÄÚÈİÊÇ²»ÊÇ´óÏà¾¶Í¥¡£

ËùÒÔ£¬ÒªÓÃºÃ NIO£¬»º³åÇøµÄ mark/position/limit/capacity ÊôĞÔÓ¦Àí½â£¬ÒÔ¼° clear()/flip()/rewind() ·Ö±ğ»áÔõÃ´Ó°Ïìµ½ÒÔÉÏÊôĞÔ¡£

»¹ÓĞ£¬ËäÈ»ËµÍ¨µÀÊÇË«ÏòµÄ£¬×ÖÃæÉÏ²»ÏñÁ÷ÄÇÑùÇø·ÖÊäÈëÍ¨µÀ»òÊÇÊä³öÍ¨µÀ£¬µ«Êµ¼ÊÍ¨µÀÒ²´æÔÚÖ»¶Á»òÖ»Ğ´µÄÌØĞÔ£¬ÀıÈçÓÉ FileInputStream.getChannel() »ñµÃµÄÍ¨µÀÊÇÎŞ·¨Ğ´ÈëÄÚÈİµÄ£¬ÓÉ FileOutputStream.getChannel() »ñµÃµÄÍ¨µÀÊÇ²»ÄÜ¶ÁµÄ£¬·ñÔò»áÅ×³öÏàÓ¦µÄÒì³£ NonWritableChannelException ºÍ NonReadableChannelException¡£¶øÇÒ Buffer Ò²´æÔÚ×ÅÊÇ·ñÖ»¶ÁµÄÊôĞÔ¡£

Ç°ÃæµÄ´úÂëÔÚÕâÀïÖ»ÊÇËµÃ÷ÓÃ NIO ¶ÁĞ´ÎÄ¼şÓ¦ÈçºÎ´¦Àí£¬²¢²»ÊÇËµ±ÈÆğÓÃ¾É IO Á÷Ê½µÄĞ´·¨Ğ§ÂÊ¾Í¸ü¸ßÁË¡£NIO µÄ¸ßĞ§ÂÊÖ»»áÌåÏÖÔÚÓĞĞ©Ê±ºò£¬²¢·ÇÈÎºÎÊ±ºò¶¼ÓÅÓÚ¾É IO£¬ÄÇÊÇ¿é²Ù×÷ºÍ×Ö½Ú²Ù×÷µÄÇø±ğ£¬ÓÃ NIO Ê±ÒªĞ¡ĞÄÄÚ´æ¡£ÉìÊÖ¾ÍÄÜÕªµ½µÄÀæÓÃ²»×Å°á¸öµÊ×Ó£¬ºÎ¿ö¾É IO ÊµÏÖÆğÀ´»¹¸ü¼ò½àĞ©ÄØ! £¨ÎÄ/¸ôÒ¶»Æİº£©
