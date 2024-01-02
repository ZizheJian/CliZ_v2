#ifndef __PRINTDETAIL_CPP__
#define __PRINTDETAIL_CPP__

#include "debug.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::print_detail()
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
		printf("Data name=%s\n",data_name);
		#if defined(JOB_TYPE_COMPRESS) || defined(JOB_TYPE_DECOMPRESS)
			printf("Input file path=%s\n",in_file_path);
			printf("Output file path=%s\n",out_file_path);
			printf("Configuration file mode=%s\n",cfg_file_mode);
			printf("Configuration file path=%s\n",cfg_file_path);
			printf("Map file mode=%s\n",map_file_mode);
			printf("Map file path=%s\n",map_file_path);
			printf("Mask file path=%s\n",mask_file_path);
		#endif
		#ifdef JOB_TYPE_VALIDATE
			printf("Source file path=%s\n",src_file_path);
			printf("Decompressed file path=%s\n",dec_file_path);
		#endif
		printf("Data type=%s\n",data_type);
		if (dimension_type[0]!=NULL)
			printf("dimension={(%s)%lld",dimension_type[0],dimension[0]);
		else
			printf("dimension={%lld",dimension[0]);
		for (int i=1;i<dimension_num;i++)
			if (dimension_type[i]!=NULL)
				printf(",(%s)%lld",dimension_type[i],dimension[i]);
			else
				printf(",%lld",dimension[i]);
		printf("}\n");
		if ((cfg_file_mode==NULL) || (strcmp(cfg_file_mode,"set")==0))
		{
			printf("error type=%s\n",err_type);
			printf("raw error bound=%lf\n",raw_err_bound);
		}
		else
			printf("error bound=%lf\n",err_bound);
		#if defined(JOB_TYPE_COMPRESS) || defined(JOB_TYPE_DECOMPRESS)
			if (debug)
				printf("Debugging activated\n");
		#endif
	}
}

#endif