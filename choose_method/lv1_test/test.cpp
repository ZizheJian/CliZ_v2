#ifndef __TEST_CPP__
#define __TEST_CPP__

#include "lv1_test.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::test()
	{
		if (FAST_SAMPLING)
		{

		}
		else
		{
			new_data(compress_function,FUNC_NAME_LENGTH);
			strcpy(compress_function,"compress_test");
			test_all_dimension_sequence();
			delete_data(compress_function);
		}
	}
}

#endif