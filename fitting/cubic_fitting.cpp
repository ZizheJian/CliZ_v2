#ifndef __CUBIC_FITTING_CPP__
#define __CUBIC_FITTING_CPP__

#include "fitting.hpp2"

namespace cliz
{
	template<typename T>
	T task_c<T>::cubic_fitting_ddpdd(long long i,long long stride)
	{
		return (-data[i-3*stride]+9*data[i-stride]+9*data[i+stride]-data[i+3*stride])/16;
	}

	template<typename T>
	T task_c<T>::quadratic_fitting_ddpd(long long i,long long stride)
	{
		return (-data[i-3*stride]+6*data[i-stride]+3*data[i+stride])/8;
	}

	template<typename T>
	T task_c<T>::quadratic_fitting_dddp(long long i,long long stride)
	{
		return (3*data[i-5*stride]-10*data[i-3*stride]+15*data[i-stride])/8;
	}
}

#endif