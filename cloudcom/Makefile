# weizili@360.cn 
#
# The study test code project 
#
# Please use gmake but not make in FreeBSD OS
#

		
SUBDIRS=src/slrsa src/idea src/osl src/net src/apputil src/libtest

TOPDIR=`pwd`

all:
	for t in $(SUBDIRS); do $(MAKE) -C $$t ; $(MAKE) install -C $$t; done
	
clean:
	for t in $(SUBDIRS); do $(MAKE) clean -C $$t; done

