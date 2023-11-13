#ifndef __DRAW_QUANT_BIN_CPP__
#define __DRAW_QUANT_BIN_CPP__

#include "debug.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::draw_quant_bin(int lngid,int latid)
	{
		/*hyper_iterator_c *graph_it=new_data<hyper_iterator_c>(dimension_num);
		graph_it->append_related_iterator_seq(it2);
		for (int did=0,djd=0;did<dimension_num;did++)
		{
			if (did==dimension_num-2)
				graph_it->related_iterator_vec[0].dim_seq[did]=latid;
			if (did==dimension_num-1)
				graph_it->related_iterator_vec[0].dim_seq[did]=lngid;
			if ((did!=dimension_num-2) && (did!=dimension_num-1))
			{
				while ((djd==latid) || (djd==lngid))
					djd++;
				graph_it->related_iterator_vec[0].dim_seq[did]=djd;
				djd++;
			}
		}
		for (int did=dimension_num-1;did>=0;did--)
		{
			graph_it->mn[did]=it2->mn[graph_it->related_iterator_vec[0].dim_seq[did]];
			graph_it->mx[did]=it2->mx[graph_it->related_iterator_vec[0].dim_seq[did]];
			graph_it->gap[did]=it2->gap[graph_it->related_iterator_vec[0].dim_seq[did]];
			if (did==dimension_num-1)
				graph_it->weight[did]=1;
			else
				graph_it->weight[did]=graph_it->weight[did+1]*graph_it->mx[did+1];
		}
		unsigned char *quant_bin_graph=new_data<unsigned char>(3*graph_it->mx[dimension_num-2]*graph_it->mx[dimension_num-1],true);
		char *graph_name=new_data<char>(100);
		for (graph_it->begin();graph_it->check_end();graph_it->plus())
		{
			if (quant_bin[it2->pos]==0)
			{
				quant_bin_graph[3*(graph_it->pos%graph_it->weight[dimension_num-3])+0]=255;
				quant_bin_graph[3*(graph_it->pos%graph_it->weight[dimension_num-3])+1]=255;
				quant_bin_graph[3*(graph_it->pos%graph_it->weight[dimension_num-3])+2]=255;
			}
			if (quant_bin[it2->pos]>0)
			{
				quant_bin_graph[3*(graph_it->pos%graph_it->weight[dimension_num-3])+0]=255-255*floor(log(quant_bin[it2->pos]))/15;
				quant_bin_graph[3*(graph_it->pos%graph_it->weight[dimension_num-3])+1]=64-64*floor(log(quant_bin[it2->pos]))/15;
				quant_bin_graph[3*(graph_it->pos%graph_it->weight[dimension_num-3])+2]=64-64*floor(log(quant_bin[it2->pos]))/15;
			}
			if (quant_bin[it2->pos]<0)
			{
				quant_bin_graph[3*(graph_it->pos%graph_it->weight[dimension_num-3])+0]=64-64*floor(log(-quant_bin[it2->pos]))/15;
				quant_bin_graph[3*(graph_it->pos%graph_it->weight[dimension_num-3])+1]=64-64*floor(log(-quant_bin[it2->pos]))/15;
				quant_bin_graph[3*(graph_it->pos%graph_it->weight[dimension_num-3])+2]=255-255*floor(log(-quant_bin[it2->pos]))/15;
			}
			if ((graph_it->current[dimension_num-2]==graph_it->mx[dimension_num-2]-1) && (graph_it->current[dimension_num-1]==graph_it->mx[dimension_num-1]-1))
			{
				
				sprintf(graph_name,"result/bin%lld.png",graph_it->current[dimension_num-3]);
				FILE *f_bin=fopen(graph_name,"wb");
				png::output_png(f_bin,graph_it->mx[dimension_num-1],graph_it->mx[dimension_num-2],quant_bin_graph);
				fclose(f_bin);
			}
		}
		delete_data(graph_it);
		delete_data(quant_bin_graph);
		delete_data(graph_name);*/
	}
}



#endif