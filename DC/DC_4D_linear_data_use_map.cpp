#ifndef __DC_4D_LINEAR_DATA_USE_MAP_CPP__
#define __DC_4D_LINEAR_DATA_USE_MAP_CPP__

#include "DC.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::DC_4D_linear_data_use_map()
	{
		long long *mx=best_it1->mx;
		long long *weight=best_it1->weight;
		int interpolation_level=0;
		for (int i=0;i<4;i++)
			interpolation_level=max(interpolation_level,(int)ceil(log2(mx[i])));
		long long quant_bin_pos=0;
		#ifdef JOB_TYPE_COMPRESS
			quant_bin[quant_bin_pos]=quantize(0,0);
			qb2horiz_mapping[quant_bin_pos]=pos2horiz_mapping[0];
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
				for (long long b1b=0;b1b<mx[1];b1b+=stride*32)
				{
					long long b1e=min(mx[1]-1,b1b+stride*32);
					for (long long b2b=0;b2b<mx[2];b2b+=stride*32)
					{
						long long b2e=min(mx[2]-1,b2b+stride*32);
						for (long long b3b=0;b3b<mx[3];b3b+=stride*32)
						{
							long long b3e=min(mx[3]-1,b3b+stride*32);
							for (long long i1=(b1b?b1b+2*stride:0);i1<=b1e;i1+=2*stride)
								for (long long i2=(b2b?b2b+2*stride:0);i2<=b2e;i2+=2*stride)
									for (long long i3=(b3b?b3b+2*stride:0);i3<=b3e;i3+=2*stride)
									{
										long long pos=i1*weight[1]+i2*weight[2]+i3*weight[3];
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
												quant_bin[quant_bin_pos]=quantize(pos+i0*weight[0],pred);
												qb2horiz_mapping[quant_bin_pos]=pos2horiz_mapping[pos+i0*weight[0]];
											#endif
											#ifdef JOB_TYPE_DECOMPRESS
												printf("Error: DC_4D_linear_data_use_map shouldn't be called during decompression.\n");
												exit(0);
											#endif
											quant_bin_pos++;
										}
									}
							for (long long i0=(b0b?b0b+stride:0);i0<=b0e;i0+=stride)
								for (long long i2=(b2b?b2b+2*stride:0);i2<=b2e;i2+=2*stride)
									for (long long i3=(b3b?b3b+2*stride:0);i3<=b3e;i3+=2*stride)
									{
										long long pos=i0*weight[0]+i2*weight[2]+i3*weight[3];
										for (long long i1=b1b+stride;i1<=b1e;i1+=2*stride)
										{
											T pred;
											if (i1+stride<=b1e)
												pred=linear_fitting_dpd(pos+i1*weight[1],stride*weight[1]);
											else
												if (i1-3*stride>=b1b)
													pred=linear_fitting_ddp(pos+i1*weight[1],stride*weight[1]);
												else
													pred=constant_fitting_dp(pos+i1*weight[1],stride*weight[1]);
											#ifdef JOB_TYPE_COMPRESS
												quant_bin[quant_bin_pos]=quantize(pos+i1*weight[1],pred);
												qb2horiz_mapping[quant_bin_pos]=pos2horiz_mapping[pos+i1*weight[1]];
											#endif
											#ifdef JOB_TYPE_DECOMPRESS
												printf("Error: DC_4D_linear_data_use_map shouldn't be called during decompression.\n");
												exit(0);
											#endif
											quant_bin_pos++;
										}
									}
							for (long long i0=(b0b?b0b+stride:0);i0<=b0e;i0+=stride)
								for (long long i1=(b1b?b1b+stride:0);i1<=b1e;i1+=stride)
									for (long long i3=(b3b?b3b+2*stride:0);i3<=b3e;i3+=2*stride)
									{
										long long pos=i0*weight[0]+i1*weight[1]+i3*weight[3];
										for (long long i2=b2b+stride;i2<=b2e;i2+=2*stride)
										{
											T pred;
											if (i2+stride<=b2e)
												pred=linear_fitting_dpd(pos+i2*weight[2],stride*weight[2]);
											else
												if (i2-3*stride>=b2b)
													pred=linear_fitting_ddp(pos+i2*weight[2],stride*weight[2]);
												else
													pred=constant_fitting_dp(pos+i2*weight[2],stride*weight[2]);
											#ifdef JOB_TYPE_COMPRESS
												quant_bin[quant_bin_pos]=quantize(pos+i2*weight[2],pred);
												qb2horiz_mapping[quant_bin_pos]=pos2horiz_mapping[pos+i2*weight[2]];
											#endif
											#ifdef JOB_TYPE_DECOMPRESS
												printf("Error: DC_4D_linear_data_use_map shouldn't be called during decompression.\n");
												exit(0);
											#endif
											quant_bin_pos++;
										}
									}
							for (long long i0=(b0b?b0b+stride:0);i0<=b0e;i0+=stride)
								for (long long i1=(b1b?b1b+stride:0);i1<=b1e;i1+=stride)
									for (long long i2=(b2b?b2b+stride:0);i2<=b2e;i2+=stride)
									{
										long long pos=i0*weight[0]+i1*weight[1]+i2*weight[2];
										for (long long i3=b3b+stride;i3<=b3e;i3+=2*stride)
										{
											T pred;
											if (i3+stride<=b3e)
												pred=linear_fitting_dpd(pos+i3*weight[3],stride*weight[3]);
											else
												if (i3-3*stride>=b3b)
													pred=linear_fitting_ddp(pos+i3*weight[3],stride*weight[3]);
												else
													pred=constant_fitting_dp(pos+i3*weight[3],stride*weight[3]);
											#ifdef JOB_TYPE_COMPRESS
												quant_bin[quant_bin_pos]=quantize(pos+i3*weight[3],pred);
												qb2horiz_mapping[quant_bin_pos]=pos2horiz_mapping[pos+i3*weight[3]];
											#endif
											#ifdef JOB_TYPE_DECOMPRESS
												printf("Error: DC_4D_linear_data_use_map shouldn't be called during decompression.\n");
												exit(0);
											#endif
											quant_bin_pos++;
										}
									}
						}
					}
				}
			}
		}
	}
}

#endif