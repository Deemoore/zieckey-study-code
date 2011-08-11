# weizili@360.cn 
# The study test code project 
#


CC=gcc
CXX=g++
AR=ar
ARFLAGS=cru
CFLAGS=-g -fPIC -Wshadow -Wcast-qual -Wcast-align -Wwrite-strings -Wsign-compare -Winvalid-pch -fms-extensions -Wall -I/usr/local/include -I.
CPPFLAGS= -Woverloaded-virtual -Wsign-promo -fno-gnu-keywords
#-Wp64
CPPFLAGS=-Woverloaded-virtual -Wsign-promo -fno-gnu-keywords 
LDFLAGS=-lstdc++ -L/usr/local/lib
objs=libeventtest.o dmalloctest.o mkfifo.o mkfifo2.o zlib.o mkdir.o getpagesize.o stat.o test.o cast.o classinfunc.o fwrspeed.o getabspath.o buserror1.o size_t.o 
program=libeventtest dmalloctest mkfifo mkfifo2 zlib mkdir getpagesize stat test cast classinfunc fwrspeed getabspath buserror1 size_t 
subpro=c_call_cpp rsa

    
TOPDIR=`pwd`

all: $(objs) $(program) 
	for t in $(subpro); do cd $$t ; make || exit 1; cd ..; done

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
	
mkdir: mkdir.o 
	$(CC) $(LDFLAGS) mkdir.o -o $@
	
clean:
	rm -rf *.o $(program)
	for t in $(subpro); do cd $$t ; make clean || exit 1; cd ..; done

