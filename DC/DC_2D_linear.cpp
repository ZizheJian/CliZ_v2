#ifndef __DC_2D_LINEAR_CPP__
#define __DC_2D_LINEAR_CPP__

#include "DC.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::DC_2D_linear()
	{
		long long *mx=best_it1->mx;
		long long *weight=best_it1->weight;
		int interpolation_level=0;
		for (int i=0;i<2;i++)
			interpolation_level=max(interpolation_level,(int)ceil(log2(mx[i])));
		long long quant_bin_pos=0;
		#ifdef JOB_TYPE_COMPRESS
			quant_bin[quant_bin_pos]=quantize(0,0);
		#endif
		#ifdef JOB_TYPE_DECOMPRESS
			data[0]=dequantize(quant_bin_pos,0);
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
				for (long long b1b=0;b1b<mx[1];b1b+=stride*32)
				{
					long long b1e=min(mx[1]-1,b1b+stride*32);
					for (long long i1=(b1b?b1b+2*stride:0);i1<=b1e;i1+=2*stride)
					{
						long long pos=i1*weight[1];
						for (long long i0=b0b+stride;i0<=b0e;i0+=2*stride)
						{
							T pred;
							if (i0+stride<=b0e)
								pred=linear_fitting_dpd(pos+i0*weight[0],stride*weight[0]);
							else
								if (i0-3*stride>=b0b)
									pred=linear_fitting_ddp(pos+i0*weight[0],stride*weight[0]);
								else
									pred=linear_fitting_dp(pos+i0*weight[0],stride*weight[0]);
							#ifdef JOB_TYPE_COMPRESS
								quant_bin[quant_bin_pos]=quantize(pos+i0*weight[0],pred);
							#endif
							#ifdef JOB_TYPE_DECOMPRESS
								data[pos+i0*weight[0]]=dequantize(quant_bin_pos,pred);
							#endif
							quant_bin_pos++;
						}
					}
					for (long long i0=(b0b?b0b+stride:0);i0<=b0e;i0+=stride)
					{
						long long pos=i0*weight[0];
						for (long long i1=b1b+stride;i1<=b1e;i1+=2*stride)
						{
							T pred;
							if (i1+stride<=b1e)
								pred=linear_fitting_dpd(pos+i1*weight[1],stride*weight[1]);
							else
								if (i1-3*stride>=b1b)
									pred=linear_fitting_ddp(pos+i1*weight[1],stride*weight[1]);
								else
									pred=linear_fitting_dp(pos+i1*weight[1],stride*weight[1]);
							#ifdef JOB_TYPE_COMPRESS
								quant_bin[quant_bin_pos]=quantize(pos+i1*weight[1],pred);
							#endif
							#ifdef JOB_TYPE_DECOMPRESS
								data[pos+i1*weight[1]]=dequantize(quant_bin_pos,pred);
							#endif
							quant_bin_pos++;
						}
					}
				}
			}
		}
	}
}

#endif