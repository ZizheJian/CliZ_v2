#ifndef __CALL_VALIDATE_FUNCTIONS_CPP__
#define __CALL_VALIDATE_FUNCTIONS_CPP__

#include "validate.hpp2"

namespace cliz
{
    template<typename T>
    void task_c<T>::call_validate_functions()
    {
        new_data(src_data,data_num);
        src_file=fopen(src_file_path,"rb");
        fread(src_data,sizeof(T),data_num,src_file);
        fclose(src_file);
        new_data(dec_data,data_num);
        dec_file=fopen(dec_file_path,"rb");
        fread(dec_data,sizeof(T),data_num,dec_file);
        fclose(dec_file);
        validate_ABS();
    }
}

#endif