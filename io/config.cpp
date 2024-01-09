#ifndef __CONFIG_CPP__
#define __CONFIG_CPP__

#include "io.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::write_cfg()
	{
		if ((cfg_file_mode==NULL) || (strcmp(cfg_file_mode,"use")==0))
			return;
		cfg_file=fopen(cfg_file_path,"w");
		fprintf(cfg_file,"Dimension num=%d\n",dimension_num);
		fprintf(cfg_file,"Dimension=");
		for (int did=0;did<dimension_num;did++)
			if (dimension_type[did]!=NULL)
				fprintf(cfg_file,"%s%lld ",dimension_type[did],dimension[did]);
			else
				fprintf(cfg_file,"%lld ",dimension[did]);
		fprintf(cfg_file,"\n");
		fprintf(cfg_file,"Data type=%s\n",data_type);
		fprintf(cfg_file,"Error bound=%la\n",err_bound);
		fprintf(cfg_file,"Best compress function=%s\n",best_compress_function);
		fprintf(cfg_file,"Best fitting function=%s\n",best_fitting_function);
		best_it1->write(cfg_file);
		// if (pert!=0)
		// {
		//	 fprintf(cfg_file,"Best avg decompress framework=de%s\n",best_avg_compress_framework.name);
		//	 fprintf(cfg_file,"Best avg predictor=%s\n",best_avg_predictor.name);
		// }
		// if (pert!=0)
		//	 fprintf(cfg_file,"Pert=%lld\n",pert);
		// fprintf(cfg_file,"\n");
	
		// best_it1->write(cfg_file);
		// if (pert!=0)
		//	 best_avg_it1->write(cfg_file);
		fclose(cfg_file);
	}

	template<typename T>
	void task_c<T>::read_cfg()
	{
		cfg_file=fopen(cfg_file_path,"r");
		char *temp_string=new_data<char>(TEMP_STRING_LENGTH);
		while (fscanf(cfg_file,"%[^\n]",temp_string)==1)
		{
			fseek(cfg_file,1,SEEK_CUR);
			if (strncmp(temp_string,"Dimension num=",14)==0)
			{
				read_cfg_dimension_num(temp_string+14);
				continue;
			}
			if (strncmp(temp_string,"Dimension=",10)==0)
			{
				read_cfg_dimension(temp_string+10);
				continue;
			}
			if (strncmp(temp_string,"Data type=",10)==0)
			{
				read_cfg_data_type(temp_string+10);
				continue;
			}
			if (strncmp(temp_string,"Error bound=",12)==0)
			{
				read_cfg_err_bound(temp_string+12);
				continue;
			}
			if (strncmp(temp_string,"Best compress function=",23)==0)
			{
				#ifdef JOB_TYPE_COMPRESS
					read_cfg_best_compress_function(temp_string+23);
				#elif defined JOB_TYPE_DECOMPRESS
					read_cfg_best_decompress_function(temp_string+23);
				#endif
				continue;
			}
			if (strncmp(temp_string,"Best fitting function=",22)==0)
			{
				read_cfg_best_fitting_function(temp_string+22);
				continue;
			}
			if (strncmp(temp_string,"Max=",4)==0)
			{
				read_cfg_it1_max(temp_string+4);
				continue;
			}
			if (strncmp(temp_string,"Dimension sequence=",19)==0)
			{
				read_cfg_seq_mapping(temp_string+19);
				continue;
			}
			if (strncmp(temp_string,"Dimension fission=",18)==0)
			{
				read_cfg_fission_mapping(temp_string+18);
				continue;
			}
		}
	}

	template<typename T>
	void task_c<T>::read_cfg_dimension_num(char *temp_string)
	{
		int temp_dimension_num;
		sscanf(temp_string,"%d\n",&temp_dimension_num);
		if (dimension_num==0)
			dimension_num=temp_dimension_num;
		else
			if (dimension_num!=temp_dimension_num)
			{
				printf("Error: Dimension mismatch.\n");
				exit(0);
			}
	}

	template<typename T>
	void task_c<T>::read_cfg_dimension(char *temp_string)
	{
		istringstream iss(temp_string);
		string s;
		if (dimension==NULL)
		{
			new_data(dimension,dimension_num);
			new_data(dimension_type,dimension_num);
			data_num=1;
			for (int i=0;iss>>s;i++)
			{
				dimension[i]=0;
				int weight=1;
				int type_len=0;
				for (int k=strlen(s.c_str())-1;k>=0;k--)
					if ((s[k]>='0') && (s[k]<='9'))
					{
						dimension[i]+=(s[k]-'0')*weight;
						weight*=10;
					}
					else
					{
						type_len=k+1;
						break;
					}
				if (type_len==0)
					dimension_type[i]=NULL;
				else
				{
					new_data(dimension_type[i],type_len+1);
					strncpy(dimension_type[i],s.c_str(),type_len);
					dimension_type[i][type_len]=0;
				}
				data_num*=dimension[i];
			}
		}
		else
			for (int i=0;iss>>s;i++)
			{
				long long temp_dimension=0;
				int weight=1;
				int type_len=0;
				for (int k=strlen(s.c_str())-1;k>=0;k--)
					if ((s[k]>='0') && (s[k]<='9'))
					{
						temp_dimension+=(s[k]-'0')*weight;
						weight*=10;
					}
					else
					{
						type_len=k+1;
						break;
					}
				if (dimension[i]!=temp_dimension)
				{
					printf("Error: Dimension mismatch.\n");
					exit(0);
				}
				if (type_len==0)
					if (dimension_type[i]!=NULL)
					{
						printf("Error: Dimension_type mismatch.\n");
						exit(0);
					}
				else
					if (strncmp(dimension_type[i],s.c_str(),type_len)!=0)
					{
						printf("Error: Dimension_type mismatch.\n");
						exit(0);
					}
			}
	}

	template<typename T>
	void task_c<T>::read_cfg_data_type(char *temp_string)
	{
		char *temp_data_type=new_data<char>(strlen(temp_string)+1);
		sscanf(temp_string,"%s",temp_data_type);
		if (data_type==NULL)
			data_type=temp_data_type;
		else
			if (strcmp(data_type,temp_string)!=0)
			{
				printf("Error: Data type mismatch.\n");
				exit(0);
			}
	}

	template<typename T>
	void task_c<T>::read_cfg_err_bound(char *temp_string)
	{
		if (sscanf(temp_string,"%lf",&err_bound)==1){}
		else 
			sscanf(temp_string,"%la",&err_bound);
	}

	template<typename T>
	void task_c<T>::read_cfg_best_compress_function(char *temp_string)
	{
		new_data(best_compress_function,strlen(temp_string)+1);
		sscanf(temp_string,"%s",best_compress_function);
	}

	template<typename T>
	void task_c<T>::read_cfg_best_decompress_function(char *temp_string)
	{
		new_data(best_decompress_function,strlen(temp_string)+3);
		sprintf(best_decompress_function,"de%s",temp_string);
	}

	template<typename T>
	void task_c<T>::read_cfg_best_fitting_function(char *temp_string)
	{
		new_data(best_fitting_function,strlen(temp_string)+1);
		sscanf(temp_string,"%s",best_fitting_function);
	}

	template<typename T>
	void task_c<T>::read_cfg_it1_max(char *temp_string)
	{
		istringstream iss(temp_string);
		string s;
		int temp_n=0;
		while (iss>>s)
			temp_n++;
		new_data(best_it1,temp_n);
		iss.clear();
		iss.seekg(0,ios::beg);
		for (int did=0;iss>>s;did++)
			sscanf(s.c_str(),"%lld",&best_it1->mx[did]);
		for (int did=best_it1->n-1;did>=0;did--)
		{
			if (did==best_it1->n-1)
				best_it1->weight[did]=1;
			else
				best_it1->weight[did]=best_it1->weight[did+1]*best_it1->mx[did+1];
		}
	}

	template<typename T>
	void task_c<T>::read_cfg_seq_mapping(char *temp_string)
	{
		if (best_it1==NULL)
		{
			printf("Error: Defining mapping before definning iterators.\n");
			exit(0);
		}
		istringstream iss(temp_string);
		string s;
		int temp_n=0;
		while (iss>>s)
			temp_n++;
		iss.clear();
		iss.seekg(0,ios::beg);
		if (dimension_num!=0)
			if (temp_n!=dimension_num)
			{
				printf("Error: Length of dimension sequence != dimension num.\n");
				exit(0);
			}
		new_data(best_it1->dim_seq,dimension_num);
		for (int did=0;iss>>s;did++)
			sscanf(s.c_str(),"%d",&best_it1->dim_seq[did]);
	}

	template<typename T>
	void task_c<T>::read_cfg_fission_mapping(char *temp_string)
	{
		if (best_it1==NULL)
		{
			printf("Error: Defining mapping before definning iterators.\n");
			exit(0);
		}
		istringstream iss(temp_string);
		string s;
		int temp_n=0;
		while (iss>>s)
			temp_n++;
		iss.clear();
		iss.seekg(0,ios::beg);
		if (temp_n!=2)
		{
			printf("Error: Length of dimension fission != 2.\n");
			exit(0);
		}
		iss>>s;
		sscanf(s.c_str(),"%d",&best_it1->dim_fission_l);
		iss>>s;
		sscanf(s.c_str(),"%d",&best_it1->dim_fission_r);
	}
}

#endif