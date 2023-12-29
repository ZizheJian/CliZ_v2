#ifndef __CHOOSE_METHOD_CPP__
#define __CHOOSE_METHOD_CPP__

#include "choose_method.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::choose_method()
	{
		if (cfg_file_mode!=NULL)
			if (strcmp(cfg_file_mode,"use")==0)
				return;
			else
			{
				new_data(best_compress_function,FUNC_NAME_LENGTH);
				strcpy(best_compress_function,"compress");
				new_data(best_fitting_function,FUNC_NAME_LENGTH);
				strcpy(best_fitting_function,"linear");
				copy_iterator(best_it1,it1);
			}
		else
		{
			new_data(best_compress_function,FUNC_NAME_LENGTH);
			strcpy(best_compress_function,"compress");
			new_data(best_fitting_function,FUNC_NAME_LENGTH);
			strcpy(best_fitting_function,"linear");
			copy_iterator(best_it1,it1);
		}
	}
}

#endif