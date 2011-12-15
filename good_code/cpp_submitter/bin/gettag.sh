root=/home/s/apps/CloudSafeLine/MidBuild
logpath=$root/logs
datapath=$root/data/output
 
#--------------------------------------

gettag()
{
	/usr/local/php5/bin/php $root/php/gettag.php
}

gettag
