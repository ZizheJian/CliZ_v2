#ifndef __DC_1D_LINEAR_DATA_MASK_CPP__
#define __DC_1D_LINEAR_DATA_MASK_CPP__

#include "DC.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::DC_1D_linear_data_mask()
	{
		long long *mx=best_it1->mx;
		long long *weight=best_it1->weight;
		int interpolation_level=0;
		for (int i=0;i<1;i++)
			interpolation_level=max(interpolation_level,(int)ceil(log2(mx[i])));
		long long quant_bin_pos=0;
		#ifdef JOB_TYPE_COMPRESS
		#endif
		#ifdef JOB_TYPE_DECOMPRESS
		#endif
		quant_bin_pos++;
		double err_bound_backup=err_bound;
		for (int lv=interpolation_level-1;lv>=0;lv--)
		{
			if (lv>=2)
				err_bound=err_bound_backup*0.5;
			else
				err_bound=err_bound_backup;
			err_bound_reciprocal=1/err_bound;
			long long stride=1<<lv;
			for (long long b0b=0;b0b<mx[0];b0b+=stride*32)
			{
				long long b0e=min(mx[0]-1,b0b+stride*32);
				long long pos=0;
				for (long long i0=b0b+stride;i0<=b0e;i0+=2*stride)
				{
					T pred;
					if (i0+stride<=b0e)
						pred=linear_fitting_dpd(pos+i0*weight[0],stride*weight[0]);
					else
						if (i0-3*stride>=b0b)
							pred=linear_fitting_ddp(pos+i0*weight[0],stride*weight[0]);
						else
							pred=constant_fitting_dp(pos+i0*weight[0],stride*weight[0]);
					#ifdef JOB_TYPE_COMPRESS
					#endif
					#ifdef JOB_TYPE_DECOMPRESS
					#endif
					quant_bin_pos++;
				}
			}
		}
	}
}

#endif