#ifndef __CALL_DC_FUNCTIONS_CPP__
#define __CALL_DC_FUNCTIONS_CPP__

#include "DC.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::call_DC_functions()
	{
		if (strcmp(best_fitting_function,"linear")==0)
		{
			if (best_it1->n==1)
				DC_1D_linear();
			if (best_it1->n==2)
				DC_2D_linear();
			if (best_it1->n==3)
				DC_3D_linear();
			if (best_it1->n==4)
				DC_4D_linear();
		}
		if (strcmp(best_fitting_function,"cubic")==0)
		{
			if (best_it1->n==1)
				DC_1D_cubic();
			if (best_it1->n==2)
				DC_2D_cubic();
			if (best_it1->n==3)
				DC_3D_cubic();
			if (best_it1->n==4)
				DC_4D_cubic();
		}
	}
}

#endif