#ifndef __GENERATE_MAP_CPP__
#define __GENERATE_MAP_CPP__

#include "compress.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::generate_map()
	{
		long long other_data_num=data_num/map_num;
		for (long long i=0;i<map_num;i++)
		{
			shift_map[i]=-1;
			width_map[i]=0;
			if (horiz_hist[5*i+2+shift_map[i]]<horiz_hist[5*i+2])
				shift_map[i]=0;
			if (horiz_hist[5*i+2+shift_map[i]]<horiz_hist[5*i+3])
				shift_map[i]=1;
			if (horiz_hist[5*i+2+shift_map[i]]<0.4*other_data_num)
				width_map[i]=1;
		}
	}
}

#endif