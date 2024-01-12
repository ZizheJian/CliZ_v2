#ifndef __DECODE_MAP_CPP__
#define __DECODE_MAP_CPP__

#include "huffman_decode.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::decode_map()
	{
		huffman_tree_c<T> &this_huffman_map=huffman[2];
		unordered_map<int,node_c,simple_hash> &this_nodes_map=this_huffman_map.nodes;
		unsigned char *bitstream_backup=bitstream;
		long long bitstream_index_backup=bitstream_start;
		bitstream=map_bitstream;
		bitstream_start=map_bitstream_start;
		int cache_digit=0;
		int nid=32767+this_nodes_map.size()/2;
		unsigned char cache=read_cache<unsigned char>();
		for (long long i=0;i<map_num;)
		{
			if (cache_digit==8)
			{
				read_cache(cache);
				cache_digit=0;
			}
			while ((nid>=32768) && (cache_digit<8))
			{
				if ((cache>>(7-cache_digit))&1)
					nid=this_nodes_map[nid].lson;
				else
					nid=this_nodes_map[nid].rson;
				cache_digit++;
			}
			if (nid<32768)
			{
				width_map[i]=nid/3;
				shift_map[i]=nid%3-1;
				nid=32767+this_nodes_map.size()/2;
				i++;
			}
		}
		bitstream=bitstream_backup;
		map_bitstream_start=bitstream_start;
		bitstream_start=bitstream_index_backup;
	}
}

#endif