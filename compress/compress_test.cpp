#ifndef __COMPRESS_TEST_CPP__
#define __COMPRESS_TEST_CPP__

#include "compress.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::compress_test()
	{
		if (TEST_ALL)
		{
			hyper_iterator_c *best_it1_backup=NULL;
			copy_iterator(best_it1_backup,best_it1);
			copy_iterator(best_it1,it1);
			char *best_fitting_function_backup=best_fitting_function;
			best_fitting_function=fitting_function;
			T *data_backup=new_data<T>(data_num);
			memcpy(data_backup,data,data_num*sizeof(T));
			compress();
			copy_iterator(best_it1,best_it1_backup);
			best_fitting_function=best_fitting_function_backup;
			delete_data(data);
			data=data_backup;
		}
		else
		{
			hyper_iterator_c *it1_backup=NULL;
			copy_iterator(it1_backup,it1);
			hyper_iterator_c *it2_backup=NULL;
			copy_iterator(it2_backup,it2);
			float r=pow(SAMPLING_RATE,1.0/it2->n)/2;
			for (int did=0;did<it2->n;did++)
				it2->mx[did]=2*ceil(r*it2_backup->mx[did]);
			for (int did=it2->n-1;did>=0;did--)
				if (did==it2->n-1)
					it2->weight[did]=1;
				else
					it2->weight[did]=it2->weight[did+1]*it2->mx[did+1];
			long long *mxm=new long long[it2->n];
			if (it1->dim_seq!=NULL)
				for (int did=0;did<it2->n;did++)
					mxm[did]=it2->mx[it1->dim_seq[did]];
			else
				memcpy(mxm,it2->mx,it2->n*sizeof(long long));
			if (it1->dim_fission_l!=it1->dim_fission_r)
				for (int did=0;did<it1->n;did++)
				{
					if (did<it1->dim_fission_l)
						it1->mx[did]=mxm[did];
					if (did==it1->dim_fission_l)
					{
						it1->mx[did]=1;
						for (int djd=it1->dim_fission_l;djd<it1->dim_fission_r;djd++)
							it1->mx[did]*=mxm[djd];
					}
					if (did>it1->dim_fission_l)
						it1->mx[did]=mxm[did+it1->dim_fission_r-it1->dim_fission_l-1];
				}
			else
				memcpy(it1->mx,mxm,it1->n*sizeof(long long));
			for (int did=it1->n-1;did>=0;did--)
				if (did==it1->n-1)
					it1->weight[did]=1;
				else
					it1->weight[did]=it1->weight[did+1]*it1->mx[did+1];
			T *data_backup=data;
			long long data_num_backup=data_num;
			data_num=1;
			for (int did=0;did<it2->n;did++)
				data_num*=it2->mx[did];
			new_data(data,data_num,false,false);
			if (it2->n==1)
				collect_data_1D(data_backup,it2_backup);
			if (it2->n==2)
				collect_data_2D(data_backup,it2_backup);
			if (it2->n==3)
				collect_data_3D(data_backup,it2_backup);
			if (it2->n==4)
				collect_data_4D(data_backup,it2_backup);
			hyper_iterator_c *best_it1_backup=NULL;
			copy_iterator(best_it1_backup,best_it1);
			copy_iterator(best_it1,it1);
			char *best_fitting_function_backup=best_fitting_function;
			best_fitting_function=fitting_function;
			compress();
			copy_iterator(best_it1,best_it1_backup);
			copy_iterator(it1,it1_backup);
			copy_iterator(it2,it2_backup);
			delete_data(best_it1_backup);
			delete_data(it1_backup);
			delete_data(it2_backup);
			delete_data(mxm);
			best_fitting_function=best_fitting_function_backup;
			data_num=data_num_backup;
			delete_data(data);
			data=data_backup;
		}
		if (strcmp(fitting_function,"cubic")==0)
			CR*=1;
		if (debug)
			print_test_condition();
		if (CR>best_CR)
		{
			best_CR=CR;
			copy_iterator(best_it1,it1);
			if (strcmp(compress_function,"compress_test")==0)
				strcpy(best_compress_function,"compress");
			strcpy(best_fitting_function,fitting_function);
		}
		bitstream_length=0;
	}
}


#endif