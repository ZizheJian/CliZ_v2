#ifndef __CUBIC_FITTING_CPP__
#define __CUBIC_FITTING_CPP__

#include "fitting.hpp2"

namespace cliz
{
	template<typename T>
	T task_c<T>::cubic_fitting(long long mini,long long i,long long maxi,long long stride)
	{
		bool v[4];
		T d[4],p[4],ans=0;
		v[0]=(i-3*stride>=mini);
		v[1]=(i-stride>=mini);
		v[2]=(i+stride<maxi);
		v[3]=(i+3*stride<maxi);
		d[0]=v[0]?data[i-3*stride]:0;
		d[1]=v[1]?data[i-stride]:0;
		d[2]=v[2]?data[i+stride]:0;
		d[3]=v[3]?data[i+3*stride]:0;
		p[0]=v[0]*(v[1]?-0.5:1)*(v[2]?0.25:1)*(v[3]?0.5:1);
		p[1]=(v[0]?1.5:1)*v[1]*(v[2]?0.5:1)*(v[3]?0.75:1);
		p[2]=(v[0]?0.75:1)*(v[1]?0.5:1)*v[2]*(v[3]?1.5:1);
		p[3]=(v[0]?0.5:1)*(v[1]?0.25:1)*(v[2]?-0.5:1)*v[3];
		ans=p[0]*d[0]+p[1]*d[1]+p[2]*d[2]+p[3]*d[3];
		return ans;
	}
}

#endif