from task import generate_command_compress,generate_command_validate

def b40_SOILLIQ():
	test_name=None
	source_path="~/compress/b40.clm2/SOILLIQ.bin"
	compressed_path="~/compress/b40.clm2/SOILLIQ.bin.cliz"
	decompressed_path="~/compress/b40.clm2/SOILLIQ.bin.cliz.bin"
	config_path="~/compress/b40.clm2/SOILLIQ.bin.cliz.cfg"
	map_path="~/compress/b40.clm2/SOILLIQ.bin.cliz.map"
	mask_path="~/compress/b40.clm2/MASK.bin"
	err=["REL",1e-7]
	dimension=[["pert",360],["h",15],["lat",96],["lng",144]]
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
			,dimension=dimension
			,err=err
			,debug=True
		)
	if test_name=="Recompress":
		command=generate_command_compress(job_type="compress"
			,input_path=source_path
			,config=["use",config_path]
			,map=["set",map_path]
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
			,dimension=dimension
			,err=err
		)
	return command