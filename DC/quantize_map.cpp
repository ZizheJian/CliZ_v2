#ifndef __QUANTIZE_MAP_CPP__
#define __QUANTIZE_MAP_CPP__

#include "DC.hpp2"

namespace cliz
{
	template<typename T>
	short task_c<T>::quantize_map(long long i,T pred)
	{
		T diff=data[i]-pred;
		if (fabs(diff)<=65535*err_bound)
		{
			int bin=0;
			if (diff>=0)
				bin=ceil((diff-err_bound)*err_bound_reciprocal/2);
			else
				bin=floor((diff+err_bound)*err_bound_reciprocal/2);
			//printf("pos=%lld, data=%f, pred=%f, diff=%f, bin=%d, data'=%f\n",i,data[i],pred,diff,bin,pred+bin*2*err_bound);
			data[i]=pred+bin*2*err_bound;
			return bin;
		}
		else
		{
			irregular_data.push_back(data[i]);
			//printf("pos=%lld, data=%f, pred=%f, diff=%f, bin=-32768, data'=%f\n",i,data[i],pred,diff,data[i]);
			return -32768;
		}
	}
}

#endif