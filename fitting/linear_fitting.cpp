#ifndef __LINEAR_FITTING_CPP__
#define __LINEAR_FITTING_CPP__

#include "fitting.hpp2"

namespace cliz
{
	template<typename T>
	T task_c<T>::linear_fitting_dpd(long long i,long long stride)
	{
		return 0.5*(data[i-stride]+data[i+stride]);
	}

	template<typename T>
	T task_c<T>::linear_fitting_ddp(long long i,long long stride)
	{
		return -0.5*data[i-3*stride]+1.5*data[i-stride];
	}

	template<typename T>
	T task_c<T>::constant_fitting_dp(long long i,long long stride)
	{
		return data[i-stride];
	}
}

#endif