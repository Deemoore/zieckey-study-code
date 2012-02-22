# weizili@360.cn 

CC=gcc
CXX=g++
AR=ar
ARFLAGS=cru
CURRENT_DIR=$(shell echo `pwd`)
SOURCE_DIR=$(CURRENT_DIR)/src
PREFIX=${CURRENT_DIR}/../../install
CFLAGS=$(TOP_CFLAGS) -c -fPIC -Wshadow -Wcast-qual -Wcast-align -Wwrite-strings -Wsign-compare -Winvalid-pch -fms-extensions -Wall -I${SOURCE_DIR}/../../3rdparty/unixinclude -I .. -I/usr/local/include  -MMD
CPPFLAGS= -Woverloaded-virtual -Wsign-promo -fno-gnu-keywords $(CFLAGS)
LDFLAGS=$(TOP_LDFLAGS) -L/usr/local/lib -lpthread 
LIBNAME=qoslib

IDEA_OBJS := ../idea/i_cbc.o  ../idea/i_cfb64.o  ../idea/i_ecb.o  ../idea/i_ofb64.o  ../idea/i_skey.o
SLRSA_OBJS := ../slrsa/md5c.o ../slrsa/nn.o ../slrsa/rsa.o ../slrsa/shsc.o ../slrsa/slrsa.o

SRCS := $(wildcard src/*.cc)
OBJS := $(patsubst src/%.cc, src/%.o, $(SRCS)) $(CCOBJS) $(IDEA_OBJS) $(SLRSA_OBJS)
DEPS := $(patsubst %.o, %.d, $(OBJS))

TARGET_SO=lib$(LIBNAME).so
TARGET_A=lib$(LIBNAME).a

all : $(TARGET_SO) $(TARGET_A)
	$(MAKE) install

$(TARGET_A) : $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS) 
	ranlib $@			   

$(TARGET_SO) : $(OBJS)
	$(CXX) $(LDFLAGS)  $(OBJS) -shared -o $@
	
check : $(TARGET_A)	$(TARGET_SO)	
	$(MAKE) check -C test

cc/%.o : cc/%.cpp include/%.h
	$(CXX) $(CPPFLAGS) $< -o $@
	
cc/%.o : cc/%.cpp
	$(CXX) $(CPPFLAGS) $< -o $@

src/%.o : src/%.cpp include/%.h
	$(CXX) $(CPPFLAGS) $< -o $@
	
src/%.o : src/%.cpp
	$(CXX) $(CPPFLAGS) $< -o $@

../idea/%.o : ../idea/%.c
	$(CC) $(CFLAGS) $< -o $@

../slrsa/%.o : ../slrsa/%.c
	$(CC) $(CFLAGS) $< -o $@

../slrsa/%.o : ../slrsa/%.c
	$(CC) $(CFLAGS) $< -o $@

-include $(DEPS)

t:
	@echo "LIBNAME:" $(LIBNAME)
	@echo "SRCS:" $(SRCS)
	@echo "OBJS:" $(OBJS)
	@echo "CFLAGS:" $(CFLAGS)
	@echo "CPPFLAGS:" $(CPPFLAGS)

install: $(TARGET_A) $(TARGET_SO) 
	cp -f $(TARGET_A) $(TARGET_SO) $(PREFIX)/lib

clean:
	rm -rf src/*.o src/*.d $(OBJS) $(DEPS) $(TARGET_SO) $(TARGET_A)

