//! \file   HString.h
//! \brief  标准库basic_string包装,以及扩展


#ifndef QOSLIB_STRING_
#define QOSLIB_STRING_

#include "osl/include/stl_container.h"

#define H_STD_STRING

namespace osl
{
    struct STLStringAName
    {
        static const char* NAME()
        {
            return "StringA";
        }
    };
    struct STLStringWName
    {
        static const char* NAME()
        {
            return "StringW";
        }
    };

    //! String class which receive NULL value.
    template < class _Elem,
             class _Traits,
             class _Ax >
    class Basic_String : public std::basic_string< _Elem, _Traits, _Ax >
    {
    public:
        typedef std::basic_string< _Elem, _Traits, _Ax > _BaseType;

        Basic_String() {};

        Basic_String( const typename _BaseType::value_type* _Ptr, typename _BaseType::size_type _Count )
        {
            if( _Ptr )
            {
                assign( _Ptr, _Count );
            }
        }

        Basic_String(
            const typename _BaseType::value_type* _Ptr
        )
        {
            if( _Ptr )
            {
                assign( _Ptr );
            }
        }

        Basic_String(
            const Basic_String& _Right,
            typename _BaseType::size_type _Roff,
            typename _BaseType::size_type _Count = _BaseType::npos
        ) : _BaseType( _Right, _Roff, _Count ) {};

        Basic_String(
            const _BaseType& _Right
        )
        {
            if( _Right.length() )
            {
                assign( _Right.c_str(), _Right.length() );
            }
        }

        Basic_String(
            typename _BaseType::size_type _Count,
            typename _BaseType::value_type _Ch
        ) : _BaseType( _Count, _Ch ) {};

        template<class _It>
        Basic_String(
            _It _First,
            _It _Last
        ): _BaseType( _First, _Last ) {};

        Basic_String(const std::basic_string< _Elem >& ohs)
        {
            assign( ohs.c_str(), ohs.length() );
        }
            
    };

#ifdef H_STD_STRING

    typedef std::wstring StringW;
    typedef std::string StringA;

    typedef std::wstringstream StringStreamW;
    typedef std::wostringstream OStringStreamW;
    typedef std::wistringstream IStringStreamW;

    typedef std::stringstream StringStreamA;
    typedef std::ostringstream OStringStreamA;
    typedef std::istringstream IStringStreamA;

#else

    typedef Basic_String<wchar_t, std::char_traits<wchar_t>, osl::HSTLAllocator<wchar_t, STLStringWName> >    	StringW;
    typedef Basic_String<char,    std::char_traits<char>,    osl::HSTLAllocator<char, STLStringAName> >		    StringA;

    typedef std::basic_stringstream<wchar_t,  std::char_traits<wchar_t>, osl::HSTLAllocator<wchar_t, STLStringWName> >	StringStreamW;
    typedef std::basic_ostringstream<wchar_t, std::char_traits<wchar_t>, osl::HSTLAllocator<wchar_t, STLStringWName> >	OStringStreamW;
    typedef std::basic_istringstream<wchar_t, std::char_traits<wchar_t>, osl::HSTLAllocator<wchar_t, STLStringWName> >	IStringStreamW;

    typedef std::basic_stringstream<char,  std::char_traits<char>, osl::HSTLAllocator<char, STLStringAName> >	StringStreamA;
    typedef std::basic_ostringstream<char, std::char_traits<char>, osl::HSTLAllocator<char, STLStringAName> >	OStringStreamA;
    typedef std::basic_istringstream<char, std::char_traits<char>, osl::HSTLAllocator<char, STLStringAName> >	IStringStreamA;

#endif

	template<class _Elem,class _Traits,class _Alloc> 
	bool operator == (
		const Basic_String<_Elem, _Traits, _Alloc>& _Left,
		const Basic_String<_Elem, _Traits, _Alloc>& _Right)
	{	// test for string equality
		if ( _Left.length() != _Right.length() )
		{
			return false;
		}
		return (_Left.compare(_Right) == 0);
	}
	template<class _Elem,class _Traits,class _Alloc> 
	bool operator != (
		const Basic_String<_Elem, _Traits, _Alloc>& _Left,
		const Basic_String<_Elem, _Traits, _Alloc>& _Right)
	{
		return !( _Left == _Right );
	}




#ifdef H_WIDE_CHAR

    typedef StringW String;
    typedef StringStreamW   StringStream;
    typedef OStringStreamW OStringStream;
    typedef IStringStreamW IStringStream;

#else

    typedef StringA               String;
    typedef StringStreamA   StringStream;
    typedef OStringStreamA OStringStream;
    typedef IStringStreamA IStringStream;

#endif

    // vector
    H_DEF_VECTOR( osl::String, StringVector );
    H_DEF_VECTOR( osl::StringA, StringAVector );
    H_DEF_VECTOR( osl::StringW, StringWVector );

    // lists

    H_DEF_LIST( osl::String,  StringList );
    H_DEF_LIST( osl::StringA, StringAList );
    H_DEF_LIST( osl::StringW, StringWList );

    // sets
    H_DEF_SET( osl::String, StringSet );
    H_DEF_SET( osl::StringA, StringASet );
    H_DEF_SET( osl::StringW, StringWSet );

    H_DEF_MAP( osl::StringA, osl::StringA, StringAStringAMap );





    namespace detail
    {
        template<class T>
        size_t internal_hash_value( const T& _Keyval )
        {
            size_t ret = 2166136261U;

            for ( typename T::const_iterator it = _Keyval.begin(); it != _Keyval.end(); ++it )
            {
                ret = 16777619U * ret ^ static_cast<size_t>( *it );
            }
            return ret;
        }
    }
};


// If we're using the GCC 3.1 C++ Std lib
#if (defined(H_COMPILER_GNUC) && H_COMP_VER >= 310)

#include <ext/hash_map>
namespace __gnu_cxx
{

    template<>
    struct hash< osl::StringA >
    {
        size_t operator()( const osl::String& _Keyval ) const
        {
            return osl::detail::internal_hash_value( _Keyval );
        }
    };

    template<>
    struct hash< osl::StringW >
    {
        size_t operator()( const osl::StringW& _Keyval ) const
        {
            return osl::detail::internal_hash_value( _Keyval );
        }
    };
}

#else

namespace osl
{
    inline size_t hash_value( const StringA& _Keyval )
    {
        return osl::detail::internal_hash_value( _Keyval );
    }

    inline size_t hash_value( const StringW& _Keyval )
    {
        return osl::detail::internal_hash_value( _Keyval );
    }
};

#endif


namespace std
{
    inline void swap( osl::StringA& l , osl::StringA& r)
    {
        l.swap( r );
    }
}




namespace osl {

class Slice {
 public:
  // Create an empty slice.
  Slice() : data_(""), size_(0) { }

  // Create a slice that refers to d[0,n-1].
  Slice(const char* d, size_t n) : data_(d), size_(n) { }

  // Create a slice that refers to the contents of "s"
  Slice(const std::string& s) : data_(s.data()), size_(s.size()) { }

  // Create a slice that refers to s[0,strlen(s)-1]
  Slice(const char* s) : data_(s), size_(strlen(s)) { }

  // Return a pointer to the beginning of the referenced data
  const char* data() const { return data_; }

  // Return the length (in bytes) of the referenced data
  size_t size() const { return size_; }

  // Return true iff the length of the referenced data is zero
  bool empty() const { return size_ == 0; }

  // Return the ith byte in the referenced data.
  // REQUIRES: n < size()
  char operator[](size_t n) const {
    assert(n < size());
    return data_[n];
  }

  // Change this slice to refer to an empty array
  void clear() { data_ = ""; size_ = 0; }

  // Drop the first "n" bytes from this slice.
  void remove_prefix(size_t n) {
    assert(n <= size());
    data_ += n;
    size_ -= n;
  }

  // Return a string that contains the copy of the referenced data.
  StringA toString() const { return std::string(data_, size_); }

  // Three-way comparison.  Returns value:
  //   <  0 iff "*this" <  "b",
  //   == 0 iff "*this" == "b",
  //   >  0 iff "*this" >  "b"
  int compare(const Slice& b) const;

  // Return true iff "x" is a prefix of "*this"
  bool starts_with(const Slice& x) const {
    return ((size_ >= x.size_) &&
            (memcmp(data_, x.data_, x.size_) == 0));
  }

 private:
  const char* data_;
  size_t size_;

  // Intentionally copyable
};

inline bool operator==(const Slice& x, const Slice& y) {
  return ((x.size() == y.size()) &&
          (memcmp(x.data(), y.data(), x.size()) == 0));
}

inline bool operator!=(const Slice& x, const Slice& y) {
  return !(x == y);
}

inline int Slice::compare(const Slice& b) const {
  const int min_len = (size_ < b.size_) ? size_ : b.size_;
  int r = memcmp(data_, b.data_, min_len);
  if (r == 0) {
    if (size_ < b.size_) r = -1;
    else if (size_ > b.size_) r = +1;
  }
  return r;
}

}  // namespace osl





#endif//end of file
