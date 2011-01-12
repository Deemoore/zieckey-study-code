function stopRKey(evt) {
var evt = (evt) ? evt : ((event) ? event : null);
var node = (evt.target) ? evt.target : ((evt.srcElement) ? evt.srcElement : null);
if ((evt.keyCode == 13) && (node.type=="text")) { return false; }
}

function handleEnter (field, event) {
var keyCode = event.keyCode ? event.keyCode : event.which ? event.which : event.charCode;
if (keyCode == 13) {
var i;
for (i = 0; i < field.form.elements.length; i++)
if (field == field.form.elements[i])
break;
i = (i + 1) % field.form.elements.length;
field.form.elements[i].focus();
return false;
} 
else
return true;
} 

function openMailtoForm() {
url = "http://webcheatsheet.com/mailtofriend.php?url=" + document.location.href
w=window.open(url, "smileys", "fullscreen=no,toolbar=no,status=no,menubar=no,scrollbars=yes,resizable=yes,directories=no,location=no,width=400,height=220");
  if(!w.opener)
  {
  w.opener=self;
  }
}

function showHideComments() {
	if ($("#showcomments").html() == 'Hide Comments') {
		$("#allcomments").slideUp("fast");
		$("#showcomments").html('Show Comments');
	} else {
		$("#allcomments").slideDown("fast");
		$("#showcomments").html('Hide Comments');
	}	
	return false; 
}

function showHideForm() {
	if ($("#addcomment").html() == 'Hide Form') {
		$("#commentform").slideUp("fast");
		$("#addcomment").html('Add New');
	} else {
		$("#commentform").slideDown("fast");
		$("#addcomment").html('Hide Form');
		
	}
	return false; 
}

function validateName(fld) {
    var error = "";
  
    if (fld.value.length == 0) {
        fld.style.background = '#EBEBFE'; 
        error = "Please enter your name.\n"
    } else {
        fld.style.background = 'White';
    }
    return error;   
}

function validateEmpty(fld) {
    var error = "";
  
    if (fld.value.length == 0) {
        fld.style.background = '#EBEBFE'; 
        error = "Please enter your " + fld.name + ".\n"
    } else {
        fld.style.background = 'White';
    }
    return error;   
}

function validateComments(fld) {
    var error = "";
  
    if (fld.value.length == 0) {
        fld.style.background = '#EBEBFE'; 
        error = "Please enter some comments.\n"
    } else {
        fld.style.background = 'White';
    }
    return error;   
}

function trim(s) {
  return s.replace(/^\s+|\s+$/, '');
} 

function validateEmail(fld) {
    var error="";
    var tfld = trim(fld.value);                        // value of field with whitespace trimmed off
    var emailFilter = /^[^@]+@[^@.]+\.[^@]*\w\w$/ ;
    var illegalChars= /[\(\)\<\>\,\;\:\\\"\[\]]/ ;
    
    if (fld.value == "") {
        //fld.style.background = '#EBEBFE';
        //error = "Please enter an email address.\n";
		return error;
    } else if (!emailFilter.test(tfld)) {              //test email for illegal characters
        fld.style.background = '#EBEBFE';
        error = "Please enter a valid email address.\n";
    } else if (fld.value.match(illegalChars)) {
        fld.style.background = '#EBEBFE';
        error = "The email address contains illegal characters.\n";
    } else {
        fld.style.background = 'White';
    }
    return error;
}

function sendComments() 
{ 
	var reason = "";

	reason += validateName($("#name")[0]);
	reason += validateEmail($("#email")[0]);
	reason += validateComments($("#comments")[0]);
      
	if (reason != "") {
		alert("Some fields need correction:\n" + reason);
	} else {
		$("div#allcomments").html("<div class=\"commentsuccess\"><span style=\"position:relative; top:0; left:0;\"><img src=\"/images/animated_loading.gif\"/></span><span style=\"position:relative; top:-4; left:10;\">Loading ...</span></div>");
		showHideForm();		
		$.post("/bitrix/templates/template1/scripts/addDisplayComments.php",
		{	
			action: 	$("#action").val(),
			name: 		$("#name").val(),
			email: 		$("#email").val(),
			comments: 	$("#comments").val(),
			//captcha: 	$("#captcha").val(),
			selfURL: 	document.location.href
		},
		function(txt){
			$("div#allcomments").html(txt);
			$("img#captcha").attr("src","/bitrix/templates/template1/scripts/captcha_image.php?" + Math.random());
		});
	}
}
	
function blogIt() 
{ 
	var reason = "";

	reason += validateEmpty($("#username")[0]);
	reason += validateEmpty($("#password")[0]);
	reason += validateEmpty($("#title")[0]);
	reason += validateEmpty($("#text")[0]);
      
	if (reason != "") {
		alert("Some fields need correction:\n" + reason);
	} else {
		$.post("/bitrix/templates/template1/scripts/proxy.php", 
		{
			blogtype: 	  $("#blogtype").val(),
			username: 	  $("#username").val(),
			pwd: 		  $("#password").val(),
			blogurl: 	  $("#blogurl").val(),
			title: 		  $("#title").val(),
			blog_content: $("#text").val(),
			selfURL : 	  $("#selfURL").val()
		},
		function(xml){
			var txt_type = $("blogtype",xml).text();
			var txt_response = $("blogresponse",xml).text();
			$("div#blog_response").html(txt_response);
			switch (txt_type)
			{
				case "livejournal" :
					if ($(".update-errors").text()) {
						$("div#blog_condition").html("<div class=\"commenterror\">" + $(".update-errors").text() + "</div>");
					} else if ($("div.errorbar").html()) {
						$("div#blog_condition").html("<div class=\"commenterror\">" + $("div.errorbar").html() + "</div>");
					} else {
						$("div#blog_condition").html(txt_response);
					}
					break;
				default :
				 alert("There is no such flower in our shop");
				 break;
			}
			$("div#blog_response").html("");
		});
		$("#blog_condition").html("<div class=\"commentsuccess\"><span style=\"position:relative; top:0; left:0;\"><img src=\"/images/animated_loading.gif\"/></span><span style=\"position:relative; top:-4; left:10;\">Loading ...</span></div>");
	}
}
		
function authorArticles() 
{ 
	$("div#about_author").html($("div#articles_list").html());
}

function contactAuthor(author) 
{
	$("div#tabcontent").html($("div#contact_author").html());
}

function sendEmailToAuthor()
{
	var reason = "";

	reason += validateEmpty($("#name")[0]);
	reason += validateEmpty($("#email")[0]);
	reason += validateEmail($("#email")[0]);
	reason += validateEmpty($("#message")[0]);
      
	if (reason != "") {
		alert("Some fields need correction:\n" + reason);
	} else {
		$.post("/bitrix/templates/template1/scripts/contactauthor.php",
		{	
			action: 	$("#action").val(),
			name: 		$("#name").val(),
			email: 		$("#email").val(),
			message: 	$("#message").val(),
			captcha: 	$("#captcha").val(),
			selfURL: 	document.location.href
		},
		function(txt){
			$("div#tabcontent").html(txt);
			$("#imgCaptcha").attr("src","/bitrix/templates/template1/scripts/captcha_image.php?" + Math.random());
		});
	}
}

function selectNode(node) {
   var selection, range, doc, win;
   if ((doc = node.ownerDocument) && (win = doc.defaultView) && typeof
win.getSelection != 'undefined' && typeof doc.createRange != 'undefined'
&& (selection = window.getSelection()) && typeof
selection.removeAllRanges != 'undefined') {
     range = doc.createRange();
     range.selectNode(node);
     selection.removeAllRanges();
     selection.addRange(range);
   }
   else if (document.body && typeof document.body.createTextRange !=
'undefined' && (range = document.body.createTextRange())) {
     range.moveToElementText(node);
     range.select();
   }
}

$(document).ready(function () {
	$("select.action").change(function() {
		if (this.options[this.selectedIndex].text == "Select All") {
			selectNode(this.parentNode.parentNode);
			this.selectedIndex = 0;
		} else if (this.options[this.selectedIndex].text == "Try It") {
			var newwindow;
			var link = document.location.href;
			var section = link.split("/");
			url = "http://www.webcheatsheet.com/tryit/index.php?section="+section[section.length-2]+"&example="+this.options[this.selectedIndex].value;
			newwindow=window.open(url,'name','fullscreen=no,toolbar=yes,status=no,menubar=yes,scrollbars=yes,resizable=yes,directories=no,location=yes');
			if (window.focus) {newwindow.focus()}
			this.selectedIndex = 0;
		}
	});
});