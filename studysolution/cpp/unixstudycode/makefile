# weizili@360.cn 
#
# The study test code project 
#
# Please use gmake but not make in FreeBSD OS
#


CC=gcc
CXX=g++
AR=ar
ARFLAGS=cru
CFLAGS=-g -fPIC -Wshadow -Wcast-qual -Wcast-align -Wwrite-strings -Wsign-compare -Winvalid-pch -fms-extensions -Wall -I/usr/local/include -I.
CPPFLAGS=-Woverloaded-virtual -Wsign-promo -fno-gnu-keywords 
LDFLAGS=-lstdc++ -L/usr/local/lib

C_SRCS=$(wildcard *.c)
CPP_SRCS=$(wildcard *.cpp) 

OBJS=$(patsubst %.c, %.o, $(C_SRCS) )		
OBJS+=$(patsubst %.cpp, %.o, $(CPP_SRCS) )
PROGRAMS=$(patsubst %.o, %, $(OBJS) )		
		
SUBDIRS=c_call_cpp rsa protobuf

    
TOPDIR=`pwd`

all: $(OBJS) $(PROGRAMS) 
	for t in $(SUBDIRS); do cd $$t ; make || exit 1; cd ..; done
	
zlib : zlib.o 
	$(CC) $(LDFLAGS)  -lz zlib.o -o $@
	
libeventtest : libeventtest.o 
	$(CC) $(LDFLAGS)  -levent libeventtest.o -o $@

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@
	
%.o : %.cpp
	$(CXX) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

clean:
	rm -rf *.o $(PROGRAMS) $(OBJS)
	for t in $(SUBDIRS); do cd $$t ; make clean || exit 1; cd ..; done

