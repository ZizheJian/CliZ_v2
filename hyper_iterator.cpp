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
		printf("mx=(");
		for (int i=0;i<n-1;i++)
			printf("%lld, ",mx[i]);
		printf("%lld)\n",mx[n-1]);
		printf("weight=(");
		for (int i=0;i<n-1;i++)
			printf("%lld, ",weight[i]);
		printf("%lld)\n",weight[n-1]);
		for (auto rel_it=relationship_chain.begin();rel_it!=relationship_chain.end();rel_it++)
		{
			printf("    mapping_f_name=%s",rel_it->mapping_name);
			if (strcmp(rel_it->mapping_name,"seq_mapping")==0)
			{
				printf("    dim_seq=(");
				for (int did=0;did<n-1;did++)
					printf("%d, ",rel_it->dim_seq[did]);
				printf("%d)\n",rel_it->dim_seq[n-1]);
			}
			if (strcmp(rel_it->mapping_name,"fission_mapping")==0)
			{
				printf("    dim_fission_l=%d\n",rel_it->dim_fission_l);
				printf("    dim_fission_r=%d\n",rel_it->dim_fission_r);
			}
		}
	}

	void hyper_iterator_c::write(FILE *cfg_file)
	{
		/*fprintf(cfg_file,"n=%d\n",n);
		fprintf(cfg_file,"address=%p\n",this);
		if (base_iterator)
			fprintf(cfg_file,"name=%s\n",name);
		fprintf(cfg_file,"mn=");
		for (int i=0;i<n;i++)
			fprintf(cfg_file,"%lld ",mn[i]);
		fprintf(cfg_file,"\nmx=");
		for (int i=0;i<n;i++)
			fprintf(cfg_file,"%lld ",mx[i]);
		fprintf(cfg_file,"\ngap=");
		for (int i=0;i<n;i++)
			fprintf(cfg_file,"%lld ",gap[i]);
		fprintf(cfg_file,"\nweight=");
		for (int i=0;i<n;i++)
			fprintf(cfg_file,"%lld ",weight[i]);
		fprintf(cfg_file,"\n");
		for (auto rel_it=related_iterator_vec.begin();rel_it!=related_iterator_vec.end();rel_it++)
		{
			fprintf(cfg_file,"    mapping_f_name=%s\n",rel_it->mapping_f_name);
			if (strcmp(rel_it->mapping_f_name,"seq_mapping")==0)
			{
				fprintf(cfg_file,"    dim_seq=");
				for (int did=0;did<n;did++)
					fprintf(cfg_file,"%d ",rel_it->dim_seq[did]);
				fprintf(cfg_file,"\n");
			}
			if (strcmp(rel_it->mapping_f_name,"fission_mapping")==0)
			{
				fprintf(cfg_file,"    dim_fission_l=%d\n",rel_it->dim_fission_l);
				fprintf(cfg_file,"    dim_fission_r=%d\n",rel_it->dim_fission_r);
			}
			if (strcmp(rel_it->mapping_f_name,"linear_mapping")==0)
			{
				fprintf(cfg_file,"    mul=");
				for (int did=0;did<n;did++)
					fprintf(cfg_file,"%lld ",rel_it->mul[did]);
				fprintf(cfg_file,"\n    div=");
				for (int did=0;did<n;did++)
					fprintf(cfg_file,"%lld ",rel_it->div[did]);
				fprintf(cfg_file,"\n    plus=");
				for (int did=0;did<n;did++)
					fprintf(cfg_file,"%lld ",rel_it->plus[did]);
				fprintf(cfg_file,"\n");
			}
			if (strcmp(rel_it->mapping_f_name,"pert_mapping")==0)
			{
				fprintf(cfg_file,"    pert=");
				for (int did=0;did<n;did++)
					fprintf(cfg_file,"%lld ",rel_it->pert[did]);
				fprintf(cfg_file,"\n");
			}
		}
		fprintf(cfg_file,"\n");
		for (auto rel_it=related_iterator_vec.begin();rel_it!=related_iterator_vec.end();rel_it++)
			rel_it->son_it->write(cfg_file);*/
	}

	//释放这个hyper_iterator中数组占用的内存
	void hyper_iterator_c::delete_iterator()
	{
		delete_data(mx);
		delete_data(weight);
		for (auto rel_it=relationship_chain.begin();rel_it!=relationship_chain.end();rel_it=relationship_chain.begin())
		{
			delete_data(rel_it->dim_seq);
			delete_data(rel_it->mapping_name);
			relationship_chain.erase(rel_it);
		}
	}

	void copy_iterator(hyper_iterator_c *&ity,hyper_iterator_c *itx)
	{
		delete_data(ity);
		new_data(ity,itx->n);
		memcpy(ity->mx,itx->mx,itx->n*sizeof(long long));
		memcpy(ity->weight,itx->weight,itx->n*sizeof(long long));
		for (auto rel_it=itx->relationship_chain.begin();rel_it!=itx->relationship_chain.end();rel_it++)
		{
			ity->relationship_chain.push_back(hyper_iterator_c::iterator_relationship_c());
			memcpy(&*(ity->relationship_chain.rbegin()),&*(rel_it),sizeof(hyper_iterator_c::iterator_relationship_c));
		}
	}
}

#endif