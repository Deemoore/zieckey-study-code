
so=_pair.so

all: $(so)

$(so):pair_wrap.o
	g++ -shared pair_wrap.o -o $(so) 
	
pair_wrap.cxx:pair.i
	swig -python -c++ pair.i

pair_wrap.o:pair_wrap.cxx
	g++ -c -fPIC pair_wrap.cxx -I/usr/local/include/python2.5

clean:
	-rm -f *.o pair_wrap.* pair.py pair.pyc $(so)
