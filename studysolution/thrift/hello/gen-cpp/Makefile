CPPFLAGS= -g -fPIC -Wshadow -Wcast-qual -Wcast-align -Wwrite-strings -Wsign-compare -Winvalid-pch -fms-extensions -Wall -I/usr/local/include/thrift -I/usr/local/include 
LDFLAGS=-L/usr/local/lib

server=server
client=client
all:${client} ${server}

${client}: ${client}.o hello_constants.o UserExchange.o hello_types.o
	g++ -g -o ${client} ${client}.o hello_constants.o UserExchange.o hello_types.o ${LDFLAGS} -lthrift
${server}: ${server}.o hello_constants.o UserExchange.o hello_types.o
	g++ -g -o ${server} ${server}.o hello_constants.o UserExchange.o hello_types.o ${LDFLAGS} -lthrift
${client}.o : ${client}.cpp
	g++ -g -c ${client}.cpp $(CPPFLAGS)
hello_constants.o : hello_constants.cpp hello_constants.h
	g++ -g -c hello_constants.cpp $(CPPFLAGS)
UserExchange.o : UserExchange.cpp UserExchange.h
	g++ -g -c UserExchange.cpp $(CPPFLAGS)
hello_types.o : hello_types.cpp hello_types.h
	g++ -g -c hello_types.cpp $(CPPFLAGS)
${server}.o : ${server}.cpp
	g++ -g -c ${server}.cpp $(CPPFLAGS)
clean:
	rm -rf *.o ${server} ${client}
