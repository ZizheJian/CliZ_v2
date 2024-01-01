#ifndef __TEST_ALL_FITTING_FUNCTION_CPP__
#define __TEST_ALL_FITTING_FUNCTION_CPP__

#include "lv2_test.hpp2"

namespace cliz
{
    template<typename T>
    void task_c<T>::test_all_fitting_function()
    {
        new_data(fitting_function,FUNC_NAME_LENGTH);
        strcpy(fitting_function,"linear");
        call_compress_functions_test();
        strcpy(fitting_function,"cubic");
        call_compress_functions_test();
        delete_data(fitting_function);
    }
}


#endif