#ifndef __ENCODE_DATA_CPP__
#define __ENCODE_DATA_CPP__

#include "huffman_encode.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::encode_data()
	{
		align_cache<unsigned char>();
		int cache_digit=0;
		int code_digit=0;
		unsigned char cache=0;
		huffman_tree_c<T> &this_huffman=huffman[0];
		unordered_map<int,node_c,simple_hash> &this_nodes=this_huffman.nodes;
		for (long long i=0;i<quant_bin_num;)
		{
			node_c &this_node=this_nodes[quant_bin[i]];
			long long code=this_node.code;
			int length=this_node.length;
			int new_digit=min(8-cache_digit,length-code_digit);
			cache<<=new_digit;
			cache+=((code>>(length-code_digit-new_digit))&((1LL<<new_digit)-1));
			cache_digit+=new_digit;
			code_digit+=new_digit;
			if (cache_digit==8)
			{
				append_cache(cache);
				cache_digit=0;
				cache=0;
			}
			if (code_digit==length)
			{
				i++;
				code_digit=0;
				if (i%10000000==0)
					printf("i=%lld, bitstream_length=%lld\n",i,bitstream_length);
			}
		}
		if (cache_digit!=0)
		{
			cache<<=(8-cache_digit);
			append_cache(cache);
			cache_digit=0;
			cache=0;
		}
	}
}

#endif