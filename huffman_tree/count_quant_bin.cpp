#ifndef __COUNT_QUANT_BIN_CPP__
#define __COUNT_QUANT_BIN_CPP__

#include "huffman_tree.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::count_quant_bin()
	{
		huffman_tree_c<T> &this_huffman=huffman[0];
		unordered_map<int,node_c,simple_hash> &this_nodes=this_huffman.nodes;
		for (long long i=0;i<quant_bin_num;i++)
			this_nodes[quant_bin[i]].count++;
	}
}

#endif