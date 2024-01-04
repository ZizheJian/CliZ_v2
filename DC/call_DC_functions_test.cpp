#ifndef __CALL_DC_FUNCTIONS_TEST_CPP__
#define __CALL_DC_FUNCTIONS_TEST_CPP__

#include "DC.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::call_DC_functions_test()
	{
		if (strcmp(fitting_function,"linear")==0)
		{
			DC_linear_test();
		}
		if (strcmp(fitting_function,"cubic")==0)
		{
			// if (best_it1->n==3)
			// 	DC_3D_cubic_test();
		}
		// if (dimension_num==4)
		// 	DC_4D();
	}
}

#endif