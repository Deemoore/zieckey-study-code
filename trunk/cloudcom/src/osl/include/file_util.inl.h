
#pragma once

#ifdef H_OS_WINDOWS
#   include <direct.h>
#   include <io.h>
#else
#   include <sys/types.h>
//#   include <sys/dir.h>
#	include <dirent.h>
#endif

//#include "osl/include/HUtil.h"

namespace osl
{




    //----------------------------------------------------------
    inline bool FileUtil::isDirectoryName( const StringA& strFileName )
    {
        if ( *strFileName.rbegin() == H_STR( '/' ) )
        {
            return true;
        }

        return false;
    }
    //----------------------------------------------------------
    inline bool FileUtil::isValidDirName( const char* szName )
    {
        return !( szName [0] == ( '.' ) ||
            ( szName [1] != 0 && ( szName[1] == '.' && szName[2] == 0 ) ) );
    }
    //----------------------------------------------------------
    //! Query whether strFileName is a absolute path.
    inline bool FileUtil::isAbsolutePathName( const StringA& strPathName )
    {
        if( strPathName.size() == 0 )
        {
            return false;
        }

#ifdef H_OS_WINDOWS

        if ( isalpha( static_cast<unsigned char>(strPathName[0]) ) && strPathName[1] == ':' )
        {
            return true;
        }
        else
        {
            return false;
        }

#else
        return strPathName[0] == '/';
#endif

    }
    //----------------------------------------------------------
    inline StringA FileUtil::getAbsolutePathName( const StringA& strPathName )
    {
        StringA strTmp = strPathName;

        if ( !isAbsolutePathName( strTmp ) )
        {
            //
            char szDir[_MAX_PATH];
#ifdef H_OS_WINDOWS
            if( _getcwd( szDir, _MAX_PATH ) )
            {
                strTmp =  StringA( szDir ) + ( "/" ) + strTmp;
            }
#else
            getcwd( szDir, _MAX_PATH );
            strTmp =  StringA( szDir ) + ( "/" ) + strTmp;
#endif

        }

        // convert file name here.
        convertFileName( strTmp );

        return strTmp;
    }
    //----------------------------------------------------------
    inline StringA FileUtil::buildAbsolutePathName( const StringA& strPathName, const StringA& strDefaultParentDir )
    {
        if( isAbsolutePathName( strPathName ) )
        {
            return strPathName;
        }

        return compactPathName( strDefaultParentDir + "/" + strPathName );
    }
    //----------------------------------------------------------
    inline StringA FileUtil::getFileName( const StringA& strFileName )
    {
        // since '/' equal to L'/', we can cast to either one.
        StringA::size_type i = strFileName.find_last_of( ( StringA::value_type )'/' );

        if ( i == StringA::npos )
        {
            return strFileName;
        }

        return strFileName.substr( i + 1 );
    }
    //----------------------------------------------------------
    inline StringA FileUtil::getFileNameWithNoExt( const StringA& strFileName )
    {
        // since '/' equal to L'/', we can cast to either one.
        StringA::size_type iStart = strFileName.find_last_of( ( StringA::value_type )'/' );

        if ( iStart == StringA::npos )
        {
            iStart = 0;
        }
        else
        {
            // skip the '/'
            ++iStart;
        }

        return strFileName.substr( iStart, strFileName.find_last_of( ( StringA::value_type )'.' ) - iStart );
    }
    //----------------------------------------------------------
    inline StringA FileUtil::getFileNameExtension( const StringA& strFileName )
    {
        StringA::size_type endPos = strFileName.find_last_of ( ( StringA::value_type )'.' );

        if ( endPos < strFileName.length() - 1 )
        {
            return strFileName.substr( endPos + 1 );
        }

        return StringA();
    }
    //----------------------------------------------------------
    inline StringA FileUtil::getFileDirName( const StringA& strFileName )
    {
        // since '/' equal to L'/', we can cast to either one.
        StringA::size_type i = strFileName.find_last_of( ( StringA::value_type )'/' );

        if ( i == StringA::npos )
        {
            return StringA();
        }

        return strFileName.substr( 0, i );
    }

    //-------------------------------------------------------------------
    inline bool FileUtil::isDirectory( const char* szFileName )
    {
        if ( !szFileName )
        {
            return false;
        }
        return isDirectory( szFileName );
    }

    //-------------------------------------------------------------------
    inline bool FileUtil::isDirectory( const StringA& strFileName )
    {
        //for the 'stat' API, the parameter strFileName SHOULD not contain a trailing backslash
        osl::StringA strStandardisePath = standardisePath( strFileName, false );

        struct stat st;
        if ( 0 != stat( strStandardisePath.c_str(), &st ) )
        {
            return false;
        }

#ifdef H_OS_WINDOWS

        if ( st.st_mode == _S_IFDIR )
#else
        if ( st.st_mode == S_IFDIR )
#endif
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    //-------------------------------------------------------------------
    inline bool FileUtil::removeFSDirIfEmpty( const StringA& strDirName, bool bRecursivelyDeleteEmptyParentDir /*= true*/ )
    {
        if ( !isDirectory( strDirName ) )
        {
            return true;
        }

        bool retval = true;

        StringAList files;
        getFiles( strDirName, files, true );

        if ( files.size() == 0 )
        {
            if ( FileUtil::rmdir( strDirName.c_str() ) != 0 )
            {
                retval = false;
            }
        }

        if ( bRecursivelyDeleteEmptyParentDir )
        {
            StringA strParentDir = getParentDirName( strDirName );

            if ( !removeFSDirIfEmpty( strParentDir, bRecursivelyDeleteEmptyParentDir ) )
            {
                retval = false;
            }
        }

        return retval;
    }

    //-------------------------------------------------------------------
    inline StringA FileUtil::getParentDirName( const StringA& strFileName, bool bWithEndSlash /*= true*/ )
    {
        StringA path = standardisePath( strFileName, false );

        if ( !isAbsolutePathName( strFileName ) )
        {
            path = getAbsolutePathName( path );
        }

        size_t pos = path.find_last_of( '/' );

        if ( pos == 0 || pos == StringA::npos )
        {
            if ( bWithEndSlash )
            {
                path += "/";
            }

            return path;
        }
        else
        {
            if ( bWithEndSlash )
            {
                StringA retp = StringA( path.c_str(), pos ) + "/";
                return retp;
            }
            else
            {
                return StringA( path.c_str(), pos );
            }
        }
    }

    //-------------------------------------------------------------------
    inline bool FileUtil::rmdir( const StringA& strDirName )
    {
        return rmdir( strDirName.c_str() );
    }

    //-------------------------------------------------------------------
    inline bool FileUtil::rmdir( const char* strDirName )
    {
#ifdef H_OS_WINDOWS

        if ( ::_rmdir( strDirName ) == 0 )
#else
        if ( ::rmdir( strDirName ) == 0 )
#endif
        {
            return true;
        }


        return false;
    }

};//namespace irr.


