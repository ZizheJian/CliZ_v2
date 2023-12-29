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
        ////////////////Huffman Decode////////////////
        new_data(quant_bin,data_num);
        decode();
        timer->write();

	}
}

#endif