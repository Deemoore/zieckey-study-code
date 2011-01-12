var arr = new Array();
function statDiaryHit(domain){
	var date = new Date();
	var options=new Object();
	var diaryStr= "";
	
	for(i=0;i<arr.length;i++){
		if(i<arr.length-1)
		   diaryStr += domain+"_vbi_"+getId(arr[i])+",";
		else
		   diaryStr += domain+"_vbi_"+getId(arr[i]);
	}
	
	options.method="get";
	options.asynchronous=true;
	options.parameters="date="+date.getYear()+date.getMonth()+date.getDay()+date.getMinutes()+date.getSeconds()+"&action=10&username="+domain+"&oid="+diaryStr;
	options.onComplete=showDiaryHit;		
	var sUrl = "/stats/pvcounter.fcgi?date="+date.getYear()+date.getMonth()+date.getDay()+date.getMinutes()+date.getSeconds();
	new Ajax.Request(sUrl, options);
}

function statPhoto(domain){
	var date = new Date();
	var options=new Object();
	var diaryStr= "";
	
	for(i=0;i<arr.length;i++){
		if(i<arr.length-1)
		   diaryStr += domain+"_vii_"+getId(arr[i])+",";
		else
		   diaryStr += domain+"_vii_"+getId(arr[i]);
	}
	options.method="get";
	options.asynchronous=true;
	options.parameters="date="+date.getYear()+date.getMonth()+date.getDay()+date.getMinutes()+date.getSeconds()+"&action=10&username="+domain+"&oid="+diaryStr;
	options.onComplete=showPhotoHit;
			
	var sUrl = "/stats/pvcounter.fcgi?date="+date.getYear()+date.getMonth()+date.getDay()+date.getMinutes()+date.getSeconds();
	new Ajax.Request(sUrl, options);
}

function putDiary(obj){
	arr[arr.length] = obj;
}

function putPhoto(obj){
	arr[arr.length] = obj;
}

function getId(obj){
    var str = obj.id.substring(1,obj.id.length);
	return 	str;
}

function showDiaryHit(ajax){
	if(ajax.readyState==4){
		if(ajax.status==200){
			var str = ajax.responseText;
			var temp = new Array();
			if(arr.length ==1)
				temp[0] = str;
			else
  			    temp = str.split(",");
			for(i=0;i<arr.length;i++){
				  arr[i].innerHTML = "�Ķ���"+ temp[i];
			}
		}
		else{
			for(i=0;i<arr.length;i++){
			  arr[i].innerHTML = "�Ķ���ͳ��ʧ��";
			}
		}
	}
}

function showPhotoHit(ajax){
	if(ajax.readyState==4){
		if(ajax.status==200){
			var str = ajax.responseText;
			var temp = new Array();
			if(arr.length ==1)
				temp[0] = str;
			else
  			    temp = str.split(",");
			for(i=0;i<arr.length;i++){
				  arr[i].innerHTML = temp[i];
			}
		}
		else{
			for(i=0;i<arr.length;i++){
			  arr[i].innerHTML = "ͳ��ʧ��";
			}
		}
	}
}

function statAll(domain){
	var options=new Object();		
	options.method="get";
	options.asynchronous=true;
	var date = new Date();
	options.parameters="date="+date.getYear()+date.getMonth()+date.getDay()+date.getMinutes()+date.getSeconds()+"&action=10&username="+domain+"&oid="+domain+"_WC,"+domain+"_wh,"+domain+"_vb,"+domain+"_vi,"+domain+"_vf";
	options.onComplete=showAll;		
	var sUrl = "/stats/pvcounter.fcgi?date="+date.getYear()+date.getMonth()+date.getDay()+date.getMinutes()+date.getSeconds();
	new Ajax.Request(sUrl, options);
}

function showAll(ajax){
	if(ajax.readyState==4){
		if(ajax.status==200){
			var str = ajax.responseText;
  			if(str == null || str.length == 0){
  				document.getElementById("numstat").innerHTML = "ͳ��ʧ��";
  				return ;
  			}
  			temp = str.split(",");
  			if(temp.length != 5){
  				document.getElementById("numstat").innerHTML = "ͳ��ʧ��";
  				return ;  				
  			}
  			
  			var html= "���շ��ʣ�<strong>"+temp[0]+"</strong>&nbsp;&nbsp;��ʷ���ʣ�<strong>"+temp[1]
  			        +"</strong>&nbsp;&nbsp;��־���ʣ�<strong>"+temp[2]+"</strong>&nbsp;&nbsp;ͼƬ���ʣ�<strong>"+temp[3]
  			        +"</strong>&nbsp;&nbsp;����ҳ����ʣ�<strong>"+temp[4]+"</strong>";
  			        
  			document.getElementById("numstat").innerHTML = html;
  			
		}
		else{
			document.getElementById("numstat").innerHTML = "ͳ��ʧ��";
		}
	}
}
