#ifndef __DECOMPRESS_MAP_CPP__
#define __DECOMPRESS_MAP_CPP__

#include "decompress.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::decompress_map()
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
		////////////////Generate Quant-Bin-To-Horizontal-Position Mapping////////////////
		timer->start();
		quant_bin_num=data_num;
		new_data(qb2horiz_mapping,quant_bin_num);
		call_DC_functions_map();
		delete_data(pos2horiz_mapping);
		timer->pause();
		////////////////Zstd////////////////
		timer->start();
		unsigned char *temp_bitstream=bitstream;
		new_data(bitstream,data_num*sizeof(T),false,false);
		bitstream_length=ZSTD_decompress(bitstream,data_num*sizeof(T),temp_bitstream,bitstream_length);
		delete_data(temp_bitstream);
		unsigned char *temp_map_bitstream=map_bitstream;
		new_data(map_bitstream,it2->mx[latid]*it2->mx[lngid],false,false);
		map_bitstream_length=ZSTD_decompress(map_bitstream,it2->mx[latid]*it2->mx[lngid],temp_map_bitstream,map_bitstream_length);
		delete_data(temp_map_bitstream);
		timer->pause();
		////////////////Huffman Tree////////////////
		timer->start();
		bitstream_index=0;
		map_bitstream_index=0;
		huffman.push_back(huffman_tree_c<T>());
		huffman.push_back(huffman_tree_c<T>());
		huffman.push_back(huffman_tree_c<T>());
		huffman_tree_c<T> &this_huffman_0=huffman[0];
		huffman_tree_c<T> &this_huffman_1=huffman[1];
		huffman_tree_c<T> &this_huffman_map=huffman[2];
		this_huffman_0.rebuild(this);
		this_huffman_1.rebuild(this);
		unsigned char *bitstream_backup=bitstream;
		long long bitstream_index_backup=bitstream_index;
		bitstream=map_bitstream;
		bitstream_index=map_bitstream_index;
		this_huffman_map.rebuild(this);
		map_bitstream_index=bitstream_index;
		bitstream_index=bitstream_index_backup;
		bitstream=bitstream_backup;
		timer->pause();
		printf("bitstream_progress=%lld/%lld, map_bitstream_progress=%lld/%lld\n",bitstream_index,bitstream_length,map_bitstream_index,map_bitstream_length);
		////////////////Huffman Decode////////////////
		timer->start();
		new_data(quant_bin,quant_bin_num);
		new_data(width_map,it2->mx[latid]*it2->mx[lngid]);
		new_data(shift_map,it2->mx[latid]*it2->mx[lngid]);
		decode_data_and_map();
		timer->pause();
		printf("bitstream_progress=%lld/%lld, map_bitstream_progress=%lld/%lld\n",bitstream_index,bitstream_length,map_bitstream_index,map_bitstream_length);
		////////////////Map////////////////
		timer->start();
		undo_apply_map();
		delete_data(qb2horiz_mapping);
		delete_data(width_map);
		delete_data(shift_map);
		timer->pause();
		////////////////Quant Bin & Irregular////////////////
		timer->start();
		call_DC_functions_data();
		delete_data(quant_bin);
		timer->pause();
		timer->write();
		printf("bitstream_progress=%lld/%lld, map_bitstream_progress=%lld/%lld\n",bitstream_index,bitstream_length,map_bitstream_index,map_bitstream_length);
		////////////////Anti-Transpose////////////////
		timer->start();
		if (best_it1->dim_seq!=NULL)
		{
			T *data_backup=data;
			new_data(data,data_num,false,false);
			anti_transpose_data(data_backup);
			delete_data(data_backup);
		}
	}
}

#endif