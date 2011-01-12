/* 这里修改推荐内容 text: 显示内容 url: 访问链接 */
var hotList = [
{ text: "最牛程序员奋斗历程"
, url: "http://topic.csdn.net/u/20090908/18/09923fa2-6ace-45dd-bac0-5551c19f21b4.html"
}
, { text: "VFP导出excel的方法探讨"
, url: "http://topic.csdn.net/u/20090910/08/01B1FAF5-02AA-40CE-BA73-BBA959F2F59A.html"
}
, { text: "40岁互联网遭遇中年危机"
, url: "http://topic.csdn.net/u/20090908/15/5abc2589-213e-4ee3-af6a-b52422ece78c.html"
}
, { text: "海量数据库相关处理问题"
, url: "http://topic.csdn.net/u/20090909/11/B71C160F-18C1-417E-9B8A-FC5BDF1A65BB.html"
}
, { text: "选择.Net 今年3K 明年6K"
, url: "http://www.rzhh.com.cn/"
}
];

var hotVersion = "2009091001";

function setCookie(name, value, days) {
    var expires = "";
    if (days) {
        var d = new Date();
        d.setTime(d.getTime() + days * 24 * 60 * 60 * 1000);
        expires = "; expires=" + d.toGMTString();
    }
    document.cookie = name + "=" + value + expires + "; path=/";
}

function getCookie(name) {
    var re = new RegExp("(\;|^)[^;]*(" + name + ")\=([^;]*)(;|$)");
    var res = re.exec(document.cookie);
    return res != null ? res[3] : null;
}

function getDocumentBounds() {
    var agent = navigator.userAgent.toLowerCase();
    if (document.documentElement && document.compatMode == "CSS1Compat" &&
    agent.indexOf('chrome') < 0 && agent.indexOf('safari') < 0) {
        return {
            st: document.documentElement.scrollTop,
            sl: document.documentElement.scrollLeft,
            sw: document.documentElement.scrollWidth,
            sh: document.documentElement.scrollHeight,
            cw: document.documentElement.clientWidth,
            ch: document.documentElement.clientHeight
        }
    } else if (document.body) {
        return {
            st: document.body.scrollTop,
            sl: document.body.scrollLeft,
            sw: document.body.scrollWidth,
            sh: document.body.scrollHeight,
            cw: document.body.clientWidth,
            ch: document.body.clientHeight
        }
    }
}

function absolutePoint(element) {
    var result = { x: element.offsetLeft, y: element.offsetTop };
    element = element.offsetParent;
    while (element) {
        result.x += element.offsetLeft;
        result.y += element.offsetTop;
        element = element.offsetParent;
    }
    return result;
}

function CsdnFloatBox(left, top, width, height) {
    this.div_box = document.createElement("div");
    this.left = left;
    this.top = top;
    this.width = width ? width : 200;
    this.height = height ? height : 200;
    this.visivle = false;
    with (this.div_box.style) {
        textAlign = "left";
        display = "none";
        position = "absolute";
        borderStyle = "none";
        borderWidth = "0px";
        zIndex = "9999";
    }
    document.body.insertBefore(this.div_box, document.body.firstChild);
    this.resize(left, top, width, height);
}

CsdnFloatBox.prototype.resize = function(left, top, width, height) {
    if (this.left == left && this.top == top &&
        this.width == width && this.height == height) return;
    this.left = left;
    this.top = top;
    this.width = width ? width : 200;
    this.height = height ? height : 200;
    with (this.div_box.style) {
        top = this.top + "px";
        left = this.left + "px";
        width = this.width + "px";
        height = this.height + "px";
    }
};

CsdnFloatBox.prototype.show = function() {
    if (this.visible == true) return;
    this.visible = true;
    this.div_box.style.display = "block";
};

CsdnFloatBox.prototype.hide = function() {
    if (this.visible == false) false;
    this.visible = false;
    this.div_box.style.display = "none";
};

var currentFloatBox = null;
var pageArea = "?";
if ((/\/t\/\d+\/\d+\/\d+\.html/ig).test(location)) /* 老帖 */
    pageArea = "t";
else if ((/\/u\/\d+\/\d+\/[\w\-]+\.html/ig).test(location)) /* 当前帖 */
    pageArea = "u";
else if ((/\/games\/gamePawn\.aspx/ig).test(location)) /* 押宝 */
    pageArea = "g";
else if ((/book\.csdn\.net\/review\/[\w+_]+\.html/ig).test(location)) /* 图书 */
    pageArea = "b";
else if ((/\.csdn\.net\/VoteList\.aspx/ig).test(location)) /* 投票列表 */
    pageArea = "V";
else if ((/\.csdn\.net\/VotePost\.aspx/ig).test(location)) /* 单项投票 */
    pageArea = "v";

function showFloatBox(options) {
    if (!currentFloatBox) {
        currentFloatBox = new CsdnFloatBox(options.left, options.top, options.width, options.height);
        var html =
"<table border=\"0\" cellpadding=\"2\" cellspacing=\"1\" style=\"font-size:12px;line-height:18px;width:165px;height:117px;background-color:#CDD3DA;\">" +
"<tr><td align=\"center\" style=\"height:18px;background-color:#FFFADC;line-height:14px;width:160px;\">" +
"<div><strong style=\"float:left;margin-left:50px\"><a href=\"http://community.csdn.net/HomePage.aspx\" target=\"_blank\" style=\"color:#993300;\" onclick=\"if (typeof LogClickCount == 'function') LogClickCount(this, 70);\">社区焦点</a></strong>" +
"<a style=\"text-decoration:none;color:#4477AA;float:right;margin-right:5px;\" href=\"javascript:void(0)\" onclick=\"closeFloatBox()\" title=\"关闭\">x</a>" +
"</div></td></tr><tr>" +
"<td style=\"height:77px;background-color:White;\">";
        for (var i = 0; i < hotList.length; i++)
            html += "<div><a href=\"" + hotList[i].url + "\" target=\"_blank\" style=\"text-decoration:none;color:#4477AA;margin-left:5px;\" onclick=\"if (typeof LogClickCount == 'function') LogClickCount(this, 70);\">" + hotList[i].text + "</a></div>";
        html += "</td></tr></table>";
        currentFloatBox.div_box.innerHTML = html;
        if ("?tbvV".indexOf(pageArea) >= 0) {
            currentFloatBox.calc_pos = function() {
                currentFloatBox.show();
                var bounds = getDocumentBounds();
                currentFloatBox.div_box.style.top = bounds.st + 300 + "px";
                currentFloatBox.div_box.style.right = "13px";
            };
        } else if ("u" == pageArea) {
            currentFloatBox.calc_pos = function() {
                var tables = document.getElementsByTagName("table");
                currentFloatBox.show();
                var bounds = getDocumentBounds();
                var point = { x: 0, y: 0 };
                for (var i = 0; i < tables.length; i++) {
                    if (tables[i].className == "r" || (/\bitem\s+(topic|reply)\b/i).test(tables[i].className)) {
                        var absPoint = absolutePoint(tables[i]);
                        var y = absPoint.y + tables[i].clientHeight - currentFloatBox.height - 32;
                        if (tables[i].className == "r") y = y - 20;
                        if (y > bounds.st) {
                            point = { x: absPoint.x + tables[i].clientWidth - currentFloatBox.width - 3, y: y };
                            break;
                        }
                    }
                }
                point.x = Math.min(point.x, bounds.cw - currentFloatBox.width - 4);
                currentFloatBox.resize(point.x, point.y, currentFloatBox.width, currentFloatBox.height);
            }
        } else if ("g" == pageArea) {
            currentFloatBox.calc_pos = function() {
                currentFloatBox.show();
                var bounds = getDocumentBounds();
                currentFloatBox.div_box.style.top = bounds.st + bounds.ch - currentFloatBox.height - 10 + "px";
                currentFloatBox.div_box.style.left = bounds.sl + bounds.cw - currentFloatBox.width - 10 + "px";
            };
        }
    }
    currentFloatBox.timer = setInterval(function() { currentFloatBox.calc_pos(); },
        "u".indexOf(pageArea) < 0 ? 50 : 3000);
}

function closeFloatBox() {
    if (currentFloatBox) currentFloatBox.hide();
    setCookie("close_fbver2", hotVersion, 0.5);
    clearInterval(currentFloatBox.timer);
}

if (getCookie("close_fbver2") != hotVersion)
    showFloatBox({ left: 10, top: 10, width: 165, height: 117 });