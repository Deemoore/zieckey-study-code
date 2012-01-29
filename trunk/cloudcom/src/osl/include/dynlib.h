#ifndef OSLIB_DYNLIB_H_
#define OSLIB_DYNLIB_H_

#include "osl/include/config.h"

#if H_PROVIDE_DLL_MANAGER

#include "osl/include/inner_pre.h"
#include "osl/include/object.h"
#include "osl/include/string_ext.h"

namespace osl
{
#ifdef H_OS_WINDOWS
#    define DYNLIB_HANDLE         HMODULE
#elif defined( H_OS_LINUX )
#    define DYNLIB_HANDLE         void*
#else
#    define DYNLIB_HANDLE         void*
#endif

    //! Dynamic library. It is used load and find symbol in the library.
    //! \remark You should keep the object alive before unload the loaded library.
    class _EXPORT_OSLIB DynLib : public Object
    {
        H_ALLOC_OBJECT( DynLib )
    public:
        //! Constructor
        //! \param strName  Full patch name for the library. e.g. "e:/project/hph/bin/test.dll", "/root/bin/test.a"
        DynLib( const StringA& strFullPath );

        //! Deconstructor.
        ~DynLib();

        //! Actively load the library.
        //! \return false if failed to load.
        bool load();

        //! Unload the library.
        //! \return false if failed to unload
        bool unload();

        //! Query whether the library has been loaded.
        bool isLoaded();

        //! Get full path name of the library
        const StringA& getName( void ) const
        {
            return m_strFullPath;
        }

        //! Gets symbol in the library.
        //! \return NULL if find nothing.
        void* getSymbol( const String& strName );


        //! Gets the last loading error. It is used keep error reason when failed to
        //! load or unload library.
        const StringA& getLastError( void )const
        {
            return m_strLastError;
        }

    private:

        StringA            m_strFullPath;

        /// Handle to the loaded library.
        DYNLIB_HANDLE            m_hInst;

        StringA           m_strLastError;   //! error string.


    private:

        //! Generate library load error. It generated from system.
        StringA dynlibError();

    };

    typedef RefPtr<DynLib>   DynLibPtr;

};//namespace
#endif //#if H_PROVIDE_DLL_MANAGER

#endif //#ifndef OSLIB_DYNLIB_H_
