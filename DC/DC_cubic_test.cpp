#ifndef __DC_CUBIC_TEST_CPP__
#define __DC_CUBIC_TEST_CPP__

#include "DC.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::DC_cubic_test()
	{
		T *data_backup=data;
		new_data(data,13,false,false);
		long long *mx1=it1->mx;
		long long *mx2=it2->mx;
		long long *weight2=it2->weight;
		long long *i1=new_data<long long>(it1->n);
		long long *i2=new_data<long long>(it2->n);
		T err_bound_backup=err_bound;
		for (long long test_id=0;test_id<test_num;test_id++)
		{
			//printf("test_id=%lld, test_pos=%lld\n",test_id,test_pos[test_id]);
			if (test_pos[test_id]==0)
			{
				data[7]=data_backup[0];
				quant_bin[test_id]=quantize(7,0);
				continue;
			}
			for (int did=it2->n-1;did>=0;did--)
				i2[did]=(test_pos[test_id]/weight2[did])%mx2[did];
			//printf("i2[0]=%lld, i2[1]=%lld, i2[2]=%lld\n",i2[0],i2[1],i2[2]);
			reverse_convert(i1,i2,it1,it2);
			//printf("i1[0]=%lld, i1[1]=%lld, i1[2]=%lld\n",i1[0],i1[1],i1[2]);
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
			int left_data=2;
			int right_data=2;
			while (i1[direction]-(2*left_data-1)*stride<0)
				left_data--;
			while (i1[direction]+(2*right_data-1)*stride>=mx1[direction])
				right_data--;
			while ((i1[direction]-(2*left_data+1)*stride>=0) && (left_data+right_data<3))
				left_data++;
			while ((i1[direction]+(2*right_data+1)*stride<mx1[direction]) && (left_data+right_data<3))
				right_data++;
			long long i1_direction_backup=i1[direction];
			long long pos2=i2[0]*weight2[0]+i2[1]*weight2[1]+i2[2]*weight2[2];
			data[7]=data_backup[pos2];
			for (int i=1;i<=left_data;i++)
			{
				i1[direction]=i1_direction_backup-(2*i-1)*stride;
				convert(i1,i2,it1,it2);
				long long pos2l=i2[0]*weight2[0]+i2[1]*weight2[1]+i2[2]*weight2[2];
				data[8-2*i]=data_backup[pos2l];
			}
			for (int i=1;i<=right_data;i++)
			{
				i1[direction]=i1_direction_backup+(2*i-1)*stride;
				convert(i1,i2,it1,it2);
				long long pos2r=i2[0]*weight2[0]+i2[1]*weight2[1]+i2[2]*weight2[2];
				data[6+2*i]=data_backup[pos2r];
			}
			T pred;
			if (left_data==1)
			{
				if (right_data==0)
					pred=constant_fitting_dp(7,1);
				if (right_data==1)
					pred=linear_fitting_dpd(7,1);
				if (right_data==2)
					pred=quadratic_fitting_ddpd(7,-1);
			}
			if (left_data==2)
			{
				if (right_data==0)
					pred=linear_fitting_ddp(7,1);
				if (right_data==1)
					pred=quadratic_fitting_ddpd(7,1);
				if (right_data==2)
					pred=cubic_fitting_ddpdd(7,1);
			}
			if (left_data==3)
			{
				if (right_data==0)
					pred=quadratic_fitting_dddp(7,1);
			}
			quant_bin[test_id]=quantize(7,pred);
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