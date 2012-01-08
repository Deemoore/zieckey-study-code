# weizili@360.cn 

CC=gcc
CXX=g++
AR=ar
ARFLAGS=cru
CURRENT_DIR=$(shell echo `pwd`)
SOURCE_DIR=$(CURRENT_DIR)/src
PREFIX=${CURRENT_DIR}/../../install
CFLAGS=-g -O3 -c -fPIC -Wshadow -Wcast-qual -Wcast-align -Wwrite-strings -Wsign-compare -Winvalid-pch -fms-extensions -Wall -I${SOURCE_DIR}/../../3rdparty/unixinclude -I .. -I/usr/local/include  -MMD
CPPFLAGS= -Woverloaded-virtual -Wsign-promo -fno-gnu-keywords $(CFLAGS)
LDFLAGS=-L/usr/local/lib -lpthread 
LIBNAME=$(shell basename `pwd`)

IDEA_SRCS := $(filter-out ../idea/ideatest.c,$(wildcard ../idea/*.c))
IDEA_OBJS := $(patsubst ../idea/%.c, ../idea/%.o, $(IDEA_SRCS))

CCSRCS:= $(wildcard src/*.cc)
CCOBJS:= $(patsubst src/%.cc, src/%.o, $(CCSRCS))
SRCS := $(wildcard src/*.cpp)
OBJS := $(patsubst src/%.cpp, src/%.o, $(SRCS)) $(IDEA_OBJS) $(CCOBJS)
DEPS := $(patsubst %.o, %.d, $(OBJS))

TARGET_SO=lib$(LIBNAME).so
TARGET_A=lib$(LIBNAME).a

all : $(TARGET_SO) $(TARGET_A)
	cp -f $(TARGET_A) $(TARGET_SO) $(PREFIX)/lib

$(TARGET_A) : $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS) 
	ranlib $@			   

$(TARGET_SO) : $(OBJS)
	$(CXX) $(LDFLAGS)  $(OBJS) -shared -o $@
	
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

