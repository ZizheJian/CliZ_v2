#ifndef __GENERATE_POS2HORIZ_MAPPING_CPP__
#define __GENERATE_POS2HORIZ_MAPPING_CPP__

#include "transform.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::generate_pos2horiz_mapping()
	{
		long long lat_weight=it2->weight[latid];
		long long lat_mx=it2->mx[latid];
		long long lng_weight=it2->weight[lngid];
		long long lng_mx=it2->mx[lngid];
		for (long long i=0,lat_i=0,lat_j=0,lng_i=0,lng_j=0;i<data_num;i++,lat_j++,lng_j++)
		{
			if (lat_j==lat_weight)
			{
				lat_j=0;
				lat_i++;
			}
			if (lat_i==lat_mx)
				lat_i=0;
			if (lng_j==lng_weight)
			{
				lng_j=0;
				lng_i++;
			}
			if (lng_i==lng_mx)
				lng_i=0;
			pos2horiz_mapping[i]=lat_i*lat_weight+lng_i*lng_weight;
		}
	}
}

#endif