// #ifndef __FILE_CPP__
// #define __FILE_CPP__

// #include "io.hpp2"

// namespace cliz
// {
// 	void open_file(FILE *&f,const char *fname,const char *type,bool reuse_check=true)
// 	{
// 		if ((f!=NULL) && (reuse_check))
// 		{
// 			printf("Warning: Reusing file pointer.\n");
// 			return;
// 		}
// 		f=fopen(fname,type);
// 		if (f==NULL)
// 		{
// 			printf("Error: File \"%s\" open failed\n",fname);
// 			exit(0);
// 		}
// 	}

// 	void close_file(FILE *&f)
// 	{
// 		if (f!=NULL)
// 		{
// 			fclose(f);
// 			f=NULL;
// 		}
// 		else
// 			printf("Warning: Closing an invalid file pointer.\n");
// 	}
// }

// #ifndef __IO_CPP__
// #define __IO_CPP__

// #include "globalvar.hpp"

// namespace cliz
// {
// 	//从文件读取一些char
// 	//读到0x00时停止（0x00会被读，但不会被记录）
// 	//给char *s分配一个字符串，将读到的内容写进去，最后补上一个0。但如果没有读到任何字符，就写入NULL
// 	void read_string(FILE *f,char *&s,int additional_char=0)
// 	{
// 		vector<char> buffer;
// 		while (true)
// 		{
// 			char next_char;
// 			fread(&next_char,sizeof(char),1,f);
// 			if (next_char!=0)
// 				buffer.push_back(next_char);
// 			else
// 				break;
// 		}
// 		if (buffer.size()==0)
// 			s=NULL;
// 		else
// 		{
// 			new_data(s,buffer.size()+additional_char+1);
// 			for (int j=0;j<buffer.size();j++)
// 				s[j]=buffer[j];
// 			s[buffer.size()]=0;
// 		}
// 	}

// 	void write_string(FILE *f,char *s)
// 	{
// 		char zero=0;
// 		if (s==NULL)
// 			fwrite(&zero,sizeof(char),1,f);
// 		else
// 			fwrite(s,sizeof(char),strlen(s)+1,f);
// 	}

// 	template<typename T>
// 	void task_c<T>::read_iterator(hyper_iterator_c *&it)
// 	{
// 		/*int n;
// 		fread(&n,sizeof(int),1,source_file);
// 		new_data(it,n);
// 		fread(it->mn,sizeof(long long),it->n,source_file);
// 		fread(it->mx,sizeof(long long),it->n,source_file);
// 		fread(it->weight,sizeof(long long),it->n,source_file);
// 		fread(&(it->base_iterator),sizeof(bool),1,source_file);
// 		if (it->base_iterator)
// 		{
// 			for (int did=0;did<it->n;did++)
// 				it->gap[did]=1;
// 			read_string(source_file,it->name,10);
// 			strcat(it->name,".air");
// 			for (auto t=task_i32.begin();t!=task_i32.end();t++)
// 				if (strcmp(t->name,it->name)==0)
// 					if (t->it2==NULL)
// 						t->it2=it;
// 					else
// 					{
// 						delete_data(it);
// 						it=t->it2;
// 					}
// 			for (auto t=task_f32.begin();t!=task_f32.end();t++)
// 				if (strcmp(t->name,it->name)==0)
// 					if (t->it2==NULL)
// 						t->it2=it;
// 					else
// 					{
// 						delete_data(it);
// 						it=t->it2;
// 					}
// 			for (auto t=task_f64.begin();t!=task_f64.end();t++)
// 				if (strcmp(t->name,it->name)==0)
// 					if (t->it2==NULL)
// 						t->it2=it;
// 					else
// 					{
// 						delete_data(it);
// 						it=t->it2;
// 					}
// 		}
// 		int len;
// 		fread(&len,sizeof(int),1,source_file);
// 		for (int i=0;i<len;i++)
// 		{
// 			char *f_name=new_data<char>(F_NAME_LENGTH);
// 			read_string(source_file,f_name);
// 			if (strcmp(f_name,"seq_mapping")==0)
// 			{
// 				if (i==it->related_iterator_vec.size())
// 					it->append_related_iterator_seq(NULL);
// 				fread(it->related_iterator_vec[i].dim_seq,sizeof(int),it->n,source_file);
// 			}
// 			if (strcmp(f_name,"fission_mapping")==0)
// 			{
// 				if (i==it->related_iterator_vec.size())
// 					it->append_related_iterator_fission(NULL);
// 				fread(&(it->related_iterator_vec[i].dim_fission_l),sizeof(int),1,source_file);
// 				fread(&(it->related_iterator_vec[i].dim_fission_r),sizeof(int),1,source_file);
// 			}
// 			if (strcmp(f_name,"linear_mapping")==0)
// 			{
// 				if (i==it->related_iterator_vec.size())
// 					it->append_related_iterator_linear(NULL);
// 				fread(it->related_iterator_vec[i].mul,sizeof(long long),it->n,source_file);
// 				fread(it->related_iterator_vec[i].div,sizeof(long long),it->n,source_file);
// 				fread(it->related_iterator_vec[i].plus,sizeof(long long),it->n,source_file);
// 			}
// 			hyper_iterator_c *temp_it=NULL;
// 			if (i<it->related_iterator_vec.size())
// 				temp_it=it->related_iterator_vec[i].son_it;
// 			read_iterator(temp_it);
// 			it->related_iterator_vec[i].son_it=temp_it;
// 			delete_data(f_name);
// 		}*/
// 	}

// 	/*template<typename T>
// 	void task_c<T>::write_iterator(hyper_iterator_c *it)
// 	{
// 		fwrite(&(it->n),sizeof(int),1,out_file);
// 		fwrite(it->mn,sizeof(long long),it->n,out_file);
// 		fwrite(it->mx,sizeof(long long),it->n,out_file);
// 		fwrite(it->weight,sizeof(long long),it->n,out_file);
// 		fwrite(&(it->base_iterator),sizeof(bool),1,out_file);
// 		if (it->base_iterator)
// 			write_string(out_file,it->name);
// 		int len=(it->related_iterator_vec).size();
// 		fwrite(&len,sizeof(int),1,out_file);
// 		for (auto rel_it=it->related_iterator_vec.begin();rel_it!=it->related_iterator_vec.end();rel_it++)
// 		{
// 			write_string(out_file,rel_it->mapping_f_name);
// 			if (strcmp(rel_it->mapping_f_name,"seq_mapping")==0)
// 				fwrite(rel_it->dim_seq,sizeof(int),it->n,out_file);
// 			if (strcmp(rel_it->mapping_f_name,"fission_mapping")==0)
// 			{
// 				fwrite(&(rel_it->dim_fission_l),sizeof(int),1,out_file);
// 				fwrite(&(rel_it->dim_fission_r),sizeof(int),1,out_file);
// 			}
// 			if (strcmp(rel_it->mapping_f_name,"linear_mapping")==0)
// 			{
// 				fwrite(rel_it->mul,sizeof(long long),it->n,out_file);
// 				fwrite(rel_it->div,sizeof(long long),it->n,out_file);
// 				fwrite(rel_it->plus,sizeof(long long),it->n,out_file);
// 			}
// 			write_iterator(rel_it->son_it);
// 		}
// 	}*/

// 	//读取维度数量，维度，维度类型，数据类型，数据物理意义，最大误差
// 	//计算数据数量
// 	//支持反复读取
// 	template<typename T>
// 	void task_c<T>::read_info()
// 	{
// 		/*read_string(in_file,data_type);
// 		get_data_type=true;
// 		fread(&err_bound,sizeof(float),1,in_file);
// 		get_err_bound=true;
// 		read_iterator(it1);
// 		data_num=1;
// 		dimension_num=it2->n;
// 		new_data(dimension,it2->n);
// 		new_data(dimension_type,it2->n,true);
// 		for (int did=0;did<it2->n;did++)
// 		{
// 			data_num*=it2->mx[did];
// 			dimension[did]=it2->mx[did];
// 		}
// 		read_string(in_file,decompress_framework_f_name);
// 		if (decompress_framework_f_name!=NULL)
// 		{
// 			char *temp=new_data<char>(strlen(decompress_framework_f_name)+10);
// 			sprintf(temp,"de%s",decompress_framework_f_name);
// 			delete_data(decompress_framework_f_name);
// 			decompress_framework_f_name=temp;
// 		}
// 		read_string(in_file,predictor_f_name);
// 		read_string(in_file,dequantize_f_name);
// 		if (dequantize_f_name!=NULL)
// 		{
// 			char *temp=new_data<char>(strlen(dequantize_f_name)+10);
// 			sprintf(temp,"de%s",dequantize_f_name);
// 			delete_data(dequantize_f_name);
// 			dequantize_f_name=temp;
// 		}
// 		if ((decompress_framework_f_name!=NULL) && ((strcmp(decompress_framework_f_name,"decompress_framework_AI")==0)
// 			|| (strcmp(decompress_framework_f_name,"decompress_framework_AI_mask")==0)))
// 		{
// 			if (strcmp(predictor_f_name,"linear_AI_predictor")==0)
// 			{
// 				new_data(AI.mem_f_name,F_NAME_LENGTH);
// 				strcpy(AI.mem_f_name,"linear_mem");
// 				AI.mem_f=[&](bool active){AI.linear_mem(active);};
// 			}
// 			if (strcmp(predictor_f_name,"cubic_AI_predictor")==0)
// 			{
// 				new_data(AI.mem_f_name,F_NAME_LENGTH);
// 				strcpy(AI.mem_f_name,"cubic_mem");
// 				AI.mem_f=[&](bool active){AI.cubic_mem(active);};
// 			}
// 			if (strcmp(predictor_f_name,"highdim_AI_predictor")==0)
// 			{
// 				new_data(AI.mem_f_name,F_NAME_LENGTH);
// 				strcpy(AI.mem_f_name,"highdim_mem");
// 				AI.mem_f=[&](bool active){AI.highdim_mem(active);};
// 			}
// 			AI.mem_f(true);
// 			fread(AI_param,sizeof(T),AI_digit,in_file);
// 		}*/
// 	}

// 	//向输出文件写入维度数量，维度，维度类型，数据类型，数据物理意义，最大误差
// 	template<typename T>
// 	void task_c<T>::write_info()
// 	{
// 		/*fprintf(cfg_file,"Data name=%s\n",data_name);
// 		fprintf(cfg_file,"Dimension num=%d\n",dimension_num);
// 		fprintf(cfg_file,"Dimension=");
// 		for (int did=0;did<dimension_num;did++)
// 			fprintf(cfg_file,"%lld ",dimension[did]);
// 		fprintf(cfg_file,"\nDimension type=");
// 		for (int did=0;did<dimension_num;did++)
// 			fprintf(cfg_file,"%s ",dimension_type[did]);
// 		fprintf(cfg_file,"\n");
// 		if ((strcmp(best_compress_framework.name,"compress_framework_map_mask")==0)
// 			|| ((pert!=0) && (strcmp(best_avg_compress_framework.name,"compress_framework_map_mask")==0)))
// 			fprintf(cfg_file,"Map file path=%s\n",map_file_path);
// 		fprintf(cfg_file,"Data type=%s\n",data_type);
// 		fprintf(cfg_file,"Error bound=%.30f\n",ABS_err_bound);
// 		fprintf(cfg_file,"Best decompress framework=de%s\n",best_compress_framework.name);
// 		fprintf(cfg_file,"Best predictor=%s\n",best_predictor.name);
// 		if (pert!=0)
// 		{
// 			fprintf(cfg_file,"Best avg decompress framework=de%s\n",best_avg_compress_framework.name);
// 			fprintf(cfg_file,"Best avg predictor=%s\n",best_avg_predictor.name);
// 		}
// 		if (pert!=0)
// 			fprintf(cfg_file,"Pert=%lld\n",pert);
// 		fprintf(cfg_file,"\n");
		
// 		best_it1->write(cfg_file);
// 		if (pert!=0)
// 			best_avg_it1->write(cfg_file);*/
// 	}

// 	template<typename T>
// 	void task_c<T>::read_data()
// 	{
// 		fread(data,sizeof(T),data_num,in_file);
// 	}

// 	template<typename T>
// 	void task_c<T>::read_decompressed_data()
// 	{
// 		fread(data,sizeof(T),data_num,out_file);
// 	}

// 	template<typename T>
// 	void task_c<T>::write_data()
// 	{
// 		fwrite(data,sizeof(T),data_num,out_file);
// 	}

// 	template<typename T>
// 	void task_c<T>::read_huffman_tree_cache_size(int pid)
// 	{
// 		fread(&(huffman[pid].tree_cache_length),sizeof(int),1,in_file);
// 	}

// 	//读取huffman树的cache的编码数量
// 	//读取cache
// 	template<typename T>
// 	void task_c<T>::read_huffman_tree(int pid)
// 	{
// 		fread(huffman[pid].cache,sizeof(unsigned short),huffman[pid].tree_cache_length,in_file);
// 	}

// 	//一个int型的cache编码数量
// 	//cache_length个unsigned short
// 	template<typename T>
// 	void task_c<T>::write_huffman_tree(int pid)
// 	{
// 		fwrite(&(huffman[pid].tree_cache_length),sizeof(int),1,out_file);
// 		printf("huffman[%d].tree_cache_length=%ld\n",pid,huffman[pid].tree_cache_length*sizeof(unsigned short));
// 		fwrite(huffman[pid].cache,sizeof(unsigned short),huffman[pid].tree_cache_length,out_file);
// 	}

// 	template<typename T>
// 	void task_c<T>::read_quant_bin_cache_length()
// 	{
// 		fread(sumbits+0,sizeof(long long),1,in_file);
// 		sumbytes[0]=(sumbits[0]+7)/8;
// 	}

// 	template<typename T>
// 	void task_c<T>::read_quant_bin_cache()
// 	{
// 		fread(quant_bin_cache,sizeof(unsigned char),sumbytes[0],in_file);
// 	}

// 	//一个long long型的quant_bin_cache有效位数
// 	//sumbytes个unsigned char
// 	template<typename T>
// 	void task_c<T>::write_quant_bin()
// 	{
// 		fwrite(sumbits,sizeof(long long),1,out_file);
// 		printf("quant_bin_cache_length=%lld\n",sumbytes[0]);
// 		fwrite(quant_bin_cache,sizeof(unsigned char),sumbytes[0],out_file);
// 	}

// 	template<typename T>
// 	void task_c<T>::read_irr_data()
// 	{
// 		long long len;
// 		fread(&len,sizeof(long long),1,in_file);
// 		for (long long i=0;i<len;i++)
// 		{
// 			T irr;
// 			fread(&irr,sizeof(T),1,in_file);
// 			irregular_data.push_back(irr);
// 		}
// 	}

// 	template<typename T>
// 	void task_c<T>::write_irr_data()
// 	{
// 		long long len=irregular_data.size();
// 		fwrite(&len,sizeof(long long),1,out_file);
// 		printf("irregulat_data.length=%lld\n",len*sizeof(T));
// 		for (auto it=irregular_data.begin();it!=irregular_data.end();it++)
// 		{
// 			T irr=*it;
// 			fwrite(&irr,sizeof(T),1,out_file);
// 		}
// 	}
// }

// #endif


// #ifndef __READ_CFG_CPP__
// #define __READ_CFG_CPP__

// #include "io.hpp2"

// namespace cliz
// {
// 	hyper_iterator_c *read_iterator(FILE *cfg_file,map<long long int,hyper_iterator_c*> &it_list)
// 	{
// 		printf("Error: read_iterator incomplete.\n");
// 		exit(0);
// 		/*char *temp_string=new_data<char>(100);
// 		fscanf(cfg_file,"%s",temp_string);
// 		fseek(cfg_file,-strlen(temp_string),SEEK_CUR);
// 		int temp_n;
// 		fscanf(cfg_file,"n=%d\n",&temp_n);
// 		long long int temp_p;
// 		fscanf(cfg_file,"address=%p\n",(hyper_iterator_c**)(&temp_p));
// 		if (it_list.find(temp_p)!=it_list.end())
// 		{
// 			hyper_iterator_c *temp_it=it_list[temp_p];
// 			fscanf(cfg_file,"%s",temp_string);
// 			fseek(cfg_file,-strlen(temp_string),SEEK_CUR);
// 			if (temp_string[0]=='n')
// 			{
// 				temp_it->base_iterator=true;
// 				fscanf(cfg_file,"name=%s\n",temp_string);
// 				for (auto t=task_i32.begin();(t!=task_i32.end()) && (temp_it->name==NULL);t++)
// 					if (strcmp(t->data_name,temp_string)==0)
// 					{
// 						new_data(temp_it->name,strlen(temp_string)+1);
// 						strcpy(temp_it->name,temp_string);
// 						t->it2=temp_it;
// 					}
// 				for (auto t=task_f32.begin();(t!=task_f32.end()) && (temp_it->name==NULL);t++)
// 					if (strcmp(t->data_name,temp_string)==0)
// 					{
// 						new_data(temp_it->name,strlen(temp_string)+1);
// 						strcpy(temp_it->name,temp_string);
// 						t->it2=temp_it;
// 					}
// 				for (auto t=task_f64.begin();(t!=task_f64.end()) && (temp_it->name==NULL);t++)
// 					if (strcmp(t->data_name,temp_string)==0)
// 					{
// 						new_data(temp_it->name,strlen(temp_string)+1);
// 						strcpy(temp_it->name,temp_string);
// 						t->it2=temp_it;
// 					}
// 				if (strcmp(temp_string+strlen(temp_string)-5,"(avg)")==0)
// 				{
// 					temp_string[strlen(temp_string)-5]=0;
// 					for (auto t=task_i32.begin();(t!=task_i32.end()) && (temp_it->name==NULL);t++)
// 						if (strcmp(t->data_name,temp_string)==0)
// 						{
// 							new_data(temp_it->name,strlen(temp_string)+6);
// 							strcpy(temp_it->name,temp_string);
// 							strcat(temp_it->name,"(avg)");
// 							t->avg_it2=temp_it;
// 						}
// 					for (auto t=task_f32.begin();(t!=task_f32.end()) && (temp_it->name==NULL);t++)
// 						if (strcmp(t->data_name,temp_string)==0)
// 						{
// 							new_data(temp_it->name,strlen(temp_string)+6);
// 							strcpy(temp_it->name,temp_string);
// 							strcat(temp_it->name,"(avg)");
// 							t->avg_it2=temp_it;
// 						}
// 					for (auto t=task_f64.begin();(t!=task_f64.end()) && (temp_it->name==NULL);t++)
// 						if (strcmp(t->data_name,temp_string)==0)
// 						{
// 							new_data(temp_it->name,strlen(temp_string)+6);
// 							strcpy(temp_it->name,temp_string);
// 							strcat(temp_it->name,"(avg)");
// 							t->avg_it2=temp_it;
// 						}
// 				}
// 			}
// 			for (int i=0;i<4*temp_it->n;i++)
// 				fscanf(cfg_file,"%s\n",temp_string);
// 			while ((fscanf(cfg_file,"%s",temp_string)==1) && (fseek(cfg_file,-strlen(temp_string),SEEK_CUR)==0) && (temp_string[0]=='m'))
// 			{
// 				fscanf(cfg_file,"mapping_f_name=%s\n",temp_string);
// 				if (strcmp(temp_string,"seq_mapping")==0)
// 					for (int i=0;i<temp_it->n;i++)
// 						fscanf(cfg_file,"%s\n",temp_string);
// 				if (strcmp(temp_string,"fission_mapping")==0)
// 				{
// 					fscanf(cfg_file,"%s\n",temp_string);
// 					fscanf(cfg_file,"%s\n",temp_string);
// 				}
// 				if (strcmp(temp_string,"linear_mapping")==0){}
// 				if (strcmp(temp_string,"pert_mapping")==0)
// 					for (int i=0;i<temp_it->n;i++)
// 						fscanf(cfg_file,"%s\n",temp_string);
// 			}
// 			for (auto rel=temp_it->related_iterator_vec.begin();rel!=temp_it->related_iterator_vec.end();rel++)
// 				rel->son_it=read_iterator(cfg_file,it_list);
// 			return temp_it;
// 		}
// 		else
// 		{
// 			hyper_iterator_c *temp_it=new_data<hyper_iterator_c>(temp_n);
// 			it_list[temp_p]=temp_it;
// 			fscanf(cfg_file,"%s",temp_string);
// 			fseek(cfg_file,-strlen(temp_string),SEEK_CUR);
// 			if (temp_string[0]=='n')
// 			{
// 				temp_it->base_iterator=true;
// 				fscanf(cfg_file,"name=%s\n",temp_string);
// 				for (auto t=task_i32.begin();(t!=task_i32.end()) && (temp_it->name==NULL);t++)
// 					if (strcmp(t->data_name,temp_string)==0)
// 					{
// 						new_data(temp_it->name,strlen(temp_string)+1);
// 						strcpy(temp_it->name,temp_string);
// 						t->it2=temp_it;
// 					}
// 				for (auto t=task_f32.begin();(t!=task_f32.end()) && (temp_it->name==NULL);t++)
// 					if (strcmp(t->data_name,temp_string)==0)
// 					{
// 						new_data(temp_it->name,strlen(temp_string)+1);
// 						strcpy(temp_it->name,temp_string);
// 						t->it2=temp_it;
// 					}
// 				for (auto t=task_f64.begin();(t!=task_f64.end()) && (temp_it->name==NULL);t++)
// 					if (strcmp(t->data_name,temp_string)==0)
// 					{
// 						new_data(temp_it->name,strlen(temp_string)+1);
// 						strcpy(temp_it->name,temp_string);
// 						t->it2=temp_it;
// 					}
// 				if (strcmp(temp_string+strlen(temp_string)-5,"(avg)")==0)
// 				{
// 					temp_string[strlen(temp_string)-5]=0;
// 					for (auto t=task_i32.begin();(t!=task_i32.end()) && (temp_it->name==NULL);t++)
// 						if (strcmp(t->data_name,temp_string)==0)
// 						{
// 							new_data(temp_it->name,strlen(temp_string)+6);
// 							strcpy(temp_it->name,temp_string);
// 							strcat(temp_it->name,"(avg)");
// 							t->avg_it2=temp_it;
// 						}
// 					for (auto t=task_f32.begin();(t!=task_f32.end()) && (temp_it->name==NULL);t++)
// 						if (strcmp(t->data_name,temp_string)==0)
// 						{
// 							new_data(temp_it->name,strlen(temp_string)+6);
// 							strcpy(temp_it->name,temp_string);
// 							strcat(temp_it->name,"(avg)");
// 							t->avg_it2=temp_it;
// 						}
// 					for (auto t=task_f64.begin();(t!=task_f64.end()) && (temp_it->name==NULL);t++)
// 						if (strcmp(t->data_name,temp_string)==0)
// 						{
// 							new_data(temp_it->name,strlen(temp_string)+6);
// 							strcpy(temp_it->name,temp_string);
// 							strcat(temp_it->name,"(avg)");
// 							t->avg_it2=temp_it;
// 						}
// 				}
// 			}
// 			fscanf(cfg_file,"mn=");
// 			for (int did=0;did<temp_it->n;did++)
// 				fscanf(cfg_file,"%lld",temp_it->mn+did);
// 			fscanf(cfg_file,"\nmx=");
// 			for (int did=0;did<temp_it->n;did++)
// 				fscanf(cfg_file,"%lld",temp_it->mx+did);
// 			fscanf(cfg_file,"\ngap=");
// 			for (int did=0;did<temp_it->n;did++)
// 				fscanf(cfg_file,"%lld",temp_it->gap+did);
// 			fscanf(cfg_file,"\nweight=");
// 			for (int did=0;did<temp_it->n;did++)
// 				fscanf(cfg_file,"%lld",temp_it->weight+did);
// 			while ((fscanf(cfg_file,"%s",temp_string)==1) && (fseek(cfg_file,-strlen(temp_string),SEEK_CUR)==0) && (temp_string[0]=='m'))
// 			{
// 				fscanf(cfg_file,"mapping_f_name=%s\n",temp_string);
// 				if (strcmp(temp_string,"seq_mapping")==0)
// 				{
// 					temp_it->append_related_iterator_seq(NULL);
// 					fscanf(cfg_file,"dim_seq=");
// 					for (int did=0;did<temp_it->n;did++)
// 						fscanf(cfg_file,"%d",temp_it->related_iterator_vec.rbegin()->dim_seq+did);
// 				}
// 				if (strcmp(temp_string,"fission_mapping")==0)
// 				{
// 					temp_it->append_related_iterator_fission(NULL);
// 					fscanf(cfg_file,"dim_fission_l=%d\n",&(temp_it->related_iterator_vec.rbegin()->dim_fission_l));
// 					fscanf(cfg_file,"dim_fission_r=%d\n",&(temp_it->related_iterator_vec.rbegin()->dim_fission_r));
// 				}
// 				if (strcmp(temp_string,"linear_mapping")==0)
// 				{
// 					temp_it->append_related_iterator_seq(NULL);
// 				}
// 				if (strcmp(temp_string,"pert_mapping")==0)
// 				{
// 					temp_it->append_related_iterator_pert(NULL);
// 					fscanf(cfg_file,"pert=");
// 					for (int did=0;did<temp_it->n;did++)
// 						fscanf(cfg_file,"%lld",temp_it->related_iterator_vec.rbegin()->pert+did);
// 				}
// 			}
// 			for (auto rel=temp_it->related_iterator_vec.begin();rel!=temp_it->related_iterator_vec.end();rel++)
// 				rel->son_it=read_iterator(cfg_file,it_list);
// 			return temp_it;
// 		}*/
// 	}
// }



// #endif