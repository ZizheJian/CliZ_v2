from task import generate_command_compress,generate_command_validate

def b_e11_SSH():
	test_name=None
	source_path="~/compress/b.e11.B20TRC5CNBDRD.f09_g16.030.pop.h.SSH.192001-200512/SSH.bin"
	compressed_path="~/compress/b.e11.B20TRC5CNBDRD.f09_g16.030.pop.h.SSH.192001-200512/SSH.bin.cliz"
	decompressed_path="~/compress/b.e11.B20TRC5CNBDRD.f09_g16.030.pop.h.SSH.192001-200512/SSH.bin.cliz.bin"
	config_path="~/compress/b.e11.B20TRC5CNBDRD.f09_g16.030.pop.h.SSH.192001-200512/SSH.bin.cliz.cfg"
	map_path="~/compress/b.e11.B20TRC5CNBDRD.f09_g16.030.pop.h.SSH.192001-200512/SSH.bin.cliz.map"
	mask_path="~/compress/b.e11.B20TRC5CNBDRD.f09_g16.030.pop.h.SSH.192001-200512/REGION_MASK.bin"
	#test_name="Compress"
	test_name="Recompress"
	#test_name="Decompress"
	#test_name="Validate"
	command=None
	if test_name=="Compress":
		command=generate_command_compress(job_type="compress"
			,input_path=source_path
			,config=["set",config_path]
			#,map=["set",map_path]
			,mask=mask_path
			,dimension=[["t",1032],["lat",384],["lng",320]]
			,err=["REL",1e-3]
			,debug=True
		)
	if test_name=="Recompress":
		command=generate_command_compress(job_type="compress"
			,input_path=source_path
			,config=["use",config_path]
			,map=["set",map_path]
			,mask=mask_path
		)
	if test_name=="Decompress":
		command=generate_command_compress(job_type="decompress"
			,input_path=compressed_path
			,config=["use",config_path]
			#,map=["use",map_path]
			,mask=mask_path
		)
	if test_name=="Validate":
		command=generate_command_validate(job_type="validate"
			,source_path=source_path
			,decompressed_path=decompressed_path
			,mask_path=mask_path
			,dimension=[["t",1032],["lat",384],["lng",320]]
			,err=["REL",1e-3]
		)
	return command