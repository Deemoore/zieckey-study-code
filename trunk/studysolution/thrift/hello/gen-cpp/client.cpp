#include <transport/TSocket.h>
#include <transport/TBufferTransports.h>
#include <protocol/TBinaryProtocol.h>
#include "UserExchange.h"
//#include "hello_types.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;

using boost::shared_ptr;

using namespace hello;

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
    UserExchangeClient client(protocol);

    try {
        transport->open();

        int32_t i = 1;

        User user;
        user.firstname = "zili";
        user.lastname = "wei";
        user.user_id = i++;
        user.sex = SexType::MALE;    

        int32_t retcode = client.add_user(user);
        printf( "retcode=%d\n", retcode );

        user.firstname = "liujin";
        user.user_id = i++;
        client.add_user(user);
        printf( "retcode=%d\n", retcode );

        user.firstname = "chenggang";
        user.user_id = i++;
        client.add_user(user);
        printf( "retcode=%d\n", retcode );

        transport->close();
    } catch (TException &tx) {
        printf("ERROR: %s\n", tx.what());
    }
}

