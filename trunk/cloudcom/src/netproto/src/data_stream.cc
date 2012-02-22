#include "netproto/include/data_stream.h"

#ifdef WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif


namespace npp
{


    //////////////////////////////////////////////////////////////////////////
    //                         MemoryDataStream
    //////////////////////////////////////////////////////////////////////////

    
    //------------------------------------------------------------
    void MemoryDataStream::toText()
    {
        if( m_nSize > 0 )
        {
            if( *( m_pData + m_nSize - 1 ) != 0 )
            {
                seekp( m_nSize - tellp() );
                write( (char)0 );
				seekp( -1 );
				setSize( m_nSize - 1 );
            }
        }
    }
    //------------------------------------------------------------
    bool MemoryDataStream::openRawFile( const std::string& strFileName )
    {
        return readRawFile( strFileName );
    }

    //----------------------------------------------
    bool MemoryDataStream::readRawFile( const std::string& strFileName )
    {
        std::string strPathName = strFileName;

        // clear old data.
        if ( m_bSelfCreate && m_pData )
        {
            H_FREE(m_pData);
            m_pData = NULL;
            m_nSizeBuffer = 0;
            m_bSelfCreate = true;
        }

        m_nPosWrite = 0;
        m_nPosRead  = 0;
        m_nSize = 0;


        if ( strPathName.size() < 1 )
        {
            return false;
        }

        FILE* pF = fopen( strPathName.c_str(), "r" );
        struct stat st;

        //////////////////////////////////////////////////////////////////////////
        //   I DONT KNOW WHY  _fstat( pF, &st ) cant work correctly.
        //////////////////////////////////////////////////////////////////////////

        if ( !pF || 0 != stat( strPathName.c_str(), &st ) )
        {
            if ( pF )
            {
                fclose( pF );
            }

            return false;
        }


        // allocate memory.
        m_pData = ( u8* )H_ALLOC_NAME( st.st_size, "MemoryDataStream" );

        if ( !m_pData )//st.st_size may be 0
        {
            fclose( pF );
            return false;
        }

        m_bSelfCreate = true;
        m_nSize = st.st_size;
        m_nSizeBuffer = m_nSize;



        size_t nRemainSize = m_nSize;

        while ( nRemainSize > 0 && !feof( pF ) )
        {

            size_t nRead = fread( m_pData + ( m_nSize - nRemainSize ) ,
                                  sizeof( char ), nRemainSize, pF );

            nRemainSize -= nRead;

            if ( ferror( pF ) )
            {
                if ( pF )
                {
                    fclose( pF );
                }

                return false;
            }
        }

        fclose( pF );

        assert( nRemainSize == 0 );
        seekp( (s32)m_nSize );

        return true;
    }

    void createDir( const std::string& strFileName )
    {
        //std::string strPathName = StringUtil::utf8ToMbs(strFileName);
        std::string strPathName = strFileName;

        std::replace( strPathName.begin(), strPathName.end(), '\\', '/' );

        size_t nCurSplit = 0, nNextSplit = 0;

        do
        {
            //  "/abc/ab/abc",   "e:/abac/adc"   "abcc/abc/a",   "abc"
            // get current dir name.
            nCurSplit = strPathName.find_first_of( ( std::string::value_type )'/', nNextSplit );

            if ( nCurSplit != 0 && nCurSplit != std::string::npos  )
            {
                // current dir
#ifdef H_OS_WINDOWS
                _mkdir( strPathName.substr( 0, nCurSplit ).c_str() );

#elif defined(H_OS_LINUX)
                mkdir( strPathName.substr( 0, nCurSplit ).c_str(), 0777 );
#endif
            }

            nNextSplit = nCurSplit + 1;

            // nNextSplit = strPathName.find_first_of( (std::string::value_type)'/', nCurSplit + 1 );

            // next dir
            //nCurSplit = nNextSplit + 1;

        }
        while ( nCurSplit != std::string::npos );
    }
    //----------------------------------------------
    bool MemoryDataStream::saveToFile( const std::string& strFileName )
    {
        // create directory.
        createDir( strFileName );

		//std::string strPathName = StringUtil::utf8ToMbs(strFileName);
		std::string strPathName = strFileName;
        
        // open file.
        FILE* pF = fopen( strPathName.c_str(), ( "w+" ) );

        if ( !pF )
        {
            return false;
        }

        size_t nWroteSize = fwrite( m_pData, 1, m_nSize, pF );

        fclose( pF );

        if ( nWroteSize < ( u32 )m_nPosWrite )
        {
            return false;
        }

        return true;
    }

    //-------------------------------------------------------
};//namespace
