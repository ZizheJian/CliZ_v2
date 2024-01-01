#ifndef __INIT_DIMENSION_CPP__
#define __INIT_DIMENSION_CPP__

#include "init.hpp2"

namespace cliz
{
	void read_dimension_command(task_c<float> &task_f32,int argc,char **argv,int &i)
	{
		if (task_f32.dimension_num!=0)
		{
			printf("Error: Dimension redefined.\n");
			exit(0);
		}
		vector<int> vec1;
		vector<char*> vec2;
		for (i++;(i<argc) && (argv[i][0]!='-');i++)
		{
			vec1.push_back(0);
			int weight=1;
			int type_len=0;
			for (int k=strlen(argv[i])-1;k>=0;k--)
				if ((argv[i][k]>='0') && (argv[i][k]<='9'))
				{
					vec1.back()+=(argv[i][k]-'0')*weight;
					weight*=10;
				}
				else
				{
					type_len=k+1;
					break;
				}
			if (type_len==0)
				vec2.push_back(NULL);
			else
			{
				vec2.push_back(new_data<char>(type_len+1));
				strncpy(vec2.back(),argv[i],type_len);
				vec2.back()[type_len]=0;
			}
		}
		task_f32.dimension_num=vec1.size();
		new_data(task_f32.dimension,task_f32.dimension_num);
		for (int j=0;j<task_f32.dimension_num;j++)
			task_f32.dimension[j]=vec1[j];
		new_data(task_f32.dimension_type,task_f32.dimension_num);
		for (int j=0;j<task_f32.dimension_num;j++)
			task_f32.dimension_type[j]=vec2[j];
		i--;
	}

	void check_dimension(task_c<float> &task_f32)
	{
		#if defined(JOB_TYPE_COMPRESS) || defined(JOB_TYPE_DECOMPRESS)
			if ((task_f32.dimension==NULL) && ((task_f32.cfg_file_mode==NULL) || (strcmp(task_f32.cfg_file_mode,"set")==0)))
			{
				printf("Error: Dimension missing.\n");
				exit(0);
			}
		#endif
		if (task_f32.dimension==NULL)
			return;
		task_f32.data_num=1;
		for (int i=0;i<task_f32.dimension_num;i++)
		{
			if (task_f32.dimension[i]<=0)
			{
				printf("Error: Dimension must be positive integers.\n");
				exit(0);
			}
			if (task_f32.dimension_type[i]!=NULL)
			{
				int appear=0;
				for (int j=0;j<sizeof(supported_dimension_type)/sizeof(char*);j++)
					if (strcmp(task_f32.dimension_type[i],supported_dimension_type[j])==0)
						appear++;
				if (appear==0)
				{
					printf("Error: Invalid dimension.\n");
					exit(0);
				}
			}
			task_f32.data_num*=task_f32.dimension[i];
		}
		for (int i=0;i<sizeof(supported_dimension_type)/sizeof(char*);i++)
		{
			int appear=0;
			for (int j=0;j<task_f32.dimension_num;j++)
				if ((task_f32.dimension_type[j]!=NULL) && (strcmp(supported_dimension_type[i],task_f32.dimension_type[j])==0))
					appear++;
			if (appear>1)
			{
				printf("Error: Invalid dimension\n");
				exit(0);
			}
		}
	}

	void deduce_data_num(task_c<float> &task_f32)
	{
		if (task_f32.dimension==NULL)
		{
			task_f32.dimension_num=1;
			new_data(task_f32.dimension,1);
			new_data(task_f32.dimension_type,1,true);
			task_f32.src_file=fopen(task_f32.src_file_path,"rb");
			fseek(task_f32.src_file,0,SEEK_END);
			task_f32.dimension[0]=ftell(task_f32.src_file);
			if ((strcmp(task_f32.data_type,"i32")==0) || (strcmp(task_f32.data_type,"f32")==0))
				task_f32.dimension[0]/=4;
			if (strcmp(task_f32.data_type,"f64")==0)
				task_f32.dimension[0]/=8;
			fclose(task_f32.src_file);
			task_f32.data_num=task_f32.dimension[0];
		}
	}
}

#endif