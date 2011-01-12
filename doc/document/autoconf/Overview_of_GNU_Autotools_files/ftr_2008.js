/* -----------------------------------------------
Title: Footer Script
Author: Jarid Love

Modified: 16 Sep 2009
Modified-by: Connor Boyack
Change: Added novell_lang_redirect_refer cookie detection for language redirects

Modified: 04 Jul 2009
Modified-by: Connor Boyack
Change: Added search tracking code

Modified: 15 Jun 2009
Modified-by: Connor Boyack
Change: Added setA7Cookie()

----------------------------------------------- */

/* Used by searchRAC to grab query params
---------------------------------------------------- */
function gup(name, URL){
	name = name.replace(/[\[]/,"\\\[").replace(/[\]]/,"\\\]");
	var regexS = "[\\?&]"+name+"=([^&#]*)";
	var regex = new RegExp( regexS );
	if((URL == null) || (URL == ""))
		URL = window.location.href; //get current URL if none is supplied
	var results = regex.exec( URL );
	if( results == null )
		return "";
	else
		return results[1];
}

/* Track search terms and URLs for RAC conversions
---------------------------------------------------- */
function searchRAC(){
	// code to track adwords
	var gAdword = getQueryParm("google_adword");
	if(gAdword && gAdword != null) document.cookie = "google_adword=GooglePS:"+gAdword+";path=/;domain=.novell.com";

	// code to track newsletter links
	var gnews = getQueryParm("gnews");
	if(gnews && gnews != null) document.cookie = "g_newsletter=GlobalNews:"+gnews+";path=/;domain=.novell.com";

	// code to track visitors from search engines
	var referrer = document.referrer;
	var query = "";

	var issearchref = /google|yahoo|msn|bing|baidu/.test(referrer);
	
	if(!issearchref){
		referrer = readCookie("novell_lang_redirect_refer");
		issearchref = /google|yahoo|msn|bing|baidu/.test(referrer); //try the language redirect original referrer
		deleteCookie("novell_lang_redirect_refer");
	} 
	
	var gclid = gup("gclid", window.location.href); //check and see if they're using google adwords
	var utm = gup("utm_campaign", window.location.href); //check and see if they're using other paid search services
	var campaign = gup("campaign", window.location.href); //paid search campaign name
	var keyword = gup("keyword", window.location.href); //paid search keyword

	if(issearchref || (gclid != "") || (utm != "")){
		if(/google|bing/.test(referrer)){ //is google or bing?
			query = gup("q", referrer);
		}
		if(/yahoo/.test(referrer)){ //is yahoo
			query = gup("p", referrer);
		}
		if(/baidu/.test(referrer)){ //is yahoo
			query = gup("wd", referrer);
		}
		if(query != "")
			query = query.replace(/\+/g, "%20");

		var search_type;
		if((gclid == "") && (utm == "")){ //no keyword, so they're natural search
			search_type = "natural";
			query = "N: " + query;
		}
		else{ //they're paid search
			search_type = "paid";
			query = "P: " + query;
		}
		
		
		//how long should the cookie live?
		var cookie_date = (search_type == "paid") ? 30 : 1;

		//save search type
		createCookie("novell_search_type", search_type, cookie_date);

		//set cookie w/ search string for one day
		createCookie("novell_search", query, cookie_date);

		//save landing page URL
		createCookie("novell_search_landing", window.location.href, cookie_date);

		//save campaign name
		createCookie("novell_search_campaign", campaign, cookie_date);

		//save paid keyword
		createCookie("novell_search_paid_keyword", keyword, cookie_date);
	}
}

/* Set A7 cookie
---------------------------------------------------- */
function setA7Cookie() {
	var a7 = getQueryParm("a7");
	if(a7){
		createCookie("novell_a7", a7, 1); //set the a7 cookie for one day
	}
}

/* Add Printer Friendly
---------------------------------------------------- */
function addPf() {
	if(window.name != "printer_friendly") {
		if(typeof nftr_pf == "undefined") return;
		var li = document.createElement("li");
		li.id = "ftr_pf";
		li.innerHTML = '<a href="javascript:showPrinterFriendly();void(true);">'+nftr_pf+'</a>';
		
		var ftrLnks = document.getElementById("ftr_nav");
		var ftrLang = document.getElementById("ftr_language");
		if(ftrLang) ftrLnks.insertBefore(li,ftrLang);
		else ftrLnks.appendChild(li);
	}
}

/* Language Swap
---------------------------------------------------- */
function swapFtrLang() {
	if(n_lang == 'en-us') return;
	var ftr = document.getElementById("ftr_nav");
	if(ftr) {
		var lnks = ftr.getElementsByTagName("a");
		for(var i = lnks.length-1; i > -1; i--) {
			switch(lnks[i].parentNode.id) {
				case "ftr_careers" : lnks[i].innerHTML = nftr_careers; break;
				case "ftr_contact" : lnks[i].innerHTML = nftr_contact; break;
				case "ftr_fb" : lnks[i].innerHTML = nftr_feedback; break;
				case "ftr_privacy" : lnks[i].innerHTML = nftr_legal; break;
			}
			if(isStage) lnks[i].href = lnks[i].href.replace("www.novell.com","wwwstage.provo.novell.com");
		}
		document.getElementById("ftr_copy").innerHTML = nftr_copywrite;
	}
}

/* tag line popup function
---------------------------------------------------- */
function openTagLinePopup(popupUrl) {
	window.open(popupUrl,"_blank","width=676,height=797");
	return false;
}

/* Init
---------------------------------------------------- */
function initFtr() {
	if(!isDOM) return;

	if(typeof hasLeftNav != 'undefined' && hasLeftNav) {
		createLeftNav("1"); // create js left nav menus
	} else {
		var lnav = document.getElementById("left_nav"); // create html left nav menus
		if(lnav) {
			var lnavItems = lnav.getElementsByTagName("li");
			for(var i=0; i<lnavItems.length; i++) {
				lnavItems[i].onmouseover=function() { this.className="on"; hidePlugins(); }
				lnavItems[i].onmouseout=function(){ this.className="off"; showPlugins(); }
				var lnavItmLnks = lnavItems[i].getElementsByTagName("a");
				if(lnavItmLnks.length > 0 && window.location.href == lnavItmLnks[0].href) lnavItmLnks[0].innerHTML = "<strong>"+lnavItmLnks[0].innerHTML+"</strong>";
			}
		}
	}

	addPf();
	swapFtrLang();
	setA7Cookie();
	searchRAC();
	document.getElementById("ftr_fb").getElementsByTagName("a")[0].onclick = function() {
		window.open(this.href+'?url='+escape(top.location.href),'web_fb','width=560,height=600,resizable=yes,scrollbars=no');
		return false;
	}
}

initFtr();
