function check(){
		 
		if(document.fm.username.value==''){
			alert("�û�������Ϊ�գ�");
			document.fm.username.focus();
			return false;
		} else if(document.fm.username.value.length>16){
			alert("�û���̫����!");
			document.fm.username.focus();
			return false;
		}
		if(document.fm.password.value == ''){
			alert("���벻��Ϊ�գ�");
			document.fm.password.focus();
			return false;
		} else if(document.fm.password.value.length>16){
			alert("����̫����!");
			document.fm.username.focus();
			return false;
		}
		return true;
}

