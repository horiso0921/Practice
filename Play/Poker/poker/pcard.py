import random


class PlayingCard:
    """definitio of Playing Card"""
#    SUIT_LIST = ('♣', '♢', '♡', '♠')
    SUIT_LIST = ['C', 'D', 'H', 'S']
    NUMBER_LIST = ['', 'A', '2', '3', '4', '5', '6',
                   '7', '8', '9', '10', 'J', 'Q', 'K']

    def __init__(self, suit, number):
        """deconstructor of Playing Card"""
        self.suit = suit
        self.number = number

    def output(self):
        return self.suit + self.NUMBER_LIST[self.number]

    def __str__(self):
        return self.suit + self.NUMBER_LIST[self.number]

    def __eq__(self, other):
        return self.suit == other.suit
    '''
    def __lt__(self, other):
        a = (self.number, self.SUIT_LIST.index(self.suit))
        b = (other.number, self.SUIT_LIST.index(other.suit))
        return a < b
    '''
    '''
    def __lt__(self, other):
        a = (self.number, self.suit)
        b = (other.number, other.suit)
        return a < b
    '''


    def __hash__(self):
        return hash((self.suit, self.number))


class Deck(list):
    """definitio of Deck"""
    def __init__(self):
        """deconstructor of Deck"""
        super().__init__()
        self.extend([PlayingCard(x, y)
                     for x in PlayingCard.SUIT_LIST
                     for y in range(1, 14)])
        self.shuffle()

    def pop(self):
        return super().pop()

    draw = pop

    def shuffle(self):
        """shuffle the deck"""
        random.shuffle(self)

    def __str__(self):
        return " ".join([str(c) for c in self])

    def insert(self, card):
        """insert the card at the random point"""
        i = random.randint(0, len(self))
        super().insert(i, card)


if __name__ == "__main__":
    card1 = PlayingCard(PlayingCard.SUIT_LIST[3], 1)
    card2 = PlayingCard(PlayingCard.SUIT_LIST[0], 11)
    card3 = PlayingCard(PlayingCard.SUIT_LIST[2], 12)
    card4 = PlayingCard(PlayingCard.SUIT_LIST[1], 13)
    print(card1.output() + card2.output() +
          card3.output() + card4.output())

    deck = Deck()
    print(deck)
#    for i in range(52):
#        card = deck.draw()
#        print(card.output(), end=" ")
#    print()
