#ifndef __COMPRESS_CPP__
#define __COMPRESS_CPP__

#include "compress.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::compress()
	{
		auto timer=new timer_c();
		////////////////Quant Bin////////////////
		timer->start();
		new_data(quant_bin,data_num);
		call_DC_functions();
		timer->pause();
		////////////////Huffman Tree////////////////
		timer->start();
		huffman.push_back(huffman_tree_c<T>());
		count_quant_bin();
		huffman_tree_c<T> & this_huffman=huffman[0];
		this_huffman.generate_tree();
		this_huffman.generate_code(this);
		timer->pause();
		//printf("%lld\n",out_length);
		//for (int i=0;i<out_length/2;i++)
		//	printf("%d ",((short*)out_bitstream)[i]);
		printf("%lld\n",out_length);
		////////////////Huffman Encode////////////////
		timer->start();
		encode();
		delete_data(quant_bin);
		this_huffman.nodes.clear();
		huffman.clear();
		timer->pause();
		printf("%lld\n",out_length);
		////////////////Irregular////////////////
		timer->start();
		memcpy(out_bitstream+out_length,irregular_data.data(),irregular_data.size()*sizeof(T));
		irregular_data.clear();
		timer->pause();
		printf("%lld\n",out_length);
		////////////////Zstd////////////////
		timer->start();
		unsigned char *temp_out_bitstream=out_bitstream;
		new_data(out_bitstream,data_num*sizeof(T),false,false);
		out_length=ZSTD_compress(out_bitstream,data_num*sizeof(T),temp_out_bitstream,out_length,3);
		delete_data(temp_out_bitstream);
		timer->pause();
		printf("%lld\n",out_length);
		timer->write();
	}
}

#endif