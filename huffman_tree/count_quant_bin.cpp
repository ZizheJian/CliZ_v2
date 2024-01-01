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
		for (long long i=0;i<data_num;i++)
		{
			//printf("i=%lld, quant_bin[i]=%d\n",i,quant_bin[i]);
			this_nodes[quant_bin[i]].count++;
			//printf("quant_bin_count[0][%d]=%lld\n",quant_bin[i],quant_bin_count[0][quant_bin[i]]);
		}
		//for (auto it=this_nodes.begin();it!=this_nodes.end();it++)
		//	printf("%d %lld\n",it->first,it->second.count);
	}
}

#endif