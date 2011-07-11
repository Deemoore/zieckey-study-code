# weizili@360.cn 
# The study test code project 
#


CC=gcc
CXX=g++
AR=ar
ARFLAGS=cru
#CFLAGS=-g -O3 -fPIC  -Wshadow -Wcast-qual -Wcast-align -Wwrite-strings -Wsign-compare -Winvalid-pch -fms-extensions -Wall 
CFLAGS=-g -O3 -fPIC -Wconversion -Wall -Wformat -I/usr/local/include/
#-Wp64
CPPFLAGS=-Woverloaded-virtual -Wsign-promo -fno-gnu-keywords 
LDFLAGS=-lstdc++ -L/usr/local/lib
objs=size_t.o mkfifo.o mkfifo2.o getpagesize.o stat.o test.o cast.o classinfunc.o zlib.o fwrspeed.o libeventtest.o getabspath.o buserror1.o dmalloctest.o
program=size_t mkfifo mkfifo2 getpagesize stat test cast classinfunc zlib fwrspeed libeventtest getabspath buserror1 dmalloctest
subpro=c_call_cpp rsa

    
#TOPDIR=$(shell pwd)
TOPDIR=`pwd`

all: $(program) 
	for t in $(subpro); do cd $$t ; make || exit 1; cd ..; done


#    check: $(PROGRAMS) $(TESTS)
#            for t in $(TESTS); do echo "***** Running $$t"; ./$$t || exit 1; done


size_t : size_t.o 
	$(CC) $(LDFLAGS) size_t.o -o $@
	
mkfifo: mkfifo.o 
	$(CC) $(LDFLAGS) mkfifo.o -o $@
	
mkfifo2: mkfifo2.o
	$(CC) $(LDFLAGS) mkfifo2.o -o $@
	
getpagesize: getpagesize.o
	$(CC) $(LDFLAGS) getpagesize.o -o $@
	
stat: stat.o
	$(CC) $(LDFLAGS) stat.o -o $@
	
test: test.o 
	$(CC) $(LDFLAGS) test.o -o $@
	
cast : cast.o 
	$(CC) $(LDFLAGS) cast.o -o $@
	
classinfunc : classinfunc.o 
	$(CC) $(LDFLAGS) classinfunc.o -o $@
	
zlib : zlib.o 
	$(CC) $(LDFLAGS) -lz zlib.o -o $@

fwrspeed : fwrspeed.o
	$(CC) $(LDFLAGS) fwrspeed.o -o $@
	
libeventtest : libeventtest.o 
	$(CC) $(LDFLAGS) -levent libeventtest.o -o $@
	
getabspath : getabspath.o 
	$(CC) $(LDFLAGS) getabspath.o -o $@
	
buserror1 : buserror1.o 
	$(CC) $(LDFLAGS) buserror1.o -o $@
	
dmalloctest : dmalloctest.o 
	$(CC) $(LDFLAGS) dmalloctest.o -o $@
	
clean:
	rm -rf *.o $(program)
	for t in $(subpro); do cd $$t ; make clean || exit 1; cd ..; done

