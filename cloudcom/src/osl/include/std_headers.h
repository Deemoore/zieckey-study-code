//! \file   HStdHeaders.h
//! \brief  stl头文件包含
//!	\author Tian Shengcai

#ifndef QOSLIB_STDHEADER_
#define QOSLIB_STDHEADER_

#include "osl/include/platform_micros.h"

#ifdef __BORLANDC__
#ifndef __STD_ALGORITHM
#	define __STD_ALGORITHM
#endif
#endif


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// STL containers
#include <vector>
#include <map>
#include <string>
#include <set>
#include <list>
// #include <deque>
// #include <queue>
// #include <bitset>
#include <typeinfo>
#include <stdexcept>
// Note - not in the original STL, but exists in SGI STL and STLport
#if (defined(H_COMPILER_GNUC) && !defined(STLPORT))
#   include <ext/hash_map>
#   include <ext/hash_set>
#else
//#   include <hash_set>
#   include <hash_map>
#endif

// STL algorithms & functions
#include <algorithm>
#include <functional>
#include <limits>

// C++ Stream stuff
//#include <fstream>
//#include <iostream>
#include <sstream>

#include <sys/types.h>
#include <sys/stat.h>
#include <float.h>


#ifdef H_OS_WINDOWS
#include <process.h>
#elif defined(H_OS_LINUX)
#include <unistd.h>
#include <errno.h>
#endif

#ifdef __BORLANDC__
namespace irr
{
    using namespace std;
}
#endif

// extern "C"
// {
// 
// #   include <sys/types.h>
// #   include <sys/stat.h>
// 
// }

#ifdef H_OS_WINDOWS
#  undef min
#  undef max
#  if defined( __MINGW32__ )
#    include <unistd.h>
#  endif
#	include<memory>
#endif

#ifdef H_OS_LINUX
extern "C"
{

#	include <stdio.h>
#	include <stdlib.h>
#	include <unistd.h>
#	include <dlfcn.h>
#	include <errno.h>
#	include <stdio.h>
#	include<bits/allocator.h>
#include <sys/types.h>
//#	include <stdarg.h>
//#	include <string.h>

//#	include <netdb.h>
//#	include <fcntl.h>
//#	include <sys/time.h>
//#	include <sys/socket.h>
//#	include <netinet/in.h>
//#	include <arpa/inet.h>
//#include <sys/time.h>
//#include <sys/resource.h>
}
#endif


#ifdef H_OS_MACOSX
extern "C"
{
#   include <unistd.h>
#   include <sys/param.h>
#   include <CoreFoundation/CoreFoundation.h>
}
#endif



#endif
