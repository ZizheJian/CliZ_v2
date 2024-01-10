for dimension_num in [1,2,3,4]:
	for map in ["_data","_map","_data_set_map","_data_use_map","_data_mask"]:
		if map=="_data_mask":
			mask="_mask"
		else:
			mask=""
		file=open(f"DC_{dimension_num}D_linear{map}.cpp","w")
		file.write(f"#ifndef __DC_{dimension_num}D_LINEAR{map.upper()}_CPP__\n")
		file.write(f"#define __DC_{dimension_num}D_LINEAR{map.upper()}_CPP__\n")
		file.write("\n")
		file.write("#include \"DC.hpp2\"\n")
		file.write("\n")
		file.write("namespace cliz\n")
		file.write("{\n")
		file.write("	template<typename T>\n")
		file.write(f"	void task_c<T>::DC_{dimension_num}D_linear{map}()\n")
		file.write("	{\n")
		file.write("		long long *mx=best_it1->mx;\n")
		file.write("		long long *weight=best_it1->weight;\n")
		file.write("		int interpolation_level=0;\n")
		file.write(f"		for (int i=0;i<{dimension_num};i++)\n")
		file.write("			interpolation_level=max(interpolation_level,(int)ceil(log2(mx[i])));\n")
		file.write("		quant_bin_num=0;\n")
		if mask=="_mask":
			file.write("		if (mask_data[pos2horiz_mapping[0]]!=0)\n")
			file.write("		{\n")
			tabnum=3
		if mask=="":
			tabnum=2
		file.write("	"*tabnum+"#ifdef JOB_TYPE_COMPRESS\n")
		if map=="_data":
			file.write("	"*tabnum+"	quant_bin[quant_bin_num]=quantize(0,0);\n")
		if map=="_map":
			file.write("	"*tabnum+f"	printf(\"Error: DC_{dimension_num}D_linear{map} shouldn't be called during compression.\\n\");\n")
			file.write("	"*tabnum+"	exit(0);\n")
		if map=="_data_set_map":
			file.write("	"*tabnum+"	quant_bin[quant_bin_num]=quantize(0,0);\n")
			file.write("	"*tabnum+"	qb2horiz_mapping[quant_bin_num]=pos2horiz_mapping[0];\n")
			file.write("	"*tabnum+"	if (abs(quant_bin[quant_bin_num])<=2)\n")
			file.write("	"*tabnum+"		horiz_hist[qb2horiz_mapping[quant_bin_num]*5+quant_bin[quant_bin_num]+2]++;\n")
		if map=="_data_use_map":
			file.write("	"*tabnum+"	quant_bin[quant_bin_num]=quantize(0,0);\n")
			file.write("	"*tabnum+"	qb2horiz_mapping[quant_bin_num]=pos2horiz_mapping[0];\n")
		if map=="_data_mask":
			file.write("	"*tabnum+"	quant_bin[quant_bin_num]=quantize(0,0);\n")
		file.write("	"*tabnum+"#endif\n")
		file.write("	"*tabnum+"#ifdef JOB_TYPE_DECOMPRESS\n")
		if map=="_data":
			file.write("	"*tabnum+"	data[0]=dequantize(quant_bin_num,0);\n")
		if map=="_map":
			file.write("	"*tabnum+"	qb2horiz_mapping[quant_bin_num]=pos2horiz_mapping[0];\n")
		if map=="_data_set_map" or map=="_data_use_map":
			file.write("	"*tabnum+f"	printf(\"Error: DC_{dimension_num}D_linear{map} shouldn't be called during decompression.\\n\");\n")
			file.write("	"*tabnum+"	exit(0);\n")
		if map=="_data_mask":
			file.write("	"*tabnum+"	data[0]=dequantize(quant_bin_num,0);\n")
		file.write("	"*tabnum+"#endif\n")
		if mask=="_mask":
			file.write("	"*tabnum+"quant_bin_num++;\n")
			file.write("		}\n")
		if mask=="":
			file.write("		quant_bin_num++;\n")
		file.write("		double err_bound_backup=err_bound;\n")
		file.write("		for (int lv=interpolation_level-1;lv>=0;lv--)\n")
		file.write("		{\n")
		file.write("			if (lv>=2)\n")
		file.write("				err_bound=err_bound_backup*0.5;\n")
		file.write("			else\n")
		file.write("				err_bound=err_bound_backup;\n")
		file.write("			err_bound_reciprocal=1/err_bound;\n")
		file.write("			long long stride=1<<lv;\n")
		tabnum=3
		for bid in range(dimension_num):
			file.write("	"*(tabnum+bid)+f"for (long long b{bid}b=0;b{bid}b<mx[{bid}];b{bid}b+=stride*32)\n")
			file.write("	"*(tabnum+bid)+"{\n")
			file.write("	"*(tabnum+bid+1)+f"long long b{bid}e=min(mx[{bid}]-1,b{bid}b+stride*32);\n")
		tabnum=3+dimension_num
		for direction in range(dimension_num):
			for other_did,other_dim in enumerate(x for x in range(dimension_num) if x!=direction):
				if other_dim>direction:
					file.write("	"*(tabnum+other_did)+f"for (long long i{other_dim}=(b{other_dim}b?b{other_dim}b+2*stride:0);i{other_dim}<=b{other_dim}e;i{other_dim}+=2*stride)\n")
				else:
					file.write("	"*(tabnum+other_did)+f"for (long long i{other_dim}=(b{other_dim}b?b{other_dim}b+stride:0);i{other_dim}<=b{other_dim}e;i{other_dim}+=stride)\n")
			if dimension_num==1:
				file.write("	"*(tabnum+dimension_num-1)+"long long pos=0;\n")
			else:
				file.write("	"*(tabnum+dimension_num-2)+"{\n")
				file.write("	"*(tabnum+dimension_num-1)+"long long pos=")
				for other_did,other_dim in enumerate(x for x in range(dimension_num) if x!=direction):
					if other_did==0:
						file.write(f"i{other_dim}*weight[{other_dim}]")
					else:
						file.write(f"+i{other_dim}*weight[{other_dim}]")
				file.write(";\n")
			file.write("	"*(tabnum+dimension_num-1)+f"for (long long i{direction}=b{direction}b+stride;i{direction}<=b{direction}e;i{direction}+=2*stride)\n")
			file.write("	"*(tabnum+dimension_num-1)+"{\n")
			tabnum=3+dimension_num*2
			if map=="_data_mask":
				file.write("	"*tabnum+f"if (mask_data[pos2horiz_mapping[pos+i{direction}*weight[{direction}]]]==0)\n")
				file.write("	"*tabnum+f"	continue;\n")
			file.write("	"*tabnum+"T pred;\n")
			file.write("	"*tabnum+f"if (i{direction}+stride<=b{direction}e)\n")
			file.write("	"*tabnum+f"	pred=linear_fitting_dpd{mask}(pos+i{direction}*weight[{direction}],stride*weight[{direction}]);\n")
			file.write("	"*tabnum+"else\n")
			file.write("	"*tabnum+f"	if (i{direction}-3*stride>=b{direction}b)\n")
			file.write("	"*tabnum+f"		pred=linear_fitting_ddp{mask}(pos+i{direction}*weight[{direction}],stride*weight[{direction}]);\n")
			file.write("	"*tabnum+"	else\n")
			file.write("	"*tabnum+f"		pred=constant_fitting_dp{mask}(pos+i{direction}*weight[{direction}],stride*weight[{direction}]);\n")
			file.write("	"*tabnum+f"#ifdef JOB_TYPE_COMPRESS\n")
			if map=="_data" or map=="_data_mask":
				file.write("	"*tabnum+f"	quant_bin[quant_bin_num]=quantize(pos+i{direction}*weight[{direction}],pred);\n")
			if map=="_map":
				file.write(f"			printf(\"Error: DC_{dimension_num}D_linear{map} shouldn't be called during compression.\\n\");\n")
				file.write(f"			exit(0);\n")
			if map=="_data_set_map":
				file.write("	"*tabnum+f"	short qb=quantize(pos+i{direction}*weight[{direction}],pred);\n")
				file.write("	"*tabnum+f"	quant_bin[quant_bin_num]=qb;\n")
				file.write("	"*tabnum+f"	long long horiz=pos2horiz_mapping[pos+i{direction}*weight[{direction}]];\n")
				file.write("	"*tabnum+f"	qb2horiz_mapping[quant_bin_num]=horiz;\n")
				file.write("	"*tabnum+f"	if (abs(qb)<=2)\n")
				file.write("	"*tabnum+f"		horiz_hist[horiz*5+qb+2]++;\n")
			if map=="_data_use_map":
				file.write("	"*tabnum+f"	quant_bin[quant_bin_num]=quantize(pos+i{direction}*weight[{direction}],pred);\n")
				file.write("	"*tabnum+f"	qb2horiz_mapping[quant_bin_num]=pos2horiz_mapping[pos+i{direction}*weight[{direction}]];\n")
			file.write("	"*tabnum+f"#endif\n")
			file.write("	"*tabnum+f"#ifdef JOB_TYPE_DECOMPRESS\n")
			if map=="_data" or map=="_data_mask":
				file.write("	"*tabnum+f"	data[pos+i{direction}*weight[{direction}]]=dequantize(quant_bin_num,pred);\n")
			if map=="_map":
				file.write("	"*tabnum+f"	qb2horiz_mapping[quant_bin_num]=pos2horiz_mapping[pos+i{direction}*weight[{direction}]];\n")
			if map=="_data_set_map" or map=="_data_use_map":
				file.write("	"*tabnum+f"	printf(\"Error: DC_{dimension_num}D_linear{map} shouldn't be called during decompression.\\n\");\n")
				file.write("	"*tabnum+f"	exit(0);\n")
			file.write("	"*tabnum+f"#endif\n")
			file.write("	"*tabnum+f"quant_bin_num++;\n")
			tabnum=3+dimension_num
			file.write("	"*(tabnum+dimension_num-1)+"}\n")
			if dimension_num!=1:
				file.write("	"*(tabnum+dimension_num-2)+"}\n")
		tabnum=3
		for bid in range(dimension_num)[::-1]:
			file.write("	"*(tabnum+bid)+"}\n")
		file.write("		}\n")
		file.write("	}\n")
		file.write("}\n")
		file.write("\n")
		file.write("#endif")
		file.close()

for dimension_num in [1,2,3,4]:
	for map in ["_data","_map","_data_set_map","_data_use_map","_data_mask"]:
		if map=="_data_mask":
			mask="_mask"
		else:
			mask=""
		file=open(f"DC_{dimension_num}D_cubic{map}.cpp","w")
		file.write(f"#ifndef __DC_{dimension_num}D_CUBIC{map.upper()}_CPP__\n")
		file.write(f"#define __DC_{dimension_num}D_CUBIC{map.upper()}_CPP__\n")
		file.write("\n")
		file.write("#include \"DC.hpp2\"\n")
		file.write("\n")
		file.write("namespace cliz\n")
		file.write("{\n")
		file.write("	template<typename T>\n")
		file.write(f"	void task_c<T>::DC_{dimension_num}D_cubic{map}()\n")
		file.write("	{\n")
		file.write("		long long *mx=best_it1->mx;\n")
		file.write("		long long *weight=best_it1->weight;\n")
		file.write("		int interpolation_level=0;\n")
		file.write(f"		for (int i=0;i<{dimension_num};i++)\n")
		file.write("			interpolation_level=max(interpolation_level,(int)ceil(log2(mx[i])));\n")
		file.write("		quant_bin_num=0;\n")
		if mask=="_mask":
			file.write("		if (mask_data[pos2horiz_mapping[0]]!=0)\n")
			file.write("		{\n")
			tabnum=3
		if mask=="":
			tabnum=2
		file.write("	"*tabnum+"#ifdef JOB_TYPE_COMPRESS\n")
		if map=="_data":
			file.write("	"*tabnum+"	quant_bin[quant_bin_num]=quantize(0,0);\n")
		if map=="_map":
			file.write("	"*tabnum+f"	printf(\"Error: DC_{dimension_num}D_linear{map} shouldn't be called during compression.\\n\");\n")
			file.write("	"*tabnum+"	exit(0);\n")
		if map=="_data_set_map":
			file.write("	"*tabnum+"	quant_bin[quant_bin_num]=quantize(0,0);\n")
			file.write("	"*tabnum+"	qb2horiz_mapping[quant_bin_num]=pos2horiz_mapping[0];\n")
			file.write("	"*tabnum+"	if (abs(quant_bin[quant_bin_num])<=2)\n")
			file.write("	"*tabnum+"		horiz_hist[qb2horiz_mapping[quant_bin_num]*5+quant_bin[quant_bin_num]+2]++;\n")
		if map=="_data_use_map":
			file.write("	"*tabnum+"	quant_bin[quant_bin_num]=quantize(0,0);\n")
			file.write("	"*tabnum+"	qb2horiz_mapping[quant_bin_num]=pos2horiz_mapping[0];\n")
		if map=="_data_mask":
			file.write("	"*tabnum+"	quant_bin[quant_bin_num]=quantize(0,0);\n")
		file.write("	"*tabnum+"#endif\n")
		file.write("	"*tabnum+"#ifdef JOB_TYPE_DECOMPRESS\n")
		if map=="_data":
			file.write("	"*tabnum+"	data[0]=dequantize(quant_bin_num,0);\n")
		if map=="_map":
			file.write("	"*tabnum+"	qb2horiz_mapping[quant_bin_num]=pos2horiz_mapping[0];\n")
		if map=="_data_set_map" or map=="_data_use_map":
			file.write("	"*tabnum+f"	printf(\"Error: DC_{dimension_num}D_linear{map} shouldn't be called during decompression.\\n\");\n")
			file.write("	"*tabnum+"	exit(0);\n")
		if map=="_data_mask":
			file.write("	"*tabnum+"	data[0]=dequantize(quant_bin_num,0);\n")
		file.write("	"*tabnum+"#endif\n")
		if mask=="_mask":
			file.write("	"*tabnum+"quant_bin_num++;\n")
			file.write("		}\n")
		if mask=="":
			file.write("		quant_bin_num++;\n")
		file.write("		double err_bound_backup=err_bound;\n")
		file.write("		for (int lv=interpolation_level-1;lv>=0;lv--)\n")
		file.write("		{\n")
		file.write("			if (lv>=2)\n")
		file.write("				err_bound=err_bound_backup*0.5;\n")
		file.write("			else\n")
		file.write("				err_bound=err_bound_backup;\n")
		file.write("			err_bound_reciprocal=1/err_bound;\n")
		file.write("			long long stride=1<<lv;\n")
		tabnum=3
		for direction in range(dimension_num):
			for other_did,other_dim in enumerate(x for x in range(dimension_num) if x!=direction):
				if other_dim>direction:
					file.write("	"*(tabnum+other_did)+f"for (long long i{other_dim}=0;i{other_dim}<mx[{other_dim}];i{other_dim}+=2*stride)\n")
				else:
					file.write("	"*(tabnum+other_did)+f"for (long long i{other_dim}=0;i{other_dim}<mx[{other_dim}];i{other_dim}+=stride)\n")
			if dimension_num==1:
				file.write("	"*(tabnum+dimension_num-1)+"long long pos=0;\n")
			else:
				file.write("	"*(tabnum+dimension_num-2)+"{\n")
				file.write("	"*(tabnum+dimension_num-1)+"long long pos=")
				for other_did,other_dim in enumerate(x for x in range(dimension_num) if x!=direction):
					if other_did==0:
						file.write(f"i{other_dim}*weight[{other_dim}]")
					else:
						file.write(f"+i{other_dim}*weight[{other_dim}]")
				file.write(";\n")
			file.write("	"*(tabnum+dimension_num-1)+f"for (long long i{direction}=stride;i{direction}<mx[{direction}];i{direction}+=2*stride)\n")
			file.write("	"*(tabnum+dimension_num-1)+"{\n")
			tabnum=3+dimension_num
			if map=="_data_mask":
				file.write("	"*tabnum+f"if (mask_data[pos2horiz_mapping[pos+i{direction}*weight[{direction}]]]==0)\n")
				file.write("	"*tabnum+f"	continue;\n")
			file.write("	"*tabnum+"T pred;\n")
			file.write("	"*tabnum+f"if (i{direction}+3*stride<mx[{direction}])\n")
			file.write("	"*tabnum+f"	if (i{direction}-3*stride>=0)\n")
			file.write("	"*tabnum+f"		pred=cubic_fitting_ddpdd{mask}(pos+i{direction}*weight[{direction}],stride*weight[{direction}]);\n")
			file.write("	"*tabnum+f"	else\n")
			file.write("	"*tabnum+f"		pred=quadratic_fitting_ddpd{mask}(pos+i{direction}*weight[{direction}],-stride*weight[{direction}]);\n")
			file.write("	"*tabnum+f"else\n")
			file.write("	"*tabnum+f"	if (i{direction}+stride<mx[{direction}])\n")
			file.write("	"*tabnum+f"		if (i{direction}-3*stride>=0)\n")
			file.write("	"*tabnum+f"			pred=quadratic_fitting_ddpd{mask}(pos+i{direction}*weight[{direction}],stride*weight[{direction}]);\n")
			file.write("	"*tabnum+f"		else\n")
			file.write("	"*tabnum+f"			pred=linear_fitting_dpd{mask}(pos+i{direction}*weight[{direction}],stride*weight[{direction}]);\n")
			file.write("	"*tabnum+f"	else\n")
			file.write("	"*tabnum+f"		if (i{direction}-5*stride>=0)\n")
			file.write("	"*tabnum+f"			pred=quadratic_fitting_dddp{mask}(pos+i{direction}*weight[{direction}],stride*weight[{direction}]);\n")
			file.write("	"*tabnum+f"		else\n")
			file.write("	"*tabnum+f"			if (i{direction}-3*stride>=0)\n")
			file.write("	"*tabnum+f"				pred=linear_fitting_ddp{mask}(pos+i{direction}*weight[{direction}],stride*weight[{direction}]);\n")
			file.write("	"*tabnum+f"			else\n")
			file.write("	"*tabnum+f"				pred=constant_fitting_dp{mask}(pos+i{direction}*weight[{direction}],stride*weight[{direction}]);\n")
			file.write("	"*tabnum+f"#ifdef JOB_TYPE_COMPRESS\n")
			if map=="_data" or map=="_data_mask":
				file.write("	"*tabnum+f"	quant_bin[quant_bin_num]=quantize(pos+i{direction}*weight[{direction}],pred);\n")
			if map=="_map":
				file.write(f"			printf(\"Error: DC_{dimension_num}D_linear{map} shouldn't be called during compression.\\n\");\n")
				file.write(f"			exit(0);\n")
			if map=="_data_set_map":
				file.write("	"*tabnum+f"	short qb=quantize(pos+i{direction}*weight[{direction}],pred);\n")
				file.write("	"*tabnum+f"	quant_bin[quant_bin_num]=qb;\n")
				file.write("	"*tabnum+f"	long long horiz=pos2horiz_mapping[pos+i{direction}*weight[{direction}]];\n")
				file.write("	"*tabnum+f"	qb2horiz_mapping[quant_bin_num]=horiz;\n")
				file.write("	"*tabnum+f"	if (abs(qb)<=2)\n")
				file.write("	"*tabnum+f"		horiz_hist[horiz*5+qb+2]++;\n")
			if map=="_data_use_map":
				file.write("	"*tabnum+f"	quant_bin[quant_bin_num]=quantize(pos+i{direction}*weight[{direction}],pred);\n")
				file.write("	"*tabnum+f"	qb2horiz_mapping[quant_bin_num]=pos2horiz_mapping[pos+i{direction}*weight[{direction}]];\n")
			file.write("	"*tabnum+f"#endif\n")
			file.write("	"*tabnum+f"#ifdef JOB_TYPE_DECOMPRESS\n")
			if map=="_data" or map=="_data_mask":
				file.write("	"*tabnum+f"	data[pos+i{direction}*weight[{direction}]]=dequantize(quant_bin_num,pred);\n")
			if map=="_map":
				file.write("	"*tabnum+f"	qb2horiz_mapping[quant_bin_num]=pos2horiz_mapping[pos+i{direction}*weight[{direction}]];\n")
			if map=="_data_set_map" or map=="_data_use_map":
				file.write("	"*tabnum+f"	printf(\"Error: DC_{dimension_num}D_linear{map} shouldn't be called during decompression.\\n\");\n")
				file.write("	"*tabnum+f"	exit(0);\n")
			file.write("	"*tabnum+f"#endif\n")
			file.write("	"*tabnum+f"quant_bin_num++;\n")
			tabnum=3
			file.write("	"*(tabnum+dimension_num-1)+"}\n")
			if dimension_num!=1:
				file.write("	"*(tabnum+dimension_num-2)+"}\n")
		file.write("		}\n")
		file.write("	}\n")
		file.write("}\n")
		file.write("\n")
		file.write("#endif")
		file.close()