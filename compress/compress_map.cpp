#ifndef __COMPRESS_MAP_CPP__
#define __COMPRESS_MAP_CPP__

#include "compress.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::compress_map()
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
			transpose_data_and_map(data_backup,pos2horiz_mapping_backup);
			delete_data(data_backup);
			delete_data(pos2horiz_mapping_backup);
		}
		timer->pause();
		////////////////Quant Bin////////////////
		timer->start();
		new_data(quant_bin,data_num);
		new_data(qb2horiz_mapping,data_num);
		new_data(horiz_hist,it2->mx[latid]*it2->mx[lngid]*5);
		call_DC_functions_data_and_map();
		delete_data(pos2horiz_mapping);
		timer->pause();
		////////////////Map////////////////
		timer->start();
		new_data(width_map,it2->mx[latid]*it2->mx[lngid]);
		new_data(shift_map,it2->mx[latid]*it2->mx[lngid]);
		generate_map();
		apply_map();
		timer->pause();
		////////////////Huffman Tree////////////////
		timer->start();
		huffman.push_back(huffman_tree_c<T>());
		huffman.push_back(huffman_tree_c<T>());
		huffman.push_back(huffman_tree_c<T>());
		count_quant_bin_map();
		huffman_tree_c<T> &this_huffman_0=huffman[0];
		huffman_tree_c<T> &this_huffman_1=huffman[1];
		huffman_tree_c<T> &this_huffman_map=huffman[2];
		this_huffman_0.generate_tree();
		this_huffman_0.generate_code(this);
		this_huffman_1.generate_tree();
		this_huffman_1.generate_code(this);
		unsigned char *bitstream_backup=bitstream;
		long long bitstream_length_backup=bitstream_length;
		bitstream=map_bitstream;
		bitstream_length=map_bitstream_length;
		this_huffman_map.generate_tree();
		this_huffman_map.generate_code(this);
		map_bitstream_length=bitstream_length;
		bitstream=bitstream_backup;
		bitstream_length=bitstream_length_backup;
		timer->pause();
		printf("bitstream_length=%lld+%lld=%lld\n",bitstream_length,map_bitstream_length,bitstream_length+map_bitstream_length);
		////////////////Huffman Encode////////////////
		timer->start();
		encode_map();
		delete_data(quant_bin);
		this_huffman_0.nodes.clear();
		this_huffman_1.nodes.clear();
		this_huffman_map.nodes.clear();
		huffman.clear();
		timer->pause();
		printf("bitstream_length=%lld+%lld=%lld\n",bitstream_length,map_bitstream_length,bitstream_length+map_bitstream_length);
		////////////////Irregular////////////////
		timer->start();
		memcpy(bitstream+bitstream_length,irregular_data.data(),irregular_data.size()*sizeof(T));
		irregular_data.clear();
		timer->pause();
		printf("bitstream_length=%lld+%lld=%lld\n",bitstream_length,map_bitstream_length,bitstream_length+map_bitstream_length);
		////////////////Zstd////////////////
		timer->start();
		unsigned char *temp_bitstream=bitstream;
		new_data(bitstream,data_num*sizeof(T),false,false);
		bitstream_length=ZSTD_compress(bitstream,data_num*sizeof(T),temp_bitstream,bitstream_length,3);
		delete_data(temp_bitstream);
		unsigned char *temp_map_bitstream=map_bitstream;
		new_data(map_bitstream,it2->mx[latid]*it2->mx[lngid],false,false);
		map_bitstream_length=ZSTD_compress(map_bitstream,it2->mx[latid]*it2->mx[lngid],temp_map_bitstream,map_bitstream_length,3);
		delete_data(temp_map_bitstream);
		timer->pause();
		printf("bitstream_length=%lld+%lld=%lld\n",bitstream_length,map_bitstream_length,bitstream_length+map_bitstream_length);
		CR=((float)data_num*sizeof(T))/(bitstream_length+map_bitstream_length);
		timer->write();
	}
}

#endif