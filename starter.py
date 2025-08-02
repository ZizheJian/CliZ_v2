# starter.py is a easy tool for running CliZ. It can be moved to any directory.
# Some modifications are required to run starter.py.
# 1. Create a file to store the information of your dataset.
# 2. Modify the "project root" variable to the root directory of CliZ.
# 3. Write your own compression procedures.

import os
from pathlib import Path
# Here is an example of how to import your dataset settings.
# You can copy "Hurricane_T.py" and rename it to your own dataset settings file.
# Make sure the file is in the "starter_setting" directory.
# And don't forget to import it here.
from starter_setting.Hurricane_T import Hurricane_T

# "project root" is the root directory of CliZ.
# Change it to where you put CliZ.
project_root="/home/x-zjian1/CliZ_v2"

# Run some code_generation.py scripts. No need to modify.
code_generation_list=["choose_method","DC","transform"]
for code_generation_folder in code_generation_list:
	code_generation_path=os.path.join(project_root,code_generation_folder)
	py_path=os.path.join(code_generation_path,"code_generation.py")
	stamp_path=os.path.join(code_generation_path,"code_generation.stamp")
	if not os.path.exists(stamp_path) or Path(py_path).stat().st_mtime>Path(stamp_path).stat().st_mtime:
		print(f"Generating code for {code_generation_folder} ...")
		current_path=os.getcwd()
		os.chdir(code_generation_path)
		os.system(f"python3 code_generation.py")
		os.system(f"touch {stamp_path}")
		os.chdir(current_path)

# Compile CliZ using makefile. No need to modify.
compile_commands=[]
compile_commands.append("make -j16")
for command in compile_commands:
	print("command=",command)
	os.system(command)

# Here you can write your own compression procedures.
execute_commands=[]
# Example: Compressing Hurricane_T
Hurricane_T_compress=Hurricane_T(project_root)
execute_commands.append(Hurricane_T_compress.get_compress_command())
# Example: Using an existing configuration and map file to compress Hurricane_T
Hurricane_T_recompress=Hurricane_T(project_root)
Hurricane_T_recompress.config_path[0]="use"
Hurricane_T_recompress.map_path[0]="use"
execute_commands.append(Hurricane_T_recompress.get_compress_command())
# Example: Decompressing Hurricane_T
Hurricane_T_decompress=Hurricane_T(project_root)
Hurricane_T_decompress.config_path[0]="use"
Hurricane_T_decompress.map_path[0]="use"
execute_commands.append(Hurricane_T_decompress.get_decompress_command())
# Example: Validating the decompressed file
Hurricane_T_validate=Hurricane_T(project_root)
execute_commands.append(Hurricane_T_validate.get_validate_command())
execute_commands.append(Hurricane_T_decompress.get_ssim_command())
for command in execute_commands:
	print("command=",command)
	os.system(command)

# if testname=="compress CESM_ATM_RELHUM":
# 	task.set_job("compress")
# 	task.add_file(input_path="~/compress/SDRBENCH-CESM-ATM-26x1800x3600/RELHUM/RELHUM_1_26_1800_3600.f32"
# 		,config=["set","~/compress/SDRBENCH-CESM-ATM-26x1800x3600/RELHUM/RELHUM_1_26_1800_3600.f32.air.cfg"]
# 		,map=["set","~/compress/SDRBENCH-CESM-ATM-26x1800x3600/RELHUM/RELHUM_1_26_1800_3600.f32.air.map"]
# 		,dimension=[["h",26],["lat",1800],["lng",3600]]
# 		,data_phy="RELHUM"
# 		,err_type="ABS"
# 		,err_bound=0.000996034
# 		#,draw_dimension=[26,["h",1800],["w",3600]]
# 		,freq=True
# 	)

# if testname=="decompress CESM_ATM_RELHUM":
# 	task.set_job("decompress")
# 	task.add_file(input_path="~/compress/SDRBENCH-CESM-ATM-26x1800x3600/RELHUM/RELHUM_1_26_1800_3600.f32.air"
# 		,config=["use","~/compress/SDRBENCH-CESM-ATM-26x1800x3600/RELHUM/RELHUM_1_26_1800_3600.f32.air.cfg"]
# 		,map=["use","~/compress/SDRBENCH-CESM-ATM-26x1800x3600/RELHUM/RELHUM_1_26_1800_3600.f32.air.map"]
# 	)


# if testname=="compress SOILLIQ+mask":
# 	task.set_job("compress")
# 	task.add_file(input_path="~/compress/b40.1850.track1.2deg/SOILLIQ.bin"
# 		,config=["set","~/compress/b40.1850.track1.2deg/SOILLIQ.bin.air.cfg"]
# 		,map=["set","~/compress/b40.1850.track1.2deg/SOILLIQ.bin.air.map"]
# 		,dimension=[["pert",360],["h",15],["lat",96],["lng",144]]
# 		,data_phy="SOILLIQ"
# 		,err_type="ABS"
# 		,err_bound=1)
# 	task.add_file(input_path="~/compress/b40.1850.track1.2deg/MASK.bin"
# 		,config=["set","~/compress/b40.1850.track1.2deg/MASK.bin.air.cfg"]
# 		,dimension=[["lat",96],["lng",144]]
# 		,data_phy="MASK"
# 		,data_type="i32")

# if testname=="decompress SOILLIQ+mask":
# 	task.set_job("decompress")
# 	task.add_file(input_path="~/compress/b40.1850.track1.2deg/SOILLIQ.bin.air"
# 		,config=["use","~/compress/b40.1850.track1.2deg/SOILLIQ.bin.air.cfg"]
# 		,map=["use","~/compress/b40.1850.track1.2deg/SOILLIQ.bin.air.map"])
# 	task.add_file(input_path="~/compress/b40.1850.track1.2deg/MASK.bin.air"
# 		,config=["use","~/compress/b40.1850.track1.2deg/MASK.bin.air.cfg"])

# # if (testname=="compress CLOUDf48.log10"):
# # 	task.add_file(job="compress"
# # 		,directory_path="~/compress/SDRBENCH-Hurricane-ISABEL-100x500x500"
# # 		,file_name="CLOUDf48.log10.bin.f32"
# # 		,dimension=[["h",100],["lat",500],["lng",500]]
# # 		,err_bound=0.001
# # 		#,draw_dimension=[["",20],["h",500],["w",500]]
# # 		,freq=True
# # 	)

# # if (testname=="decompress CLOUDf48.log10"):
# # 	task.add_file(job="decompress"
# # 		,directory_path="~/compress/SDRBENCH-Hurricane-ISABEL-100x500x500"
# # 		,file_name="CLOUDf48.log10.bin.f32.air"
# # 		#,draw_dimension=[["",24],["h",384],["w",320]]
# # 	)

# # if (testname=="compress CESM-ATM-CLDLOW_2D"):
# # 	task.add_file(job="compress"
# # 		,directory_path="~/compress/SDRBENCH-CESM-ATM-26x1800x3600/1800x3600-full"
# # 		,file_name="CLDLOW_1_1800_3600.f32"
# # 		,dimension=[["lat",1800],["lng",3600]]
# # 		,data_phy="CLD"
# # 		,err_bound=0.00001
# # 		,draw_dimension=[["h",1800],["w",3600]]
# # 		,freq=True
# # 	)

# # if (testname=="decompress CESM-ATM-CLDLOW_2D"):
# # 	task.add_file(job="decompress"
# # 		,directory_path="~/compress/SDRBENCH-CESM-ATM-26x1800x3600/1800x3600-full"
# # 		,file_name="CLDLOW_1_1800_3600.f32.air"
# # 	)

# # if (testname=="compress b.nday1.SST"):
# # 	task.add_file(job="compress"
# # 		,directory_path="~/compress/b.e11.B20TRC5CNBDRD.f09_g16.030.pop.h.nday1.SST.19200102-20051231"
# # 		,file_name="b.e11.B20TRC5CNBDRD.f09_g16.030.pop.h.nday1.SST.19200102-20051231.bin"
# # 		,dimension=[[31389],["lat",384],["lng",320]]
# # 		,data_phy="SST"
# # 		,err_bound=0.001
# # 		,draw_dimension=[[20],["h",384],["w",320]]
# # 		,freq=True
# # 	)

# if (testname=="compress b.SST+mask"):
# 	task.set_job("compress")
# 	task.add_file(input_path="~/compress/b.e11.B20TRC5CNBDRD.f09_g16.030.pop.h.SST.192001-200512/SST.bin"
# 		,config=["set","~/compress/b.e11.B20TRC5CNBDRD.f09_g16.030.pop.h.SST.192001-200512/SST.bin.air.cfg"]
# 		,map=["set","~/compress/b.e11.B20TRC5CNBDRD.f09_g16.030.pop.h.SST.192001-200512/SST.bin.air.map"]
# 		,dimension=[["pert",1032],["lat",384],["lng",320]]
# 		,data_phy="SST"
# 		,err_type="REL"
# 		,err_bound=0.001
# 		,freq=True
# 	)
# 	task.add_file(input_path="~/compress/b.e11.B20TRC5CNBDRD.f09_g16.030.pop.h.SST.192001-200512/REGION_MASK.bin"
# 		,config=["set","~/compress/b.e11.B20TRC5CNBDRD.f09_g16.030.pop.h.SST.192001-200512/REGION_MASK.bin.air.cfg"]
# 		,dimension=[["lat",384],["lng",320]]
# 		,data_type="i32"
# 		,data_phy="MASK"
# 		,freq=True
# 	)

# if (testname=="compress b.nday1.SST+mask"):
# 	task.set_job("compress")
# 	task.add_file(input_path="~/compress/b.e11.B20TRC5CNBDRD.f09_g16.030.pop.h.nday1.SST.19200102-20051231/SST.bin"
# 		,config=["set","~/compress/b.e11.B20TRC5CNBDRD.f09_g16.030.pop.h.nday1.SST.19200102-20051231/SST.bin.air.cfg"]
# 		,map=["set","~/compress/b.e11.B20TRC5CNBDRD.f09_g16.030.pop.h.nday1.SST.19200102-20051231/SST.bin.air.map"]
# 		,dimension=[["pert",31389],["lat",384],["lng",320]]
# 		,data_phy="SST"
# 		,err_type="REL"
# 		,err_bound=0.001
# 		#,draw_dimension=[20,["h",384],["w",320]]
# 		,freq=True
# 	)
# 	task.add_file(input_path="~/compress/b.e11.B20TRC5CNBDRD.f09_g16.030.pop.h.nday1.SST.19200102-20051231/REGION_MASK.bin"
# 		,config=["set","~/compress/b.e11.B20TRC5CNBDRD.f09_g16.030.pop.h.nday1.SST.19200102-20051231/REGION_MASK.bin.air.cfg"]
# 		,dimension=[["lat",384],["lng",320]]
# 		,data_type="i32"
# 		,data_phy="MASK"
# 		#,draw_dimension=[["h",384],["w",320]]
# 		,freq=True
# 	)