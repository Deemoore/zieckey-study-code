# weizili@360.cn 
TOPDIR := $(shell pwd)

CC=gcc
CXX=g++
AR=ar
ARFLAGS=cru
CFLAGS=-g -O3 -fPIC -Wconversion -Wall -Wformat 
CPPFLAGS=-Woverloaded-virtual -Wsign-promo -fno-gnu-keywords 
LDFLAGS=-lstdc++ -lcrypto
objs=sign_rsa.o rsa_sign_512.o 
program=sign_rsa rsa_sign_512

all : $(program)
	
sign_rsa : sign_rsa.o
	$(CC) sign_rsa.o $(LDFLAGS) -o $@

rsa_sign_512 : rsa_sign_512.o
	$(CC) rsa_sign_512.o $(LDFLAGS) -o $@

clean:
	rm -rf *.o $(program)
