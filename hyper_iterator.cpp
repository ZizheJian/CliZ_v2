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
		printf("    mx=(");
		for (int i=0;i<n-1;i++)
			printf("%lld, ",mx[i]);
		printf("%lld)\n",mx[n-1]);
		printf("    weight=(");
		for (int i=0;i<n-1;i++)
			printf("%lld, ",weight[i]);
		printf("%lld)\n",weight[n-1]);
		if (dim_seq!=NULL)
		{
			int actual_n=((dim_fission_l==dim_fission_r)?n:(n+dim_fission_r-dim_fission_l-1));
			printf("    dim_seq=(");
			for (int did=0;did<actual_n-1;did++)
				printf("%d, ",dim_seq[did]);
			printf("%d)\n",dim_seq[actual_n-1]);
		}
		if (dim_fission_l!=dim_fission_r)
		{
			printf("    dim_fission_l=%d\n",dim_fission_l);
			printf("    dim_fission_r=%d\n",dim_fission_r);
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
}

#endif