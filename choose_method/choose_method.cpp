#ifndef __CHOOSE_METHOD_CPP__
#define __CHOOSE_METHOD_CPP__

#include "choose_method.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::choose_method()
	{
		//TODO: i32
		new_data(data,data_num);
		in_file=fopen(in_file_path,"rb");
		fread(data,sizeof(T),data_num,in_file);
		fclose(in_file);
		new_data(bitstream,data_num*sizeof(T));
		auto timer=new timer_c();
		timer->start();
		if ((cfg_file_mode==NULL) || (strcmp(cfg_file_mode,"use")==0))
			if (cfg_file_mode==NULL)
			{
				new_data(best_compress_function,FUNC_NAME_LENGTH);
				new_data(best_fitting_function,FUNC_NAME_LENGTH);
				strcpy(best_fitting_function,"cubic");
				if (map_file_mode==NULL)
					if (mask_file_path==NULL)
						strcpy(best_compress_function,"compress");
					else
						strcpy(best_compress_function,"compress_mask");
				else
					if (strcmp(map_file_mode,"set")==0)
						if (mask_file_path==NULL)
						{
							new_data(map_bitstream,it2->mx[latid]*it2->mx[lngid]);
							new_data(compress_function,FUNC_NAME_LENGTH);
							strcpy(compress_function,"compress_set_map_test");
							new_data(fitting_function,FUNC_NAME_LENGTH);
							strcpy(fitting_function,best_fitting_function);
							call_compress_functions_test();
							delete_data(map_bitstream);
							strcpy(compress_function,"compress_test");
							delete_data(compress_function);
							delete_data(fitting_function);
						}
						else
						{
							new_data(map_bitstream,it2->mx[latid]*it2->mx[lngid]);
							new_data(mask_data,it2->mx[latid]*it2->mx[lngid]);
							mask_file=fopen(mask_file_path,"rb");
							fread(mask_data,sizeof(int),it2->mx[latid]*it2->mx[lngid],mask_file);
							fclose(mask_file);
							new_data(compress_function,FUNC_NAME_LENGTH);
							strcpy(compress_function,"compress_set_map_mask_test");
							new_data(fitting_function,FUNC_NAME_LENGTH);
							strcpy(fitting_function,best_fitting_function);
							call_compress_functions_test();
							delete_data(map_bitstream);
							strcpy(compress_function,"compress_mask_test");
							delete_data(compress_function);
							delete_data(fitting_function);
							delete_data(mask_data);
						}
					else
						if (mask_file_path==NULL)
							strcpy(best_compress_function,"compress_use_map");
						else
							strcpy(best_compress_function,"compress_use_map_mask");
			}
			else
				if (map_file_mode==NULL)
				{
					if (strcmp(best_compress_function,"compress")==0);
					if (strcmp(best_compress_function,"compress_map")==0)
					{
						printf("Error: Configuration file indicates that a map file is required, but no map file is specified.\n");
						exit(0);
					}
					if (strcmp(best_compress_function,"compress_mask")==0)
						if (mask_file_path==NULL)
						{
							printf("Error: Configuration file indicates that a mask file is required, but no mask file is specified.\n");
							exit(0);
						}
						else
							strcpy(best_compress_function,"compress_mask");
					if (strcmp(best_compress_function,"compress_map_mask")==0)
					{
						printf("Error: Configuration file indicates that a map file is required, but no map file is specified.\n");
						exit(0);
					}
				}
				else
				{
					if (strcmp(best_compress_function,"compress")==0);
					if (strcmp(best_compress_function,"compress_map")==0)
						if (strcmp(map_file_mode,"set")==0)
							strcpy(best_compress_function,"compress_set_map");
						else
							strcpy(best_compress_function,"compress_use_map");
					if (strcmp(best_compress_function,"compress_mask")==0)
						if (mask_file_path==NULL)
						{
							printf("Error: Configuration file indicates that a mask file is required, but no mask file is specified.\n");
							exit(0);
						}
						else
							strcpy(best_compress_function,"compress_mask");
					if (strcmp(best_compress_function,"compress_map_mask")==0)
						if (mask_file_path==NULL)
						{
							printf("Error: Configuration file indicates that a mask file is required, but no mask file is specified.\n");
							exit(0);
						}
						else
							if (strcmp(map_file_mode,"set")==0)
								strcpy(best_compress_function,"compress_set_map_mask");
							else
								strcpy(best_compress_function,"compress_use_map_mask");
				}
		else
		{
			new_data(best_compress_function,FUNC_NAME_LENGTH);
			new_data(best_fitting_function,FUNC_NAME_LENGTH);
			if (pertid!=-1)
				test_pert();
			if (map_file_mode!=NULL)
				if (mask_file_path!=NULL)
					test_map_mask();
				else
					test_map();
			if (mask_file_path!=NULL)
				test_mask();
			else
				test();
		}
		timer->pause();
		timer->write();
		print_best_strategy();
		delete_data(data);
		delete_data(bitstream);
	}
}

#endif