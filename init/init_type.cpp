#ifndef __INIT_TYPE_CPP__
#define __INIT_TYPE_CPP__

#include "init.hpp2"

namespace cliz
{
	void read_type_command(task_c<float> &task_f32,int argc,char **argv,int &i)
	{
		if (task_f32.data_type!=NULL)
		{
			printf("Error: Data type redefined.\n");
			exit(0);
		}
		i++;
		if (i>=argc)
		{
			printf("Error: Data type missing\n");
			exit(0);
		}
		new_data(task_f32.data_type,strlen(argv[i])+1);
		strcpy(task_f32.data_type,argv[i]);
	}

	void check_type(task_c<float> &task_f32)
	{
		if ((task_f32.data_type==NULL) && ((task_f32.cfg_file_mode==NULL) || (strcmp(task_f32.cfg_file_mode,"set")==0)))
		{
			new_data(task_f32.data_type,4);
			strcpy(task_f32.data_type,"f32");
			return;
		}
		if (task_f32.data_type==NULL)
			return;
		bool supported=false;
		for (int j=0;j<sizeof(supported_data_type)/sizeof(char*);j++)
			if (strcmp(task_f32.data_type,supported_data_type[j])==0)
				supported=true;
		if (!supported)
		{
			printf("Error: Unsupported data type.\n");
			exit(0);
		}
	}

	template<typename T>
	void move_task(task_c<T> &ty,task_c<float> &tx)
	{
		ty.in_file_path=tx.in_file_path;
		ty.out_file_path=tx.out_file_path;
		ty.cfg_file_mode=tx.cfg_file_mode;
		ty.cfg_file_path=tx.cfg_file_path;
		ty.map_file_mode=tx.map_file_mode;
		ty.map_file_path=tx.map_file_path;
		ty.mask_file_path=tx.mask_file_path;
		ty.data_name=tx.data_name;
		ty.dimension_num=tx.dimension_num;
		ty.dimension=tx.dimension;
		ty.dimension_type=tx.dimension_type;
		ty.data_num=tx.data_num;
		ty.data_type=tx.data_type;
		ty.err_type=tx.err_type;
		ty.raw_err_bound=tx.raw_err_bound;
		ty.debug=tx.debug;
		ty.best_compress_function=tx.best_compress_function;
		ty.best_decompress_function=tx.best_decompress_function;
		ty.best_fitting_function=tx.best_fitting_function;
		ty.it1=tx.it1;
		ty.best_it1=tx.best_it1;
		ty.it2=tx.it2;
		/*ty.pert=tx.pert;
		ty.best_avg_it1=tx.best_avg_it1;
		ty.avg_it2=tx.avg_it2;
		ty.best_avg_decompress_framework.name=tx.best_avg_decompress_framework.name;
		ty.best_avg_predictor.name=tx.best_avg_predictor.name;*/
	}
}


#endif