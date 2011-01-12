<?php
	判断函数是否存在然后
	if(!function_exists('symlink')){ // Assume a windows system
	    function symlink($target, $link){
	        //we just use function link to replace symlink
	        return link($target, $link);
	    }
	}
?>




PHP中class不能拥有2两个 __construct 构造函数
public function __construct($type, $fileuuid, $versionid, $cachepolicy) {
	self::__init($type, $fileuuid, $versionid, $cachepolicy, "");
}

public function __construct($type, $fileuuid, $versionid, $cachepolicy, $oldfileuuid = "") {
	self::__init($type, $fileuuid, $versionid, $cachepolicy, $oldfileuuid);
}



php对变量大小写敏感
对函数大小写不敏感