#ifndef __TRANSPOSE_DATA_MAP_CPP__
#define __TRANSPOSE_DATA_MAP_CPP__

#include "transform.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::transpose_data_map(T *data_backup,long long *pos2horiz_mapping_backup)
	{
		if (it2->n==1)
			transpose_data_map_1D(data_backup,pos2horiz_mapping_backup);
		if (it2->n==2)
			transpose_data_map_2D(data_backup,pos2horiz_mapping_backup);
		if (it2->n==3)
			transpose_data_map_3D(data_backup,pos2horiz_mapping_backup);
		if (it2->n==4)
			transpose_data_map_4D(data_backup,pos2horiz_mapping_backup);
	}
}

#endif