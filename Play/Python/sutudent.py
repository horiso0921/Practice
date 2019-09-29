class student:	
	def __init__(self,id,name,score = 0):
		self.id = id
		self.name = name
		self.score = score
	def getId(self):
		return self.id

p1 = student(10, "ゴミ")
a = p1.getId()


print(p1.id)