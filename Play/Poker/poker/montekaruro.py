from pcard import *
from hand import *
from poker import *

trail = 10000
inner = 0

for i in range(trail):
	deck = Deck()
	deck.shuffle()
	
	hand = Hand()
	for j in range(5):
		hand.append(deck.draw())
	if hand.is_flush() == True:
		inner += 1

print(inner)
	