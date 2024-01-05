#ifndef __WRITE_QUNAT_BIN_FREQ_CPP__
#define __WRITE_QUNAT_BIN_FREQ_CPP__

#include "debug.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::write_quant_bin_freq(int num)
	{
		char *freq_file_path=new char[FILE_NAME_LENGTH];
		FILE *freq_file=NULL;
		for (int i=0;i<=65536;i++)
		{
			if (i==65536)
			{
				printf("Error: Too many frequency files already exist.\n");
				exit(0);
			}
			sprintf(freq_file_path,"result/freq(%d).txt",i);
			freq_file=fopen(freq_file_path,"r");
			if (freq_file==NULL)
			{
				freq_file=fopen(freq_file_path,"w");
				break;
			}
			fclose(freq_file);
		}
		for (int i=-32768;i<32768;i++)
		{
			for (int j=0;j<num;j++)
			{
				auto this_huffman=huffman[j];
				auto this_nodes=this_huffman.nodes;
				auto it=this_nodes.find(i);
				if (it!=this_nodes.end())
					fprintf(freq_file,"%lld ",it->second.count);
				else
					fprintf(freq_file,"0 ");
			}
			fprintf(freq_file,"\n");
		}
		fclose(freq_file);
	}
}

#endif