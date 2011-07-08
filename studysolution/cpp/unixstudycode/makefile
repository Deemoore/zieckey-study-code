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
objs=size_t.o mkfifo.o mkfifo2.o getpagesize.o stat.o test.o cast.o classinfunc.o zlib.o fwrspeed.o libeventtest.o getabspath.o
program=size_t mkfifo mkfifo2 getpagesize stat test cast classinfunc zlib fwrspeed libeventtest getabspath
subpro=c_call_cpp rsa

    
#TOPDIR=$(shell pwd)
TOPDIR=`pwd`

all: $(program) 
	for t in $(subpro); do cd $$t ; make || exit 1; cd ..; done


#    check: $(PROGRAMS) $(TESTS)
#            for t in $(TESTS); do echo "***** Running $$t"; ./$$t || exit 1; done


size_t : $(objs)
	$(CC) $(LDFLAGS) size_t.o -o $@
	
mkfifo: $(objs)
	$(CC) $(LDFLAGS) mkfifo.o -o $@
	
mkfifo2: $(objs)
	$(CC) $(LDFLAGS) mkfifo2.o -o $@
	
getpagesize: $(objs)
	$(CC) $(LDFLAGS) getpagesize.o -o $@
	
stat: $(objs)
	$(CC) $(LDFLAGS) stat.o -o $@
	
test: $(objs)
	$(CC) $(LDFLAGS) test.o -o $@
	
cast : $(objs)
	$(CC) $(LDFLAGS) cast.o -o $@
	
classinfunc : $(objs)
	$(CC) $(LDFLAGS) classinfunc.o -o $@
	
zlib : $(objs)
	$(CC) $(LDFLAGS) -lz zlib.o -o $@

fwrspeed : $(objs)
	$(CC) $(LDFLAGS) fwrspeed.o -o $@
	
libeventtest : $(objs)
	$(CC) $(LDFLAGS) -levent libeventtest.o -o $@
	
getabspath : $(objs)
	$(CC) $(LDFLAGS) getabspath.o -o $@
	
clean:
	rm -rf *.o $(program)
	for t in $(subpro); do cd $$t ; make clean || exit 1; cd ..; done

