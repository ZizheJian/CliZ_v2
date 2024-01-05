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
		sprintf(temp_string+strlen(temp_string),"%d%d",it1->dim_fission_l,it1->dim_fission_r);
		if (strcmp(fitting_function,"cubic")==0)
			sprintf(temp_string+strlen(temp_string),"1");
		if (strcmp(fitting_function,"linear")==0)
			sprintf(temp_string+strlen(temp_string),"0");
		if (TEST_ALL)
			sprintf(temp_string+strlen(temp_string)," ALL %f",((float)data_num*sizeof(T))/(bitstream_length));
		else
			sprintf(temp_string+strlen(temp_string)," %f %f",(float)SAMPLING_RATE,((float)test_num*sizeof(T))/(bitstream_length));
		printf("%s\n",temp_string);
		FILE *test_condition_file=fopen("result/test_condition.txt","a");
		fprintf(test_condition_file,"%s\n",temp_string);
		fclose(test_condition_file);
	}
}

#endif