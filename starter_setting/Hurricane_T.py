from starter_setting.template_dataset import template_dataset

# "template_dataset" includes the functions for generating commands.
class Hurricane_T(template_dataset):
	def __init__(self,project_root):
		super().__init__(project_root)
		self.source_path="/anvil/projects/x-cis240192/shared/Hurricane/TCf48.bin.f32"
		self.compressed_path="/home/x-zjian1/CliZ_v2/result/TCf48.bin.f32.cliz"
		self.decompressed_path="/home/x-zjian1/CliZ_v2/result/TCf48.bin.f32.cliz.bin"
		# "config_path" is a list which includes 2 strings.
		# The first string is the mode of the config file. If it is "set", CliZ will generate a config file.
		# If it is "use", CliZ will use the config file in the second string.
		# The second string is the path of the config file.
		self.config_path=["set","/home/x-zjian1/CliZ_v2/result/TCf48.bin.f32.cliz.cfg"]
		# "map_path" is a list which includes 2 strings.
		# The first string is the mode of the map file. If it is "set", CliZ will generate a map file.
		# If it is "use", CliZ will use the map file in the second string.
		# The second string is the path of the map file.
		self.map_path=["set","/home/x-zjian1/CliZ_v2/result/TCf48.bin.f32.cliz.map"]
		# "dimension" is a dictionary which includes the dimensions of the data.
		# The keys are the names of the dimensions, and the values are the sizes of the dimensions.
		self.dimension={"h":100,"lat":500,"lng":500}
		# "err" is a list which includes the error type and the error bound.
		# The first element is the error type, and the second element is the error bound.
		# The error type can be "ABS" or "REL".
		self.err=["REL",1e-3]
		self.debug=True