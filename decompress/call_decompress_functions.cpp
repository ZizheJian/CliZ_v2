#ifndef __CALL_DECOMPRESS_FUNCTIONS_CPP__
#define __CALL_DECOMPRESS_FUNCTIONS_CPP__

#include "decompress.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::call_decompress_functions()
	{
		printf("In call_decompress_functions()\n");
		if ((strcmp(best_decompress_function,"decompress_mask")==0) || (strcmp(best_decompress_function,"decompress_map_mask")==0) || ((best_pert_decompress_function!=NULL)
			&& ((strcmp(best_pert_decompress_function,"decompress_mask")==0) || (strcmp(best_pert_decompress_function,"decompress_map_mask")==0))))
		{
			new_data(mask_data,it2->mx[latid]*it2->mx[lngid]);
			mask_file=fopen(mask_file_path,"rb");
			fread(mask_data,sizeof(int),it2->mx[latid]*it2->mx[lngid],mask_file);
			fclose(mask_file);
		}
		if ((strcmp(best_decompress_function,"decompress_map")==0) || ((best_pert_compress_function!=NULL) && (strcmp(best_pert_decompress_function,"decompress_map")==0)))
		{
			map_file=fopen(map_file_path,"rb");
			new_data(map_bitstream,it2->mx[latid]*it2->mx[lngid]);
			map_bitstream_start=0;
			map_bitstream_end=0;
		}
		printf("aaa\n");
		bitstream_start=0;
		bitstream_end=0;
		in_file=fopen(in_file_path,"rb");
		if (best_pert!=0)
			new_data(bitstream,(data_num+data_num*best_pert/it2->mx[pertid])*sizeof(T));
		else
			new_data(bitstream,data_num*sizeof(T));
		new_data(data,data_num);
		if (best_pert!=0)
		{
			hyper_iterator_c *it2_backup=it2;
			it2=NULL;
			copy_iterator(it2,it2_backup);
			it2->mx[pertid]=best_pert;
			for (int did=it2->n-1;did>=0;did--)
				if (did==it2->n-1)
					it2->weight[did]=1;
				else
					it2->weight[did]=it2->weight[did+1]*it2->mx[did+1];
			hyper_iterator_c *best_it1_backup=best_it1;
			best_it1=best_pert_it1;
			char *best_fitting_function_backup=best_fitting_function;
			best_fitting_function=best_pert_fitting_function;
			long long data_num_backup=data_num;
			data_num=data_num*it2->mx[pertid]/it2_backup->mx[pertid];
			T *data_backup=data;
			new_data(data,data_num,false,false);
			bitstream_start=bitstream_end+sizeof(long long);
			long long bitstream_length;
			fread(&bitstream_length,sizeof(long long),1,in_file);
			bitstream_end=bitstream_length+bitstream_start;
			fread(bitstream+bitstream_start,sizeof(unsigned char),bitstream_length,in_file);
			if (strcmp(best_pert_decompress_function,"decompress")==0)
				decompress();
			if (strcmp(best_pert_decompress_function,"decompress_map")==0)
			{
				map_bitstream_start=map_bitstream_end+sizeof(long long);
				long long map_bitstream_length;
				fread(&map_bitstream_length,sizeof(long long),1,map_file);
				map_bitstream_end=map_bitstream_length+map_bitstream_start;
				fread(map_bitstream+map_bitstream_start,sizeof(unsigned char),map_bitstream_length,map_file);
				decompress_map();
			}
			if (strcmp(best_pert_decompress_function,"decompress_mask")==0)
			{
				decompress_mask();
				mask_value=0;
			}
			if (strcmp(best_pert_decompress_function,"decompress_map_mask")==0)
			{
				map_bitstream_start=map_bitstream_end+sizeof(long long);
				long long map_bitstream_length;
				fread(&map_bitstream_length,sizeof(long long),1,map_file);
				map_bitstream_end=map_bitstream_length+map_bitstream_start;
				fread(map_bitstream+map_bitstream_start,sizeof(unsigned char),map_bitstream_length,map_file);
				decompress_map_mask();
				mask_value=0;
			}
			pert_it2=it2;
			it2=it2_backup;
			best_it1=best_it1_backup;
			data_num=data_num_backup;
			avg_data=data;
			data=data_backup;
			best_fitting_function=best_fitting_function_backup;
		}
		bitstream_start=bitstream_end+sizeof(long long);
		long long bitstream_length;
		fread(&bitstream_length,sizeof(long long),1,in_file);
		bitstream_end=bitstream_length+bitstream_start;
		printf("bitstream_start=%lld, bitstream_end=%lld\n",bitstream_start,bitstream_end);
		fread(bitstream+bitstream_start,sizeof(unsigned char),bitstream_length,in_file);
		printf("bbb\n");
		if ((best_decompress_function==NULL) || (strcmp(best_decompress_function,"decompress")==0))
			decompress();
		printf("ccc\n");
		if ((best_decompress_function!=NULL) && (strcmp(best_decompress_function,"decompress_map")==0))
		{
			map_bitstream_start=map_bitstream_end+sizeof(long long);
			long long map_bitstream_length;
			fread(&map_bitstream_length,sizeof(long long),1,map_file);
			map_bitstream_end=map_bitstream_length+map_bitstream_start;
			fread(map_bitstream+map_bitstream_start,sizeof(unsigned char),map_bitstream_length,map_file);
			decompress_map();
			delete_data(map_bitstream);
		}
		printf("ddd\n");
		if ((best_decompress_function!=NULL) && (strcmp(best_decompress_function,"decompress_mask")==0))
			decompress_mask();
		printf("eee\n");
		if ((best_decompress_function!=NULL) && (strcmp(best_decompress_function,"decompress_map_mask")==0))
		{
			map_bitstream_start=map_bitstream_end+sizeof(long long);
			long long map_bitstream_length;
			fread(&map_bitstream_length,sizeof(long long),1,map_file);
			map_bitstream_end=map_bitstream_length+map_bitstream_start;
			fread(map_bitstream+map_bitstream_start,sizeof(unsigned char),map_bitstream_length,map_file);
			decompress_map_mask();
		}
		printf("fff\n");
		if (best_pert!=0)
			for (long long pos=0;pos<data_num;pos++)
			{
				long long lat_i=(pos/it2->weight[latid])%it2->mx[latid];
				long long lng_i=(pos/it2->weight[lngid])%it2->mx[lngid];
				long long pos_low=pos%it2->weight[pertid];
				long long pos_pert=(pos-pos_low)%(it2->weight[pertid]*it2->mx[pertid]);
				long long pos_high=pos-pos_pert-pos_low;
				pos_pert=((pos_pert/it2->weight[pertid])%pert_it2->mx[pertid])*pert_it2->weight[pertid];
				pos_high=(pos_high/it2->mx[pertid])*pert_it2->mx[pertid];
				data[pos]+=avg_data[pos_high+pos_pert+pos_low];				
			}
		printf("ggg\n");
		out_file=fopen(out_file_path,"wb");
		fwrite(data,data_num,sizeof(T),out_file);
		fclose(out_file);
		delete_data(data);
		delete_data(bitstream);
		printf("hhh\n");
	}
}

#endif