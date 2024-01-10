#ifndef __COLLECT_DATA_MASK_CPP__
#define __COLLECT_DATA_MASK_CPP__

#include "choose_method.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::collect_data_mask(int *mask_data_backup,hyper_iterator_c *it2_backup)
	{
		for (long long lat_i=0;lat_i<it2->mx[latid];lat_i++)
			for (long long lng_i=0;lng_i<it2->mx[lngid];lng_i++)
			{
				long long lat_j=((2*lat_i<it2->mx[latid])?(lat_i+floor((it2_backup->mx[latid]-it2->mx[latid])/3)):(lat_i+it2_backup->mx[latid]-it2->mx[latid]-floor((it2_backup->mx[latid]-it2->mx[latid])/3)));
				long long lng_j=((2*lng_i<it2->mx[lngid])?(lng_i+floor((it2_backup->mx[lngid]-it2->mx[lngid])/3)):(lng_i+it2_backup->mx[lngid]-it2->mx[lngid]-floor((it2_backup->mx[lngid]-it2->mx[lngid])/3)));
				mask_data[lat_i*it2->mx[lngid]+lng_i]=mask_data_backup[lat_j*it2_backup->mx[lngid]+lng_j];
			}
	}
}

#endif