#ifndef _OSLIB_UTILITY_H_
#define _OSLIB_UTILITY_H_

#include "osl/include/inner_pre.h"
#include "osl/include/string_ext.h"

namespace osl
{
    class _EXPORT_OSLIB Util
    {
    public:
        static bool equals( f64 x, f64 y, f64 tolerance = 0.000001 )
        {
            if ( x - y > - tolerance && x - y < tolerance )
            {
                return true;
            }

            return false;
        }

        enum EqualElememt
        {
            E_LESS_EQUAL,
            E_EQUAL,
            E_LARGER_EQUAL
        };

        //! \brief compare tow double
        //! \param E_LESS_EQUAL if x only less than y a little, this function will return true
        //! \param E_LARGER_EQUAL if x only larger than y a little, this function will return true
        //! \param E_EQUAL the same as equals( f64 x, f64 y, f64 tolerance = 0.000001 )
        static bool equals( f64 x, f64 y, EqualElememt ee, f64 tolerance = 0.000001 )
        {
            assert( tolerance > 0 );
            switch( ee )
            {
            case E_LESS_EQUAL:
                if ( x - y > - tolerance && x - y <= 0 )
                {
                    return true;
                }
                break;
            case E_LARGER_EQUAL:
                if ( x - y < tolerance && x - y >= 0 )
                {
                    return true;
                }
                break;
            case E_EQUAL:
                return equals( x, y, tolerance );
                break;
            default:
                assert( false );
                break;
            }

            return false;
        }


        static bool readFileLine( const StringA& strFileName, StringAList& lines )
        {
            return readFileLine( strFileName.c_str(), lines );
        }

        //! Extract strings from the a file line-by-line,
        //! every line content as a list element will be inserted to a list.
        static bool readFileLine( const char* szFileName, StringAList& lines );

        
        //! \brief This function calculate the next power of two higher than or equal to a given number. i.e. round a number up to the next power of two
        //! i.e. : 8 -> 8 , 7 -> 8, 31 -> 32, 33 -> 64
        //! \param originalvalue
        //! \return u32
        static u32 roundUpToNextPow2( u32 originalvalue )
        {
            originalvalue -= 1;
            originalvalue |= (originalvalue >> 1);
            originalvalue |= (originalvalue >> 2);
            originalvalue |= (originalvalue >> 4);
            originalvalue |= (originalvalue >> 8);
            originalvalue |= (originalvalue >> 16);

            return originalvalue + 1;
        }

        //! \brief Limit a number in a specified range
        //! \param tmin
        //! \param tmax
        //! \param value
        //! \return T
        template<typename T>
        static T getValueInRange( T tmin, T tmax, T value )
        {
            if ( tmax > tmin )
            {
                if ( value < tmin )
                {
                    return tmin;
                }
                else if ( value > tmax )
                {
                    return tmax;
                }
                else
                {
                    return value;
                }
            }
            else
            {
                if ( value < tmax )
                {
                    return tmax;
                }
                else if ( value > tmin )
                {
                    return tmin;
                }
                else
                {
                    return value;
                }
            }
        }

        //! \brief Walk the directory and get a list of files, excluded directory.
        //! \param strDirName The directory name
        //! \param files[out] The list of files are stored here. The file name is with the full path name(include the directory name)
        //! \param recursively Whether walk the subdirectories.
        //! \param filter Pattern to match against; which can include simple '*' wildcards
        static void getFiles( const osl::StringA& strDirName, StringAList& files, bool recursively = true, const osl::StringA& filter = "*.*" );
        static void listFiles( const osl::StringA& strDirName, StringAList& files, bool recursively = true, const osl::StringA& filter = "*.*" )
        {
            return getFiles( strDirName, files, recursively, filter );
        }

    };




}//end of namespace osl

#endif

