#ifndef __INIT_IT2_CPP__
#define __INIT_IT2_CPP__

#include "init.hpp2"

namespace cliz
{
	template<typename T>
	void init_it(task_c<T> &task)
	{
		new_data(task.it1,task.dimension_num);
		new_data(task.it2,task.dimension_num);
		memcpy(task.it1->mx,task.dimension,task.dimension_num*sizeof(long long));
		for (int did=task.dimension_num-1;did>=0;did--)
			if (did==task.dimension_num-1)
				task.it1->weight[did]=1;
			else
				task.it1->weight[did]=task.it1->weight[did+1]*task.it1->mx[did+1];
		memcpy(task.it2->mx,task.dimension,task.dimension_num*sizeof(long long));
		for (int did=task.dimension_num-1;did>=0;did--)
			if (did==task.dimension_num-1)
				task.it2->weight[did]=1;
			else
				task.it2->weight[did]=task.it2->weight[did+1]*task.it2->mx[did+1];
	}
}

#endif