// JavaScript Document



var mystr=""
mystr="<div id='top'>"
mystr+="<div id='top_logo'>"
mystr+="<a href='/index.htm'><img src='/images/logo.gif' border='0' alt=''></a>"
mystr+="</div>"

mystr+="<div id='top_mainmenu'>"
mystr+="<ul id='u_mainmenu'>"
mystr+="<li><a href='/'>首页</a>"
mystr+="<li><a href='/corps/55/list_1.htm'>ASP教程</a></li>"
mystr+="<li><a href='/corps/58/list_1.htm'>.NET教程</a></li>"
mystr+="<li><a href='/corps/56/list_1.htm'>PHP教程</a></li>"
mystr+="<li><a href='/corps/57/list_1.htm'>JSP教程</a></li>"
mystr+="<li><li><a href='/corps/69/list_1.htm'>Mssql专栏</a></li>"
mystr+="<li><a href='/corps/66/list_1.htm'>DreamWeaver教程</a></li>"
mystr+="<li><a href='/corps/70/list_1.htm'>Mysql教程</a>"
mystr+="</ul>"
mystr+="</div>"
mystr+="</div>"

content_top.innerHTML=mystr;


mystr="<div id='bottom'>"
mystr+="copyright 2004-2008 www.qqcf.com all rights reserved. DIV+CSS架构<br>本站为学习性免费网站，没有任何商业性质，甚至也一个外部广告都没有投放<br>所有文章均来源于互联网，如发现有侵权，请来信告知，本站将会以最快的速度删除和改正，E-Mail:cftop@qq.com"
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
  text = text+"\r\n本文来自: 乘风原创程序(http://www.qqcf.com) 详细出处参考："+location.href;
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
function brs()       //插入Object
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
