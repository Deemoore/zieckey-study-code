#include "libtest/include/inner_pre.h"
#include "osl/include/base64.h"
#include "libtest/include/test_object.h"
#include "osl/include/scoped_mem.h"

namespace LibTest
{
	class TBase64 : public ITestObject
	{
	public:

		virtual const char* getCommand()
		{
			return "test_base64";
		}

		virtual const char* getDesc()
		{
			return "test_base64 --in=input.file.name --out=encoded.output.file.name";
		}

		virtual void invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell );

		void testAll();

	private:
		bool testBase64( const osl::StringA& infilename, const osl::StringA& outfilename );
		void testEncode( const osl::StringA& src );
		void testDecode( const osl::StringA& src );
		void test3();
		void test4();
		void testEfficiency();
	};


    void TBase64::invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell )
    {
        //"test_base64 --in=input.file.name --out=encoded.output.file.name"
		osl::StringA infilename  = osl::Process::getBinDir( false ) + "/../data/libtestdata/qoslib/base64/base64.test.inputfile.txt";
		osl::StringA outfilename = osl::Process::getBinDir( false ) + "/../data/libtestdata/qoslib/base64/outputfile.txt";


        osl::AppShell::Param* pParam = pCmd->getParam( "in" );

        if ( pParam )
        {
            infilename = pParam->strVal;
        }

        pParam = pCmd->getParam( "out" );

        if ( pParam )
        {
            outfilename = pParam->strVal;
        }

        if ( !testBase64( infilename, outfilename ) )
        {
            std::cout << "please enter the right input file name.\n";
        }

		testAll();
    }

    void TBase64::testAll()
	{
		testEncode( "ABC" );
		testEncode( "AB" );
		testEncode( "A" );
		testEncode( "ABCD" );
		testEncode( "ABCDE" );
		testEncode( "ABCDEF" );
		testEncode( "ABCDEFG" );

		testDecode( "ABC" );
		testDecode( "AB" );
		testDecode( "A" );
		testDecode( "ABCD" );
		testDecode( "ABCDE" );
		testDecode( "ABCDEF" );
		testDecode( "ABCDEFG" );
        testDecode( "ABdasdfasd" );
        testDecode( "ABCDfasdfaafsdfadsfweasd" );
        testDecode( "'k" );
        testDecode( "ABC'D" );
        test3();
		test4();
        testEfficiency();

        osl::StringA infilename  = osl::Process::getBinDir( false ) + "/../data/libtestdata/qoslib/base64/base64.test.inputfile.txt";
        osl::StringA outfilename = osl::Process::getBinDir( false ) + "/../data/libtestdata/qoslib/base64/outputfile.txt";

        if ( !testBase64( infilename, outfilename ) )
        {
            std::cout << "please enter the right input file name.\n";
        }


		std::cout << "test OK!" << std::endl;
    }

    bool TBase64::testBase64( const osl::StringA& infilename, const osl::StringA& outfilename )
    {
        osl::StringA strDecodedFileName = "decoded.txt";

        {
            osl::Base64::encode( infilename.c_str(), outfilename.c_str() );
            osl::Base64::decode( outfilename.c_str(), strDecodedFileName.c_str() );
        }

        {
            osl::MemoryDataStream inSrcData;

            if ( !inSrcData.readRawFile( infilename ) )
            {
                return false;
            }

            osl::MemoryDataStream outEncodedData;
            H_ASSERT( osl::Base64::encode( inSrcData, outEncodedData ) );
            osl::MemoryDataStream sysEncodedData;
            sysEncodedData.readRawFile( outfilename );
            H_ASSERT( sysEncodedData.getSize() == outEncodedData.getSize() );

            for ( osl::u32 i = 0; i < outEncodedData.getSize(); i++ )
            {
                H_ASSERT( sysEncodedData.charAt( i ) == outEncodedData.charAt( i ) );
            }


            //compare the result
            osl::MemoryDataStream outDecodedData;
            H_ASSERT( osl::Base64::decode( outEncodedData, outDecodedData ) );
            H_ASSERT( outDecodedData.getSize() == inSrcData.getSize() );

            for ( osl::u32 i = 0; i < inSrcData.getSize(); i++ )
            {
                H_ASSERT( inSrcData.charAt( i ) == outDecodedData.charAt( i ) );
            }
        }



        return true;
    }



    //------------------------------------------------------------
    void TBase64::testEncode( const osl::StringA& src )
    {
        const char* sourceFileName = "sourceFileName.tmp";
        osl::MemoryDataStream myEncodedData;
        osl::MemoryDataStream sysEncodedData;

        osl::MemoryDataStream ds;
        ds.write( src.c_str(), src.size() );
        ds.saveToFile( sourceFileName );

		
        osl::Base64::encode( sourceFileName, sysEncodedData );    //开源人士写的编码
        osl::Base64::encode( src, myEncodedData );                //自己写的编码

		//另一个自己写的
		size_t encodelen = myEncodedData.getSize();
		osl::ScopedMem pencoded( encodelen );
		H_ASSERT( osl::Base64::encode( src.c_str(), src.length(), pencoded.get(), encodelen ) );
        H_ASSERT( osl::Base64::getEncodedBufLen(src.length()) >= encodelen );

        //验证两者是否一致
        H_ASSERT( sysEncodedData.getSize() == myEncodedData.getSize()  );
		H_ASSERT( encodelen == myEncodedData.getSize() );

        for ( osl::u32 i = 0; i < sysEncodedData.getSize(); i++ )
        {
            H_ASSERT( sysEncodedData.charAt( i ) == myEncodedData.charAt( i ) );
			H_ASSERT( sysEncodedData.charAt( i ) == pencoded.get()[i] );
        }
    }


    //------------------------------------------------------------
    void TBase64::testDecode( const osl::StringA& src )
    {
        const char* sourceFileName  = "sourceFileName.tmp";
        const char* encodedFileName = "encodedFileName.tmp";
        const char* decodedFileName = "decodedFileName.tmp";
        osl::MemoryDataStream myEncodedData;
        osl::MemoryDataStream sysEncodedData;

        osl::MemoryDataStream myDecodedData;
        osl::MemoryDataStream sysDecodedData;

        osl::MemoryDataStream ds;
        ds.write( src.c_str(), src.size() );
        ds.saveToFile( sourceFileName );
        osl::Base64::encode( sourceFileName, sysEncodedData ); //开源人写的encode
        sysEncodedData.saveToFile( encodedFileName );
        osl::Base64::decode( encodedFileName, decodedFileName );//开源人写的decode
        sysDecodedData.readRawFile( decodedFileName );

        //验证开源人士写的decode
        H_ASSERT( sysDecodedData.getSize() == src.size() );

        for ( osl::u32 i = 0; i < sysDecodedData.getSize(); i++ )
        {
            H_ASSERT( sysDecodedData.charAt( i ) == src[i] );
        }

		//自己的解码程序2
		size_t decodedlen = sysDecodedData.getSize() + 3;
		osl::ScopedMem pdecode( decodedlen );
		H_ASSERT( osl::Base64::decode( sysEncodedData.getCache(), sysEncodedData.getSize(), pdecode.get(), decodedlen ) );
		H_ASSERT( sysDecodedData.getSize() == decodedlen );
        H_ASSERT( osl::Base64::getDecodedBufLen(sysEncodedData.getSize()) >= decodedlen );
        

        //自己的解码程序2
        H_ASSERT( osl::Base64::decode( sysEncodedData, myDecodedData ) );
        //验证自己的解码
        H_ASSERT( myDecodedData.getSize() == src.size() );

        for ( osl::u32 i = 0; i < myDecodedData.getSize(); i++ )
        {
			H_ASSERT( myDecodedData.charAt( i ) == src[i] );
			H_ASSERT( sysDecodedData.charAt( i ) == pdecode.get()[i] );
        }
    }

    //------------------------------------------------------------
    void TBase64::test3()
    {
        {
            osl::StringA inSrcData = "asdflkjaslfjo&&&^^%^$%$##@#.m;23014823-4asflsjdfa'k";
            osl::StringA outEncodedData;
            osl::StringA outDecodedData;
            osl::Base64::encode( inSrcData, outEncodedData );
            osl::Base64::decode( outEncodedData, outDecodedData );
            H_ASSERT( outDecodedData == inSrcData );
        }

        //随机数据的编码
        for ( osl::u32 i = 1; i < 100; i++ )
        {
            osl::u32 size = i * 1000;
            osl::MemoryDataStream inSrcData;
            inSrcData.setBufferSize( size );

            for ( osl::u32 k = 0; k < size; k++ )
            {
                osl::s8 b = ( osl::s8 )rand() % 256;
                inSrcData.write( b );
            }
			
			{
				osl::MemoryDataStream outEncodedData( size );
				osl::MemoryDataStream outDecodedData( size );
				osl::Base64::encode( inSrcData, outEncodedData );
				osl::Base64::decode( outEncodedData, outDecodedData );
				H_ASSERT( outDecodedData.getSize() == inSrcData.getSize() );

				for ( osl::u32 j = 0; j < outDecodedData.getSize(); j++ )
				{
					H_ASSERT( outDecodedData.charAt( j ) == inSrcData.charAt( j ) );
				}
			}

			{
				size_t encodelen = inSrcData.getSize() * 4 / 3 + 4;
				osl::ScopedMem pencoded( encodelen );
				H_ASSERT( osl::Base64::encode( inSrcData.getCache(), inSrcData.getSize(), pencoded.get(), encodelen ) );

				//自己的解码程序2
				size_t decodedlen = inSrcData.getSize() + 3;
				osl::ScopedMem pdecode( decodedlen );
				H_ASSERT( osl::Base64::decode( pencoded.get(), encodelen, pdecode.get(), decodedlen ) );
				H_ASSERT( inSrcData.getSize() == decodedlen );
				for ( osl::u32 j = 0; j < inSrcData.getSize(); j++ )
				{
					H_ASSERT( inSrcData.charAt( j ) == pdecode.get()[j] );
				}
			}
        }


    }


    void TBase64::testEfficiency()
    {
        //不太好比较，因为涉及到读写文件
    }

	void TBase64::test4()
	{
		osl::MemoryDataStream dssrc;
		if ( !dssrc.readRawFile( osl::Process::getBinDir( false ) + "/QOSLib_d.dll" ) )
		{
			return;
		}

		osl::MemoryDataStream dsencoded;
		osl::Base64::encode( dssrc, dsencoded );

		size_t encodedlen = dsencoded.getSize();
		osl::ScopedMem pencoded( encodedlen );
		osl::Base64::encode( dssrc.getCache(), dssrc.getSize(), pencoded.getPointer(), encodedlen );
		H_ASSERT( encodedlen == dsencoded.getSize() );
		for ( size_t i = 0; i < encodedlen; i++ )
		{
			H_ASSERT( pencoded.get()[i] == dsencoded.charAt(i) );
		}

		osl::MemoryDataStream dsdecode;
		osl::Base64::decode( dsencoded, dsdecode );
		size_t decodedlen = dsdecode.getSize() + 3;
		osl::ScopedMem pdecoded( decodedlen );
		osl::Base64::decode( dsencoded.getCache(), dsencoded.getSize(), pdecoded.get(), decodedlen );
		H_ASSERT( decodedlen == dsdecode.getSize() && decodedlen == dssrc.getSize() );
		for ( size_t i = 0; i < decodedlen; i++ )
		{
			H_ASSERT( pdecoded.get()[i] == dsdecode.charAt(i) );
			H_ASSERT( dssrc.charAt(i) == dsdecode.charAt(i) );
		}

		u8 c = dsdecode.charAt(0);
		(void)c;
	}
}//end of namespace LibTest


CREATE_FUNCTION( TBase64 );
