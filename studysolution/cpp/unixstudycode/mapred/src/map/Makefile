# weizili@360.cn 

CC=gcc
CXX=g++
AR=ar
ARFLAGS=cru
USER_HOME=$(HOME)
COMMONFLAGS=-g -D_DEBUG -fPIC  -Wshadow -Wcast-qual -Wcast-align -Wwrite-strings -Wsign-compare -Winvalid-pch -fms-extensions -Wfloat-equal -Wextra -Wall -Wno-unused-parameter -Wno-unused-function -Wunused-variable -Wunused-value -I../../../qmodule/include -I/usr/local/include -I. -I$(USER_HOME)/include
CFLAGS=$(COMMONFLAGS) 
CCFLAGS=-Woverloaded-virtual -Wsign-promo -fno-gnu-keywords $(COMMONFLAGS) 
LDFLAGS=-L $(USER_HOME)/lib $(USER_HOME)/lib/libgflags.a $(USER_HOME)/lib/libqoslib.a $(USER_HOME)/lib/libidea.a
map=map
reduce=reduce



SRCS=$(wildcard *.cc)
OBJS=$(patsubst %.cc, %.o, $(SRCS) )
PROGRAMS=$(patsubst %.o, %, $(OBJS) )

all : $(OBJS) $(PROGRAMS)

% : %.o
	$(CXX) $< $(LDFLAGS) -o $@

%.o : %.cc
	$(CXX) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

clean:
	rm -rf *.o $(PROGRAMS) $(OBJS)

