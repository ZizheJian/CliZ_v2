#ifndef __TEST_PERT_CPP__
#define __TEST_PERT_CPP__

#include "lv1_test.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::calc_pert()
	{
		auto dis=uniform_int_distribution<long long>(0,data_num-1);
		float *temp_data=new_data<float>(FFT_SAMPLE_NUM*it2->mx[pertid]);
		for (long long t=0;t<FFT_SAMPLE_NUM;t++)
		{
			long long pos=dis(gen);
			long long lat_i=(pos/it2->weight[latid])%it2->mx[latid];
			long long lng_i=(pos/it2->weight[lngid])%it2->mx[lngid];
			long long pert_i=(pos/it2->weight[pertid])%it2->mx[pertid];
			pos=pos-pert_i*it2->weight[pertid];
			for (long long i=0;i<it2->mx[pertid];i++)
				temp_data[t*it2->mx[pertid]+i]=data[pos+i*it2->weight[pertid]];
		}
		int fft_n=it2->mx[pertid];
		fftwf_complex *freq=(fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex)*FFT_SAMPLE_NUM*(fft_n/2+1));
		fftwf_plan p=fftwf_plan_many_dft_r2c(1,&fft_n,FFT_SAMPLE_NUM,temp_data,NULL,1,it2->mx[pertid],freq,NULL,1,it2->mx[pertid]/2+1,FFTW_ESTIMATE);
		fftwf_execute(p);
		fftwf_destroy_plan(p);
		delete_data(temp_data);
		int *T_bin=new_data<int>(it2->mx[pertid],true);
		for (int t=0;t<FFT_SAMPLE_NUM;t++)
		{
			int maxfreq=1;
			float maxlength=pow(freq[t*(it2->mx[pertid]/2+1)+maxfreq][0],2)+pow(freq[t*(it2->mx[pertid]/2+1)+maxfreq][1],2);
			for (int i=2;i<it2->mx[pertid]/2+1;i++)
				if (maxlength<pow(freq[t*(it2->mx[pertid]/2+1)+i][0],2)+pow(freq[t*(it2->mx[pertid]/2+1)+i][1],2))
				{
					maxfreq=i;
					maxlength=pow(freq[t*(it2->mx[pertid]/2+1)+i][0],2)+pow(freq[t*(it2->mx[pertid]/2+1)+i][1],2);
				}
			T_bin[(int)(((float)(it2->mx[pertid]))/maxfreq+0.5)]++;
		}
		fftwf_free(freq);
		pert=1;
		for (int i=2;i<it2->mx[pertid];i++)
			if (T_bin[pert]<T_bin[i])
				pert=i;
		delete_data(T_bin);
	}

	template<typename T>
	void task_c<T>::calc_pert_mask()
	{
		auto dis=uniform_int_distribution<long long>(0,data_num-1);
		float *temp_data=new_data<float>(FFT_SAMPLE_NUM*it2->mx[pertid]);
		for (long long t=0;t<FFT_SAMPLE_NUM;t++)
		{
			long long pos=dis(gen);
			long long lat_i=(pos/it2->weight[latid])%it2->mx[latid];
			long long lng_i=(pos/it2->weight[lngid])%it2->mx[lngid];
			long long pert_i=(pos/it2->weight[pertid])%it2->mx[pertid];
			if (mask_data[lat_i*it2->mx[lngid]+lng_i]==0)
			{
				t--;
				continue;
			}
			pos=pos-pert_i*it2->weight[pertid];
			for (long long i=0;i<it2->mx[pertid];i++)
				temp_data[t*it2->mx[pertid]+i]=data[pos+i*it2->weight[pertid]];
		}
		int fft_n=it2->mx[pertid];
		fftwf_complex *freq=(fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex)*FFT_SAMPLE_NUM*(fft_n/2+1));
		fftwf_plan p=fftwf_plan_many_dft_r2c(1,&fft_n,FFT_SAMPLE_NUM,temp_data,NULL,1,it2->mx[pertid],freq,NULL,1,it2->mx[pertid]/2+1,FFTW_ESTIMATE);
		fftwf_execute(p);
		fftwf_destroy_plan(p);
		delete_data(temp_data);
		int *T_bin=new_data<int>(it2->mx[pertid],true);
		for (int t=0;t<FFT_SAMPLE_NUM;t++)
		{
			int maxfreq=1;
			float maxlength=pow(freq[t*(it2->mx[pertid]/2+1)+maxfreq][0],2)+pow(freq[t*(it2->mx[pertid]/2+1)+maxfreq][1],2);
			for (int i=2;i<it2->mx[pertid]/2+1;i++)
				if (maxlength<pow(freq[t*(it2->mx[pertid]/2+1)+i][0],2)+pow(freq[t*(it2->mx[pertid]/2+1)+i][1],2))
				{
					maxfreq=i;
					maxlength=pow(freq[t*(it2->mx[pertid]/2+1)+i][0],2)+pow(freq[t*(it2->mx[pertid]/2+1)+i][1],2);
				}
			T_bin[(int)(((float)(it2->mx[pertid]))/maxfreq+0.5)]++;
		}
		fftwf_free(freq);
		pert=1;
		for (int i=2;i<it2->mx[pertid];i++)
			if (T_bin[pert]<T_bin[i])
				pert=i;
		delete_data(T_bin);
	}

	template<typename T>
	void task_c<T>::test_pert()
	{
		////////////////Find Pert////////////////
		if (mask_file_path==NULL)
			calc_pert();
		else
		{
			new_data(mask_data,it2->mx[latid]*it2->mx[lngid]);
			mask_file=fopen(mask_file_path,"rb");
			fread(mask_data,sizeof(int),it2->mx[latid]*it2->mx[lngid],mask_file);
			fclose(mask_file);
			calc_pert_mask();
		}
		if (pert==it2->mx[pertid])
		{
			if (mask_file_path!=NULL)
				delete_data(mask_data);
			return;
		}
		////////////////Test Pert////////////////
		hyper_iterator_c *it2_backup=it2;
		it2=NULL;
		copy_iterator(it2,it2_backup);
		it2->mx[pertid]=pert;
		for (int did=it2->n-1;did>=0;did--)
			if (did==it2->n-1)
				it2->weight[did]=1;
			else
				it2->weight[did]=it2->weight[did+1]*it2->mx[did+1];
		hyper_iterator_c *it1_backup=it1;
		it1=NULL;
		copy_iterator(it1,it2);
		long long data_num_backup=data_num;
		data_num=data_num*it2->mx[pertid]/it2_backup->mx[pertid];
		T *data_backup=data;
		new_data(data,data_num,true,false);
		unsigned char *bitstream_backup=bitstream;
		new_data(bitstream,data_num*sizeof(T),false,false);
		for (long long pos=0;pos<data_num_backup;pos++)
		{
			long long lat_i=(pos/it2_backup->weight[latid])%it2_backup->mx[latid];
			long long lng_i=(pos/it2_backup->weight[lngid])%it2_backup->mx[lngid];
			long long pos_low=pos%it2_backup->weight[pertid];
			long long pos_pert=(pos-pos_low)%(it2_backup->weight[pertid]*it2_backup->mx[pertid]);
			long long pos_high=pos-pos_pert-pos_low;
			pos_pert=((pos_pert/it2_backup->weight[pertid])%it2->mx[pertid])*it2->weight[pertid];
			pos_high=(pos_high/it2_backup->mx[pertid])*it2->mx[pertid];
			if ((mask_file_path!=NULL) && (mask_data[lat_i*it2_backup->mx[lngid]+lng_i]==0))
				data[pos_high+pos_pert+pos_low]=data_backup[pos];
			else
				data[pos_high+pos_pert+pos_low]+=data_backup[pos];
		}
		for (long long pos=0;pos<data_num;pos++)
		{
			long long lat_i=(pos/it2_backup->weight[latid])%it2_backup->mx[latid];
			long long lng_i=(pos/it2_backup->weight[lngid])%it2_backup->mx[lngid];
			if ((mask_file_path!=NULL) && (mask_data[lat_i*it2_backup->mx[lngid]+lng_i]==0))
				continue;
			long long pert_i=(pos/it2->weight[pertid])%it2->mx[pertid];
			data[pos]/=ceil(((float)(it2_backup->mx[pertid]-pert_i))/it2->mx[pertid]);
		}
		int *mask_data_backup=mask_data;
		mask_data=NULL;
		if (map_file_mode!=NULL)
			if (mask_file_path!=NULL)
				test_map_mask();
			else
				test_map();
		if (mask_file_path!=NULL)
			test_mask();
		else
			test();
		new_data(best_pert_compress_function,FUNC_NAME_LENGTH);
		strcpy(best_pert_compress_function,best_compress_function);
		new_data(best_pert_fitting_function,FUNC_NAME_LENGTH);
		strcpy(best_pert_fitting_function,best_fitting_function);
		copy_iterator(best_pert_it1,best_it1);
		copy_iterator(pert_it2,it2);

		////////////////Test Remaining////////////////
		best_pert_CR=best_CR;
		best_CR=0;
		delete_data(it2);
		it2=it2_backup;
		delete_data(it1);
		it1=it1_backup;
		delete_data(best_it1);
		delete_data(bitstream);
		bitstream=bitstream_backup;
		data_num=data_num_backup;
		mask_data=mask_data_backup;
		T *data_remain=new_data<T>(data_num);
		for (long long pos=0;pos<data_num;pos++)
		{
			long long lat_i=(pos/it2->weight[latid])%it2->mx[latid];
			long long lng_i=(pos/it2->weight[lngid])%it2->mx[lngid];
			long long pos_low=pos%it2->weight[pertid];
			long long pos_pert=(pos-pos_low)%(it2->weight[pertid]*it2->mx[pertid]);
			long long pos_high=pos-pos_pert-pos_low;
			pos_pert=((pos_pert/it2->weight[pertid])%pert_it2->mx[pertid])*pert_it2->weight[pertid];
			pos_high=(pos_high/it2->mx[pertid])*pert_it2->mx[pertid];
			if ((mask_file_path!=NULL) && (mask_data[lat_i*it2->mx[lngid]+lng_i]==0))
				data_remain[pos]=0;
			else
				data_remain[pos]=data_backup[pos]-data[pos_high+pos_pert+pos_low];
		}
		delete_data(data);
		data=data_remain;
		if (mask_file_path!=NULL)
			delete_data(mask_data);
		if (map_file_mode!=NULL)
			if (mask_file_path!=NULL)
				test_map_mask();
			else
				test_map();
		if (mask_file_path!=NULL)
			test_mask();
		else
			test();
		best_CR=it2->mx[pertid]/(pert/best_pert_CR+it2->mx[pertid]/best_CR);
		delete_data(data);
		data=data_backup;
	}
}

#endif