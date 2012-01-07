# weizili@360.cn 
#
# The study test code project 
#
# Please use gmake but not make in FreeBSD OS
#

		
SUBDIRS=src/slrsa src/idea src/qoslib src/qnetworklib src/qapputillib src/qlibtest

TOPDIR=`pwd`

all:
	for t in $(SUBDIRS); do $(MAKE) -C $$t ; $(MAKE) install -C $$t; done
	
clean:
	for t in $(SUBDIRS); do $(MAKE) clean -C $$t; done

