#include <transport/TSocket.h>
#include <transport/TBufferTransports.h>
#include <protocol/TBinaryProtocol.h>
#include "UserExchange.h"
//#include "hello_types.h"
//
#include <sys/time.h>

inline double current_second()
{
    struct timeval tv;
    gettimeofday( &tv, NULL );
    return (double)(tv.tv_sec) + ((double)(tv.tv_usec))/1000000.0f;
}

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

        for ( int j = 0; ; ++j )
        {
            int32_t i = 1;

            User user;
            user.firstname = "zili";
            user.lastname = "wei";
            user.user_id = i++;
            user.sex = SexType::MALE;    

            double begin = current_second();
            int32_t retcode = client.add_user(user);
            double end = current_second();
            printf( "retcode=%d cost=%fms\n", retcode, 1000*(end - begin) );

            user.firstname = "liujin";
            user.user_id = i++;
            client.add_user(user);
            printf( "retcode=%d\n", retcode );

            user.firstname = "chenggang";
            user.user_id = i++;
            client.add_user(user);
            printf( "retcode=%d\n", retcode );

            sleep(1);
        }
        transport->close();
    } catch (TException &tx) {
        printf("ERROR: %s\n", tx.what());
    }
}


