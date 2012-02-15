#include "libtest/include/inner_pre.h"

#include "libtest/include/test_object.h"

#include "osl/include/idea_wrapper.h"
#include "osl/include/file_util.h"
#include "osl/include/ini_parser.h"
#include "osl/include/crc32.h"

#include "apputil/include/ca_center.h"

#if H_PROVIDE_IDEA_ENCRYPT
#ifdef H_WINDOWS_API
#	ifdef H_DEBUG_MODE
#		pragma comment(lib,"libeay32.lib")
#	else
#		pragma comment(lib,"libeay32.lib")
#	endif
#endif
#endif // end of #if ( H_PROVIDE_NET_CA_ENCRYPT && H_PROVIDE_IDEA_ENCRYPT )


namespace
{
	class TCACenter : public LibTest::ITestObject
	{
		void testAll();
		const char* getCommand();
		const char* getDesc();
		void invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell );


		void test_1();

        void test_encrypt_decrypt( const unsigned char* s );

        void test_2();
		void test_3_fwrite();
		void test_dataloader();
        void test_decodedumpfile(
            const osl::StringA& user, 
            const osl::StringA& password, 
            const osl::StringA& indir, 
            const osl::StringA& outdir );
	};

	const char* TCACenter::getCommand()
	{
		return "test_cacenter";
	}

	const char* TCACenter::getDesc()
	{
		return "test_cacenter \n\ttest_cacenter decodedumpfile --user=weizili --password=mypassword --in=/tmp/originaldata/ --out=/tmp/decode/";
	}

	void TCACenter::testAll()
	{
		test_1();
		test_2();
		test_3_fwrite();
		test_dataloader();

		//std::cout<< getCommand() << " test all ok!" << std::endl;
	}

	void TCACenter::invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell )
	{
		if ( pCmd->hasTarget( "decodedumpfile" ) )
		{
            osl::AppShell::Param* pp = pCmd->getParam("user");
            if ( !pp )
            {
                return;
            }
            osl::StringA user = pp->strVal;

            pp = pCmd->getParam("password");
            if ( !pp )
            {
                return;
            }
            osl::StringA password = pp->strVal;
            

            pp = pCmd->getParam("in");
            if ( !pp )
            {
                return;
            }
            osl::StringA indir = pp->strVal;


            pp = pCmd->getParam("out");
            if ( !pp )
            {
                return;
            }
            osl::StringA outdir = pp->strVal;


			test_decodedumpfile(user,password,indir,outdir);
		}
		else
		{
			testAll();
		}
	}

	void TCACenter::test_1()
	{
        {
            osl::StringA strideakey = "abcdefghabcdefgh";
			const unsigned char* s = ( const unsigned char* )"abcdefg";
			unsigned int len = strlen( ( const char* )s );
			osl::MemoryDataStream ds;
			osl::IDEA::encrypt( s, len, strideakey, ds );
			{
				::IDEA_KEY_SCHEDULE keyIdeaEncrypt;
				::idea_set_encrypt_key( ( osl::u8* )strideakey.c_str(), &keyIdeaEncrypt );
				osl::MemoryDataStream encrypted;
				osl::IDEA::encrypt( s, len, keyIdeaEncrypt, encrypted );
				H_ASSERT( 0 == strncmp( ( const char* )ds.getCache(), ( const char* )encrypted.getCache(), ds.getSize() ) );
			}
			H_ASSERT( ds.getSize() == H_ALIGN( len, 8 ) );
			{
				osl::MemoryDataStream decrypted;
				osl::IDEA::decrypt( ( osl::u8* )ds.getCache(), ds.getSize(), strideakey, decrypted );
				H_ASSERT( 0 == strncmp( ( const char* )s, ( const char* )decrypted.getCache(), len ) );
			}

			{
				osl::MemoryDataStream decrypted;
				::IDEA_KEY_SCHEDULE keyIdeaEncrypt;
				::IDEA_KEY_SCHEDULE keyIdeaDecrypt;
				::idea_set_encrypt_key( ( osl::u8* )strideakey.c_str(), &keyIdeaEncrypt );
				::idea_set_decrypt_key( &keyIdeaEncrypt, &keyIdeaDecrypt );
				osl::IDEA::decrypt( ( osl::u8* )ds.getCache(), ds.getSize(), keyIdeaDecrypt, decrypted );
				H_ASSERT( 0 == strncmp( ( const char* )s, ( const char* )decrypted.getCache(), len ) );
			}


			s = ( const unsigned char* )"0123456789";
			len = strlen( ( const char* )s );
			ds.reset();
			osl::IDEA::encrypt( s, len, strideakey, ds );
			H_ASSERT( ds.getSize() == H_ALIGN( len, 8 ) );


			s = ( const unsigned char* )"abcdefg1234567893366521455513231213321321";
			len = strlen( ( const char* )s );
			ds.reset();
			osl::IDEA::encrypt( s, len, strideakey, ds );
			H_ASSERT( ds.getSize() == H_ALIGN( len, 8 ) );
		}


        {

            const unsigned char* s = NULL;
            s = ( const unsigned char* )"abcdefg";
            test_encrypt_decrypt(s);
            s = ( const unsigned char* )"uiasiudfuiasdiufaiusdfiuasdifuasiudfiuasdfiuasdiufaisudfiuasdfhasdfahsdfhasdfhasdkfjsadkjfasdfasdhf  ;';';      46123124124576543234568543214567890!@#$%^&*(''-0-09 09 8 8 89 7 7 6 56 5";
            test_encrypt_decrypt(s);
            s = ( const unsigned char* )"uiassdfasdfasdfasd5f4asd   ```~~``1122234~!@#$%^&*()_+[}{{}[[][]/'';;'\\\\\\;;lkkjhgfdfghjkl5f4a6sd4fas6dfas3df1as3d2f1as6df84as6df7/*//*//**//*/***---+++/iudfuiasdiufaiusdfiuasdifuasiudfiuasdfiuasdiufaisudfiuasdfhasdfahsdfhasdfhasdkfjsadkjfasdfasdhf  ;';';      46123124124576543234568543214567890!@#$%^&*(''-0-09 09 8 8 89 7 7 6 56 5";
            test_encrypt_decrypt(s);
            s = ( const unsigned char* )"abcdefg1234567893366521455513231213321321";
            test_encrypt_decrypt(s);
            s = ( const unsigned char* )"1";
            test_encrypt_decrypt(s);
            s = ( const unsigned char* )"12";
            test_encrypt_decrypt(s);
            s = ( const unsigned char* )"123";
            test_encrypt_decrypt(s);
            s = ( const unsigned char* )"1234";
            test_encrypt_decrypt(s);
            s = ( const unsigned char* )"12345";
            test_encrypt_decrypt(s);
            s = ( const unsigned char* )"123456";
            test_encrypt_decrypt(s);
            s = ( const unsigned char* )"1234567";
            test_encrypt_decrypt(s);
            s = ( const unsigned char* )"12345678";
            test_encrypt_decrypt(s);
            s = ( const unsigned char* )"123456789";
            test_encrypt_decrypt(s);
            s = ( const unsigned char* )"12345678901";
            test_encrypt_decrypt(s);
            s = ( const unsigned char* )"123456789012";
            test_encrypt_decrypt(s);
            s = ( const unsigned char* )"1234567890123";
            test_encrypt_decrypt(s);
            s = ( const unsigned char* )"12345678901234";
            test_encrypt_decrypt(s);
            s = ( const unsigned char* )"123456789012345";
            test_encrypt_decrypt(s);
            s = ( const unsigned char* )"1234567890123456";
            test_encrypt_decrypt(s);
            s = ( const unsigned char* )"12345678901234567";
            test_encrypt_decrypt(s);
        }


	}

    void TCACenter::test_encrypt_decrypt( const unsigned char* s )
    {
        {
            osl::StringA strideakey = "abcdefghabcdefgh";
            IDEA_KEY_SCHEDULE ekey;
            IDEA_KEY_SCHEDULE dkey;
            idea_set_encrypt_key( (const unsigned char*)strideakey.c_str(), &ekey );
            idea_set_decrypt_key( &ekey, &dkey );
            osl::IDEA::mem_data_t endata;
            osl::IDEA::mem_data_t dedata;

            endata.data = (u_char*)malloc( 1024 );
            dedata.data = (u_char*)malloc( 1024 );

            unsigned int len = strlen( ( const char* )s );


            osl::IDEA::encrypt( s, len, &ekey, &endata );
            {
                ::IDEA_KEY_SCHEDULE keyIdeaEncrypt;
                ::idea_set_encrypt_key( ( osl::u8* )strideakey.c_str(), &keyIdeaEncrypt );
                osl::MemoryDataStream encrypted;
                osl::IDEA::encrypt( s, len, keyIdeaEncrypt, encrypted );
                if ( endata.data_len > 0 )
                {
                    H_ASSERT( 0 == strncmp( (const char*)endata.data, ( const char* )encrypted.getCache(), endata.data_len ) );
                }
                H_ASSERT( endata.data_len == H_ALIGN( len, 8 ) );
                H_ASSERT( endata.data_len == encrypted.getSize() );
            }


            {
                osl::MemoryDataStream decrypted;
                osl::IDEA::decrypt( endata.data, endata.data_len, dkey, decrypted );
                osl::IDEA::decrypt( endata.data, endata.data_len, &dkey, &dedata );
                H_ASSERT( dedata.data_len == H_ALIGN(len, 8) );
                H_ASSERT( decrypted.getSize() == dedata.data_len );
                if ( dedata.data_len > 0 ) 
                {
                    H_ASSERT( 0 == strncmp( ( const char* )s, ( const char* )decrypted.getCache(), len ) );
                }
            }

            free( endata.data );
            free( dedata.data );
        }
    }

	void TCACenter::test_2()
	{

		/*
		const char* usr = "weizili";
		const char* pwd = "english";
		const char* op  = "dump";
		const char* ver = "Ccweb_engine_v0.3";
		const char* host = "192.168.32.103";
        const char* url_userverify    = "http://192.168.0.181:8360/datasafe/interface_check.php";
		const char* url_getdecryptkey = "http://192.168.0.181:8360/datasafe/interface_getkey.php";
		const char* url_operationdon  = "http://192.168.0.181:8360/datasafe/interface_done.php";
        */

		const char* usr = "hemanbin";
		const char* pwd = "mypass";
		const char* op  = "dump";
		const char* ver = "storage_cluster.v0.1";
		const char* host = "192.168.32.103";
		const char* url_userverify    = "https://app4.safe.lfc.qihoo.net/datasafe/interface_check.php";
		const char* url_getdecryptkey = "https://app4.safe.lfc.qiho/datasafe/interface_getkey.php";
		const char* url_operationdon  = "https://app4.safe.lfc.qiho/datasafe/interface_done.php";

		aut::CACenter cacenter( usr, pwd, host, ver, 30, 3, 1 );
		bool bUserVerifyOK = cacenter.doRequestUserVerify( url_userverify, op, "dump" );


		osl::StringA strideakey_encrypt  = cacenter.getEncryptKey();
		osl::StringA strdatasign = cacenter.getDataSign();

		bool bUserVerifyDoneOK = cacenter.doRequestOperationDone( url_operationdon, op, strdatasign.c_str() );

		if ( !bUserVerifyOK || !bUserVerifyDoneOK )
		{
            logError("", "verify failed!");
			return;
		}


		op = "load";
		bool bGetDecryptKeyOK = cacenter.doRequestGetDecryptKey( url_getdecryptkey, op, strdatasign.c_str() );
		osl::StringA strideakey_decrypt = cacenter.getDecryptKey();
		bool bGetDecryptKeyDoneOK = cacenter.doRequestOperationDone( url_operationdon, op, strdatasign.c_str() );

		if ( !bGetDecryptKeyOK || !bGetDecryptKeyDoneOK )
		{
			return;
		}


		const osl::u32 DATA_SIZE = 26 * 1024;

		osl::MemoryDataStream sourceData( DATA_SIZE );

		for ( osl::u32 i = 0; i < DATA_SIZE / 26; ++i )
		{
			sourceData.write( "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 26 );
		}


		osl::MemoryDataStream dataEncrypted;
		bool bEncryptedOK = osl::IDEA::encrypt(
		                        ( osl::u8* )sourceData.getCache(), sourceData.getSize(), strideakey_encrypt, dataEncrypted );

		osl::MemoryDataStream dataDecrypted;
		bool bDecryptedOK = osl::IDEA::decrypt(
		                        ( osl::u8* )dataEncrypted.getCache(), dataEncrypted.getSize(), strideakey_decrypt, dataDecrypted );

		H_ASSERT( bEncryptedOK && bDecryptedOK );
        (void)bEncryptedOK;
        (void)bDecryptedOK;

		for ( osl::u32 i = 0; i < DATA_SIZE; ++i )
		{
			char d = dataDecrypted.charAt( i );
			char c = sourceData.charAt( i );
			H_ASSERT( d == c );
            (void)d;
            (void)c;
		}

	}

	namespace
	{
#define H_TEST_CRC

		typedef osl::u8  uint8_t;
		typedef osl::u16 uint16_t;
		typedef osl::u32 uint32_t;

            class DataLoader
            {
            public:
                DataLoader( int bucketid,
                    const osl::StringA& datafile, 
                    const osl::StringA& decodedfile, 
                    const osl::StringA& usr,
                    const osl::StringA& pwd, 
                    const osl::StringA& ip,
                    int iLoadToDB = 0 )
                    : m_bucketid( bucketid )
                    , m_strDataFilePath( datafile )
                    , m_fp( NULL )
                    , m_strOutFileName( decodedfile )
                    , m_fpOutFile( NULL )
                    , m_CACenter( usr.c_str(), pwd.c_str(), ip.c_str(), NULL, 30, 3, 1 )
                    , m_bLoadSuccess( true )
                    , m_strOperateMsg( "OK" )
                    , m_buf(1024)
                    , m_nItemCount( 0 )  
                    , m_version( 0 )
                    , m_iLoadToDB( iLoadToDB )
                {
                    memset( m_szDataSign, 0, sizeof( m_szDataSign ) );
#ifdef H_TEST_CRC
                    m_nCRCTotalData = 0;
#endif
                    m_nCRCInFile = 0;

                }

                bool doWork()
                {
                    if ( begin() )
                    {
                        load(); 
                        end();
                    }
                    else
                    {
                        end();
                    }

                    return this->isLoadSuccess();
                }

                bool begin()
                {
                    m_fp = ::fopen( m_strDataFilePath.c_str(), "r" );

                    if ( !m_fp )
                    {
                        m_bLoadSuccess = false;
                        osl::OStringStream log;
                        log << "Data file cannot opened : " << m_strDataFilePath ;
                        m_strOperateMsg = log.str();
                        H_LOG_NAME_WARN( LOG_NAME, m_strOperateMsg );
                        return false;
                    }


                    m_fpOutFile = ::fopen( m_strOutFileName.c_str(), "w+" );

                    if ( !m_fpOutFile )
                    {
                        m_bLoadSuccess = false;
                        m_strOperateMsg = "Out put decoded data file cannot opened.\r\n";
                        return false;
                    }

#ifdef H_OS_WINDOWS
                    osl::StringA strConfPath = osl::Process::getBinDir( true ) + "../data/libtestdata/qoslib/iniparser/auth.ini";
#else
                    osl::StringA strConfPath = osl::Process::getBinDir( true ) + "../etc/auth.ini";
#endif
                    if ( !m_INIParser.parse( strConfPath ) )
                    {
                        ::fclose( m_fp );
                        m_fp = 0;

                        m_bLoadSuccess = false;
                        m_strOperateMsg = strConfPath + " file format wrong or not exist.";
                        H_LOG_NAME_WARN( LOG_NAME, m_strOperateMsg );
                        return false;
                    }



                    return true;
                }


                bool end()
                {

                    if ( m_fp )
                    {
                        ::fclose( m_fp );
                        m_fp = NULL;
                    }

                    if ( m_fpOutFile )
                    {
                        ::fclose( m_fpOutFile );
                        m_fpOutFile = NULL;
                    }

                    //if it is not the encrypt data we need to verify the crc code
                    if ( isUnencryptData() )
                    {
                        return m_bLoadSuccess;
                    }

                    const char* szURL = m_INIParser.get( "OP_END_INTF" );
                    if ( !szURL || !m_CACenter.doRequestOperationDone( szURL, "load", m_CACenter.getDataSign().c_str() ) )
                    {
                        m_strOperateMsg = m_CACenter.getUserName() + " do 'load' send operation DONE verification wrong";
                        H_LOG_NAME_WARN( LOG_NAME, m_strOperateMsg );
                        m_bLoadSuccess = false;
                    }

#ifdef H_TEST_CRC
                    if ( m_nCRCInFile != m_nCRCTotalData )
                    {
                        m_bLoadSuccess = false;
                        m_strOperateMsg = "CRC32 verify failed!";
                        H_LOG_NAME_WARN( LOG_NAME, m_strOperateMsg );
                    }
                    else
                    {
                        osl::OStringStream log;
                        log << "CRC32 verify OK, crc=" << m_nCRCTotalData;
                        H_LOG_NAME_INFO( LOG_NAME, log.str() );
                    }
#endif	


                    return m_bLoadSuccess;
                }

                bool load()
                {

                    if ( !m_bLoadSuccess )
                    {
                        return false;
                    }

                    //read version and determine which load method to call
                    {

                        m_buf.reset();
                        size_t rc = ::fread( m_buf.getCache(), sizeof( m_version ), 1, m_fp );
                        if ( rc != 1 )
                        {
                            m_bLoadSuccess = false;
                            m_strOperateMsg = "File content wrong. Cannot read version.";
                            logWarn( LOG_NAME, "%s", m_strOperateMsg.c_str() );
                            return false;
                        }
                        m_buf.seekp( sizeof( m_version ) );
                        m_buf.readle( &m_version );

                        if ( 1 == m_version )
                        {
                            //directly go to continue to load data file
                            logWarn( LOG_NAME, "Load an encrypted data." );
                            return load_v1();
                        }
                        else if ( isUnencryptData() )
                        {
                            // this is a no encrypt data file
                            H_LOG_NAME_INFO( LOG_NAME, "Load an plaintext data." );
                            ::fseek( m_fp, 0, SEEK_SET );//set the file pointer to the beginning
                            return load_v0();
                        }

                    }

                    return false;
                }

                bool isUnencryptData() const
                {
                    return ( m_version > 0xffffff );
                }

                bool load_v0()
                {
                    return true;
                }

                bool load_v1()
                {
                    //// step 1 : parse encrypted data file header
                    if ( !parseDataFileHeader_v1() )
                    {
                        return false;
                    }

                    //// step 2 : get the decrypt key from CA center
                    if ( !requestDecryptKey_v1() )
                    {
                        return false;
                    }

                    //// step 3 : decrypt data and load data
                    return loadItems_v1();
                }

                bool loadItems_v1()
                {
                    /*
                    for ( item in items )
                    {
                    4 bytes item data original len (according to this length we can calculate the encrypted item data length)
                    encrypted item data (the length is a multiple of 8)
                    }
                    */
                    osl::u32 nOrigDataLen = 0;
                    osl::u32 nEncryptedItemLen = 0;
                    osl::MemoryDataStream origdata( 65535 + 40 );
                    osl::MemoryDataStream decrypteddata( 65535 + 40 );


                    while ( !::feof( m_fp ) )
                    {

                        origdata.reset();
                        size_t rc = ::fread( origdata.getCache(), 1, sizeof( nOrigDataLen ), m_fp );
                        if( rc != sizeof( nOrigDataLen ) )
                        {
                            continue;
                        }
                        origdata.seekp( sizeof(nOrigDataLen) );
                        nOrigDataLen = 0;
                        origdata.readle( &nOrigDataLen );

                        nEncryptedItemLen = H_ALIGN( nOrigDataLen, 8 );

                        origdata.reset();
                        rc = ::fread( origdata.getCache(), 1, nEncryptedItemLen, m_fp );
                        if( rc != nEncryptedItemLen )
                        {
                            continue;
                        }
                        origdata.seekp( nEncryptedItemLen );

                        decrypteddata.reset();
                        osl::IDEA::decrypt( static_cast<osl::u8*>( origdata.getCache() ), origdata.getSize(), m_keyDecrypt, decrypteddata );
                        origdata.seekg( nEncryptedItemLen );

                        osl::u8* pitemdata = static_cast<osl::u8*>( decrypteddata.getCache() );

#ifdef H_TEST_CRC
                        m_nCRCTotalData ^= osl::CRC32::getCRC32( pitemdata, nOrigDataLen );//calc the CRC32
#endif

                        if ( !loadItem_v1( pitemdata, nOrigDataLen ) )
                        {
                            return false;
                            break;
                        }
                    }

                    return true;
                }

                bool loadItem_v1( osl::u8* buffer, size_t origlen )
                {
                    const size_t nkey = 32;
                    osl::u8* key = buffer;

                    osl::u32 flags = buffer[nkey+1];
                    osl::u16 ndata = 0;
                    ndata |= ( ( osl::u16 ) buffer[nkey+2] << 0 );
                    ndata |= ( ( osl::u16 ) buffer[nkey+3] << 8 );
                    H_ASSERT( origlen == nkey + 4 + ndata );

                    std::string k( reinterpret_cast<const char *>( key ), nkey );
                    std::string v;
                    v.reserve( ndata + 2 );
                    v.append( reinterpret_cast<const char*>( buffer + nkey + 4 ), ndata );
                    v.append( "\r\n" );


                    //out put the decoded data file
                    {
                        osl::MemoryDataStream outbuf( 65536 + 36 );
                        outbuf.write( k.c_str(), k.length() );
                        outbuf.write( '\t' );
                        outbuf.write( ( char )( flags & 0xff ) );
                        outbuf.write( ( char ) ( ndata >> 8 & 0xff ) );
                        outbuf.write( ( char ) ( ndata & 0xff ) );
                        outbuf.write( reinterpret_cast<const char*>( buffer + nkey + 4 ), ndata );
                        ::fwrite( outbuf.getCache(), 1, outbuf.getSize(), m_fpOutFile );
                        ::fflush( m_fpOutFile );
                    }

                    ++m_nItemCount;
#ifdef H_DEBUG_MODE
                    osl::OStringStream log;
                    log << "key=" << k << "\nvalue=" << v;
                    H_LOG_NAME_DEBUG( LOG_NAME, log.str() );
#endif

                    return true;
                }

                bool parseDataFileHeader_v1()
                {

                    /**
                    4 bytes CRC of original data
                    4 bytes data_sign length
                    256 bytes data_sign string
                    */


                    // step 1 : read 4 bytes CRC 
                    {

                        m_buf.reset();
                        size_t rc = ::fread( m_buf.getCache(), sizeof( m_nCRCInFile ), 1, m_fp );
                        if ( rc != 1 )
                        {
                            m_bLoadSuccess = false;
                            m_strOperateMsg = "File content wrong. Cannot read CRC.";
                            return false;
                        }
                        m_buf.seekp( sizeof( m_nCRCInFile ) );
                        m_buf.readle( &m_nCRCInFile );
                    }

                    // step 2 : read 4 bytes of data_sign length
                    osl::u32 nDataSignLen = 0;
                    m_buf.reset();

                    size_t rc = ::fread( m_buf.getCache(), sizeof( nDataSignLen ), 1, m_fp );
                    if( rc != 1 )
                    {
                        m_bLoadSuccess = false;
                        m_strOperateMsg = "Read data file error! Cannot read the length of data sign.";
                        H_LOG_NAME_WARN( LOG_NAME, m_strOperateMsg );
                        return false;
                    }
                    m_buf.seekp( sizeof( nDataSignLen ) );
                    m_buf.readle( &nDataSignLen );


                    // step 3 : read data_sign string
                    rc = ::fread( m_szDataSign, 1, sizeof( m_szDataSign ), m_fp );
                    if( rc != sizeof( m_szDataSign ) )
                    {
                        m_bLoadSuccess = false;
                        m_strOperateMsg = "Read data file error! cannot read data sign.";
                        H_LOG_NAME_WARN( LOG_NAME, m_strOperateMsg );
                        return false;
                    }
                    m_szDataSign[nDataSignLen] = 0;

                    return true;
                }


                bool requestDecryptKey_v1()
                {
                    const char* szURL = m_INIParser.get( "KEY_ADMIN_INTF" );
                    if ( !szURL )
                    {
                        m_bLoadSuccess = false;
                        m_strOperateMsg = "etc/authoritycenter.ini content wrong, cannot find USER_VERIFY_INTF";
                        H_LOG_NAME_WARN( LOG_NAME, m_strOperateMsg );
                        return false;
                    }

                    const char* szVer = m_INIParser.get( "STORAGE_CLUSTER_VERSION" );
                    if ( !szVer )
                    {
                        m_bLoadSuccess = false;
                        m_strOperateMsg = "etc/authoritycenter.ini content wrong, cannot find STORAGE_CLUSTER_VERSION";
                        H_LOG_NAME_WARN( LOG_NAME, m_strOperateMsg );
                        return false;
                    }


                    const char* szRetryInterval = m_INIParser.get( "REQ_RETRY_INTERVAL" );
                    if ( !szRetryInterval )
                    {
                        m_strOperateMsg = "etc/authoritycenter.ini content wrong, cannot find REQ_RETRY_INTERVAL";
                        H_LOG_NAME_WARN( "datadumper", m_strOperateMsg );
                        return false;
                    }

                    const char* szTimeout = m_INIParser.get( "REQ_TIMEOUT" );
                    if ( !szTimeout )
                    {
                        m_strOperateMsg = "etc/authoritycenter.ini content wrong, cannot find REQ_TIMEOUT";
                        H_LOG_NAME_WARN( "datadumper", m_strOperateMsg );
                        return false;
                    }

                    const char* szRetryTimes = m_INIParser.get( "REQ_RETRY_TIMES" );
                    if ( !szRetryTimes )
                    {
                        m_strOperateMsg = "etc/authoritycenter.ini content wrong, cannot find REQ_RETRY_TIMES";
                        H_LOG_NAME_WARN( "datadumper", m_strOperateMsg );
                        return false;
                    }

                    m_CACenter.setVersion( szVer );
                    m_CACenter.setTimeout( osl::StringUtil::toU32(szTimeout) );
                    m_CACenter.setRetryTimes( osl::StringUtil::toU32(szRetryTimes) );
                    m_CACenter.setRetryInterval( osl::StringUtil::toF32(szRetryInterval) );


                    if ( !m_CACenter.doRequestGetDecryptKey( szURL, "load", m_szDataSign ) )
                    {
                        m_bLoadSuccess = false;
                        m_strOperateMsg = m_CACenter.getUserName() + " do 'load' operation verification wrong";
                        H_LOG_NAME_WARN( LOG_NAME, m_strOperateMsg );
                        return false;
                    }
                    else
                    {
                        H_LOG_NAME_INFO( LOG_NAME, "Authority verification pass." );
                    }

                    const unsigned char* szIdeaKey = reinterpret_cast<const unsigned char*>( m_CACenter.getDecryptKey().c_str() );

                    ::IDEA_KEY_SCHEDULE keyIdeaEncrypt;

                    ::idea_set_encrypt_key( szIdeaKey, &keyIdeaEncrypt );

                    ::idea_set_decrypt_key( &keyIdeaEncrypt, &m_keyDecrypt );


                    {
#ifdef H_DEBUG_MODE
                        osl::OStringStream log;
                        log << "decrypted key=" << szIdeaKey;
                        H_LOG_NAME_DEBUG( LOG_NAME, log.str() );
#endif
                    }


                    return true;
                }


                bool isLoadSuccess() const
                {
                    return m_bLoadSuccess;
                }


                const osl::StringA& getOperateMsg() const
                {
                    return m_strOperateMsg;
                }

                const size_t getItemCount() const 
                {
                    return m_nItemCount;
                }

            private:
                int                       m_bucketid;
                osl::StringA       m_strDataFilePath;
                FILE*                           m_fp;

                osl::StringA        m_strOutFileName;
                FILE*                    m_fpOutFile;


                osl::MemoryDataStream       m_outbuf;

                aut::CACenter             m_CACenter;

                ::IDEA_KEY_SCHEDULE     m_keyDecrypt;

                bool                  m_bLoadSuccess;
                osl::StringA		 m_strOperateMsg;

                osl::INIParser           m_INIParser;

                osl::MemoryDataStream          m_buf;

#ifdef H_TEST_CRC
                osl::u32             m_nCRCTotalData;
#endif
                osl::u32                m_nCRCInFile;

                size_t                  m_nItemCount;

                osl::u32				   m_version;

                int                      m_iLoadToDB;

                char  m_szDataSign[aut::CACenter::DATA_SIGN_MAX_LEN];
            };

	}//end of namespace

	void TCACenter::test_dataloader()
	{
// 		osl::StringA strDataPath = osl::Process::getBinDir( true ) + "../data/libtestdata/memcached/v7.db";
// 		const char* usr = "weizili";
// 		const char* pwd = "english";
// 		const char* op  = "load"; (void)op;
// 		const char* host = "192.168.0.225";
// 		DataLoader loader( 0, strDataPath, strDataPath + ".decoded", usr, pwd, host );
// 		loader.doWork();
// 
// 		if ( loader.isLoadSuccess() )
// 		{
// 		}
	}

	void TCACenter::test_3_fwrite()
	{
		const char* s1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		FILE* fp = ::fopen( ( osl::Process::getBinDir( true ) + "test.txt" ).c_str(), "w+" );
		::fwrite( s1, 1, strlen( s1 ), fp );
		::fflush( fp );

		const char* s2 = "0123456789";
		::fseek( fp, 0, SEEK_SET );
		::fwrite( s2, 1, strlen( s2 ), fp );//this will overwrite the file's leading data
		::fclose( fp );
	}

    void TCACenter::test_decodedumpfile(
        const osl::StringA& user, 
        const osl::StringA& password, 
        const osl::StringA& indir, 
        const osl::StringA& outdir )
	{
		char host[64] = "192.168.0.225";


        osl::StringAList infiles;
        osl::FileUtil::listAllFiles(indir, infiles );

        osl::StringAList::iterator it(infiles.begin());
        osl::StringAList::iterator ite(infiles.end());
        for ( ; it != ite; ++it )
        {
            osl::StringA strFileName;
            osl::StringA strBaseDir;
            osl::FileUtil::splitFileName( *it, strFileName, strBaseDir, true );
            osl::StringA strOutFileName = osl::FileUtil::concatenatePath( outdir, "decoded." + strFileName );

            DataLoader loader( 0, *it, strOutFileName, user, password, host );
            loader.doWork();

            if ( !loader.isLoadSuccess() )
            {
                std::cout << "Decode failed : " << *it << std::endl;
            }
        }
        
        std::cout << "Decode done!" << std::endl;
	}

    
}




CREATE_FUNCTION( TCACenter );








