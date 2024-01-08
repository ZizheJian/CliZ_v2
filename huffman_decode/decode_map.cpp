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
		long long bitstream_index_backup=bitstream_index;
		bitstream=map_bitstream;
		bitstream_index=map_bitstream_index;
		align_cache<unsigned char>();
		int cache_digit=0;
		int nid=32767+this_nodes_map.size()/2;
		unsigned char cache=read_cache<unsigned char>();
		for (long long i=0;i<it2->mx[latid]*it2->mx[lngid];)
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
		map_bitstream_index=bitstream_index;
		bitstream_index=bitstream_index_backup;

		huffman_tree_c<T> &this_huffman_0=huffman[0];
		huffman_tree_c<T> &this_huffman_1=huffman[1];
		unordered_map<int,node_c,simple_hash> &this_nodes_0=this_huffman_0.nodes;
		unordered_map<int,node_c,simple_hash> &this_nodes_1=this_huffman_1.nodes;
		align_cache<unsigned char>();
		cache_digit=0;
		nid=(width_map[qb2horiz_mapping[0]]==0)?(32767+this_nodes_0.size()/2):(32767+this_nodes_1.size()/2);
		cache=read_cache<unsigned char>();
		for (long long i=0;i<data_num;)
		{
			if (cache_digit==8)
			{
				read_cache(cache);
				cache_digit=0;
			}
			unordered_map<int,node_c,simple_hash> &this_nodes=(width_map[qb2horiz_mapping[i]]==0)?this_nodes_0:this_nodes_1;
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
				i++;
				if (i<data_num)
					nid=(width_map[qb2horiz_mapping[i]]==0)?(32767+this_nodes_0.size()/2):(32767+this_nodes_1.size()/2);
			}
		}
	}
}

#endif