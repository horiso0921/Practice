i = 0
while i < 100:
	i += 1
	if i%3 or i%5:
		continue
	elif i > 50:
		break
	else:
		print("{0:d}: FizzBuzz".format(i))