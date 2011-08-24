
so=_example.so

all: $(so)

$(so):example.o example_wrap.o
	ld -shared example.o example_wrap.o -o $(so) 
	
example_wrap.c:example.i
	swig -python example.i

example_wrap.o:example_wrap.c
	gcc -c -fPIC example_wrap.c -I/usr/local/include/python2.5

example.o: example.c
	gcc -c -fPIC example.c -I/usr/local/include/python2.5

clean:
	-rm -f *.o example_wrap.* example.py* $(so)
