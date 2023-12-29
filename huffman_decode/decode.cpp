#ifndef __DECODE_CPP__
#define __DECODE_CPP__

#include "huffman_decode.hpp2"

namespace cliz
{
    template<typename T>
    void task_c<T>::decode()
    {
        printf("%lld %lld\n",bitstream_index,bitstream_length);
        huffman_tree_c<T> &this_huffman=huffman[0];
        unordered_map<int,node_c,simple_hash> &this_nodes=this_huffman.nodes;
        align_cache<unsigned char>();
        int cache_digit=0;
        int nid=32767+this_nodes.size()/2;
        unsigned char cache=read_cache<unsigned char>();
        //printf("cache=%d\n",cache);
        for (long long i=0;i<data_num;)
        {
            if (cache_digit==8)
            {
                read_cache(cache);
                //printf("cache=%d\n",cache);
                //getchar();
                cache_digit=0;
            }
            while ((nid>=32768) && (cache_digit<8))
            {
                //printf("nid=%d, cache_digit=%d\n",nid,cache_digit);
                if ((cache>>(7-cache_digit))&1)
                    nid=this_nodes[nid].lson;
                else
                    nid=this_nodes[nid].rson;
                cache_digit++;
                //getchar();
            }
            if (nid<32768)
            {
                quant_bin[i]=nid;
                //printf("i=%lld, quant_bin[i]=%d\n",i,quant_bin[i]);
                //getchar();
                nid=32767+this_nodes.size()/2;
                i++;
            }
        }
        printf("%lld %lld\n",bitstream_index,bitstream_length);
    }
}

#endif