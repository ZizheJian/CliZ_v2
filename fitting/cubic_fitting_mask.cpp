#ifndef __CUBIC_FITTING_MASK_CPP__
#define __CUBIC_FITTING_MASK_CPP__

#include "fitting.hpp2"

namespace cliz
{
	template<typename T>
	T task_c<T>::cubic_fitting_ddpdd_mask(long long i,long long stride)
	{
		bool v0=mask_data[pos2horiz_mapping[i-3*stride]];
		bool v1=mask_data[pos2horiz_mapping[i-stride]];
		bool v2=mask_data[pos2horiz_mapping[i+stride]];
		bool v3=mask_data[pos2horiz_mapping[i+3*stride]];
		T p0=v0*(v1?-0.5:1)*(v2?0.25:1)*(v3?0.5:1);
		T p1=(v0?1.5:1)*v1*(v2?0.5:1)*(v3?0.75:1);
		T p2=(v0?0.75:1)*(v1?0.5:1)*v2*(v3?1.5:1);
		T p3=(v0?0.5:1)*(v1?0.25:1)*(v2?-0.5:1)*v3;
		return p0*data[i-3*stride]+p1*data[i-stride]+p2*data[i+stride]+p3*data[i+3*stride];
	}

	template<typename T>
	T task_c<T>::quadratic_fitting_ddpd_mask(long long i,long long stride)
	{
		bool v0=mask_data[pos2horiz_mapping[i-3*stride]];
		bool v1=mask_data[pos2horiz_mapping[i-stride]];
		bool v2=mask_data[pos2horiz_mapping[i+stride]];
		T p0=v0*(v1?-0.5:1)*(v2?0.25:1);
		T p1=(v0?1.5:1)*v1*(v2?0.5:1);
		T p2=(v0?0.75:1)*(v1?0.5:1)*v2;
		return p0*data[i-3*stride]+p1*data[i-stride]+p2*data[i+stride];
	}

	template<typename T>
	T task_c<T>::quadratic_fitting_dddp_mask(long long i,long long stride)
	{
		bool v0=mask_data[pos2horiz_mapping[i-5*stride]];
		bool v1=mask_data[pos2horiz_mapping[i-3*stride]];
		bool v2=mask_data[pos2horiz_mapping[i-stride]];
		T p0=v0*(v1?-1.5:1)*(v2?-0.25:1);
		T p1=(v0?2.5:1)*v1*(v2?-0.5:1);
		T p2=(v0?1.25:1)*(v1?1.5:1)*v2;
		return p0*data[i-5*stride]+p1*data[i-3*stride]+p2*data[i-stride];
	}
}

#endif