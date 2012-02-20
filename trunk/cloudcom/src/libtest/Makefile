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
LDFLAGS=$(TOP_LDFLAGS) -L/usr/local/lib $(PREFIX)/lib/libqoslib.a $(PREFIX)/lib/libwraputil.a $(PREFIX)/lib/libnet.a $(PREFIX)/lib/libapputil.a -lpthread -lmemcached -lcurl
LIBNAME=$(shell basename `pwd`)

SRCS := $(wildcard src/*.cc)
OBJS := $(patsubst src/%.cc, src/%.o, $(SRCS))

TARGET=$(LIBNAME)

all : $(TARGET) 
	$(MAKE) install

$(TARGET) : $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $@
	
src/%.o : src/%.cc include/%.h
	$(CXX) $(CFLAGS) $(CPPFLAGS) $< -o $@
	
src/%.o : src/%.cc
	$(CXX) $(CFLAGS) $(CPPFLAGS) $< -o $@



t:
	@echo "LIBNAME:" $(LIBNAME)
	@echo "SRCS:" $(SRCS)
	@echo "OBJS:" $(OBJS)
	@echo "CFLAGS:" $(CFLAGS)
	@echo "CPPFLAGS:" $(CPPFLAGS)

install: $(TARGET) 
	cp -f $(TARGET) $(PREFIX)/bin

clean:
	rm -rf src/*.o  $(OBJS) $(DEPS)  $(TARGET_SO) $(TARGET_A)

