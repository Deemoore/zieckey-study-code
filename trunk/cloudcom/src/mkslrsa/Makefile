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
LDFLAGS=$(TOP_LDFLAGS) -L/usr/local/lib -L$(PREFIX)/lib 
LIBNAME=$(shell basename `pwd`)

IDEA_OBJS := ../idea/i_cbc.o  ../idea/i_cfb64.o  ../idea/i_ecb.o  ../idea/i_ofb64.o  ../idea/i_skey.o
SLRSA_OBJS := ../slrsa/md5c.o ../slrsa/nn.o ../slrsa/rsa.o ../slrsa/shsc.o ../slrsa/slrsa.o
OSLIB_SRCS := $(wildcard ../netproto/src/*.cc)
OSLIB_OBJS := $(patsubst ../netproto/src/%.cc, ../netproto/src/%.o, $(OSLIB_SRCS))

SRCS := $(wildcard *.c)
OBJS := $(patsubst %.c, %.o, $(SRCS)) $(SLRSA_OBJS) $(OSLIB_OBJS) $(IDEA_OBJS)
DEPS := $(patsubst %.o, %.d, $(OBJS))

TARGET_SO=lib$(LIBNAME).so
TARGET_A=lib$(LIBNAME).a

TARGET_EXE=generator_rsa_keys

all : $(TARGET_SO) $(TARGET_A) $(TARGET_EXE)
	$(MAKE) install

install :  $(TARGET_SO) $(TARGET_A)
	cp -f $(TARGET_A) $(TARGET_SO) $(PREFIX)/lib

$(TARGET_EXE) : $(OBJS)	main.o
	$(CXX) $^ -lcrypto $(LDFLAGS) -o $@
	
$(TARGET_A) : $(OBJS)  
	$(AR) $(ARFLAGS) $@ $^
	ranlib $@			   

$(TARGET_SO) : $(OBJS)
	$(CXX) $(LDFLAGS) $^ -shared -o $@
	
%.o : %.c 
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -o $@
	
%.o : %.cc
	$(CXX) $(CFLAGS) $(CPPFLAGS) $< -o $@

%.o : %.cpp
	$(CXX) $(CFLAGS) $(CPPFLAGS) $< -o $@

../idea/%.o : ../idea/%.c
	$(CC) $(CFLAGS) $< -o $@

../slrsa/%.o : ../slrsa/%.c
	$(CC) $(CFLAGS) $< -o $@

../netproto/src/%.o : ../netproto/src/%.cc
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

