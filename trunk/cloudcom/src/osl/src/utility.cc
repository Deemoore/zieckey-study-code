#include "osl/include/osl_inner_pre.h"

#include "osl/include/string_ext.h"
#include "osl/include/string_util.h"
#include "osl/include/utility.h"
#include "osl/include/file_util.h"

#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>

namespace osl
{


	bool Util::readFileLine( const char* szFileName, StringAList& lines )
	{
		if ( !szFileName )
		{
			return false;
		}

		std::ifstream ifs( szFileName );

		if ( ! ifs )
		{
			return false;
		}

		StringA line;

		while( !ifs.eof() )
		{
			getline( ifs, line );
			lines.push_back( line );
		}

		return true;
	}



#ifdef H_OS_LINUX
    namespace
    {
        //static char filter[256];
        int scandirselect( const struct dirent *dir )
        {
            if( strlen(dir->d_name) > 5)
                return 1;
            else
                return 0;
        }
    }
#endif

    void Util::getFiles( const osl::StringA& strDirName, StringAList& files, bool recursively/* = true*/, const osl::StringA& filter/* = "*.*"*/ )
    {
#ifdef H_OS_WINDOWS
        struct _finddata_t finfo; //file info

        osl::StringA p;

        //if ( ( hFile = _findfirst( p.assign( strDirName ).append( "/*" ).append( "*" ).c_str(), &fileinfo ) ) != -1 )
        intptr_t hFile = _findfirst( osl::FileUtil::concatenatePath( strDirName, "*" ).c_str(), &finfo );
        if ( -1 == hFile )
        {
            osl::OStringStreamA log;
            log << "_findfirst failed. return value = -1, errno=" << errno;
            fprintf( stderr, log.str().c_str() );
            return;
        }

        do
        {
            if ( ( finfo.attrib & _A_SUBDIR ) )
            {
                if ( recursively && strcmp( finfo.name, "." ) != 0 && strcmp( finfo.name, ".." ) != 0 )
                {
                    //getFiles( p.assign( strDirName ).append( "/" ).append( fileinfo.name ), files, recursively, filter );
                    getFiles( osl::FileUtil::concatenatePath( strDirName, finfo.name ), files, recursively, filter );
                }
            }
            else
            {
                //files.push_back( p.assign( strDirName ).append( "/" ).append( fileinfo.name ) );
                StringA strFileName = osl::FileUtil::concatenatePath( strDirName, finfo.name );

                if ( StringUtil::match( strFileName, filter ) )
                {
                    files.push_back( strFileName );
                }
            }
        }
        while ( _findnext( hFile, &finfo ) == 0 );

        _findclose( hFile );

#else
        struct dirent **namelist;
        int n = scandir( strDirName.c_str(), &namelist, 0, alphasort );

        if ( n < 0 )
        {
            osl::OStringStreamA log;
            log << "scandir failed. return value = -1, errno=" << errno;
            fprintf( stderr, log.str().c_str() );
            return;
        }

        for ( int i = 0; i < n; ++i )
        {
            if ( namelist[i]->d_type == DT_DIR )
            {
                if ( recursively && strcmp( namelist[i]->d_name, "." ) != 0 && strcmp( namelist[i]->d_name, ".." ) != 0 )
                {
                    getFiles( osl::FileUtil::concatenatePath( strDirName, namelist[i]->d_name ), files, recursively, filter );
                }
            }
            else
            {
                StringA strFileName = osl::FileUtil::concatenatePath( strDirName, namelist[i]->d_name );

                if ( StringUtil::match( strFileName, filter ) )
                {
                    files.push_back( strFileName );
                }
            }
        }
        free( namelist );
        //H_ASSERT( false && "need implements." );
#endif
    }
}

