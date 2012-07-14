	<!--
		
		var mapWidth = Request["w"];
		var mapHeight = Request["h"];
		var strZoom = Request["zoom"];
		var strLatLon = Request["strlatlon"];
		var tmp = b.p(strLatLon);

		function reShowMap(width,height)
		{
			maplet.resize(width,height);
		}
		
		function clean()
		{
			if(!maplet)return;
			maplet.clean();
		}
		
		function cleanRoute()
		{
			if(!maplet)return;
			maplet.cleanRoute();
		}
		
		function setMode(imode)
		{
			if(!maplet)return;
			maplet.setMode(imode);
		}
		
		function setCenter(strlatlon)
		{
			if(!maplet)return;
			var tmp = b.p(strlatlon);
			maplet.setCenter(tmp[1], tmp[0]);
		}
		
		function getCurrentMap()
		{
			if(!maplet)return;
			return (maplet.getCurrentMap()+"&client="+strRemoteIP);
		}
		
		function callback(strURL) {
			parent.callback(strURL);
		}
		
		function addLabel(ImgPath, strlatlon, slabel)
		{
			if(!maplet)return;
			var tmp = b.p(strlatlon);
			maplet.addPoint(ImgPath,tmp[1], tmp[0],slabel);
		}
		function addIcon(iconname,latlonkey,title,poicontent,typea){
			maplet.addIcon(iconname,latlonkey,title,poicontent,typea);
		}
		
		function setZoomLevel(iLevel)
		{
          //  if(iLevel > 0 && iLevel <= 36)
          // {
		  //	  maplet.setZoomLevel(parseInt((iLevel-1)/3));
          // }
			maplet.setZoomLevel(iLevel);
		}
		
		function getZoomLevel()
		{

			//return (maplet.getZoomLevel()+1)*3+1;
			return maplet.getZoomLevel();
		}
		
		function showBasePois(boolean)
		{
			maplet.showBasePois(boolean);
		}

		function addPolyline(style,strline)
		{
			maplet.addPolylineString(style, strline);
			maplet.refresh();
		}
		
		function getMapString()
		{
			return maplet.getCurrentMap();
		}
		
		function refresh()
		{
			maplet.refresh();
		}
		
		/*
			设置画笔的颜色，和粗细
			penColor:#FF0000
			penStroke:1
		*/
		var default_ColorValue = '#FF0000';
		var default_SizeValue = '2';
		
		function setBrushStyle(penColor, penStroke)
		{
			maplet.setBrushStyle(penColor, penStroke);
		}
		//单独设置画笔颜色
		function setBrushColor(ColorValue)
		{
			default_ColorValue = ColorValue;
			maplet.setBrushStyle(default_ColorValue,default_SizeValue);
		}
		//单独设置画笔粗细
		function setBrushSize(SizeValue)
		{
			default_SizeValue = SizeValue;
			maplet.setBrushStyle(default_ColorValue,default_SizeValue);
		}
		
		/*
			设置地图自动显示到合适的比例尺
		*/
		function setAutoZoom(minLat, minLon, maxLat, maxLon)
		{
			maplet.setAutoZoom(minLat, minLon, maxLat, maxLon);
		}
		//LOGO true/false
		function showLogo(bOn)
		{
			maplet.showLogo(bOn);
		}
		//Scale true/false
		function showScale(bOn)
		{
			maplet.showScale(bOn);
		}
		function setCursorStyle(mouse_style){
			maplet.setCursorStyle(mouse_style);
		}
	//-->