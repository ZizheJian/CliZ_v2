#ifndef __COMPRESS_CPP__
#define __COMPRESS_CPP__

#include "compress.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::compress()
	{
		new_data(quant_bin,data_num);
		auto timer=new timer_c();
		timer->start();
		call_DC_functions();
		timer->pause();
		timer->write();
	}
}

#endif