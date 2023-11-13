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

	void delete_data(hyper_iterator_c *&r,bool recursive=true)
	{
		// if ((r!=NULL) && (!r->base_iterator))
		// {
		// 	r->delete_iterator(recursive);
		// 	delete r;
		// }
		// r=NULL;
	}
}

#endif