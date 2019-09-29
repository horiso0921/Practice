# クラスの練習
class Human:
	"""人間を表す"""
	
	def search(self,place):
		"""周りを見る処理"""
		pass
	def take(self, food):
		self.food = food
		
	def open_mouth(self):
		pass
	
	def eat(self):
		print(self.food+"を食べました")
		
hito = Human()

hito.take("バナナ")
hito.eat()