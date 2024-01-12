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
		if (best_it1->dim_seq!=NULL)
		{
			T *data_backup=data;
			new_data(data,data_num,false,false);
			transpose_data(data_backup);
			delete_data(data_backup);
		}
		timer->pause();
		////////////////Quant Bin////////////////
		timer->start();
		quant_bin_num=data_num;
		new_data(quant_bin,quant_bin_num);
		call_DC_functions_data();
		timer->pause();
		////////////////Huffman Tree////////////////
		timer->start();
		huffman.push_back(huffman_tree_c<T>());
		count_quant_bin();
		huffman_tree_c<T> &this_huffman=huffman[0];
		this_huffman.generate_tree();
		this_huffman.generate_code(this);
		timer->pause();
		printf("bitstream_length=%lld\n",bitstream_end);
		////////////////Huffman Encode////////////////
		timer->start();
		encode_data();
		delete_data(quant_bin);
		this_huffman.nodes.clear();
		huffman.clear();
		timer->pause();
		printf("bitstream_length=%lld\n",bitstream_end);
		////////////////Irregular////////////////
		timer->start();
		memcpy(bitstream+bitstream_end,irregular_data.data(),irregular_data.size()*sizeof(T));
		irregular_data.clear();
		timer->pause();
		printf("bitstream_length=%lld\n",bitstream_end);
		////////////////Zstd////////////////
		timer->start();
		unsigned char *temp_bitstream=new_data<unsigned char>(data_num*sizeof(T));
		memcpy(temp_bitstream,bitstream+bitstream_start,bitstream_end-bitstream_start);
		bitstream_end=bitstream_start+ZSTD_compress(bitstream+bitstream_start,data_num*sizeof(T),temp_bitstream,bitstream_end-bitstream_start,3);
		delete_data(temp_bitstream);
		long long bitstream_length=bitstream_end-bitstream_start;
		memcpy(bitstream,&bitstream_length,sizeof(long long));
		timer->pause();
		printf("bitstream_length=%lld\n",bitstream_end);
		CR=((float)data_num*sizeof(T))/bitstream_end;
		timer->write();
	}
}

#endif