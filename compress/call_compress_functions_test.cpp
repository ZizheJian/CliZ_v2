#ifndef __CALL_COMPRESS_FUNCTIONS_TEST_CPP__
#define __CALL_COMPRESS_FUNCTIONS_TEST_CPP__

#include "compress.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::call_compress_functions_test()
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
		bitstream_start=sizeof(long long);
		bitstream_end=sizeof(long long);
		if (strcmp(compress_function,"compress_test")==0)
			compress();
		if (strcmp(compress_function,"compress_set_map_test")==0)
		{
			map_bitstream_start=sizeof(long long);
			map_bitstream_end=sizeof(long long);
			compress_set_map();
		}
		if (strcmp(compress_function,"compress_mask_test")==0)
		{
			int *mask_data_backup=mask_data;
			new_data(mask_data,it2->mx[latid]*it2->mx[lngid],false,false);
			collect_data_mask(mask_data_backup,it2_backup);
			compress_mask();
			delete_data(mask_data);
			mask_data=mask_data_backup;
		}
		if (strcmp(compress_function,"compress_set_map_mask_test")==0)
		{
			int *mask_data_backup=mask_data;
			new_data(mask_data,it2->mx[latid]*it2->mx[lngid],false,false);
			collect_data_mask(mask_data_backup,it2_backup);
			compress_set_map_mask();
			delete_data(mask_data);
			mask_data=mask_data_backup;
		}
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
		
		if (pert!=0)
			if (it2->mx[pertid]!=pert)
				best_CR=it2->mx[pertid]/(pert/best_pert_CR+it2->mx[pertid]/best_CR);
		if (debug)
			print_test_condition();
		if (CR>best_CR)
		{
			best_CR=CR;
			copy_iterator(best_it1,it1);
			if (strcmp(compress_function,"compress_test")==0)
				strcpy(best_compress_function,"compress");
			if (strcmp(compress_function,"compress_set_map_test")==0)
				strcpy(best_compress_function,"compress_set_map");
			if (strcmp(compress_function,"compress_mask_test")==0)
				strcpy(best_compress_function,"compress_mask");
			if (strcmp(compress_function,"compress_set_map_mask_test")==0)
				strcpy(best_compress_function,"compress_set_map_mask");
			strcpy(best_fitting_function,fitting_function);
			best_pert=pert;
		}
		bitstream_start=0;
		bitstream_end=0;
		map_bitstream_start=0;
		map_bitstream_end=0;
	}
}

#endif