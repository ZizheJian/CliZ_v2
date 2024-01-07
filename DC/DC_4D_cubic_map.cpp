#ifndef __DC_4D_CUBIC_MAP_CPP__
#define __DC_4D_CUBIC_MAP_CPP__

#include "DC.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::DC_4D_cubic_map()
	{
		long long *mx=best_it1->mx;
		long long *weight=best_it1->weight;
		int interpolation_level=0;
		for (int i=0;i<4;i++)
			interpolation_level=max(interpolation_level,(int)ceil(log2(mx[i])));
		long long quant_bin_pos=0;
		#ifdef JOB_TYPE_COMPRESS
			quant_bin[quant_bin_pos]=quantize_map(0,0);
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
			for (long long i1=0;i1<mx[1];i1+=2*stride)
				for (long long i2=0;i2<mx[2];i2+=2*stride)
					for (long long i3=0;i3<mx[3];i3+=2*stride)
					{
						long long pos=i1*weight[1]+i2*weight[2]+i3*weight[3];
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
								quant_bin[quant_bin_pos]=quantize_map(pos+i0*weight[0],pred);
							#endif
							#ifdef JOB_TYPE_DECOMPRESS
								data[pos+i0*weight[0]]=dequantize(quant_bin_pos,pred);
							#endif
							quant_bin_pos++;
						}
					}
			for (long long i0=0;i0<mx[0];i0+=stride)
				for (long long i2=0;i2<mx[2];i2+=2*stride)
					for (long long i3=0;i3<mx[3];i3+=2*stride)
					{
						long long pos=i0*weight[0]+i2*weight[2]+i3*weight[3];
						for (long long i1=stride;i1<mx[1];i1+=2*stride)
						{
							T pred;
							if (i1+3*stride<mx[1])
								if (i1-3*stride>=0)
									pred=cubic_fitting_ddpdd(pos+i1*weight[1],stride*weight[1]);
								else
									pred=quadratic_fitting_ddpd(pos+i1*weight[1],-stride*weight[1]);
							else
								if (i1+stride<mx[1])
									if (i1-3*stride>=0)
										pred=quadratic_fitting_ddpd(pos+i1*weight[1],stride*weight[1]);
									else
										pred=linear_fitting_dpd(pos+i1*weight[1],stride*weight[1]);
								else
									if (i1-5*stride>=0)
										pred=quadratic_fitting_dddp(pos+i1*weight[1],stride*weight[1]);
									else
										if (i1-3*stride>=0)
											pred=linear_fitting_ddp(pos+i1*weight[1],stride*weight[1]);
										else
											pred=constant_fitting_dp(pos+i1*weight[1],stride*weight[1]);
							#ifdef JOB_TYPE_COMPRESS
								quant_bin[quant_bin_pos]=quantize_map(pos+i1*weight[1],pred);
							#endif
							#ifdef JOB_TYPE_DECOMPRESS
								data[pos+i1*weight[1]]=dequantize(quant_bin_pos,pred);
							#endif
							quant_bin_pos++;
						}
					}
			for (long long i0=0;i0<mx[0];i0+=stride)
				for (long long i1=0;i1<mx[1];i1+=stride)
					for (long long i3=0;i3<mx[3];i3+=2*stride)
					{
						long long pos=i0*weight[0]+i1*weight[1]+i3*weight[3];
						for (long long i2=stride;i2<mx[2];i2+=2*stride)
						{
							T pred;
							if (i2+3*stride<mx[2])
								if (i2-3*stride>=0)
									pred=cubic_fitting_ddpdd(pos+i2*weight[2],stride*weight[2]);
								else
									pred=quadratic_fitting_ddpd(pos+i2*weight[2],-stride*weight[2]);
							else
								if (i2+stride<mx[2])
									if (i2-3*stride>=0)
										pred=quadratic_fitting_ddpd(pos+i2*weight[2],stride*weight[2]);
									else
										pred=linear_fitting_dpd(pos+i2*weight[2],stride*weight[2]);
								else
									if (i2-5*stride>=0)
										pred=quadratic_fitting_dddp(pos+i2*weight[2],stride*weight[2]);
									else
										if (i2-3*stride>=0)
											pred=linear_fitting_ddp(pos+i2*weight[2],stride*weight[2]);
										else
											pred=constant_fitting_dp(pos+i2*weight[2],stride*weight[2]);
							#ifdef JOB_TYPE_COMPRESS
								quant_bin[quant_bin_pos]=quantize_map(pos+i2*weight[2],pred);
							#endif
							#ifdef JOB_TYPE_DECOMPRESS
								data[pos+i2*weight[2]]=dequantize(quant_bin_pos,pred);
							#endif
							quant_bin_pos++;
						}
					}
			for (long long i0=0;i0<mx[0];i0+=stride)
				for (long long i1=0;i1<mx[1];i1+=stride)
					for (long long i2=0;i2<mx[2];i2+=stride)
					{
						long long pos=i0*weight[0]+i1*weight[1]+i2*weight[2];
						for (long long i3=stride;i3<mx[3];i3+=2*stride)
						{
							T pred;
							if (i3+3*stride<mx[3])
								if (i3-3*stride>=0)
									pred=cubic_fitting_ddpdd(pos+i3*weight[3],stride*weight[3]);
								else
									pred=quadratic_fitting_ddpd(pos+i3*weight[3],-stride*weight[3]);
							else
								if (i3+stride<mx[3])
									if (i3-3*stride>=0)
										pred=quadratic_fitting_ddpd(pos+i3*weight[3],stride*weight[3]);
									else
										pred=linear_fitting_dpd(pos+i3*weight[3],stride*weight[3]);
								else
									if (i3-5*stride>=0)
										pred=quadratic_fitting_dddp(pos+i3*weight[3],stride*weight[3]);
									else
										if (i3-3*stride>=0)
											pred=linear_fitting_ddp(pos+i3*weight[3],stride*weight[3]);
										else
											pred=constant_fitting_dp(pos+i3*weight[3],stride*weight[3]);
							#ifdef JOB_TYPE_COMPRESS
								quant_bin[quant_bin_pos]=quantize_map(pos+i3*weight[3],pred);
							#endif
							#ifdef JOB_TYPE_DECOMPRESS
								data[pos+i3*weight[3]]=dequantize(quant_bin_pos,pred);
							#endif
							quant_bin_pos++;
						}
					}
		}
	}
}

#endif