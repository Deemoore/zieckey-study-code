#include "osl/include/inner_pre.h"


//! Include configuration memory pool.
#if (defined( H_MEMORY_POOL ))
//���ʹ�óأ�����ϵͳ�ڴ棬 ���Թر���
//#	define H_USE_SYS_MEM
#	include "mem_alloc_pool.h"
#else
#	include "mem_alloc_sys_heap.h"
#endif

namespace osl
{


};//namespace
