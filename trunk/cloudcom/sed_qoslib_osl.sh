#!/bin/sh

sed -in-place "s/qoslib/osl/g" *.h
sed -in-place "s/QOSLibAllExp/exp/g" *.h
sed -in-place "s/QINIParser/ini_parser/g" *.h
sed -in-place "s/QBase64/base64/g" *.h
sed -in-place "s/QJSONObject/json/g" *.h
sed -in-place "s/QMD5/md5/g" *.h
sed -in-place "s/QFileUtil/file_util/g" *.h
sed -in-place "s/QLock/lock/g" *.h
sed -in-place "s/QTimer/timer/g" *.h
sed -in-place "s/QDynLib/dynlib/g" *.h
sed -in-place "s/QSingleton/singleton/g" *.h
sed -in-place 's/osl\/include\/QMemcached/wraputil\/include\/memcached/g' *.h
sed -in-place 's/osl::QMemcached/wu::Memcached/g' *.h

sed -in-place "s/qoslib/osl/g" *.cpp
sed -in-place "s/QOSLibAllExp/exp/g" *.cpp
sed -in-place "s/QINIParser/ini_parser/g" *.cpp
sed -in-place "s/QBase64/base64/g" *.cpp
sed -in-place "s/QJSONObject/json/g" *.cpp
sed -in-place "s/QMD5/md5/g" *.cpp
sed -in-place "s/QFileUtil/file_util/g" *.cpp
sed -in-place "s/QLock/lock/g" *.cpp
sed -in-place "s/QTimer/timer/g" *.cpp
sed -in-place "s/QDynLib/dynlib/g" *.cpp
sed -in-place "s/QSingleton/singleton/g" *.cpp
sed -in-place 's/osl\/include\/QMemcached/wraputil\/include\/memcached/g' *.cpp
sed -in-place 's/osl::QMemcached/wu::Memcached/g' *.cpp

sed -in-place "s/qoslib/osl/g" *.cc
sed -in-place "s/QOSLibAllExp/exp/g" *.cc
sed -in-place "s/QINIParser/ini_parser/g" *.cc
sed -in-place "s/QBase64/base64/g" *.cc
sed -in-place "s/QJSONObject/json/g" *.cc
sed -in-place "s/QMD5/md5/g" *.cc
sed -in-place "s/QFileUtil/file_util/g" *.cc
sed -in-place "s/QLock/lock/g" *.cc
sed -in-place "s/QTimer/timer/g" *.cc
sed -in-place "s/QDynLib/dynlib/g" *.cc
sed -in-place "s/QSingleton/singleton/g" *.cc
sed -in-place 's/osl\/include\/QMemcached/wraputil\/include\/memcached/g' *.cc
sed -in-place 's/osl::Memcached/wu::Memcached/g' *.cc

rm -rf *n-place
