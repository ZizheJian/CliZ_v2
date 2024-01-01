#ifndef __TEST_ALL_DIMENSION_FISSION_CPP__
#define __TEST_ALL_DIMENSION_FISSION_CPP__

#include "lv2_test.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::test_all_dimension_fission()
	{
		test_all_fitting_function();
		hyper_iterator_c *it1_backup=NULL;
		copy_iterator(it1_backup,it1);
		delete_data(it1);
		for (int dim_fission_size=2;dim_fission_size<=it1_backup->n;dim_fission_size++)
		{
			new_data(it1,it1_backup->n-dim_fission_size+1);
			if (it1_backup->dim_seq!=NULL)
			{
				new_data(it1->dim_seq,it1_backup->n);
				memcpy(it1->dim_seq,it1_backup->dim_seq,sizeof(int)*it1_backup->n);
			}
			for (int dim_fission_l=0,dim_fission_r=dim_fission_size;dim_fission_r<=it1_backup->n;dim_fission_l++,dim_fission_r++)
			{
				it1->dim_fission_l=dim_fission_l;
				it1->dim_fission_r=dim_fission_r;
				for (int did=0;did<it1->n;did++)
				{
					if (did<dim_fission_l)
						it1->mx[did]=it1_backup->mx[did];
					if (did==dim_fission_l)
					{
						it1->mx[did]=1;
						for (int djd=dim_fission_l;djd<dim_fission_r;djd++)
							it1->mx[did]*=it1_backup->mx[djd];
					}
					if (did>dim_fission_l)
						it1->mx[did]=it1_backup->mx[did+dim_fission_size-1];
				}
				for (int did=it1->n-1;did>=0;did--)
					if (did==it1->n-1)
						it1->weight[did]=1;
					else
						it1->weight[did]=it1->weight[did+1]*it1->mx[did+1];
				test_all_fitting_function();
			}
			delete_data(it1);
		}
		copy_iterator(it1,it1_backup);
		delete_data(it1_backup);
	}
}

#endif