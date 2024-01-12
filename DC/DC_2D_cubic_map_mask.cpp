#ifndef __DC_2D_CUBIC_MAP_MASK_CPP__
#define __DC_2D_CUBIC_MAP_MASK_CPP__

#include "DC.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::DC_2D_cubic_map_mask()
	{
		long long *mx=best_it1->mx;
		long long *weight=best_it1->weight;
		int interpolation_level=0;
		for (int i=0;i<2;i++)
			interpolation_level=max(interpolation_level,(int)ceil(log2(mx[i])));
		long long quant_bin_pos=0;
		if (mask_data[pos2horiz_mapping[0]]!=0)
		{
			#ifdef JOB_TYPE_COMPRESS
				printf("Error: DC_2D_linear_map_mask shouldn't be called during compression.\n");
				exit(0);
			#endif
			#ifdef JOB_TYPE_DECOMPRESS
				qb2horiz_mapping[quant_bin_pos]=pos2horiz_mapping[0];
			#endif
			quant_bin_pos++;
		}
		double err_bound_backup=err_bound;
		for (int lv=interpolation_level-1;lv>=0;lv--)
		{
			if (lv>=2)
				err_bound=err_bound_backup*0.5;
			else
				err_bound=err_bound_backup;
			err_bound_reciprocal=1/err_bound;
			long long stride=1<<lv;
			for (long long i1=0;i1<mx[1];i1+=2*stride)
			{
				long long pos=i1*weight[1];
				for (long long i0=stride;i0<mx[0];i0+=2*stride)
				{
					if (mask_data[pos2horiz_mapping[pos+i0*weight[0]]]==0)
						continue;
					#ifdef JOB_TYPE_COMPRESS
						printf("Error: DC_2D_linear_map_mask shouldn't be called during compression.\n");
						exit(0);
					#endif
					#ifdef JOB_TYPE_DECOMPRESS
						qb2horiz_mapping[quant_bin_pos]=pos2horiz_mapping[pos+i0*weight[0]];
					#endif
					quant_bin_pos++;
				}
			}
			for (long long i0=0;i0<mx[0];i0+=stride)
			{
				long long pos=i0*weight[0];
				for (long long i1=stride;i1<mx[1];i1+=2*stride)
				{
					if (mask_data[pos2horiz_mapping[pos+i1*weight[1]]]==0)
						continue;
					#ifdef JOB_TYPE_COMPRESS
						printf("Error: DC_2D_linear_map_mask shouldn't be called during compression.\n");
						exit(0);
					#endif
					#ifdef JOB_TYPE_DECOMPRESS
						qb2horiz_mapping[quant_bin_pos]=pos2horiz_mapping[pos+i1*weight[1]];
					#endif
					quant_bin_pos++;
				}
			}
		}
	}
}

#endif