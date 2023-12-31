#define JOB_TYPE_COMPRESS
#define JOB_TYPE_ID 0

#include "init/init.hpp1"
#include "change_err_bound/change_err_bound.hpp1"
#include "choose_method/choose_method.hpp1"
#include "compress/compress.hpp1"

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
		task_i32.change_err_bound();
		task_i32.choose_method();
		task_i32.call_compress_functions();
	}
	if (task_f32.in_file_path!=NULL)
	{
		task_f32.identify_dimensions();
		task_f32.change_err_bound();
		task_f32.choose_method();
		task_f32.call_compress_functions();
	}
	if (task_f64.in_file_path!=NULL)
	{
		task_f64.identify_dimensions();
		task_f64.change_err_bound();
		task_f64.choose_method();
		task_f64.call_compress_functions();
	}
	//TODO：移植zstd
}