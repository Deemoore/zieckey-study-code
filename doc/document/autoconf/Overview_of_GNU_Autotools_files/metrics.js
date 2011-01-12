/* -----------------------------------------------
Title: Coremetrics Custom Script
Author: Jarid Love
Modified: 09 Oct 09 by Jarid Love
          "Added separate google account id for video"
----------------------------------------------- */
if(location.href.indexOf('register.novell.com') > -1) {
	var oldOnload = window.onload;
	window.onload = function() {
		cmRegInitiation();
		cmRegComplete();
		if(oldOnload) oldOnload();
	}
}
if(location.href.indexOf('surveyutil') > -1) {
	var oldOnload = window.onload;
	window.onload = function() {
		cmCreateManualLinkClickTag (url,trackingTag,siteArea);
		if(oldOnload) oldOnload();
	}
}

function cmRegInitiation() {
	var regLinks = document.getElementById('content').getElementsByTagName('a');
	for(var i = 0; i < regLinks.length; i++) {
		if(regLinks[i].href.indexOf('register.jsp') > -1 || regLinks[i].href.indexOf('action=lname_login') > -1) {
			regLinks[i].onclick = cmRegProcess;
		}
	}
	if(location.href.indexOf('register.novell.com/simple') > -1) {
		document.getElementById('fname').onfocus = cmRegProcess;
	}
}

function cmRegProcess() {
	var eventName=document.getElementsByTagName('h1')[0].innerHTML.replace(/Event Registration<br>/i,'');
	cmCreateConversionEventTag(eventName,'1','Event Registration');
	createCookie('EventRegName',eventName);
}

function cmRegComplete() {
	if(location.href.indexOf('register.novell.com/register/?action=dsp_confirm') > -1) {
		var eventName = readCookie('EventRegName',eventName);
		if(eventName != null) {
			cmCreateConversionEventTag(eventName,'2','Event Registration');
			deleteCookie('EventRegName');
		}
	}
}
function initMetrics() {
	if(typeof n_root == "undefined") {
		var n_dirs = location.pathname.split("/");
		var n_root = (n_dirs.length>=2)?n_dirs[1]:null;
		var n_root2 = (n_dirs.length>=3)?n_dirs[2]:null;
		var n_root3 = (n_dirs.length>=4)?n_dirs[3]:null;
		var n_root4 = (n_dirs.length>=5)?n_dirs[4]:null;
	}

	var urlDir1 = n_root;
	var urlDir2 = n_root2;
	var urlDir3 = n_root3;
	var pageId = null; // if pageid is null, coremetrics code will use url
	var Catg = 'MARKETING'; // default category

	if(typeof n_pageId != 'undefined' && n_Catg != 'undefined') {
		pageId = n_pageId;
		Catg = n_Catg;
	}
	else {
		switch(n_root) {
			case "de-de" :
			case "es-es" :
			case "fr-fr" :
			case "it-it" :
			case "nl-nl" :
			case "cs-cz" :
			case "ja-jp" :
			case "zh-cn" :
			case "zh-tw" :
			case "hu-hu" :
			case "pl-pl" :
			case "pt-br" :
			case "ru-ru" :
			case "sv-se" :
			case "da-dk" :
			case "fi-fi" :
			case "no-no" :
				urlDir1 = n_root2;
				urlDir2 = n_root3;
				urlDir3 = n_root4;
				break;
		}

		if(typeof n_domain == 'undefined') n_domain = 'www.novell.com';

		if(n_domain.indexOf('developer') >= 0) {
			Catg = 'COMMUNITIES';
		}
		else if(n_domain.indexOf('support') >= 0) {
			Catg = 'SUPPORT';
		}
		else if (n_domain.indexOf('download') >= 0) {
			Catg = 'DOWNLOAD';
		}
		else if(location.href.indexOf('/company/sales_call_request_popup.html') >= 0 || location.href.indexOf('/inc/feedback.php') >= 0) {
			Catg = 'UTILS';
		}
		else {
			switch(urlDir1) {
				case "products" :
				case "solutions" :
					Catg = (urlDir2 == null || urlDir2 == "") ? 'MARKETING' : urlDir2;
					break;
				case "linux" :
					Catg = 'LINUX';
					break;
				case "news" :
					Catg = 'NEWS';
					break;
				case "promo" :
					Catg = 'PROMO';
					break;
				case "success" :
					Catg = 'SUCCESS';
					break;
				case "surveyutil" :
					Catg = 'COLLATERAL';
					break;
				case "coolsolutions" :
					Catg = 'COOL SOLUTIONS';
					break;
				case "communities" :
				case "community" :
					Catg = 'COMMUNITIES';
					break;
				case "knowledgebase" :
				case "support" :
					Catg = 'SUPPORT';
					break;
				case "company" :
					Catg = 'COMPANY';
					break;
				case "connectionmagazine" :
					Catg = 'CONNECTION MAGAZINE';
					break;
				case "training" :
					Catg = 'TRAINING';
					break;
				case "consulting" :
				case "documentation" :
					Catg = 'SERVICES';
					break;
				case "center" :
				case "customercenter" :
					Catg = 'CUSTOMER CENTER';
					break;
			}
			switch (urlDir2) {
				case "blogs" :
					Catg = 'COMMUNITIES';
					break;
				case "coolsolutions" :
					Catg = 'COOLSOLUTIONS';
					break;
				case "nui" :
					Catg = 'NUI'
					break;
				case "partners" :
					Catg = 'PARTNERS';
					break;
				case "zenworks" :
					Catg = (urlDir3 == null || urlDir3 == "") ? 'ZENWORKS' : urlDir3;
					break;
			}
		}

		if(location.href.indexOf('howdoyoulinux') > -1) {
			Catg = 'HOW DO YOU LINUX';
			pageId = "How Do You Linux";
		}
		if(location.href.indexOf('geekobuilder') > -1) {
			Catg = 'GEEKO BUILDER';
			pageId = "Geeko Builder";
		}
		if(location.href.indexOf('surveyutil/survey.jsp') > -1) {
		   Catg = 'COLLATERAL';
		   pageId = "Survey: " + getQueryParm('id');
		}
	}

	if(typeof isStage == 'undefined' || (!isStage && !isTest && !isDev)) {
		cmSetProduction();
	}
	if(typeof isSearch == 'undefined') cmCreatePageviewTag(pageId,Catg,null,null); // PageID, CategoryID/NAME, Search String, # of Search Results Returned
}

initMetrics(location.host);

function cmInitiation(eventName,eventCat,points) {
	eventName = (!eventName) ? '' : eventName;
	eventCat = (!eventCat) ? '' : eventCat;
	points = (!points) ? '' : points;
    cmCreateConversionEventTag(eventName,'1',eventCat,points);
}

function cmCompletion(eventName,eventCat,points) {
	eventName = (!eventName) ? '' : eventName;
	eventCat = (!eventCat) ? '' : eventCat;
	points = (!points) ? '' : points;
    cmCreateConversionEventTag(eventName ,'2',eventCat,points);
}

function flashClick(url,trackingTag,siteArea) {
	url = (!url) ? '' : url;
	trackingTag = (!trackingTag) ? '' : trackingTag;
	siteArea = (!siteArea) ? '' : siteArea;
	cmCreateManualLinkClickTag (url,trackingTag,siteArea);
}

function flashEvent(trackingTag,siteArea) {
	trackingTag = (!trackingTag) ? '' : trackingTag;
	siteArea = (!siteArea) ? '' : siteArea;
	cmCreatePageElementTag(trackingTag,siteArea);
}

// begin google analytics code
var gaJsHost = (("https:" == document.location.protocol) ? "https://ssl." : "http://www.");
document.write(unescape("%3Cscript src='" + gaJsHost + "google-analytics.com/ga.js' type='text/javascript'%3E%3C/script%3E"));
var gaNovellKey = "UA-3367212-1";
var gaNovellKey_video = "UA-9518721-1";
if(isStage || isTest || isDev) {
	gaNovellKey = "UA-3367212-4";
	gaNovellKey_video = "UA-9518721-3";
}
// end google analytics code