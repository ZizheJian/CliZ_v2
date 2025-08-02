#ifndef __DECOMPRESS_MAP_CPP__
#define __DECOMPRESS_MAP_CPP__

#include "decompress.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::decompress_map()
	{
		printf("In decompress_map()\n");
		auto timer=new timer_c();
		////////////////Generate Position-To-Horizontal-Position Mapping////////////////
		printf("Generating Position-To-Horizontal-Position Mapping...\n");
		timer->start();
		new_data(pos2horiz_mapping,data_num);
		generate_pos2horiz_mapping();
		timer->pause();
		////////////////Transpose////////////////
		printf("Transposing...\n");
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
		printf("Generating Quant-Bin-To-Horizontal-Position Mapping...\n");
		timer->start();
		quant_bin_num=data_num;
		new_data(qb2horiz_mapping,quant_bin_num);
		call_DC_functions_map();
		delete_data(pos2horiz_mapping);
		timer->pause();
		////////////////Zstd////////////////
		printf("Zstd\n");
		timer->start();
		unsigned char *temp_bitstream=new_data<unsigned char>(data_num*sizeof(T));
		printf("bitstream_start=%lld, bitstream_end=%lld\n",bitstream_start,bitstream_end);
		bitstream_end=bitstream_start+ZSTD_decompress(temp_bitstream,data_num*sizeof(T),bitstream+bitstream_start,bitstream_end-bitstream_start);
		memcpy(bitstream+bitstream_start,temp_bitstream,bitstream_end-bitstream_start);
		delete_data(temp_bitstream);
		printf("aaaa\n");
		map_num=it2->mx[latid]*it2->mx[lngid];
		unsigned char *temp_map_bitstream=new_data<unsigned char>(map_num);
		map_bitstream_end=map_bitstream_start+ZSTD_decompress(temp_map_bitstream,map_num,map_bitstream+map_bitstream_start,map_bitstream_end-map_bitstream_start);
		memcpy(map_bitstream+map_bitstream_start,temp_map_bitstream,map_bitstream_end-map_bitstream_start);
		delete_data(temp_map_bitstream);
		timer->pause();
		printf("bitstream_progress=%lld/%lld, map_bitstream_progress=%lld/%lld\n",bitstream_start,bitstream_end,map_bitstream_start,map_bitstream_end);
		////////////////Huffman Tree////////////////
		printf("Huffman Tree\n");
		timer->start();
		huffman.push_back(huffman_tree_c<T>());
		huffman.push_back(huffman_tree_c<T>());
		huffman.push_back(huffman_tree_c<T>());
		huffman_tree_c<T> &this_huffman_0=huffman[0];
		huffman_tree_c<T> &this_huffman_1=huffman[1];
		huffman_tree_c<T> &this_huffman_map=huffman[2];
		this_huffman_0.rebuild(this);
		this_huffman_1.rebuild(this);
		unsigned char *bitstream_backup=bitstream;
		long long bitstream_start_backup=bitstream_start;
		bitstream=map_bitstream;
		bitstream_start=map_bitstream_start;
		this_huffman_map.rebuild(this);
		map_bitstream_start=bitstream_start;
		bitstream_start=bitstream_start_backup;
		bitstream=bitstream_backup;
		timer->pause();
		printf("bitstream_progress=%lld/%lld, map_bitstream_progress=%lld/%lld\n",bitstream_start,bitstream_end,map_bitstream_start,map_bitstream_end);
		////////////////Huffman Decode////////////////
		printf("Huffman Decode\n");
		timer->start();
		new_data(quant_bin,quant_bin_num);
		new_data(width_map,map_num);
		new_data(shift_map,map_num);
		decode_data_and_map();
		this_huffman_0.nodes.clear();
		this_huffman_1.nodes.clear();
		this_huffman_map.nodes.clear();
		huffman.clear();
		timer->pause();
		printf("bitstream_progress=%lld/%lld, map_bitstream_progress=%lld/%lld\n",bitstream_start,bitstream_end,map_bitstream_start,map_bitstream_end);
		////////////////Map////////////////
		printf("Undo Apply Map\n");
		timer->start();
		undo_apply_map();
		delete_data(qb2horiz_mapping);
		delete_data(width_map);
		delete_data(shift_map);
		timer->pause();
		////////////////Quant Bin & Irregular////////////////
		printf("Quant Bin & Irregular\n");
		timer->start();
		call_DC_functions_data();
		delete_data(quant_bin);
		timer->pause();
		printf("bitstream_progress=%lld/%lld, map_bitstream_progress=%lld/%lld\n",bitstream_start,bitstream_end,map_bitstream_start,map_bitstream_end);
		////////////////Anti-Transpose////////////////
		printf("Anti-Transpose\n");
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