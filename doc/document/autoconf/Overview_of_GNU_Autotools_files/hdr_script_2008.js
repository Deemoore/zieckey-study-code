/* -----------------------------------------------
Title: Common script
Author: Jarid Love

Modified: 12 Nov 2009 by Jarid Love
Comment: Printer friendly changs for sitepublisher generated pages

Modified: 29 Oct 2009 by Jarid Love
Comment: Added wwwqatest

Modified: 16 Sep 2009 by Connor Boyack
Comment: Added novell_lang_redirect_refer cookie

Modified: 20 Apr 2009 by Jarid Love
Comment: Added n_root3 (ccoray)
----------------------------------------------- */

/* Environment Variables
---------------------------------------------------- */
var isSSL = (location.protocol == "https:")?true:false;
var isStage = (location.href.indexOf("stage") > 0 || location.href.indexOf("usability") > 0) ? true : false;
var isTest = (location.href.indexOf("wwwtest.provo.novell.com") > 0  || location.href.indexOf("wwwqatest.provo.novell.com") > 0) ? true : false;
var isDev = (location.href.indexOf("wwwdev.provo.novell.com") > 0) ? true : false;
var redirect = (location.href.indexOf("forceRedirect=false") > 0) ? false: true;
function getSecureUrl() {
	return (isDev)?"https://secure-wwwdev.provo.novell.com":(isTest)?"https://secure-wwwtest.provo.novell.com":(isStage)?((location.href.indexOf("usability") > 0)?"http://usabilitytest.novell.com":"https://secure-wwwstage.provo.novell.com"):"https://secure-www.novell.com";
}

var s = (isDev)?"http://wwwdev.provo.novell.com":(isTest)?"http://wwwtest.provo.novell.com":(isStage)?((location.href.indexOf("usability") > 0)?"http://usabilitytest.novell.com":"http://wwwstage.provo.novell.com"):"http://www.novell.com";
var ss = (isSSL)? getSecureUrl() : s;
var n_domain = location.host; 
var n_dirs = location.pathname.split("/");
var n_root = (n_dirs.length>=2)?n_dirs[1]:null;
var n_root2 = (n_dirs.length>=3)?n_dirs[2]:null;
var n_root3 = (n_dirs.length>=4)?n_dirs[3]:null;
var n_root4 = (n_dirs.length>=5)?n_dirs[4]:null;

var isDOM = document.getElementById?true:false; // all DOM based browsers including IE
var isNS4 = document.layers?true:false;
var isIE = document.all?true:false;
var isMac = (navigator.appVersion.indexOf("Mac") != -1)?true:false;
var isWin = (navigator.appVersion.indexOf("Win") != -1)?true:false;
var isLinux = (navigator.platform.indexOf("Linux") != -1)?true:false;
var usragent = navigator.userAgent.toLowerCase();
var isOperaBadDom = (usragent.substr(usragent.indexOf("opera")+6,1)<=6)?true:false; // this detects opera 6 or below which have crappy DOM support
var isOperaGoodDom = (usragent.substr(usragent.indexOf("opera")+6,1)>6)?true:false;
var isKonqueror = (usragent.indexOf("konqueror")>=0)?true:false;
var langCompatible = (isDOM && n_domain.indexOf("novell.com") >= 0);

/* Cookie Functions
---------------------------------------------------- */
function readCookie(name) {
	var cks = document.cookie.split(';');
	for(var i=cks.length-1; i >= 0; i--) {
		var c = cks[i];
		while(c.charAt(0)==' ') {
			c = c.substring(1,c.length);
		}
		if(c.indexOf(name+"=")==0) {
			return c.substring(name.length+1,c.length);
		}
	}
	return null;
}

function deleteCookie(name,path,domain) {
	if(readCookie(name)) { document.cookie = name + "=" +
		((path) ? ";path=" + path : ";path=/") +
		((domain) ? ";domain=" + domain : ";domain=.novell.com") +
		";expires=Thu, 01-Jan-1970 00:00:01 GMT";
	}
}

function createCookie(name,value,days,path,domain) {
	var expires = "";
	if(days) {
		var date = new Date();
		date.setTime(date.getTime()+(days*24*60*60*1000));
		expires = "; expires="+date.toGMTString();
	}
	document.cookie = name+"="+value+expires +
		((path) ? ";path=" + path : ";path=/") +
		((domain) ? ";domain=" + domain : ";domain=.novell.com");
}

function getQueryParm(name) {
	var params = document.params;
	if(!params) {
		document.params = (location.search.substring(1)).split("&");
		params = document.params;
	}
	for(var i = 0; i < params.length; i++) {
		var param = params[i].split("=");
		if(param[0] == name) {
			return param[1];
		}
	}
	return null;
}

/* Localization Functions
---------------------------------------------------- */
function getPageCharset() {
	var mt = document.getElementsByTagName('meta');
	for(var i=0; i<mt.length; i++) {
		var ct = mt[i].getAttribute('content');
		if(ct != null && ct.toLowerCase().indexOf('charset=') != -1) {
			return ct.substring(ct.toLowerCase().indexOf('charset=')+8);
		}
	}
	return "UTF-8";
}

var n_lang = readCookie("novell_language");
var n_country = readCookie("novell_country");
var n_cnt=(n_country!=null && n_country.length>3)?n_country.substring(0,2):"US";
var n_enc = getPageCharset();

/*
if(n_lang == null) {
	createCookie("n_hasCkSupport","true",365);
	var n_hasCkSupport = readCookie("n_hasCkSupport");
	if(n_hasCkSupport == "true") {
		window.location.replace(s+"/common/util/langselect.php?referer="+escape(location.href));
	}
}
*/

function siteSupportsLang() {
	var n_lang_sites = ["supportstage.provo.novell.com","support.novell.com",s.substring(7,s.length)]; // sites that support localization
	for(var i = n_lang_sites.length-1;i > -1; i--) {
		if(n_domain == n_lang_sites[i]) {
			return true;
		}
	}
	return false;
}

function isNonEnglishDir(dir) {
	if(dir == null) {
		return false;
	}
	var langDirs = ["de-de","es-es","fr-fr","it-it","nl-nl","cs-cz","zh-cn","zh-tw","ja-jp","hu-hu","pl-pl","pt-br","ru-ru","sv-se","fi-fi","da-dk","no-no"];
	for(var i = langDirs.length-1; i > -1; i--) {
		if(langDirs[i] == dir) {
			return true;
		}
	}
	return false;
}

function isFilteredRootDir(dir) {
	switch(dir) {
		case "communities" :
		case "rc" :
		case "cgi-bin" :
		case "servlet" :
		case "global" :
		case "ICSLogin" :
		case "ICHAINLogout" :
			return true;
		default :
			return false;
	}
}

function setLang(lang) {
	createCookie("novell_language",lang,365);
}

function setCountry(co,coname) {
	createCookie("novell_country",co+"|"+coname,(co == "") ? 0 : 365);
}

function getNovellTranslation(arry) {
	var txt = arry[n_lang];
	if(!txt) {
		txt = arry["en-us"];
	}
	return txt;
}

/* Localization Redirect
---------------------------------------------------- */
if(siteSupportsLang() && langCompatible && typeof is404Page == "undefined") {
	if(n_lang==null) {
		// no lang set so set it and leave on current page
		if(typeof defaultPageLang != "undefined" && typeof defaultPageCntry != "undefined") {
			n_lang = defaultPageLang;
			n_country = defaultPageCntry;
			n_co_array = n_country.split("|");
			setCountry(n_co_array[0],n_co_array[1]);
		}
		else {
			n_lang = isNonEnglishDir(n_root) ? n_root : "en-us"; // no language selected or cookies not supported so default to lang of current lang dir
		}
		setLang(n_lang);
	}
	else if(redirect==true && !isFilteredRootDir(n_root)) {
		var isPlone = (typeof is_plone != 'undefined' && is_plone) ? true : false;
		if(isPlone || location.pathname.indexOf(".htm") >= 0 || location.pathname.lastIndexOf('/') == location.pathname.length-1) {
			if(isNonEnglishDir(n_root) && n_root != n_lang) {
				// user navigated to different lang dir so change language
				n_lang = n_root;
				setLang(n_lang);
			}
			else if((n_lang != "en-us" && n_root != n_lang) || (n_lang == "en-us" && isNonEnglishDir(n_root)) || (n_root2 == null && n_cnt != "US") || (n_lang == n_root && n_root2 != null && (n_root2.length == 2 || isPlone) && n_root2 != n_cnt)) {
				if(readCookie("novell_lang_redirect_refer")==null){ //only set value if one has not already been set
					createCookie("novell_lang_redirect_refer", document.referrer, 1);
				}
				
				// not in correct lang location
				if(isPlone && location.pathname.indexOf("home") < 0) {
					// file is plone generated so redirect to lang path
					var targetUrl = location.protocol+"//"+location.hostname;
					if(n_lang != "en-us" || (n_lang == "en-us" && n_cnt != "US")) {
						targetUrl += "/"+n_lang;
						if(n_cnt != "US") {
							targetUrl += "/"+n_cnt;
						}
					}
					var targetPath = (isNonEnglishDir(n_root) || n_root == "en-us") ?  location.pathname.substring(6) : location.pathname;
					targetPath = (n_root2 != null && n_root2.length == 2 && n_root2.search(/[A-Z][A-Z]/) > -1) ? targetPath.substring(3) : targetPath;
					targetUrl += targetPath + location.search;
					if(targetUrl != location.href) {
						window.location.replace(targetUrl);
					}
				}
				else {
					// the following include checks the file system to see if there is a better location to redirect to based on country/lang
					document.write('<script type="text/javascript" src="/common/util/langredirect.php?url='+escape(location.href)+'"><\/script>');
				}
			}
		}
	}
}

/* Include menu script, css, and local phone number
---------------------------------------------------- */
var n_phone_js = (n_lang != null && n_lang != "en-us") ? "/"+n_lang : "";
if(n_country != null && n_country != "US|United States"){
	n_phone_js += "/"+n_country.substring(0,2);
}
document.write('<script type="text/javascript" src="' + ss + n_phone_js + '/sitewide/contact/sales/contact_phone_var_js"><\/script>');

if(isDOM) { 
	if(window.name == "printer_friendly") {
		document.write('<link rel="stylesheet" type="text/css" href="'+ss+'/common/inc/printerfriendly.css" title="Printer Friendly" />');
		var s_prop15=location.href;
	}
	document.write('<script type="text/javascript" src="'+ss+'/common/inc/nav/main_2008.js"><\/script>');
	var hasHdrNav = true; 
}

function showPrinterFriendly() {
	if(document.getElementById("contentcontainer") || document.getElementById("pageContent") || (typeof jQuery != 'undefined' && ($('.pageContainer') || $('.contentContainer')))) {
		var pfwindow = window.open(location.href,"printer_friendly");
		pfwindow.focus();
	}
	else {
		window.open(s+'/inc/pf/pf.jsp?url='+escape(location.href)+'&sourceid=PrinterFriendlyFromFooter');
	}
}

/* Load Translated Text
---------------------------------------------------- */
function loadHdrTransltion(suffix) {
	suffix = (suffix == null || suffix == 'en-us' || n_lang == null) ? 'en-us' : suffix;
	document.write('<script type="text/javascript" src="'+ss+'/common/inc/local/hdr_menu_2009_'+suffix+'.js"><\/script>');
}
if(n_domain.indexOf("novell.de") >= 0) {
	loadHdrTransltion("de-de");
}
else if(n_domain.indexOf("novell.co.jp") >= 0) {
	loadHdrTransltion("ja-jp");
}
else {
	loadHdrTransltion((typeof navlang!="undefined") ? navlang : n_lang);
}

/* login/out functions
---------------------------------------------------- */
function getLoginStatus() {
	var cks = document.cookie.split(';');
	for(var i=0; i < cks.length; i++) {
		var c = cks[i];
		while(c.charAt(0)==' ') {
			c = c.substring(1,c.length);
		}
		if(c.indexOf("IPC")==0 && c.indexOf("=")==16) {
			document.write('<script type="text/javascript" src="'+ss+'/inc/util/secure/userInfo.jsp"><\/script>');
			return true;
		}
	}
	return false;
}
var isLoggedIn = getLoginStatus();

/* Misc get functions
---------------------------------------------------- */
function getRandomInt(min, max) {
	return (min >= max) ? max : Math.floor(((max+1 - min)*Math.random())+min);
}

function getItemWidth(obj) {
	var width = obj.clientWidth;
	return (width == 0) ? obj.offsetWidth : width;
}

function getItemHeight(obj) {
	var height = obj.clientHeight;
	return (height == 0) ? obj.offsetHeight : height;
}

function getXY(obj) {
	var intX = 0;
	var intY = 0;
	try {
		do { // Walk up our document tree until we find the body and add the distance from the parent to our counter.
			intX += obj.offsetLeft;
			intY += obj.offsetTop;
			obj = obj.offsetParent;
		} while(obj.tagName != "BODY" && obj.tagName != "HTML")
	}
	finally {
		return new Array(intX,intY);
	}
}

/* ajax page load functions
---------------------------------------------------- */
function novl_createRequest() {
	return (window.XMLHttpRequest) ? new XMLHttpRequest() : (window.ActiveXObject) ? new ActiveXObject("MSXML2.XMLHTTP") : null;
}

function novl_sendGetRequest(request,path,callbackSuccess,callbackFail) {
	request.open("GET", path, true);
	request.onreadystatechange = function() {
		if(request.readyState == 4) {
			if(request.status == 200) callbackSuccess(request);
			else if(callbackFail) callbackFail(request); // callback fail is optional
		}
	}
	request.send(null);
}

/* open link in new window (mainly for links to external site)
---------------------------------------------------- */
function openExternal(URL, w, h, s, n, r) {
	// It is possible to bypass w and h by passing in 'noW', 'noH'
	var attr = "";
	if(typeof w != "undefined" && w!= 'noW') attr += "width=" + w;
	if(typeof h != "undefined" && h != 'noH') attr += ",height=" + h;
	if(attr.length > 0) { // when no width or height is specified, use window core defaults, do not add any other values
		attr += (typeof s != "undefined" && s == true) ? ',scrollbars=yes' : ',scrollbars=no'; // default on sized window = no scrollbars
		attr += (typeof r != "undefined" && r == false) ? ',resizable=no' : ',resizable=yes'; // default on sized window = resizable
	}
	if(attr.charAt(0)==",") attr = attr.substring(1);
	var winExt = (!n) ? window.open(URL,'_blank',attr) : window.open(URL,n,attr);
	if(winExt && winExt.blur) winExt.focus();
}

function requestCall() {
	openExternal(ss+'/company/sales_call_request_popup.html?a7='+getQueryParm("a7")+'&profile_url='+location.href,560,640);
}


/* Functions to hide/show plugins (ie. flash)
---------------------------------------------------- */
function hidePlugins(hideall) {
	// hide select boxes in IE versions > 7 because they show through menus
	var agt=navigator.userAgent.toLowerCase();
	if(isIE && (agt.indexOf("msie 4") >= 0 || agt.indexOf("msie 5") >= 0 || agt.indexOf("msie 6") >= 0)) {
		var selects = document.getElementsByTagName("select");
		for(var i = selects.length-1; i >=0 ; i--) {
			selects[i].style.visibility = "hidden";
		}
	}
	// hide flash content because it shows through navigation
	if(typeof flash != "undefined") {
		// if flash.forcehide, hide property has been manually set
		// if linux, wmode not supported, so hide flash
		// if flash version is less than 6,0,79,0 hide flash because wmode not supported widely
		if(flash.forcehide || isLinux || (flash.version <= 6 && flash.rev < 79) || isOperaGoodDom) hideFlash(hideall);
	}
	hiddenElmnts = true;
};

function hideFlash(hideall) {
	for(var i = 0; i < flash.movies.length; i++) {
		var elmt = document.getElementById("flash_"+i);
		var y = getXY(elmt)[1];
		if ((y > 0 && y < 418) || (typeof hideall != 'undefined' && hideall == 'all')) {
			//elmt.parentNode.style.background = "#e7e7e7";
			elmt.style.visibility = 'hidden';
		}
	}
};

function showPlugins(hideall) {
	// show select boxes in IE versions > 7 that were hidden because they show through menus
	var agt=navigator.userAgent.toLowerCase();
	if(isIE && (agt.indexOf("msie 4") >= 0 || agt.indexOf("msie 5") >= 0 || agt.indexOf("msie 6") >= 0)) {
		var selects = document.getElementsByTagName("select");
		for(var i = selects.length-1; i >=0 ; i--) {
			selects[i].style.visibility = "inherit";
		}
	}
	// show flash content that was hidden because it shows through navigation
	if(typeof flash != "undefined") {
		if(flash.forcehide || isLinux || (flash.version <= 6 && flash.rev < 79) || isOperaGoodDom) showFlash(hideall);
	}
	hiddenElmnts = false;
};

function showFlash(hideall) {
	for(var i = 0; i < flash.movies.length; i++) {
		var elmt = document.getElementById("flash_"+i);
		var y = getXY(elmt)[1];
		if ((y > 0 && y < 418) || (typeof hideall != 'undefined' && hideall == 'all')) {
			elmt.style.visibility = 'visible';
		}
	}
};


// Function for opening links from flash; variables stored on individual pages
function openPopup()
{
	if(typeof openUrl == 'undefined') return false;
	window.open(openUrl,'_blank',addParams);
};