#ifndef __COMPRESS_SET_MAP_CPP__
#define __COMPRESS_SET_MAP_CPP__

#include "compress.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::compress_set_map()
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
		////////////////Quant Bin////////////////
		timer->start();
		map_num=it2->mx[latid]*it2->mx[lngid];
		quant_bin_num=data_num;
		new_data(quant_bin,quant_bin_num);
		new_data(qb2horiz_mapping,quant_bin_num);
		new_data(horiz_hist,map_num*5,true);
		call_DC_functions_data_set_map();
		delete_data(pos2horiz_mapping);
		timer->pause();
		////////////////Map////////////////
		timer->start();
		new_data(width_map,map_num);
		new_data(shift_map,map_num);
		generate_map();
		delete_data(horiz_hist);
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
		long long bitstream_length_backup=bitstream_end;
		bitstream=map_bitstream;
		bitstream_end=map_bitstream_end;
		this_huffman_map.generate_tree();
		this_huffman_map.generate_code(this);
		map_bitstream_end=bitstream_end;
		bitstream=bitstream_backup;
		bitstream_end=bitstream_length_backup;
		timer->pause();
		printf("bitstream_end=%lld+%lld=%lld\n",bitstream_end,map_bitstream_end,bitstream_end+map_bitstream_end);
		////////////////Huffman Encode////////////////
		timer->start();
		encode_data_and_map();
		delete_data(quant_bin);
		delete_data(qb2horiz_mapping);
		delete_data(width_map);
		delete_data(shift_map);
		this_huffman_0.nodes.clear();
		this_huffman_1.nodes.clear();
		this_huffman_map.nodes.clear();
		huffman.clear();
		timer->pause();
		printf("bitstream_end=%lld+%lld=%lld\n",bitstream_end,map_bitstream_end,bitstream_end+map_bitstream_end);
		////////////////Irregular////////////////
		timer->start();
		memcpy(bitstream+bitstream_end,irregular_data.data(),irregular_data.size()*sizeof(T));
		irregular_data.clear();
		timer->pause();
		printf("bitstream_end=%lld+%lld=%lld\n",bitstream_end,map_bitstream_end,bitstream_end+map_bitstream_end);
		////////////////Zstd////////////////
		timer->start();
		unsigned char *temp_bitstream=new_data<unsigned char>(data_num*sizeof(T));
		memcpy(temp_bitstream,bitstream+bitstream_start,bitstream_end-bitstream_start);
		bitstream_end=bitstream_start+ZSTD_compress(bitstream+bitstream_start,data_num*sizeof(T),temp_bitstream,bitstream_end-bitstream_start,3);
		delete_data(temp_bitstream);
		long long bitstream_length=bitstream_end-bitstream_start;
		memcpy(bitstream,&bitstream_length,sizeof(long long));
		unsigned char *temp_map_bitstream=new_data<unsigned char>(map_num);
		memcpy(temp_map_bitstream,map_bitstream+map_bitstream_start,map_bitstream_end-map_bitstream_start);
		map_bitstream_end=map_bitstream_start+ZSTD_compress(map_bitstream+map_bitstream_start,map_num*sizeof(T),temp_map_bitstream,map_bitstream_end-map_bitstream_start,3);
		delete_data(temp_map_bitstream);
		long long map_bitstream_length=map_bitstream_end-map_bitstream_start;
		memcpy(map_bitstream,&map_bitstream_length,sizeof(long long));
		timer->pause();
		printf("bitstream_end=%lld+%lld=%lld\n",bitstream_end,map_bitstream_end,bitstream_end+map_bitstream_end);
		CR=((float)data_num*sizeof(T))/(bitstream_end+map_bitstream_end);
		timer->write();
	}
}

#endif