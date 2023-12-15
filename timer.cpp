#ifndef __TIMER_CPP__
#define __TIMER_CPP__

#include "globalvar.hpp"

namespace cliz
{
	void timer_c::start()
	{
		if (state==0)
		{
			state=1;
			auto _st=chrono::time_point_cast<chrono::microseconds>(chrono::high_resolution_clock::now());
			start_time=_st.time_since_epoch().count()*0.000001;
		}
		else
			printf("Warning: Timer receives wrong command\n");
	}

	void timer_c::pause()
	{
		if (state==1)
		{
			auto _et=chrono::time_point_cast<chrono::microseconds>(chrono::high_resolution_clock::now());
			end_time=_et.time_since_epoch().count()*0.000001;
			history.push_back(end_time-start_time);
			state=0;
		}
		else
			printf("Warning: Timer receives wrong command\n");
	}

	void timer_c::reset()
	{
		history.clear();
		state=0;
	}

	void timer_c::write()
	{
		FILE *f=fopen("result/time.txt","a+");
		for (auto i=history.begin();i!=history.end();i++)
			fprintf(f,"%lf ",*i);
		fprintf(f,"\n");
		fclose(f);
	}
}

#endif