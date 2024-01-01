#ifndef __CHOOSE_METHOD_CPP__
#define __CHOOSE_METHOD_CPP__

#include "choose_method.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::choose_method()
	{
		if (cfg_file_mode==NULL)
		{
			new_data(best_compress_function,FUNC_NAME_LENGTH);
			strcpy(best_compress_function,"compress");
			new_data(best_fitting_function,FUNC_NAME_LENGTH);
			strcpy(best_fitting_function,"linear");
			copy_iterator(best_it1,it1);
			return;
		}
		if (strcmp(cfg_file_mode,"use")==0)
			return;
		new_data(data,data_num);
        in_file=fopen(in_file_path,"rb");
        fread(data,sizeof(T),data_num,in_file);
        fclose(in_file);
		new_data(bitstream,data_num*sizeof(T));
		if (strcmp(data_type,"i32")==0)
			test_i32();
		else
		{
			if (pertid!=-1)
			{
				if ((map_file_mode!=NULL) && ((strcmp(map_file_mode,"set")==0) || (strcmp(map_file_mode,"force-set")==0) || (strcmp(map_file_mode,"use")==0)))
					test_map_pert();
				if ((map_file_mode==NULL) || (strcmp(map_file_mode,"set")==0) || (strcmp(map_file_mode,"use")==0))
					test_pert();
			}
			if ((map_file_mode!=NULL) && ((strcmp(map_file_mode,"set")==0) || (strcmp(map_file_mode,"force-set")==0) || (strcmp(map_file_mode,"use")==0)))
				test_map();
			if ((map_file_mode==NULL) || (strcmp(map_file_mode,"set")==0) || (strcmp(map_file_mode,"use")==0))
				test();
		}
		delete_data(data);
		delete_data(bitstream);
	}
}

#endif