#ifndef __CALL_COMPRESS_FUNCTIONS_TEST_CPP__
#define __CALL_COMPRESS_FUNCTIONS_TEST_CPP__

#include "compress.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::call_compress_functions_test()
	{
		if (strcmp(compress_function,"compress_test")==0)
			compress_test();
	}
}

#endif