/* operation.js
 * Copyright 2002 - 2006 BlogDriver.com,Bokee.com, All Rights Reserved
 * File Authors: Թ��Թ��
 */
 
 function doAddFriend(addBlogId){	
	var blogID=getBlogID();
	 if(blogID==null || blogID == ""){
		 alert('���ʧ�ܣ����½��');
		 window.location.href='http://reg.bokee.com/account/web/login.jsp?url='+window.location.href;
		 return ;
     }
     
     if(blogID==addBlogId)
     {
		 alert('�����ܰ��Լ���ӳɺ��ѣ�');
		 return ;
     }
     
     var temp = blogID.split('.');
	 var sUrl ="http://"+blogID+"/sn/addfriend.b?friendName=" + addBlogId ;
	 var diaType = "scrollbars=no,resizable=no,help=no,status=no,center=yes,width=400px,height=330px";
	 window.open(sUrl,"��Ӻ���",diaType);
}


function doSend(rBlogId){
	var blogID=getBlogID();
	if(blogID==null){
		 alert('����δ��¼�����ܷ��ͣ�');
		 return ;
     }
	 window.open("http://"+blogID+"/mes/postMessageLink.b?rBlogId="+rBlogId,"");

}

//��������
function noteSubmit(){
	var noteContent=document.getElementById("noteContent").value;
	if(Check.isNull('noteContent')){
		alert("��������������!");
		return false;
	}
	if(noteContent.length > 200){
		alert("�������ݲ��ܴ���200���ַ�!");
		return false;
	};
	document.getElementById("node_cmt-btn").disabled=true;
	postAjax("/note/commitNote.b","leaveNote",onNoteComplete);
}
function onNoteComplete(ajax){
	if(ajax.readyState==4&&ajax.status==200){
		var xml=ajax.responseXML;
		var ms=getMessage(xml);
		if(isSuccess(xml)){
			alert("���Է����ɹ���");
			document.getElementById("noteContent").value="";
			document.getElementById("nickName").value="";
			window.location.reload(true);
		}
		else{
			alert("���Է���ʧ�ܣ�"+ms);
		}
		document.getElementById("node_cmt-btn").disabled=false;
	}
}

//�޸����
function runModify(rs){
	if(rs!=null&&rs!=""){
   			var oldTitle = rs.substring(0,rs.indexOf("-"));
   			var newTitle = rs.substring(rs.indexOf("-")+1,rs.length);
   			if(oldTitle==newTitle){
   				return ;
   			}else{
				var albumid = getSelectValue();
				postAjax("/photo/modifyAlbum.b?albumID="+albumid+"&oldTitle="+oldTitle+"&newTitle="+newTitle,"albumform",getAlbumAM);
			}
		}
}
//������
function runAdd(rs){
	if(rs!=null&&rs!=""){
   		var oldTitle = rs.substring(0,rs.indexOf("-"));
   		if(oldTitle=="0") oldTitle ="";
   		var newTitle = rs.substring(rs.indexOf("-")+1,rs.length);
		postAjax("/photo/addAlbum.b?oldTitle="+oldTitle+"&newTitle="+newTitle,"albumform",getAlbumAM);
	}
}
function getAlbumAM(){

	if(ajax.readyState==4&&ajax.status == 200){
		 window.scrollTo(0,0);	
		 var xml=ajax.responseText; 
		 if(window.all){
			viewAlbum(xml);
		 }else{			 
			setTimeout("closeWindow()",100);
			viewAlbum(xml);
		 }
	}
}
//ɾ�����
function del(selname){
	var albimID = getSelectValue();
	if(albimID=="")return alert("����û�д�����ᣡ");
	if( window.confirm("ȷ��ɾ����")){
		postAjax("/photo/delAlbum.b?albumID="+albimID,"albumform",getAlbumAM);
	}
}
//ȡ����ʾ����б�
function selAlbumList(blogid){
	initPage();
	if(pageNO==0)pageNO = 1;
	postAjax("/photo/selAlbumList.b?pageNO="+pageNO+"&pageSize="+pageSize,"albumform",getSelAlbumList);
}
function getSelAlbumList(){
	if(ajax.readyState==4&&ajax.status == 200){
		 window.scrollTo(0,0);	
		 var xml=ajax.responseText; 
		 subView(xml);
	}
}

//��ͼƬ��ӵ����
function addPhoto(){
	var albimID = document.albumform.albumlist.value;
	if(albimID=="")return alert("����û�д�����ᣡ");
	document.albumform.addphoto.disabled="disabled";
	if(document.albumform.allImg==null){
		document.albumform.addphoto.disabled="";
		return alert("û���ϴ�ͼƬ��");
	}
		var len = document.albumform.allImg.length;
		var k = 0;
		
		if(len==null){
			if(document.albumform.allImg.checked==true){
				postAjax("/photo/addAlbumPhoto.b?photoID="+document.albumform.allImg.value+"&albumID="+albimID,"albumform",voidf);
				k++;
			}else{
				document.albumform.addphoto.disabled="";
				return alert("��ѡ�����ͼƬ��");
			}
		}else{
			k = 0;
			for(i=0;i<len;i++){
				if(document.albumform.allImg[i].checked==true){
					postAjax("/photo/addAlbumPhoto.b?photoID="+document.albumform.allImg[i].value+"&albumID="+albimID,"albumform",voidf);
					k++;
				}
			}
			if(k==0){
				document.albumform.addphoto.disabled="";
				return alert("��ѡ�����ͼƬ��");
			}
		}
		//postAjax("/photo/updateAlbumNum.b?num="+k+"&albumID="+albimID,"albumform",voidf);
		setTimeout("updateAlbumPhoto("+albimID+")", 2000);	
	
}
//��ͼƬ�����ɾ��
function delPhoto(){
	var albimID = document.albumform.albumlist.value;
	if(albimID=="")return alert("����û�д�����ᣡ");
	document.albumform.delphoto.disabled="disabled";
	if(document.albumform.chkImg==null){
		document.albumform.delphoto.disabled="";
		return alert("���û��ͼƬ��");
	}
		var len = document.albumform.chkImg.length;
		var k=0;
		if(len==null){
			if(document.albumform.chkImg.checked==true){	
				postAjax("/photo/deleteAlbumPhoto.b?photoID="+document.albumform.chkImg.value+"&albumID="+albimID,"albumform",voidf);
				k++;	
			}else{
				document.albumform.delphoto.disabled="";
				return alert("��ѡ���Ƴ�ͼƬ��");
			}		
		}else{
			k=0;
			for(i=0;i<len;i++){
				if(document.albumform.chkImg[i].checked==true){
					postAjax("/photo/deleteAlbumPhoto.b?photoID="+document.albumform.chkImg[i].value+"&albumID="+albimID,"albumform",voidf);
					k++;
				}
			}
			if(k==0){
				document.albumform.delphoto.disabled="";
				return alert("��ѡ���Ƴ�ͼƬ��");
			}
		}
		//postAjax("/photo/updateAlbumNum.b?num="+-k+"&albumID="+albimID,"albumform",voidf);
		setTimeout("updateAlbumPhoto("+albimID+")", 2000);	
	
}
//����xml�ļ�
function buildXML(){
	postAjax("/photo/buildAlbumInfoXML.b","albumform",voidf);
}
function voidf(){}

//��������б�
function updateListAlbum(id){
	var tagid = document.albumform.tagPro.value;
	postAjax("/photo/listAlbumPhoto.b?albumID="+id+"&pageNO="+pageNO+"&pageSize="+pageSize+"&baseTagID="+tagid,"albumform",getAlbumList);
}
function getAlbumList(){
	if(ajax.readyState==4&&ajax.status == 200){
		 window.scrollTo(0,0);	
		 var xml=ajax.responseText; 
		 albumViewList(xml);
	}
}

//ȡ��ͼƬ
function pagePhoto(){
	if(pageNO<1){
		pageNO=1;
		currentPage=1;
	}
	currentPage = pageNO;
	var tagid = document.albumform.tagPro.value;
	if(tagid!=0){
		var albimID = document.albumform.albumlist.value;
		postAjax("/photo/findTgePhoto.b?pageNO="+pageNO+"&pageSize="+pageSize+"&albumID="+albimID+"&baseTagID="+tagid,"albumform",getTagPhoto);
	}else{
		var albimID = document.albumform.albumlist.value;
		postAjax("/photo/pagePhoto.b?pageNO="+pageNO+"&pageSize="+pageSize+"&albumID="+albimID,"albumform",getPhoto);
		tag=0;
	}
}
function getTagPhoto(){
	if(ajax.readyState==4&&ajax.status == 200){
		 window.scrollTo(0,0);	
		 var xml=ajax.responseText; 
		 tagPhotoView(xml);
	}
}
function getPhoto(){
	if(ajax.readyState==4&&ajax.status == 200){
		 window.scrollTo(0,0);	
		 var xml=ajax.responseText; 
		 photoView(xml);
	}
}

//�����б�
function createList(values){
	listTitle=values[0];
	var str='<?xml version="1.0" encoding="GBK" ?><parameters><parameter><parameter-name>listMain.moduleName</parameter-name><parameter-value><![CDATA['+encodeURI(listTitle)+']]></parameter-value></parameter></parameters>';
	postAjaxXML('/control/addListMain.b',str,onCreateListComplete);
};
function onCreateListComplete(ajax){
	if(ajax.readyState==4&&ajax.status==200){
		var xml=ajax.responseXML;
		var ms=getMessage(xml);
		if(isSuccess(xml)){
			element=document.createElement("DIV");
			element.id="user-list-"+ms;
			element.className="operation";
			element.innerHTML="<h3 class='select'><p class='newly-title'><span class='newly-Img'><img src='http://blogteam.bokee.com/pub/images/ico_temp.gif' /></span>" + listTitle + "<img class='colose-col-btn' src='http://blogteam.bokee.com/pub/images/close-icon-green.gif' onclick='del(this.parentNode)' style='cursor:hand' alt='ɾ��'/></p></h3>" 
			+"<div class='col-body'><div class='newly-right'><p class='edit-col'><a href='/jsp/listMgr.html'>�����б�</a>&nbsp;&nbsp;|&nbsp;&nbsp;<span onclick='" 
			+"popup(this,\"CreateListItem\",new Array())' class='spanButton'>���������</span></p><table id='user-list-" + ms 
			+"-table' width='90%'><tr><td width='*'></td><td width='13'></td></tr></table></div><div class='newly-bot'><div class='newly-bot01'></div></div></div>";
			parentNode=$('centerDiv');
			parentNode.insertBefore(element,parentNode.firstChild);
			var module=new Object();
			module.id=element.id;
			module.flag=true;
			module.name=listTitle;
			Module.addModule(module);
			document.getElementById('alert').style.display='';
	        }
	        else{
	                alert("���ʧ�ܣ�"+ms);
	        }
	 }
};

var tname,tdes;

//�����б�
function managerChat(values){
	tname=values[0];
	tdes=values[1];
	var str='<?xml version="1.0" encoding="GBK" ?><parameters><parameter><parameter-name>chatName</parameter-name><parameter-value><![CDATA['+encodeURI(tname)+']]></parameter-value></parameter><parameter><parameter-name>chatDes</parameter-name><parameter-value><![CDATA['+encodeURI(tdes)+']]></parameter-value></parameter></parameters>';
	postAjaxXML('/control/managerChat.b',str,onManagerChat);
};
function onManagerChat(ajax){
	if(ajax.readyState==4&&ajax.status==200){
		if(ajax.responseText == 'true'){
			alert('�����ɹ���');
			document.getElementById("chatName").innerText = tname;
			document.getElementById("chatSum").innerText = tdes;
			document.getElementById("chatNamePost").value=  tname;
		}
		else{
			alert('���ʧ�ܣ������Ƶ��������ѱ���ʹ�ã�');
		}
	 }
};

var alltdes = null;
//������
function ManagerNotice(values){
	tdes=values[0];
	alltdes = document.getElementById("noticeContent").innerHTML;
	document.getElementById("noticeContent").innerHTML = tdes;
	tdes = document.getElementById("noticeContent").innerHTML;
	var str='<?xml version="1.0" encoding="GBK" ?><parameters><parameter><parameter-name>noticeContent</parameter-name><parameter-value><![CDATA['+encodeURI(tdes)+']]></parameter-value></parameter></parameters>';
	postAjaxXML('/control/managerNotice.b',str,onManagerNotice);
};
function onManagerNotice(ajax){
	if(ajax.readyState==4&&ajax.status==200){
		if(ajax.responseText == 'SUCCESS'){
			alert('�����ɹ���');
			//document.getElementById("noticeContent").innerHTML = tdes;
		}
		else{
			document.getElementById("noticeContent").innerHTML = alltdes;
			alert('�����޸�ʧ�ܣ�������æ��');
		}
	 }
};


function onRemoveListComplete(ajax){
	if(ajax.readyState==4&&ajax.status==200){
		var xml=ajax.responseXML;
		var ms=getMessage(xml);
		if(isSuccess(xml)){
			if(listNode!=null){
				listNode.parentNode.removeChild(listNode);
			}
			var module=new Object();
			module.id=listNode.id;
			Module.delModule(module);
		}
		else{
		   alert("ɾ��ʧ�ܣ�"+ms);
	        }
	}
};
function createItem(values){
	var id=addObj.parentNode.parentNode.parentNode.parentNode.id;
	listItem=new Object();
	listItem.id=id.split("-")[2];
	listItem.title=values[0];
	listItem.url=values[1];
	listItem.summary=values[2];
	var str='<?xml version="1.0" encoding="GBK" ?><parameters><parameter><parameter-name>list.listMainId</parameter-name><parameter-value><![CDATA['
	       +listItem.id+']]></parameter-value></parameter>' +'<parameter><parameter-name>list.listName</parameter-name><parameter-value><![CDATA['
	       +encodeURI(listItem.title)+']]></parameter-value></parameter>' +'<parameter><parameter-name>list.listUrl</parameter-name><parameter-value><![CDATA['
	       +encodeURI(listItem.url)+']]></parameter-value></parameter>' +'<parameter><parameter-name>list.listDesc</parameter-name><parameter-value><![CDATA['
	       +encodeURI(listItem.summary)+']]></parameter-value></parameter>' +'</parameters>';    
	postAjaxXML('/control/addListItem.b',str,onCreateListItemComplete);
};
/*��������б�����Ӧ*/
function onCreateListItemComplete(ajax){
	if(ajax.readyState==4&&ajax.status==200){
		var xml=ajax.responseXML;
		var ms=getMessage(xml);
		if(isSuccess(xml)){
			var id=addObj.parentNode.parentNode.parentNode.parentNode.id;
			var oRow=this.$(id+'-table').insertRow(-1);
			var oCell=oRow.insertCell(-1);
			oCell.innerHTML='<a href="'+listItem.url+'">'+listItem.title+'</a>';
			oCell=oRow.insertCell(-1);
			oCell.innerHTML='<img onclick="delListItem(this,\''+listItem.id+'\',\''
			               +ms+'\')" style="cursor:hand" class="colose-col-btn2" src="http://blogteam.bokee.com/pub/images/close-icon-gray.gif" alt="ɾ������Ŀ" /></td>';
			
			if(listItem.summary !=null && listItem.summary.length >0){
				oRow=this.$(id+'-table').insertRow(-1);oCell=oRow.insertCell(-1);
				//oCell.innerHTML='<span class="textSpan">������'+listItem.summary+'</span>';
				oCell.innerHTML='<span class="textSpan">'+listItem.summary+'</span>';
				oCell=oRow.insertCell(-1);oCell.innerHTML='';
			}
		}
		else{
		        alert("���ʧ�ܣ�"+ms);
		}
	}
};
function delListItem(delObj,groupID,id){
	if(confirm('���Ƿ����ɾ�����')){
		saveDelObj=delObj;
		var str='<?xml version="1.0" encoding="GBK" ?><parameters><parameter><parameter-name>list.listMainId</parameter-name><parameter-value><![CDATA['
		       +groupID+']]></parameter-value></parameter>' +'<parameter><parameter-name>list.listId</parameter-name><parameter-value><![CDATA['
		       +id+']]></parameter-value></parameter>' +'</parameters>';
	        postAjaxXML('/control/delListItem.b',str,onDelListItemComplete);
	 }
};
/*����ɾ���б�����Ӧ*/
function onDelListItemComplete(ajax){
	if(ajax.readyState==4&&ajax.status==200){
		var xml=ajax.responseXML;
		var ms=getMessage(xml);
		if(isSuccess(xml)){
			var trObj=saveDelObj.parentNode.parentNode;
			var tableObj=trObj.parentNode;
			tableObj.removeChild(tableObj.rows[trObj.rowIndex+1]);
			tableObj.removeChild(tableObj.rows[trObj.rowIndex]);
		}
	}
	else{
	    alert("ɾ��ʧ�ܣ�"+ms);
	}
};
function delDiary(delObj,id){
	if(confirm('���Ƿ����ɾ������־��')){
		saveDelObj=delObj;
		diaryId=id;
		var str='<?xml version="1.0" encoding="GBK" ?><parameters>' +'<parameter><parameter-name>diaryId</parameter-name><parameter-value><![CDATA['
		       +diaryId+']]></parameter-value></parameter>' +'</parameters>';
		postAjaxXML('/control/delDiary.b',str,onDelDiaryComplete);
	}
};
/*����ɾ����־��Ӧ*/
function onDelDiaryComplete(ajax){
	if(ajax.readyState==4&&ajax.status==200){
		var xml=ajax.responseXML;
		var ms=getMessage(xml);
		if(isSuccess(xml)){
			var trObj=saveDelObj.parentNode.parentNode;
			var tableObj=trObj.parentNode;
			tableObj.removeChild(tableObj.rows[trObj.rowIndex]);
		}
	}
        else{
             alert("ɾ��ʧ�ܣ�"+ms);
        }
};
/*����ɾ����־��Ӧ*/
function delFriendBlogItem(delObj,id){
	if(confirm('���Ƿ����ɾ�������鲩�ͣ�')){
		saveDelObj=delObj;
		var str='<?xml version="1.0" encoding="GBK" ?><parameters>' 
		       +'<parameter><parameter-name>favoBlog.favoBlogId</parameter-name><parameter-value>'+id+'</parameter-value></parameter>' 
		       +'</parameters>';
	    postAjaxXML('/control/delFavoBlog.b',str,onFriendBlogComplete);
	 }
};

function onFriendBlogComplete(ajax){
	if(ajax.readyState==4&&ajax.status==200){
		var xml=ajax.responseXML;
		var ms=getMessage(xml);
		if(isSuccess(xml)){
			var trObj=saveDelObj.parentNode.parentNode;
			var tableObj=trObj.parentNode;
			tableObj.removeChild(tableObj.rows[trObj.rowIndex+1]);
			tableObj.removeChild(tableObj.rows[trObj.rowIndex]);
		}
	}
    else{
           alert("ɾ��ʧ�ܣ�");
    }
};

function saveDiary(){
	if(checkDiary()){
		$("diary.postSet").value=1;
		showLoad();
		changeElementState();
		postAjax("/control/doPostDiary.b","frm",onPostDiaryComplete);
	}
}
function postDiary(){
	if(checkDiary()){
		$("diary.postSet").value=0;
		showLoad();
		changeElementState();
		postAjax("/control/doPostDiary.b","frm",onPostDiaryComplete);
	}
}
function onPostDiaryComplete(){
	if(ajax.readyState==4){
		if(ajax.status == 200){
			var str;
			window.scrollTo(0,0); 
			var xml=ajax.responseXML; 
			if(isSuccess(xml)){	
				alert("��־����ɹ�");
				if($("diary.postSet").value==1){
					window.location.href='/control/diary/listDiary.b';
				}
				else{
					window.location.href='/control/diary/postDiary.b';
				}
			}
			else{
				str=getErrorStr();
				changeElementState();
				$("alert").innerHTML=str;
				$("alert").className ="stat-erro";
				showMessage();
			}
		}
		else{
			str=getErrorStr();
			changeElementState(); 
			$("alert").innerHTML=str;
			$("alert").className ="stat-erro";
			showMessage();
		}
	}
}
function createCategory(){
	if(Check.isNull("categoryName")){
		alert("��Ŀ���Ʋ���Ϊ�գ�");
		Field.focus("categoryName");
		return false;
	}
	var str='<?xml version="1.0" encoding="GBK" ?><parameters>' 
	       +'<parameter><parameter-name>diaryCategory.categoryName</parameter-name><parameter-value><![CDATA['
	       +encodeURI(trim($("categoryName").value))+']]></parameter-value></parameter>' +'</parameters>';
	postAjaxXML("/control/addCategory.b",str,onCategoryComplete);
}
function onCategoryComplete(){
	if(ajax.readyState==4){
	     if(ajax.status==200){
		var str;
		window.scrollTo(0,0);
		var xml=ajax.responseXML;
		var ms=getMessage(xml);
		if(isSuccess(xml)){
			addSelect($("categoryName").value,ms);
			$("categoryName").value='';
			$("createCategory").style.display='none';			
			$("alert").innerHTML='��Ŀ�����ɹ�';
			$("alert").className ="stat-ok";
		}
		else{
			$("alert").innerHTML=getErrorStr();
			$("alert").className ="stat-erro";
			changeElementState();
		}
	    }
	    else{
			$("alert").innerHTML=getErrorStr();
			$("alert").className ="stat-erro";
			changeElementState();
	    }
	    showMessage();
	}
}

function del(element){
   if(confirm('���Ƿ����ɾ����ģ�飿')){
      var node,node1;
      node=element.parentNode;
      if(node){
         node1=node.parentNode;
      }
      if(node1){
         if(node1.id.indexOf("user-list")==-1){
            node1.parentNode.removeChild(node1);
            var n=node1.cloneNode(false);
            n.innerHTML=node1.innerHTML;
            delObj[delObj.length]=n;
            var module=new Object();
            module.id=node1.id;
            module.flag=false;
            Module.editModule(module);
            var re=new RegExp(node1.id+"#","ig");
            saveUserModules=saveUserModules.replace(re,"");
            Element.show('alert');
          }
          else{
             if(confirm('ɾ���Ὣ���б��µ���������һ��ɾ�����Ƿ������')){
                var temp=node1.id.split("-");
                var str='<?xml version="1.0" encoding="GBK" ?><parameters><parameter><parameter-name>listMain.listMainId</parameter-name><parameter-value><![CDATA['+temp[2]+']]></parameter-value></parameter></parameters>';
                listNode=node1;
                postAjaxXML('/control/removeListMain.b',str,onRemoveListComplete);
              }
            }
         }
         else{}
         node=null;
         node1=null;
       } 
       initDndMgr();
};


function postTemplate(){
	postAjaxXML('/control/saveTemplate.b',createXML(),onChangeTemplateComplete);
	Element.hide('alert');	
};
function onChangeTemplateComplete(ajax){	
	if(ajax.readyState==4&&ajax.status==200){
		window.scrollTo(0,0);
		var xml=ajax.responseXML;
		if(isIE){
			if(isSuccess(xml)){
				window.location.reload(true);
			} 
			else{
				alert('ģ�����ʧ��!');
				canelTemplate();
				Element.hide('loadDiv');
				Element.hide('alert');
				Element.show('container');
			}
		}
		else{
			if(ajax.responseText.indexOf("SUCCESS")>-1 ){
				window.location.reload(true);
			} 
			else{
				alert('ģ�����ʧ��!');
				canelTemplate();
				Element.hide('loadDiv');
				Element.hide('alert');
				Element.show('container');
			}
		}
	}
};

function selectPhoto(){
	var diaType = "scrollbars=yes,resizable=no,help=no,status=no,center=yes,width=635px,height=360px,left="+(window.screen.width-635)/2+",top=300px";
		
	var selLoaction="/pub/neweditor/editor/imgInfo.htm?ver=20061107";
	win=window.open(selLoaction,"ѡ����Ƭ",diaType);	
}

function doUpdatePhoto(photoPath){
	if (photoPath!=null&&photoPath!=""){
		createPhotoImg(decodeURI(photoPath));
		photoPath = photoPath.replace("&","amp;");
		var sUrl = "/info/doUpdatePhoto.b?flg=3&photoAddress="+photoPath;
		postAjaxXML(sUrl , "" , showAjaxUpdateInfo);
	}
}

function createPhotoImg(photoPath){
	var imgSpan = document.getElementById("photoDiv");
	imgSpan.style.display = "block";
	document.getElementById("photoImg").src=photoPath;
}

function showAjaxUpdateInfo(ajax){
	if(ajax.readyState==4&&ajax.status==200){
		var xml=ajax.responseXML;		
		if (document.all){	
			closeWin();
			alert('���������޸ĳɹ�');
		}else{
			alert('���������޸ĳɹ�');
		}
	}
}
function closeWin(){
	if (win)
		{
			win.window.close();
		}
}

function statCount(domain){
	var date = new Date();
	var options=new Object();
	options.method="get";
	options.asynchronous=true;
	options.parameters="date="+date.getYear()+date.getMonth()+date.getDay()+date.getMinutes()+date.getSeconds()+"&action=10&username="+domain+"&oid="+domain+"_WC,"+domain+"_wh";
	options.onComplete=showAllCount;	
	
	var sUrl1 = "/stats/pvcounter.fcgi?date="+date.getYear()+date.getMonth()+date.getDay()+date.getMinutes()+date.getSeconds();
	new Ajax.Request(sUrl1, options);
	
	var sUrl2 = "/statDiary.b";	
	postAjaxXML(sUrl2 , "" , showOtherCount);
}

function showAllCount(ajax){
	if(ajax.readyState==4){
		if(ajax.status==200){
			var str = ajax.responseText;
			var temp = str.split(",");
			if(str == null || str.length==0 || temp.length != 2 ){
			  document.getElementById("numstat").innerHTML  = "���շ��ʣ�ͳ��ʧ��<BR/>"
			                                                + "��ʷ���ʣ�ͳ��ʧ��<BR/>";
			}
			else{
			  document.getElementById("numstat").innerHTML = "���շ��ʣ�<strong>"+temp[0]+"</strong><BR/>"
			                                               + "��ʷ���ʣ�<strong>"+temp[1]+"</strong><BR/>";
			}
		}
		else{
			document.getElementById("numstat").innerHTML  = "���շ��ʣ�ͳ��ʧ��<BR/>"
			                                              + "��ʷ���ʣ�ͳ��ʧ��<BR/>";
		}
	}
}

function showOtherCount(ajax){
	if(ajax.readyState==4){
		if(ajax.status==200){
			var str = ajax.responseText;
			if(str == null || str.length==0){
			   document.getElementById("diarystat").innerHTML = "��־����ͳ��ʧ��";
			}
			else{
			  document.getElementById("diarystat").innerHTML = str;
			}
		}
		else{
			 document.getElementById("diarystat").innerHTML = "��־����ͳ��ʧ��";
		}
	}
}

function getXMLHttpRequest(){
	if (window.ActiveXObject){
	 	return new ActiveXObject((navigator.userAgent.toLowerCase().indexOf('msie 5') != -1) ? 'Microsoft.XMLHTTP' : 'Msxml2.XMLHTTP');
	}
	else  if (window.XMLHttpRequest){
	 	return new XMLHttpRequest();
	}else{
	 	return null;
	}
}

function jionChatRoom(){
	if(getBlogID() != null)	{
		document.getElementById("chatRoomFrm").submit();
	}
	else{
		document.getElementById("chatRoomFrm").url.value = "http://"+window.location.host+"/control/showChat.b?chatNamePost1="+ encodeURI(document.getElementById("chatRoomFrm").chatNamePost.value);
		document.getElementById("chatRoomFrm").action = "http://reg.bokee.com/account/LoginCtrl.b";
		document.getElementById("chatRoomFrm").submit();
	}
}

function jionChatRoomMyPhoto(){
	if(getBlogID() != null)	{
		document.getElementById("chatRoomFrmMyPhoto").submit();
	}
	else{
		document.getElementById("chatRoomFrmMyPhoto").url.value = "http://"+window.location.host+"/control/showChat.b?chatNamePost1="+ encodeURI(document.getElementById("chatRoomFrmMyPhoto").chatNamePost.value);
		document.getElementById("chatRoomFrmMyPhoto").action = "http://reg.bokee.com/account/LoginCtrl.b";
		document.getElementById("chatRoomFrmMyPhoto").submit();
	}
}

function sendMsg(blog){
   var blogID=getBlogID();
   if(blogID == null){
   		alert('δ��½�����½!');   		
   		window.location.href='http://reg.bokee.com/account/web/login.jsp?url='+ window.location.href;
   		return;
   }
   window.location.href='http://'+blogID+'/mes/postMessage.b?message.receiver='+blog;
}


function commendblog(blog){
   var blogID=getBlogID();
   if(blogID == null){
   		alert('δ��½�����½!');   		
   		window.location.href='http://reg.bokee.com/account/web/login.jsp?url='+ window.location.href;
   		return;
   }

   var sUrl ="http://"+blogID+"/sn/commendblog.b?commend=" + blog;
   var diaType = "scrollbars=no,resizable=no,help=no,status=no,center=yes,width=400px,height=330px";
   window.open(sUrl,"",diaType);
}

function popPostMsg(blog){
   var blogID=getBlogID();
   if(blogID == null){
   		alert('δ��½�����½!');   		
   		window.location.href='http://reg.bokee.com/account/web/login.jsp?url='+ window.location.href;
   		return;
   }
   var sUrl ="http://"+blogID+"/mes/poppostmsg.b?message.receiver="+blog;
   var diaType = "scrollbars=no,resizable=no,help=no,status=no,center=yes,width=400px,height=330px";
   window.open(sUrl,"",diaType);
}
function popNote(blogID){
   var sUrl ="http://"+blogID+"/note/popnote.b";
   var diaType = "scrollbars=no,resizable=no,help=no,status=no,center=yes,width=400px,height=230px";
   window.open(sUrl,"",diaType);
}

function getBlogIDName(){
   var blogID=getBlogID();
   if (blogID !=null) {
   	return blogID.split(".")[0];
   	}else
   	{
   	return "";
   	}
}