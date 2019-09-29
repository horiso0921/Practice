
class HumanName:
	"""人を表すクラス"""
	def setName(self, name):
		"""名前を設定するメソッド"""
		self.name = name
	def getName(self):
		"""名前を所得するメソッド"""
		return self.name
		
#インスタンス設定
taro = HumanName()
taro.setName("Taro")
print(taro.getName())

jiro = HumanName()
jiro.setName("jiro")
print(jiro.getName())
print(jiro.name)