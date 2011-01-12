/* -----------------------------------------------
Title: Header Script
Author: Jarid Love
Modified: 02 Oct 2008 (Added Edit Profile Link)
Modified-by: Jarid Love
----------------------------------------------- */

/* Navigation Menu Functions
---------------------------------------------------- */
function showNovellMenuWithSlide() {
	var mnuContainer = document.getElementById("n_menu");
	mnuContainer.mouseOverMnu = true;
	if(mnuContainer.hideTimer) {
		clearTimeout(mnuContainer.hideTimer);
		mnuContainer.hideTimer = null;
	}
	if(mnuContainer.style.height == "auto" || mnuContainer.slideInProgress) return;
	with(mnuContainer.style) {
		height = "0px";
		display = "block";
	}
	mnuContainer.mnuHeight = getItemHeight(document.getElementById("n_menu_content"));
	hidePlugins();
	slideMenu(1);
}

function hideNovellMenu() {
	// called by flash menu
	hideNovellMenuWithoutSlide(0);
}

function hideNovellMenuWithSlide(delay) {
	var mnuContainer = document.getElementById("n_menu");
	mnuContainer.mouseOverMnu = false;
	if(mnuContainer.slideInProgress || mnuContainer.style.height == "0px") return;
	mnuContainer.mnuHeight = getItemHeight(document.getElementById("n_menu_content"));
	if(delay && delay > 0) mnuContainer.hideTimer = setTimeout("slideMenu(-1)", delay);
	else slideMenu(-1);
}

function slideMenu(direction) {
	var mnuContainer = document.getElementById("n_menu");
	if(mnuContainer.mouseOverMnu == false && direction == 1) direction = -1;
	if(mnuContainer.mouseOverMnu == true && direction == -1) direction = 1;
	mnuContainer.slideInProgress = true;
	var rerunFunction = true;
	if(mnuContainer.style.height == "auto" && direction == -1) document.getElementById("n_menu_close").firstChild.innerHTML = mnuContainer.openMsg;
	
	// calculate new height
	var containerHeight =  getItemHeight(mnuContainer);
	var mnuHeight =  mnuContainer.mnuHeight;

	var newHeight = (direction > 0) ? containerHeight + Math.max(1,(mnuHeight - containerHeight)/mnuContainer.slideSpeed) : (containerHeight == 71) ? 0 : containerHeight - Math.max(1,(containerHeight-71)/mnuContainer.slideSpeed);

	if(newHeight >= mnuHeight) {
		newHeight = mnuHeight;
		rerunFunction = false;
	}
	else if(newHeight <= 1){
		newHeight = 0;
		rerunFunction = false;
	}

	// set height and position
	document.getElementById("n_menu_content").style.top = Math.min(0,newHeight - mnuHeight)+"px";
	mnuContainer.style.height = newHeight + "px";
	
	// determine if rerun or end
	if(rerunFunction) setTimeout("slideMenu("+direction+")",20);
	else {
		if(newHeight <= 1) {
			mnuContainer.style.display = "none";
			showPlugins();
		}
		else {
			mnuContainer.style.height = "auto";
			document.getElementById("n_menu_close").firstChild.innerHTML = mnuContainer.closeMsg; 
		}
		if(mnuContainer.callback && mnuContainer.callback.length > 0) {
			eval(mnuContainer.callback);
			mnuContainer.callback = null;
		}
		mnuContainer.slideInProgress = false;
	}
}

function createLiLink(href,txt) {
	var li = document.createElement("li");
	li.innerHTML = '<a href="'+href+'">'+txt+'</a>';
	return li;
}

function addNavToHdr() {
	document.getElementById("n_menu_content").innerHTML=nhdr_nav;
}

function initNovellMenu() {
	addNavToHdr();
	
	var mnuContainer = document.getElementById("n_menu");
	if(!mnuContainer) return false;
	
	mnuContainer.slideSpeed = 3;
	mnuContainer.slideInProgress = false;
	/*mnuContainer.parentNode.onmouseout = function() {
		if(this.showTimer) {
			clearTimeout(this.showTimer);
			this.showTimer = null;
		}
	}*/
	document.getElementById("hdr_lnks_menu").onmouseover = function() {
	//mnuContainer.parentNode.onmouseover = function() {
		this.showTimer = setTimeout("showNovellMenuWithSlide()",200);
		this.onmouseout = function() {
			if(this.showTimer) {
				clearTimeout(this.showTimer);
				this.showTimer = null;
			}
		}
	}
	mnuContainer.onmouseover = showNovellMenuWithSlide;
	mnuContainer.onmouseout = function() {
		hideNovellMenuWithSlide(500);
	}
	
	mnuContainer.closeMsg = "- "+nhdr_mnuclose;
	mnuContainer.openMsg = "+ "+nhdr_mnuopen;

	var closeBtn = document.createElement("div");
	closeBtn.id = "n_menu_close";
	closeBtn.innerHTML = '<a href="#" onclick="hideNovellMenuWithSlide();this.blur();return false;">'+mnuContainer.closeMsg+'</a>';
	mnuContainer.appendChild(closeBtn);
	
	var menuCanopy = document.createElement("div");
	menuCanopy.id = "n_menu_canopy";
	mnuContainer.appendChild(menuCanopy);

	var homeLink = document.getElementById("hdr_home").cloneNode(true);
	homeLink.id = "n_menu_home";
	menuCanopy.appendChild(homeLink);
	
	var mnuLnk = document.getElementById("hdr_lnks_menu").getElementsByTagName("a")[0];
	mnuLnk.onclick = function() {
		if(showNovellMenuWithSlide) showNovellMenuWithSlide();
		return false;	
	}
	
	return true;
}

/* Search Functions
---------------------------------------------------- */
function submitHdrSrch() {
	if((this.query.value.length == 0) || (this.query.value == nhdr_search)) {
		alert(nhdr_search_fail);
		return false;
	}
	if(this.collection.value == "Support;SupportWeb") this.theme.value = "support";
	return true;
}

function initSrch() {
	var hdrSrchFrm = document.getElementById("hdr-srch-frm");
	hdrSrchFrm.onsubmit = submitHdrSrch;
	if(n_lang != null && n_lang.toLowerCase() != "en-us") hdrSrchFrm.collection.value = "Novell-"+n_lang;
	switch(n_root) {
		case "news" : hdrSrchFrm.collection.value = "NovellPress"; break;
		case "support" : hdrSrchFrm.collection.value = "Support;SupportWeb"; break;
	}
	switch(n_domain) {
		case "developer.novell.com" : {
			hdrSrchFrm.collection.value = "developer;dev_ndk";
			hdrSrchFrm.bbindex.value = "NDKBestBets";
			break;
		}
		case "support.novell.com" : hdrSrchFrm.collection.value = "Support;SupportWeb"; break;
	}
	if (hdrSrchFrm.retencoding) {
		hdrSrchFrm.encoding.value = hdrSrchFrm.retencoding.value = n_enc;
		hdrSrchFrm.elements["lang"].value = (n_lang != null)?n_lang.split("-")[0]:"en";
		hdrSrchFrm.elements["country"].value = (n_country!=null)?n_country.substring(0,2):"US";
	}
}

/* Language Functions
---------------------------------------------------- */
function getLangLink() {
	var langMsgTxt = nhdr_create_account;
	if(langCompatible) {
		var langLnk = document.createElement("li");
		langLnk.id = "n_lang_select";
		var langLnkA = document.createElement("a");
		langLnkA.href = ss+"/common/util/langselect.php?referer="+escape(location.href);
		var langStr = nhdr_changelang;
		switch(n_lang) {
			case "de-de" : langStr = "Deutsch"; langMsgTxt = "Diese Seite steht leider noch nicht in der von Ihnen gew&#228;hlten Sprache zur Verf&#252;gung."; break; 
			case "fr-fr" : langStr = "Fran&#231;ais"; langMsgTxt = "D&#233;sol&#233;, cette page n'est pas encore disponible dans la langue que vous avez s&#233;lectionn&#233;e."; break; 
			case "es-es" : langStr = "Espa&#241;ol"; langMsgTxt = "Esta p&#225;gina todav&#237;a no est&#225; disponible en el idioma seleccionado. Disculpen las molestias."; break; 
			case "it-it" : langStr = "Italiano"; langMsgTxt = "La pagina richiesta non &#232; ancora disponibile nella lingua selezionata."; break; 
			case "nl-nl" : langStr = "Nederlands"; langMsgTxt = "Deze pagina is nog niet in de door u geselecteerde taal beschikbaar."; break; 
			case "cs-cz" : langStr = "&#269;e&#353;tina"; langMsgTxt = "Omlouv&#225;me se, tato str&#225;nka nen&#237; je&#353;t&#283; k dispozici pro v&#225;mi zvolen&#253; jazyk."; break; 
			case "zh-cn" : langStr = "&#20013;&#25991;(&#31616;&#20307;)"; langMsgTxt = "&#25265;&#27465;&#65292;&#26412;&#39029;&#23578;&#19981;&#33021;&#20197;&#24744;&#25152;&#36873;&#30340;&#35821;&#35328;&#26174;&#31034;&#12290;"; break; 
			case "zh-tw" : langStr = "&#20013;&#25991;(&#32321;&#20307;&#65289;"; langMsgTxt = "&#24456;&#25265;&#27465;&#65292;&#26412;&#32178;&#38913;&#30446;&#21069;&#23578;&#28961;&#24744;&#25152;&#36984;&#21462;&#30340;&#35486;&#35328;&#29256;&#26412;&#12290;"; break; 
			case "ja-jp" : langStr = "&#26085;&#26412;&#35486;"; langMsgTxt = "&#30003;&#12375;&#35379;&#12372;&#12374;&#12356;&#12414;&#12379;&#12435;&#12364;&#12289;&#12371;&#12398;&#12506;&#12540;&#12472;&#12399;&#12414;&#12384;&#12362;&#23458;&#27096;&#12364;&#36984;&#25246;&#12375;&#12383;&#35328;&#35486;&#12395;&#32763;&#35379;&#12373;&#12428;&#12390;&#12356;&#12414;&#12379;&#12435;"; break; 
			case "hu-hu" : langStr = "Magyar"; langMsgTxt = "Az oldal a v&#225;lasztott nyelven egyenl&#245;re nem el&#233;rhet&#245;."; break; 
			case "pl-pl" : langStr = "Polski"; langMsgTxt = "Przepraszamy, ta strona jeszcze nie jest dost&#234;pna w wybranym j&#234;zyku."; break; 
			case "pt-br" : langStr = "portugu&#234;s (Brasil)"; langMsgTxt = "Infelizmente, esta p&#225;gina ainda n&#227;o est&#225; dispon&#237;vel no idioma selecionado."; break; 
			case "ru-ru" : langStr = "&#1056;&#1091;&#1089;&#1089;&#1082;&#1080;&#1081;"; langMsgTxt = "&#1055;&#1088;&#1080;&#1085;&#1086;&#1089;&#1080;&#1084; &#1089;&#1074;&#1086;&#1080; &#1080;&#1079;&#1074;&#1080;&#1085;&#1077;&#1085;&#1080;&#1103;, &#1076;&#1072;&#1085;&#1085;&#1072;&#1103; &#1089;&#1090;&#1088;&#1072;&#1085;&#1080;&#1094;&#1072; &#1074; &#1085;&#1072;&#1089;&#1090;&#1086;&#1103;&#1097;&#1080;&#1081; &#1084;&#1086;&#1084;&#1077;&#1085;&#1090; &#1085;&#1077;&#1076;&#1086;&#1089;&#1090;&#1091;&#1087;&#1085;&#1072; &#1085;&#1072; &#1074;&#1099;&#1073;&#1088;&#1072;&#1085;&#1085;&#1086;&#1084; &#1103;&#1079;&#1099;&#1082;&#1077;."; break; 
			case "sv-se" : langStr = "Svenska"; langMsgTxt = "Tyv&#228;rr finns inte den h&#228;r sidan p&#229; ditt valda spr&#229;k &#228;nnu."; break; 
			case "fi-fi" : langStr = "Suomi"; langMsgTxt = "Sorry, this page is not yet available in your selected language."; break; 
			case "da-dk" : langStr = "Dansk"; langMsgTxt = "Sorry, this page is not yet available in your selected language."; break;
			case "no-no" : langStr = "Norsk"; langMsgTxt = "Denne siden er desverre ikke tilgjengelig i valgt spr&#229;k."; break;
		}
		langLnkA.innerHTML = nhdr_changelang;
		langLnk.appendChild(langLnkA);
		if(typeof(showNotTranslatedMsg) != "undefined" && showNotTranslatedMsg) {
			var noTrnsltnMsg = document.createElement("p");
			noTrnsltnMsg.id = "n_lang_notavailable";
			noTrnsltnMsg.innerHTML = langMsgTxt;
			document.getElementById("hdr").appendChild(noTrnsltnMsg);
		}
		return langLnk;
	}
	return null;
}

function swapHdrLang() {
	if(n_lang == 'en-us') return;
	var homeImg = document.getElementById("hdr_home").getElementsByTagName("img")[0];
	homeImg.alt = nhdr_home;
	var skipLnk = document.getElementById("hdr_lnks_skip").getElementsByTagName("a")[0];
	skipLnk.innerHTML = nhdr_slip;
	var mnuLnk = document.getElementById("hdr_lnks_menu").getElementsByTagName("a")[0];
	mnuLnk.innerHTML = "+ " + nhdr_mnuopen;
	var srchBox =  document.getElementById("hdr-srch-input");
	//srchBox.value = nhdr_search;
}

/* Login/Out functions
---------------------------------------------------- */
function addLoginBlock() {
	if(typeof isLoggedIn == "undefined") return;

	var loginLnkA = document.createElement("a");
	loginLnkA.href = (isLoggedIn) ? getSecureUrl()+"/cmd/ICSLogout" : (location.pathname.indexOf("communities") >= 0) ?  "/communities/login?destination="+location.pathname.replace("/communities/","") : getSecureUrl().replace("secure-","")+"/ICSLogin/?%22"+location.href+"%22";
	loginLnkA.innerHTML = (isLoggedIn) ? nhdr_logout : nhdr_login;

	var loginLnk = document.createElement("li");
	loginLnk.appendChild(loginLnkA);

	var loginSubLnks = document.createElement("ul");
	var linkAcct = document.createElement("li");
	var acctTxt = (isLoggedIn) ? ((typeof nhdr_edit_account != 'undefined') ? nhdr_edit_account : "Edit My Profile") : nhdr_create_account;
	var acctUrl = getSecureUrl() + ((isLoggedIn) ? '/selfreg/jsp/protected/manageAccount.jsp' : '/selfreg/jsp/createAccount.jsp');
	linkAcct.innerHTML = '<a href="'+acctUrl+'">'+acctTxt+'</a>';
	loginSubLnks.appendChild(linkAcct);
	var linkLang = getLangLink();
	if(linkLang) loginSubLnks.appendChild(linkLang);
	loginLnk.appendChild(loginSubLnks);

	var loginUl = document.createElement("ul");
	document.getElementById("n_menu_login").appendChild(loginUl);
	loginUl.appendChild(loginLnk);
		
	/*	if(isLoggedIn) {
			var hdrUserName = document.createElement("p");
			var fName = escape(FIRSTNAME);
			var lName = escape(LASTNAME);
			hdrUserName.id = "hdr_username";
			hdrUserName.innerHTML = "<strong>"+nhdr_welcome+"</strong><br />"+decodeURI(fName)+" "+decodeURI(lName);
		}
	*/ //No longer part of the header
 }

/* Initialize
---------------------------------------------------- */
function initHdr() {
	if(!isDOM) return;
	if(typeof lang_redir != "undefined" && lang_redir) {
		document.body.style.display = "none"; // don't render if doing lang redir to speed up redirect
		return;
	}

	var hasMenu = initNovellMenu();
	if(hasMenu) {
		addLoginBlock();
		initSrch();
		swapHdrLang();
	}
	
	// remove styles for printer friendly
	if(window.name == "printer_friendly") {
		for ( i = 0; i < document.styleSheets.length; i++ ) {
			if (document.styleSheets[i].title && document.styleSheets[i].title == "Printer Friendly") document.styleSheets[i].disabled = false;
			else document.styleSheets[i].disabled = true;
		}
	}
}

initHdr();