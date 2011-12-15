#!/bin/sh

path=/home/s/apps/CloudSafeLine/MidBuild2

exec 2>> $path/logs/start.sh.log
set -x

ps aux | grep midbuilder | grep -v grep | awk '{print $2}' | sort
