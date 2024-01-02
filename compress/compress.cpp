#ifndef __COMPRESS_CPP__
#define __COMPRESS_CPP__

#include "compress.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::compress()
	{
		auto timer=new timer_c();
		////////////////Transpose////////////////
		timer->start();
		hyper_iterator_c *best_it1_backup=NULL;
		if (it1->dim_seq!=NULL)
		{
			T *data_backup=data;
			new_data(data,data_num,false,false);
			transpose(data_backup);
			copy_iterator(best_it1_backup,it1);
			delete_data(best_it1->dim_seq);
		}
		timer->pause();
		////////////////Quant Bin////////////////
		timer->start();
		new_data(quant_bin,data_num);
		call_DC_functions();
		timer->pause();
		////////////////Huffman Tree////////////////
		timer->start();
		huffman.push_back(huffman_tree_c<T>());
		count_quant_bin();
		huffman_tree_c<T> & this_huffman=huffman[0];
		this_huffman.generate_tree();
		this_huffman.generate_code(this);
		timer->pause();
		printf("%lld\n",bitstream_length);
		////////////////Huffman Encode////////////////
		timer->start();
		encode();
		delete_data(quant_bin);
		this_huffman.nodes.clear();
		huffman.clear();
		timer->pause();
		printf("%lld\n",bitstream_length);
		////////////////Irregular////////////////
		timer->start();
		memcpy(bitstream+bitstream_length,irregular_data.data(),irregular_data.size()*sizeof(T));
		irregular_data.clear();
		timer->pause();
		printf("%lld\n",bitstream_length);
		////////////////Zstd////////////////
		timer->start();
		unsigned char *temp_bitstream=bitstream;
		new_data(bitstream,data_num*sizeof(T),false,false);
		bitstream_length=ZSTD_compress(bitstream,data_num*sizeof(T),temp_bitstream,bitstream_length,3);
		delete_data(temp_bitstream);
		timer->pause();
		printf("%lld\n",bitstream_length);
		timer->write();
		////////////////Anti-Tanspose////////////////
		timer->start();
		if (it1->dim_seq!=NULL)
			copy_iterator(best_it1,best_it1_backup);
		timer->write();
	}
}

#endif