from task import generate_command_compress,generate_command_validate

def CESM_T():
	test_name=None
	source_path="~/compress/SDRBENCH-CESM-ATM-26x1800x3600/T/T_1_26_1800_3600.f32"
	compressed_path="~/compress/SDRBENCH-CESM-ATM-26x1800x3600/T/T_1_26_1800_3600.f32.cliz"
	decompressed_path="~/compress/SDRBENCH-CESM-ATM-26x1800x3600/T/T_1_26_1800_3600.f32.cliz.bin"
	config_path="~/compress/SDRBENCH-CESM-ATM-26x1800x3600/T/T_1_26_1800_3600.f32.cliz.cfg"
	map_path="~/compress/SDRBENCH-CESM-ATM-26x1800x3600/T/T_1_26_1800_3600.f32.cliz.map"
	#test_name="Compress"
	#test_name="Recompress"
	#test_name="Decompress"
	#test_name="Validate"
	command=None
	if test_name=="Compress":
		command=generate_command_compress(job_type="compress"
			,input_path=source_path
			,config=["set",config_path]
			,map=["force-set",map_path]
			,dimension=[["h",26],["lat",1800],["lng",3600]]
			,err=["REL",1e-3]
			,debug=True
		)
	if test_name=="Recompress":
		command=generate_command_compress(job_type="compress"
			,input_path=source_path
			,config=["use",config_path]
		)
	if test_name=="Decompress":
		command=generate_command_compress(job_type="decompress"
			,input_path=compressed_path
			,config=["use",config_path]
		)
	if test_name=="Validate":
		command=generate_command_validate(job_type="validate"
			,source_path=source_path
			,decompressed_path=decompressed_path
			,dimension=[["h",26],["lat",1800],["lng",3600]]
			,data_type="f32"
			,err=["REL",1e-3]
		)
	return command