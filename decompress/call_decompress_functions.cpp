#ifndef __CALL_DECOMPRESS_FUNCTIONS_CPP__
#define __CALL_DECOMPRESS_FUNCTIONS_CPP__

#include "decompress.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::call_decompress_functions()
	{
		in_file=fopen(in_file_path,"rb");
		fseek(in_file,0,SEEK_END);
		bitstream_length=ftell(in_file)/sizeof(unsigned char);
		fseek(in_file,0,SEEK_SET);
		new_data(bitstream,data_num*sizeof(T));
		fread(bitstream,sizeof(unsigned char),bitstream_length,in_file);
		fclose(in_file);
		new_data(data,data_num);
		if (strcmp(best_decompress_function,"decompress")==0)
			decompress();
		out_file=fopen(out_file_path,"wb");
		fwrite(data,data_num,sizeof(T),out_file);
		fclose(out_file);
		delete_data(data);
		delete_data(bitstream);
	}
}

#endif