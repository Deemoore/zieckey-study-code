# weizili@360.cn 

CC=gcc
CXX=g++
AR=ar
ARFLAGS=cru
CURRENT_DIR=$(shell echo `pwd`)
SOURCE_DIR=$(CURRENT_DIR)/src
PREFIX=${CURRENT_DIR}/../../install
CFLAGS=$(TOP_CFLAGS) -c -fPIC -Wshadow -Wcast-qual -Wcast-align -Wwrite-strings -Wsign-compare -Winvalid-pch -fms-extensions -Wall -I${SOURCE_DIR}/../../q3rdparty/unixinclude -I .. -I/usr/local/include 
CPPFLAGS= -Woverloaded-virtual -Wsign-promo -fno-gnu-keywords 
LDFLAGS=$(TOP_LDFLAGS) -L/usr/local/lib -L$(PREFIX)/lib -lmemcached
LIBNAME=$(shell basename `pwd`)


IDEA_OBJS := ../idea/i_cbc.o  ../idea/i_cfb64.o  ../idea/i_ecb.o  ../idea/i_ofb64.o  ../idea/i_skey.o
SLRSA_OBJS := ../slrsa/md5c.o ../slrsa/nn.o ../slrsa/rsa.o ../slrsa/shsc.o ../slrsa/slrsa.o
OSLIB_SRCS := $(wildcard ../osl/src/*.cc)
OSLIB_OBJS := $(patsubst ../osl/src/%.cc, ../osl/src/%.o, $(OSLIB_SRCS))

SRCS := $(wildcard src/*.cc)
OBJS := $(patsubst src/%.cc, src/%.o, $(SRCS))
DEPS := $(patsubst %.o, %.d, $(OBJS))

TARGET_SO=lib$(LIBNAME).so
TARGET_A=lib$(LIBNAME).a

all : $(TARGET_SO) $(TARGET_A)
	$(MAKE) install

install :  $(TARGET_SO) $(TARGET_A)
	cp -f $(TARGET_A) $(TARGET_SO) $(PREFIX)/lib

$(TARGET_A) : $(OBJS)  $(IDEA_OBJS) $(SLRSA_OBJS) $(OSLIB_OBJS)
	$(AR) $(ARFLAGS) $@ $^
	ranlib $@			   

$(TARGET_SO) : $(OBJS) $(IDEA_OBJS) $(SLRSA_OBJS) $(OSLIB_OBJS) 
	$(CXX) $(LDFLAGS) $^ -shared -o $@
	
src/%.o : src/%.cc include/%.h
	$(CXX) $(CFLAGS) $(CPPFLAGS) $< -o $@
	
src/%.o : src/%.cc
	$(CXX) $(CFLAGS) $(CPPFLAGS) $< -o $@

../idea/%.o : ../idea/%.c
	$(CC) $(CFLAGS) $< -o $@

../slrsa/%.o : ../slrsa/%.c
	$(CC) $(CFLAGS) $< -o $@

../osl/src/%.o : ../osl/src/%.cc
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@

-include $(DEPS)


t:
	@echo "LIBNAME:" $(LIBNAME)
	@echo "SRCS:" $(SRCS)
	@echo "OBJS:" $(OBJS)
	@echo "CFLAGS:" $(CFLAGS)
	@echo "CPPFLAGS:" $(CPPFLAGS)

clean:
	rm -rf src/*.o $(OBJS) $(DEPS) $(TARGET_SO) $(TARGET_A)

