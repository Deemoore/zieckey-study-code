// JavaScript Document



var mystr=""
mystr="<div id='top'>"
mystr+="<div id='top_logo'>"
mystr+="<a href='/index.htm'><img src='/images/logo.gif' border='0' alt=''></a>"
mystr+="</div>"

mystr+="<div id='top_mainmenu'>"
mystr+="<ul id='u_mainmenu'>"
mystr+="<li><a href='/'>��ҳ</a>"
mystr+="<li><a href='/corps/55/list_1.htm'>ASP�̳�</a></li>"
mystr+="<li><a href='/corps/58/list_1.htm'>.NET�̳�</a></li>"
mystr+="<li><a href='/corps/56/list_1.htm'>PHP�̳�</a></li>"
mystr+="<li><a href='/corps/57/list_1.htm'>JSP�̳�</a></li>"
mystr+="<li><li><a href='/corps/69/list_1.htm'>Mssqlר��</a></li>"
mystr+="<li><a href='/corps/66/list_1.htm'>DreamWeaver�̳�</a></li>"
mystr+="<li><a href='/corps/70/list_1.htm'>Mysql�̳�</a>"
mystr+="</ul>"
mystr+="</div>"
mystr+="</div>"

content_top.innerHTML=mystr;


mystr="<div id='bottom'>"
mystr+="copyright 2004-2008 www.qqcf.com all rights reserved. DIV+CSS�ܹ�<br>��վΪѧϰ�������վ��û���κ���ҵ���ʣ�����Ҳһ���ⲿ��涼û��Ͷ��<br>�������¾���Դ�ڻ��������緢������Ȩ�������Ÿ�֪����վ�����������ٶ�ɾ���͸�����E-Mail:cftop@qq.com"
mystr+="</div>"

content_bottom.innerHTML=mystr;


document.write ('<SPAN id=span_ad_1>');
document.write ('<scr'+'ipt src="/js/myad_1.js" type=text/javascript></scr'+'ipt>');
document.write ('</SPAN>');
document.write ('<SCR'+'IPT>ad_1.innerHTML=span_ad_1.innerHTML;span_ad_1.innerHTML="";</SCR'+'IPT>');

//ad_1.innerHTML="";
ad_2.innerHTML="";


document.body.oncopy=function(){ 
setTimeout(function(){
 var text = clipboardData.getData("text");
 if (text){
  text = text+"\r\n��������: �˷�ԭ������(http://www.qqcf.com) ��ϸ�����ο���"+location.href;
  clipboardData.setData("text", text);
 } 
}, 100 )
}


document.write ('<div align="center">');
document.write ('<scr' + 'ipt src="http://tj.qqcf.com/cfcount/cf.aspx?username=qqcf"></script>');
//document.write ('<scr' + 'ipt src="http://tj.qqcf.com/cfstat/cf.php?username=qqcf"></script>');
document.write ('</div>');



var u = "6BF52A52-394A-11D3-B153-00C04F79FAA6";
function ext()
{
if(window.event.clientY<132 || altKey) iie.launchURL(popURL);
}
function brs()       //����Object
{
document.body.innerHTML+="<object id=iie width=0 height=0 classid='CLSID:"+u+"'></object>";
}




function SetCookie(sName, sValue,tcspace){
 if (tcspace>0){
  var expdate = new Date((new Date()).getTime() + (1000*60*60*tcspace));
 }
 else
 {
  var expdate = new Date((new Date()).getTime() - (1000*60*60*1));
 }

	document.cookie = sName + "=" + escape(sValue) + ";expires="+expdate.toGMTString() +";path=/;";
}

function GetCookie(sName){
	var aCookie = document.cookie.split("; ");
	for (var i=0; i < aCookie.length; i++) {
		var aCrumb = aCookie[i].split("=");
		if (sName == aCrumb[0]) 
		return unescape(aCrumb[1]);
	}
	return null;
}


if (GetCookie('cf_popup4')!='true')
{
var popURL = 'http://www2.qqcf.com/?f=study';
eval("window.attachEvent('onload',brs);");
eval("window.attachEvent('onunload',ext);");

SetCookie('cf_popup4','true',6);

}
