#!/bin/bash

export QTDIR=/usr/local/arm-linux/qt_toolchain/qt-2.3.2
export PATH=$QTDIR/bin:$PATH
export LD_LIBRARY_PATH=$QTDIR/lib:$LD_LIBRARY_PATH

export TMAKEDIR=/usr/local/arm-linux/qt_toolchain/tmake-1.11
export PATH=/usr/local/arm-linux/qt_toolchain/tmake-1.11/bin:$PATH
export TMAKEPATH=/usr/local/arm-linux/qt_toolchain/tmake-1.11/lib/linux-g++
