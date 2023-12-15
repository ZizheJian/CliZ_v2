#ifndef __CALL_DC_FUNCTIONS_CPP__
#define __CALL_DC_FUNCTIONS_CPP__

#include "DC.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::call_DC_functions()
	{
		// if (dimension_num==2)
		// 	DC_2D();
		if (strcmp(best_fitting_function,"linear")==0)
		{
			if (dimension_num==3)
				DC_3D_linear();
		}
		if (strcmp(best_fitting_function,"cubic")==0)
		{
			if (dimension_num==3)
				DC_3D_cubic();
		}
		// if (dimension_num==4)
		// 	DC_4D();
	}
}

#endif