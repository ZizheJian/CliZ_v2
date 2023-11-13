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

	void hyper_iterator_c::print_more(bool recursive)
	{
		/*printf("address=%p\n",this);
		if (base_iterator)
			printf("name=%s\n",name);
		printf("mn=      ");
		for (int i=0;i<n;i++)
			printf("[%d]=%lld ",i,mn[i]);
		printf("\nmx=      ");
		for (int i=0;i<n;i++)
			printf("[%d]=%lld ",i,mx[i]);
		printf("\ngap=     ");
		for (int i=0;i<n;i++)
			printf("[%d]=%lld ",i,gap[i]);
		printf("\ncurrent= ");
		for (int i=0;i<n;i++)
			printf("[%d]=%lld ",i,current[i]);
		printf("\nweight=  ");
		for (int i=0;i<n;i++)
			printf("[%d]=%lld ",i,weight[i]);
		printf("\npos=%lld\n",pos);
		for (auto rel_it=related_iterator_vec.begin();rel_it!=related_iterator_vec.end();rel_it++)
		{
			printf("    father_it=%p\n",rel_it->father_it);
			printf("    son_it=%p\n",rel_it->son_it);
			printf("    mapping_f_name=%s",rel_it->mapping_f_name);
			if (rel_it->active)
				printf("\n");
			else
				printf(" (deactivated)\n");
			if (strcmp(rel_it->mapping_f_name,"seq_mapping")==0)
			{
				printf("    dim_seq=");
				for (int did=0;did<n;did++)
					printf("%d ",rel_it->dim_seq[did]);
				printf("\n");
			}
			if (strcmp(rel_it->mapping_f_name,"fission_mapping")==0)
			{
				printf("    dim_fission_l=%d\n",rel_it->dim_fission_l);
				printf("    dim_fission_r=%d\n",rel_it->dim_fission_r);
			}
			if (strcmp(rel_it->mapping_f_name,"linear_mapping")==0)
			{
				printf("    mul=");
				for (int did=0;did<n;did++)
					printf("%lld ",rel_it->mul[did]);
				printf("\n    div=");
				for (int did=0;did<n;did++)
					printf("%lld ",rel_it->div[did]);
				printf("\n    plus=");
				for (int did=0;did<n;did++)
					printf("%lld ",rel_it->plus[did]);
				printf("\n");
			}
			if (strcmp(rel_it->mapping_f_name,"pert_mapping")==0)
			{
				printf("    pert=");
				for (int did=0;did<n;did++)
					printf("%lld ",rel_it->pert[did]);
				printf("\n");
			}
		}
		printf("\n");
		for (auto rel_it=related_iterator_vec.begin();rel_it!=related_iterator_vec.end();rel_it++)
			if (rel_it->active)
				rel_it->son_it->print_more(recursive);*/
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
	void hyper_iterator_c::delete_iterator(bool recursive)
	{
		/*for (auto rel_it=related_iterator_vec.begin();rel_it!=related_iterator_vec.end();rel_it=related_iterator_vec.begin())
		{
			if (recursive)
				if (rel_it->active)
					delete_data(rel_it->son_it,recursive);
			delete_data(rel_it->dim_seq);
			delete_data(rel_it->mul);
			delete_data(rel_it->div);
			delete_data(rel_it->plus);
			delete_data(rel_it->mapping_f_name);
			related_iterator_vec.erase(rel_it);
		}
		delete_data(mn);
		delete_data(mx);
		delete_data(gap);
		delete_data(current);
		delete_data(weight);*/
	}

	void copy_iterator(hyper_iterator_c *&ity,hyper_iterator_c *itx,bool recursive=true)
	{
		/*delete_data(ity);
		if (itx->base_iterator)
		{
			ity=itx;
			return;
		}
		new_data(ity,itx->n);
		memcpy(ity->mn,itx->mn,sizeof(long long)*itx->n);
		memcpy(ity->mx,itx->mx,sizeof(long long)*itx->n);
		memcpy(ity->gap,itx->gap,sizeof(long long)*itx->n);
		memcpy(ity->current,itx->current,sizeof(long long)*itx->n);
		memcpy(ity->weight,itx->weight,sizeof(long long)*itx->n);
		if (!recursive)
			return;
		for (auto rel_it=itx->related_iterator_vec.begin();rel_it!=itx->related_iterator_vec.end();rel_it++)
		{
			hyper_iterator_c *temp_it1=NULL;
			if (rel_it->son_it->base_iterator)
				temp_it1=rel_it->son_it;
			else
				copy_iterator(temp_it1,rel_it->son_it);
			if (strcmp(rel_it->mapping_f_name,"seq_mapping")==0)
			{
				ity->append_related_iterator_seq(temp_it1);
				memcpy(ity->related_iterator_vec[ity->related_iterator_vec.size()-1].dim_seq,rel_it->dim_seq,
					itx->n*sizeof(int));
			}
			if (strcmp(rel_it->mapping_f_name,"fission_mapping")==0)
			{
				ity->append_related_iterator_fission(temp_it1);
				ity->related_iterator_vec[ity->related_iterator_vec.size()-1].dim_fission_l=rel_it->dim_fission_l;
				ity->related_iterator_vec[ity->related_iterator_vec.size()-1].dim_fission_r=rel_it->dim_fission_r;
			}
			if (strcmp(rel_it->mapping_f_name,"linear_mapping")==0)
			{
				ity->append_related_iterator_linear(temp_it1);
				memcpy(ity->related_iterator_vec[ity->related_iterator_vec.size()-1].mul,rel_it->mul,
					itx->n*sizeof(long long));
				memcpy(ity->related_iterator_vec[ity->related_iterator_vec.size()-1].div,rel_it->div,
					itx->n*sizeof(long long));
				memcpy(ity->related_iterator_vec[ity->related_iterator_vec.size()-1].div,rel_it->div,
					itx->n*sizeof(long long));
			}
		}*/
	}
}

#endif