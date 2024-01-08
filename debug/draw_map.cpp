#ifndef __DRAW_MAP_CPP__
#define __DRAW_MAP_CPP__

#include "debug.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::draw_map()
	{
		unsigned char *map_graph=new_data<unsigned char>(it2->mx[latid]*it2->mx[lngid]*3,true);
		for (int i0=0;i0<it2->mx[latid];i0++)
			for (int i1=0;i1<it2->mx[lngid];i1++)
			{
				if (shift_map[i0*it2->mx[lngid]+i1]==0)
				{
					map_graph[3*(i0*it2->mx[lngid]+i1)+0]=0;
					map_graph[3*(i0*it2->mx[lngid]+i1)+2]=0;
				}
				else
					if (shift_map[i0*it2->mx[lngid]+i1]==1)
					{
						map_graph[3*(i0*it2->mx[lngid]+i1)+0]=255;
						map_graph[3*(i0*it2->mx[lngid]+i1)+2]=0;
					}
					else
					{
						map_graph[3*(i0*it2->mx[lngid]+i1)+0]=0;
						map_graph[3*(i0*it2->mx[lngid]+i1)+2]=255;
					}
				if (width_map[i0*it2->mx[lngid]+i1]==0)
					map_graph[3*(i0*it2->mx[lngid]+i1)+1]=0;
				else
					map_graph[3*(i0*it2->mx[lngid]+i1)+1]=255;
			}
		char *png_file_path=new char[FILE_NAME_LENGTH];
		FILE *png_file=NULL;
		for (int i=0;i<=65536;i++)
		{
			if (i==65536)
			{
				printf("Error: Too many map images already exist.\n");
				exit(0);
			}
			sprintf(png_file_path,"result/map(%d).png",i);
			png_file=fopen(png_file_path,"r");
			if (png_file==NULL)
			{
				png_file=fopen(png_file_path,"w");
				break;
			}
			fclose(png_file);
		}
		png::output_png(png_file,it2->mx[lngid],it2->mx[latid],map_graph);
		fclose(png_file);
		delete_data(map_graph);
	}
}

#endif