#ifndef __PRINTDETAIL_CPP__
#define __PRINTDETAIL_CPP__

#include "debug.hpp2"

namespace cliz
{
	template<typename T>
	void print_detail(task_c<T> &task)
	{
		#ifdef JOB_TYPE_COMPRESS
			printf("Job type=compress\n");
		#endif
		#ifdef JOB_TYPE_DECOMPRESS
			printf("Job type=decompress\n");
		#endif
		printf("Data name=%s\n",task.data_name);
		printf("Input file path=%s\n",task.in_file_path);
		printf("Output file path=%s\n",task.out_file_path);
		printf("Configuration file mode=%s\n",task.cfg_file_mode);
		printf("Configuration file path=%s\n",task.cfg_file_path);
		printf("Map file mode=%s\n",task.map_file_mode);
		printf("Map file path=%s\n",task.map_file_path);
		printf("Mask file path=%s\n",task.mask_file_path);
		printf("Data type=%s\n",task.data_type);
		if (task.dimension_type[0]!=NULL)
			printf("dimension={(%s)%lld",task.dimension_type[0],task.dimension[0]);
		else
			printf("dimension={%lld",task.dimension[0]);
		for (int i=1;i<task.dimension_num;i++)
			if (task.dimension_type[i]!=NULL)
				printf(",(%s)%lld",task.dimension_type[i],task.dimension[i]);
			else
				printf(",%lld",task.dimension[i]);
		printf("}\n");
		printf("error type=%s\n",task.err_type);
		printf("error bound=%lf\n",task.err_bound);
		if (task.debug)
			printf("Debugging activated\n");
		/*#ifdef JOB_TYPE_DECOMPRESS
			if (pert!=0)
			{
				printf("Best avg decompress framework=%s\n",best_avg_decompress_framework.name);
				printf("Best avg predictor=%s\n",best_avg_predictor.name);
				printf("Best avg it1=\n");
				best_avg_it1->print_more();
				printf("avg it2=\n");
				avg_it2->print_more();
			}
			printf("Best decompress framework=%s\n",best_decompress_framework.name);
			printf("Best predictor=%s\n",best_predictor.name);
			printf("Best it1=\n");
			best_it1->print_more();
			printf("it2=\n");
			it2->print_more();
		#endif*/
	}
}

#endif