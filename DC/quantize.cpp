#ifndef __QUANTIZE_CPP__
#define __QUANTIZE_CPP__

#include "DC.hpp2"

namespace cliz
{
	template<typename T>
	short task_c<T>::quantize(long long i,T pred)
	{
		T diff=data[i]-pred;
		//printf("In quantize, pos=%lld, data=%f\n",i,data[i]);
		if (fabs(diff)<=65535*err_bound)
		{
			int bin=0;
			if (diff>=0)
				bin=ceil((diff-err_bound)*err_bound_reciprocal/2);
			else
				bin=floor((diff+err_bound)*err_bound_reciprocal/2);
			data[i]=pred+bin*2*err_bound;
			//printf("In quantize, pos=%lld, data=%f, pred=%f, ret=%d\n",i,data[i],pred,bin+32768);
			return bin;
		}
		else
		{
			//printf("In quantize, pos=%lld, data=%f, pred=%f, ret=%d\n",i,data[i],pred,0);
			irregular_data.push_back(data[i]);
			return -32768;
		}
	}
}

#endif