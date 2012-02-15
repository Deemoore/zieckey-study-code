#include "libtest/include/inner_pre.h"

#include "osl/include/file_util.h"
#include "osl/include/md5.h"

#include "net/include/http_post_work.h"

#include "curl/curl.h"


#include "libtest/include/test_object.h"

#include "osl/include/event.h"
#include "net/include/curl_service.h"
#include "net/include/curl_work.h"


namespace LibTest
{
    //class MyFileServiceListener;

    class TCurl : public ITestObject, public net::CURLWork::Listener
    {
        H_REFERENCE_METHODS( osl::Object );
    public:
        TCurl();
        ~TCurl();

        const char* getCommand()
        {
            return "test_curl";
        }
        const char* getDesc()
        {
            return "test_curl --cfgfile=config_file_name"
                "(input the config filename, we will read this file and send HTTP request according to this file)"
                "\n\t--type=1(download file)|2(upload file)|3(http post)|4(down out website url)"
                "|5(cookie) --cookie=EA4556FDF2EDCAFEF17FE1007ECBD5F7|6(sample)|7(FileDownWork)"
                "|8(downurl)|9(http header)|10(compress)|11(headerparse)|12(speed)|13(resumable)"
                "|14(percentage)|15(blockingrequest)|16(curl_post_bin_data)|17(msv)|0(all)";
        }
        void invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell );

        void processCURLAutoTest( osl::AppShell::Command* pCmd );

        void onFinishErrorT( net::HttpErrorCode hec, const osl::StringA& errmsg, net::CURLWork* pw  );
        void onFinishOKT( net::CURLWork* pw );

    private:
        void testAll();
        void testDownloadWorkURL();
        void testFileDownloader();
        void testHttpPostWork();
        void testDownloadOuterWebSite();
        void testFileUpload();
        void testCURLSample();
        void testCookie( const osl::StringA& cookie );
        void testFileDownWork();
        void testCookieSample();
        void testFileDownloadSpeed();

        void testBlockingDoHttpRequest();

        void testAddHeader();

        void testHttpHeaderParser();

        void testCompressFileUploadAndDownload( int ncount = 1000 );

        void testResumableTransfer();//断点续传

        void testonWorkingPercentage();//下载报告百分比

        void test_curl_post_bin_data_16();

        void test_msv_17();

        void test_HttpPostWork_appendParameters_18();

    private:
        void printCookies( void *curl );


        //
        // 		net::HttpPostFile* createHttpPostFile( Json::JSONObject* pJWorkUnit );
        // 		net::HttpPostWork* createHttpPostWork( Json::JSONObject* pJWorkUnit );
        // 		net::HttpGetWork* createHttpGetWork( Json::JSONObject* pJWorkUnit );
        // 
        // 		void addCURLWorkParameters( Json::JSONObject* pJParams, net::CURLWork* pCURLWork );

    private:
        osl::RefPtr<net::CURLService>   m_ptrCURLService;
        /*osl::RefPtr<net::FileService>   m_ptrFileService;*/

        size_t                                     m_count;
        osl::Event                               m_event;
    };

} // end of namespace LibTest



namespace LibTest
{
	namespace
	{

		class MyEvent : public osl::Event, public osl::Object
		{
		};
		typedef osl::RefPtr<MyEvent> MyEventPtr;

        class TestDownloadFileSpeedListener : public osl::Object, public net::CURLWork::Listener/*, public net::FileService::Listener*/
        {
            osl::AtomicInt32 nSuccessCount;
            osl::AtomicInt32 nFailedCount;
        public:
            TestDownloadFileSpeedListener()
            {
                nSuccessCount = nFailedCount = 0;
            }

            H_REFERENCE_METHODS( osl::Object );
            virtual void onFinishOKT( net::CURLWork* pw )
            {
                InterlockedInc32( &nSuccessCount );
                osl::OStringStreamA log;
                log << "Success downloaded file count = " << nSuccessCount;
                H_LOG_NAME_INFO( "", log.str() );
            }

            virtual void onFinishErrorT( net::HttpErrorCode hec, const osl::StringA& errmsg, net::CURLWork* pw )
            {
                InterlockedInc32( &nFailedCount );
                osl::OStringStreamA log;
                log << "Failed downloaded file count = " << nFailedCount << ", " << errmsg;
                H_LOG_NAME_INFO( "", log.str() );
            }


            virtual void notifyOKT( void* pWorkUnit, osl::MemoryDataStream* pFileData )
            {
                InterlockedInc32( &nSuccessCount );
                osl::OStringStreamA log;
                log << "Success downloaded file count = " << nSuccessCount;
                H_LOG_NAME_INFO( "", log.str() );
            }

            virtual void notifyErrorT( void* pWorkUnit )
            {
                InterlockedInc32( &nFailedCount );
                osl::OStringStreamA log;
                log << "Failed downloaded file count = " << nFailedCount;
                H_LOG_NAME_INFO( "", log.str() );
            }
        };
        typedef osl::RefPtr<TestDownloadFileSpeedListener> TestDownloadFileSpeedListenerPtr;


        class TestonWorkingPercentage : public osl::Object, public net::CURLWork::Listener
        {
        public:
            H_REFERENCE_METHODS( osl::Object );
            virtual void onFinishOKT( net::CURLWork* pw )
            {
                
            }

            virtual void onFinishErrorT( net::HttpErrorCode hec, const osl::StringA& errmsg, net::CURLWork* pw )
            {
                
            }


            void onWorkingPercentage( net::CURLWork* pw, double fPercent ) 
            {
                osl::OStringStreamA log;
                log << "percentage=" << fPercent;
                H_LOG_NAME_INFO( "TestonWorkingPercentage::onWorkingPercentage", log.str() );
            }
        };
        typedef osl::RefPtr<TestonWorkingPercentage> TestonWorkingPercentagePtr;
	}

    

	//------------------------------------------------
// 	class MyFileServiceListener : public net::FileService::Listener, public osl::Object
// 	{
// 	public:
// 		MyFileServiceListener( osl::Event* pev ): m_pEvent( pev ) {}
// 
// 		~MyFileServiceListener()
// 		{
// 			osl::OStringStreamA str;
// 			str << "MyFileServiceListener::~MyFileServiceListener(), this=" << this;
// 			H_LOG_NAME_DEBUG( "CURLWorkListener", str.str() );
// 		}
// 
// 		osl::Set<net::CURLWork*> m_vFilesToLoad;
// 		osl::Set<net::CURLWork*> m_vFilesReturn;
// 
// 		void addFileToLoad( net::CURLWork* pFile )
// 		{
// 			m_vFilesToLoad.insert( pFile );
// 		}
// 
// 		void notifyOKT( void* pWorkUnit, osl::MemoryDataStream* pFileData )
// 		{
// 			pFileData->write( '0' );
// 			osl::OStringStreamA log;
// 			log << ( const char* )pFileData->getCache();
// 			H_LOG_NAME_INFO( "CURLTest", log.str() );
// 		}
// 
// 		void notifyErrorT( void* pWorkUnit )
// 		{
// 			H_LOG_NAME_INFO( "CURLTest", "=========error==========" );
// 		}
// 
// 		//! Object reference.
// 		H_REFERENCE_METHODS( osl::Object );
// 
// 		osl::Event* m_pEvent;
// 	};



	TCurl::TCurl()
	{
// 		osl::AsyncWorkSet* pWorkSet = new osl::AsyncWorkSet( 1 );
// 		pWorkSet->start();

		m_ptrCURLService = new net::CURLService( 4 );
		m_ptrCURLService->start();

// 		m_pFileServiceListener = new MyFileServiceListener( &m_event );
// 		m_pFileServiceListener->ref();

// 		m_ptrFileService = new net::FileService(  );
// 		m_ptrFileService->setCURLService( m_ptrCURLService.getPointer() );
// 		m_ptrFileService->setAsyncWorkSet( pWorkSet );

		m_count = 5;
	}

	TCurl::~TCurl()
	{
		//delete m_pFileServiceListener;
	}

	void TCurl::invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell )
	{
		//"test_curl --type=1(download file)|2(upload file)|3(post http)|4(outweb, down out website url)|5(cookie)|6(sample)|0(all)"
		osl::AppShell::Param* pParam = pCmd->getParam( "type" );

		if ( pParam )
		{
			osl::StringA value = pParam->strVal;
			osl::StringUtil::toLowerCase( value );

			if ( value == "0" )
			{
				testAll();
			}
			else if ( value == "1" || osl::StringUtil::startsWith( value, "download" ) )
			{
				testFileDownloader();
			}
			else if ( value == "2"  || osl::StringUtil::startsWith( value, "upload" ) )
			{
				testFileUpload();
			}
			else if ( value == "3"  || osl::StringUtil::startsWith( value, "post" ) )
			{
				testHttpPostWork();
			}
			else if ( value == "4"  || osl::StringUtil::startsWith( value, "outweb" ) )
			{
				testDownloadOuterWebSite();
			}
			else if ( value == "5"  || osl::StringUtil::startsWith( value, "cookie" ) )
			{
				osl::StringA cookie = "";
				osl::AppShell::Param* pCookie = pCmd->getParam( "cookie" );

				if ( pCookie )
				{
					cookie = pCookie->strVal;
				}

				testCookie( cookie );
			}
			else if ( value == "6"  || osl::StringUtil::startsWith( value, "sample" ) )
			{
				testCURLSample();
				testCookieSample();
			}
			else if ( value == "7"  || osl::StringUtil::startsWith( value, "filedownwork" ) )
			{
				testFileDownWork();
			}
			else if ( value == "8"  || osl::StringUtil::startsWith( value, "downurl" ) )
			{
				testDownloadWorkURL();
			}
			else if ( value == "9"  || osl::StringUtil::startsWith( value, "addheader" ) )
			{
				testAddHeader();
			}
			else if ( value == "10"  || osl::StringUtil::startsWith( value, "compress" ) )
			{
				int count = 10;
				pParam = pCmd->getParam( "times" );

				if ( pParam )
				{
					count = atoi( pParam->strVal.c_str() );

					if ( count <= 0 )
					{
						count = 10;
					}
				}

				testCompressFileUploadAndDownload( count );
            }
            else if ( value == "11"  || osl::StringUtil::startsWith( value, "headerparse" ) )
            {
                testHttpHeaderParser();
            }
            else if ( value == "12"  || osl::StringUtil::startsWith( value, "speed" ) )
            {
                testFileDownloadSpeed();
            }
            else if ( value == "13"  || osl::StringUtil::startsWith( value, "resumable" ) )
            {
                testResumableTransfer();
            }
            else if ( value == "14"  || osl::StringUtil::startsWith( value, "percentage" ) )
            {
                testonWorkingPercentage();
            }
            else if ( value == "15"  || osl::StringUtil::startsWith( value, "blockingrequest" ) )
            {
                testBlockingDoHttpRequest();
            }
            else if ( value == "16"  || osl::StringUtil::startsWith( value, "curl_post_bin_data" ) )
            {
                test_curl_post_bin_data_16();
            }
            else if ( value == "17"  || osl::StringUtil::startsWith( value, "msv" ) )
            {
                test_msv_17();
            }
            else if ( value == "18"  || osl::StringUtil::startsWith( value, "appendParameters" ) )
            {
                test_HttpPostWork_appendParameters_18();
            }
			else
			{
				//add more test case here
			}
		}
		else
		{
			processCURLAutoTest( pCmd );
			return;

		}



	}

	void TCurl::testAll()
	{
		testFileDownloader();
		testHttpPostWork();
		testDownloadOuterWebSite();
		testFileUpload();
		testCURLSample();
		testCookie( "" );
		testDownloadWorkURL();
		testAddHeader();
        testBlockingDoHttpRequest();
	}
// 
// 	net::HttpPostFile* TCurl::createHttpPostFile( Json::JSONObject* pJWorkUnit )
// 	{
// 		Json::JSONString* pJSDataFileName = pJWorkUnit->getJSONString( "datafilename" );
// 
// 		if ( !pJSDataFileName )
// 		{
// 			H_LOG_NAME_INFO( "TestCurl", "We cannot find 'datafilename' key, please check the config file contents." );
// 			return NULL;
// 		}
// 
// 		Json::JSONObject* pJParams = pJWorkUnit->getJSONObject( "paramters" );
// 
// 		if ( !pJParams )
// 		{
// 			H_LOG_NAME_INFO( "TestCurl", "We cannot find 'paramters' key, please check the config file contents." );
// 			return NULL;
// 		}
// 
// 		Json::JSONString* pJSURL = pJWorkUnit->getJSONString( "url" );
// 
// 		if ( !pJSURL )
// 		{
// 			H_LOG_NAME_INFO( "TestCurl", "We cannot find 'url' key, please check the config file contents." );
// 			return NULL;
// 		}
// 
// 		osl::MemoryDataStreamPtr ptrData = H_NEW osl::MemoryDataStream;
// 
// 		if ( !ptrData->readRawFile( pJSDataFileName->getRealValue() ) )
// 		{
// 			osl::OStringStreamA log;
// 			log << "We cannot open the data file name : " << pJSDataFileName->getRealValue() << ", please check the config file name.";
// 			H_LOG_NAME_INFO( "TestCurl", log.str() );
// 			return NULL;
// 		}
// 
// 		net::HttpPostFile* pCURLWork = H_NEW net::HttpPostFile( pJSURL->getRealValue() );
// 		pCURLWork->addSendDataItem( ptrData.getPointer() );
// 		addCURLWorkParameters( pJParams, pCURLWork );
// 		return pCURLWork;
// 	}
// 
// 	net::HttpPostWork* TCurl::createHttpPostWork( Json::JSONObject* pJWorkUnit )
// 	{
// 		Json::JSONObject* pJParams = pJWorkUnit->getJSONObject( "paramters" );
// 
// 		if ( !pJParams )
// 		{
// 			H_LOG_NAME_INFO( "TestCurl", "We cannot find 'paramters' key, please check the config file contents." );
// 			return NULL;
// 		}
// 
// 		Json::JSONString* pJSURL = pJWorkUnit->getJSONString( "url" );
// 
// 		if ( !pJSURL )
// 		{
// 			H_LOG_NAME_INFO( "TestCurl", "We cannot find 'url' key, please check the config file contents." );
// 			return NULL;
// 		}
// 
// 		net::HttpPostWork* pCURLWork = H_NEW net::HttpPostWork( pJSURL->getRealValue() );
// 		addCURLWorkParameters( pJParams, pCURLWork );
// 		return pCURLWork;
// 	}
// 
// 	net::HttpGetWork* TCurl::createHttpGetWork( Json::JSONObject* pJWorkUnit )
// 	{
// 		Json::JSONObject* pJParams = pJWorkUnit->getJSONObject( "paramters" );
// 
// 		if ( !pJParams )
// 		{
// 			H_LOG_NAME_INFO( "TestCurl", "We cannot find 'paramters' key, please check the config file contents." );
// 			return NULL;
// 		}
// 
// 		Json::JSONString* pJSURL = pJWorkUnit->getJSONString( "url" );
// 
// 		if ( !pJSURL )
// 		{
// 			H_LOG_NAME_INFO( "TestCurl", "We cannot find 'url' key, please check the config file contents." );
// 			return NULL;
// 		}
// 
// 		net::HttpGetWork* pCURLWork = H_NEW net::HttpGetWork( pJSURL->getRealValue() );
// 		addCURLWorkParameters( pJParams, pCURLWork );
// 		return pCURLWork;
// 	}
// 
// 
// 
// 	void TCurl::addCURLWorkParameters( Json::JSONObject* pJParams, net::CURLWork* pCURLWork )
// 	{
// 		const Json::JSONObject::Map& mapParamObjects = pJParams->getObjects();
// 		Json::JSONObject::Map::const_iterator it( mapParamObjects.begin() ), ite( mapParamObjects.end() );
// 
// 		for ( ; it != ite; ++it )
// 		{
// 			pCURLWork->addParameter( it->first, ( ( Json::JSONString* )( it->second.getPointer() ) )->getRealValue() );
// 		}
// 	}

	void TCurl::testFileUpload()
	{
		//upload a memory data buffer
//         {
//             osl::QUUID id( true );
//             printf( "uuid=%s\n", id.toStringA().c_str() );
//             net::HttpPostFile* pWork = new net::HttpPostFile( "http://192.168.0.43/filewebserver/post.php" );
//             pWork->addParameter( "uuid", "82af1c05-f31b-3c9d-4b18-f537083a460a" );//delete the olduuid file, and create the new file.
//             pWork->addParameter( "type", "aaaaaaa" );
//
//             osl::MemoryDataStreamPtr pFile = H_NEW osl::MemoryDataStream();
//
//             if ( !pFile->openRawFile( osl::Process::getConfDir() + "/" + "networklibconf.xml" ) )
//             {
//                 *pFile << "test file";
//             }
//
//             //dynamic_cast<net::FileUploadWork*>( pWork )->setSendDataStream( pFile );
//             pWork->addSendDataItem( pFile );
//
//             pWork->addListener( this );
//
//             m_ptrCURLService->addWorkT( pWork );
//         }

		//upload a local hard disk file to file web server
// 		{
// 			osl::QUUID id( true );
// 			printf( "uuid=%s\n", id.toStringA().c_str() );
// 			net::UploadFileWork* pWork = new net::UploadFileWork( "http://192.168.0.43/filewebserver/post.php", osl::Process::getConfDir() + "/" + "networklibconf.xml" );
// 			pWork->addParameter( "uuid", id.toStringA() );
// 			pWork->addParameter( "type", "aa/aa/aaa" );
// 			pWork->addListener( this );
// 			pWork->setResponseWithHeader( false );
// 			m_ptrCURLService->addWorkT( pWork );
// 		}
	}

	void TCurl::testFileDownloader()
	{
// 		osl::StringA strUUID = "6b210a181e0f53a251c1d93f9cd5e9ca";
// 		net::DownloadFileWork* pWork = H_NEW net::DownloadFileWork( "http://192.168.0.43/filewebserver/get.php", "aaaaaaaaaa.txt", net::CURLWork::ECM_BZIP_BEST_SPEED );
// 		pWork->addParameter( "type", "abcde" );
// 		pWork->addParameter( "uuid", strUUID.c_str() );
// 		m_ptrCURLService->addWorkT( pWork );
// 		pWork->addListener( this );

//          osl::QUUID id;
//          id.generate();
//          printf( "------------------uuid=%s\n", id.toStringA().c_str() );
//          net::HttpPostFile* pWork = new net::HttpPostFile( "http://192.168.0.43/filewebserver/post.php");
//          pWork->addParameter( "olduuid", "82af1c05-f31b-3c9d-4b18-f537083a460a" );//delete the olduuid file, and create the new file.
//          pWork->addListener( m_pFileServiceListener );
//          m_ptrCURLService->addWorkT( pWork );
//
//          m_event.wait();
//
//          for ( size_t i = 0; i < m_count; i++ )
//          {
//              osl::OStringStreamA url;
//              id.m_l64 += 1;
//              //http://releases.mozillaonline.com/pub/mozilla.org/firefox/releases/3.5.2/linux-i686/en-US/firefox-3.5.2.tar.bz2
//              url << "http://192.168.0.43/filewebserver/get.php?type=test&uuid=" << id.toStringA();
//              //url << "http://download.cnet.com/windows/most-popular/3101-20_4-0.html";
//              void* pDownloadWork;
//              m_ptrFileService->doHttpGetWorkT( pDownloadWork, m_pFileServiceListener, url.str(), 1000000 );
//
//              //pDownloadWork->getSocket()
//              m_pFileServiceListener->addFileToLoad( pDownloadWork.getPointer() );
//
//              /*if( i > 3 )
//              break;*/
//          }
//
//          while ( m_pFileServiceListener->m_vFilesToLoad.size() != m_pFileServiceListener->m_vFilesReturn.size() )
//          {
//              osl::Process::msSleep( 100 );
//          }
	}

	void TCurl::testFileDownWork()
	{


//         osl::QUUID id( true );
//         printf( "------------------uuid=%s\n", id.toStringA().c_str() );
//         net::CURLWork* pWork = new net::FileUploadWork( "http://192.168.0.43/filewebserver/post.php",
//                                                         id.toStringA(),
//                                                         "test",
//                                                         "uploadfile.txt",
//                                                         100 );
//         pWork->addParameter( "olduuid", "82af1c05-f31b-3c9d-4b18-f537083a460a" );//delete the olduuid file, and create the new file.
//         pWork->addListener( m_pFileServiceListener );
//         m_ptrCURLService->addWorkT( pWork );
//
//         m_event.wait();
//
//         osl::OStringStreamA url;
//         url << "http://192.168.0.43/filewebserver/get.php?type=test&uuid=" << id.toStringA();
//         pWork = H_NEW net::FileDownWork( url.str() );
//         pWork->addListener( m_pFileServiceListener );
//         m_ptrCURLService->addWorkT( pWork );
//
//
//         pWork = H_NEW net::FileDownWork( "http://192.168.0.43/filewebserver/get.php?type=test&uuid=a54f712209494f975e0bd98e625b98a2" );
//         pWork->addListener( m_pFileServiceListener );
//         m_ptrCURLService->addWorkT( pWork );

	}

	void TCurl::testDownloadOuterWebSite()
	{
//         osl::OStringStreamA strTip;
//         //strTip << "http://202.108.22.5";
//         strTip << "http://www.baidu.com";
//         void* pDownloadWork;
//         m_ptrFileService->doHttpGetWorkT( pDownloadWork, m_pFileServiceListener, strTip.str(), 10000 );
	}

	namespace
	{
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
							unsigned char raw16bytes[16] = { '\0' };
							md5.getRawDigest( raw16bytes );
							char vk1[128] = { '\0' };
							md5_text(vk1, raw16bytes+12, 4);
							std::cout << "Original vk=" << vk1 << " by ccweb_engine" << std::endl;
							std::cout << "new vk=" << vk;
							assert( strncmp( vk, vk1, 8) == 0 );
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
	}


	void TCurl::testHttpPostWork()
	{
		//
		{
			const char* usr = "weizili";
			const char* pwd = "english";
			const char* op  = "dump";
			const char* ver = "Ccweb_engine_v0.3";
			const char* host= "192.168.32.103";

			net::HttpPostWork* pWork = H_NEW net::HttpPostWork("http://192.168.0.181:8360/datasafe/interface_check.php");
			pWork->addParameter( "usr", usr );
			pWork->addParameter( "pwd", pwd );
			pWork->addParameter( "op",  op );
			pWork->addParameter( "host", host );
			pWork->addParameter( "ver", ver );

			char vk[32] = { '\0' };
			getVk( usr, pwd, op, host, vk );
			pWork->addParameter( "vk", vk );

			pWork->addListener( this );
			m_ptrCURLService->addWorkT( pWork );

		}

		{
// 			osl::QUUID id( true );
// 			printf( "uuid=%s\n", id.toStringA().c_str() );
// 			net::HttpPostFile* pWork = new net::HttpPostFile( "http://192.168.0.43/filewebserver/post.php" );
// 			pWork->addParameter( "uuid", id.toStringA() );//delete the olduuid file, and create the new file.
// 			pWork->addParameter( "type", "aaaaaaa" );
// 
// 			osl::MemoryDataStreamPtr pFile = H_NEW osl::MemoryDataStream();
// 
// 			if ( !pFile->openRawFile( osl::Process::getConfDir() + "/" + "networklibconf.xml" ) )
// 			{
// 				*pFile << "test file";
// 			}
// 
// 			//dynamic_cast<net::FileUploadWork*>( pWork )->setSendDataStream( pFile );
// 			pWork->addSendDataItem( pFile );
// 
// 			pWork->addListener( this );
// 
// 			m_ptrCURLService->addWorkT( pWork );
		}
//          {
//              osl::StringA url = "http://192.168.0.43/filewebserver/post.php";
//              net::HttpPostWork *pWork = new net::HttpPostWork( url, 10 );
//              pWork->addParameter( "username", "bajie" );
//              pWork->addParameter( "password", "123456" );
//              pWork->addParameter( "other1", "123456" );
//              pWork->addParameter( "other2", "" );
//              pWork->addParameter( "other3", "123456" );
//              pWork->addListener( this );
//              m_ptrCURLService->addWorkT( pWork );
//          }

		if(1)
		{
			//osl::StringA url = "http://202.150.215.251/logicwebserver/inventory/upload.do";
// 			osl::StringA url = "http://192.168.0.44/logicwebserver/inventory/upload.do";
// 			net::HttpPostWork *pWork = H_NEW net::HttpPostWork( url );
//             pWork->setTimeOut( 5 );
// 			osl::StringA value = "{\"dirid\":\"00000000-0000-0000-0000-000000002b67\",\"name\":\"testuploaddir\",\"parentid\":true,\"userid\":true}";
// 			pWork->addParameter( "Json", value );
// 			pWork->addParameter( "username", "bajie" );
// 			pWork->addParameter( "password", "123456" );
// 			pWork->addListener( this );
// 			m_ptrCURLService->addWorkT( pWork );
		}
	}

	void TCurl::onFinishOKT( net::CURLWork* pw )
	{
		static size_t i = 0;
		osl::MemoryDataStream* pRecvData = pw->getRecvDataStream();
		pRecvData->write( '\0' );
		pRecvData->setSize( pRecvData->getSize() - 1 );
		osl::OStringStreamA log;
		log << "server response data: " << i++ << "\t" << ( char* )pRecvData->getCache() << std::endl;
		std::cout << log.str();

// 		if ( !dynamic_cast<net::UploadFileWork*>( pw ) && !dynamic_cast<net::DownloadFileWork*>( pw ) )
// 		{
// 			pRecvData->write( '\0' );
// 			pRecvData->setSize( pRecvData->getSize() - 1 );
// 			osl::OStringStreamA log;
// 			log << "server response data: " << i++ << "\t" << ( char* )pRecvData->getCache() << std::endl;
// 			H_LOG_NAME_INFO( "TCurl", log.str() );
// 		}

		osl::Object* pUserData = pw->getObjectUserData();

		if ( pUserData )
		{
// 			if ( dynamic_cast<net::UploadFileWork*>( pw ) )
// 			{
// 				MyEvent* pev = dynamic_cast<MyEvent*>( pUserData );
// 
// 				if ( pev )
// 				{
// 					pev->signal();
// 				}
// 				else
// 				{
// 					H_ASSERT( false && "upload file work getusedata failed." );
// 				}
// 			}
// 			else if ( dynamic_cast<net::DownloadFileWork*>( pw ) )
// 			{
// 				static size_t nDownSuccessCount = 0;
// 				osl::OStringStreamA log;
// 				log << "nDownSuccessCount=" << ++nDownSuccessCount << std::endl;
// 				H_LOG_NAME_INFO( "TCurl", log.str() );
// 
// 				osl::MemoryDataStream* pSrcData = dynamic_cast<osl::MemoryDataStream*>( pUserData );
// 
// 				if ( pSrcData )
// 				{
// 					H_ASSERT( pSrcData->getSize() == pRecvData->getSize() );
// 
// 					for ( osl::u32 i = 0; i < pRecvData->getSize(); ++i )
// 					{
// 						H_ASSERT( pSrcData->charAt( i ) == pRecvData->charAt( i ) );
// 					}
// 				}
// 				else
// 				{
// 					H_ASSERT( false && "download file work getusedata failed." );
// 				}
// 			}
// 			else
// 			{
// 				H_ASSERT( false && "cound not come here." );
// 			}
		}
	}

	void TCurl::onFinishErrorT( net::HttpErrorCode hec, const osl::StringA& errmsg, net::CURLWork* pw )
	{
		static int i = 0;
		osl::OStringStreamA log;
		log << "failed. No." << ++i << "\thec=" << (int)hec << ", errmsg:" << errmsg << " ================" << std::endl;
		H_LOG_NAME_INFO( "TCurl", log.str() );

		osl::Object* pUserData = pw->getObjectUserData();

		if ( pUserData )
		{
			// 			if ( dynamic_cast<net::UploadFileWork*>( pw ) )
			// 			{
			// 				MyEvent* pev = dynamic_cast<MyEvent*>( pUserData );
			// 
			// 				if ( pev )
			// 				{
			// 					pev->signal();
			// 				}
			// 			}
			// 			else if ( dynamic_cast<net::DownloadFileWork*>( pw ) )
			// 			{
			// 				static size_t nDownFailedCount = 0;
			// 				osl::OStringStreamA log;
			// 				log << "nDownSuccessCount=" << ++nDownFailedCount << std::endl;
			// 				H_LOG_NAME_INFO( "TCurl", log.str() );
			// 			}
		}
	}

	void TCurl::testCookie( const osl::StringA& cookie )
	{
		osl::StringA url = "http://192.168.0.44/logicwebserver/community/list.do";
		//m_ptrFileService->doHttpGetWorkT( pHandle, m_pFileServiceListener, url.c_str() );
	}
	void TCurl::testAddHeader()
	{
		net::HttpPostWork* pWork = H_NEW net::HttpPostWork( "http://192.168.0.43/filewebserver/post.php" );
		pWork->addHeader( "content-type:text/xml,text/plain" );
		pWork->addParameter( "type", "patch_desc" );
		m_ptrCURLService->addWorkT( pWork );
	}

// 	void TCurl::onFinishOKT( net::CURLWork* pw )
// 	{
// 		static size_t i = 0;
// 		osl::MemoryDataStream* pRecvData = pw->getRecvDataStream();
//
// 		osl::Object* pUserData = pw->getHObjectUserData();
//
// 		if ( pUserData )
// 		{
// 			if ( dynamic_cast<net::UploadFileWork*>( pw ) )
// 			{
// 				MyEvent* pev = dynamic_cast<MyEvent*>( pUserData );
//
// 				if ( pev )
// 				{
// 					pev->signal();
// 				}
// 			}
// 			else if ( dynamic_cast<net::DownloadFileWork*>( pw ) )
// 			{
// 				static size_t nDownFailedCount = 0;
// 				osl::OStringStreamA log;
// 				log << "nDownSuccessCount=" << ++nDownFailedCount << std::endl;
// 				H_LOG_NAME_INFO( "TCurl", log.str() );
// 			}
// 		}
// 	}
//
// 	osl::Object* pUserData = pw->getHObjectUserData();
//
// 	if ( pUserData )
// 	{
// 		if ( dynamic_cast<net::UploadFileWork*>( pw ) )
// 		{
// 			MyEvent* pev = dynamic_cast<MyEvent*>( pUserData );
//
// 			if ( pev )
// 			{
// 				pev->signal();
// 			}
// 			else
// 			{
// 				H_ASSERT( false && "upload file work getusedata failed." );
// 			}
// 		}
// 		else if ( dynamic_cast<net::DownloadFileWork*>( pw ) )
// 		{
// 			static size_t nDownSuccessCount = 0;
// 			osl::OStringStreamA log;
// 			log << "nDownSuccessCount=" << ++nDownSuccessCount << std::endl;
// 			H_LOG_NAME_INFO( "TCurl", log.str() );
//
// 			osl::MemoryDataStream* pSrcData = dynamic_cast<osl::MemoryDataStream*>( pUserData );
//
// 			if ( pSrcData )
// 			{
// 				H_ASSERT( pSrcData->getSize() == pRecvData->getSize() );
//
// 				for ( osl::u32 i = 0; i < pRecvData->getSize(); ++i )
// 				{
// 					H_ASSERT( pSrcData->charAt( i ) == pRecvData->charAt( i ) );
// 				}
// 			}
// 			else
// 			{
// 				H_ASSERT( false && "download file work getusedata failed." );
// 			}
// 		}
// 		else
// 		{
// 			H_ASSERT( false && "cound not come here." );
// 		}
// 	}
// }

	

	void TCurl::processCURLAutoTest( osl::AppShell::Command* pCmd )
	{
        osl::StringA strConfigFileName = osl::Process::getBinDir(true) + "curlconf.json";
		osl::AppShell::Param* pParam = pCmd->getParam( "cfgfile" );

		if ( pParam )
		{
			strConfigFileName = pParam->strVal;
			H_LOG_NAME_INFO( "TestCurl", "You don't input the config file name, we use the default config file name : 'curlconf.json'" );
		}


		osl::MemoryDataStream ds;

		if ( !ds.readRawFile( strConfigFileName ) )
		{
			H_LOG_NAME_INFO( "TestCurl", "We cannot open the config file name, please check the config file name." );
			return;
		}

// 		Json::JSONObject joConfig;
// 		joConfig.parse( ( const char* )ds.getCache(), ds.getSize() );
// 		osl::s32 nFailedRetryTimes = ( osl::s32 )joConfig.getInteger( "failedretrytimes" );
// 
// 		if ( nFailedRetryTimes > 0 )
// 		{
// 			m_ptrFileService->setMaxNetError( ( size_t )nFailedRetryTimes );
// 		}
// 
// 		if ( nFailedRetryTimes > 0 )
// 		{
// 			m_ptrFileService->setMaxNetError( ( size_t )nFailedRetryTimes );
// 		}
// 
// 		Json::JSONArray* pWorksArray = joConfig.getJSONArray( "CURLWorks" );
// 
// 		if ( !pWorksArray )
// 		{
// 			H_LOG_NAME_INFO( "TestCurl", "We cannot find 'CURLWorks' key, please check the config file contents." );
// 			return;
// 		}
// 
// 		for ( size_t i = 0; i < pWorksArray->size(); ++i )
// 		{
// 			Json::JSONObject* pJWorkUnit = pWorksArray->getJSONObject( i );
// 
// 			if ( !pJWorkUnit )
// 			{
// 				continue;
// 			}
// 
// 			osl::u32 loopnumber = 1;
// 			Json::JSONInteger* pJILoopNum = pJWorkUnit->getJSONInteger( "loopnumber" );
// 
// 			if ( pJILoopNum )
// 			{
// 				loopnumber = pJILoopNum->getRealValue();
// 
// 				if ( loopnumber <= 0 )
// 				{
// 					loopnumber = 1;
// 				}
// 			}
// 
// 			for ( size_t j = 0; j < loopnumber; j++ )
// 			{
// 				Json::JSONString* pJSWorkName = pJWorkUnit->getJSONString( "curlworkname" );
// 
// 				if ( !pJSWorkName )
// 				{
// 					H_LOG_NAME_INFO( "TestCurl", "We cannot find 'curlworkname' key, please check the config file contents." );
// 					continue;
// 				}
// 
// 				void* pHandle = NULL;
// 				osl::StringA strWorkName = pJSWorkName->getRealValue();
// 
// 				if ( strWorkName == "HttpPostFile" )
// 				{
// 					net::HttpPostFile* pWork = createHttpPostFile( pJWorkUnit );
// 
// 					if ( pWork )
// 					{
// 						m_ptrFileService->doHttpPostFileT( pHandle, m_pFileServiceListener, pWork );
// 					}
// 				}
// 				else if ( strWorkName == "HttpPostWork" )
// 				{
// 					net::HttpPostWork* pWork = createHttpPostWork( pJWorkUnit );
// 
// 					if ( pWork )
// 					{
// 						m_ptrFileService->doHttpPostWorkT( pHandle, m_pFileServiceListener, pWork );
// 					}
// 
// 				}
// 				else if ( strWorkName == "HttpGetWork" )
// 				{
// 					net::HttpGetWork* pWork = createHttpGetWork( pJWorkUnit );
// 
// 					if ( pWork )
// 					{
// 						m_ptrFileService->doHttpGetWorkT( pHandle, m_pFileServiceListener, pWork );
// 					}
// 
// 				}
// 			}
// 		}
	}


	void TCurl::testCompressFileUploadAndDownload( int ncount/* = 1000 */ )
	{


		osl::StringA strFileName = osl::Process::getConfDir() + "/" + "networklibconf.xml";
		osl::MemoryDataStreamPtr pSrcData = H_NEW osl::MemoryDataStream( 10240 );
		pSrcData->readRawFile( strFileName );
		//const char* ptype = "zipfiles_aaaaaaaaaaa";


		for ( int i = 0; i < ncount; i++ )
		{
			MyEventPtr pEvent = H_NEW MyEvent;
// 			osl::QUUID id( true );
// 
// 			{
// 				net::UploadFileWork* pWork = new net::UploadFileWork( "http://192.168.0.43/filewebserver/post.php", strFileName, net::CURLWork::ECM_BZIP_BEST_SPEED );
// 				pWork->addParameter( "uuid", id.toStringA() );
// 				pWork->addParameter( "type", ptype );
// 				pWork->addListener( this );
// 				pWork->setHObjectUserData( pEvent );
// 				m_ptrCURLService->addWorkT( pWork );
// 			}
// 
// 			pEvent->wait();//wait UploadFileWork is done.
// 
// 			{
// 				net::DownloadFileWork* pWork = H_NEW net::DownloadFileWork( "http://192.168.0.43/filewebserver/get.php", "aaaaaaaaaa.txt", net::CURLWork::ECM_BZIP_BEST_SPEED );
//                 pWork->setTimeOut( 5 );
// 				pWork->addParameter( "type", ptype );
// 				pWork->addParameter( "uuid", id.toStringA().c_str() );
// 				pWork->setHObjectUserData( pSrcData );//used for compare the download result
// 				pWork->addListener( this );
// 				m_ptrCURLService->addWorkT( pWork );
// 			}
// 
// 			if ( i % 30 == 0 )
// 			{
// 				osl::Process::msSleep( 5000 );
// 			}
		} // end of for
	}
	void TCurl::testHttpHeaderParser()
	{
// 		osl::StringA strTestDataDirPath = osl::Process::getBinDir() + "/../testdata/hlibtest_data/httphead/";
// 		osl::StringAList files;
// 		osl::Util::getFiles( strTestDataDirPath, files, false, "*.txt" );
// 		osl::StringAList::iterator it( files.begin() ), ite( files.end() );
// 
// 		for ( ; it != ite; ++it )
// 		{
// 			osl::MemoryDataStream ds;
// 			ds.readRawFile( *it );
// 			net::HttpHeaderParser parser;
// 			parser.parse( ( const char* )ds.getCache(), ds.getSize() );
// 			osl::StringA strFileContent( ( const char* )ds.getCache(), ds.getSize() );
// 
// 			const osl::StringAStringAMap& mapData = parser.getMetaDataMap();
// 			osl::StringAStringAMap::const_iterator itm( mapData.begin() ), itme( mapData.end() );
// 
// 			for ( ; itm != itme; ++itm )
// 			{
// 				size_t index = strFileContent.find( itm->first );
// 				H_ASSERT( index != osl::StringA::npos );
// 				H_ASSERT( strFileContent[index + itm->first.size() ] == ':' );
// 
// 				index = strFileContent.find( itm->second );
// 				H_ASSERT( index != osl::StringA::npos );
// 			}
// 		}
	}

    void TCurl::testFileDownloadSpeed()
    {
//         }
    }




    void TCurl::testonWorkingPercentage()
    {
    }

    void TCurl::testBlockingDoHttpRequest()
    {

        //test HttpPostWork
        {
            const char* usr = "weizili";
            const char* pwd = "english";
            const char* op  = "dump";
            const char* ver = "Ccweb_engine_v0.3";
            const char* host= "192.168.32.103";

            net::HttpPostWorkPtr pWork = H_NEW net::HttpPostWork("http://192.168.0.181:8360/datasafe/interface_check.php");
            pWork->addParameter( "usr", usr );
            pWork->addParameter( "pwd", pwd );
            pWork->addParameter( "op",  op );
            pWork->addParameter( "host", host );
            pWork->addParameter( "ver", ver );
            pWork->setTimeOut( 30 );

            char vk[32] = { '\0' };
            getVk( usr, pwd, op, host, vk );
            pWork->addParameter( "vk", vk );

            pWork->setBlockingDoHttpRequest( true );
            pWork->doHttpBlockingRequest();

            osl::MemoryDataStream* pdata = pWork->getRecvDataStream();
            pdata->toText();
        }


        {
            for ( int i = 0; i < 10; ++i )
            {
                net::HttpGetWorkPtr pWork = H_NEW net::HttpGetWork("http://log4.safe.bjt.qihoo.net:8360/midlogs/cols.php?op=interface");
                pWork->addParameter( "op", "interface" );
                pWork->setTimeOut( 5 );


                pWork->setBlockingDoHttpRequest( true );
                pWork->doHttpBlockingRequest();

                osl::MemoryDataStream* pdata = pWork->getRecvDataStream();
                pdata->toText();

                std::cout << (char*)pdata->getCache() << "\n\n\n\n====================\n====================\n====================\n====================\n\n\n\n\n";
            }


            for ( int i = 0; i < 10; ++i )
            {
                net::HttpGetWork pWork("http://log4.safe.bjt.qihoo.net:8360/midlogs/rules.php");
                pWork.setTimeOut( 5 );

                pWork.setBlockingDoHttpRequest( true );
                pWork.doHttpBlockingRequest();

                osl::MemoryDataStream* pdata = pWork.getRecvDataStream();
                pdata->toText();

                std::cout << (char*)pdata->getCache() << "\n\n\n\n====================\n====================\n====================\n====================\n\n\n\n\n";
            }
            
        }





    }

    void TCurl::test_msv_17()
    {
        {
            osl::MemoryDataStream ds;
            if ( !ds.readRawFile("/home/weizili/tmp/msvbin.dat") )
            {
                return;
            }

            const char* url = "http://bole.kill.corp.qihoo.net:8012/msvquery";
            const char* key = "micropattern_bole_query";
            
            for ( int i = 0; i < 1000000000; ++i )
            {
                net::HttpPostFilePtr pWork = new net::HttpPostFile( url );
                pWork->setTimeOut( 5 );
                pWork->addParameter( key, ds.getCache(), ds.getSize() );
                pWork->setBlockingDoHttpRequest( true );
                pWork->doHttpBlockingRequest();
                osl::MemoryDataStream* pdata = pWork->getRecvDataStream();
                pdata->toText();
                std::cout << "i=" << i << std::endl;
            }
        }
    }

    void TCurl::test_HttpPostWork_appendParameters_18()
    {
        {
            net::HttpPostWorkPtr pWork = H_NEW net::HttpPostWork("http://192.168.0.181:8360/datasafe/interface_check.php");
            osl::StringA content = "abcdefgljasldjfalskdjf;asldfjasdlfkjasldjfasdjfahsdfahsdf";
            pWork->appendParameters( content );
            pWork->setBlockingDoHttpRequest( true );
            pWork->doHttpBlockingRequest();

            osl::MemoryDataStream* pdata = pWork->getRecvDataStream();
            pdata->toText();
        }

        {
            net::HttpPostWorkPtr pWork = H_NEW net::HttpPostWork("http://192.168.0.181:8360/datasafe/interface_check.php");
            osl::StringA content = "abcdefgljasldjfalskdjf;asldfjasdlfkjasldjfasdjfahsdfahsdf";
            pWork->setRawHttpBodyContent( content );
            pWork->setBlockingDoHttpRequest( true );
            pWork->doHttpBlockingRequest();

            osl::MemoryDataStream* pdata = pWork->getRecvDataStream();
            pdata->toText();
        }

        {
            net::HttpPostWorkPtr pWork = H_NEW net::HttpPostWork("http://build4.kill.corp.qihoo.net:8013/scan/online/avirascaner");
            osl::StringA content = "abcdefgljasldjfalskdjf;asldfjasdlfkjasldjfasdjfahsdfahsdf";
            pWork->setRawHttpBodyContent( content );
            pWork->setBlockingDoHttpRequest( true );
            bool ok = pWork->doHttpBlockingRequest();
            if ( !ok )
            {
                std::cout << "doHttpBlockingRequest failed" << std::endl;
            }
            else
            {
                osl::MemoryDataStream* pdata = pWork->getRecvDataStream();
                pdata->toText();
                std::cout << (char*)pdata->getCache() << std::endl;
            }
        }

        {
            net::HttpPostWorkPtr pWork = H_NEW net::HttpPostWork("http://build4.kill.corp.qihoo.net:8013/scan/online/bdscaner");
            osl::StringA content = "abcdefgljasldjfalskdjf;asldfjasdlfkjasldjfasdjfahsdfahsdf";
            pWork->setRawHttpBodyContent( content );
            pWork->setBlockingDoHttpRequest( true );
            bool ok = pWork->doHttpBlockingRequest();
            if ( !ok )
            {
                std::cout << "doHttpBlockingRequest failed" << std::endl;
            }
            else
            {
                osl::MemoryDataStream* pdata = pWork->getRecvDataStream();
                pdata->toText();
                std::cout << (char*)pdata->getCache() << std::endl;
            }
        }

    }

    void TCurl::test_curl_post_bin_data_16()
    {
        {
            osl::MemoryDataStream ds;
            if ( !ds.readRawFile("e:/p2sp_user_bin.dat") )
            {
                return;
            }

            CURL *curl = NULL;
            CURLcode res = CURLE_OK;
            struct curl_httppost* formpost = NULL;
            struct curl_httppost* lastformpost = NULL;

            curl = curl_easy_init();
            curl_easy_setopt( curl, CURLOPT_URL, "http://192.168.0.185:8011/urlquery" );

            CURLFORMcode fcode = ::curl_formadd( &formpost,
                &lastformpost,
                CURLFORM_COPYNAME, "p2sp_request_no_CURLFORM_CONTENTSLENGTH",
                CURLFORM_COPYCONTENTS, ds.getCache(),
                CURLFORM_END );

            if(  fcode != CURL_FORMADD_OK )
            {
                return;
            }

            fcode = ::curl_formadd( &formpost,
                &lastformpost,
                CURLFORM_COPYNAME, "p2sp_request",
                CURLFORM_COPYCONTENTS, ds.getCache(),
                CURLFORM_CONTENTSLENGTH, (long)ds.getSize(),
                CURLFORM_END );

            if(  fcode != CURL_FORMADD_OK )
            {
                return;
            }

            curl_easy_setopt( curl, CURLOPT_HTTPPOST, formpost );


            res = curl_easy_perform( curl );
            /* always cleanup */
            curl_easy_cleanup( curl );
        }

        test_HttpPostWork_appendParameters_18();

    }

    void TCurl::testResumableTransfer()
    {
        CURL *curl = NULL;
        CURLcode res = CURLE_OK;

        curl = curl_easy_init();
        curl_easy_setopt( curl, CURLOPT_URL, "http://192.168.0.43/fws/a.txt" );
        std::cout << "\n=========================================\ncurl_easy_setopt( curl, CURLOPT_RANGE, \"0-\" );\n" << std::endl;
        curl_easy_setopt( curl, CURLOPT_RANGE, "0-" );//略过前面0字节，从第1字节开始的所有数据都会下载下来。偏移地址从0开始。实际上就是全部下载下来。
        res = curl_easy_perform( curl );
        std::cout << "\n\n\n\n\n\n";

        curl = curl_easy_init();
        curl_easy_setopt( curl, CURLOPT_URL, "http://192.168.0.43/fws/a.txt" );
        std::cout << "\n=========================================\ncurl_easy_setopt( curl, CURLOPT_RANGE, \"5-\" );\n" << std::endl;
        curl_easy_setopt( curl, CURLOPT_RANGE, "5-" );// [5 - oo) 略过前面5字节，从第6字节开始的所有数据都会下载下来。偏移地址从0开始
        res = curl_easy_perform( curl );
        std::cout << "\n\n\n\n\n\n";


        curl = curl_easy_init();
        curl_easy_setopt( curl, CURLOPT_URL, "http://192.168.0.43/fws/a.txt" );
        std::cout << "\n=========================================\ncurl_easy_setopt( curl, CURLOPT_RANGE, \"5-10\" );\n" << std::endl;
        curl_easy_setopt( curl, CURLOPT_RANGE, "5-10" ); // [5,10]之间的数据（共6字节）的都会下载下来。偏移地址从0开始
        res = curl_easy_perform( curl );
        std::cout << "\n\n\n\n\n\n";

        /* always cleanup */
        curl_easy_cleanup( curl );
    }


	void TCurl::testCURLSample()
	{

		CURL *curl = NULL;
		CURLcode res;

		curl_easy_setopt( curl, CURLOPT_URL, "http://www.sina.com.cn" );
		res = curl_easy_perform( curl );

		std::cout << "\n\n\n\n\n\n";

		for ( int i = 0; i < 20; i++ )
		{
			std::cout << "=========================================================";
		}

		std::cout << "\n\n\n\n\n\n";


		curl_easy_setopt( curl, CURLOPT_URL, "http://www.baidu.com" );
		res = curl_easy_perform( curl );
		curl = curl_easy_init();
		std::cout << "\n\n\n\n\n\n";

		for ( int i = 0; i < 20; i++ )
		{
			std::cout << "=========================================================";
		}

		std::cout << "\n\n\n\n\n\n";


		curl_easy_setopt( curl, CURLOPT_URL, "http://www.sina.com.cn" );
		res = curl_easy_perform( curl );

		if ( !curl )
		{
			return;
		}

		std::cout << "\n\n\n\n\n\n";

		for ( int i = 0; i < 20; i++ )
		{
			std::cout << "=========================================================";
		}

		std::cout << "\n\n\n\n\n\n";


		curl_easy_setopt( curl, CURLOPT_URL, "http://www.163.com" );
		res = curl_easy_perform( curl );

		std::cout << "\n\n\n\n\n\n";

		for ( int i = 0; i < 20; i++ )
		{
			std::cout << "=========================================================";
			std::cout << "\n\n\n\n\n\n";


			curl_easy_setopt( curl, CURLOPT_URL, "http://www.baidu.com" );
			res = curl_easy_perform( curl );

			std::cout << "\n\n\n\n\n\n";

			for ( int u = 0; u < 20; u++ )
			{
				std::cout << "=========================================================";
			}

			std::cout << "\n\n\n\n\n\n";


			curl_easy_setopt( curl, CURLOPT_URL, "http://www.sina.com.cn" );
			res = curl_easy_perform( curl );

			std::cout << "\n\n\n\n\n\n";

			for ( int u = 0; u < 20; u++ )
			{
				std::cout << "=========================================================";
			}

			std::cout << "\n\n\n\n\n\n";
		}

	}

	void TCurl::printCookies( void * curl )
	{
		CURLcode res;
		struct curl_slist *cookies;
		struct curl_slist *nc;
		int i;

		printf( "Cookies, curl knows:\n" );
		res = curl_easy_getinfo( curl, CURLINFO_COOKIELIST, &cookies );

		if ( res != CURLE_OK )
		{
			fprintf( stderr, "Curl curl_easy_getinfo failed: %s\n", curl_easy_strerror( res ) );
			return;
		}

		nc = cookies, i = 1;

		while ( nc )
		{
			printf( "[%d]: %s\n", i, nc->data );
			nc = nc->next;
			i++;
		}

		if ( i == 1 )
		{
			printf( "(none)\n" );
		}

		curl_slist_free_all( cookies );
	}

	void TCurl::testCookieSample()
	{
		CURL *curl;
		CURLcode res;

		curl_global_init( CURL_GLOBAL_ALL );
		curl = curl_easy_init();

		if ( curl )
		{
			char nline[256];

			curl_easy_setopt( curl, CURLOPT_URL, "http://www.google.com/" ); /* google.com sets "PREF" cookie */
			curl_easy_setopt( curl, CURLOPT_VERBOSE, 1L );
			curl_easy_setopt( curl, CURLOPT_COOKIEFILE, "" ); /* just to start the cookie engine */
			res = curl_easy_perform( curl );

			if ( res != CURLE_OK )
			{
				fprintf( stderr, "Curl perform failed: %s\n", curl_easy_strerror( res ) );
				return;
			}

			printCookies( curl );

			printf( "Erasing curl's knowledge of cookies!\n" );
			curl_easy_setopt( curl, CURLOPT_COOKIELIST, "ALL" );

			printCookies( curl );

			printf( "-----------------------------------------------\n"
			        "Setting a cookie \"PREF\" via cookie interface:\n" );

			/* Netscape format cookie */
			snprintf( nline, sizeof( nline ), "%s\t%s\t%s\t%s\t%lu\t%s\t%s",
			          ".google.com", "TRUE", "/", "FALSE", time( NULL ) + 31337, "PREF", "hello google, i like you very much!" );
			res = curl_easy_setopt( curl, CURLOPT_COOKIELIST, nline );

			if ( res != CURLE_OK )
			{
				fprintf( stderr, "Curl curl_easy_setopt failed: %s\n", curl_easy_strerror( res ) );
				return;
			}

			/* HTTP-header style cookie */
			snprintf( nline, sizeof( nline ),
			          "Set-Cookie: OLD_PREF=3d141414bf4209321; "
			          "expires=Sun, 17-Jan-2038 19:14:07 GMT; path=/; domain=.google.com" );
			res = curl_easy_setopt( curl, CURLOPT_COOKIELIST, nline );

			if ( res != CURLE_OK )
			{
				fprintf( stderr, "Curl curl_easy_setopt failed: %s\n", curl_easy_strerror( res ) );
				return;
			}

			printCookies( curl );

			res = curl_easy_perform( curl );

			if ( res != CURLE_OK )
			{
				fprintf( stderr, "Curl perform failed: %s\n", curl_easy_strerror( res ) );
				return;
			}
		}
		else
		{
			fprintf( stderr, "Curl init failed!\n" );
			return;
		}

		curl_global_cleanup();
	}

	//------------------------------------------------------------
	void TCurl::testDownloadWorkURL()
	{
	}


}

CREATE_FUNCTION( TCurl );
