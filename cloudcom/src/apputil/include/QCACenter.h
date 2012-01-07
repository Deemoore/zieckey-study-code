#ifndef Q_APP_UTILITY_CA_CENTER_UTILITY_H_
#define Q_APP_UTILITY_CA_CENTER_UTILITY_H_

#include "apputil/include/QAppUtilConfig.h"

#if ( H_PROVIDE_NET_CA_ENCRYPT && H_PROVIDE_IDEA_ENCRYPT )

namespace aut
{
    /** A class of Certificate Authority Center
    */
    class _EXPORT_APPUTIL CACenter : public osl::NoCopy
    {
    public:
        enum{ DATA_SIGN_MAX_LEN = 256 };

    public:
        CACenter( const char* usr, const char* pwd, 
				  const char* host, const char* ver, 
                  unsigned int timeout, 
                  unsigned int retrytimes, 
                  float retryinterval )//in seconds
            : m_strUserName( usr != NULL ? usr : "" )
            , m_strPassword( pwd != NULL ? pwd : "" )
            , m_strVersion( ver != NULL ? ver : "" )
            , m_strHostName( host != NULL ? host : "" )
            , m_nTimeout( timeout )
            , m_nRetryTimes( retrytimes )
            , m_fRetryInterval( retryinterval )
        {}

        //! \brief Do a HTTP request to verify user authority
        //!     The HTTP response data include the encrypt key and data sign, 
        //!   which has a data format : errno|encrypt_key|data_sign
        //!     errno : 0 verify successfully, other failed
        //!     encrypt_key : the encrypt key
        //!     data_sign : the data sign, this will be used to get decrypt key.
        //! \param const char*  usr - the CA center url, 
        //!         like http://192.168.0.181:8360/datasafe/interface_check.php, 
        //!         USER_VERIFY_INTF in the config file
        //! \param const char * operation - support "dump" , "load" or "dump_value"
        //! \param const char * op_type - support "plaintext", "ciphertext"
        //! \return bool - return true when request successfull y
        bool doRequestUserVerify( const char* url, const char* operation, const char* op_type );

        //! \brief Do a HTTP request to get decrypt key
        //! \param const char*  usr - the CA center url, 
        //!         like http://192.168.0.181:8360/datasafe/interface_getkey.php
        //!         KEY_ADMIN_INTF in the config file
        //! \param const char * operation - support "load" or "dump_value"
        //! \param const char * data_sign - the data sign
        //! \return bool - return true when request successfully
        bool doRequestGetDecryptKey( const char* url, const char* operation, const char* data_sign );

        //! \brief Send a HTTP response to notify server that this operation has done
        //! \param const char*  usr - the CA center url, 
        //!         like http://192.168.0.181:8360/datasafe/interface_done.php
        //!         OP_END_INTF in the config file
        //! \param const char * operation - support "dump" , "load" or "dump_value"
        //! \param const char * data_sign - the data sign
        //! \return bool - return true when notify successfully
        bool doRequestOperationDone( const char* url, const char* operation, const char* data_sign );

        
		//! \brief @see http://twiki.corp.qihoo.net/twiki/bin/view/Main/UserVerifyIntf
		//! \param const char*  usr - the CA center url, 
        //!         like http://192.168.0.181:8360/datasafe/interface_check.php, 
        //!         USER_VERIFY_INTF in the config file
        //! \param const char*  usr - user name
		//! \param const char*  pwd - password
		//! \param const char*  op - support "dump" , "load" or "dump_value"
        //! \param const char * op_type - support "plaintext", "ciphertext"
        //! \param const char*  host - the hostname of the operation machine
        //! \param const char*  ver - memcached-engine version
		//! \param osl::StringA& output - the HTTP response data, 
        //!         the format is errno|encrypt_key|data_sign
		//! \return bool -
        static bool getEncryptKeyFromCACenter( const char* url, 
                                               const char* usr, 
                                               const char* pwd, 
                                               const char* op, 
                                               const char* op_type, 
                                               const char* host, 
                                               const char* ver, 
                                               unsigned int timeout, 
                                               osl::StringA& output );

        //! \brief @see http://twiki.corp.qihoo.net/twiki/bin/view/Main/EncriptKeyMngIntf
        //! \param const char*  usr - the CA center url, 
        //!         like http://192.168.0.181:8360/datasafe/interface_getkey.php
        //!         KEY_ADMIN_INTF in the config file
        //! \param const char*  usr - user name
        //! \param const char*  pwd - password
        //! \param const char*  op - ONLY support "load" or "dump_value"
        //! \param const char*  data_sign - the data sign
        //! \param const char*  host - the hostname of the operation machine
        //! \param const char*  ver - memcached-engine version
        //! \param osl::StringA& output - the HTTP response data
        //!         the format is errno|decrypt_key
        //! \return bool -
        static bool getDecryptKeyFromCACenter( const char* url, 
                                               const char* usr, 
                                               const char* pwd, 
                                               const char* op, 
                                               const char* data_sign,
                                               const char* host, 
                                               const char* ver, 
                                               unsigned int timeout, 
                                               osl::StringA& output );

        //! \brief Send a HTTP response to notify server that this operation has done
        //! \param const char*  usr - the CA center url, 
        //!         like http://192.168.0.181:8360/datasafe/interface_done.php
        //!         OP_END_INTF in the config file
        //! \param const char * operation - support "dump" , "load" or "dump_value"
        //! \param const char * data_sign - the data sign
        //! \param osl::StringA& output - the HTTP response data
        //!         the format is errno
        //! \return bool - 
        static bool sendOperateDoneACK( const char* url, 
                                        const char* operation, 
                                        const char* data_sign, 
                                        unsigned int timeout, 
                                        osl::StringA& output );

    public:
        const osl::StringA& getEncryptKey() const { return m_strEncryptKey; }
        const osl::StringA& getDecryptKey() const { return m_strDecryptKey; }

        /// getters and setters
    public:
        const osl::StringA& getDataSign() const { return m_strDataSign; }

        const osl::StringA& getUserName() const { return m_strUserName; }
        void setUserName( const osl::StringA& val ) { m_strUserName = val; }

        const osl::StringA& getPassword() const { return m_strPassword; }
        void setPassword( const osl::StringA& val ) { m_strPassword = val; }

        const osl::StringA& getVersion() const { return m_strVersion; }
        void setVersion( const osl::StringA& val ) { m_strVersion = val; }

        const osl::StringA& getHostName() const { return m_strHostName; }
        void setHostName( const osl::StringA& val ) { m_strHostName = val; }

        osl::u32 getTimeout() const { return m_nTimeout; }
        void setTimeout(osl::u32 val) { m_nTimeout = val; }

        osl::u32 getRetryTimes() const { return m_nRetryTimes; }
        void setRetryTimes(osl::u32 val) { m_nRetryTimes = val; }

        osl::f32 getRetryInterval() const { return m_fRetryInterval; }
        void setRetryInterval(osl::f32 val) { m_fRetryInterval = val; }

    private:
        osl::StringA  m_strUserName;
        osl::StringA  m_strPassword;
        osl::StringA   m_strVersion;
        osl::StringA  m_strHostName; //! the host name of the operation machine
        osl::u32         m_nTimeout;
        osl::u32      m_nRetryTimes;
        osl::f32   m_fRetryInterval;//! the interval to sleep, in seconds

        //---------------------------------------------------------
        //HTTP user verify response data
        osl::StringA      m_strUVErrno;
        osl::StringA   m_strEncryptKey;
        osl::StringA     m_strDataSign;

        //---------------------------------------------------------
        //HTTP request to get decrypt key
        osl::StringA m_strGetDecryptKeyErrno;
        osl::StringA         m_strDecryptKey;


    };
} // end of namespace ext

#endif // end of #if ( H_PROVIDE_NET_CA_ENCRYPT && H_PROVIDE_IDEA_ENCRYPT )



#endif //end of #ifndef Q_APP_UTILITY_CA_CENTER_UTILITY_H_




