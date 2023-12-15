#ifndef __QUANTIZE_CPP__
#define __QUANTIZE_CPP__

#include "DC.hpp2"

namespace cliz
{
	template<typename T>
	unsigned short task_c<T>::quantize(long long i,T pred)
	{
		T diff=data[i]-pred;
		printf("%lld %f\n",i,data[i]);
		if (fabs(diff)<=65535*err_bound)
		{
			int bin=0;
			if (diff>=0)
				bin=ceil((diff-err_bound)*err_bound_reciprocal/2);
			else
				bin=floor((diff+err_bound)*err_bound_reciprocal/2);
			data[i]=pred+bin*2*err_bound;
			printf("%lld %f %f %d\n",i,data[i],pred,bin+32768);
			return bin+32768;
		}
		else
		{
			printf("%lld %f %f %d\n",i,data[i],pred,0);
			irregular_data.push_back(data[i]);
			return 0;
		}
	}
}

#endif