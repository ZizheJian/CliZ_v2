#ifndef __TRANSPOSE_4D_CPP__
#define __TRANSPOSE_4D_CPP__

#include "transform.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::transpose_4D(T *data_backup)
	{
		long long *mx1=it1->mx;
		long long *weight1=it1->weight;
		long long *weight2=it2->weight;
		int *dim_seq=it1->dim_seq;
		long long *i=new_data<long long>(it2->n);
		long long *j=new_data<long long>(it2->n);
		for (i[0]=0;i[0]<mx1[0];i[0]++)
		{
			j[dim_seq[0]]=i[0];
			for (i[1]=0;i[1]<mx1[1];i[1]++)
			{
				j[dim_seq[1]]=i[1];
				for (i[2]=0;i[2]<mx1[2];i[2]++)
				{
					j[dim_seq[2]]=i[2];
					for (i[3]=0;i[3]<mx1[3];i[3]++)
					{
						j[dim_seq[3]]=i[3];
						long long pos1=i[0]*weight1[0]+i[1]*weight1[1]+i[2]*weight1[2]+i[3]*weight1[3];
						long long pos2=j[0]*weight2[0]+j[1]*weight2[1]+j[2]*weight2[2]+j[3]*weight2[3];
						data[pos1]=data_backup[pos2];
					}
				}
			}
		}
	}
}

#endif