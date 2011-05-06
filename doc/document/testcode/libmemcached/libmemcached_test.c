/**
  * gcc libmemcached_test.c -lmemcached -L /usr/local/lib -I /usr/local/include/
  */

#include <stdio.h>
#include <string.h>
#include <unistd.h>


#include <libmemcached/memcached.h>

int main(int argc, char *argv[])
{
    memcached_return rc = MEMCACHED_SUCCESS;
    memcached_st* memc = memcached_create(NULL);
    memcached_server_st* servers = NULL;
    servers = memcached_server_list_append(servers, "localhost", 10001, &rc);
    rc = memcached_server_push(memc, servers);
    //rc = memcached_server_add_unix_socket( memc, "/home/weizili/memcached.sock" );

    if (rc == MEMCACHED_SUCCESS)
        fprintf(stdout,"Added server successfully\n");
    else
        fprintf(stdout,"Couldn't add server: %s\n",memcached_strerror(memc, rc));

    char* key   = "e1784a20a471ab9222d65bbfa60a23fa";
    char* value = "helloworld";

    /** set a key */
    {
        rc = memcached_set(memc, key, strlen(key), value, strlen(value), (time_t)0, (uint32_t)0);
        if (rc == MEMCACHED_SUCCESS)
            fprintf(stdout,"Key stored successfully\n");
        else
            fprintf(stdout,"Couldn't store key: %s\n",memcached_strerror(memc, rc));
    }

	/** get a key */
    {
        size_t value_len = 0;
        uint32_t flags = 0;
        char* retvalue = memcached_get(memc, key, strlen(key), &value_len, &flags, &rc);
        if (rc == MEMCACHED_SUCCESS)
        {
            fprintf(stdout,"Key get successfully, value=%s\n", retvalue);
            free( retvalue );
        }
        else
            fprintf(stdout,"Couldn't get key: %s\n",memcached_strerror(memc, rc));
    }

    /** get a key */
    {
        const char* key1 = "f6f552271b7f3c86e7eb2f8698075e8a";
        size_t value_len = 0;
        uint32_t flags = 0;
        char* retvalue = memcached_get(memc, key1, strlen(key1), &value_len, &flags, &rc);
        if (rc == MEMCACHED_SUCCESS)
        {
            fprintf(stdout,"Key get successfully, key1=%s,value=%s\n", key1, retvalue);
            free( retvalue );
        }
        else
            fprintf(stdout,"Couldn't get key=%s\terrormsg=%s\n",key1,memcached_strerror(memc, rc));
                         
    }

	/** delete a key */
	{
		rc = memcached_delete( memc, key, strlen(key), (time_t)0 );
		if ( rc == MEMCACHED_SUCCESS )
		{
			fprintf( stdout, "key %s delete successfully.\n", key );
		}
        else
            fprintf(stdout,"Couldn't delete key: %s\n",memcached_strerror(memc, rc));
	}
    return 0;
}
