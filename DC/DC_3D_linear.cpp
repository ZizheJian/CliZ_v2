#ifndef __DC_3D_LINEAR_CPP__
#define __DC_3D_LINEAR_CPP__

#include "DC.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::DC_3D_linear()
	{
		//FILE *qb_file=fopen("result/qb.txt","a");
		long long *mx=best_it1->mx;
		long long *weight=best_it1->weight;
		int interpolation_level=0;
		for (int i=0;i<3;i++)
			interpolation_level=max(interpolation_level,(int)ceil(log2(mx[i])));
		long long quant_bin_pos=0;
		quant_bin[quant_bin_pos]=quantize(0,0);
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
				long long b0e=min(mx[0],b0b+stride*32);
				for (long long b1b=0;b1b<mx[1];b1b+=stride*32)
				{
					long long b1e=min(mx[1],b1b+stride*32);
					for (long long b2b=0;b2b<mx[2];b2b+=stride*32)
					{
						long long b2e=min(mx[2],b2b+stride*32);
						//printf("stride=%lld, b0b=%lld, b1b=%lld, b2b=%lld\n",stride,b0b,b1b,b2b);
						for (long long i1=b1b;i1<b1e;i1+=2*stride)
							for (long long i2=b2b;i2<b2e;i2+=2*stride)
							{
								//printf("i0=%ld, i1=%ld, i2=%ld\n",b0b,i1,i2);
								long long pos=i1*weight[1]+i2*weight[2];
								//printf("begin=[%lld,%lld,%lld], end=[%lld,%lld,%lld]\n",b0b,i1,i2,b0e,i1,i2);
								for (long long i0=b0b+stride;i0<b0e;i0+=2*stride)
								{
									//if (quant_bin_pos==539)
									//	printf("%lld %lld %lld %lld %lld %lld %lld\n",stride,b0b,b1b,b2b,i0,i1,i2);
									T pred;
									if (i0+stride<b0e)
										pred=linear_fitting_dpd(pos+i0*weight[0],stride*weight[0]);
									else
										if (i0-3*stride>=b0b)
											pred=linear_fitting_ddp(pos+i0*weight[0],stride*weight[0]);
										else
											pred=linear_fitting_dp(pos+i0*weight[0],stride*weight[0]);
									quant_bin[quant_bin_pos]=quantize(pos+i0*weight[0],pred);
									//if (quant_bin_pos<10000)
									//	fprintf(qb_file,"%d\n",quant_bin[quant_bin_pos]);
									//printf("quant_bin[%d]=%d\n",quant_bin_pos,quant_bin[quant_bin_pos]);
									//getchar();
									quant_bin_pos++;
								}
							}
						//printf("quant_bin_pos=%lld\n",quant_bin_pos);
						//getchar();
						for (long long i0=b0b;i0<b0e;i0+=stride)
							for (long long i2=b2b;i2<b2e;i2+=2*stride)
							{
								//printf("i0=%ld, i1=%ld, i2=%ld\n",i0,b1b,i2);
								long long pos=i0*weight[0]+i2*weight[2];
								//printf("begin=[%lld,%lld,%lld], end=[%lld,%lld,%lld]\n",i0,b1b,i2,i0,b1e,i2);
								for (long long i1=b1b+stride;i1<b1e;i1+=2*stride)
								{
									//if (quant_bin_pos==539)
									//{
									//	printf("%lld %lld %lld %lld %lld %lld %lld\n",stride,b0b,b1b,b2b,i0,i1,i2);
									//	getchar();
									//}
									T pred;
									if (i1+stride<b1e)
										pred=linear_fitting_dpd(pos+i1*weight[1],stride*weight[1]);
									else
										if (i1-3*stride>=b1b)
											pred=linear_fitting_ddp(pos+i1*weight[1],stride*weight[1]);
										else
											pred=linear_fitting_dp(pos+i1*weight[1],stride*weight[1]);
									quant_bin[quant_bin_pos]=quantize(pos+i1*weight[1],pred);
									//if (quant_bin_pos<10000)
									//	fprintf(qb_file,"%d\n",quant_bin[quant_bin_pos]);
									//if (quant_bin_pos==24999063)
									//	printf("quant_bin[%d]=%d\n",quant_bin_pos,quant_bin[quant_bin_pos]);
									//getchar();
									quant_bin_pos++;
								}
							}
						//printf("quant_bin_pos=%lld\n",quant_bin_pos);
						//getchar();
						for (long long i0=b0b;i0<b0e;i0+=stride)
							for (long long i1=b1b;i1<b1e;i1+=stride)
							{
								//printf("i0=%ld, i1=%ld, i2=%ld\n",i0,i1,b2b);
								long long pos=i0*weight[0]+i1*weight[1];
								//printf("begin=[%lld,%lld,%lld], end=[%lld,%lld,%lld]\n",i0,i1,b2b,i0,i1,b2e);
								for (long long i2=b2b+stride;i2<b2e;i2+=2*stride)
								{
									//if (quant_bin_pos==539)
									//	printf("%lld %lld %lld %lld %lld %lld %lld\n",stride,b0b,b1b,b2b,i0,i1,i2);
									T pred;
									if (i2+stride<b2e)
										pred=linear_fitting_dpd(pos+i2*weight[2],stride*weight[2]);
									else
										if (i2-3*stride>=b2b)
											pred=linear_fitting_ddp(pos+i2*weight[2],stride*weight[2]);
										else
											pred=linear_fitting_dp(pos+i2*weight[2],stride*weight[2]);
									//if (quant_bin_pos==539)
									//	printf("data=%f, pred=%f\n",data[pos+i2*weight[2]],pred);
									quant_bin[quant_bin_pos]=quantize(pos+i2*weight[2],pred);
									//if (quant_bin_pos==539)
									//{
									//	printf("error_bound=%f\n",err_bound);
									//	printf("quant_bin[%d]=%d\n",quant_bin_pos,quant_bin[quant_bin_pos]);
									//}
									//if (quant_bin_pos<10000)
									//	fprintf(qb_file,"%d\n",quant_bin[quant_bin_pos]);
									//printf("quant_bin[%d]=%d\n",quant_bin_pos,quant_bin[quant_bin_pos]);
									//getchar();
									quant_bin_pos++;
								}
							}
						//printf("quant_bin_pos=%lld\n",quant_bin_pos);
						//getchar();
					}
				}
			}
			//printf("%lld %lld\n",stride,quant_bin_pos);
			//getchar();
		}
		//printf("quant_bin_pos=%lld\n",quant_bin_pos);
		//fclose(qb_file);


		/*for (int lv=interpolation_level-1;lv>=0;lv--)
		{
			if (lv>=2)
				err_bound=err_bound_backup*0.5;
			else
				err_bound=err_bound_backup;
			err_bound_reciprocal=1/err_bound;
			long long stride=1<<lv;
			for (long long b0b=0;b0b<mx[0];b0b+=stride*32)
			{
				long long b0e=min(mx[0],b0b+stride*32+1);
				for (long long b1b=0;b1b<mx[1];b1b+=stride*32)
				{
					long long b1e=min(mx[1],b1b+stride*32+1);
					for (long long b2b=0;b2b<mx[2];b2b+=stride*32)
					{
						long long b2e=min(mx[2],b2b+stride*32+1);
						//printf("stride=%lld, b0b=%lld, b1b=%lld, b2b=%lld\n",stride,b0b,b1b,b2b);
						for (long long i1=(b1b?b1b+2*stride:0);i1<b1e;i1+=2*stride)
							for (long long i2=(b2b?b2b+2*stride:0);i2<b2e;i2+=2*stride)
							{
								//printf("i0=%ld, i1=%ld, i2=%ld\n",b0b,i1,i2);
								long long pos=i1*weight[1]+i2*weight[2];
								//printf("begin=[%lld,%lld,%lld], end=[%lld,%lld,%lld]\n",b0b,i1,i2,b0e,i1,i2);
								for (long long i0=b0b+stride;i0<b0e;i0+=2*stride)
								{
									//if (quant_bin_pos==539)
									//	printf("%lld %lld %lld %lld %lld %lld %lld\n",stride,b0b,b1b,b2b,i0,i1,i2);
									T pred;
									if (i0+stride<b0e)
										pred=linear_fitting_dpd(pos+i0*weight[0],stride*weight[0]);
									else
										if (i0-3*stride>=b0b)
											pred=linear_fitting_ddp(pos+i0*weight[0],stride*weight[0]);
										else
											pred=linear_fitting_dp(pos+i0*weight[0],stride*weight[0]);
									quant_bin[quant_bin_pos]=quantize(pos+i0*weight[0],pred);
									//if (quant_bin_pos<10000)
									//	fprintf(qb_file,"%d\n",quant_bin[quant_bin_pos]);
									//printf("quant_bin[%d]=%d\n",quant_bin_pos,quant_bin[quant_bin_pos]);
									//getchar();
									quant_bin_pos++;
								}
							}
						//printf("quant_bin_pos=%lld\n",quant_bin_pos);
						//getchar();
						for (long long i0=(b0b?b0b+stride:0);i0<b0e;i0+=stride)
							for (long long i2=(b2b?b2b+2*stride:0);i2<b2e;i2+=2*stride)
							{
								//printf("i0=%ld, i1=%ld, i2=%ld\n",i0,b1b,i2);
								long long pos=i0*weight[0]+i2*weight[2];
								//printf("begin=[%lld,%lld,%lld], end=[%lld,%lld,%lld]\n",i0,b1b,i2,i0,b1e,i2);
								for (long long i1=b1b+stride;i1<b1e;i1+=2*stride)
								{
									//if (quant_bin_pos==539)
									//{
									//	printf("%lld %lld %lld %lld %lld %lld %lld\n",stride,b0b,b1b,b2b,i0,i1,i2);
									//	getchar();
									//}
									T pred;
									if (i1+stride<b1e)
										pred=linear_fitting_dpd(pos+i1*weight[1],stride*weight[1]);
									else
										if (i1-3*stride>=b1b)
											pred=linear_fitting_ddp(pos+i1*weight[1],stride*weight[1]);
										else
											pred=linear_fitting_dp(pos+i1*weight[1],stride*weight[1]);
									quant_bin[quant_bin_pos]=quantize(pos+i1*weight[1],pred);
									//if (quant_bin_pos<10000)
									//	fprintf(qb_file,"%d\n",quant_bin[quant_bin_pos]);
									//if (quant_bin_pos==24999063)
									//	printf("quant_bin[%d]=%d\n",quant_bin_pos,quant_bin[quant_bin_pos]);
									//getchar();
									quant_bin_pos++;
								}
							}
						//printf("quant_bin_pos=%lld\n",quant_bin_pos);
						//getchar();
						for (long long i0=(b0b?b0b+stride:0);i0<b0e;i0+=stride)
							for (long long i1=(b1b?b1b+stride:0);i1<b1e;i1+=stride)
							{
								//printf("i0=%ld, i1=%ld, i2=%ld\n",i0,i1,b2b);
								long long pos=i0*weight[0]+i1*weight[1];
								//printf("begin=[%lld,%lld,%lld], end=[%lld,%lld,%lld]\n",i0,i1,b2b,i0,i1,b2e);
								for (long long i2=b2b+stride;i2<b2e;i2+=2*stride)
								{
									//if (quant_bin_pos==539)
									//	printf("%lld %lld %lld %lld %lld %lld %lld\n",stride,b0b,b1b,b2b,i0,i1,i2);
									T pred;
									if (i2+stride<b2e)
										pred=linear_fitting_dpd(pos+i2*weight[2],stride*weight[2]);
									else
										if (i2-3*stride>=b2b)
											pred=linear_fitting_ddp(pos+i2*weight[2],stride*weight[2]);
										else
											pred=linear_fitting_dp(pos+i2*weight[2],stride*weight[2]);
									//if (quant_bin_pos==539)
									//	printf("data=%f, pred=%f\n",data[pos+i2*weight[2]],pred);
									quant_bin[quant_bin_pos]=quantize(pos+i2*weight[2],pred);
									//if (quant_bin_pos==539)
									//{
									//	printf("error_bound=%f\n",err_bound);
									//	printf("quant_bin[%d]=%d\n",quant_bin_pos,quant_bin[quant_bin_pos]);
									//}
									//if (quant_bin_pos<10000)
									//	fprintf(qb_file,"%d\n",quant_bin[quant_bin_pos]);
									//printf("quant_bin[%d]=%d\n",quant_bin_pos,quant_bin[quant_bin_pos]);
									//getchar();
									quant_bin_pos++;
								}
							}
						//printf("quant_bin_pos=%lld\n",quant_bin_pos);
						//getchar();
					}
				}
			}
			//printf("%lld %lld\n",stride,quant_bin_pos);
			//getchar();
		}
		//printf("quant_bin_pos=%lld\n",quant_bin_pos);
		//fclose(qb_file);*/
	}
}

#endif