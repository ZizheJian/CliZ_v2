#ifndef __DECOMPRESS_CPP__
#define __DECOMPRESS_CPP__

#include "decompress.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::decompress()
	{
		auto timer=new timer_c();
		////////////////Zstd////////////////
		timer->start();
		unsigned char *temp_bitstream=bitstream;
		new_data(bitstream,data_num*sizeof(T),false,false);
		bitstream_length=ZSTD_decompress(bitstream,data_num*sizeof(T),temp_bitstream,bitstream_length);
		delete_data(temp_bitstream);
		timer->pause();
		////////////////Huffman Tree////////////////
		timer->start();
		bitstream_index=0;
		huffman.push_back(huffman_tree_c<T>());
		huffman_tree_c<T> &this_huffman=huffman[0];
		this_huffman.rebuild(this);
		timer->pause();
		printf("bitstream_progress=%lld/%lld\n",bitstream_index,bitstream_length);
		////////////////Huffman Decode////////////////
		timer->start();
		quant_bin_num=data_num;
		new_data(quant_bin,quant_bin_num);
		decode_data();
		timer->pause();
		printf("bitstream_progress=%lld/%lld\n",bitstream_index,bitstream_length);
		////////////////Quant Bin & Irregular////////////////
		timer->start();
		call_DC_functions_data();
		delete_data(quant_bin);
		timer->pause();
		printf("bitstream_progress=%lld/%lld\n",bitstream_index,bitstream_length);
		////////////////Anti-Transpose////////////////
		timer->start();
		if (best_it1->dim_seq!=NULL)
		{
			T *data_backup=data;
			new_data(data,data_num,false,false);
			anti_transpose_data(data_backup);
			delete_data(data_backup);
		}
		timer->pause();
		timer->write();
	}
}

#endif