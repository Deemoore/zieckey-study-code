<?php
	�жϺ����Ƿ����Ȼ��
	if(!function_exists('symlink')){ // Assume a windows system
	    function symlink($target, $link){
	        //we just use function link to replace symlink
	        return link($target, $link);
	    }
	}
?>




PHP��class����ӵ��2���� __construct ���캯��
public function __construct($type, $fileuuid, $versionid, $cachepolicy) {
	self::__init($type, $fileuuid, $versionid, $cachepolicy, "");
}

public function __construct($type, $fileuuid, $versionid, $cachepolicy, $oldfileuuid = "") {
	self::__init($type, $fileuuid, $versionid, $cachepolicy, $oldfileuuid);
}



php�Ա�����Сд����
�Ժ�����Сд������