#ifndef __CHANGE_ERR_BOUND_CPP__
#define __CHANGE_ERR_BOUND_CPP__

#include "change_err_bound.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::change_err_bound()
	{
		#if defined(JOB_TYPE_COMPRESS) || defined(JOB_TYPE_VALIDATE)
			if (mask_file_path!=NULL)
			{
				new_data(pos2horiz_mapping,data_num);
				generate_pos2horiz_mapping();
			}
			bool find_mask_value=(cfg_file_path!=NULL) && (strcmp(cfg_file_mode,"use")==0);
			char *decisive_file_path=NULL;
			#ifdef JOB_TYPE_COMPRESS
				decisive_file_path=in_file_path;
			#endif
			#ifdef JOB_TYPE_VALIDATE
				decisive_file_path=src_file_path;
			#endif
			if ((cfg_file_mode==NULL) || (strcmp(cfg_file_mode,"set")==0))
			{
				if (strcmp(err_type,"ABS")==0)
					err_bound=raw_err_bound;
				if (strcmp(err_type,"REL")==0)
				{
					new_data(data,data_num);
					FILE *decisive_file=fopen(decisive_file_path,"rb");
					fread(data,sizeof(T),data_num,decisive_file);
					fclose(decisive_file);
					if (mask_file_path!=NULL)
					{
						new_data(mask_data,it2->mx[latid]*it2->mx[lngid]);
						mask_file=fopen(mask_file_path,"rb");
						fread(mask_data,sizeof(int),it2->mx[latid]*it2->mx[lngid],mask_file);
						fclose(mask_file);
					}
					T data_mn=numeric_limits<T>::max();
					T data_mx=numeric_limits<T>::min();
					for (long long i=0;i<data_num;i++)
						if ((mask_file_path!=NULL) && (mask_data[pos2horiz_mapping[i]]==0))
							if (find_mask_value)
							{
								if (mask_value!=data[i])
								{
									printf("Error: Multiple mask value found.\n");
									exit(0);
								}
							}
							else
							{
								mask_value=data[i];
								find_mask_value=true;
							}
						else
						{
							if (data[i]<data_mn)
								data_mn=data[i];
							if (data[i]>data_mx)
								data_mx=data[i];
						}
					err_bound=(data_mx-data_mn)*raw_err_bound;
					delete_data(data);
					if (mask_file_path!=NULL)
						delete_data(mask_data);
				}
			}
			else
			{
				if (err_type==NULL)
				{
					new_data(err_type,4);
					strcpy(err_type,"ABS");
				}
				else
				{
					if ((strcmp(err_type,"ABS")==0) && (err_bound!=raw_err_bound))
					{
						printf("Error: Error bound mismatch.\n");
						exit(0);
					}
					if (strcmp(err_type,"REL")==0)
					{
						new_data(data,data_num);
						FILE *decisive_file=fopen(decisive_file_path,"rb");
						fread(data,sizeof(T),data_num,decisive_file);
						fclose(decisive_file);
						if (mask_file_path!=NULL)
						{
							new_data(mask_data,it2->mx[latid]*it2->mx[lngid]);
							mask_file=fopen(mask_file_path,"rb");
							fread(mask_data,sizeof(int),it2->mx[latid]*it2->mx[lngid],mask_file);
							fclose(mask_file);
						}
						T data_mn=numeric_limits<T>::max();
						T data_mx=numeric_limits<T>::min();
						for (long long i=0;i<data_num;i++)
						if ((mask_file_path!=NULL) && (mask_data[pos2horiz_mapping[i]]==0))
							if (find_mask_value)
							{
								if (mask_value!=data[i])
								{
									printf("Error: Multiple mask value found.\n");
									exit(0);
								}
							}
							else
							{
								mask_value=data[i];
								find_mask_value=true;
							}
						else
						{
							if (data[i]<data_mn)
								data_mn=data[i];
							if (data[i]>data_mx)
								data_mx=data[i];
						}
						if (err_bound!=(data_mx-data_mn)*raw_err_bound)
						{
							printf("Error: Error bound mismatch.\n");
							exit(0);
						}
						delete_data(data);
						if (mask_file_path!=NULL)
							delete_data(mask_data);
					}
				}
			}
			err_bound_reciprocal=1/err_bound;
			if (mask_file_path!=NULL)
				delete_data(pos2horiz_mapping);
		#endif
		#ifdef JOB_TYPE_DECOMPRESS
			if (strcmp(err_type,"ABS")!=0)
			{
				printf("Error: When configuration file isn't given, error type must be ABS.\n");
				exit(0);
			}
			err_bound=raw_err_bound;
		#endif
	}
}

#endif