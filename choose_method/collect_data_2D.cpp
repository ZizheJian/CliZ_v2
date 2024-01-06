#ifndef __COLLECT_DATA_2D_CPP__
#define __COLLECT_DATA_2D_CPP__

#include "choose_method.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::collect_data_2D(T *data_backup,hyper_iterator_c *it2_backup)
	{
		for (long long i0=0;i0<it2->mx[0];i0++)
			for (long long i1=0;i1<it2->mx[1];i1++)
			{
				long long j0=((2*i0<it2->mx[0])?(i0+floor((it2_backup->mx[0]-it2->mx[0])/3)):(i0+it2_backup->mx[0]-it2->mx[0]-floor((it2_backup->mx[0]-it2->mx[0])/3)));
				long long j1=((2*i1<it2->mx[1])?(i1+floor((it2_backup->mx[1]-it2->mx[1])/3)):(i1+it2_backup->mx[1]-it2->mx[1]-floor((it2_backup->mx[1]-it2->mx[1])/3)));
				data[i0*it2->weight[0]+i1*it2->weight[1]]=data_backup[j0*it2_backup->weight[0]+j1*it2_backup->weight[1]];
			}
	}
}

#endif