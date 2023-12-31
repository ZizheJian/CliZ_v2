#define JOB_TYPE_DECOMPRESS
#define JOB_TYPE_ID 1

#include "init/init.hpp1"
#include "change_err_bound/change_err_bound.hpp1"
#include "choose_method/choose_method.hpp1"
#include "decompress/decompress.hpp1"

using namespace cliz;

int main(int argc,char **argv)
{
	task_c<int> task_i32;
	task_c<float> task_f32;
	task_c<double> task_f64;
	init(task_i32,task_f32,task_f64,argc,argv);
	if (task_i32.in_file_path!=NULL)
	{
		task_i32.identify_dimensions();
		task_i32.call_decompress_functions();
	}
	if (task_f32.in_file_path!=NULL)
	{
		task_f32.identify_dimensions();
		task_f32.call_decompress_functions();
	}
	if (task_f64.in_file_path!=NULL)
	{
		task_f64.identify_dimensions();
		task_f64.call_decompress_functions();
	}
	//TODO：移植zstd
}