#ifndef __READ_CFG_CPP__
#define __READ_CFG_CPP__

#include "init.hpp2"

namespace cliz
{
	void read_cfg(task_c<float> &task_f32)
	{
		// char *temp_string=new_data<char>(100);
		// open_file(t->cfg_file,t->cfg_file_path,"r");
		// fscanf(t->cfg_file,"Data name=%s\n",t->data_name);
		// fscanf(t->cfg_file,"Dimension num=%d\n",&(t->dimension_num));
		// new_data(t->dimension,t->dimension_num);
		// fscanf(t->cfg_file,"Dimension=\n");
		// t->data_num=1;
		// for (int did=0;did<t->dimension_num;did++)
		// {
		// 	fscanf(t->cfg_file,"%lld ",&(t->dimension[did]));
		// 	t->data_num*=t->dimension[did];
		// }
		// new_data(t->dimension_type,t->dimension_num,true);
		// fscanf(t->cfg_file,"\nDimension type=\n");
		// for (int did=0;did<t->dimension_num;did++)
		// {
		// 	new_data(t->dimension_type[did],10);
		// 	fscanf(t->cfg_file,"%s ",t->dimension_type[did]);
		// }
		// fscanf(t->cfg_file,"%s",temp_string);
		// fseek(t->cfg_file,-strlen(temp_string),SEEK_CUR);
		// if (strcmp(temp_string,"Map")==0)
		// 	fscanf(t->cfg_file,"Map file path=%s\n",t->map_file_path);
		// char *temp_data_type=new_data<char>(4);
		// fscanf(t->cfg_file,"Data type=%s\n",temp_data_type);
		// if (t->data_type==NULL)
		// {
		// 	new_data(t->data_type,4);
		// 	strcpy(t->data_type,temp_data_type);
		// }
		// else
		// 	if (strcmp(t->data_type,temp_data_type)!=0)
		// 	{
		// 		printf("Error: cfg file and input command mismatch.\n");
		// 		exit(0);
		// 	}
		// delete_data(temp_data_type);
		// fscanf(t->cfg_file,"Error bound=%f\n",&(t->ABS_err_bound));
		// t->err_bound=t->ABS_err_bound;
		// #ifdef JOB_TYPE_COMPRESS
		// 	new_data(t->best_compress_framework.name,unc);
		// 	fscanf(t->cfg_file,"Best compress framework=%s\n",t->best_compress_framework.name);
		// #endif
		// #ifdef JOB_TYPE_DECOMPRESS
		// 	new_data(t->best_decompress_framework.name,unc);
		// 	fscanf(t->cfg_file,"Best decompress framework=%s\n",t->best_decompress_framework.name);
		// #endif
		// new_data(t->best_predictor.name,unc);
		// fscanf(t->cfg_file,"Best predictor=%s\n",t->best_predictor.name);
		// fscanf(t->cfg_file,"%s",temp_string);
		// fseek(t->cfg_file,-strlen(temp_string),SEEK_CUR);
		// if (temp_string[0]=='B')
		// {
		// 	#ifdef JOB_TYPE_COMPRESS
		// 		new_data(t->best_avg_compress_framework.name,unc);
		// 		fscanf(t->cfg_file,"Best avg compress framework=%s\n",t->best_avg_compress_framework.name);
		// 	#endif
		// 	#ifdef JOB_TYPE_DECOMPRESS
		// 		new_data(t->best_avg_decompress_framework.name,unc);
		// 		fscanf(t->cfg_file,"Best avg decompress framework=%s\n",t->best_avg_decompress_framework.name);
		// 	#endif
		// 	new_data(t->best_avg_predictor.name,unc);
		// 	fscanf(t->cfg_file,"Best avg predictor=%s\n",t->best_avg_predictor.name);
		// }
		// fscanf(t->cfg_file,"%s",temp_string);
		// fseek(t->cfg_file,-strlen(temp_string),SEEK_CUR);
		// if (temp_string[0]=='P')
		// 	fscanf(t->cfg_file,"Pert=%lld\n",&(t->pert));
		// t->best_it1=read_iterator(t->cfg_file,it_list);
		// if (t->pert!=0)
		// 	t->best_avg_it1=read_iterator(t->cfg_file,it_list);
	}

	hyper_iterator_c *read_iterator(FILE *cfg_file,map<long long int,hyper_iterator_c*> &it_list)
	{
		printf("Error: read_iterator incomplete.\n");
		exit(0);
		/*char *temp_string=new_data<char>(100);
		fscanf(cfg_file,"%s",temp_string);
		fseek(cfg_file,-strlen(temp_string),SEEK_CUR);
		int temp_n;
		fscanf(cfg_file,"n=%d\n",&temp_n);
		long long int temp_p;
		fscanf(cfg_file,"address=%p\n",(hyper_iterator_c**)(&temp_p));
		if (it_list.find(temp_p)!=it_list.end())
		{
			hyper_iterator_c *temp_it=it_list[temp_p];
			fscanf(cfg_file,"%s",temp_string);
			fseek(cfg_file,-strlen(temp_string),SEEK_CUR);
			if (temp_string[0]=='n')
			{
				temp_it->base_iterator=true;
				fscanf(cfg_file,"name=%s\n",temp_string);
				for (auto t=task_i32.begin();(t!=task_i32.end()) && (temp_it->name==NULL);t++)
					if (strcmp(t->data_name,temp_string)==0)
					{
						new_data(temp_it->name,strlen(temp_string)+1);
						strcpy(temp_it->name,temp_string);
						t->it2=temp_it;
					}
				for (auto t=task_f32.begin();(t!=task_f32.end()) && (temp_it->name==NULL);t++)
					if (strcmp(t->data_name,temp_string)==0)
					{
						new_data(temp_it->name,strlen(temp_string)+1);
						strcpy(temp_it->name,temp_string);
						t->it2=temp_it;
					}
				for (auto t=task_f64.begin();(t!=task_f64.end()) && (temp_it->name==NULL);t++)
					if (strcmp(t->data_name,temp_string)==0)
					{
						new_data(temp_it->name,strlen(temp_string)+1);
						strcpy(temp_it->name,temp_string);
						t->it2=temp_it;
					}
				if (strcmp(temp_string+strlen(temp_string)-5,"(avg)")==0)
				{
					temp_string[strlen(temp_string)-5]=0;
					for (auto t=task_i32.begin();(t!=task_i32.end()) && (temp_it->name==NULL);t++)
						if (strcmp(t->data_name,temp_string)==0)
						{
							new_data(temp_it->name,strlen(temp_string)+6);
							strcpy(temp_it->name,temp_string);
							strcat(temp_it->name,"(avg)");
							t->avg_it2=temp_it;
						}
					for (auto t=task_f32.begin();(t!=task_f32.end()) && (temp_it->name==NULL);t++)
						if (strcmp(t->data_name,temp_string)==0)
						{
							new_data(temp_it->name,strlen(temp_string)+6);
							strcpy(temp_it->name,temp_string);
							strcat(temp_it->name,"(avg)");
							t->avg_it2=temp_it;
						}
					for (auto t=task_f64.begin();(t!=task_f64.end()) && (temp_it->name==NULL);t++)
						if (strcmp(t->data_name,temp_string)==0)
						{
							new_data(temp_it->name,strlen(temp_string)+6);
							strcpy(temp_it->name,temp_string);
							strcat(temp_it->name,"(avg)");
							t->avg_it2=temp_it;
						}
				}
			}
			for (int i=0;i<4*temp_it->n;i++)
				fscanf(cfg_file,"%s\n",temp_string);
			while ((fscanf(cfg_file,"%s",temp_string)==1) && (fseek(cfg_file,-strlen(temp_string),SEEK_CUR)==0) && (temp_string[0]=='m'))
			{
				fscanf(cfg_file,"mapping_f_name=%s\n",temp_string);
				if (strcmp(temp_string,"seq_mapping")==0)
					for (int i=0;i<temp_it->n;i++)
						fscanf(cfg_file,"%s\n",temp_string);
				if (strcmp(temp_string,"fission_mapping")==0)
				{
					fscanf(cfg_file,"%s\n",temp_string);
					fscanf(cfg_file,"%s\n",temp_string);
				}
				if (strcmp(temp_string,"linear_mapping")==0){}
				if (strcmp(temp_string,"pert_mapping")==0)
					for (int i=0;i<temp_it->n;i++)
						fscanf(cfg_file,"%s\n",temp_string);
			}
			for (auto rel=temp_it->related_iterator_vec.begin();rel!=temp_it->related_iterator_vec.end();rel++)
				rel->son_it=read_iterator(cfg_file,it_list);
			return temp_it;
		}
		else
		{
			hyper_iterator_c *temp_it=new_data<hyper_iterator_c>(temp_n);
			it_list[temp_p]=temp_it;
			fscanf(cfg_file,"%s",temp_string);
			fseek(cfg_file,-strlen(temp_string),SEEK_CUR);
			if (temp_string[0]=='n')
			{
				temp_it->base_iterator=true;
				fscanf(cfg_file,"name=%s\n",temp_string);
				for (auto t=task_i32.begin();(t!=task_i32.end()) && (temp_it->name==NULL);t++)
					if (strcmp(t->data_name,temp_string)==0)
					{
						new_data(temp_it->name,strlen(temp_string)+1);
						strcpy(temp_it->name,temp_string);
						t->it2=temp_it;
					}
				for (auto t=task_f32.begin();(t!=task_f32.end()) && (temp_it->name==NULL);t++)
					if (strcmp(t->data_name,temp_string)==0)
					{
						new_data(temp_it->name,strlen(temp_string)+1);
						strcpy(temp_it->name,temp_string);
						t->it2=temp_it;
					}
				for (auto t=task_f64.begin();(t!=task_f64.end()) && (temp_it->name==NULL);t++)
					if (strcmp(t->data_name,temp_string)==0)
					{
						new_data(temp_it->name,strlen(temp_string)+1);
						strcpy(temp_it->name,temp_string);
						t->it2=temp_it;
					}
				if (strcmp(temp_string+strlen(temp_string)-5,"(avg)")==0)
				{
					temp_string[strlen(temp_string)-5]=0;
					for (auto t=task_i32.begin();(t!=task_i32.end()) && (temp_it->name==NULL);t++)
						if (strcmp(t->data_name,temp_string)==0)
						{
							new_data(temp_it->name,strlen(temp_string)+6);
							strcpy(temp_it->name,temp_string);
							strcat(temp_it->name,"(avg)");
							t->avg_it2=temp_it;
						}
					for (auto t=task_f32.begin();(t!=task_f32.end()) && (temp_it->name==NULL);t++)
						if (strcmp(t->data_name,temp_string)==0)
						{
							new_data(temp_it->name,strlen(temp_string)+6);
							strcpy(temp_it->name,temp_string);
							strcat(temp_it->name,"(avg)");
							t->avg_it2=temp_it;
						}
					for (auto t=task_f64.begin();(t!=task_f64.end()) && (temp_it->name==NULL);t++)
						if (strcmp(t->data_name,temp_string)==0)
						{
							new_data(temp_it->name,strlen(temp_string)+6);
							strcpy(temp_it->name,temp_string);
							strcat(temp_it->name,"(avg)");
							t->avg_it2=temp_it;
						}
				}
			}
			fscanf(cfg_file,"mn=");
			for (int did=0;did<temp_it->n;did++)
				fscanf(cfg_file,"%lld",temp_it->mn+did);
			fscanf(cfg_file,"\nmx=");
			for (int did=0;did<temp_it->n;did++)
				fscanf(cfg_file,"%lld",temp_it->mx+did);
			fscanf(cfg_file,"\ngap=");
			for (int did=0;did<temp_it->n;did++)
				fscanf(cfg_file,"%lld",temp_it->gap+did);
			fscanf(cfg_file,"\nweight=");
			for (int did=0;did<temp_it->n;did++)
				fscanf(cfg_file,"%lld",temp_it->weight+did);
			while ((fscanf(cfg_file,"%s",temp_string)==1) && (fseek(cfg_file,-strlen(temp_string),SEEK_CUR)==0) && (temp_string[0]=='m'))
			{
				fscanf(cfg_file,"mapping_f_name=%s\n",temp_string);
				if (strcmp(temp_string,"seq_mapping")==0)
				{
					temp_it->append_related_iterator_seq(NULL);
					fscanf(cfg_file,"dim_seq=");
					for (int did=0;did<temp_it->n;did++)
						fscanf(cfg_file,"%d",temp_it->related_iterator_vec.rbegin()->dim_seq+did);
				}
				if (strcmp(temp_string,"fission_mapping")==0)
				{
					temp_it->append_related_iterator_fission(NULL);
					fscanf(cfg_file,"dim_fission_l=%d\n",&(temp_it->related_iterator_vec.rbegin()->dim_fission_l));
					fscanf(cfg_file,"dim_fission_r=%d\n",&(temp_it->related_iterator_vec.rbegin()->dim_fission_r));
				}
				if (strcmp(temp_string,"linear_mapping")==0)
				{
					temp_it->append_related_iterator_seq(NULL);
				}
				if (strcmp(temp_string,"pert_mapping")==0)
				{
					temp_it->append_related_iterator_pert(NULL);
					fscanf(cfg_file,"pert=");
					for (int did=0;did<temp_it->n;did++)
						fscanf(cfg_file,"%lld",temp_it->related_iterator_vec.rbegin()->pert+did);
				}
			}
			for (auto rel=temp_it->related_iterator_vec.begin();rel!=temp_it->related_iterator_vec.end();rel++)
				rel->son_it=read_iterator(cfg_file,it_list);
			return temp_it;
		}*/
	}
}



#endif