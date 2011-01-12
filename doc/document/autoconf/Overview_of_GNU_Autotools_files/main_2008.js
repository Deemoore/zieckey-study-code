/* -----------------------------------------------
Title: Menu Script Source File
Author: Jarid Love
Modified: 04 Oct 2005
----------------------------------------------- */

var cMT = null; // current menu tree
var cMnu = null; // current menu
var mHT = null; // menu hide timer
var mST = null; // menu show timer
var mOM = false; // mouse on menu boolean
var tM = []; // top menus array
var isHC = false; // is header created boolean
var hiddenElmnts = false; // to identify if flash and form elements have been hidden
var fc = ["#6B6C69","#000000","#FFFFFF","#FFFFFF"]; // font color
var fc_o = ["#000000","#FFFFFF","#FFFFFF","#FFFFFF"]; // font color on mouseover
var bg = ["transparent","#C8C8C8","#6B6C69","#2E3436"]; // background color
var bg_o = ["#C8C8C8","#6B6C69","#2E3436","#000000"]; // background color on mouseover

// left navigation creation function
function createLeftNav(menuId) {
	cMnu = null;
	var mArray = eval("menu_" + menuId);
	cMT = { width:152,x:12 };
	tM[tM.length] = cMn(menuId,false);
	if(typeof lnavTrail != "undefined") {
		var lnavTrailObj = document.createElement("div");
		lnavTrailObj.innerHTML = lnavTrail;
		tM[tM.length-1].appendChild(lnavTrailObj);
	}
	var rowCount = mArray.length;
	//var lnavContact = document.getElementById("subnav-contact");
	//if(rowCount > 9 && lnavContact) lnavContact.style.top = (350 + (20*(rowCount-9))) + "px";
	var lnavFlash = document.getElementById("lnavflashpromo");
	if(lnavFlash) lnavFlash.style.top = (150 + document.getElementById("menu1").offsetHeight + 15) + "px";
};

// cMn = create menu (creates individual menu items)
function cMn(menuId) {
	var lyr = document.createElement("DIV");
	lyr.id = "menu" + menuId;
	lyr.className = "ddmnu-mnu-sub";
	lyr.a = eval("menu_" + menuId);
	lyr.itemCount = 0;
	lyr.tree  = cMT;
	lyr.showL = showL;
	lyr.hideL = hideL;
	lyr.onmouseover = menuOn;
	lyr.onmouseout = menuOut;
	lyr.hideT = hideT;
	lyr.hideChildren = hideCM;
	lyr.hasCVisible = false;
	lyr.isOn = false;
	lyr.currentItem = null;
	
	// set style attributes
	var l_s = lyr.style;
	if(cMnu) {
		// if current menu exists, this is not a top level menu so set arributes differently
		l_s.left = l_s.top = "-200px";
		l_s.width = cMT.width + "px";
		lyr.parentMenu = cMnu;
		lyr.level = cMnu.level+1;
		lyr.parentRow = cMnu.row;
		lyr.parentRow.child = lyr;
		lyr.hasParent = true;
	}
	else {
		// top level menu
		l_s.left = cMT.x + "px";
		l_s.width = "138px";
		lyr.hasParent = false;
		cMT.treeParent = lyr;
		lyr.level = 1;
		lyr.isOn = true;
		lyr.topBarItm = null;
		lyr.btmBarItm = null;
		if(!document.getElementById("contentcontainer")) l_s.top = eval("menu_" + menuId)[0][2];
	}
	
	l_s.backgroundColor = bg[lyr.level-1];
	
	// for each menu item create a row & set it's position
	cMnu = lyr;
	var itr = lyr.a.length-1;
	while(itr--) {
		cMnu.itemCount++;
		var row = createRow(menuId);
		if(row) {
			cMnu.row = row;
			cMnu.appendChild(row);
			if(row.hasMore) {
				var childMenu = cMn(menuId+"_"+cMnu.itemCount);
				if(childMenu) cMnu = cMnu.parentMenu;
			}
		}
	}
	
	if(lyr.level == 1) {
 		if(cMnu.topBarItm != null) cMnu.topBarItm.className += " ddmnu-top";
 		if(cMnu.btmBarItm != null) cMnu.btmBarItm.className += " ddmnu-btm";
	}
	
	// add new menu to page in predefined div
	document.getElementById("subnav").appendChild(lyr);
	return cMnu;
};

function createRow(menuId) {
	// create row div object and basic variables
	var row = document.createElement("DIV");
	row.className = "ddmnu-row ddmnu-row-l" + cMnu.level;
	row.id = "row" + menuId + "_" + cMnu.itemCount;
	row.menu = cMnu;
	row.tree = cMT;
	row.index = cMnu.itemCount - 1;
	row.child = null;
	
	// set colors
	row.a = cMnu.a[cMnu.itemCount];
	if(row.a[9] == 2) {
		row.hasMore = false;
		row.className += " ddmnu-keylnk";
	}
	else row.hasMore = row.a[9];
	if((cMnu.level == 1 && row.a[9] != 2) || (cMnu.level == 1 && row.index == 0)) {
		if(row.index == 0) {
			cMnu.topBarItm = row;
		}
		cMnu.btmBarItm = row;
	}
	row.fc = fc[cMnu.level-1];
	
	rowLink = row.a[1];
	if(rowLink && rowLink.length > 0) {

		currentLink = location.href;
		if(currentLink.indexOf("://") > 0) {
			currentLink = currentLink.substring(currentLink.indexOf("://")+3);
			currentLink = currentLink.substring(currentLink.indexOf("/"));
		}
		if(currentLink.indexOf("index.htm") > 0) currentLink = currentLink.substring(0,currentLink.indexOf("index.htm"));
		
		if(rowLink.indexOf("://") > 0) {
			rowLink = rowLink.substring(rowLink.indexOf("://")+3);
			rowLink = (rowLink.indexOf("/") > 0) ? rowLink.substring(rowLink.indexOf("/")) : rowLink = "";
		}
		if(rowLink.indexOf("index.htm") > 0) rowLink = rowLink.substring(0,rowLink.indexOf("index.htm"));
		
		if(currentLink == rowLink) {
			row.className += " currentpage";
			row.fc = "#000000";
		}
	}
	
	row.fc_o = fc_o[cMnu.level-1];
	row.bg = bg[cMnu.level-1];
	row.bg_o = bg_o[cMnu.level-1];
	if(row.className.indexOf("ddmnu-keylnk") < 0) {
		row.onmouseover = rowOn;
		row.onmouseout = rowOut;
		row.showCM = showCM;
	}
	else {
		row.onmouseover = keyOn;
	}

	// set div object style attributes
	var r_s = row.style;
	r_s.backgroundColor = row.bg;
	r_s.color = row.fc;
	
	// set row text & link
	var linktxt = (typeof row.a[1] == 'undefined') ? "" : row.a[1];
	
	// create interior text of div object
	if(linktxt.length>0 && linktxt != "#") {
		if(row.hasMore) {
			//row.imageSrc = ((typeof isExternalSite != "undefined" && isExternalSite) ? ss : "") + "/common/img/nav-arrrow.gif";
			row.innerHTML = '<a class="ddmnu-link" href="'+linktxt+'" style="color:'+r_s.color+';"><span>'+row.a[0]+'&nbsp;&nbsp;<em>&gt;</em></span></a>';
		}
		else {
			row.innerHTML = '<a class="ddmnu-link" href="'+linktxt+'" style="color:'+r_s.color+';"><span>'+row.a[0]+'</span></a>';
		}
		
	}
	else {
		if(row.hasMore) {
			row.innerHTML = '<div class="ddmnu-empty">'+row.a[0]+'&nbsp;&nbsp;<em>&gt;</em></div>';
		}
		else {
			row.innerHTML = '<div class="ddmnu-empty">'+row.a[0]+'</div>';
		}
	}

	if(cMnu.level == 1) {
		var subClass = (cMnu.topBarItm == row) ? 'ddmnu-top"' : '';
		if(cMnu.btmBarItm == row) subClass = 'ddmnu-btm"';
		row.innerHTML = '<div class="ddmnu-inner">'+row.innerHTML+'</div>';
	}

	return row;
};

function keyOn() {
	cMnu.hideT()
}

function menuOn() {
	var t_tp = this.tree.treeParent;
	if(!t_tp) t_tp = this;
	if(t_tp == this) hidetM(this);
	mOM = true;
	cMnu = this;
	if(mHT) clearTimeout(mHT);
};

function menuOut() {
	mOM = false;
	mHT = setTimeout("cMnu.hideT()",600);
};

// hidetM = hide tree menu
function hidetM(callingmenu) {
	for(var i = tM.length-1; i >= 0; i--) {
		var topMenu = tM[i].tree.treeParent;
		if(topMenu == callingmenu) continue;
		if(topMenu.hasCVisible) topMenu.hideChildren();
		if(topMenu.isOn) topMenu.hideL();
	}
};

function rowOn() {
	//if(this.menu.level == 1) this.menu.style.width = "152px";
	this.style.backgroundColor = this.bg_o;
	if(this.getElementsByTagName('a').length == 1) this.getElementsByTagName('a')[0].style.color = this.fc_o;
	else this.style.color = this.fc_o;
	if(this.menu.hasCVisible) {
		var v_c = this.menu.visibleChild;
		if(v_c == this.child && v_c.hasCVisible) v_c.hideChildren(this);
		else this.menu.hideChildren(this);
	}
	if(this.menu.currentItem && this.menu.currentItem != this) {
		var current = this.menu.currentItem;
		current.style.backgroundColor = current.bg;
		if(current.getElementsByTagName('a').length == 1) current.getElementsByTagName('a')[0].style.color = current.fc;
		else current.style.color = current.fc;
		//if(current.hasMore) current.style.backgroundImage = "url(" + current.imageSrc + ")";
	}
	this.menu.currentItem = this;
	if(this.hasMore) {
		//this.style.backgroundImage = "";
		this.showCM();
	}
};

function rowOut() {
	if(!this.menu.hasCVisible) {
		this.style.backgroundColor = this.bg;
		//if(this.menu.level == 1) this.menu.style.width = "138px";
		if(this.getElementsByTagName('a').length == 1) this.getElementsByTagName('a')[0].style.color = this.fc;
		else this.style.color = this.fc;
		//if(this.hasMore) this.style.backgroundImage = "url(" + this.imageSrc + ")";
	}
};

// showL = show links
function showL() {
	if(this.tree.treeParent != this) {
		if(!hiddenElmnts) hidePlugins();
		this.style.visibility = "visible";
		this.isOn = true;
	}
};

// hideL = hide links
function hideL() {
	if(this.tree.treeParent != this) {
		this.style.visibility = "hidden";
		this.isOn = false;
	}
	if(this.currentItem) {
		var current = this.currentItem;
		current.style.backgroundColor = current.bg;
		//if(this.level == 1) current.menu.style.width = "138px";
		if(current.getElementsByTagName('a').length == 1) current.getElementsByTagName('a')[0].style.color = current.fc;
		else current.style.color = current.fc;
		//if(current.hasMore) current.style.backgroundImage = "url(" + current.imageSrc + ")";
	}
	this.currentItem = null;
};

// hideT = hide tree
function hideT() {
	clearTimeout(mHT);
	if(mOM) return;
	if(this.hasCVisible) this.hideChildren(this);
	var menu = this;
	menu.hideL();
	while(menu.hasParent) {
		menu = menu.parentMenu;
		menu.hideL();
	}
    if(hiddenElmnts) showPlugins();
};

// showCM = show child menu
function showCM() {
	var menu = this.menu;
	var c_s = this.child.style;
	c_s.top = (parseInt((menu.style.top) ? menu.style.top : menu.offsetTop) + this.offsetTop) + "px";
	c_s.left = (parseInt((menu.style.left) ? menu.style.left : menu.offsetLeft) + parseInt(this.offsetWidth)) + "px";
	menu.hasCVisible = true;
	menu.visibleChild = this.child;
	this.child.showL();
};

// hide child menu
function hideCM(caller) {
	var menu = this.visibleChild;
	while(menu.hasCVisible) {
		menu.visibleChild.hideL();
		menu.hasCVisible = false;
		menu = menu.visibleChild;
	}
	if((caller && (!caller.hasMore || this.visibleChild != caller.child)) || (!caller && this.isOn)) {
		this.visibleChild.hideL();
		this.hasCVisible = false;
	}
};