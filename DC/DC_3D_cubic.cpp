#ifndef __DC_3D_CUBIC_CPP__
#define __DC_3D_CUBIC_CPP__

#include "DC.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::DC_3D_cubic()
	{
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
						for (long long i1=b1b;i1<b1e;i1+=2*stride)
							for (long long i2=b2b;i2<b2e;i2+=2*stride)
							{
								long long pos=i1*weight[1]+i2*weight[2];
								for (long long i0=b0b+stride;i0<b0e;i0+=2*stride)
								{
									//printf("%lld %lld %lld %lld %lld %lld %lld\n",stride,b0b,b1b,b2b,i0,i1,i2);
									T pred=cubic_fitting(pos+b0b*weight[0],pos+i0*weight[0],pos+b0e*weight[0],stride*weight[0]);
									quant_bin[quant_bin_pos]=quantize(pos+i0*weight[0],pred);
									quant_bin_pos++;
								}
							}
						for (long long i0=b0b;i0<b0e;i0+=stride)
							for (long long i2=b2b;i2<b2e;i2+=2*stride)
							{
								long long pos=i0*weight[0]+i2*weight[2];
								for (long long i1=b1b+stride;i1<b1e;i1+=2*stride)
								{
									//printf("%lld %lld %lld %lld %lld %lld %lld\n",stride,b0b,b1b,b2b,i0,i1,i2);
									T pred=cubic_fitting(pos+b1b*weight[1],pos+i1*weight[1],pos+b1e*weight[1],stride*weight[1]);
									quant_bin[quant_bin_pos]=quantize(pos+i1*weight[1],pred);
									quant_bin_pos++;
								}
							}
						for (long long i0=b0b;i0<b0e;i0+=stride)
							for (long long i1=b1b;i1<b1e;i1+=stride)
							{
								long long pos=i0*weight[0]+i1*weight[1];
								for (long long i2=b2b+stride;i2<b2e;i2+=2*stride)
								{
									//printf("%lld %lld %lld %lld %lld %lld %lld\n",stride,b0b,b1b,b2b,i0,i1,i2);
									T pred=cubic_fitting(pos+b2b*weight[2],pos+i2*weight[2],pos+b2e*weight[2],stride*weight[2]);
									quant_bin[quant_bin_pos]=quantize(pos+i2*weight[2],pred);
									quant_bin_pos++;
								}
							}
					}
				}
			}
			//printf("%lld %lld\n",stride,quant_bin_pos);
			//getchar();
		}
		//printf("%lld\n",quant_bin_pos);
	}
}

#endif