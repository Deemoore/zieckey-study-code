/****************************** Module Header ********************************\
    Name: auto_delete.h
 Created: 2012/01/07 7:1:2012 17:23
  Author: weizili

 Purpose: 
\*****************************************************************************/

#ifndef OSLIB_AUTO_DELETE_H_
#define OSLIB_AUTO_DELETE_H_

namespace osl
{
    namespace ext
    {
        /**********************************************************************
         *   usage example 1£º
         *       <code>
         *       char* ps = new char[1024];
         *       stdext::auto_delete<char> ps_auto_deleted(ps);
         *       </code>
         *
         *   usage example 2£º
         *       <code>
         *       struct student 
         *       { 
         *           long no;
         *       };
         *
         *       template<> inline
         *       auto_delete< student >::~auto_delete()
         *       {
         *           if ( ptr_ref_to_be_deleted_ )
         *           {
         *               delete ptr_ref_to_be_deleted_;
         *               ptr_ref_to_be_deleted_ = NULL;
         *           }
         *       }
         *       </code>
         *********************************************************************/

        //! Name: auto_delete
        template<class T>
        struct auto_delete
        {
            T*& ptr_ref_to_be_deleted_;
            auto_delete( T*& pointer )
                : ptr_ref_to_be_deleted_( pointer )
            {
            }

            ~auto_delete()
            {
                if ( ptr_ref_to_be_deleted_ )
                {
                    delete ptr_ref_to_be_deleted_;
                    ptr_ref_to_be_deleted_ = 0;
                }
            }

            void noop() {}
        private:
            auto_delete(const auto_delete&);
            auto_delete&operator=(const auto_delete&);
        };

        template<class T>
        struct auto_delete<T*>; //! \note Leave it be. Do not write any implementation



        //! Name: auto_delete
        template<class T>
        struct auto_free
        {
            T*& ptr_ref_to_be_deleted_;
            auto_free( T*& pointer )
                : ptr_ref_to_be_deleted_( pointer )
            {
            }

            ~auto_free()
            {
                if ( ptr_ref_to_be_deleted_ )
                {
                    free(ptr_ref_to_be_deleted_);
                    ptr_ref_to_be_deleted_ = 0;
                }
            }

            void noop() {}
        private:
            auto_free(const auto_free&);
            auto_free&operator=(const auto_free&);
        };

        template<class T>
        struct auto_free<T*>; //! \note Leave it be. Do not write any implementation

    }// end of namespace ext
} // end of namespace osl


#endif //end of OSLIB_AUTO_DELETE_H_



