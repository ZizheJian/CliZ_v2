#ifndef __DC_LINEAR_TEST_CPP__
#define __DC_LINEAR_TEST_CPP__

#include "DC.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::DC_linear_test()
	{
		T *data_backup=data;
		new_data(data,5,false,false);
		long long *mx1=it1->mx;
		long long *mx2=it2->mx;
		long long *weight2=it2->weight;
		long long *i1=new_data<long long>(it1->n);
		long long *i2=new_data<long long>(it2->n);
		T err_bound_backup=err_bound;
		for (long long test_id=0;test_id<test_num;test_id++)
		{
			if (test_pos[test_id]==0)
			{
				data[3]=data_backup[0];
				quant_bin[test_id]=quantize(3,0);
				continue;
			}
			for (int did=it2->n-1;did>=0;did--)
				i2[did]=(test_pos[test_id]/weight2[did])%mx2[did];
			reverse_convert(i1,i2);
			int lv=0;
			int direction=0;
			for (lv=0;;lv++)
			{
				long long stride=1<<lv;
				bool flag=true;
				for (int did=it1->n-1;did>=0;did--)
					if (i1[did]%(2*stride)!=0)
					{
						direction=did;
						flag=false;
						break;
					}
				if (!flag)
					break;
			}
			long long stride=1<<lv;
			if (lv>=2)
				err_bound=err_bound_backup*0.5;
			else
				err_bound=err_bound_backup;
			err_bound_reciprocal=1/err_bound;
			long long pos2=i2[0]*weight2[0]+i2[1]*weight2[1]+i2[2]*weight2[2];
			data[3]=data_backup[pos2];
			i1[direction]-=stride;
			convert(i1,i2);
			long long pos2l=i2[0]*weight2[0]+i2[1]*weight2[1]+i2[2]*weight2[2];
			data[2]=data_backup[pos2l];
			T pred=0;
			if (i1[direction]+2*stride<mx1[direction])
			{
				i1[direction]+=2*stride;
				convert(i1,i2);
				long long pos2r=i2[0]*weight2[0]+i2[1]*weight2[1]+i2[2]*weight2[2];
				data[4]=data_backup[pos2r];
				pred=linear_fitting_dpd(3,1);
			}
			else
				if (i1[direction]-2*stride>=0)
				{
					i1[direction]-=2*stride;
					convert(i1,i2);
					long long pos2ll=i2[0]*weight2[0]+i2[1]*weight2[1]+i2[2]*weight2[2];
					data[0]=data_backup[pos2ll];
					pred=linear_fitting_ddp(3,1);
				}
				else
					pred=constant_fitting_dp(3,1);
			quant_bin[test_id]=quantize(3,pred);
		}
		delete_data(data);
		data=data_backup;
		delete_data(i1);
		delete_data(i2);
		err_bound=err_bound_backup;
		err_bound_reciprocal=1/err_bound;
	}
}

#endif