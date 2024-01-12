#ifndef __VALIDATE_ABS_CPP__
#define __VALIDATE_ABS_CPP__

#include "validate.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::validate_ABS()
	{
		//TODO: add i32 condition
		T max_err=0;
		for (long long i=0;i<data_num;i++)
		{
			T abs_err=fabs(src_data[i]-dec_data[i]);
			if (abs_err>max_err)
				max_err=abs_err;
			if (abs_err>err_bound*2)
			{
				printf("Error at %lld: %f %f\n",i,(float)src_data[i],(float)dec_data[i]);
				getchar();
			}
		}
		if (err_bound==0)
			printf("Max absolute error=%f\n",(float)max_err);
		else
			printf("Error Utilization=%f\n",(float)(max_err/err_bound));
	}
}

#endif