for dimension_num in [1,2,3,4]:
	file=open(f"transform_{dimension_num}D.cpp","w")
	file.write(f"#ifndef __TRANSPOSE_{dimension_num}D_CPP__\n")
	file.write(f"#define __TRANSPOSE_{dimension_num}D_CPP__\n")
	file.write("\n")
	file.write("#include \"transform.hpp2\"\n")
	file.write("\n")
	file.write("namespace cliz\n")
	file.write("{\n")
	file.write("	template<typename T>\n")
	file.write(f"	void task_c<T>::transpose_{dimension_num}D(T *data_backup)\n")
	file.write("	{\n")
	file.write("		long long *mx1=it1->mx;\n")
	file.write("		long long *weight1=it1->weight;\n")
	file.write("		long long *weight2=it2->weight;\n")
	file.write("		int *dim_seq=it1->dim_seq;\n")
	file.write("		long long *i=new_data<long long>(it2->n);\n")
	file.write("		long long *j=new_data<long long>(it2->n);\n")
	tabnum=2
	for did in range(dimension_num):
		file.write("	"*(tabnum+did)+f"for (i[{did}]=0;i[{did}]<mx1[{did}];i[{did}]++)\n")
		file.write("	"*(tabnum+did)+"{\n")
		file.write("	"*(tabnum+did+1)+f"j[dim_seq[{did}]]=i[{did}];\n")
	tabnum=2+dimension_num
	file.write("	"*tabnum+"long long pos1=")
	for did in range(dimension_num):
		if did==0:
			file.write(f"i[{did}]*weight1[{did}]")
		else:
			file.write(f"+i[{did}]*weight1[{did}]")
	file.write(";\n")
	file.write("	"*tabnum+"long long pos2=")
	for did in range(dimension_num):
		if did==0:
			file.write(f"j[{did}]*weight2[{did}]")
		else:
			file.write(f"+j[{did}]*weight2[{did}]")
	file.write(";\n")
	file.write("	"*tabnum+"data[pos1]=data_backup[pos2];\n")
	tabnum=2
	for did in range(dimension_num)[::-1]:
		file.write("	"*(tabnum+did)+"}\n")
	file.write("	}\n")
	file.write("}\n")
	file.write("\n")
	file.write("#endif")