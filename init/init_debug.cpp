#ifndef __INIT_DEBUG_CPP__
#define __INIT_DEBUG_CPP__

#include "init.hpp2"

namespace cliz
{
	void check_debug(task_c<float> &task_f32){}

	void read_debug_command(task_c<float> &task_f32,int argc,char **argv,int &i)
	{
		task_f32.debug=true;
		std::filesystem::create_directory("result");
	}
}

#endif