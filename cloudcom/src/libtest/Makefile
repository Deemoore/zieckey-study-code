# weizili@360.cn 

CC=gcc
CXX=g++
AR=ar
ARFLAGS=cru
CURRENT_DIR=$(shell echo `pwd`)
SOURCE_DIR=$(CURRENT_DIR)/src
PREFIX=${CURRENT_DIR}/../../debug
CFLAGS=-g -O3 -c -fPIC -Wshadow -Wcast-qual -Wcast-align -Wwrite-strings -Wsign-compare -Winvalid-pch -fms-extensions -Wall -I${SOURCE_DIR}/../../q3rdparty/unixinclude -I .. -I/usr/local/include 
CPPFLAGS= -Woverloaded-virtual -Wsign-promo -fno-gnu-keywords 
LDFLAGS=-L/usr/local/lib  $(PREFIX)/lib/libqoslib.a  $(PREFIX)/lib/libqnetworklib.a $(PREFIX)/lib/libqapputillib.a $(PREFIX)/lib/libidea.a -lpthread -lcurl -lmemcached
LIBNAME=$(shell basename `pwd`)

SRCS := $(wildcard src/*.cpp)
OBJS := $(patsubst src/%.cpp, src/%.o, $(SRCS))

TARGET=$(LIBNAME)

all : $(TARGET) 
	cp -f $(TARGET) $(PREFIX)/bin

$(TARGET) : $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $@
	
src/%.o : src/%.cpp include/%.h
	$(CXX) $(CFLAGS) $(CPPFLAGS) $< -o $@
	
src/%.o : src/%.cpp
	$(CXX) $(CFLAGS) $(CPPFLAGS) $< -o $@



t:
	@echo "LIBNAME:" $(LIBNAME)
	@echo "SRCS:" $(SRCS)
	@echo "OBJS:" $(OBJS)
	@echo "CFLAGS:" $(CFLAGS)
	@echo "CPPFLAGS:" $(CPPFLAGS)

install: $(TARGET) 
	cp -f $(TARGET) $(PREFIX)/lib

clean:
	rm -rf src/*.o  $(OBJS) $(DEPS)  $(TARGET_SO) $(TARGET_A)

