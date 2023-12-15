#ifndef __INIT_CPP__
#define __INIT_CPP__

#include "init.hpp2"

namespace cliz
{
	void init(task_c<int> &task_i32,task_c<float> &task_f32,task_c<double> &task_f64,int argc,char **argv)
	{
		read_command(task_f32,argc,argv);
		check(task_i32,task_f32,task_f64);
		if ((task_f32.cfg_file_mode!=NULL) && (strcmp(task_f32.cfg_file_mode,"use")==0))
			read_cfg(task_f32);
		if (strcmp(task_f32.data_type,"i32")==0)
			move_task(task_i32,task_f32);
		if (strcmp(task_f32.data_type,"f64")==0)
			move_task(task_f64,task_f32);
		if (task_i32.in_file_path!=NULL)
		{
			if (task_i32.best_it1==NULL)
				init_it(task_i32);
			print_detail(task_i32);
		}
		if (task_f32.in_file_path!=NULL)
		{
			if (task_f32.best_it1==NULL)
				init_it(task_f32);
			print_detail(task_f32);
		}
		if (task_f64.in_file_path!=NULL)
		{
			if (task_f64.best_it1==NULL)
				init_it(task_f64);
			print_detail(task_f64);
		}
	}

	void read_command(task_c<float> &task_f32,int argc,char **argv)
	{
		for (int i=1;i<argc;i++)
		{
			if (strcmp(argv[i],"-in")==0)
			{
				read_in_file_command(task_f32,argc,argv,i);
				continue;
			}
			if (strcmp(argv[i],"-out")==0)
			{
				read_out_file_command(task_f32,argc,argv,i);
				continue;
			}
			if ((strcmp(argv[i],"-set-cfg")==0) || (strcmp(argv[i],"-use-cfg")==0))
			{
				read_cfg_file_command(task_f32,argc,argv,i);
				continue;
			}
			if ((strcmp(argv[i],"-set-map")==0) || (strcmp(argv[i],"-force-set-map")==0) || (strcmp(argv[i],"-use-map")==0) || (strcmp(argv[i],"-force-use-map")==0))
			{
				read_map_file_command(task_f32,argc,argv,i);
				continue;
			}
			if (strcmp(argv[i],"-mask")==0)
			{
				read_mask_file_command(task_f32,argc,argv,i);
				continue;
			}
			if (strcmp(argv[i],"-dim")==0)
			{
				read_dimension_command(task_f32,argc,argv,i);
				continue;
			}
			if (strcmp(argv[i],"-type")==0)
			{
				read_type_command(task_f32,argc,argv,i);
				continue;
			}
			if (strcmp(argv[i],"-err")==0)
			{
				read_err_command(task_f32,argc,argv,i);
				continue;
			}
			if (strcmp(argv[i],"-debug")==0)
			{
				read_debug_command(task_f32,argc,argv,i);
				continue;
			}
			printf("Error: Undefined instructions\n");
			exit(0);
		}
	}

	void check(task_c<int> &task_i32,task_c<float> &task_f32,task_c<double> &task_f64)
	{
		check_in_file(task_f32);
		check_out_file(task_f32);
		check_cfg_file(task_f32);
		check_map_file(task_f32);
		check_mask_file(task_f32);
		check_dimension(task_f32);
		check_err_bound(task_f32);
		check_debug(task_f32);
		check_type(task_f32);
	}
}

#endif