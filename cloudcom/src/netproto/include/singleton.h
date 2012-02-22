/****************************** Module Header ********************************\
    Name: singleton.h
 Created: 2012/01/08 8:1:2012 1:28
  Author: weizili

 Purpose: 
\*****************************************************************************/

#ifndef OSLIB_SINGLETON_H_
#define OSLIB_SINGLETON_H_

#include <assert.h>

namespace osl
{
    /**
     * Usage:
     *  <code>
     *      //log_manager.h
     *      class LogManager : public Singleton<LogManager>
     *      {}
     *
     *      //log_manager.cpp
     *      template<> LogManager* Singleton<LogManager>::ms_Singleton = NULL;
     *  </code>
     */

    /** Template class for creating single-instance global classes.  */
    template <typename T> class Singleton
    {
    public:
        static T& getSingleton( void )
        {
            //assert( ms_Singleton );
            return ( *ms_Singleton );
        }

        static T* getSingletonPtr( void )
        {
            return ms_Singleton;
        }

    protected:
        Singleton( void )
        {
            assert(0 == ms_Singleton);
            ms_Singleton = static_cast< T* >( this );
        }

        ~Singleton( void )
        {
            //assert( ms_Singleton );
            ms_Singleton = 0;
        }

    protected:
        static T* ms_Singleton;
    };
};//namespace

#endif
