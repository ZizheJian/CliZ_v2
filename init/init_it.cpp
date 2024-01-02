#ifndef __INIT_IT_CPP__
#define __INIT_IT_CPP__

#include "init.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::init_it()
	{
		new_data(it1,dimension_num);
		new_data(it2,dimension_num);
		memcpy(it1->mx,dimension,dimension_num*sizeof(long long));
		for (int did=dimension_num-1;did>=0;did--)
			if (did==dimension_num-1)
				it1->weight[did]=1;
			else
				it1->weight[did]=it1->weight[did+1]*it1->mx[did+1];
		memcpy(it2->mx,dimension,dimension_num*sizeof(long long));
		for (int did=dimension_num-1;did>=0;did--)
			if (did==dimension_num-1)
				it2->weight[did]=1;
			else
				it2->weight[did]=it2->weight[did+1]*it2->mx[did+1];
	}
}

#endif