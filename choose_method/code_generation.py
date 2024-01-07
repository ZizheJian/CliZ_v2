for dimension_num in [1,2,3,4]:
	file=open(f"collect_data_{dimension_num}D.cpp","w")
	file.write(f"#ifndef __COLLECT_DATA_{dimension_num}D_CPP__\n")
	file.write(f"#define __COLLECT_DATA_{dimension_num}D_CPP__\n")
	file.write("\n")
	file.write("#include \"choose_method.hpp2\"\n")
	file.write("\n")
	file.write("namespace cliz\n")
	file.write("{\n")
	file.write("	template<typename T>\n")
	file.write(f"	void task_c<T>::collect_data_{dimension_num}D(T *data_backup,hyper_iterator_c *it2_backup)\n")
	file.write("	{\n")
	tabnum=2
	for did in range(dimension_num):
		file.write("	"*(tabnum+did)+f"for (long long i{did}=0;i{did}<it2->mx[{did}];i{did}++)\n")
	file.write("	"*(tabnum+dimension_num-1)+"{\n")
	tabnum=2+dimension_num
	for did in range(dimension_num):
		file.write("	"*tabnum+f"long long j{did}=((2*i{did}<it2->mx[{did}])?(i{did}+floor((it2_backup->mx[{did}]-it2->mx[{did}])/3)):(i{did}+it2_backup->mx[{did}]-it2->mx[{did}]-floor((it2_backup->mx[{did}]-it2->mx[{did}])/3)));\n")
	file.write("	"*tabnum+"data[")
	for did in range(dimension_num):
		if did!=0:
			file.write("+")
		file.write(f"i{did}*it2->weight[{did}]")
	file.write("]=data_backup[")
	for did in range(dimension_num):
		if did!=0:
			file.write("+")
		file.write(f"j{did}*it2_backup->weight[{did}]")
	file.write("];\n")
	tabnum=2
	file.write("	"*(tabnum+dimension_num-1)+"}\n")
	file.write("	}\n")
	file.write("}\n")
	file.write("\n")
	file.write("#endif")
	file.close()