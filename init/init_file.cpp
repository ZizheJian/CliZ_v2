#ifndef __INIT_FILE_CPP__
#define __INIT_FILE_CPP__

#include "init.hpp2"

namespace cliz
{
	void read_in_file_command(task_c<float> &task_f32,int argc,char **argv,int &i)
	{
		if (task_f32.in_file_path!=NULL)
		{
			printf("Error: Input file redefined.\n");
			exit(0);
		}
		i++;
		if (i>=argc)
		{
			printf("Error: Input file path missing.\n");
			exit(0);
		}
		new_data(task_f32.in_file_path,strlen(argv[i])+1);
		strcpy(task_f32.in_file_path,argv[i]);
	}

	void read_out_file_command(task_c<float> &task_f32,int argc,char **argv,int &i)
	{
		if (task_f32.out_file_path!=NULL)
		{
			printf("Error: Output file redefined.\n");
			exit(0);
		}
		i++;
		if (i>=argc)
		{
			printf("Error: Output file path missing.\n");
			exit(0);
		}
		new_data(task_f32.out_file_path,strlen(argv[i])+1);
		strcpy(task_f32.out_file_path,argv[i]);
	}

	void read_cfg_file_command(task_c<float> &task_f32,int argc,char **argv,int &i)
	{
		if (task_f32.cfg_file_path!=NULL)
		{
			printf("Error: Configuration file redefined.\n");
			exit(0);
		}
		new_data(task_f32.cfg_file_mode,strlen(argv[i])-4);
		strncpy(task_f32.cfg_file_mode,argv[i]+1,strlen(argv[i])-5);
		i++;
		if (i>=argc)
		{
			printf("Error: Configuration file path missing.\n");
			exit(0);
		}
		new_data(task_f32.cfg_file_path,strlen(argv[i])+1);
		strcpy(task_f32.cfg_file_path,argv[i]);
	}

	void read_map_file_command(task_c<float> &task_f32,int argc,char **argv,int &i)
	{
		if (task_f32.map_file_path!=NULL)
		{
			printf("Error: Map file redefined.\n");
			exit(0);
		}
		new_data(task_f32.map_file_mode,strlen(argv[i])-4);
		strncpy(task_f32.map_file_mode,argv[i]+1,strlen(argv[i])-5);
		i++;
		if (i>=argc)
		{
			printf("Error: Map file path missing.\n");
			exit(0);
		}
		new_data(task_f32.map_file_path,strlen(argv[i])+1);
		strcpy(task_f32.map_file_path,argv[i]);
	}

	void read_mask_file_command(task_c<float> &task_f32,int argc,char **argv,int &i)
	{
		if (task_f32.mask_file_path!=NULL)
		{
			printf("Error: Mask file redefined.\n");
			exit(0);
		}
		i++;
		if (i>=argc)
		{
			printf("Error: Mask file path missing.\n");
			exit(0);
		}
		new_data(task_f32.mask_file_path,strlen(argv[i])+1);
		strcpy(task_f32.mask_file_path,argv[i]);
	}

	void check_in_file(task_c<float> &task_f32)
	{
		for (int i=strlen(task_f32.in_file_path)-1;i>=0;i--)
			if (task_f32.in_file_path[i]=='/')
			{
				new_data(task_f32.data_name,strlen(task_f32.in_file_path)-i);
				strcpy(task_f32.data_name,task_f32.in_file_path+i+1);
				break;
			}
	}

	void check_out_file(task_c<float> &task_f32)
	{
		if (task_f32.out_file_path==NULL)
		{
			#ifdef JOB_TYPE_COMPRESS
				new_data(task_f32.out_file_path,strlen(task_f32.in_file_path)+6);
				strcpy(task_f32.out_file_path,task_f32.in_file_path);
				strcat(task_f32.out_file_path,".cliz");
			#endif
			#ifdef JOB_TYPE_DECOMPRESS
				new_data(task_f32.out_file_path,strlen(task_f32.in_file_path)+5);
				strcpy(task_f32.out_file_path,task_f32.in_file_path);
				strcat(task_f32.out_file_path,".bin");
			#endif
		}
	}

	void check_cfg_file(task_c<float> &task_f32){}

	void check_map_file(task_c<float> &task_f32){}

	void check_mask_file(task_c<float> &task_f32){}
}

#endif