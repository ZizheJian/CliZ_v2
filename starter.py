import os
from starter_setting.Hurricane_T import Hurricane_T
from starter_setting.CESM_T import CESM_T

os.chdir("change_err_bound")
os.system("python3 code_generation.py")
os.chdir("..")
os.chdir("DC")
os.system("python3 code_generation.py")
os.chdir("..")
os.chdir("transform")
os.system("python3 code_generation.py")
os.chdir("..")

datasets=[Hurricane_T,CESM_T]
commands=[]

#testname="compress CESM_ATM_RELHUM"
#testname="decompress CESM_ATM_RELHUM"
#testname="compress SOILLIQ+mask"
#testname="decompress SOILLIQ+mask"
#testname="compress b.SSH"
#testname="decompress b.SSH"
#testname="compress b.SSH+mask"
#testname="decompress b.SSH+mask"
#testname="compress CLOUDf48.log10"
#testname="decompress CLOUDf48.log10"
#testname="compress CESM-ATM-T"
#testname="decompress CESM-ATM-T"
#testname="compress CESM-ATM-CLDLOW_2D"
#testname="decompress CESM-ATM-CLDLOW_2D"
#testname="compress b.nday1.SST"
#testname="compress b.SST+mask"
#testname="compress b.nday1.SST+mask"
#testname="api test"

for dataset in datasets:
	command=dataset()
	if command!=None:
		commands.append(command)
if (len(commands)!=1):
	print("Error: More than one tasks are selected.")
	exit()
os.system("make")
print("command=",commands[0])
os.system(commands[0])

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

# if (testname=="compress b.SSH"):
# 	task.set_job("compress")
# 	task.add_file(input_path="~/compress/b.e11.B20TRC5CNBDRD.f09_g16.030.pop.h.SSH.192001-200512/SSH.bin"
# 		,config=["set","~/compress/b.e11.B20TRC5CNBDRD.f09_g16.030.pop.h.SSH.192001-200512/SSH.bin.air.cfg"]
# 		,map=["set","~/compress/b.e11.B20TRC5CNBDRD.f09_g16.030.pop.h.SSH.192001-200512/SSH.bin.air.map"]
# 		,dimension=[["t",1032],["lat",384],["lng",320]]
# 		,data_phy="SSH"
# 		,err_type="ABS"
# 		,err_bound=0.4
# 		#,draw_dimension=[20,["h",384],["w",320]]
# 		,freq=True
# 	)

# # if (testname=="decompress b.SSH"):
# # 	task.add_file(job="decompress"
# # 		,directory_path="~/compress/b.e11.B20TRC5CNBDRD.f09_g16.030.pop.h.SSH.192001-200512"
# # 		,file_name="b.e11.B20TRC5CNBDRD.f09_g16.030.pop.h.SSH.192001-200512.bin.air"
# # 		#,draw_dimension=[["",24],["h",384],["w",320]]
# # 	)

# if (testname=="compress b.SSH+mask"):
# 	task.set_job("compress")
# 	task.add_file(input_path="~/compress/b.e11.B20TRC5CNBDRD.f09_g16.030.pop.h.SSH.192001-200512/SSH.bin"
# 		,config=["set","~/compress/b.e11.B20TRC5CNBDRD.f09_g16.030.pop.h.SSH.192001-200512/SSH.bin.air.cfg"]
# 		#,map=["set","~/compress/b.e11.B20TRC5CNBDRD.f09_g16.030.pop.h.SSH.192001-200512/SSH.bin.air.map"]
# 		,dimension=[["pert",1032],["lat",384],["lng",320]]
# 		,data_phy="SSH"
# 		,err_type="ABS"
# 		,err_bound=0.0000414172318
# 		#,draw_dimension=[20,["h",384],["w",320]]
# 		#,freq=True
# 	)
# 	task.add_file(input_path="~/compress/b.e11.B20TRC5CNBDRD.f09_g16.030.pop.h.SSH.192001-200512/REGION_MASK.bin"
# 		,config=["set","~/compress/b.e11.B20TRC5CNBDRD.f09_g16.030.pop.h.SSH.192001-200512/REGION_MASK.bin.air.cfg"]
# 		,dimension=[["lat",384],["lng",320]]
# 		,data_type="i32"
# 		,data_phy="MASK"
# 		#,draw_dimension=[["h",384],["w",320]]
# 		#,freq=True
# 	)

# if (testname=="decompress b.SSH+mask"):
# 	task.set_job("decompress")
# 	task.add_file(input_path="~/compress/b.e11.B20TRC5CNBDRD.f09_g16.030.pop.h.SSH.192001-200512/SSH.bin.air"
# 		,config=["use","~/compress/b.e11.B20TRC5CNBDRD.f09_g16.030.pop.h.SSH.192001-200512/SSH.bin.air.cfg"]
# 		,map=["use","~/compress/b.e11.B20TRC5CNBDRD.f09_g16.030.pop.h.SSH.192001-200512/SSH.bin.air.map"]
# 	)
# 	task.add_file(input_path="~/compress/b.e11.B20TRC5CNBDRD.f09_g16.030.pop.h.SSH.192001-200512/REGION_MASK.bin.air"
# 		,config=["use","~/compress/b.e11.B20TRC5CNBDRD.f09_g16.030.pop.h.SSH.192001-200512/REGION_MASK.bin.air.cfg"]
# 		#,draw_dimension=[["h",384],["w",320]]
# 	)

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

# if (testname=="api test"):
# 	os.system("make")
# 	os.system("./api_example")

# task.run()