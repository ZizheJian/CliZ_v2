#ifndef __COLLECT_DATA_4D_CPP__
#define __COLLECT_DATA_4D_CPP__

#include "choose_method.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::collect_data_4D(T *data_backup,hyper_iterator_c *it2_backup)
	{
		for (long long i0=0;i0<it2->mx[0];i0++)
			for (long long i1=0;i1<it2->mx[1];i1++)
				for (long long i2=0;i2<it2->mx[2];i2++)
					for (long long i3=0;i3<it2->mx[3];i3++)
					{
						long long j0=((2*i0<it2->mx[0])?(i0+floor((it2_backup->mx[0]-it2->mx[0])/3)):(i0+it2_backup->mx[0]-it2->mx[0]-floor((it2_backup->mx[0]-it2->mx[0])/3)));
						long long j1=((2*i1<it2->mx[1])?(i1+floor((it2_backup->mx[1]-it2->mx[1])/3)):(i1+it2_backup->mx[1]-it2->mx[1]-floor((it2_backup->mx[1]-it2->mx[1])/3)));
						long long j2=((2*i2<it2->mx[2])?(i2+floor((it2_backup->mx[2]-it2->mx[2])/3)):(i2+it2_backup->mx[2]-it2->mx[2]-floor((it2_backup->mx[2]-it2->mx[2])/3)));
						long long j3=((2*i3<it2->mx[3])?(i3+floor((it2_backup->mx[3]-it2->mx[3])/3)):(i3+it2_backup->mx[3]-it2->mx[3]-floor((it2_backup->mx[3]-it2->mx[3])/3)));
						data[i0*it2->weight[0]+i1*it2->weight[1]+i2*it2->weight[2]+i3*it2->weight[3]]=data_backup[j0*it2_backup->weight[0]+j1*it2_backup->weight[1]+j2*it2_backup->weight[2]+j3*it2_backup->weight[3]];
					}
	}
}

#endif