#ifndef _QMEMCACHED_H__
#define _QMEMCACHED_H__

#include "wraputil/include/inner_pre.h"

#include "osl/include/auto_delete.h"
#include "osl/include/string_ext.h"
#include "osl/include/string_util.h"

#ifdef H_PROVIDE_LIBMEMCACHED 

#include <libmemcached/memcached.h>

namespace wu
{
    //! The wrapper class of libmemcached-0.43
    class _EXPORT_WRAPUTIL Memcached 
    {
    public:
        typedef osl::Map<osl::StringA, osl::StringA> StringAStringAMap;

    public:
        Memcached( const char* domainsock, 
                   const char* hostname, 
                   const char* port );

        ~Memcached();

        bool setBehavior( const memcached_behavior_t& option, 
                          const uint64_t value, osl::StringA& errmsg );
        
        /**
         * @brief Select multiple keys at once from memcached
         * 
         * @param[in] const size_t retrytimes - the retry times when error happened
         * @param[in,out] keyvalues - the key-value result stored here
         * @param[out] StringA& errmsg - the error message will stored here, 
         *  if there is any error happened.
         * @return < 0, when something error, error message are stored errmsg
         *           0, when donnot match any keys
         *         > 0, when matches n count of keys, n MUST BE <= keyvalues.size() 
         */
        int mget( const size_t retrytimes, StringAStringAMap& keyvalues, osl::StringA& errmsg );

        /**
         * @brief Query a key's value from memcached
         * 
         * @param[in] const char* key - the query key
         * @param[in] const size_t keylen - the length of the query key
         * @param[in] const StringA& key - the query key
         * @param[in] const size_t retrytimes - the retry times when error happened
         * @param[out] StringA& value - the value all stored here
         * @param[out] StringA& errmsg - the error message will stored here, 
         *  if there is any error happened.
         * @return false, when something error happened
         *         true, if get the valuesuccessfully
         */
        bool get( const char* key, const size_t keylen, const size_t retrytimes, osl::StringA& value, osl::StringA& errmsg );
        bool get( const osl::StringA& key, const size_t retrytimes, osl::StringA& value, osl::StringA& errmsg );
        bool get( const size_t retrytimes, const osl::StringA& key, osl::StringA& value, osl::StringA& errmsg );

        /**
         * @brief Set a key/value pair to memcached
         * @note If there is already a value associated with this key in memcached,
         *      the old value will be overrided.
         * @param[in] const size_t retrytimes - the retry times when error happened
         * @param[out] StringA& errmsg - the error message will stored here, 
         *  if there is any error happened.
         * @return false, when something error happened
         *         true, if set the value successfully
         */
        bool set( const char* key,   const size_t keylen, 
                  const void* value, const size_t valuelen, osl::StringA& errmsg );
        bool set( const osl::StringA& key, const void* value, const size_t valuelen, osl::StringA& errmsg );
        bool set( const osl::StringA& key, const osl::StringA& value, osl::StringA& errmsg );

        bool set( const char* key,   const size_t keylen, 
                  const void* value, const size_t valuelen, 
                  const size_t retrytimes, osl::StringA& errmsg );

        /**
         * @brief Delete a key/value pair from memcached
         * @param[out] StringA& errmsg - the error message will stored here, 
         *  if there is any error happened.
         * @return false, when something error happened
         *         true, if set the value successfully
         */
        bool erase( const osl::StringA& key, osl::StringA& errmsg );
        bool erase( const char* key, const size_t keylen, osl::StringA& errmsg );

    private:
        osl::StringA domainsock_;
        osl::StringA hostname_;
        osl::StringA port_;

        memcached_st* mc_;//a long-connect to memcached handler
    };
}//end of namespace osl


namespace osl { namespace ext {
    template<> inline 
        auto_delete < memcached_result_st >::~auto_delete()
        {    
            if ( ptr_ref_to_be_deleted_ )
            {
                memcached_result_free( ptr_ref_to_be_deleted_ );
                ptr_ref_to_be_deleted_ = NULL;
            }
        }
} }


#endif //end #if LIBMEMCACHED_API

#endif
