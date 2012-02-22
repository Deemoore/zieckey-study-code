#ifndef _OSLIB_FILE_UTIL_H_
#define _OSLIB_FILE_UTIL_H_

#include "osl/include/string_ext.h"

#ifdef H_OS_WINDOWS
#   include <direct.h>
#endif

namespace osl
{


    //! File access utility. Provide many help methods to make it easy to do some file operation.
    //! \remark The instance is created when the module is initialized.
    class _EXPORT_OSLIB FileUtil
    {
        H_ALLOCRAW_OPERATORS( FileUtil );
    public:
        //! Query whether the file name is a directory.
        //! \param strFileName name of the file. if end with '/', it is a directory, else
        //! is a file.
        static bool isDirectoryName( const StringA& strFileName );

        //! Query whether the file name is a valid directory. e.g. ".", ".." are invalid
        //! directory name.
        static bool isValidDirName( const char* szName );

        //! Query whether strFileName is a absolute path.
        static bool isAbsolutePathName( const StringA& strPathName );

        //! Gets absolute path name.
        //! \param strPathName If already is a absolute path name return it, else build
        //! absolute path name with current path.
        static StringA getAbsolutePathName( const StringA& strPathName );

		//! Build absolute path name.
		//! ( "../test1/test1-1", "c:/parentname" )==> "c:/parentname/../test1/test1-1".
		//! ( "f:/test1/test1-1", "c:/parentname" )==> "f:/test1/test1-1".
		//! \param strPathName Path name to build new absolute path name.
		//! \param strDefaultParentDir Parent directory to make new path.
		static StringA buildAbsolutePathName( const StringA& strPathName, const StringA& strDefaultParentDir );

		//! Remove reduant "../../" from path name."c:/te1/t2/t2-1/../t3/t3-1" ==> "c:/te1/t2/t3/t3-1"
		static StringA compactPathName( const StringA& strPathName );

        //! Gets relative path name. "e:/test/b1/aaa.txt" - "e:/test" = "b1/aa.txt"
        //! \param strRelPathName Relative path name.
        //! \param strFullPathName  MUST be an absolute full path, otherwise behavior is undefined
        //! \param strPartPathName  MUST be an absolute full path, otherwise behavior is undefined
        //! \return false if strPartPathName does not match strFullPathName.
        static bool getRelativePathName( StringA& strRelPathName, const StringA& strFullPathName, const StringA& strPartPathName );

        /** Convert "\" in the file name to "/".
        *  @param fileName [in/out] File name to convert.
        */
        static void convertFileName( StringA& fileName );
        static void convertFileName( StringW& fileName );


        //! \brief splitting a fully qualified filename into file name and base path dir.
        //! \param qualifiedName Path is standardized as in <code>standardisePath</code>
        //! \param strFileName[out]
        //! \param strBasePathDir[out]
        //! \param bWithEndSlash[in] true, End of the string With a SLASH "/".
        static void splitFileName( const StringW& qualifiedName,
                                   StringW& strFileName, StringW& strBasePathDir, bool bWithEndSlash = false );
        static void splitFileName( const StringA& qualifiedName,
                                   StringA& strFileName, StringA& strBasePathDir, bool bWithEndSlash = false );



        //! Concatenate tow path into one, and return it.
        static StringA concatenatePath( const StringA& prefix, const StringA& postfix );
        static StringW concatenatePath( const StringW& prefix, const StringW& postfix );


        //! \brief Method for standardizing paths - use forward slashes "/" only
        //! \param strOrignal
        //! \param bWithEndSlash
        //!         true, End of the string With a SLASH "/".
        //!         false, without a SLASH "/" at the end of the string
        //! \return osl::StringA
        static StringA standardisePath( const StringA& strOrignal, bool bWithEndSlash = true );
		static StringW standardisePath( const StringW& strOrignal, bool bWithEndSlash = true );
		static StringA canonicalizePath( const StringA& strOrignal, bool bWithEndSlash = true )
		{
			return standardisePath( strOrignal, bWithEndSlash );
		}
		static StringW canonicalizePath( const StringW& strOrignal, bool bWithEndSlash = true )
		{
			return standardisePath( strOrignal, bWithEndSlash );
		}


        //! \brief Gets path's parent directory name. The path can be a normal file or a directory
        //! e.g. "D:\test\aab.jpg" ==> "D:/test/" or "D:/test"
        //! e.g. "D:/test/abc/" ==> "D:/test/" or "D:/test"
        //! \warning The return parent director name is suitable for <code>standardisePath</code>
        //!         That means it uses forward slash "/" as path separator
        //! \note It take care of relative path.
        //! \param bWithEndSlash
        //!         true, End of the string With a SLASH "/".
        //!         false, without a SLASH "/" at the end of the string
        //! \return StringA,
        static StringA getParentDirName( const StringA& strFileName, bool bWithEndSlash = true );

        //! Gets file name without path..
        //! e.g. "D:/test/aab.jpg" ==> "aab.jpg"
        static StringA getFileName( const StringA& strFileName );

        //! Gets base file name. the file extension will be removed.
        //! e.g. "D:/test/aab.jpg" ==> "aab"
        static StringA getFileNameWithNoExt( const StringA& strFileName );

        //! Gets file name extension. If can not find the last '.', null string
        //! will be returned. e.g. "D:/test/aab.jpg" ==> "jpg"
        //!
        static StringA getFileNameExtension( const StringA& strFileName );

        //! Gets file path name without end '/'.
        //! e.g. "D:/test/aab.jpg" ==> "D:/test"
        static StringA getFileDirName( const StringA& strFileName );



        //! Quickly remove file or directory from local file system.
        //! \param strFileName if end with '/', it is a directory, all the children will be
        //! remove, else is a file and the file will be removed.
        //! \return bool True if successfully.
        static bool removeFSFile( const StringA& strFileName ) ;


        //! \brief Remove the empty directory. If it is not empty or it is not directory, we do nothing and just return true.
        //! \remark Empty directory definition: it doesn't has any normal file.
        //! e.g. /home/a_dir/b_dir/c_dir
        //!     Condition: c_dir has no files in it, and b_dir only has c_dir and a_dir only has b_dir
        //!     If we call removeFSDirIfEmpty( "/home/a_dir/b_dir", false ), them b_dir will be deleted and its child c_dir deleted
        //!     If we call removeFSDirIfEmpty( "/home/a_dir/b_dir", true ), them a_dir, b_dir, c_dir will all be deleted.
        //! \param bRecurcively True, we will delete its parent directory if its parent directory is also empty
        //! \return bool True if successfully.
        static bool removeFSDirIfEmpty( const StringA& strDirName, bool bRecursivelyDeleteEmptyParentDir = true );

        //! Make directory hierarchy in local file system.
        //! Its behavior is similar with the command 'mkdir -p'
        //! \param strDirPath Absolute directory file name. e.g. '/home/weizili/test'
        //! \return true if successfully
        static bool makeFSDir( const StringA& strDirPath );
        static bool mkdir( const StringA& strDirPath ) { return makeFSDir(strDirPath); }

        static bool rmdir( const StringA& strDirName );
        static bool rmdir( const char* strDirName );


        //! Determines if a file exists and could be opened. 
        //! \note The file CAN be a directory
        /** \param filename is the string identifying the file which should be tested for existence.
        \return Returns true if file exists, and false if it does not exist or an error occurred. */
        static bool isFSFileExist( const osl::StringA& strFileName );
        static bool exists( const osl::StringA& strFileName ) { return isFSFileExist(strFileName); }


        //! \brief copy a file to another place. This function has the same feature like DOS Command 'copy' or Linux Command 'cp'
        //! \warning If the destination file is exist, it will be replaced.
        //! \warning strDestFile MUST BE a file, NOT a directory
        //! \param strSrcFile The source file
        //! \param strDestFile The target file
        //! \param bOverride True, this will override the old existent file.
        //! \return bool True if successfully
        static bool copyFSFile( const osl::StringA& strSrcFile, const osl::StringA& strDestFile, bool bOverride = true  ) ;

        //! \brief Query whether the given path is a directory.
        static bool isDirectory( const char* strFileName );
        static bool isDirectory( const StringA& strFileName );

		//! \brief Walk the directory and get a list of files, excluded directory.
		//! \param strDirName The directory name
		//! \param files[out] The list of files are stored here. The file name is with the full path name(include the directory name)
		//! \param recursively Whether walk the subdirectories.
		//! \param filter Pattern to match against; which can include simple '*' wildcards
		static void getFiles( const StringA& strDirName, StringAList& files, bool recursively = true, const StringA& filter = "*" );
		static void listFiles( const StringA& strDirName, StringAList& files, bool recursively = true, const StringA& filter = "*" )
		{
			return getFiles( strDirName, files, recursively, filter );
		}

        //! \brief Walk the directory and get a list of all kinds of files, included directory.
        //! \param strDirName The directory name
        //! \param files[out] The list of files are stored here. The file name is with the full path name(include the directory name)
        //! \param depth The depth to walk the subdirectories. 0 means only walk the top dir strDirName
        //! \param filter Pattern to match against; which can include simple '*' wildcards
        static void listAllFiles( const StringA& strDirName, StringAList& files, int depth = 0, const StringA& filter = "*" );


        //! Extract strings from the a file line-by-line,
        //! every line content as a list element will be inserted to a list.
        static bool readFileLine( const StringA& strFileName, StringAList& lines )
        {
            return readFileLine( strFileName.c_str(), lines );
        }
        static bool readFileLine( const char* szFileName, StringAList& lines );

        /**
         * @brief Write the data into a file. 
         *  The file is created if it does not exist, otherwise it is truncated
         * @param const char* filepath - The file path where the data is stored
         * @param const void* content - The file content
         * @param const size_t len - The length of the content
         * @return true if successfully
         */
        static bool writeToFile( const char* filepath, const void* content, const size_t len );
        static bool writeToFile( const StringA& filepath, const void* content, const size_t len );

    private:

        //! Only visible for osl::Initializer.
        FileUtil();
        ~FileUtil();

        //! convert file match pattern to perl regular express pattern.
        StringA filePatternToPerlRegex( const StringA& strFilePattern );

    };

};//namespace osl

#include "osl/include/file_util.inl.h"

#endif //#ifndef _OSLIB_FILE_UTIL_H_


