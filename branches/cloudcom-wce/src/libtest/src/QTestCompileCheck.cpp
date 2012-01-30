#include "libtest/include/QLibTestPrerequisits.h"
#include "osl/include/type_traits_ext.h"

namespace
{

    void Test_Is_Pointer()
    {
        test_bool_type( stdext::is_pointer<int*>::type() );
        test_bool_type( stdext::is_same<stdext::is_pointer<int>::type , stdext::false_type>::type () );






    }




}
