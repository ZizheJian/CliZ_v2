from starter_setting.template_dataset import template_dataset

class Hurricane_T(template_dataset):
	def __init__(self):
		super().__init__()
		self.source_path="/anvil/projects/x-cis240192/shared/Hurricane/TCf48.bin.f32"
		self.decompressed_path="/anvil/projects/x-cis240192/shared/Hurricane/TCf48.bin.f32.cliz.bin"
		self.config_path=["set","/anvil/projects/x-cis240192/shared/Hurricane/TCf48.bin.f32.cliz.cfg"]
		self.map_path=["set","/anvil/projects/x-cis240192/shared/Hurricane/TCf48.bin.f32.cliz.map"]
		self.dimension={"h":100,"lat":500,"lng":500}
		self.err=["REL",1e-3]
		self.debug=True