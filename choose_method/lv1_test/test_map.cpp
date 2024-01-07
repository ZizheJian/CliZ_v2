#ifndef __TEST_MAP_CPP__
#define __TEST_MAP_CPP__

#include "lv1_test.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::test_map()
	{
		strcpy(best_compress_function,"compress_map");
		strcpy(best_fitting_function,"cubic");
		copy_iterator(best_it1,it1);
	}
}

#endif