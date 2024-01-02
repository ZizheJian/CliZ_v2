#ifndef __TRANSPOSE_CPP__
#define __TRANSPOSE_CPP__

#include "transform.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::transpose(T *data_backup)
	{
		if (it2->n==1)
			transpose_1D(data_backup);
		if (it2->n==2)
			transpose_2D(data_backup);
		if (it2->n==3)
			transpose_3D(data_backup);
		if (it2->n==4)
			transpose_4D(data_backup);
	}
}

#endif