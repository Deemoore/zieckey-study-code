

all: hello.so 

hello.so: hello.o
	g++ -shared hello.o -o hello.so 

hello.o: hello.cpp
	g++ -fPIC -c -I /usr/local/include/python2.5 -o hello.o hello.cpp

clean:
	-rm -f hello.o hello.so
