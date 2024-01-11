#ifndef __TEST_MASK_CPP__
#define __TEST_MASK_CPP__

#include "lv1_test.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::test_mask()
	{
		if (FAST_SAMPLING)
		{

		}
		else
		{
			new_data(mask_data,it2->mx[latid]*it2->mx[lngid]);
			mask_file=fopen(mask_file_path,"rb");
			fread(mask_data,sizeof(int),it2->mx[latid]*it2->mx[lngid],mask_file);
			fclose(mask_file);
			new_data(compress_function,FUNC_NAME_LENGTH);
			strcpy(compress_function,"compress_mask_test");
			test_all_dimension_sequence();
			delete_data(mask_data);
			delete_data(compress_function);
		}
	}
}

#endif