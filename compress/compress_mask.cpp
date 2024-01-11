#ifndef __COMPRESS_MASK_CPP__
#define __COMPRESS_MASK_CPP__

#include "compress.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::compress_mask()
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
			T *data_backup=data;
			new_data(data,data_num,false,false);
			long long *pos2horiz_mapping_backup=pos2horiz_mapping;
			new_data(pos2horiz_mapping,data_num,false,false);
			transpose_data_map(data_backup,pos2horiz_mapping_backup);
			delete_data(data_backup);
			delete_data(pos2horiz_mapping_backup);
		}
		timer->pause();
		////////////////Count Map Size////////////////
		timer->start();
		calc_quant_bin_size();
		timer->pause();
		////////////////Quant Bin////////////////
		timer->start();
		new_data(quant_bin,quant_bin_num);
		call_DC_functions_data_mask();
		delete_data(pos2horiz_mapping);
		timer->pause();
		////////////////Huffman Tree////////////////
		timer->start();
		huffman.push_back(huffman_tree_c<T>());
		count_quant_bin();
		huffman_tree_c<T> &this_huffman=huffman[0];
		this_huffman.generate_tree();
		this_huffman.generate_code(this);
		timer->pause();
		printf("bitstream_length=%lld\n",bitstream_length);
		////////////////Huffman Encode////////////////
		timer->start();
		encode_data();
		delete_data(quant_bin);
		this_huffman.nodes.clear();
		huffman.clear();
		timer->pause();
		printf("bitstream_length=%lld\n",bitstream_length);
		////////////////Irregular////////////////
		timer->start();
		memcpy(bitstream+bitstream_length,irregular_data.data(),irregular_data.size()*sizeof(T));
		irregular_data.clear();
		timer->pause();
		printf("bitstream_length=%lld\n",bitstream_length);
		////////////////Zstd////////////////
		timer->start();
		unsigned char *temp_bitstream=bitstream;
		new_data(bitstream,data_num*sizeof(T),false,false);
		bitstream_length=ZSTD_compress(bitstream,data_num*sizeof(T),temp_bitstream,bitstream_length,3);
		delete_data(temp_bitstream);
		timer->pause();
		printf("bitstream_length=%lld\n",bitstream_length);
		CR=((float)data_num*sizeof(T))/bitstream_length;
		timer->write();
	}
}

#endif