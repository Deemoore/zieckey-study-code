#ifndef NETPROTO_STD_STREAM_
#define NETPROTO_STD_STREAM_

#include "netproto/include/inner_pre.h"
#include "netproto/include/data_stream.h"

namespace npp
{

    template < class _Elem,
             class _Traits >
    class MemoryStreamBuf : public std::basic_streambuf<_Elem, _Traits>
    {
        MemoryDataStreamPtr m_MemDataStream;
        typedef typename std::basic_streambuf<_Elem, _Traits>::int_type __SizeType;
    public:
        MemoryStreamBuf( MemoryDataStream* pString ): m_MemDataStream( pString )
        {
        }
    protected:

        /// Following for writing.

        //output stream buffer
        virtual __SizeType overflow( __SizeType val )
        {
            m_MemDataStream->write( &val , sizeof( _Elem ) );

            return val;
        }
        //output stream buffer
        virtual std::streamsize xsputn( const _Elem *_Ptr, std::streamsize _Count )
        {
            m_MemDataStream->write( _Ptr , _Count * sizeof( _Elem ) );
            return _Count;
        }

        /// Following for read.
        //intput stream
        virtual __SizeType underflow()
        {
            _Elem elm = _Elem();

            if ( m_MemDataStream->read( &elm , sizeof( elm ) ) )
            {
                m_MemDataStream->seekg( - ( s32 )sizeof( elm ) );
                return elm;
            }
            else
            {
                return _Traits::eof();
            }
        }
        virtual __SizeType uflow()
        {
            _Elem elm = _Elem();

            if ( m_MemDataStream->read( &elm , sizeof( elm ) ) )
            {

                return elm;
            }
            else
            {
                return _Traits::eof();
            }
        }
        virtual std::streamsize xsgetn( _Elem * _Ptr, std::streamsize _Count )
        {
            if ( m_MemDataStream->read( _Ptr , sizeof( _Elem )*_Count ) )
            {
                return _Count;
            }
            else
            {
                return 0;
            }
        }
    };


    template < class _Elem,
             class _Traits >
    class MemoryStream : public std::basic_iostream< _Elem , _Traits >
    {
        typedef std::basic_iostream< _Elem , _Traits > BaseClass;
        typedef MemoryStreamBuf<_Elem, _Traits> _Mysb;
    public:
        MemoryStream ( MemoryDataStream* pString = NULL )
            : BaseClass( &mStreamBuf )
            , mStreamBuf( pString ? pString : H_NEW MemoryDataStream )
        {
        }
    protected:
        _Mysb mStreamBuf;
    };


    typedef MemoryStream<char, std::char_traits<char> >  MemoryByteStream;

};//namespace

#endif

