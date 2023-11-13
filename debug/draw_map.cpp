#ifndef __DRAW_MAP_CPP__
#define __DRAW_MAP_CPP__

#include "debug.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::draw_map(int lngid,int latid)
	{
		/*unsigned char *map_graph=new_data<unsigned char>(it2->mx[latid]*it2->mx[lngid]*3,true);
		long long *count=new_data<long long>(6,true);
		for (int i0=0;i0<it2->mx[latid];i0++)
			for (int i1=0;i1<it2->mx[lngid];i1++)
			{
				count[map[i0*it2->mx[lngid]+i1]]++;
				int pid=map[i0*it2->mx[lngid]+i1]/3;
				int sid=map[i0*it2->mx[lngid]+i1]%3-1;
				if (sid==0)
				{
					map_graph[3*(i0*it2->mx[lngid]+i1)+0]=0;
					map_graph[3*(i0*it2->mx[lngid]+i1)+2]=0;
				}
				else
					if (sid>0)
					{
						map_graph[3*(i0*it2->mx[lngid]+i1)+0]=255;
						map_graph[3*(i0*it2->mx[lngid]+i1)+2]=0;
					}
					else
					{
						map_graph[3*(i0*it2->mx[lngid]+i1)+0]=0;
						map_graph[3*(i0*it2->mx[lngid]+i1)+2]=255;
					}
				if (pid>0)
					map_graph[3*(i0*it2->mx[lngid]+i1)+1]=255;
				else
					map_graph[3*(i0*it2->mx[lngid]+i1)+1]=0;
			}
		FILE *f_map=fopen("result/map.png","wb");
		png::output_png(f_map,it2->mx[lngid],it2->mx[latid],map_graph);
		fclose(f_map);
		delete_data(map_graph);
		for (int i=0;i<6;i++)
			printf("%lld ",count[i]);
		printf("\n");*/
	}
}

#endif