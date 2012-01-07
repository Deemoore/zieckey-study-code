#include "qoslib/include/QOSLibPrerequisits.h"

#include "qoslib/include/QMemcached.h"

#ifdef H_PROVIDE_LIBMEMCACHED

namespace osl
{
    namespace 
    {//{{{
        bool isSocketExist( const char* domainsock )
        {
            struct stat st;
            int ret = stat( domainsock, &st );
            if ( ret != 0 )
            {
                return false;
            }

            if( S_ISSOCK(st.st_mode) )
            {
                return true;
            }
            else
            {
                return false;
            }
        }

    }//}}}


    Memcached::Memcached( const char* domainsock, 
                const char* hostname, 
                const char* port )
        : domainsock_(domainsock), hostname_(hostname), 
        port_(port), mc_(NULL)
    {
        bool use_socket = false;
        if ( isSocketExist(domainsock) )
        {
            use_socket = true;
        }

        memcached_return_t rc = MEMCACHED_SUCCESS;
        mc_ = memcached_create(NULL);
        if ( use_socket )
        {
            fprintf( stdout,"use unix domain socket to connect to memcached. domainsock=%s\n", domainsock_.c_str());
            rc = memcached_server_add_unix_socket( mc_, domainsock );
            if (rc != MEMCACHED_SUCCESS)
            {
                fprintf( stderr,"Couldn't add_unix_socket server: %s\n",
                         memcached_strerror(mc_, rc));
            }
        }
        else
        {
            fprintf( stdout, "use network socket to connect to memcached. host=%s port=%s\n", hostname_.c_str(), port_.c_str() );
            memcached_server_st* servers = NULL;
            servers = memcached_server_list_append( servers, hostname, 
                        atoi(port), &rc);
            rc = memcached_server_push( mc_, servers);
            if (rc != MEMCACHED_SUCCESS)
            {
                fprintf( stderr,"Couldn't add_unix_socket server: %s\n",memcached_strerror(mc_, rc));
            }
        }
        

        StringA errmsg;
        setBehavior( MEMCACHED_BEHAVIOR_POLL_TIMEOUT, 1000, errmsg );
        setBehavior( MEMCACHED_BEHAVIOR_CACHE_LOOKUPS, 1, errmsg );
        setBehavior( MEMCACHED_BEHAVIOR_POLL_TIMEOUT, 1000, errmsg );
        setBehavior( MEMCACHED_BEHAVIOR_RCV_TIMEOUT, 1000, errmsg );
        setBehavior( MEMCACHED_BEHAVIOR_SND_TIMEOUT, 1000, errmsg );
        setBehavior( MEMCACHED_BEHAVIOR_NO_BLOCK, true, errmsg );
    }

    Memcached::~Memcached()
    {
        if ( mc_ )
        {
            memcached_free( mc_ );
            mc_ = NULL;
        }
    }

    bool Memcached::setBehavior( const memcached_behavior_t& option, 
                const uint64_t value, StringA& errmsg )
    {
        assert( mc_ && "memcached not initialized!" );
        memcached_return_t rc = memcached_behavior_set( mc_, option, value );
        if (rc != MEMCACHED_SUCCESS)
        {
            fprintf( stderr,"Couldn't behavior_set :%s\n", memcached_strerror(mc_, rc));
            errmsg = memcached_strerror(mc_, rc);
            return false;
        }

        return true;
    }
    
    int Memcached::mget( const size_t retrytimes, StringAStringAMap& keyvalues, StringA& errmsg )
    {
        if ( keyvalues.empty() )
        {
            return 0;
        }

        StringAStringAMap::iterator it(keyvalues.begin());
        StringAStringAMap::iterator ite(keyvalues.end());

        char**  keys    = new char*[keyvalues.size()];
        size_t* keylens = new size_t[keyvalues.size()];

        size_t i = 0;
        for ( ; it != ite; ++it )
        {
            keys[i] = const_cast<char*>(it->first.c_str());
            keylens[i] = it->first.length();
            ++i;
        }

        //auto delete the memory allocated above when this function finished
        char* keys_help_to_delete = reinterpret_cast<char*>(keys);
        stdext::auto_delete<char> keys_auto_deleted(keys_help_to_delete);
        stdext::auto_delete<size_t> keylens_auto_deleted(keylens);
        (void)keys_auto_deleted;
        (void)keylens_auto_deleted;

        size_t key_num = i;

        memcached_return_t rc = MEMCACHED_SUCCESS; 
        for ( size_t j = 0; j <= retrytimes; ++j )
        {
            rc = memcached_mget(mc_, (const char* const*)keys, keylens, key_num);

            if ( rc == MEMCACHED_NOTFOUND )
            {
                return 0;
            }

            if( rc == MEMCACHED_SUCCESS )
            {
                break;
            }
        }

        if ( rc != MEMCACHED_SUCCESS ) 
        {
            OStringStream oss;
            oss << "memcached_mget failed. "
                << "ret=" << (int)rc << ", "
                << memcached_strerror(mc_, rc);
            errmsg = oss.str();
            //fprintf( stderr, "%s, although we have tried %lu times\n", errmsg.c_str(), retrytimes + 1 );
            return -1;
        }

        uint32_t    flags      = 0;
        const char* rkey       = NULL;
        size_t      rkeylen    = 0;
        const char* rvalue     = NULL;
        size_t      rvaluelen  = 0;

        memcached_result_st  resultobj; 
        memcached_result_st* presultobj = &resultobj;
        memcached_result_st* result     = memcached_result_create( mc_, presultobj );

        /*this will automatically call memcached_result_free( presultobj ) 
         * to free the memcached created objects */
        stdext::auto_delete< memcached_result_st > result_obj_autofree( presultobj );

        int goodresultcount = 0;
        while ( memcached_fetch_result(mc_, result, &rc) != NULL)
        {
            if ( rc == MEMCACHED_SUCCESS )
            {   
                flags     = memcached_result_flags( result );
                rkey      = memcached_result_key_value( result );
                rkeylen   = memcached_result_key_length( result );
                rvalue    = memcached_result_value( result );
                rvaluelen = memcached_result_length( result );

                StringA strkey(rkey, rkeylen);
                it = keyvalues.find( strkey );
                if ( it == keyvalues.end() )
                {
                    //fprintf( stderr, "key=%s is not in the query keys but returned by memcached server.\n", strkey.c_str() );
                    continue;
                }

                it->second = StringA(rvalue, rvaluelen);

                ++goodresultcount;

            }
            else if ( rc == MEMCACHED_END )
            {
                break;
            }
            else
            {
                OStringStream oss;
                oss << "memcached_fetch_result failed. ret=" 
                    << (int)rc << ", "
                    << memcached_strerror(mc_, rc);
                errmsg = oss.str();
                //fprintf( stderr, "%s\n", errmsg.c_str() );
                return -2;
            }
        }

        if ( rc != MEMCACHED_SUCCESS && rc != MEMCACHED_END )
        {   
            OStringStream oss;
            oss << "after memcached_fetch_result failed, ret="
                << (int)rc << ", "
                << memcached_strerror(mc_, rc);
            errmsg = oss.str();
            //fprintf( stderr, "%s\n", errmsg.c_str() );
            return -3;

        }

        assert( goodresultcount <= (int)key_num );
        return goodresultcount;
    }

    bool Memcached::get( const char* key, const size_t keylen, const size_t retrytimes, StringA& rvalue, StringA& errmsg )
    {
        size_t value_len = 0;
        uint32_t flags = 0;
        for ( size_t i = 0; i <= retrytimes; ++i )
        {
            memcached_return_t rc = MEMCACHED_SUCCESS;
            char* value = memcached_get( mc_, key, keylen,
                        &value_len, &flags, &rc ); //remember to free this returned value
            stdext::auto_delete<char> value_autofree(value);

            if ( rc == MEMCACHED_SUCCESS )
            {
                if ( value )
                {
                    rvalue = StringA( value, value_len );
                }
                return true;
            }
            else if ( rc == MEMCACHED_NOTFOUND )
            {
                OStringStream oss;
                oss << "key=" << key << " "
                    << "ret=" << (int)rc << ", "
                    << memcached_strerror(mc_, rc);
                errmsg = oss.str();
                return true;
            }
            else
            {
                OStringStream oss;
                oss << "key=" << key << " "
                    << "memcached_get failed, although we had retried " << retrytimes << " times. "
                    << "ret=" << (int)rc << ", "
                    << memcached_strerror(mc_, rc);
                errmsg = oss.str();
                //fprintf( stderr, "%s but we will retry %lu times", errmsg.c_str(), retrytimes - i );
                continue;
            }
        }

        return false;
    }

    
    bool Memcached::get( const StringA& key, const size_t retrytimes, StringA& rvalue, StringA& errmsg )
    {
        return get( key.c_str(), key.length(), retrytimes, rvalue, errmsg );
    }

    bool Memcached::set( const char* key,   const size_t keylen, 
            const void* value, const size_t valuelen, StringA& errmsg )
    {
        memcached_return_t rc = MEMCACHED_SUCCESS;
        rc = memcached_set( mc_, key, keylen, (const char*)value, valuelen, (time_t)0, (uint32_t)0 );
        if ( rc != MEMCACHED_SUCCESS )
        {
            OStringStream oss;
            oss << "memcached_set error, ret=" 
                << (int)rc << ", " 
                << memcached_strerror( mc_, rc );
            errmsg = oss.str();
            //fprintf( stderr, "%s\n", errmsg.c_str() );
            return false;
        }

        return true;
    }



    bool Memcached::set( const char* key,   const size_t keylen, 
                         const void* value, const size_t valuelen, 
                         const size_t retrytimes, StringA& errmsg )
    {
        for ( size_t i = 0; i <= retrytimes; ++i )
        {
            if ( set( key, keylen, value, valuelen, errmsg ) )
            {
                return true;
            }
        }
        
        return false;
    }

    bool Memcached::set( const StringA& key, const StringA& value, StringA& errmsg )
    {
        return set( key.c_str(), key.length(), value.c_str(), value.length(), errmsg );
    }

    bool Memcached::set( const StringA& key,
            const void* value, const size_t valuelen, StringA& errmsg )
    {
        return set( key.c_str(), key.length(), value, valuelen, errmsg );
    }
 
    bool Memcached::erase( const StringA& key, StringA& errmsg )
    {
        return erase( key.c_str(), key.length(), errmsg );
    }

    bool Memcached::erase( const char* key, const size_t keylen, StringA& errmsg )
    {
        memcached_return_t rc = MEMCACHED_SUCCESS;
        rc = memcached_delete( mc_, key, keylen, (uint32_t)0 );
        if ( rc != MEMCACHED_SUCCESS )
        {
            OStringStream oss;
            oss << "memcached_delete error, ret=" 
                << (int)rc << ", " 
                << memcached_strerror( mc_, rc );
            errmsg = oss.str();
            //fprintf( stderr, "%s\n", errmsg.c_str() );
            return false;
        }

        return true;

    }

} // end of namespace osl

#endif //end #if LIBMEMCACHED_API

