#ifndef __HYPER_ITERATOR_CPP__
#define __HYPER_ITERATOR_CPP__

#include "globalvar.hpp"
#include "io/io.hpp1"

namespace cliz
{
	hyper_iterator_c::hyper_iterator_c(int a)
	{
		n=a;
		new_data(mx,n);
		new_data(weight,n);
	}

	void hyper_iterator_c::print()
	{
		printf("	mx=(");
		for (int i=0;i<n-1;i++)
			printf("%lld, ",mx[i]);
		printf("%lld)\n",mx[n-1]);
		printf("	weight=(");
		for (int i=0;i<n-1;i++)
			printf("%lld, ",weight[i]);
		printf("%lld)\n",weight[n-1]);
		if (dim_seq!=NULL)
		{
			int actual_n=((dim_fission_l==dim_fission_r)?n:(n+dim_fission_r-dim_fission_l-1));
			printf("	dim_seq=(");
			for (int did=0;did<actual_n-1;did++)
				printf("%d, ",dim_seq[did]);
			printf("%d)\n",dim_seq[actual_n-1]);
		}
		if (dim_fission_l!=dim_fission_r)
		{
			printf("	dim_fission_l=%d\n",dim_fission_l);
			printf("	dim_fission_r=%d\n",dim_fission_r);
		}
	}

	void hyper_iterator_c::write(FILE *cfg_file)
	{
		fprintf(cfg_file,"Max=");
		for (int did=0;did<n;did++)
			fprintf(cfg_file,"%lld ",mx[did]);
		fprintf(cfg_file,"\n");
		if (dim_seq!=NULL)
		{
			int actual_n=((dim_fission_l==dim_fission_r)?n:(n+dim_fission_r-dim_fission_l-1));
			fprintf(cfg_file,"Dimension sequence=");
			for (int did=0;did<actual_n;did++)
				fprintf(cfg_file,"%d ",dim_seq[did]);
		}
		if (dim_fission_l!=dim_fission_r)
			fprintf(cfg_file,"Dimension fission=%d %d\n",dim_fission_l,dim_fission_r);
	}

	//释放这个hyper_iterator中数组占用的内存
	void hyper_iterator_c::delete_iterator()
	{
		delete_data(mx);
		delete_data(weight);
		delete_data(dim_seq);
	}

	void copy_iterator(hyper_iterator_c *&ity,hyper_iterator_c *itx)
	{
		delete_data(ity);
		if (itx==NULL)
			return;
		new_data(ity,itx->n);
		memcpy(ity->mx,itx->mx,itx->n*sizeof(long long));
		memcpy(ity->weight,itx->weight,itx->n*sizeof(long long));
		if (itx->dim_seq!=NULL)
		{
			int actual_n=((itx->dim_fission_l==itx->dim_fission_r)?itx->n:(itx->n+itx->dim_fission_r-itx->dim_fission_l-1));
			new_data(ity->dim_seq,actual_n);
			memcpy(ity->dim_seq,itx->dim_seq,actual_n*sizeof(int));
		}
		ity->dim_fission_l=itx->dim_fission_l;
		ity->dim_fission_r=itx->dim_fission_r;
	}

	template<typename T>
	void task_c<T>::reverse_convert(long long *i1,long long *i2)
	{
		if (it1->dim_fission_l==it1->dim_fission_r)
			if (it1->dim_seq==NULL)
				memcpy(i1,i2,it2->n*sizeof(long long));
			else
				for (int did=0;did<it2->n;did++)
					i1[did]=i2[it1->dim_seq[did]];
		else
			if (it1->dim_seq==NULL)
			{
				int dim_fission_l=it1->dim_fission_l;
				int dim_fission_r=it1->dim_fission_r;
				for (int did=0;did<dim_fission_l;did++)
					i1[did]=i2[did];
				i1[dim_fission_l]=0;
				for (int did=dim_fission_l;did<dim_fission_r;did++)
				{
					i1[dim_fission_l]*=it2->mx[did];
					i1[dim_fission_l]+=i2[did];
				}
				for (int did=dim_fission_l+1;did<it1->n;did++)
					i1[did]=i2[did+dim_fission_r-dim_fission_l-1];
			}
			else
			{
				int dim_fission_l=it1->dim_fission_l;
				int dim_fission_r=it1->dim_fission_r;
				int *dim_seq=it1->dim_seq;
				for (int did=0;did<dim_fission_l;did++)
					i1[did]=i2[dim_seq[did]];
				i1[dim_fission_l]=0;
				for (int did=dim_fission_l;did<dim_fission_r;did++)
				{
					i1[dim_fission_l]*=it2->mx[dim_seq[did]];
					i1[dim_fission_l]+=i2[dim_seq[did]];
				}
				for (int did=dim_fission_l+1;did<it1->n;did++)
					i1[did]=i2[dim_seq[did+dim_fission_r-dim_fission_l-1]];
			}
	}

	template<typename T>
	void task_c<T>::convert(long long *i1,long long *i2)
	{
		if (it1->dim_fission_l==it1->dim_fission_r)
			if (it1->dim_seq==NULL)
				memcpy(i2,i1,it2->n*sizeof(long long));
			else
				for (int did=0;did<it2->n;did++)
					i2[it1->dim_seq[did]]=i1[did];
		else
			if (it1->dim_seq==NULL)
			{
				int dim_fission_l=it1->dim_fission_l;
				int dim_fission_r=it1->dim_fission_r;
				for (int did=it2->n-1;did>=dim_fission_r;did--)
					i2[did]=i1[did+dim_fission_l-dim_fission_r+1];
				long long temp=i1[dim_fission_l];
				for (int did=dim_fission_r-1;did>=dim_fission_l;did--)
				{
					i2[did]=temp%it2->mx[did];
					temp/=it2->mx[did];
				}
				for (int did=dim_fission_l-1;did>=0;did--)
					i2[did]=i1[did];
			}
			else
			{
				int dim_fission_l=it1->dim_fission_l;
				int dim_fission_r=it1->dim_fission_r;
				int *dim_seq=it1->dim_seq;
				for (int did=it2->n-1;did>=dim_fission_r;did--)
					i2[dim_seq[did]]=i1[did+dim_fission_l-dim_fission_r+1];
				long long temp=i1[dim_fission_l];
				for (int did=dim_fission_r-1;did>=dim_fission_l;did--)
				{
					i2[dim_seq[did]]=temp%it2->mx[dim_seq[did]];
					temp/=it2->mx[dim_seq[did]];
				}
				for (int did=dim_fission_l-1;did>=0;did--)
					i2[dim_seq[did]]=i1[did];
			}
	}
}

#endif