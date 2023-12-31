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
		#ifdef JOB_TYPE_VALIDATE
			printf("Job type=validate\n");
		#endif
		printf("Data name=%s\n",task.data_name);
		#if defined(JOB_TYPE_COMPRESS) || defined(JOB_TYPE_DECOMPRESS)
			printf("Input file path=%s\n",task.in_file_path);
			printf("Output file path=%s\n",task.out_file_path);
			printf("Configuration file mode=%s\n",task.cfg_file_mode);
			printf("Configuration file path=%s\n",task.cfg_file_path);
			printf("Map file mode=%s\n",task.map_file_mode);
			printf("Map file path=%s\n",task.map_file_path);
			printf("Mask file path=%s\n",task.mask_file_path);
		#endif
		#ifdef JOB_TYPE_VALIDATE
			printf("Source file path=%s\n",task.src_file_path);
			printf("Decompressed file path=%s\n",task.dec_file_path);
		#endif
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
		if ((task.cfg_file_mode==NULL) || (strcmp(task.cfg_file_mode,"set")==0))
		{
			printf("error type=%s\n",task.err_type);
			printf("raw error bound=%lf\n",task.raw_err_bound);
		}
		else
			printf("error bound=%lf\n",task.err_bound);
		#if defined(JOB_TYPE_COMPRESS) || defined(JOB_TYPE_DECOMPRESS)
			if (task.debug)
				printf("Debugging activated\n");
			if ((task.cfg_file_mode!=NULL) && (strcmp(task.cfg_file_mode,"use")==0))
			{
				#ifdef JOB_TYPE_COMPRESS
					printf("best compress function=%s\n",task.best_compress_function);
				#endif
				#ifdef JOB_TYPE_DECOMPRESS
					printf("best decompress function=%s\n",task.best_decompress_function);
				#endif
				printf("best_fitting_function=%s\n",task.best_fitting_function);
				task.best_it1->print();
			}
		#endif
	}
}

#endif