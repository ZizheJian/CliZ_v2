from task import generate_command

def Hurricane_T():
    #test_name="Compress Hurricane_T"
    #test_name="Recompress Hurricane_T"
    test_name="Decompress Hurricane_T"
    command=None
    if test_name=="Compress Hurricane_T":
        command=generate_command(job_type="compress"
            ,input_path="~/compress/SDRBENCH-Hurricane-ISABEL-100x500x500/TCf48.bin.f32"
            ,config=["set","~/compress/SDRBENCH-Hurricane-ISABEL-100x500x500/TCf48.bin.f32.cliz.cfg"]
            ,map=["set","~/compress/SDRBENCH-Hurricane-ISABEL-100x500x500/TCf48.bin.f32.cliz.map"]
            ,dimension=[["h",100],["lat",500],["lng",500]]
            ,err=["REL",1e-3]
            ,debug=True
        )
    if test_name=="Recompress Hurricane_T":
        command=generate_command(job_type="compress"
            ,input_path="~/compress/SDRBENCH-Hurricane-ISABEL-100x500x500/TCf48.bin.f32"
            ,config=["use","~/compress/SDRBENCH-Hurricane-ISABEL-100x500x500/TCf48.bin.f32.cliz.cfg"]
        )
    if test_name=="Decompress Hurricane_T":
        command=generate_command(job_type="decompress"
            ,input_path="~/compress/SDRBENCH-Hurricane-ISABEL-100x500x500/TCf48.bin.f32.cliz"
            ,config=["use","~/compress/SDRBENCH-Hurricane-ISABEL-100x500x500/TCf48.bin.f32.cliz.cfg"]
        )
    return command