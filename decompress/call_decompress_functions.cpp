#ifndef __CALL_DECOMPRESS_FUNCTIONS_CPP__
#define __CALL_DECOMPRESS_FUNCTIONS_CPP__

#include "decompress.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::call_decompress_functions()
	{
		bitstream_start=sizeof(long long);
		in_file=fopen(in_file_path,"rb");
		long long bitstream_length;
		fread(&bitstream_length,sizeof(long long),1,in_file);
		bitstream_end=bitstream_length+bitstream_start;
		new_data(bitstream,data_num*sizeof(T));
		fread(bitstream+bitstream_start,sizeof(unsigned char),bitstream_length,in_file);
		fclose(in_file);
		new_data(data,data_num);
		if ((best_decompress_function==NULL) || (strcmp(best_decompress_function,"decompress")==0))
			decompress();
		if ((best_decompress_function!=NULL) && (strcmp(best_decompress_function,"decompress_map")==0))
		{
			map_bitstream_start=sizeof(long long);
			map_file=fopen(map_file_path,"rb");
			long long map_bitstream_length;
			fread(&map_bitstream_length,sizeof(long long),1,map_file);
			map_bitstream_end=map_bitstream_length+map_bitstream_start;
			new_data(map_bitstream,it2->mx[latid]*it2->mx[lngid]);
			fread(map_bitstream+map_bitstream_start,sizeof(unsigned char),map_bitstream_length,map_file);
			fclose(map_file);
			decompress_map();
			delete_data(map_bitstream);
		}
		if ((best_decompress_function!=NULL) && (strcmp(best_decompress_function,"decompress_mask")==0))
		{
			mask_file=fopen(mask_file_path,"rb");
			new_data(mask_data,it2->mx[latid]*it2->mx[lngid]);
			fread(mask_data,sizeof(int),it2->mx[latid]*it2->mx[lngid],mask_file);
			fclose(mask_file);
			decompress_mask();
			delete_data(mask_data);
		}
		if ((best_decompress_function!=NULL) && (strcmp(best_decompress_function,"decompress_map_mask")==0))
		{
			map_bitstream_start=sizeof(long long);
			map_file=fopen(map_file_path,"rb");
			long long map_bitstream_length;
			fread(&map_bitstream_length,sizeof(long long),1,map_file);
			map_bitstream_end=map_bitstream_length+map_bitstream_start;
			new_data(map_bitstream,it2->mx[latid]*it2->mx[lngid]);
			fread(map_bitstream+map_bitstream_start,sizeof(unsigned char),map_bitstream_length,map_file);
			mask_file=fopen(mask_file_path,"rb");
			new_data(mask_data,it2->mx[latid]*it2->mx[lngid]);
			fread(mask_data,sizeof(int),it2->mx[latid]*it2->mx[lngid],mask_file);
			fclose(mask_file);
			decompress_map_mask();
			delete_data(map_bitstream);
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