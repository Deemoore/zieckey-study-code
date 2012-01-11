#include "osl/include/inner_pre.h"

#include "osl/include/mem_alloc.h"
#include "osl/include/string_ext.h"
#include "osl/include/string_util.h"
#include "osl/include/file_util.h"
#include "osl/include/object.h"
#include "osl/include/data_stream.h"

#include <sys/types.h>
#include <sys/stat.h>

#include <fstream>

//#if defined(H_OS_LINUX) || defined(H_OS_MACOSX)
//#   include <sys/param.h>
//#   define MAX_PATH MAXPATHLEN
//#endif


namespace osl
{

    //------------------------------------------------------
    //FileUtil* FileUtil::m_pFileUtil = NULL;
    //---------------------------------------------------------
    FileUtil::FileUtil()
    {
//         H_ASSERT( !m_pFileUtil );
//         m_pFileUtil = this;

//        // register working file directory
//        {
//            char szDir[_MAX_PATH];
//
//
//#ifdef H_OS_WINDOWS
//			StringA strDir;
//            if( _getcwd( szDir, _MAX_PATH ) )
//			{
//				strDir = szDir;
//			}
//#else
//            getcwd( szDir, _MAX_PATH );
//			StringA strDir = szDir;
//#endif
//            
//            osl::FileUtil::convertFileName( strDir );
//
//            FSDirectory* pDir = H_NEW osl::FSFileArchive( strDir );
//            pDir->open();
//            registerFileDirectory( FD_WORK, pDir );
//
//			//
//			//pDir = H_NEW osl::FSFileArchive( strDir + "/data/boot" );
//            //pDir->open();
//            //registerFileDirectory( FD_BOOT_RESOURCE, pDir );
//        }
    }
    //---------------------------------------------------------
    FileUtil::~FileUtil()
    {
        //m_pFileUtil = NULL;
    }
	//---------------------------------------------------------
// 	void  FileUtil::setTemporaryFSDir( const osl::StringA& strDirName )
// 	{
// 		FSDirectory* pDir = H_NEW osl::FSFileArchive( strDirName );
// 		pDir->open();
// 		registerFileDirectory( FD_TEMPORARY, pDir );
// 	}
// 	//---------------------------------------------------------
// 	osl::StringA  FileUtil::getTemporaryFSDir()
// 	{
// 		if( m_vDirLookup[FD_TEMPORARY] )
// 		{
// 			return m_vDirLookup[FD_TEMPORARY]->getFullFileName();
// 		}
// 
// 		return osl::OS::getBinDir() + "/temp";
// 	}
//	 //----------------------------------------------------------
//	bool FileUtil::isRelativeFileName( const StringA& strFileName )
//	{
//#ifdef H_OS_WINDOWS
//
//		// if can not find ":", must be relative path
//		if( strFileName.find(":") != strFileName.npos )
//		{
//			return true;
//		}
//
//		return false;
//
//#elif defined( H_OS_LINUX )
//
//		// if size is zero or first character is not "/", must be relative.
//		if( strFileName.size() == 0 || strFileName[0] != '/' )
//		{
//			return true;
//		}
//
//		return false;
//#endif
//	}
	//----------------------------------------------------------
	StringA FileUtil::compactPathName( const StringA& strPathName )
	{
		// Not Tested yet.
		//".././././././heyuandata/./.././heyuandata"

		Vector<StringA> vPaths;
		osl::StringUtil::split( vPaths, strPathName, "/\\", 0 );

		osl::OStringStreamA strNewPath;

		// incase of root dir.
		if( strPathName[0] == '/' )
		{
			strNewPath << (char)'/';
		}


		// erase null.
		List<StringA> vNewPaths;
		{
			Vector<StringA>::reverse_iterator it( vPaths.rbegin() ), ite( vPaths.rend() );
			for(; it != ite; ++it )
			{
				if( *it == "." )
				{
					continue;
				}
				else if( *it == ".." )
				{
					// erase none '.' parent dir.
					while( ++it != ite 
						&& *it == "." )
					{
						// do nothing.
					}

					// if first of the path is "../" , should reserve it.
					if( it == ite )
					{
						vNewPaths.push_front( ".." );
						break;
					}
				}
				else
				{
					vNewPaths.push_front( *it );
				}
			}
		}

		// build string
		{
			List<StringA>::iterator it( vNewPaths.begin() ), ite( vNewPaths.end() );
			while( it != ite )
			{
				strNewPath << *it;

				if( ++it == ite )
				{
					break;
				}

				strNewPath << (char)'/';
			}
		}

		// TODO;
		return strNewPath.str(); 
	}
    //-------------------------------------------------------------------
    StringA FileUtil::concatenatePath( const StringA& prefix, const StringA& postfix )
    {
        typedef StringA MyString;
        MyString pre = prefix;
        MyString post = postfix;
        pre = standardisePath( pre, false );
        post = standardisePath( post, false );
        StringUtil::trim( post, "/", true, false );
        if ( osl::StringUtil::endsWith( postfix, "/") )
        {
            post += "/";
        }
        return pre + "/" + post;
    }

    //-------------------------------------------------------------------
    StringW FileUtil::concatenatePath( const StringW& prefix, const StringW& postfix )
    {
        typedef StringW MyString;
        MyString pre = prefix;
        MyString post = postfix;
        pre = standardisePath( pre, false );
        post = standardisePath( post, false );
        StringUtil::trim( post, L"/", true, false );
        if ( osl::StringUtil::endsWith( postfix, L"/") )
        {
            post += L"/";
        }
        return pre + L"/" + post;
    }
    //-----------------------------------------------------------------------
    StringA FileUtil::standardisePath( const StringA& init, bool bWithEndSlash /*= true*/ )
    {
        if ( init.length() < 1 )
        {
            return init;
        }

        StringA path = init;

        std::replace( path.begin(), path.end(), '\\', '/' );

        if ( path[path.length() - 1] != '/' && bWithEndSlash )
        {
            path += "/";
        }
        else if ( path[path.length() - 1] == '/' && !bWithEndSlash )
        {
            StringUtil::trim( path, "/", false, true );
        }

#ifdef H_OS_WINDOWS
        StringUtil::toLowerCase( path );
#endif

        return path;
    }


    //-----------------------------------------------------------------------
    StringW FileUtil::standardisePath( const StringW& init, bool bWithEndSlash /*= true*/ )
    {
        if ( init.length() < 1 )
        {
            return init;
        }

        StringW path = init;

        std::replace( path.begin(), path.end(), L'\\', L'/' );

        if ( path[path.length() - 1] != L'/' && bWithEndSlash )
        {
            path += L"/";
        }
        else if ( path[path.length() - 1] == L'/' && !bWithEndSlash )
        {
            StringUtil::trim( path, L"/", false, true );
        }

#ifdef H_OS_WINDOWS
        StringUtil::toLowerCase( path );
#endif
        return path;
    }

    //-----------------------------------------------------------------------
    void FileUtil::splitFileName( const StringA& qualifiedName,
                                  StringA& outBasename, StringA& outPath, bool bWithEndSlash /*= false */  )
    {
        StringA path = qualifiedName;
        // Replace \ to / 
        std::replace( path.begin(), path.end(), '\\', '/' );
        // split based on final /
        size_t i = path.find_last_of( '/' );

        if ( i == StringA::npos )
        {
            outPath = "";
            outBasename = qualifiedName;
        }
        else
        {
            outBasename = path.substr( i + 1, path.size() - i - 1 );
            if ( bWithEndSlash )
            {
                outPath = path.substr( 0, i + 1 );
            }
            else
            {
                outPath = path.substr( 0, i );
            }
        }

#ifdef H_OS_WINDOWS
        StringUtil::toLowerCase( outBasename );
        StringUtil::toLowerCase( outPath );
#endif
    }

    //-----------------------------------------------------------------------
    void FileUtil::splitFileName( const StringW& qualifiedName,
                                  StringW& outBasename, StringW& outPath, bool bWithEndSlash /*= false */  )
    {
        StringW path = qualifiedName;
        // Replace \ with / first
        std::replace( path.begin(), path.end(), L'\\', L'/' );
        // split based on final /
        size_t i = path.find_last_of( L'/' );

        if ( i == StringW::npos )
        {
            outPath = L"";
            outBasename = qualifiedName;
        }
        else
        {
            outBasename = path.substr( i + 1, path.size() - i - 1 );
            if ( bWithEndSlash )
            {
                outPath = path.substr( 0, i + 1 );
            }
            else
            {
                outPath = path.substr( 0, i );
            }
        }

#ifdef H_OS_WINDOWS
        StringUtil::toLowerCase( outBasename );
        StringUtil::toLowerCase( outPath );
#endif
    }
    //-----------------------------------------------------------------------
    void FileUtil::convertFileName( StringW& fileName )
    {
        std::replace( fileName.begin(), fileName.end(), L'\\', L'/' );

#ifdef H_OS_WINDOWS
        StringUtil::toLowerCase( fileName );
#endif
    }
    //-----------------------------------------------------------------------
    void FileUtil::convertFileName( StringA& fileName )
    {
        std::replace( fileName.begin(), fileName.end(), '\\', '/' );

#ifdef H_OS_WINDOWS
        StringUtil::toLowerCase( fileName );
#endif
    }

    //----------------------------------------------------------
//     bool FileUtil::copyFileHierarchy( IFileDirectory* pSrcDir, IFileDirectory* pDstDir )
//     {
//         if ( !pSrcDir || !pDstDir )
//         {
//             return false;
//         }
// 
//         IFileDirectory::IEnumChildPtr pSrcChildren = pSrcDir->getChildEnum();
// 
//         // check whether has any child.
//         if ( pSrcChildren.isNull() )
//         {
//             return false;
//         }
// 
//         while ( pSrcChildren->hasMoreElements() )
//         {
//             IFile* pSrcFile = pSrcChildren->getNext();
// 
// 
//             IFile* pDstFile = pDstDir->createFile( pSrcFile->getFileName(), pSrcFile->isDirectory() );
// 
//             // if any subclass do not obey type rule.
//             if ( !pDstDir || pSrcFile->isDirectory() != pDstFile->isDirectory() )
//             {
//                 return false;
//             }
// 
//             // assure open the file.
//             pSrcFile->open();
// 
//             // if is directory should copy hierarchy.
//             if ( pSrcFile->isDirectory() )
//             {
//                 if ( !copyFileHierarchy( ( IFileDirectory* )pSrcFile, ( IFileDirectory* )pDstFile ) )
//                 {
//                     return false;
//                 }
// 
//                 // if is a file, should copy data.
//             }
//             else
//             {
//                 if ( pSrcFile->getSize() > 0 )
//                 {
//                     pDstFile->write( pSrcFile->getCache(), pSrcFile->getSize() );
//                 }
//             }
// 
//             // flush it.
//             pDstFile->flush();
// 
//         }// while each child
// 
//         // flush the data.
//         if ( pDstDir )
//         {
//             pDstDir->flush();
//         }
// 
//         return true;
//     }
//     //----------------------------------------------------------
//     bool FileUtil::saveFSFile( IFile* pFile, const StringA& strFileName )
//     {
//         // assure make directory.
//         makeFSDir( getFileDirName( strFileName ) );
// 
//         FILE* pF = NULL;
// 
//         pF = fopen( strFileName.c_str(), "w+" );
// 
//         if ( !pF )
//         {
//             return false;
//         }
// 
//         size_t nWrote = fwrite( pFile->getCache(), 1, pFile->getSize(), pF );
// 
//         if ( nWrote != pFile->getSize() )
//         {
//             fclose( pF );
//             return false;
//         }
// 
//         fclose( pF );
// 
//         return true;
//     }
    //----------------------------------------------------------
    bool FileUtil::removeFSFile( const StringA& strFileName )
    {
        bool bDir = FileUtil::isDirectory( strFileName );

        if ( bDir )
        {
			assert( 0 && "not supported");
            //FSDirectory fsDir( NULL, strFileName );
            //fsDir.removeAllFiles();
			return false;
        }

        // remove self
        if ( bDir )
        {
            return rmdir( strFileName.c_str() ) == 0;
        }
        else
        {
#ifdef H_OS_WINDOWS
            return ::DeleteFileA( strFileName.c_str() ) ? true : false;
#else
            return remove( strFileName.c_str() ) == 0;
#endif
        }
    }
    //----------------------------------------------------------
    bool FileUtil::makeFSDir( const StringA& strFileName )
    {
        size_t nCurSplit = 0, nNextSplit = 0;

        int iret = 0;

        do
        {

            // get current dir name.
            nCurSplit = strFileName.find_first_of( ( StringA::value_type )'/', nNextSplit );
            nNextSplit = strFileName.find_first_of( ( StringA::value_type )'/', nCurSplit + 1 );

#ifdef H_OS_WINDOWS
            // current dir
            iret = _mkdir( strFileName.substr( 0, nNextSplit ).c_str() );
#else
            // current dir
            iret = mkdir( strFileName.substr( 0, nNextSplit ).c_str(), 0755 );
#endif
            /*
            if ( iret != 0 )
            {
                char buf[1024] = {};
                snprintf( buf, sizeof(buf), "%s mkdir failed. errno=%d, %s ", __func__, errno, strFileName.c_str() );
                perror( buf );
                return false;
            }
            */

            // next dir
            nCurSplit = nNextSplit + 1;

        }
        while ( nNextSplit != StringA::npos );

        return true;
    }
    //----------------------------------------------------------
    //! Find files in directory with a perl regular expression.
    //! \param regex Regular expression conforming to perl. It is boost::regex or boost::wregex.
    //! \param pFileDir Directory to find files.
    //! \param vFiles[out] Files container. It is list,vector etc. what support push_back() method.
    //! \param bRecursive Whether find in child directories of pFileDir.
    //! \param
//     template<typename REGEX, typename CONTAINER>
//     void findFilesWithRegex( const REGEX& regex, IFileDirectory* pFileDir, CONTAINER& vFiles, bool bRecursive )
//     {
//         if ( !pFileDir->isOpen() )
//         {
//             if ( !pFileDir->open() )
//             {
//                 return;
//             }
//         }
// 
//         IFileDirectory::IEnumChildPtr pChildEnum = pFileDir->getChildEnum();
// 
//         while ( pChildEnum->hasMoreElements() )
//         {
//             IFile* pFile = pChildEnum->getNext();
// 
//             if ( pFile->isDirectory() )
//             {
//                 // find in children
//                 if ( bRecursive )
//                 {
//                     findFilesWithRegex(
//                         regex, ( IFileDirectory* )( pFile ), vFiles, bRecursive );
//                 }
// 
//             }
//             else
//             {
// 
//                 s32	nMatch[2];
// 
//                 s32 nResult = pcre_exec( regex, 0,
//                                          pFile->getFileName().c_str(),
//                                          pFile->getFileName().length(),
//                                          0, 0, nMatch, 2 );
// 
//                 if ( nResult >= 0 )
//                 {
//                     vFiles.push_back( pFile );
//                 }
//             }
// 
//         }
//     }
//     //----------------------------------------------------------
//     void FileUtil::findFiles( const StringA& strFilePattern,
//                               IFileDirectory* pFileDir, osl::IFileList& vFiles, bool bRecursive )
//     {
//         /// Build regular match expression.
// 
//         OStringStreamA strRet;
// 
//         StringA::const_iterator it( strFilePattern.begin() ), ite( strFilePattern.end() );
// 
//         for ( ; it != ite; ++it )
//         {
//             switch ( *it )
//             {
//                 case '?':
//                     {
//                         strRet << ( ".{1}" );
//                     }
//                     break;
//                 case '.':
//                     {
//                         strRet << ( "[.]" );
//                     }
//                     break;
//                 case '*':
//                     {
//                         strRet << ( ".*" );
//                     }
//                     break;
//                 default:
//                     {
//                         strRet << *it;
//                     }
//                     break;
//             }
//         }
// 
// 
//         /// 2. find files in directories.
//         findFilesWithPerlRegex( strRet.str(), pFileDir, vFiles, bRecursive );
//     }
    //----------------------------------------------------------
    StringA FileUtil::filePatternToPerlRegex( const StringA& strFilePattern )
    {
        osl::OStringStreamA strRet;

        StringA::const_iterator it( strFilePattern.begin() ), ite( strFilePattern.end() );

        for ( ; it != ite; ++it )
        {
            switch ( *it )
            {
                case '?':
                    {
                        strRet << ( ".{1}" );
                    }
                    break;
                case '.':
                    {
                        strRet << ( "[.]" );
                    }
                    break;
                case '*':
                    {
                        strRet << ( ".*" );
                    }
                    break;
                default:
                    {
                        strRet << *it;
                    }
                    break;
            }
        }

        return strRet.str();
    }
    //----------------------------------------------------------
//     void FileUtil::findFilesWithPerlRegex( const StringA& strFilePattern,
//                                            IFileDirectory* pFileDir, IFileList& vFiles, bool bRecursive )
//     {
//         const char* pError = NULL;
//         s32   nCol = 0;
// 
//         pcre* pPcre = pcre_compile( strFilePattern.c_str(), 0, &pError, &nCol, 0 );
// 
//         if ( !pPcre )
//         {
//             OStringStreamA strTip;
//             strTip << "failed to compile regex pattern:" << strFilePattern;
//             H_LOG_NAME_ERROR( "oslib", strTip.str() );
//             return;
//         }
// 
// 
//         ///
//         findFilesWithRegex( pPcre, pFileDir, vFiles, bRecursive );
// 
// 
//         /// free it.
//         pcre_free( pPcre );
// 
// 
//         //try{
// 
//         //	boost::regex e( strFilePattern.c_str() );
// 
//         //	findFilesWithRegex( e, pFileDir, vFiles, bRecursive );
// 
//         //}catch( boost::regex_error& err )
//         //{
//         //	H_ASSERT( false && "Error: Wrong file pattern"  );
// 
//         //	// printf log.
//         //	//OStreamStringA strTip;
//         //	//strTip << ("Error: Wrong file pattern:") << strFilePattern << err.what();
//         //	//LOG_DEFAULT( strTip.str() );
//         //}
//     }
//     //----------------------------------------------------------
//     void FileUtil::registerFileDirectory( u32 nIndex, IFileDirectory* pFileDir )
//     {
//         if ( nIndex < FD_NUM )
//         {
//             m_vDirLookup[nIndex] = pFileDir;
//         }
//     }
    //-----------------------------------------------------------------------
    bool FileUtil::getRelativePathName( StringA& strRelPathName, const StringA& strFullPathName, const StringA& strPartPathName )
    {

        //"e:/test/b1/aaa.txt" - "e:/test/" = "b1/aa.txt"
        // strFullPathName  "e:/test/b1/aaa.txt" "e:/test" "e:/test/"
        // strPartPathName  "e:/test" "e:/test/"

        if( isAbsolutePathName( strFullPathName ) && isAbsolutePathName( strPartPathName ) )
        {
            StringA strFullName = strFullPathName;
            convertFileName( strFullName );
            StringA strPartName = standardisePath( strPartPathName );

            const char* pPath = strstr( strFullName.c_str(), strPartName.c_str() );

            if( pPath )
            {
                strRelPathName = strFullName.substr( strPartName.length() );
                return true;
            }
        }

        strRelPathName = strFullPathName;

        return false;
    }
    //----------------------------------------------------------
//     IFile* FileUtil::openReadFile( const StringA& strFileName, u32 nDirIndex )
//     {
//         IFileDirectory* pDir = getFileDirectory( nDirIndex );
// 
//         if ( pDir )
//         {
//             osl::StringA strRelName ;
//             getRelativePathName( strRelName, strFileName, pDir->getFullFileName() ) ;
// 
//             IFile* pRet = pDir->openFile( strRelName );
// 
//             if ( pRet )
//             {
//                 pRet->open();
//                 return pRet;
//             }
//         }
// 
//         return NULL;
//     }
    //----------------------------------------------------------
//     IFile* FileUtil::createWriteFile( const StringA& strFileName, u32 nDirIndex  )
//     {
//         IFileDirectory* pDir = getFileDirectory( nDirIndex );
// 
//         if ( pDir )
//         {
//             osl::StringA strRelName;
//             getRelativePathName( strRelName, strFileName, pDir->getFullFileName() );
// 
//             IFile* pRet = pDir->createFile( strRelName, false );
// 
//             if ( pRet )
//             {
//                 pRet->open();
//                 return pRet;
//             }
//         }
// 
//         return NULL;
//     }
    //----------------------------------------------------------
//     IFile* FileUtil::createAndWriteFile( const StringA& strFileName,  bool append )
//     {
//         return getFileDirectory( 0 )->createFile( strFileName, false );
//     }
    ////----------------------------------------------------------
    //IXMLReader* FileUtil::createXMLReader(const StringA& strFileName, u32 nDirIndex )
    //{
    //	if( nDirIndex < FD_NUM )
    //	{
    //		IFile* pFile = m_vDirLookup[nDirIndex]->openFile( strFileName );

    //		if( pFile )
    //		{
    //			return createIXMLReader( pFile );
    //		}
    //	}

    //	return NULL;
    //}
    ////----------------------------------------------------------
    //IXMLReader* FileUtil::createXMLReader(IReadFile* pFile )
    //{
    //	if( pFile )
    //	{
    //		return createIXMLReader( pFile );
    //	}

    //	return NULL;
    //}
    ////----------------------------------------------------------
    //IXMLReaderUTF8* FileUtil::createXMLReaderUTF8( const StringA& strFileName,u32 nDirIndex )
    //{
    //	if( nDirIndex < FD_NUM )
    //	{
    //		IFile* pFile = m_vDirLookup[nDirIndex]->openFile( strFileName );

    //		if( pFile )
    //		{
    //			return createXMLReaderUTF8( pFile );
    //		}
    //	}
    //	return NULL;
    //}
    ////----------------------------------------------------------
    //IXMLReaderUTF8* FileUtil::createXMLReaderUTF8(IReadFile* pFile )
    //{
    //	if( pFile )
    //	{
    //		return createIXMLReaderUTF8( pFile );
    //	}

    //	return NULL;
    //}

    ////----------------------------------------------------------
    //IXMLWriter* FileUtil::createXMLWriter( const StringA& strFileName, u32 nDirIndex)
    //{
    //	if( nDirIndex < FD_NUM )
    //	{
    //		IFile* pFile = m_vDirLookup[nDirIndex]->createFile( strFileName, false );

    //		if( pFile )
    //		{
    //			return createXMLWriter( pFile );
    //		}
    //	}
    //	return NULL;
    //}
    ////----------------------------------------------------------
    //IXMLWriter* FileUtil::createXMLWriter(IWriteFile* pFile )
    //{
    //	return new CXMLWriter(pFile);
    //}
    ////----------------------------------------------------------
    //IReadFile* FileUtil::createAndOpenFile(const c8* filename)
    //{
    //	return getFileDirectory(0)->openFile(  filename );
    //}
    ////----------------------------------------------------------
    //IReadFile* FileUtil::createMemoryReadFile(void* memory, s32 len, const c8* fileName, bool deleteMemoryWhenDropped)
    //{
    //	return new MemoryFile( memory, len, deleteMemoryWhenDropped );
    //}

    //----------------------------------------------------------
    bool FileUtil::isFSFileExist( const osl::StringA& strFileName )
    {
        struct stat st;

        //////////////////////////////////////////////////////////////////////////
        //   I DONT KNOW WHY  _fstat( pF, &st ) cant work correctly.
        //////////////////////////////////////////////////////////////////////////

        if (  0 != stat( strFileName.c_str(), &st ) )
        {
            return false;
        }

        return true;
    }

// #ifdef H_OS_LINUX
//     namespace
//     {
//         static char filter[256];
//         int scandirselect( const struct dirent *dir )
//         {
//             if( strlen(dir->d_name) > 5)
//                 return 1;
//             else
//                 return 0;
//         }
//     }
// #endif

//    void FileUtil::getFiles( const osl::StringA& strDirName, StringAList& files, bool recursively/* = true*/, const osl::StringA& filter/* = "*.*"*/ )
//    {
//#ifdef H_OS_WINDOWS
//        struct _finddata_t finfo; //file info
//
//        osl::StringA p;
//
//        //if ( ( hFile = _findfirst( p.assign( strDirName ).append( "/*" ).append( "*" ).c_str(), &fileinfo ) ) != -1 )
//        intptr_t hFile = _findfirst( concatenatePath( strDirName, "*" ).c_str(), &finfo );
//        if ( -1 == hFile )
//        {
//            osl::OStringStreamA log;
//            log << "_findfirst failed. return value = -1, errno=" << errno;
//            H_LOG_NAME_DEBUG( "FileUtil", log.str() );
//            return;
//        }
//
//        do
//        {
//            if ( ( finfo.attrib & _A_SUBDIR ) )
//            {
//                if ( recursively && strcmp( finfo.name, "." ) != 0 && strcmp( finfo.name, ".." ) != 0 )
//                {
//                    //getFiles( p.assign( strDirName ).append( "/" ).append( fileinfo.name ), files, recursively, filter );
//                    getFiles( concatenatePath( strDirName, finfo.name ), files, recursively, filter );
//                }
//            }
//            else
//            {
//                //files.push_back( p.assign( strDirName ).append( "/" ).append( fileinfo.name ) );
//                StringA strFileName = concatenatePath( strDirName, finfo.name );
//
//                if ( StringUtil::match( strFileName, filter ) )
//                {
//                    files.push_back( strFileName );
//                }
//            }
//        }
//        while ( _findnext( hFile, &finfo ) == 0 );
//
//        _findclose( hFile );
//
//#else
//        struct dirent **namelist;
//        int n = scandir( strDirName.c_str(), &namelist, 0, alphasort );
//
//        if ( n < 0 )
//        {
//            osl::OStringStreamA log;
//            log << "scandir failed. return value = -1, errno=" << errno;
//            H_LOG_NAME_DEBUG( "FileUtil", log.str() );
//            return;
//        }
//
//        for ( int i = 0; i < n; ++i )
//        {
//            if ( namelist[i]->d_type == DT_DIR )
//            {
//                if ( recursively && strcmp( namelist[i]->d_name, "." ) != 0 && strcmp( namelist[i]->d_name, ".." ) != 0 )
//                {
//                    getFiles( concatenatePath( strDirName, namelist[i]->d_name ), files, recursively, filter );
//                }
//            }
//            else
//            {
//                StringA strFileName = concatenatePath( strDirName, namelist[i]->d_name );
//
//                if ( StringUtil::match( strFileName, filter ) )
//                {
//                    files.push_back( strFileName );
//                }
//            }
//        }
//
//        free( namelist );
//        //H_ASSERT( false && "need implements." );
//#endif
//    }



    bool FileUtil::copyFSFile( const osl::StringA& strSrcFile, const osl::StringA& strDestFile, bool bOverride/* = true */ )
    {
        if ( isDirectory( strSrcFile ) )
        {
            return false;
        }

        StringA strDestFilePath = strDestFile;

        if ( isDirectory( strDestFile ) )
        {
            strDestFilePath = concatenatePath( strDestFile, getFileName( strSrcFile ) );
        }

        if ( isFSFileExist( strDestFilePath ) && !bOverride )
        {
            return false;
        }

        osl::MemoryDataStream databuf;
        databuf.readRawFile( strSrcFile );
        databuf.saveToFile( strDestFile );
        return true;
    }

    //-------------------------------------------------------------------
    bool FileUtil::readFileLine( const char* szFileName, StringAList& lines )
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

    bool FileUtil::writeToFile( const StringA& filepath, const void* content, const size_t len )
    {
        return writeToFile( filepath.c_str(), content, len );
    }

    bool FileUtil::writeToFile( const char* filepath, const void* content, const size_t len )
    {
        FILE* infile = ::fopen( filepath, "a");

        if ( infile == NULL )
        {
            fprintf( stderr, "%s : could not open file \"%s\" for write", __func__, filepath);
            return false;
        }

        ::fwrite( content, sizeof(char), len, infile);

        ::fclose(infile);

        return true;
    }


    void FileUtil::getFiles( const StringA& strDirName, StringAList& files, bool recursively/* = true*/, const StringA& filter/* = "*.*"*/ )
    {
#ifdef H_OS_WINDOWS
        struct _finddata_t finfo; //file info

        osl::StringA p;

        //if ( ( hFile = _findfirst( p.assign( strDirName ).append( "/*" ).append( "*" ).c_str(), &fileinfo ) ) != -1 )
        intptr_t hFile = _findfirst( osl::FileUtil::concatenatePath( strDirName, "*" ).c_str(), &finfo );
        if ( -1 == hFile )
        {
#ifdef H_RECORD_LOG
            osl::OStringStreamA log;
            log << "_findfirst failed. return value = -1, errno=" << errno;
            //H_LOG_NAME_DEBUG( "FileUtil", log.str() );
#endif		
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
            //H_LOG_NAME_DEBUG( "FileUtil", log.str() );
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

#endif
    }

    void FileUtil::listAllFiles( const StringA& strDirName, StringAList& files, int depth /*= 0*/, const StringA& filter/* = "*"*/ )
    {
        if ( depth < 0 )
        {
            return;
        }

#ifdef H_OS_WINDOWS
        struct _finddata_t finfo; //file info

        osl::StringA p;

        //if ( ( hFile = _findfirst( p.assign( strDirName ).append( "/*" ).append( "*" ).c_str(), &fileinfo ) ) != -1 )
        intptr_t hFile = _findfirst( osl::FileUtil::concatenatePath( strDirName, "*" ).c_str(), &finfo );
        if ( -1 == hFile )
        {
#ifdef H_RECORD_LOG
            osl::OStringStreamA log;
            log << "_findfirst failed. return value = -1, errno=" << errno;
            //H_LOG_NAME_DEBUG( "FileUtil", log.str() );
#endif		
            return;
        }

        do
        {
            StringA strFileName = osl::FileUtil::concatenatePath( strDirName, finfo.name );
            if ( ( finfo.attrib & _A_SUBDIR ) )
            {
                if ( strcmp( finfo.name, "." ) != 0 && strcmp( finfo.name, ".." ) != 0 )
                {
                    if ( StringUtil::match( strFileName, filter ) )
                    {
                        files.push_back( strFileName );
                    }

                    if ( depth > 0 )
                    {
                        listAllFiles( strFileName, files, depth - 1, filter );
                    }
                }
            }
            else
            {
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
            //H_LOG_NAME_DEBUG( "FileUtil", log.str() );
            return;
        }

        for ( int i = 0; i < n; ++i )
        {
            StringA strFileName = osl::FileUtil::concatenatePath( strDirName, namelist[i]->d_name );

            if ( namelist[i]->d_type == DT_DIR )
            {
                if ( strcmp( namelist[i]->d_name, "." ) != 0 && strcmp( namelist[i]->d_name, ".." ) != 0 )
                {
                    if ( StringUtil::match( strFileName, filter ) )
                    {
                        files.push_back( strFileName );
                    }

                    if ( depth > 0 )
                    {
                        listAllFiles( strFileName, files, depth - 1, filter );
                    }
                }
            }
            else
            {
                if ( StringUtil::match( strFileName, filter ) )
                {
                    files.push_back( strFileName );
                }
            }
        }

        free( namelist );

#endif

    }

};//namespace
