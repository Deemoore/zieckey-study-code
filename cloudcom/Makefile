# weizili
#
# The study test code project 
#
# Please use gmake but not make in FreeBSD OS
#

		
SUBDIRS=src/slrsa src/idea src/netproto src/osl src/wraputil src/net src/apputil src/libtest

TESTDIRS=src/osl/test src/netproto/test

TOPDIR=`pwd`

TOP_CFLAGS="-g -O3 -DNDEBUG"
#TOP_CFLAGS="-g -D_DEBUG"
#TOP_CFLAGS="-g -D_DEBUG"
TOP_LDFLAGS=""

all:
	for t in $(SUBDIRS); do $(MAKE) TOP_CFLAGS=$(TOP_CFLAGS) TOP_LDFLAGS=$(TOP_LDFLAGS) -C $$t ; $(MAKE) install -C $$t; done
	cp install/lib/libwraputil.* ~/lib
	cp install/lib/libnetproto.* ~/lib
	cp install/lib/libnet.* ~/lib

check: all
	for t in $(TESTDIRS); do $(MAKE) check  TOP_CFLAGS=$(TOP_CFLAGS) TOP_LDFLAGS=$(TOP_LDFLAGS) -C $$t ; done
	
clean:
	for t in $(SUBDIRS); do $(MAKE) clean -C $$t; done
	for t in $(TESTDIRS); do $(MAKE) clean -C $$t; done

