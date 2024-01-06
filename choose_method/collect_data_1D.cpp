#ifndef __COLLECT_DATA_1D_CPP__
#define __COLLECT_DATA_1D_CPP__

#include "choose_method.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::collect_data_1D(T *data_backup,hyper_iterator_c *it2_backup)
	{
		for (long long i0=0;i0<it2->mx[0];i0++)
		{
			long long j0=((2*i0<it2->mx[0])?(i0+floor((it2_backup->mx[0]-it2->mx[0])/3)):(i0+it2_backup->mx[0]-it2->mx[0]-floor((it2_backup->mx[0]-it2->mx[0])/3)));
			data[i0*it2->weight[0]]=data_backup[j0*it2_backup->weight[0]];
		}
	}
}

#endif