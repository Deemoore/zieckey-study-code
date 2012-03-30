#!/bin/sh

if [ $# -ne 1 ];then
        echo "Usage $0 [source_file_name]"
        echo "For example: $0 process_logic.cc"
        exit
fi

file_name=$1
modify_file_name=${file_name}.modify
base_file_name=${file_name}.base.cxx
#svn up
#version=`svn up` 
#version=`echo $version | awk '{print $3}' | awk -F. '{print $1}'`
cp -rf $file_name $modify_file_name
svn revert $file_name
cp -rf $file_name $base_file_name
cp $modify_file_name $file_name
vimdiff $file_name $base_file_name
rm -f $modify_file_name
rm -f $base_file_name
