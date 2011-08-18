CPPFLAGS=-I/usr/local/include/thrift -I/usr/local/include
LDFLAGS=-L/usr/local/lib

server=server
client=client
all:${client} ${server}

${client}: ${client}.o logger_constants.o Logger.o logger_types.o
	g++ -g -o ${client} ${client}.o logger_constants.o Logger.o logger_types.o ${LDFLAGS} -lthrift
${server}: Logger_${server}.o logger_constants.o Logger.o logger_types.o
	g++ -g -o ${server} Logger_${server}.o logger_constants.o Logger.o logger_types.o ${LDFLAGS} -lthrift
${client}.o : ${client}.cpp
	g++ -g -c ${client}.cpp $(CPPFLAGS)
logger_constants.o : logger_constants.cpp logger_constants.h
	g++ -g -c logger_constants.cpp $(CPPFLAGS)
Logger.o : Logger.cpp Logger.h
	g++ -g -c Logger.cpp $(CPPFLAGS)
logger_types.o : logger_types.cpp logger_types.h
	g++ -g -c logger_types.cpp $(CPPFLAGS)
Logger_${server}.o : Logger_${server}.cpp
	g++ -g -c Logger_${server}.cpp $(CPPFLAGS)
clean:
	rm -rf *.o ${server} ${client}
