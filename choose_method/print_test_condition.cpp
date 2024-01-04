#ifndef __PRINT_TEST_CONDITION_CPP__
#define __PRINT_TEST_CONDITION_CPP__

#include "choose_method.hpp2"

namespace cliz
{
	template<typename T>
	void task_c<T>::print_test_condition()
	{
		char *temp_string=new_data<char>(TEMP_STRING_LENGTH,true);
		if (it1->dim_seq==NULL)
			for (int did=0;did<it2->n;did++)
				sprintf(temp_string+strlen(temp_string),"%d",did);
		else
			for (int did=0;did<it2->n;did++)
				sprintf(temp_string+strlen(temp_string),"%d",it1->dim_seq[did]);
		if (TEST_ALL)
			sprintf(temp_string+strlen(temp_string),"%d%d ALL %f",it1->dim_fission_l,it1->dim_fission_r,((float)bitstream_length)/(data_num*sizeof(T)));
		else
			sprintf(temp_string+strlen(temp_string),"%d%d %f %f",it1->dim_fission_l,it1->dim_fission_r,(float)SAMPLING_RATE,((float)bitstream_length)/(test_num*sizeof(T)));
		printf("%s\n",temp_string);
		FILE *test_condition_file=fopen("result/test_condition.txt","a");
		fprintf(test_condition_file,"%s\n",temp_string);
		fclose(test_condition_file);
	}
}

#endif