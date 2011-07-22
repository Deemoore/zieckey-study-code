#!/bin/sh

_datenow=`date +%Y%m%d`
_timenow=`date +%H%M%S`
_pack=qvm_1_${_datenow}_${_timenow}.tar.gz
_contentfile="./mailcontent"
echo ${_pack};
cd /da1/weizili/msvbin/qvm
rm -rf 1
tar vjxf /tmp/qvm.tar.bz2 -C /da1/weizili/msvbin
rm -rf 1/cfg
tar zcvf ${_pack} 1
rm -rf ${_contentfile}

echo "qvm program location: build3 " `pwd`/${_pack} "   " >> ${_contentfile}
echo `md5 ${_pack}`" " >> ${_contentfile}

echo "" >> ${_contentfile}
echo "" >> ${_contentfile}
echo "" >> ${_contentfile}

echo "Please update bole.kill.corp.qihoo.net first.  " >> ${_contentfile}
echo "" >> ${_contentfile}
echo "If it works, please update one online machine : bkill1.safe.dxt.qihoo.net " >> ${_contentfile}
echo "" >> ${_contentfile}
echo "If there is no something wrong, please update all online machine : bkill[1~5].safe.[bjt|dxt].qihoo.net " >> ${_contentfile}

echo "" >> ${_contentfile}
echo "" >> ${_contentfile}
echo "" >> ${_contentfile}
echo "Update steps:" >> ${_contentfile}
echo "" >> ${_contentfile}
echo "Step1: backup /usr/home/q/apps/CloudSafeLine/qvm/1" >> ${_contentfile}
echo "" >> ${_contentfile}
echo "Step2: overwrite the old qvm files : tar zxvf ${_pack} /home/s/apps/CloudSafeLine/qvm" >> ${_contentfile}
echo "" >> ${_contentfile}
echo "Step3: reload nginx : sudo nwebctl reload" >> ${_contentfile}

echo "" >> ${_contentfile}
echo "" >> ${_contentfile}
echo "" >> ${_contentfile}
echo "" >> ${_contentfile}
echo "Thanks!" >> ${_contentfile}
echo "" >> ${_contentfile}
echo "" >> ${_contentfile}
echo "" >> ${_contentfile}
echo "" >> ${_contentfile}
echo "weizili" >> ${_contentfile}
echo "" >> ${_contentfile}


mailx -s "QVM program update" -c yangkang@360.cn -c xiangyong@360.cn cloudops@360.cn < ${_contentfile}

