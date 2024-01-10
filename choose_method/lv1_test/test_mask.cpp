#ifndef __TEST_MASK_CPP__
#define __TEST_MASK_CPP__

#include "lv1_test.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::test_mask()
	{
		strcpy(best_compress_function,"compress_mask");
		strcpy(best_fitting_function,"cubic");
		copy_iterator(best_it1,it1);
		return;
		if (FAST_SAMPLING)
		{

		}
		else
		{
			new_data(compress_function,FUNC_NAME_LENGTH);
			strcpy(compress_function,"compress_mask_test");
			test_all_dimension_sequence();
			delete_data(compress_function);
		}
	}
}

#endif