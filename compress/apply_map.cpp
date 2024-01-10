#ifndef __APPLY_MAP_CPP__
#define __APPLY_MAP_CPP__

#include "compress.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::apply_map()
	{
		for (long long i=0;i<quant_bin_num;i++)
		{
			long long horiz=qb2horiz_mapping[i];
			char shift=shift_map[horiz];
			if (shift==1)
				if (quant_bin[i]==-32768)
					quant_bin[i]=32767;
				else
					quant_bin[i]--;
			if (shift==-1)
				if (quant_bin[i]==32767)
					quant_bin[i]=-32768;
				else
					quant_bin[i]++;
		}
	}
}

#endif