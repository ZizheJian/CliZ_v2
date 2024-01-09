for dimension_num in [1,2,3,4]:
	for map in ["_data","_map","_data_map"]:
		file=open(f"transpose{map}_{dimension_num}D.cpp","w")
		file.write(f"#ifndef __TRANSPOSE{map.upper()}_{dimension_num}D_CPP__\n")
		file.write(f"#define __TRANSPOSE{map.upper()}_{dimension_num}D_CPP__\n")
		file.write("\n")
		file.write("#include \"transform.hpp2\"\n")
		file.write("\n")
		file.write("namespace cliz\n")
		file.write("{\n")
		file.write("	template<typename T>\n")
		if map=="_data":
			file.write(f"	void task_c<T>::transpose{map}_{dimension_num}D(T *data_backup)\n")
		if map=="_map":
			file.write(f"	void task_c<T>::transpose{map}_{dimension_num}D(long long *pos2horiz_mapping_backup)\n")
		if map=="_data_map":
			file.write(f"	void task_c<T>::transpose{map}_{dimension_num}D(T *data_backup,long long *pos2horiz_mapping_backup)\n")
		file.write("	{\n")
		file.write("		int *dim_seq=best_it1->dim_seq;\n")
		file.write("		long long *mx2=it2->mx;\n")
		file.write("		long long *weight2=it2->weight;\n")
		file.write("		long long *mx1=new_data<long long>(it2->n);\n")
		file.write("		for (int did=0;did<it2->n;did++)\n")
		file.write("			mx1[did]=mx2[dim_seq[did]];\n")
		file.write("		long long *weight1=new_data<long long>(it2->n);\n")
		file.write("		for (int did=it2->n-1;did>=0;did--)\n")
		file.write("			if (did==it2->n-1)\n")
		file.write("				weight1[did]=1;\n")
		file.write("			else\n")
		file.write("				weight1[did]=weight1[did+1]*mx1[did+1];\n")
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
		if map=="_data":
			file.write("	"*tabnum+"data[pos1]=data_backup[pos2];\n")
		if map=="_map":
			file.write("	"*tabnum+"pos2horiz_mapping[pos1]=pos2horiz_mapping_backup[pos2];\n")
		if map=="_data_map":
			file.write("	"*tabnum+"data[pos1]=data_backup[pos2];\n")
			file.write("	"*tabnum+"pos2horiz_mapping[pos1]=pos2horiz_mapping_backup[pos2];\n")
		tabnum=2
		for did in range(dimension_num)[::-1]:
			file.write("	"*(tabnum+did)+"}\n")
		file.write("		delete_data(mx1);\n")
		file.write("		delete_data(weight1);\n")
		file.write("		delete_data(i);\n")
		file.write("		delete_data(j);\n")
		file.write("	}\n")
		file.write("}\n")
		file.write("\n")
		file.write("#endif")

for dimension_num in [1,2,3,4]:
	file=open(f"anti_transpose_data_{dimension_num}D.cpp","w")
	file.write(f"#ifndef __ANTI_TRANSPOSE_DATA_{dimension_num}D_CPP__\n")
	file.write(f"#define __ANTI_TRANSPOSE_DATA_{dimension_num}D_CPP__\n")
	file.write("\n")
	file.write("#include \"transform.hpp2\"\n")
	file.write("\n")
	file.write("namespace cliz\n")
	file.write("{\n")
	file.write("	template<typename T>\n")
	file.write(f"	void task_c<T>::anti_transpose_data_{dimension_num}D(T *data_backup)\n")
	file.write("	{\n")
	file.write("		int *dim_seq=best_it1->dim_seq;\n")
	file.write("		long long *mx2=it2->mx;\n")
	file.write("		long long *weight2=it2->weight;\n")
	file.write("		long long *mx1=new_data<long long>(it2->n);\n")
	file.write("		for (int did=0;did<it2->n;did++)\n")
	file.write("			mx1[did]=mx2[dim_seq[did]];\n")
	file.write("		long long *weight1=new_data<long long>(it2->n);\n")
	file.write("		for (int did=it2->n-1;did>=0;did--)\n")
	file.write("			if (did==it2->n-1)\n")
	file.write("				weight1[did]=1;\n")
	file.write("			else\n")
	file.write("				weight1[did]=weight1[did+1]*mx1[did+1];\n")
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
	file.write("	"*tabnum+"data[pos2]=data_backup[pos1];\n")
	tabnum=2
	for did in range(dimension_num)[::-1]:
		file.write("	"*(tabnum+did)+"}\n")
	file.write("		delete_data(mx1);\n")
	file.write("		delete_data(weight1);\n")
	file.write("		delete_data(i);\n")
	file.write("		delete_data(j);\n")
	file.write("	}\n")
	file.write("}\n")
	file.write("\n")
	file.write("#endif")