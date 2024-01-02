#ifndef __PRINT_BEST_STRATEGY_CPP__
#define __PRINT_BEST_STRATEGY_CPP__

#include "debug.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::print_best_strategy()
	{
		#ifdef JOB_TYPE_COMPRESS
			printf("best_compress_function=%s\n",best_compress_function);
		#endif
		#ifdef JOB_TYPE_DECOMPRESS
			printf("best_decompress_function=%s\n",best_decompress_function);
		#endif
		printf("best_fitting_function=%s\n",best_fitting_function);
		printf("best_it1=\n");
		best_it1->print();
	}
}

#endif