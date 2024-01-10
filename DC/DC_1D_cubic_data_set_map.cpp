#ifndef __DC_1D_CUBIC_DATA_SET_MAP_CPP__
#define __DC_1D_CUBIC_DATA_SET_MAP_CPP__

#include "DC.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::DC_1D_cubic_data_set_map()
	{
		long long *mx=best_it1->mx;
		long long *weight=best_it1->weight;
		int interpolation_level=0;
		for (int i=0;i<1;i++)
			interpolation_level=max(interpolation_level,(int)ceil(log2(mx[i])));
		quant_bin_num=0;
		#ifdef JOB_TYPE_COMPRESS
			quant_bin[quant_bin_num]=quantize(0,0);
			qb2horiz_mapping[quant_bin_num]=pos2horiz_mapping[0];
			if (abs(quant_bin[quant_bin_num])<=2)
				horiz_hist[qb2horiz_mapping[quant_bin_num]*5+quant_bin[quant_bin_num]+2]++;
		#endif
		#ifdef JOB_TYPE_DECOMPRESS
			printf("Error: DC_1D_linear_data_set_map shouldn't be called during decompression.\n");
			exit(0);
		#endif
		quant_bin_num++;
		double err_bound_backup=err_bound;
		for (int lv=interpolation_level-1;lv>=0;lv--)
		{
			if (lv>=2)
				err_bound=err_bound_backup*0.5;
			else
				err_bound=err_bound_backup;
			err_bound_reciprocal=1/err_bound;
			long long stride=1<<lv;
			long long pos=0;
			for (long long i0=stride;i0<mx[0];i0+=2*stride)
			{
				T pred;
				if (i0+3*stride<mx[0])
					if (i0-3*stride>=0)
						pred=cubic_fitting_ddpdd(pos+i0*weight[0],stride*weight[0]);
					else
						pred=quadratic_fitting_ddpd(pos+i0*weight[0],-stride*weight[0]);
				else
					if (i0+stride<mx[0])
						if (i0-3*stride>=0)
							pred=quadratic_fitting_ddpd(pos+i0*weight[0],stride*weight[0]);
						else
							pred=linear_fitting_dpd(pos+i0*weight[0],stride*weight[0]);
					else
						if (i0-5*stride>=0)
							pred=quadratic_fitting_dddp(pos+i0*weight[0],stride*weight[0]);
						else
							if (i0-3*stride>=0)
								pred=linear_fitting_ddp(pos+i0*weight[0],stride*weight[0]);
							else
								pred=constant_fitting_dp(pos+i0*weight[0],stride*weight[0]);
				#ifdef JOB_TYPE_COMPRESS
					short qb=quantize(pos+i0*weight[0],pred);
					quant_bin[quant_bin_num]=qb;
					long long horiz=pos2horiz_mapping[pos+i0*weight[0]];
					qb2horiz_mapping[quant_bin_num]=horiz;
					if (abs(qb)<=2)
						horiz_hist[horiz*5+qb+2]++;
				#endif
				#ifdef JOB_TYPE_DECOMPRESS
					printf("Error: DC_1D_linear_data_set_map shouldn't be called during decompression.\n");
					exit(0);
				#endif
				quant_bin_num++;
			}
		}
	}
}

#endif