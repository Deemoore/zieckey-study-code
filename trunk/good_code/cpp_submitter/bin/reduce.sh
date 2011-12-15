#!/bin/sh

path=/home/s/apps/CloudSafeLine/MidBuild2

exec 2>> $path/logs/reduce.sh.log
set -x

root=/home/s/apps/CloudSafeLine/MidBuild2
logpath=$root/logs
datapath=$root/data/output
 
#--------------------------------------
clean_xml()
{
        echo -e "\n\n\n\n... remove Inc*xml input and output data files ...\n"
 
        day=`date -v -2d +%Y%m%d`
        TowDays=`date -v -2d +%Y%m%d`
        Threeday=`date -v -3d +%Y%m%d`

        Hours=`date -v -4H +%Y-%m-%d-%H`
 
        #if [ -d $root/data/backup/$day ]; then
        #        echo "dir $root/data/backup/$day exist"
        #else
        #        mkdir $root/data/backup/$day
        #fi
 
 
        find $root/data/input/*/* -name "bak*$TowDays*" | xargs rm -rf

        find $root/data/output/ -name "*$TowDays*xml" | xargs rm -rf
}
 
#--------------------------------------
 
clean_log()
{
        echo "---- clean ----"
        day=`date -v -2d +%Y-%m-%d`
 
        rm  $root/logs/*$day*
}
 
#--------------------------------------
clean_xml
 
#--------------------------------------
clean_log
