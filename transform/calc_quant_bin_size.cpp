#ifndef __COUNT_MAP_SIZE_CPP__
#define __COUNT_MAP_SIZE_CPP__

#include "transform.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::calc_quant_bin_size()
	{
		quant_bin_num=0;
		for (long long lat_i=0;lat_i<it2->mx[latid];lat_i++)
			for (long long lng_i=0;lng_i<it2->mx[lngid];lng_i++)
			{
				long long pos=lat_i*it2->mx[lngid]+lng_i;
				if (mask_data[pos]!=0)
					quant_bin_num++;
			}
		quant_bin_num*=data_num;
		quant_bin_num/=(it2->mx[latid]*it2->mx[lngid]);
	}
}

#endif