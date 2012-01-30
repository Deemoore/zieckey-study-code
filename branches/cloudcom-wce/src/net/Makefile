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
LDFLAGS=$(TOP_LDFLAGS) -L/usr/local/lib -L$(PREFIX)/lib -losl -lpthread -lcurl
LIBNAME=$(shell basename `pwd`)

SRCS := $(wildcard src/*.cc)
OBJS := $(patsubst src/%.cc, src/%.o, $(SRCS))
DEPS := $(patsubst %.o, %.d, $(OBJS))

TARGET_SO=lib$(LIBNAME).so
TARGET_A=lib$(LIBNAME).a

all : $(TARGET_SO) $(TARGET_A)
	$(MAKE) install

install :  $(TARGET_SO) $(TARGET_A)
	cp -f $(TARGET_A) $(TARGET_SO) $(PREFIX)/lib

check : $(TARGET_A)	$(TARGET_SO)	
	$(MAKE) check -C test

$(TARGET_A) : $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS) 
	ranlib $@			   

$(TARGET_SO) : $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -shared -o $@
	
src/%.o : src/%.cc include/%.h
	$(CXX) $(CFLAGS) $(CPPFLAGS) $< -o $@
	
src/%.o : src/%.cc
	$(CXX) $(CFLAGS) $(CPPFLAGS) $< -o $@


-include $(DEPS)


t:
	@echo "LIBNAME:" $(LIBNAME)
	@echo "SRCS:" $(SRCS)
	@echo "OBJS:" $(OBJS)
	@echo "CFLAGS:" $(CFLAGS)
	@echo "CPPFLAGS:" $(CPPFLAGS)

clean:
	rm -rf src/*.o $(OBJS) $(DEPS) $(TARGET_SO) $(TARGET_A)

