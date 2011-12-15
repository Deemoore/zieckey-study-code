path=/home/s/apps/CloudSafeLine/MidBuild2
binpath=$path/bin
confpath=$path/conf
phppath=$path/src
logpath=$path/logs
php_exec=/usr/local/bin/php

if [ $# -ne 1 ];then
    echo "Usage start.sh [mode:gm_MidBuild_inc]"
    exit
fi

mode=$1
stage=$mode

crashpath=/home/s/var/proc

channel=0
while [ $channel -lt $1 ]
do
#$php_exec $phppath/gearman_receive.php  -k $stage -p $crashpath -s $stage > $logpath/run.log 2>&1
    $php_exec $phppath/main.php  -k $stage -p $crashpath -s $stage -m $mode -t $channel
        channel=`expr $channel + 1`
done
