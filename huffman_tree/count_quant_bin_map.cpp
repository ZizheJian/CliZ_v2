#ifndef __COUNT_QUANT_BIN_MAP_CPP__
#define __COUNT_QUANT_BIN_MAP_CPP__

#include "huffman_tree.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::count_quant_bin_map()
	{
		huffman_tree_c<T> &this_huffman_0=huffman[0];
		huffman_tree_c<T> &this_huffman_1=huffman[1];
		unordered_map<int,node_c,simple_hash> &this_nodes_0=this_huffman_0.nodes;
		unordered_map<int,node_c,simple_hash> &this_nodes_1=this_huffman_1.nodes;
		for (long long i=0;i<quant_bin_num;i++)
			if (width_map[qb2horiz_mapping[i]]==0)
				this_nodes_0[quant_bin[i]].count++;
			else
				this_nodes_1[quant_bin[i]].count++;
		huffman_tree_c<T> &this_huffman_map=huffman[2];
		unordered_map<int,node_c,simple_hash> &this_nodes_map=this_huffman_map.nodes;
		for (long long i=0;i<map_num;i++)
			this_nodes_map[width_map[i]*3+shift_map[i]+1].count++;
	}
}

#endif