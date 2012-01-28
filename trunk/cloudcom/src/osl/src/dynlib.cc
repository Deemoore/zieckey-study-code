#include "osl/include/inner_pre.h"

#if H_PROVIDE_DLL_MANAGER

#include "osl/include/object.h"
#include "osl/include/string_ext.h"
#include "osl/include/string_util.h"
#include "osl/include/dynlib.h"

#ifdef H_OS_LINUX
#include <dlfcn.h>
#endif

namespace osl
{

#ifdef H_OS_WINDOWS
#    define DYNLIB_LOAD( a )      LoadLibraryA( a )
#    define DYNLIB_GETSYM( a, b ) GetProcAddress( a, b )
#    define DYNLIB_UNLOAD( a )    !FreeLibrary( a )
#elif defined( H_OS_LINUX )
#    define DYNLIB_LOAD( a )      dlopen( a, RTLD_LAZY | RTLD_LOCAL)
#    define DYNLIB_GETSYM( a, b ) dlsym( a, b )
#    define DYNLIB_UNLOAD( a )    dlclose( a )
#else
#    define DYNLIB_LOAD( a )      dlopen( a, RTLD_LAZY | RTLD_LOCAL)
#    define DYNLIB_GETSYM( a, b ) dlsym( a, b )
#    define DYNLIB_UNLOAD( a )    dlclose( a )
#endif


    //------------------------------------------------------
    
    //-----------------------------------------------------------------------
    DynLib::DynLib( const String& strFullPath )
        : m_strFullPath( strFullPath )
    {
        m_hInst = NULL;
    }

    //-----------------------------------------------------------------------
    DynLib::~DynLib()
    {
    }
    //-----------------------------------------------------------------------
    bool DynLib::isLoaded()
    {
        return m_hInst == NULL ? false : true;
    }
    //-----------------------------------------------------------------------
    bool DynLib::load()
    {
        // Log library load
        //LogManager::getSingleton().logMessage("Loading library " + mName);

        StringA strName = m_strFullPath;

#ifdef H_OS_WINDOWS
        m_hInst = ( DYNLIB_HANDLE )::LoadLibraryA( strName.c_str() );
#else //H_OS_LINUX
        m_hInst = ( DYNLIB_HANDLE )::dlopen( strName.c_str(), RTLD_LAZY | RTLD_LOCAL);
#endif

        if( m_hInst )
        {
            return true;
        }


        OStringStreamA strTip;
        strTip << __func__ << " : Load dynamic library " 
            << m_strFullPath << " failed. "
            << "Error message : " << dynlibError();
        m_strLastError = strTip.str();
        return false;
    }

    //-----------------------------------------------------------------------
    bool DynLib::unload()
    {
        if ( !m_hInst )
        {
            OStringStreamA strTip;
            strTip 
                << __PRETTY_FUNCTION__ 
                << " Could not unload dynamic library " << m_strFullPath
                << ". maybe it haven't loaded yet, because m_hInst=NULL";
            m_strLastError = strTip.str();
            return false;
        }

#ifdef H_OS_WINDOWS
        if ( ::FreeLibrary(m_hInst) ) // If the function FreeLibrary() succeeds, the return value is nonzero.
        {
            return true;
        }
#else // H_OS_LINUX
        if ( 0 == dlclose( m_hInst ) ) //The function dlclose() returns 0 on success, and non-zero on error.
        {
            return true;
        }
#endif
        


        OStringStreamA strTip;
        strTip << __func__ << " : Unload dynamic library " 
            << m_strFullPath << " failed. "
            << "Error message : " << dynlibError();
        m_strLastError = strTip.str();
        return false;
    }

    //-----------------------------------------------------------------------
    void* DynLib::getSymbol( const String& strName )
    {
        void* rp = NULL;

#ifdef H_OS_WINDOWS
        rp = (void*)::GetProcAddress( m_hInst, strName.c_str() );
#else
        rp = (void*)::dlsym( m_hInst, strName.c_str() );
#endif

        if ( rp == NULL )
        {
            OStringStreamA strTip;

            strTip << __func__ 
                << " : Could not get the symbol : " << strName
                << ". Error Message : " << dynlibError();

            m_strLastError = strTip.str();
        }

        return rp;
    }

    //-----------------------------------------------------------------------
    StringA DynLib::dynlibError()
    {
#ifdef H_OS_WINDOWS
        LPVOID lpMsgBuf;
        FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            GetLastError(),
            MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ),
            ( LPTSTR ) &lpMsgBuf,
            0,
            NULL
        );
        String ret = ( char* )lpMsgBuf;
        // Free the buffer.
        LocalFree( lpMsgBuf );
        return ret;
#else //
        return String( dlerror() );
#endif
    }

}
#endif //#if H_PROVIDE_DLL_MANAGER

