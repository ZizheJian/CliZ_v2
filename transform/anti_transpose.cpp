#ifndef __ANTI_TRANSPOSE_CPP__
#define __ANTI_TRANSPOSE_CPP__

#include "transform.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::anti_transpose(T *data_backup)
	{
		if (it2->n==1)
			anti_transpose_1D(data_backup);
		if (it2->n==2)
			anti_transpose_2D(data_backup);
		if (it2->n==3)
			anti_transpose_3D(data_backup);
		if (it2->n==4)
			anti_transpose_4D(data_backup);
	}
}

#endif