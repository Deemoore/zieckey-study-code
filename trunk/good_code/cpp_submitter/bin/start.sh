#!/bin/sh

path=/home/s/apps/CloudSafeLine/MidBuild2

exec 2>> $path/logs/start.sh.log
set -x

crashpath=/home/s/var/proc

binpath=$path/bin
confpath=$path/conf
logpath=$path/logs

if [ $# -ne 2 ];then
        echo "Usage $0 [priority_count] [instance_count]"
        echo "For example: $0 16 16"
        exit
fi

channel=0
priority_count=$1
instance_count=$2

dump_time=30
dump_count=50000

while [ $channel -lt $instance_count ]
do
    $path/bin/midbuilder --log_prefix=Inc_ --log_path=$path/data/input/$channel --dump_time=$dump_time --dump_count=$dump_count --memcached_sock=/home/s/apps/CloudSafeLine/QueryEngine/MemDB/var/memcached.sock --output_dir=$path/data/output --id_file_path=$path/conf/pkg_center --qlog_config=$path/conf/scan.log.conf --priority_level=$priority_count --daemonize=true 
    channel=`expr $channel + 1`
done
