#ifndef __PRINT_BEST_STRATEGY_CPP__
#define __PRINT_BEST_STRATEGY_CPP__

#include "debug.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::print_best_strategy()
	{
		#ifdef JOB_TYPE_COMPRESS
			if (strcmp(best_compress_function,"compress")==0)
				printf("best compress function=%s\n",best_compress_function);
			if ((strcmp(best_compress_function,"compress_set_map")==0) || (strcmp(best_compress_function,"compress_use_map")==0))
				printf("best compress function=compress_map\n");
			if (strcmp(best_compress_function,"compress_mask")==0)
				printf("best compress function=compress_mask\n");
			if ((strcmp(best_compress_function,"compress_set_map_mask")==0) || (strcmp(best_compress_function,"compress_use_map_mask")==0))
				printf("best compress function=compress_map_mask\n");
		#endif
		#ifdef JOB_TYPE_DECOMPRESS
			printf("best decompress function=%s\n",best_decompress_function);
		#endif
		printf("best fitting function=%s\n",best_fitting_function);
		printf("best it1=\n");
		best_it1->print();
		if (best_pert!=0)
		{
			printf("best pert=%lld\n",best_pert);
			#ifdef JOB_TYPE_COMPRESS
				if (strcmp(best_pert_compress_function,"compress")==0)
					printf("best pert compress function=%s\n",best_compress_function);
				if ((strcmp(best_pert_compress_function,"compress_set_map")==0) || (strcmp(best_pert_compress_function,"compress_use_map")==0))
					printf("best pert compress function=compress_map\n");
				if (strcmp(best_pert_compress_function,"compress_mask")==0)
					printf("best pert compress function=compress_mask\n");
				if ((strcmp(best_pert_compress_function,"compress_set_map_mask")==0) || (strcmp(best_pert_compress_function,"compress_use_map_mask")==0))
					printf("best pert compress function=compress_map_mask\n");
			#endif
			#ifdef JOB_TYPE_DECOMPRESS
				printf("best pert decompress function=%s\n",best_pert_decompress_function);
			#endif
			printf("best pert fitting function=%s\n",best_pert_fitting_function);
			printf("best pert it1=\n");
			best_pert_it1->print();
		}
	}
}

#endif