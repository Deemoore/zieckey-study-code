# weizili@360.cn 
#
# The study test code project 
#
# Please use gmake but not make in FreeBSD OS
#

		
SUBDIRS=src/slrsa src/idea src/osl src/wraputil src/net src/apputil src/libtest

TESTDIRS=src/osl/test

TOPDIR=`pwd`

#TOP_CFLAGS="-g -O3"
TOP_CFLAGS="-g"
TOP_LDFLAGS=""

all:
	for t in $(SUBDIRS); do $(MAKE) TOP_CFLAGS=$(TOP_CFLAGS) TOP_LDFLAGS=$(TOP_LDFLAGS) -C $$t ; $(MAKE) install -C $$t; done

check: all
	for t in $(TESTDIRS); do $(MAKE) check -C $$t ; done
	
clean:
	for t in $(SUBDIRS); do $(MAKE) clean -C $$t; done
	for t in $(TESTDIRS); do $(MAKE) clean -C $$t; done

