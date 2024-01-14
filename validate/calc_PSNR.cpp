#ifndef __CALC_PSNR_CPP__
#define __CALC_PSNR_CPP__

#include "validate.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::calc_PSNR()
	{
		T MSE=0;
		T mx=0;
		if (mask_file_path!=NULL)
		{
			mask_file=fopen(mask_file_path,"rb");
			new_data(mask_data,it2->mx[latid]*it2->mx[lngid]);
			fread(mask_data,sizeof(int),it2->mx[latid]*it2->mx[lngid],mask_file);
			fclose(mask_file);
		}
		long long actual_data_num=0;
		for (long long i=0;i<data_num;i++)
		{
			bool valid=true;
			if (mask_file!=NULL)
			{
				long long lat_i=(i/it2->weight[latid])%it2->mx[latid];
				long long lng_i=(i/it2->weight[lngid])%it2->mx[lngid];
				if (mask_data[lat_i*it2->mx[lngid]+lng_i]==0)
					valid=false;
			}
			if (valid)
			{
				MSE+=(src_data[i]-dec_data[i])*(src_data[i]-dec_data[i]);
				mx=max(mx,abs(src_data[i]));
				actual_data_num++;
			}
		}
		MSE/=actual_data_num;
		T PSNR=10*log10(mx*mx/MSE);
		printf("PSNR= %f\n",(float)PSNR);
		delete_data(mask_data);
	}
}

#endif
