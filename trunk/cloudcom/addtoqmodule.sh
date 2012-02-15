#!/usr/local/bin/bash


declare workdir=$(pwd)

rm -rf qmodule/storage_cluster 		

version=`awk -F, '{w=match($3,"weizili@360.cn"); if(w) print $2 }' configure.in`
echo "packet version:$version";

mkdir -p qmodule/storage_cluster/lib
mkdir -p qmodule/storage_cluster/include
mkdir -p qmodule/storage_cluster/include/slrsa/
mkdir -p qmodule/storage_cluster/include/snappy/
mkdir -p qmodule/storage_cluster/include/idea/
mkdir -p qmodule/storage_cluster/include/qoslib/include
mkdir -p qmodule/storage_cluster/include/qnetworklib/include
mkdir -p qmodule/storage_cluster/include/qapputillib/include

cp -rf debug/lib/* qmodule/storage_cluster/lib

cp -rf src/snappy/*.h							qmodule/storage_cluster/include/snappy
cp -rf src/slrsa/*.h							qmodule/storage_cluster/include/slrsa
cp -rf src/idea/*.h								qmodule/storage_cluster/include/idea
cp -rf src/e_leveldb/c_src/leveldb/include/*	qmodule/storage_cluster/include/
cp -rf src/qoslib/include/*.h					qmodule/storage_cluster/include/qoslib/include
cp -rf src/qnetworklib/include/*.h				qmodule/storage_cluster/include/qnetworklib/include
cp -rf src/qapputillib/include/*.h				qmodule/storage_cluster/include/qapputillib/include
cp -rf src/q3rdparty/include/*					qmodule/storage_cluster/include
cp -rf src/q3rdparty/unixinclude/*				qmodule/storage_cluster/include

rm -rf qmodule/storage_cluster/include/qdb/src
rm -rf qmodule/storage_cluster/lib/centeroslib

cd qmodule/storage_cluster
find . -name .svn | xargs rm -rf
find . -name *.o | xargs rm -rf
cd ../
qmodule_add CloudQueryEngine $version storage_cluster

