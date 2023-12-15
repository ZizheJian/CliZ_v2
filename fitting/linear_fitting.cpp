#ifndef __LINEAR_FITTING_CPP__
#define __LINEAR_FITTING_CPP__

#include "fitting.hpp2"

namespace cliz
{
	template<typename T>
	T task_c<T>::linear_fitting_dpd(long long i,long long stride)
	{
		printf("%lld %lld %f %lld %f\n",i,i-stride,data[i-stride],i+stride,data[i+stride]);
		return 0.5*(data[i-stride]+data[i+stride]);
	}

	template<typename T>
	T task_c<T>::linear_fitting_dp(long long i,long long stride)
	{
		printf("%lld %lld %f\n",i,i-stride,data[i-stride]);
		return data[i-stride];
	}

	template<typename T>
	T task_c<T>::linear_fitting_ddp(long long i,long long stride)
	{
		printf("%lld %lld %f %lld %f\n",i,i-3*stride,data[i-3*stride],i-stride,data[i-stride]);
		return -0.5*data[i-3*stride]+1.5*data[i-stride];
	}
}

#endif