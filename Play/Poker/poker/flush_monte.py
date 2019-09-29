from pcard import *
from hand import *
import poker

while 1:
	times = 10000
	count = 0
	hand = Hand()
	
	for i in range(times):
		deck = Deck()
		for i in range(5):
			hand.append(deck.draw())
		if hand.is_flush():
			count += 1
			hand.clear()
		
	P = (count/times)*100
	print('{}{:.3f}{}'.format('flush:', P, '%'))

