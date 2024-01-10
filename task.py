def generate_command_compress(job_type,input_path,output_path=None,config=None,map=None,mask=None,dimension=None,data_type=None,err=None,debug=False):
	command="./cliz_"+job_type
	command+=" -in "+input_path
	if (output_path!=None):
		command+=" -out "+output_path
	if (config!=None):
		command+=" -"+config[0]+"-cfg "+config[1]
	if (map!=None):
		command+=" -"+map[0]+"-map "+map[1]
	if (mask!=None):
		command+=" -mask "+mask
	if (dimension!=None):
		command+=" -dim"
		for i in range(len(dimension)):
			if type(dimension[i])==list:
				if len(dimension[i])==2:
					command+=" "+dimension[i][0]+str(dimension[i][1])
				else:
					command+=" "+str(dimension[i][0])
			else:
				command+=" "+str(dimension[i])
	if data_type!=None:
		command+=" -type "+data_type
	if err!=None:
		if type(err)!=list:
			command+=" -err "+str(err)
		else:
			if len(err)==1:
				command+=" -err "+str(err[0])
			else:
				command+=" -err "+err[0]+str(err[1])
	if debug:
		command+=" -debug"
	return command

def generate_command_validate(job_type,source_path,decompressed_path=None,dimension=None,data_type=None,err=None):
	command="./cliz_"+job_type
	command+=" -src "+source_path
	if decompressed_path!=None:
		command+=" -dec "+decompressed_path
	if dimension!=None:
		command+=" -dim"
		for i in range(len(dimension)):
			if type(dimension[i])==list:
				if len(dimension[i])==2:
					command+=" "+dimension[i][0]+str(dimension[i][1])
				else:
					command+=" "+str(dimension[i][0])
			else:
				command+=" "+str(dimension[i])
	if data_type!=None:
		command+=" -type "+data_type
	if err!=None:
		if type(err)!=list:
			command+=" -err "+str(err)
		else:
			if len(err)==1:
				command+=" -err "+str(err[0])
			else:
				command+=" -err "+err[0]+str(err[1])
	return command