#!/bin/sh

path=/home/s/apps/CloudSafeLine/MidBuild2

exec 2>> $path/logs/start.sh.log
set -x

kill `ps aux | grep midbuilder | grep -v grep | awk '{printf "%d ",$2}'`
