# weizili@360.cn 

CC=gcc
CXX=g++
AR=ar
ARFLAGS=cru
CFLAGS=-g -O3 -fPIC  -Wshadow  -Wcast-align -Wwrite-strings -Wsign-compare -Winvalid-pch -fms-extensions -Wall 
CPPFLAGS=-Woverloaded-virtual -Wsign-promo -fno-gnu-keywords 
LDFLAGS=-lstdc++ 
libobjs=md5c.o nn.o rsa.o shsc.o slrsa.o
objs=$(libobjs) main.o
liba=libslrsa.a
libso=libslrsa.so
testbin=rsatest

all : $(testbin) $(liba) $(libso)
	$(MAKE) install

$(testbin) : $(objs)
	$(CC) $(objs) $(LDFLAGS) -o $@

$(liba) : $(libobjs)
	$(AR) $(ARFLAGS) $@ $(libobjs) 
	ranlib $@			   

$(libso) : $(libobjs)
	$(CC) $(libobjs) -shared -o $@

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@
	
%.o : %.cpp
	$(CXX) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

install:  $(liba) $(libso) $(testbin)	
	cp -f $(liba) $(libso) ../../install/lib
	cp -f $(testbin) ../../install/bin

clean:
	rm -rf *.o

distclean:
	rm -rf *.o $(libso) $(liba) $(testbin)
