#include <transport/TSocket.h>
#include <transport/TBufferTransports.h>
#include <protocol/TBinaryProtocol.h>
#include "Logger.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;

using boost::shared_ptr;

using namespace logger;

int main( int argc, char** argv )
{

    const char* message = "client comming";
    if ( argc > 1 )
    {
        message = argv[1];
    }

    shared_ptr<TTransport> socket(new TSocket("localhost", 9090));
    shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    logger::LoggerClient client(protocol);

    try {
        transport->open();
        logger::LogMessage lm;
        lm.timestamp = time(NULL);
        lm.message = message;
        client.log(lm);
        client.log(lm);
        client.log(lm);
        client.log(lm);
        transport->close();
    } catch (TException &tx) {
        printf("ERROR: %s\n", tx.what());
    }
}

