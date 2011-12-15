crashpath=/home/weizili/var
path=/data1/weizili/qdev/CloudQueryEngine/trunk/CloudSrvNG/engine_http/httpwrapper/ngx_module_main/module/midtag/build/php

binpath=$path/bin
confpath=$path/conf
phppath=$path/src
logpath=$path/logs
php_exec=/usr/local/bin/php

#stage=specimenUp

if [ $# -ne 2 ];then
        echo "Usage $0 [instance_count] [mode:file_MidBuild]"
        echo "For example: $0 1 file_MidBuild"
        exit
fi

channel=0
mode=$2
stage=$mode

while [ $channel -lt $1 ]
do
        #$php_exec $phppath/main.php  -d $stage -p $crashpath -s $stage -m $mode -t $channel> $logpath/run.log 2>&1
        $php_exec $phppath/main.php  -d $stage -p $crashpath -s $stage -m $mode -t $channel> /dev/null 2>&1
        channel=`expr $channel + 1`
done
