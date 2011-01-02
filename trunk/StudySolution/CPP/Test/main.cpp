// #include<iostream>
// #include<string>
// #include<windows.h>
// #include<io.h>
// #include <assert.h>
// 
// bool ZgIsFileExist( const char* p_chName )
// {
//     if( !p_chName )
//     {
//         return false;
//     }
// 
//     intptr_t hf;
//     _finddata_t fd;
// 
//     hf = _findfirst( p_chName, &fd );
// 
//     if( hf == -1 )
//     {
//         return false;
//     }
// 
//     if( !( fd.attrib & _A_SUBDIR ) )
//     {
//         _findclose( hf );
//         return true;
//     }
// 
//     for( ;; )
//     {
//         assert( 0 );
// 
//         if( _findnext( hf, &fd ) )
//         {
//             _findclose( hf );
//             return false;
//         }
// 
//         if( !( fd.attrib & _A_SUBDIR ) )
//         {
//             _findclose( hf );
//             return true;
//         }
//     }
// 
//     return false;
// }
// 
// int main()
// {
//     /*        HANDLE h = CreateFile( "test.cpp" , 0 , 0 , NULL , OPEN_EXISTING , 0 , 0 );
// 
//     if( INVALID_HANDLE_VALUE != h )
//     {
//     CloseHandle( h );
//     puts( "文件存在" );
//     }
//     else
//     {
//     puts( "文件不存在" );
//     }
//     */
// 
//     DWORD begin = GetTickCount( );
// 
//     for( int i = 0; i < 1000 * 100 ; i++ )
//     {
//         bool b = ZgIsFileExist( "xx.cpp" );
// 
//         if( b )
//         {
//             //puts( "文件存在" );
//         }
//         else
//         {
//             //puts( "文件不存在" );
//         }
//     }
// 
//     printf( "%d" , GetTickCount() - begin );
//     system( "pause" );
//     return 0;
// }


#include <fstream>
#include <sstream>
using namespace std;

int main()
{
    const int FILE_COUNT = 2048;
    for ( int i = 1; i <= FILE_COUNT; ++i ) // create FILE_COUNT files.
    {
        fstream file;
        ostringstream filename;
        filename << i << ".txt";
        file.open( filename.str().c_str(), ios_base::out );

        for ( int j = 0; j < i; ++j )
        {
            file << "ABCDEFGHIJ"; //write 10 bytes.
        }

        file.flush();
        file.close();
    }

    return 0;
}
