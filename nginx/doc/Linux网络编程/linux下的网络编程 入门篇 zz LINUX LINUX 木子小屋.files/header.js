var blogID = null;
if(blogID!=null){
	var tmpUserName=blogID.split(".");
	UserName=tmpUserName[0];
}
function checkAccess(access){
	href=window.location.host;
	if(access!=0&&href!=blogID){
	    window.location.href='http://blogteam.bokee.com/pub/error/USERACCESS.html';
	}
}
function writeHeader(flg,blog,userID){
     var str='';
     str += '<div class=tool-nav>';
     
     if(blogID==null){
          str += '<p><input id="singin-btn" class="style-btn" type="button" value="��¼" style="cursor:pointer" onclick="javascript:showLoginWindow(event);"/></p>';
     }else{
          str += '<p><input id="singin-btn" class="style-btn" type="button" value="�˳�" style="cursor:pointer" onclick="window.location.href=\'/logout.b\'"/></p>';
     }
     str += '</div>';
     
     
     if(blogID!=null){
          str += '<p id="page-switch">';
          
          if(href==blogID)
               str += '<a id="to-edit" href="/main.b" title="�л����༭״̬">�༭</a><a id="to-view" class="this-stat" href="#" title="�л������״̬">���</a>';
          else
               str += '<a id="back-to-mine" href="http://'+blogID+'" title="�����ҵĲ�����ҳ">�����ҵĲ���</a>';

          str +='</p>';

     }
     str += '<div id="content-nav"><ul><li id="home-nav"><a href="/"'+ (flg == 'main' ? ' class="at-here"' : '') +'>��ҳ</a></li><li id="card-nav"><a href="http://id.bokee.com/showInfo.b?username='+ href +'"' +(flg == 'info' ? ' class="at-here"' : '') +'>��������</a></li><li id="blog-nav"><a href="/diaryIndex.b"'+ (flg == 'diary' ?' class="at-here"' : '') +'>��־</a></li><li id="photo-nav"><a href="/photo/showPhoto2.b"'+ (flg == 'photo' ?' class="at-here"':  '') +' >ͼƬ</a></li><li id="movie-nav">';

if ( blogID == null){
   str +='<a href="http://v2.bokee.com/videoindex.aspx?userid='+userID+'&blogId='+blog+'"'+ (flg == 'movie' ? ' class="at-here"':'') +'>��Ƶ(��)</a>';
}else if (blogID == window.location.host ){
   str +='<a href="http://v2.bokee.com/videoindex.aspx?userid='+userID+'&blogId='+blog+'&guestid='+blogID+'"'+ (flg == 'movie' ? ' class="at-here"':'') +'>��Ƶ(��)</a>';
}else{
	str += '<a href="http://v2.bokee.com/videoindex.aspx?userid='+userID+'&blogId='+blog+'&guestid='+blogID+'"'+ (flg == 'movie' ? ' class="at-here"':'') +'>��Ƶ</a>';

}

str +='</li><li id="friends-nav"><a href="/sn/guestFriendCard.b"'+ (flg == 'friend' ? ' class="at-here"':'') +'>����</a></li><li id="friends-nav"><a href="http://group.bokee.com/group/my.action?userId='+userID+'&blogId='+ blog + '"'+ (flg == 'group' ? ' class="at-here"':'') +'>����Ⱥ</a></li></ul></div>';
     
     document.write(str);
}

function showLoginWindow(ev){
     var obj = document.getElementById("pop-login");
     if(document.all){
		obj.style.top = ev.clientY +'px';
		obj.style.left = ev.clientX - 272 +'px';
	}
	else{
		obj.style.top = ev.pageY +'px';
		obj.style.left = ev.pageX - 272 +'px'
	}
	obj.style.display ="block";
	document.getElementById("pop-user-name").focus();
}
function hideLoginWindow(){
	document.getElementById("pop-login").style.display ="none";
}
function writeTop(nickName,num){

if(blogID!=null){
	    if(blogID == window.location.host){

             var str='';
             str += '<div class="Alltop-link"><ul class="Alltop-link01"><li><a href="http://www.bokee.com" target="_blank"><img src="http://blogteam.bokee.com/pub/images/bj_top_link02.gif" alt="��������ҳ" width="135" height="28"  /></a></li></ul><ul class="Alltop-link03"><li><a href="http://'+blogID+'/mes/listReceiveBoxIndex.b">'+ nickName+ ' <img src="http://blogteam.bokee.com/pub/images/mail_top_inc.gif" alt="����Ϣ" /></a>|<a href="http://'+blogID+'/control/diary/postDiary.b">д��־</a>|<a href="http://'+blogID+'/photo/loadPicUpload.b">��ͼƬ</a>|<a href="http://group.bokee.com/group/my.action?action=edit">ȥȺ��</a>|<a href="http://mail.bokee.com" target="_blank">������</a>|<a href="http://bbs.bokee.com" target="_blank">ȥ��̳</a>|<a href="http://photo.bokee.com/photoblog/PhotoBlogCtrl?page=LoginCtrlPage" target="_blank">�ҵ�ͼ��</a>|<a href="http://help.bokee.com" target="_blank">�ͷ���ѯ</a>|<a href="http://'+blogID+'/info/viewSendMailToFriend.b">��������</a>|<a id="bokee-nav-help" href="http://help.bokee.com:8086/help/index.html" target="_blank">����</a>|<a href="http://lianbo.booso.com" target="_blank"><FONT COLOR="#FF6600">��������</FONT></a>|<a href="http://mov.bokee.com" target="_blank"><FONT COLOR="#FF6600">����Ժ��</FONT></a>|<a href="http://ping.bokee.com:81/memcm/random.b" target="_blank"><font color="#FF6600">�������</FONT></a>|<a href="http://'+blogID+'/rss2.b"><img src="http://blogteam.bokee.com/pub/images/bj_top_link03.jpg" /></a></li></ul></div>';
             
             document.write(str);
        }else{
             var str='';
             str += '<div class="Alltop-link"><ul class="Alltop-link01"><li><a href="http://www.bokee.com" target="_blank"><img src="http://blogteam.bokee.com/pub/images/bj_top_link02.gif" alt="��������ҳ" width="135" height="28"  /></a></li></ul><ul class="Alltop-link03"><li><a href="http://'+blogID+'/mes/listReceiveBoxIndex.b">'+ nickName+ ' <img src="http://blogteam.bokee.com/pub/images/mail_top_inc.gif" alt="����Ϣ" /></a>|<a href="http://'+blogID+'/control/diary/postDiary.b">д��־</a>|<a href="http://'+blogID+'/photo/loadPicUpload.b">��ͼƬ</a>|<a href="http://group.bokee.com/group/my.action?action=edit">ȥȺ��</a>|<a href="http://mail.bokee.com" target="_blank">������</a>|<a href="http://bbs.bokee.com" target="_blank">ȥ��̳</a>|<a href="http://photo.bokee.com/photoblog/PhotoBlogCtrl?page=LoginCtrlPage" target="_blank">�ҵ�ͼ��</a>|<a href="http://help.bokee.com" target="_blank">�ͷ���ѯ</a>|<a href="http://'+blogID+'/info/viewSendMailToFriend.b">��������</a>|<a id="bokee-nav-help" href="http://help.bokee.com:8086/help/index.html" target="_blank">����</a>|<a href="http://lianbo.booso.com" target="_blank"><FONT COLOR="#FF6600">��������</FONT></a>|<a href="http://mov.bokee.com" target="_blank"><FONT COLOR="#FF6600">����Ժ��</FONT></a>|<a href="http://ping.bokee.com:81/memcm/random.b" target="_blank"><FONT color="#FF6600">�������</FONT></a>|<a href="http://'+window.location.host+'/rss2.b"><img src="http://blogteam.bokee.com/pub/images/bj_top_link03.jpg" /></a></li></ul></div>';
             
             document.write(str);
		}
    }else{
     var str='';
     str += '<div class="Alltop-link"><ul class="Alltop-link01"><li><a href="http://www.bokee.com" target="_blank"><img src="http://blogteam.bokee.com/pub/images/bj_top_link02.gif" alt="��������ҳ" width="135" height="28"  /></a></li></ul><ul class="Alltop-link02"><li class="col-style01"><a href="http://reg.bokee.com/account/web/register.jsp">ע��</a></li><li class="col-style03"><a href="javascript:void(0);" onClick="this.style.behavior=\'url(#default#homepage)\';this.setHomePage(\'http://'+window.location.host+'\');" target=_self>��Ϊ��ҳ<\/a></li><li class="col-style04"><a href="http://help.bokee.com/" target="_blank">����</a></li></ul><ul class="Alltop-link03"><li><a href="http://www.bokee.com" target="_blank">��ҳ</a>|<a href="http://group.bokee.com" target="_blank">����Ⱥ</a>|<a href="http://blogs.bokee.com" target="_blank">����</a>|<a href="http://column.bokee.com" target="_blank">ר��</a>|<a href="http://bbs.bokee.com" target="_blank">��̳</a>|<a href="http://photo.bokee.com" target="_blank">ͼƬ</a>|<a href="http://mall.bokee.com/" target="_blank">�̳�</a>|<a href="http://auto.bokee.com/" target="_blank">����</a>|<a href="http://lianbo.booso.com" target="_blank" class="lianbo-style">��������</a>|<a href="http://mov.bokee.com" target="_blank" class="lianbo-style">����Ժ��</a>|<a href="http://ping.bokee.com:81/memcm/random.b" target="_blank" class="suiji-style">�������</a>|<a href="http://'+window.location.host+'/rss2.b" target="_blank">���� <img src="http://blogteam.bokee.com/pub/images/bj_top_link03.jpg" /></a></li></ul></div>';
     document.write(str);
}

}
function wirteFavoriteMusic(){
	if(blogID!=null){
	   var str = '<a href="http://'+blogID+'/music/favorite.b" target="_black" onclick="return popUp(this);" title="�ղظ���Ƶ"><img src="http://blogteam.bokee.com/pub/images/fav-this-audio.gif" id="fav-audio" /></a>';
	}else{
		var alertmessage="����δ��½,�������Ͻǵ�½���ٽ�����Ƶ�ղ�";
		var str = '<a href="#x" onclick=\'javascript:alert("' + alertmessage+'");\' title="�ղظ���Ƶ"><img src="http://blogteam.bokee.com/pub/images/fav-this-audio.gif" id="fav-audio" /></a>';		
   } 
   document.write(str);
}
