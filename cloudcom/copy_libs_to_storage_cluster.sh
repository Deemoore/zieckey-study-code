#!/usr/local/bin/bash

declare workdir=$(pwd)


#install to qdev/CloudQueryEngine/trunk/CloudSrvNG/storage_cluster/lib
cp -rf ${workdir}/debug/lib/* ${workdir}/../lib/lib
