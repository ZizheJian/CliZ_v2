import os
from typing import Dict,List

class template_dataset():
    def __init__(self,project_root:str):
        self.project_root:str=project_root
        self.source_path:str=None
        self.compressed_path:str=None
        self.decompressed_path:str=None
        self.config_path:List[str,str]=None
        self.map_path:List[str,str]=None
        self.mask_path:str=None
        self.data_type:str="f32" # i32, f32, f64
        self.dimension:Dict[str,int]=None
        self.err:List[str,float]=None
        self.debug:bool=False
    def get_compress_command(self):
        command=os.path.join(self.project_root,"cliz_compress")
        if (self.source_path!=None):
            command+=f" -in {self.source_path}"
        else:
            raise ValueError("source_path is not set.")
        if (self.compressed_path!=None):
            command+=f" -out {self.compressed_path}"
        if (self.config_path!=None):
            command+=f" -{self.config_path[0]}-cfg {self.config_path[1]}"
        if (self.map_path!=None):
            command+=f" -{self.map_path[0]}-map {self.map_path[1]}"
        if (self.mask_path!=None):
            command+=f" -mask {self.mask_path}"
        if (self.dimension!=None):
            command+=f" -dim{len(self.dimension)}"
            for key,value in self.dimension.items():
                command+=f" {key}{value}"
        else:
            raise ValueError("dimension is not set.")
        if self.data_type!=None:
            command+=f" -type {self.data_type}"
        if self.err!=None:
            command+=f" -err {self.err[0]} {self.err[1]}"
        if self.debug:
            command+=" -debug"
        return command
    def get_decompress_command(self):
        command=os.path.join(self.project_root,"cliz_decompress")
        if (self.compressed_path!=None):
            command+=f" -in {self.compressed_path}"
        else:
            raise ValueError("compressed_path is not set.")
        if (self.decompressed_path!=None):
            command+=f" -out {self.decompressed_path}"
        if (self.config_path!=None):
            command+=f" -{self.config_path[0]}-cfg {self.config_path[1]}"
        if (self.map_path!=None):
            command+=f" -{self.map_path[0]}-map {self.map_path[1]}"
        if (self.mask_path!=None):
            command+=f" -mask {self.mask_path}"
        if (self.dimension!=None):
            command+=f" -dim{len(self.dimension)}"
            for key,value in self.dimension.items():
                command+=f" {key}{value}"
        else:
            raise ValueError("dimension is not set.")
        if self.data_type!=None:
            command+=f" -type {self.data_type}"
        return command
    def get_validate_command(self):
        command=os.path.join(self.project_root,"cliz_validate")
        if (self.source_path!=None):
            command+=f" -src {self.source_path}"
        else:
            raise ValueError("source_path is not set.")
        if (self.decompressed_path!=None):
            command+=f" -dec {self.decompressed_path}"
        if (self.mask_path!=None):
            command+=f" -mask {self.mask_path}"
        if (self.dimension!=None):
            command+=f" -dim{len(self.dimension)}"
            for key,value in self.dimension.items():
                command+=f" {key}{value}"
        if (self.data_type!=None):
            command+=f" -type {self.data_type}"
        if (self.err!=None):
            command+=f" -err {self.err[0]} {self.err[1]}"
        return command
    def get_ssim_command(self):
        if self.source_path is None or self.decompressed_path is None:
            raise ValueError("source_path and decompressed_path must be set for SSIM calculation.")
        command=f"calculateSSIM -f {self.source_path} {self.decompressed_path}"
        for value in reversed(list(self.dimension.values())):
            command+=f" {value}"
        return command