/* index.js
 * Copyright 2002 - 2006 BlogDriver.com,Bokee.com, All Rights Reserved
 * File Authors: Թ��Թ��
 */

function addBlogMark(title,url,centent){
	void(
	     keyit=window.open('http://blogmark.bokee.com/jsp/key/quickaddkey.jsp?k=' 
	          +encodeURI(title)+'&u='+encodeURI(url)+'&c='+encodeURI(centent),'keyit','scrollbars=no,width=500,height=430,status=no,resizable=yes'));
	     keyit.focus();
	}
function addFavorite(favName,url){
	var blogID=getBlogID();
	if(blogID==null){
		alert('����û�е�½�����ȵ�½�����ղأ�');
		window.location.href='http://reg.bokee.com/account/web/login.jsp?url='+ window.location.href;
		return;
	}
	var frmObj=document.createElement("IMG");
	frmObj.src='http://'+blogID+'/list/addDiaryFavorite.b?favorite.blogId='+blogID+'&favorite.favName='
	          +favName+'&favorite.url='+url+'&favorite.property=1';
	frmObj.style.display='none';
	document.body.appendChild(frmObj);
	alert('�����ɹ���');
}    	
function setImg(){
        var objs=document.getElementsByTagName("img");
        for(var i=0;i<objs.length;i++){
                if(objs[i].id == null || objs[i].id!='systemImg'){
                        if(parseInt(objs[i].width)>512){
                                objs[i].width='512';
                                objs[i].style.width='512';
                                objs[i].style.height='';
                        }
                }
        }
}


//google search
 function submitFormWithChannel(channelname) {
  document.gform.channel.value=channelname;
  document.gform.submit();
  return;
 }
