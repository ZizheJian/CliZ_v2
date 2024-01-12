#ifndef __DEQUANTIZE_CPP__
#define __DEQUANTIZE_CPP__

#include "DC.hpp2"

namespace cliz
{
	template<typename T>
	T task_c<T>::dequantize(long long i,T pred)
	{
		if (quant_bin[i]==-32768)
		{
			T irr;
			memcpy(&irr,bitstream+bitstream_start,sizeof(T));
			bitstream_start+=sizeof(T);
			return irr;
		}
		else
			return pred+quant_bin[i]*2*err_bound;
	}
}

#endif