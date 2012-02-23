#!/usr/local/bin/bash

declare workdir=$(pwd)

rm -rf qmodule/storage_cluster 		

#version=`awk -F, '{w=match($3,"weizili@360.cn"); if(w) print $2 }' configure.in`
version=1.0.17
echo "packet version:$version";

mkdir -p qmodule/lib
mkdir -p qmodule/include
mkdir -p qmodule/include/slrsa/
mkdir -p qmodule/include/idea/
mkdir -p qmodule/include/osl/include
mkdir -p qmodule/include/net/include
mkdir -p qmodule/include/apputil/include
mkdir -p qmodule/include/wraputil/include

cp -rf ./install/lib/* qmodule/lib

cp -rf src/slrsa/*.h							qmodule/include/slrsa
cp -rf src/idea/*.h								qmodule/include/idea
cp -rf src/osl/include/*.h					    qmodule/include/osl/include
cp -rf src/net/include/*.h				        qmodule/include/net/include
cp -rf src/apputil/include/*.h				    qmodule/include/apputil/include
cp -rf src/wraputil/include/*.h				    qmodule/include/wraputil/include
cp -rf src/3rdparty/include/*					qmodule/include
cp -rf src/3rdparty/unixinclude/*				qmodule/include

rm -rf qmodule/include/qdb/src
rm -rf qmodule/lib/centeroslib

cd qmodule
find . -name .svn | xargs rm -rf
find . -name *.o | xargs rm -rf

qmodule_add CloudQueryEngine $version .

