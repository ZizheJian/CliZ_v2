#ifndef __CALL_DECOMPRESS_FUNCTIONS_CPP__
#define __CALL_DECOMPRESS_FUNCTIONS_CPP__

#include "decompress.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::call_decompress_functions()
	{
		printf("In call_decompress_functions\n");
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
		if (strcmp(best_decompress_function,"decompress_map")==0)
		{
			map_file=fopen(map_file_path,"rb");
			fseek(map_file,0,SEEK_END);
			map_bitstream_length=ftell(map_file)/sizeof(unsigned char);
			fseek(map_file,0,SEEK_SET);
			new_data(map_bitstream,it2->mx[latid]*it2->mx[lngid]);
			fread(map_bitstream,sizeof(unsigned char),map_bitstream_length,map_file);
			fclose(map_file);
			decompress_map();
			delete_data(map_bitstream);
		}
		if (strcmp(best_decompress_function,"decompress_mask")==0)
		{
			mask_file=fopen(mask_file_path,"rb");
			new_data(mask_data,it2->mx[latid]*it2->mx[lngid]);
			fread(mask_data,sizeof(int),it2->mx[latid]*it2->mx[lngid],mask_file);
			fclose(mask_file);
			decompress_mask();
			delete_data(mask_data);
		}
		out_file=fopen(out_file_path,"wb");
		fwrite(data,data_num,sizeof(T),out_file);
		fclose(out_file);
		delete_data(data);
		delete_data(bitstream);
	}
}

#endif