#ifndef __TEST_CPP__
#define __TEST_CPP__

#include "lv1_test.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::test()
	{
		if (!TEST_ALL)
		{
			test_num=ceil(data_num*TEST_RATE);
			new_data(test_pos,test_num);
			uniform_int_distribution<long long> dist(0,data_num-1);
			for (long long i=0;i<test_num;i++)
				test_pos[i]=dist(gen);
		}
		if (FAST_SAMPLING)
		{

		}
		else
		{
			new_data(compress_function,FUNC_NAME_LENGTH);
			strcpy(compress_function,"compress_test");
			test_all_dimension_sequence();
			delete_data(compress_function);
		}
		if (!TEST_ALL)
			delete_data(test_pos);
	}
}

#endif