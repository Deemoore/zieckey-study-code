function check(){
		 
		if(document.fm.username.value==''){
			alert("用户名不能为空！");
			document.fm.username.focus();
			return false;
		} else if(document.fm.username.value.length>16){
			alert("用户名太长了!");
			document.fm.username.focus();
			return false;
		}
		if(document.fm.password.value == ''){
			alert("密码不能为空！");
			document.fm.password.focus();
			return false;
		} else if(document.fm.password.value.length>16){
			alert("密码太长了!");
			document.fm.username.focus();
			return false;
		}
		return true;
}

