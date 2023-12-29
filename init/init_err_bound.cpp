#ifndef __INIT_ERR_BOUND_CPP__
#define __INIT_ERR_BOUND_CPP__

#include "init.hpp2"

namespace cliz
{
	void read_err_command(task_c<float> &task_f32,int argc,char **argv,int &i)
	{
		if (task_f32.err_type!=NULL)
		{
			printf("Error: Error bound redefined.\n");
			exit(0);
		}
		i++;
		if (i>=argc)
		{
			printf("Error: Error bound missing.\n");
			exit(0);
		}
		for (int j=0;j<strlen(argv[i]);j++)
			if ((argv[i][j]<'A') || (argv[i][j]>'Z'))
			{
				if (j==0)
				{
					new_data(task_f32.err_type,4);
					strcpy(task_f32.err_type,"ABS");
				}
				else
				{
					new_data(task_f32.err_type,j+1);
					strncpy(task_f32.err_type,argv[i],j);
					task_f32.err_type[j]=0;
				}
				task_f32.raw_err_bound=stod(argv[i]+j);
				break;
			}
	}

	void check_err_bound(task_c<float> &task_f32)
	{
		if ((task_f32.err_type==NULL) && ((task_f32.cfg_file_mode==NULL) || (strcmp(task_f32.cfg_file_mode,"set")==0)))
		{
			new_data(task_f32.err_type,4);
			strcpy(task_f32.err_type,"ABS");
			task_f32.raw_err_bound=0;
			return;
		}
		if (task_f32.err_type==NULL)
			return;
		if (task_f32.raw_err_bound<0)
		{
			printf("Error: error bound must be non-negative.\n");
			exit(0);
		}
		bool supported=false;
		for (int j=0;j<sizeof(supported_err_type)/sizeof(char*);j++)
			if (strcmp(task_f32.err_type,supported_err_type[j])==0)
				supported=true;
		if (!supported)
		{
			printf("Error: Unsupported error bound.\n");
			exit(0);
		}
	}
}

#endif