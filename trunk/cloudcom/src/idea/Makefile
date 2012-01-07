# weizili@360.cn 

CC=gcc
CXX=g++
AR=ar
ARFLAGS=cru
CFLAGS=-g -O3 -fPIC -Wshadow -Wcast-qual -Wcast-align -Wwrite-strings -Wsign-compare -Winvalid-pch -fms-extensions -Wall -I../3rdparty/unixinclude -I.
CPPFLAGS= -Woverloaded-virtual -Wsign-promo -fno-gnu-keywords 
LDFLAGS=
LIBSRC=i_cbc.c i_cfb64.c i_ofb64.c i_ecb.c i_skey.c
libobjs=i_cbc.o i_cfb64.o i_ofb64.o i_ecb.o i_skey.o
objs=$(libobjs) ideatest.o
liba=libidea.a
libso=libidea.so
testbin=ideatest

all : $(liba) $(libso)
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
	(cp -f $(liba) $(libso) ../../install/lib)

clean:
	rm -rf *.o $(testbin)

distclean:
	rm -rf *.o $(libso) $(liba)  $(testbin)
