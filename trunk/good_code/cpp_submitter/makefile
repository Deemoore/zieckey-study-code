# weizili@360.cn 

CC=gcc
CXX=g++
AR=ar
ARFLAGS=cru
QMODULE=./qmodule
COMMONFLAGS=-g -D_DEBUG -O3 -fPIC -Wshadow -Wcast-qual -Wcast-align -Wwrite-strings -Winvalid-pch -fms-extensions -Wfloat-equal -Wextra -Wall -Wno-unused-parameter -Wno-unused-function -Wunused-variable -Wunused-value -I$(QMODULE)/include -I/usr/local/include -I.. -I. -I include -I$(HOME)/include
#COMMONFLAGS=-g -O3 -fPIC -Wshadow -Wcast-qual -Wcast-align -Wwrite-strings -Winvalid-pch -fms-extensions -Wfloat-equal -Wextra -Wall -Wno-unused-parameter -Wno-unused-function -Wunused-variable -Wunused-value -I$(QMODULE)/include -I/usr/local/include -I.. -I. -I include -I$(HOME)/include
CFLAGS=$(COMMONFLAGS)
CCFLAGS=-Woverloaded-virtual -Wsign-promo -fno-gnu-keywords $(COMMONFLAGS) 
LDFLAGS=-L $(QMODULE)/lib -L/usr/local/lib $(HOME)/lib/libqlog.a $(QMODULE)/lib/libgflags.a $(QMODULE)/lib/libdaemon.a -lmemcached -lstdc++
PREFIX :=$(QMODULE)/lib

SRCS := $(wildcard *.cc)
OBJS := $(patsubst %.cc, %.o, $(SRCS))

MIDBUILD_OBJS := $(OBJS)
MIDBUILDER=midbuilder

UNITTEST_SRC = $(wildcard test/*.cc)
UNITTEST_OBJ = $(patsubst %.cc, %.o, $(UNITTEST_SRC))
UNITTEST_CFLAGS =
UNITTEST_LDFLAGS = -L$(HOME)/lib/
UNITTEST_LIBS= -lcppunit -lboost_filesystem
UNITTEST_TARGET=unittest 

all :  $(MIDBUILDER) 

$(MIDBUILDER) : $(MIDBUILD_OBJS)
	$(CXX) $^ $(LDFLAGS) -o $@

check:test $(MIDBUILDER)
	./$(UNITTEST_TARGET)

%.o : %.cpp %.h
	$(CXX) -c $(CFLAGS) $(CCFLAGS) $< -o $@

%.o : %.cc %.h
	$(CXX) -c $(CFLAGS) $(CCFLAGS) $< -o $@

%.o : %.cc 
	$(CXX) -c $(CFLAGS) $(CCFLAGS) $< -o $@

clean:
	rm -rf *.o test/*.o $(MIDBUILDER) $(UNITTEST_TARGET)

distclean:
	$(MAKE) clean
	rm -rf *.o 

test/%.o : test/%.cc
	$(CXX) -c $(UNITTEST_CFLAGS) $(CFLAGS) -o $@ $<

test: $(UNITTEST_TARGET) 

$(UNITTEST_TARGET): $(UNITTEST_OBJ) $(MIDBUILD_OBJS)
	$(CXX) $(UNITTEST_OBJ) $(filter-out main.o,$(MIDBUILD_OBJS)) $(LDFLAGS) $(UNITTEST_LDFLAGS) $(UNITTEST_LIBS) -o $(UNITTEST_TARGET)

.PHONY: test  


