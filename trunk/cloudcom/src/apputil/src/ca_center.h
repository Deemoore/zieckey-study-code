#include "apputil/include/inner_pre.h"


#include "apputil/include/ca_center.h"

#include "osl/include/idea_wrapper.h"
#include "osl/include/md5.h"


#include "net/include/curl_service.h"
#include "net/include/curl_work.h"
#include "net/include/http_post_work.h"



#if ( H_PROVIDE_NET_CA_ENCRYPT && H_PROVIDE_IDEA_ENCRYPT )

namespace aut
{

    namespace
    {
#ifdef H_DEBUG_MODE
        static void md5_text(char *text, unsigned char *md5, size_t len)
        {/*{{{*/
            size_t i;
            static u_char hex[] = "0123456789abcdef";

            for (i = 0; i < len; i++) {
                *text++ = hex[md5[i] >> 4];
                *text++ = hex[md5[i] & 0xf];
            }

            *text = '\0';
        }/*}}}*/
#endif

        static int getVk(const char *usr, const char *pwd, const char *op, const char *host, char *vk)
        {/*{{{*/
            int total_len=0;
            //unsigned char buffer[16];
            char host_part[16], md5_str[128];
            char *first_point=NULL, *second_point=NULL, *third_point=NULL;
            first_point = strchr( const_cast<char*>(host), 46); //find first .

            if(first_point != NULL)
            {
                second_point = strchr(first_point+1, 46); //find second .
                if(second_point != NULL)
                {
                    third_point = strchr(second_point+1, 46); //find third .
                    if(third_point != NULL)
                    {
                        int host_part_len = first_point - host;
                        if(host_part_len > 14) return 1;
                        strncpy(host_part, host, first_point-host);

                        host_part[host_part_len] = '_';

                        host_part_len += 1;
                        if(host_part_len+third_point-second_point-1 > 15) return 1;
                        strncpy(host_part+host_part_len, second_point+1, third_point-second_point-1);

                        host_part[first_point-host+third_point-second_point] = '\0';

                        total_len = first_point-host+third_point-second_point + strlen(usr) + strlen(pwd) + strlen(op);
                        if(total_len > 127) return 1; 

                        sprintf(md5_str, "%s%s%s%s", usr, pwd, op, host_part);
                        md5_str[total_len] = '\0';

                        osl::MD5 md5( (unsigned char *)md5_str, total_len );
                        char buf[33] = { '\0' };
                        md5.getHexDigest( buf );
                        memcpy( vk, buf + 24, 8 );
                        vk[8] = '\0';


                        //check data 
                        {
#ifdef H_DEBUG_MODE
                            unsigned char raw16bytes[16] = { '\0' };
                            md5.getRawDigest( raw16bytes );
                            char vk1[128] = { '\0' };
                            md5_text(vk1, raw16bytes+12, 4);
                            assert( strncmp( vk, vk1, 8) == 0 );
#endif
                        }
                        // 
                        // 						MD5_CTX md5;
                        // 						MD5Init(&md5);
                        // 						MD5Update(&md5, (unsigned char *)md5_str, total_len);
                        // 						MD5Final(buffer, &md5);

                        //md5_text(vk, buffer+12, 4);
                        return 0;
                    }
                }
            }
            return 1;
        }/*}}}*/
    } // end of namespace

    bool CACenter::doRequestUserVerify( const char* url, const char* operation, const char* op_type )
    {/*{{{*/
        if ( !url || !operation )
        {
            return false;
        }

        osl::StringA strHttpData;
        for ( osl::u32 i = 0; i <= m_nRetryTimes; ++i )
        {
            bool ret = CACenter::getEncryptKeyFromCACenter( 
                        url, 
                        m_strUserName.c_str(), 
                        m_strPassword.c_str(), 
                        operation, 
                        op_type,
                        m_strHostName.c_str(), 
                        m_strVersion.c_str(), 
                        m_nTimeout,
                        strHttpData );

            if ( ret && strHttpData.length() > 0 )
            {

                osl::Vector<osl::StringA> strvec;
                osl::StringUtil::split( strvec, strHttpData, "|" );
                if ( strvec.size() == 3 && strvec[0] == "0" )
                {
                    m_strUVErrno    = strvec[0];
                    m_strEncryptKey = strvec[1];
                    m_strDataSign   = strvec[2];
                    H_ASSERT( m_strEncryptKey.length() == 16 
                                && "CA web center response error" );
                    return true;
                }

            }

            if ( i < m_nRetryTimes )
            {
                logInfo( "CACenter", "getEncryptKeyFromCACenter failed."
                            "%ust to retry, CACenter %s", 
                            i + 1, strHttpData.c_str() );
                osl::Process::msSleep( (osl::s32)(m_fRetryInterval * 1000) );
            }
            else
            {
                logInfo( "CACenter", "getEncryptKeyFromCACenter failed,"
                            "we have retried %d times, but also failed."
                            "CA web center respnse : %s",
                            m_nRetryTimes, strHttpData.c_str() );
                return false;
            }
        }

        return false;
    }/*}}}*/

    bool CACenter::doRequestGetDecryptKey( const char* url, 
                const char* operation, const char* data_sign )
    {/*{{{*/
        if ( !url || !operation || !data_sign )
        {
            return false;
        }

        osl::StringA strHttpData;
        for ( osl::u32 i = 0; i <= m_nRetryTimes; ++i )
        {
            bool ret = CACenter::getDecryptKeyFromCACenter( 
                        url, 
                        m_strUserName.c_str(), 
                        m_strPassword.c_str(), 
                        operation, 
                        data_sign,
                        m_strHostName.c_str(), 
                        m_strVersion.c_str(), 
                        m_nTimeout,
                        strHttpData );

            if ( ret && strHttpData.length() > 0 )
            {
                osl::Vector<osl::StringA> strvec;
                osl::StringUtil::split( strvec, strHttpData, "|" );
                if ( strvec.size() == 2 && strvec[0] == "0" )
                {
                    m_strGetDecryptKeyErrno = strvec[0];
                    m_strDecryptKey = strvec[1];
                    return true;
                }
            }

            if ( i < m_nRetryTimes )
            {
                logInfo( "CACenter", "getDecryptKeyFromCACenter failed, "
                            "%ust to retry, CACenter resp:%s", 
                            i + 1, strHttpData.c_str() );
                osl::Process::msSleep( (osl::s32)(m_fRetryInterval * 1000) );
            }
            else
            {
                logInfo( "CACenter", "getDecryptKeyFromCACenter failed, "
                            "we have retried %d times, but also failed.", 
                            m_nRetryTimes );
                return false;
            }
        }


        return false;
    }/*}}}*/

    bool CACenter::doRequestOperationDone( const char* url, 
                const char* op, const char* data_sign )
    {/*{{{*/
        if ( !url || !op || !data_sign )
        {
            logInfo( "CACenter", "%s parameter wrong", __func__ );
            return false;
        }

        osl::StringA strHttpData;
        for ( osl::u32 i = 0; i <= m_nRetryTimes; ++i )
        {
            bool ret = CACenter::sendOperateDoneACK( url, op, 
                        data_sign, m_nTimeout, strHttpData );

            if ( ret && strHttpData.length() > 0 && strHttpData[0] == '0' )
            {
                return true;
            }
            else
            {
                if ( i < m_nRetryTimes )
                {
                    logInfo( "CACenter", "sendOperateDoneACK failed, "
                                "%ust to retry, CACenter resp:%s", 
                                i + 1, strHttpData.c_str() );
                    osl::Process::msSleep( (osl::s32)(m_fRetryInterval * 1000) );
                }
                else
                {
                    logInfo( "CACenter", "sendOperateDoneACK failed, "
                                "we have retried %d times, but also failed."
                                , m_nRetryTimes );
                    return false;
                }
            }
        }
        return false;
    }/*}}}*/

    bool CACenter::getEncryptKeyFromCACenter( const char* url, const char* usr, 
				const char* pwd, 
				const char* op, 
				const char* op_type, 
				const char* host, 
				const char* ver, 
                unsigned int timeout,
				osl::StringA& output )
    {/*{{{*/
        if ( !url || !usr || !pwd || !op || !host || !ver )
        {
            logWarn( "CACenter", "parameter wrong. url=%p usr=%p pwd=%p op=%p host=%p ver=%p", url, usr, pwd, op, host, ver );
            return false;
        }

        net::HttpPostWorkPtr pWork = H_NEW net::HttpPostWork( url );
        pWork->setTimeOut( timeout );
        pWork->addParameter( "usr", usr );
        pWork->addParameter( "pwd", pwd );
        pWork->addParameter( "op",  op );
        pWork->addParameter( "op_type",  op_type );
        pWork->addParameter( "host", host );
        pWork->addParameter( "ver", ver );


        //! vk -  a string as substr(md5($usr.$pwd.$op.$host_part), -8,8) , 
        //!       $host_part is the 1st and 3st of the host name separated by pointer '.'
        //!       e.g: hostname=kill1.safe.lfc.qihoo.net => $host_part=kill1_lfc

        char vk[32] = { '\0' };
        getVk( usr, pwd, op, host, vk );
        pWork->addParameter( "vk", vk );

        pWork->setBlockingDoHttpRequest( true );
        if ( !pWork->doHttpBlockingRequest() )
        {
            logError( "CACeter", "curl operater failed" );
            return false;
        }

        osl::MemoryDataStream* pdata = pWork->getRecvDataStream();
        output = osl::StringA( (const char*)pdata->getCache(), pdata->getSize() );

        return true;
    }/*}}}*/

    bool CACenter::getDecryptKeyFromCACenter( const char* url, const char* usr, const char* pwd, const char* op, const char* data_sign, const char* host, const char* ver, unsigned int timeout, osl::StringA& output )
    {/*{{{*/
        if ( !url || !usr || !pwd || !op || !host || !ver || !data_sign )
        {
            logWarn( "CACenter", "parameter wrong. url=%p usr=%p pwd=%p op=%p host=%p ver=%p", url, usr, pwd, op, host, ver );
            return false;
        }

        net::HttpPostWorkPtr pWork = H_NEW net::HttpPostWork( url );
        pWork->setTimeOut( timeout );
        pWork->addParameter( "usr", usr );
        pWork->addParameter( "pwd", pwd );
        pWork->addParameter( "op",  op );
        pWork->addParameter( "host", host );
        pWork->addParameter( "ver", ver );
        pWork->addParameter( "data_sign", data_sign );


        //! vk -  a string as substr(md5($usr.$pwd.$op.$host_part), -8,8) , 
        //!       $host_part is the 1st and 3st of the host name separated by pointer '.'
        //!       e.g: hostname=kill1.safe.lfc.qihoo.net => $host_part=kill1_lfc

        char vk[32] = { '\0' };
        getVk( usr, pwd, op, host, vk );
        pWork->addParameter( "vk", vk );

        pWork->setBlockingDoHttpRequest( true );
        if ( !pWork->doHttpBlockingRequest() )
        {
            return false;
        }

        osl::MemoryDataStream* pdata = pWork->getRecvDataStream();
        output = osl::StringA( (const char*)pdata->getCache(), pdata->getSize() );

        return true;
    }/*}}}*/

    bool CACenter::sendOperateDoneACK( const char* url, const char* op, const char* data_sign, unsigned int timeout, osl::StringA& output )
    {/*{{{*/
        if ( !url || !op || !data_sign )
        {
            logWarn( "CACenter", "parameter wrong. url=%p op=%p datasign=%p", url, op, data_sign );
            return false;
        }


        net::HttpPostWorkPtr pWork = H_NEW net::HttpPostWork( url );
        pWork->setTimeOut( timeout );
        pWork->addParameter( "op",  op );
        pWork->addParameter( "data_sign", data_sign );

        pWork->setBlockingDoHttpRequest( true );
        if ( !pWork->doHttpBlockingRequest() )
        {
            return false;
        }

        osl::MemoryDataStream* pdata = pWork->getRecvDataStream();
        output = osl::StringA( (const char*)pdata->getCache(), pdata->getSize() );

        return true;
    }/*}}}*/

} // end of namespace ext

#endif // end of #if ( H_PROVIDE_NET_CA_ENCRYPT && H_PROVIDE_IDEA_ENCRYPT )



