#!/bin/bash

#qt 
export QTDIR=/usr/local/arm-linux/qt_toolchain/qt-2.3.7
export PATH=$QTDIR/bin:$PATH
export LD_LIBRARY_PATH=$QTDIR/lib:$LD_LIBRARY_PATH

#tmake	
export TMAKEDIR=/usr/local/arm-linux/qt_toolchain/tmake-1.11
export PATH=$TMAKEDIR/bin:$PATH
export TMAKEPATH=$TMAKEDIR/lib/qws/linux-arm-g++
