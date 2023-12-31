#ifndef __CHANGE_ERR_BOUND_CPP__
#define __CHANGE_ERR_BOUND_CPP__

#include "change_err_bound.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::change_err_bound()
	{
		if (mask_file_path!=NULL)
		{
			if (dimension_num==1)
				change_err_bound_mask_1D();
			if (dimension_num==2)
				change_err_bound_mask_2D();
			if (dimension_num==3)
				change_err_bound_mask_3D();
			if (dimension_num==4)
				change_err_bound_mask_4D();
		}
		else
		{
			if (dimension_num==1)
				change_err_bound_1D();
			if (dimension_num==2)
				change_err_bound_2D();
			if (dimension_num==3)
				change_err_bound_3D();
			if (dimension_num==4)
				change_err_bound_4D();
		}
	}
}

#endif