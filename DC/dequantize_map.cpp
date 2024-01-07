#ifndef __DEQUANTIZE_MAP_CPP__
#define __DEQUANTIZE_MAP_CPP__

#include "DC.hpp2"

namespace cliz
{
	template<typename T>
	T task_c<T>::dequantize_map(long long i,T pred)
	{
		if (quant_bin[i]==-32768)
		{
			T irr;
			memcpy(&irr,bitstream+bitstream_index,sizeof(T));
			bitstream_index+=sizeof(T);
			return irr;
		}
		else
			return pred+quant_bin[i]*2*err_bound;
	}
}

#endif