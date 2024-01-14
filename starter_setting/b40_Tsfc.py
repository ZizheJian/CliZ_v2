from task import generate_command_compress,generate_command_validate

def b40_Tsfc():
	test_name=None
	source_path="~/compress/b40.cice/Tsfc.bin"
	compressed_path="~/compress/b40.cice/Tsfc.bin.cliz"
	decompressed_path="~/compress/b40.cice/Tsfc.bin.cliz.bin"
	config_path="~/compress/b40.cice/Tsfc.bin.cliz.cfg"
	map_path="~/compress/b40.cice/Tsfc.bin.cliz.map"
	mask_path="~/compress/b40.cice/tmask.bin"
	err=["REL",1e-7]
	#test_name="Compress"
	#test_name="Recompress"
	#test_name="Decompress"
	#test_name="Validate"
	command=None
	if test_name=="Compress":
		command=generate_command_compress(job_type="compress"
			,input_path=source_path
			,config=["set",config_path]
			,map=["set",map_path]
			,mask_path=mask_path
			,dimension=[["pert",360],["lat",384],["lng",320]]
			,err=err
			,debug=True
		)
	if test_name=="Recompress":
		command=generate_command_compress(job_type="compress"
			,input_path=source_path
			,config=["use",config_path]
			,map=["use",map_path]
			,mask_path=mask_path
		)
	if test_name=="Decompress":
		command=generate_command_compress(job_type="decompress"
			,input_path=compressed_path
			,config=["use",config_path]
			,map=["use",map_path]
			,mask_path=mask_path
		)
	if test_name=="Validate":
		command=generate_command_validate(job_type="validate"
			,source_path=source_path
			,decompressed_path=decompressed_path
			,mask_path=mask_path
			,dimension=[["t",360],["lat",384],["lng",320]]
			,err=err
		)
	return command