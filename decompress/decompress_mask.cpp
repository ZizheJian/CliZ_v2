#ifndef __DECOMPRESS_MASK_CPP__
#define __DECOMPRESS_MASK_CPP__

#include "decompress.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::decompress_mask()
	{
		auto timer=new timer_c();
		////////////////Generate Position-To-Horizontal-Position Mapping////////////////
		timer->start();
		new_data(pos2horiz_mapping,data_num);
		generate_pos2horiz_mapping();
		timer->pause();
		////////////////Transpose////////////////
		timer->start();
		if (best_it1->dim_seq!=NULL)
		{
			long long *pos2horiz_mapping_backup=pos2horiz_mapping;
			new_data(pos2horiz_mapping,data_num,false,false);
			transpose_map(pos2horiz_mapping_backup);
			delete_data(pos2horiz_mapping_backup);
		}
		timer->pause();
		////////////////Count Map Size////////////////
		timer->start();
		calc_quant_bin_size();
		timer->pause();
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
		new_data(quant_bin,quant_bin_num);
		decode_data();
		timer->pause();
		printf("bitstream_progress=%lld/%lld\n",bitstream_index,bitstream_length);
		////////////////Quant Bin & Irregular////////////////
		timer->start();
		for (long long i=0;i<data_num;i++)
			data[i]=mask_value;
		call_DC_functions_data_mask();
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