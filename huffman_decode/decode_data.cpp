#ifndef __DECODE_DATA_CPP__
#define __DECODE_DATA_CPP__

#include "huffman_decode.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::decode_data()
	{
		huffman_tree_c<T> &this_huffman=huffman[0];
		unordered_map<int,node_c,simple_hash> &this_nodes=this_huffman.nodes;
		int cache_digit=0;
		int nid=32767+this_nodes.size()/2;
		unsigned char cache=read_cache<unsigned char>();
		for (long long i=0;i<quant_bin_num;)
		{
			if (cache_digit==8)
			{
				read_cache(cache);
				cache_digit=0;
			}
			while ((nid>=32768) && (cache_digit<8))
			{
				if ((cache>>(7-cache_digit))&1)
					nid=this_nodes[nid].lson;
				else
					nid=this_nodes[nid].rson;
				cache_digit++;
			}
			if (nid<32768)
			{
				quant_bin[i]=nid;
				nid=32767+this_nodes.size()/2;
				i++;
			}
		}
	}
}

#endif