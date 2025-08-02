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