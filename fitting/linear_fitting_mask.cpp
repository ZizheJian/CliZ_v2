#ifndef __LINEAR_FITTING_MASK_CPP__
#define __LINEAR_FITTING_MASK_CPP__

#include "fitting.hpp2"

namespace cliz
{
	template<typename T>
	T task_c<T>::linear_fitting_dpd_mask(long long i,long long stride)
	{
		bool v0=mask_data[pos2horiz_mapping[i-stride]];
		bool v1=mask_data[pos2horiz_mapping[i+stride]];
		T p0=v0*(v1?0.5:1);
		T p1=(v0?0.5:1)*v1;
		return p0*data[i-stride]+p1*data[i+stride];
	}

	template<typename T>
	T task_c<T>::linear_fitting_ddp_mask(long long i,long long stride)
	{
		bool v0=mask_data[pos2horiz_mapping[i-3*stride]];
		bool v1=mask_data[pos2horiz_mapping[i-stride]];
		T p0=v0*(v1?-0.5:1);
		T p1=(v0?1.5:1)*v1;
		return p0*data[i-3*stride]+p1*data[i-stride];
	}

	template<typename T>
	T task_c<T>::constant_fitting_dp_mask(long long i,long long stride)
	{
		bool v0=mask_data[pos2horiz_mapping[i-stride]];
		T p0=v0;
		return p0*data[i-stride];
	}
}

#endif