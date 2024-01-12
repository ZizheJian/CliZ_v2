#ifndef __ENCODE_DATA_WITH_MAP_CPP__
#define __ENCODE_DATA_WITH_MAP_CPP__

#include "huffman_encode.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::encode_data_with_map()
	{
		int cache_digit=0;
		int code_digit=0;
		unsigned char cache=0;
		huffman_tree_c<T> &this_huffman_0=huffman[0];
		huffman_tree_c<T> &this_huffman_1=huffman[1];
		unordered_map<int,node_c,simple_hash> &this_nodes_0=this_huffman_0.nodes;
		unordered_map<int,node_c,simple_hash> &this_nodes_1=this_huffman_1.nodes;
		for (long long i=0;i<quant_bin_num;)
		{
			node_c &this_node=(width_map[qb2horiz_mapping[i]]==0)?this_nodes_0[quant_bin[i]]:this_nodes_1[quant_bin[i]];
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