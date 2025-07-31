import os
from typing import Dict,List

class template_dataset():
    def __init__(self):
        self.cliz_path="/home/x-zjian1/CliZ_v2" # the directory of the CliZ executables
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
        command=os.path.join(self.cliz_path,"cliz_compress")
        command+=self._get_compress_command()
        return command
    def get_decompress_command(self):
        command=os.path.join(self.cliz_path,"cliz_decompress")
        command+=self._get_compress_command() # same as compress command
        return command
    def get_validate_command(self):
        command=os.path.join(self.cliz_path,"cliz_validate")
        command+=self._get_validate_command()
        return command
    def _get_compress_command(self):
        command=""
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
    def _get_validate_command(self):
        command=""
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