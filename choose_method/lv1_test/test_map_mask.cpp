#ifndef __TEST_MAP_MASK_CPP__
#define __TEST_MAP_MASK_CPP__

#include "lv1_test.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::test_map_mask()
	{
		if (FAST_SAMPLING)
		{

		}
		else
		{
			new_data(map_bitstream,it2->mx[latid]*it2->mx[lngid]);
			new_data(compress_function,FUNC_NAME_LENGTH);
			strcpy(compress_function,"compress_set_map_mask_test");
			test_all_dimension_sequence();
			delete_data(compress_function);
			delete_data(map_bitstream);
		}
	}
}

#endif