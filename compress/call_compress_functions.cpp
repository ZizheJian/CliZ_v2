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
		bitstream_start=0;
		bitstream_end=0;
		if ((strcmp(best_compress_function,"compress_mask")==0) || (strcmp(best_compress_function,"compress_set_map_mask")==0) || (strcmp(best_compress_function,"compress_use_map_mask")==0)
			|| ((best_pert_compress_function!=NULL) && ((strcmp(best_pert_compress_function,"compress_mask")==0) || (strcmp(best_pert_compress_function,"compress_set_map_mask")==0)
			|| (strcmp(best_pert_compress_function,"compress_use_map_mask")==0))))
		{
			new_data(mask_data,it2->mx[latid]*it2->mx[lngid]);
			mask_file=fopen(mask_file_path,"rb");
			fread(mask_data,sizeof(int),it2->mx[latid]*it2->mx[lngid],mask_file);
			fclose(mask_file);
		}
		if ((strcmp(best_compress_function,"compress_set_map")==0) || (strcmp(best_compress_function,"compress_set_map_mask")==0)
			|| ((best_pert_compress_function!=NULL) && ((strcmp(best_pert_compress_function,"compress_set_map")==0) || (strcmp(best_pert_compress_function,"compress_set_map_mask")==0))))
		{
			new_data(map_bitstream,it2->mx[latid]*it2->mx[lngid]);
			map_bitstream_start=0;
			map_bitstream_end=0;
		}
		if ((strcmp(best_compress_function,"compress_use_map")==0) || (strcmp(best_compress_function,"compress_use_map_mask")==0)
			|| ((best_pert_compress_function!=NULL) && ((strcmp(best_pert_compress_function,"compress_use_map")==0) || (strcmp(best_pert_compress_function,"compress_use_map_mask")==0))))
		{
			map_file=fopen(map_file_path,"rb");
			map_bitstream_start=0;
			map_bitstream_end=0;
			new_data(map_bitstream,it2->mx[latid]*it2->mx[lngid]);
		}
		printf("aaa\n");
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
			long long data_num_backup=data_num;
			data_num=data_num*it2->mx[pertid]/it2_backup->mx[pertid];
			char *best_fitting_function_backup=best_fitting_function;
			best_fitting_function=best_pert_fitting_function;
			T *data_backup=data;
			new_data(data,data_num,true,false);
			unsigned char *bitstream_backup=bitstream;
			for (long long pos=0;pos<data_num_backup;pos++)
			{
				long long lat_i=(pos/it2_backup->weight[latid])%it2_backup->mx[latid];
				long long lng_i=(pos/it2_backup->weight[lngid])%it2_backup->mx[lngid];
				long long pos_low=pos%it2_backup->weight[pertid];
				long long pos_pert=(pos-pos_low)%(it2_backup->weight[pertid]*it2_backup->mx[pertid]);
				long long pos_high=pos-pos_pert-pos_low;
				pos_pert=((pos_pert/it2_backup->weight[pertid])%it2->mx[pertid])*it2->weight[pertid];
				pos_high=(pos_high/it2_backup->mx[pertid])*it2->mx[pertid];
				if ((mask_file_path!=NULL) && (mask_data[lat_i*it2_backup->mx[lngid]+lng_i]==0))
					data[pos_high+pos_pert+pos_low]=data_backup[pos];
				else
					data[pos_high+pos_pert+pos_low]+=data_backup[pos];
			}
			for (long long pos=0;pos<data_num;pos++)
			{
				long long lat_i=(pos/it2->weight[latid])%it2->mx[latid];
				long long lng_i=(pos/it2->weight[lngid])%it2->mx[lngid];
				if ((mask_file_path!=NULL) && (mask_data[lat_i*it2_backup->mx[lngid]+lng_i]==0))
					continue;
				long long pert_i=(pos/it2->weight[pertid])%it2->mx[pertid];
				data[pos]/=ceil(((float)(it2_backup->mx[pertid]-pert_i))/it2->mx[pertid]);
			}
			bitstream_start=bitstream_end+sizeof(long long);
			bitstream_end=bitstream_start;
			printf("aaaa\n");
			if (strcmp(best_pert_compress_function,"compress")==0)
				compress();
			if (strcmp(best_pert_compress_function,"compress_mask")==0)
				compress_mask();
			if (strcmp(best_pert_compress_function,"compress_set_map")==0)
			{
				map_bitstream_start=map_bitstream_end+sizeof(long long);
				map_bitstream_end=map_bitstream_start;
				compress_set_map();
			}
			if (strcmp(best_pert_compress_function,"compress_use_map")==0)
			{
				map_bitstream_start=map_bitstream_end+sizeof(long long);
				long long map_bitstream_length;
				fread(&map_bitstream_length,sizeof(long long),1,map_file);
				map_bitstream_end=map_bitstream_length+map_bitstream_start;
				fread(map_bitstream+map_bitstream_start,sizeof(unsigned char),map_bitstream_length,map_file);
				compress_use_map();
			}
			if (strcmp(best_pert_compress_function,"compress_set_map_mask")==0)
			{
				map_bitstream_start=map_bitstream_end+sizeof(long long);
				map_bitstream_end=map_bitstream_start;
				compress_set_map_mask();
			}
			if (strcmp(best_pert_compress_function,"compress_use_map_mask")==0)
			{
				map_bitstream_start=map_bitstream_end+sizeof(long long);
				long long map_bitstream_length;
				fread(&map_bitstream_length,sizeof(long long),1,map_file);
				map_bitstream_end=map_bitstream_length+map_bitstream_start;
				new_data(map_bitstream,it2->mx[latid]*it2->mx[lngid]);
				fread(map_bitstream+map_bitstream_start,sizeof(unsigned char),map_bitstream_length,map_file);
				compress_use_map_mask();
			}
			printf("bbbb\n");
			if (best_it1->dim_seq!=NULL)
			{
				T *data_backup=data;
				new_data(data,data_num,false,false);
				anti_transpose_data(data_backup);
				delete_data(data_backup);
			}
			pert_it2=it2;
			it2=it2_backup;
			best_it1=best_it1_backup;
			data_num=data_num_backup;
			for (long long pos=0;pos<data_num;pos++)
			{
				long long lat_i=(pos/it2->weight[latid])%it2->mx[latid];
				long long lng_i=(pos/it2->weight[lngid])%it2->mx[lngid];
				long long pos_low=pos%it2->weight[pertid];
				long long pos_pert=(pos-pos_low)%(it2->weight[pertid]*it2->mx[pertid]);
				long long pos_high=pos-pos_pert-pos_low;
				pos_pert=((pos_pert/it2->weight[pertid])%pert_it2->mx[pertid])*pert_it2->weight[pertid];
				pos_high=(pos_high/it2->mx[pertid])*pert_it2->mx[pertid];
				if ((mask_file_path!=NULL) && (mask_data[lat_i*it2->mx[lngid]+lng_i]==0))
					data_backup[pos]=0;
				else
					data_backup[pos]-=data[pos_high+pos_pert+pos_low];
			}
			delete_data(pert_it2);
			best_fitting_function=best_fitting_function_backup;
			delete_data(data);
			data=data_backup;
		}
		printf("bbb\n");
		bitstream_start=bitstream_end+sizeof(long long);
		bitstream_end=bitstream_start;
		if (strcmp(best_compress_function,"compress")==0)
			compress();
		if (strcmp(best_compress_function,"compress_mask")==0)
			compress_mask();
		if (strcmp(best_compress_function,"compress_set_map")==0)
		{
			map_bitstream_start=map_bitstream_end+sizeof(long long);
			map_bitstream_end=map_bitstream_start;
			compress_set_map();
		}
		if (strcmp(best_compress_function,"compress_use_map")==0)
		{
			map_bitstream_start=map_bitstream_end+sizeof(long long);
			long long map_bitstream_length;
			fread(&map_bitstream_length,sizeof(long long),1,map_file);
			map_bitstream_end=map_bitstream_length+map_bitstream_start;
			new_data(map_bitstream,it2->mx[latid]*it2->mx[lngid]);
			fread(map_bitstream+map_bitstream_start,sizeof(unsigned char),map_bitstream_length,map_file);
			compress_use_map();
		}
		if (strcmp(best_compress_function,"compress_set_map_mask")==0)
		{
			map_bitstream_start=map_bitstream_end+sizeof(long long);
			map_bitstream_end=map_bitstream_start;
			compress_set_map_mask();
		}
		if (strcmp(best_compress_function,"compress_use_map_mask")==0)
		{
			map_bitstream_start=map_bitstream_end+sizeof(long long);
			long long map_bitstream_length;
			fread(&map_bitstream_length,sizeof(long long),1,map_file);
			map_bitstream_end=map_bitstream_length+map_bitstream_start;
			new_data(map_bitstream,it2->mx[latid]*it2->mx[lngid]);
			fread(map_bitstream+map_bitstream_start,sizeof(unsigned char),map_bitstream_length,map_file);
			compress_use_map_mask();
		}
		if ((strcmp(best_compress_function,"compress_mask")==0) || (strcmp(best_compress_function,"compress_set_map_mask")==0) || (strcmp(best_compress_function,"compress_use_map_mask")==0)
			|| ((best_pert_compress_function!=NULL) && ((strcmp(best_pert_compress_function,"compress_mask")==0) || (strcmp(best_pert_compress_function,"compress_set_map_mask")==0)
			|| (strcmp(best_pert_compress_function,"compress_use_map_mask")==0))))
			delete_data(mask_data);
		if ((strcmp(best_compress_function,"compress_set_map")==0) || (strcmp(best_compress_function,"compress_set_map_mask")==0)
			|| ((best_pert_compress_function!=NULL) && ((strcmp(best_pert_compress_function,"compress_set_map")==0) || (strcmp(best_pert_compress_function,"compress_set_map_mask")==0))))
		{
			map_file=fopen(map_file_path,"wb");
			fwrite(map_bitstream,map_bitstream_end,sizeof(unsigned char),map_file);
			fclose(map_file);
			delete_data(map_bitstream);
		}
		if ((strcmp(best_compress_function,"compress_use_map")==0) || (strcmp(best_compress_function,"compress_use_map_mask")==0)
			|| ((best_pert_compress_function!=NULL) && ((strcmp(best_pert_compress_function,"compress_use_map")==0) || (strcmp(best_pert_compress_function,"compress_use_map_mask")==0))))
		{
			delete_data(map_bitstream);
			fclose(map_file);
		}
		out_file=fopen(out_file_path,"wb");
		fwrite(bitstream,bitstream_end,sizeof(unsigned char),out_file);
		fclose(out_file);
		delete_data(data);
		delete_data(bitstream);
	}
}

#endif