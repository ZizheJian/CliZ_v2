#ifndef __CALL_COMPRESS_FUNCTIONS_CPP__
#define __CALL_COMPRESS_FUNCTIONS_CPP__

#include "compress.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::call_compress_functions()
	{
		new_data(data,data_num);
		in_file=fopen(in_file_path,"rb");
		fread(data,sizeof(T),data_num,in_file);
		fclose(in_file);
		new_data(bitstream,data_num*sizeof(T));
		if (strcmp(best_compress_function,"compress")==0)
			compress();
		if (strcmp(best_compress_function,"compress_map")==0)
			compress_map();
		out_file=fopen(out_file_path,"wb");
		fwrite(bitstream,bitstream_length,sizeof(unsigned char),out_file);
		fclose(out_file);
		delete_data(data);
		delete_data(bitstream);
	}
}

#endif