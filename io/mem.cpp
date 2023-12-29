#ifndef __MEM_CPP__
#define __MEM_CPP__

#include "io.hpp2"

namespace cliz
{
	template<typename T>
	T *new_data(long long num,bool memclear=false)
	{
		T *r=new T[num];
		if (memclear)
			memset(r,0,sizeof(T)*num);
		return r;
	}

	template<>
	hyper_iterator_c *new_data(long long num,bool memclear)
	{
		// hyper_iterator_c *r=new hyper_iterator_c(num);
		// return r;
		printf("Error: new_data incomplete.\n");
		exit(0);
	}

	template<typename T>
	void new_data(T *&r,long long num,bool memclear=false,bool reuse_check=true)
	{
		if ((r!=NULL) && (reuse_check))
		{
			printf("Warning: Reusing array pointer.\n");
			return;
		}
		r=new T[num];
		if (memclear)
			memset(r,0,sizeof(T)*num);
	}

	template<>
	void new_data(hyper_iterator_c *&r,long long num,bool memclear,bool reuse_check)
	{
		if ((r!=NULL) && (reuse_check))
		{
			printf("Warning: Reusing hyper iterator pointer.\n");
			return;
		}
		r=new hyper_iterator_c(num);
	}

	//释放原始数据占用的空间
	template<typename T>
	void delete_data(T *&r)
	{
		if (r!=NULL)
			delete[] r;
		r=NULL;
	}

	template<>
	void delete_data(hyper_iterator_c *&r)
	{
		if (r!=NULL)
		{
			r->delete_iterator();
			delete r;
		}
		r=NULL;
	}

	template<typename T1>
	template<typename T2>
	void task_c<T1>::align_cache()
	{
		#ifdef JOB_TYPE_COMPRESS
			if (bitstream_length%sizeof(T2)==0)
				return;
			long long zeros=sizeof(T2)-bitstream_length%sizeof(T2);
			memset(bitstream+bitstream_length,0,zeros);
			bitstream_length+=zeros;
		#endif
		#ifdef JOB_TYPE_DECOMPRESS
			if (bitstream_index%sizeof(T2)==0)
				return;
			bitstream_index+=sizeof(T2)-bitstream_index%sizeof(T2);
		#endif
	}

	template<typename T1>
	template<typename T2>
	void task_c<T1>::append_cache(T2 x)
	{
		*(reinterpret_cast<T2*>(bitstream+bitstream_length))=x;
	    bitstream_length+=sizeof(T2);
	}

	template<typename T1>
	template<typename T2>
	void task_c<T1>::read_cache(T2 &x)
	{
		x=*(reinterpret_cast<T2*>(bitstream+bitstream_index));
	    bitstream_index+=sizeof(T2);
	}

	template<typename T1>
	template<typename T2>
	T2 task_c<T1>::read_cache()
	{
		T2 x=*(reinterpret_cast<T2*>(bitstream+bitstream_index));
	    bitstream_index+=sizeof(T2);
		return x;
	}
}

#endif