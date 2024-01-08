#ifndef __TRANSPOSE_DATA_CPP__
#define __TRANSPOSE_DATA_CPP__

#include "transform.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::transpose_data(T *data_backup)
	{
		if (it2->n==1)
			transpose_data_1D(data_backup);
		if (it2->n==2)
			transpose_data_2D(data_backup);
		if (it2->n==3)
			transpose_data_3D(data_backup);
		if (it2->n==4)
			transpose_data_4D(data_backup);
	}
}

#endif