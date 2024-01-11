#ifndef __COMPRESS_USE_MAP_MASK_CPP__
#define __COMPRESS_USE_MAP_MASK_CPP__

#include "compress.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::compress_use_map_mask()
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
		////////////////Zstd////////////////
		timer->start();
		map_num=it2->mx[latid]*it2->mx[lngid];
		unsigned char *temp_map_bitstream=map_bitstream;
		new_data(map_bitstream,map_num,false,false);
		map_bitstream_length=ZSTD_decompress(map_bitstream,map_num,temp_map_bitstream,map_bitstream_length);
		delete_data(temp_map_bitstream);
		timer->pause();
		////////////////Huffman Tree////////////////
		timer->start();
		map_bitstream_index=0;
		huffman.push_back(huffman_tree_c<T>());
		huffman.push_back(huffman_tree_c<T>());
		huffman.push_back(huffman_tree_c<T>());
		huffman_tree_c<T> &this_huffman_map=huffman[2];
		unsigned char *bitstream_backup=bitstream;
		bitstream=map_bitstream;
		bitstream_index=map_bitstream_index;
		this_huffman_map.rebuild(this);
		map_bitstream_index=bitstream_index;
		bitstream_index=0;
		bitstream=bitstream_backup;
		timer->pause();
		printf("bitstream_length=0, map_bitstream_progress=%lld/%lld\n",map_bitstream_index,map_bitstream_length);
		////////////////Huffman Decode////////////////
		timer->start();
		new_data(width_map,map_num);
		new_data(shift_map,map_num);
		decode_map();
		timer->pause();
		printf("bitstream_length=0, map_bitstream_progress=%lld/%lld\n",map_bitstream_index,map_bitstream_length);
		////////////////Quant Bin////////////////
		timer->start();
		new_data(quant_bin,quant_bin_num);
		new_data(qb2horiz_mapping,quant_bin_num);
		call_DC_functions_data_use_map_mask();
		delete_data(pos2horiz_mapping);
		timer->pause();
		////////////////Map////////////////
		timer->start();
		apply_map();
		timer->pause();
		////////////////Huffman Tree////////////////
		timer->start();
		count_quant_bin_map();
		huffman_tree_c<T> &this_huffman_0=huffman[0];
		huffman_tree_c<T> &this_huffman_1=huffman[1];
		this_huffman_0.generate_tree();
		this_huffman_0.generate_code(this);
		this_huffman_1.generate_tree();
		this_huffman_1.generate_code(this);
		timer->pause();
		printf("bitstream_length=%lld, map_bitstream_progress=%lld/%lld\n",bitstream_length,map_bitstream_index,map_bitstream_length);
		////////////////Huffman Encode////////////////
		timer->start();
		encode_data_with_map();
		delete_data(quant_bin);
		delete_data(qb2horiz_mapping);
		delete_data(width_map);
		delete_data(shift_map);
		this_huffman_0.nodes.clear();
		this_huffman_1.nodes.clear();
		this_huffman_map.nodes.clear();
		huffman.clear();
		timer->pause();
		printf("bitstream_length=%lld, map_bitstream_progress=%lld/%lld\n",bitstream_length,map_bitstream_index,map_bitstream_length);
		////////////////Irregular////////////////
		timer->start();
		memcpy(bitstream+bitstream_length,irregular_data.data(),irregular_data.size()*sizeof(T));
		irregular_data.clear();
		timer->pause();
		printf("bitstream_length=%lld, map_bitstream_progress=%lld/%lld\n",bitstream_length,map_bitstream_index,map_bitstream_length);
		////////////////Zstd////////////////
		timer->start();
		unsigned char *temp_bitstream=bitstream;
		new_data(bitstream,data_num*sizeof(T),false,false);
		bitstream_length=ZSTD_compress(bitstream,data_num*sizeof(T),temp_bitstream,bitstream_length,3);
		delete_data(temp_bitstream);
		timer->pause();
		printf("bitstream_length=%lld, map_bitstream_progress=%lld/%lld\n",bitstream_length,map_bitstream_index,map_bitstream_length);
		CR=((float)data_num*sizeof(T))/(bitstream_length+map_bitstream_length);
		timer->write();
	}
}

#endif