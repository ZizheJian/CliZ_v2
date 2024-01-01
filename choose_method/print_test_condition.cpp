#ifndef __PRINT_TEST_CONDITION_CPP__
#define __PRINT_TEST_CONDITION_CPP__

#include "choose_method.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::print_test_condition()
	{
		if (it1->dim_seq==NULL)
			for (int did=0;did<it2->n;did++)
				printf("%d",did);
		else
			for (int did=0;did<it2->n;did++)
				printf("%d",it1->dim_seq[did]);
		printf("%d%d %f\n",it1->dim_fission_l,it1->dim_fission_r,((float)bitstream_length)/(data_num*sizeof(T)));
	}
}

#endif