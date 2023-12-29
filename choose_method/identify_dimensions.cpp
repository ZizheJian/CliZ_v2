#ifndef __IDENTIFY_DIMENSIONS_CPP__
#define __IDENTIFY_DIMENSIONS_CPP__

#include "choose_method.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::identify_dimensions()
	{
		for (int i=0;i<dimension_num;i++)
		{
			if ((dimension_type[i]!=NULL) && (strcmp(dimension_type[i],"lat")==0))
				latid=i;
			if ((dimension_type[i]!=NULL) && (strcmp(dimension_type[i],"lng")==0))
				lngid=i;
			if ((dimension_type[i]!=NULL) && (strcmp(dimension_type[i],"h")==0))
				hid=i;
			if ((dimension_type[i]!=NULL) && (strcmp(dimension_type[i],"t")==0))
				tid=i;
		}
		if (mask_file_path!=NULL)
			if ((latid<0) || (lngid<0))
			{
				printf("Error: Lacking necessary dimensions for mask file.\n");
				exit(0);
			}
	}
}

#endif