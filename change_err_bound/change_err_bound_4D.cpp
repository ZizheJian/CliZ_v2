#ifndef __CHANGE_ERR_BOUND_4D_CPP__
#define __CHANGE_ERR_BOUND_4D_CPP__

#include "change_err_bound.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::change_err_bound_4D()
	{
		char *decisive_file_path=NULL;
		#if defined(JOB_TYPE_COMPRESS) || defined(JOB_TYPE_DECOMPRESS)
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
				T data_mn=numeric_limits<T>::max();
				T data_mx=numeric_limits<T>::min();
				long long *mx=it2->mx;
				long long *weight=it2->weight;
				for (long long i0=0;i0<mx[0];i0++)
					for (long long i1=0;i1<mx[1];i1++)
						for (long long i2=0;i2<mx[2];i2++)
							for (long long i3=0;i3<mx[3];i3++)
							{
								long long pos=i0*weight[0]+i1*weight[1]+i2*weight[2]+i3;
								if (data[pos]<data_mn)
									data_mn=data[pos];
								if (data[pos]>data_mx)
									data_mx=data[pos];
							}
				err_bound=(data_mx-data_mn)*raw_err_bound;
				delete_data(data);
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
					T data_mn=numeric_limits<T>::max();
					T data_mx=numeric_limits<T>::min();
					long long *mx=it2->mx;
					long long *weight=it2->weight;
					for (long long i0=0;i0<mx[0];i0++)
						for (long long i1=0;i1<mx[1];i1++)
							for (long long i2=0;i2<mx[2];i2++)
								for (long long i3=0;i3<mx[3];i3++)
								{
									long long pos=i0*weight[0]+i1*weight[1]+i2*weight[2]+i3;
									if (data[pos]<data_mn)
										data_mn=data[pos];
									if (data[pos]>data_mx)
										data_mx=data[pos];
								}
					if (err_bound!=(data_mx-data_mn)*raw_err_bound)
					{
						printf("Error: Error bound mismatch.\n");
						exit(0);
					}
					delete_data(data);
				}
			}
		}
		err_bound_reciprocal=1/err_bound;
	}
}

#endif