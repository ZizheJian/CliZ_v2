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
			memcpy(&irr,bitstream+bitstream_index,sizeof(T));
			bitstream_index+=sizeof(T);
			//printf("i=???, data=%f, pred=%f, bin=%d\n",irr,pred,-32768);
			return irr;
		}
		else
		{
			//printf("i=???, data=%f, pred=%f, bin=%d\n",pred+quant_bin[i]*2*err_bound,pred,quant_bin[i]);
			return pred+quant_bin[i]*2*err_bound;
		}
	}
}

#endif