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
			hyper_iterator_c *best_it1_backup=NULL;
			copy_iterator(best_it1_backup,best_it1);
			copy_iterator(best_it1,it1);
			char *best_fitting_function_backup=best_fitting_function;
			best_fitting_function=fitting_function;
			T *data_backup=new_data<T>(data_num);
			memcpy(data_backup,data,data_num*sizeof(T));
			compress();
			copy_iterator(best_it1,best_it1_backup);
			best_fitting_function=best_fitting_function_backup;
			delete_data(data);
			data=data_backup;
		}
		else
		{
			if ((it1->dim_seq!=NULL) || (it1->dim_fission_l!=it1->dim_fission_r) || (SAMPLING_RATE!=1))
				return;
			////////////////Quant Bin////////////////
			new_data(quant_bin,test_num);
			call_DC_functions_test();
			////////////////Huffman Tree////////////////
			huffman.push_back(huffman_tree_c<T>());
			count_quant_bin_test();
			write_quant_bin_freq(1);
			huffman_tree_c<T> & this_huffman=huffman[0];
			this_huffman.generate_tree();
			this_huffman.generate_code(this);
			printf("bitstream_length=%lld\n",bitstream_length);
			// ////////////////Huffman Encode////////////////
			encode_test();
			delete_data(quant_bin);
			this_huffman.nodes.clear();
			huffman.clear();
			printf("bitstream_length=%lld\n",bitstream_length);
			////////////////Irregular////////////////
			memcpy(bitstream+bitstream_length,irregular_data.data(),irregular_data.size()*sizeof(T));
			irregular_data.clear();
			printf("bitstream_length=%lld\n",bitstream_length);
			////////////////Zstd////////////////
			unsigned char *temp_bitstream=bitstream;
			new_data(bitstream,data_num*sizeof(T),false,false);
			bitstream_length=ZSTD_compress(bitstream,data_num*sizeof(T),temp_bitstream,bitstream_length,3);
			delete_data(temp_bitstream);
			printf("bitstream_length=%lld\n",bitstream_length);
		}
		if (debug)
			print_test_condition();
		if (bitstream_length<best_bitstream_length)
		{
			best_bitstream_length=bitstream_length;
			copy_iterator(best_it1,it1);
			if (strcmp(compress_function,"compress_test")==0)
				strcpy(best_compress_function,"compress");
			strcpy(best_fitting_function,fitting_function);
		}
		bitstream_length=0;
		//getchar();
	}
}


#endif