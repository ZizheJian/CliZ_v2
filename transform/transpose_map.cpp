#ifndef __TRANSPOSE_MAP_CPP__
#define __TRANSPOSE_MAP_CPP__

#include "transform.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::transpose_map(long long *pos2horiz_mapping_backup)
	{
		if (it2->n==1)
			transpose_map_1D(pos2horiz_mapping_backup);
		if (it2->n==2)
			transpose_map_2D(pos2horiz_mapping_backup);
		if (it2->n==3)
			transpose_map_3D(pos2horiz_mapping_backup);
		if (it2->n==4)
			transpose_map_4D(pos2horiz_mapping_backup);
	}
}

#endif