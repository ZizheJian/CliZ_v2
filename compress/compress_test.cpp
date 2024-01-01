#ifndef __COMPRESS_TEST_CPP__
#define __COMPRESS_TEST_CPP__

#include "compress.hpp2"

namespace cliz
{
    template<typename T>
    void task_c<T>::compress_test()
    {
		if (TEST_ALL)
		{
			hyper_iterator_c *best_it1_backup=best_it1;
			best_it1=it1;
			char *best_fitting_function_backup=best_fitting_function;
			best_fitting_function=fitting_function;
			T *data_backup=new_data<T>(data_num);
			memcpy(data_backup,data,data_num*sizeof(T));
			compress();
			best_it1=best_it1_backup;
			best_fitting_function=best_fitting_function_backup;
			delete_data(data);
			data=data_backup;
			print_test_condition();
			bitstream_length=0;
			getchar();
			return;
		}
        auto timer=new timer_c();
		////////////////Quant Bin////////////////
		timer->start();
		new_data(quant_bin,test_num);
		call_DC_functions_test();
		timer->pause();
		////////////////Huffman Tree////////////////
		timer->start();
		huffman.push_back(huffman_tree_c<T>());
		count_quant_bin();
		huffman_tree_c<T> & this_huffman=huffman[0];
		this_huffman.generate_tree();
		this_huffman.generate_code(this);
		timer->pause();
		printf("%lld\n",bitstream_length);
		////////////////Huffman Encode////////////////
		timer->start();
		encode();
		delete_data(quant_bin);
		this_huffman.nodes.clear();
		huffman.clear();
		timer->pause();
		printf("%lld\n",bitstream_length);
		////////////////Irregular////////////////
		timer->start();
		memcpy(bitstream+bitstream_length,irregular_data.data(),irregular_data.size()*sizeof(T));
		irregular_data.clear();
		timer->pause();
		printf("%lld\n",bitstream_length);
		////////////////Zstd////////////////
		timer->start();
		unsigned char *temp_bitstream=bitstream;
		new_data(bitstream,data_num*sizeof(T),false,false);
		bitstream_length=ZSTD_compress(bitstream,data_num*sizeof(T),temp_bitstream,bitstream_length,3);
		delete_data(temp_bitstream);
		timer->pause();
		printf("%lld\n",bitstream_length);
		timer->write();
    }
}


#endif