# weizili@360.cn 

CC=gcc
CXX=g++
AR=ar
ARFLAGS=cru

LIBSRC=hello.cpp hello_boost.cpp
libobjs=hello.o hello_boost.o 
libso=hello_ext.so

CFLAGS=-g -O3 -fPIC -Wcast-qual -Wcast-align -Wwrite-strings -Wsign-compare -Winvalid-pch -fms-extensions -Wall -I../q3rdparty/unixinclude -I.  -I/usr/local/include  -I/usr/local/include/python2.5
CPPFLAGS= -Woverloaded-virtual -Wsign-promo -fno-gnu-keywords
LDFLAGS=-lstdc++ -lboost_python -lpython2.5 -Wl,-soname,$(libso) -L/usr/local/lib 

all : $(libso)

$(libso) : $(libobjs)
	$(CXX) $(libobjs) $(LDFLAGS) -shared -o $@

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@
	
%.o : %.cpp
	$(CXX) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

clean:
	rm -rf *.o $(libso) 
