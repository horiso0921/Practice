#!/usr/bin/env python3
import unittest
import copy
from pcard import PlayingCard
from hand import Hand
import poker

class TestPlayingCard(unittest.TestCase):
    """test PlayingCard class"""
    
    def test_is_four_of_a_kind(self):
        hand = Hand()
        hand.set_up("S1 D2 H4 C4 S5")
        self.assertFalse(hand.is_four_of_a_kind())
        hand.set_up("S1 D12 C10 H9 C1")
        self.assertFalse(hand.is_four_of_a_kind())
        hand.set_up("S9 D9 H1 H9 C8")
        self.assertFalse(hand.is_four_of_a_kind())
        # True
        hand.set_up("S1 D1 h1 h9 c1")
        self.assertTrue(hand.is_four_of_a_kind())
        hand.set_up("S9 D9 h1 h9 c9")
        self.assertTrue(hand.is_four_of_a_kind())

    def test_is_full_house(self):
        hand = Hand()
        # False
        hand.set_up("S1 D2 H4 C4 S5")
        self.assertFalse(hand.is_full_house())
        hand.set_up("S1 D2 H4 C4 S5")
        self.assertFalse(hand.is_full_house())
        hand.set_up("S1 D12 C10 H9 C1")
        self.assertFalse(hand.is_full_house())
        hand.set_up("S9 D9 H1 H9 C8")     # Three of a kind
        self.assertFalse(hand.is_full_house())
        hand.set_up("S1 D1 H1 H9 C1")
        self.assertFalse(hand.is_full_house())
        hand.set_up("S9 D9 H1 H9 C9")
        self.assertFalse(hand.is_full_house())
        hand.set_up("S1 D1 C10 H10 C9")
        self.assertFalse(hand.is_full_house())
        hand.set_up("S9 D9 H1 H9 C9")   # four of a kind
        self.assertFalse(hand.is_full_house())
        hand.set_up("S1 D1 H1 H9 C1")   # four of a kind
        self.assertFalse(hand.is_full_house())
        # True
        hand.set_up("S1 D1 C10 H10 C1") # full house
        self.assertTrue(hand.is_full_house())
        hand.set_up("D3 C2 H3 S2 S3") # full house
        self.assertTrue(hand.is_full_house())

    def test_is_three_of_a_kind(self):
        hand = Hand()
        # False
        hand.set_up("S1 D2 H4 C4 S5")     # one pair
        self.assertFalse(hand.is_three_of_a_kind())
        hand.set_up("S1 D12 C10 H9 C1")   # one pair
        self.assertFalse(hand.is_three_of_a_kind())
        hand.set_up("S1 D2 H4 C4 H1")     # two pair
        self.assertFalse(hand.is_three_of_a_kind())
        hand.set_up("S1 D1 H4 C4 H10")    # two pair
        self.assertFalse(hand.is_three_of_a_kind())
        hand.set_up("S1 D2 H2 C4 H4")     # two pair
        self.assertFalse(hand.is_three_of_a_kind())
        hand.set_up("S1 D1 C10 H10 C9")   # two pair
        self.assertFalse(hand.is_three_of_a_kind())
        hand.set_up("S2 D3 H4 S1 S5")     # straight
        self.assertFalse(hand.is_three_of_a_kind())
        # True
        hand.set_up("H12 S1 D12 S3 C12")  # Three of a kind
        self.assertTrue(hand.is_three_of_a_kind())
        hand.set_up("S9 D9 H1 H9 C8")     # Three of a kind
        self.assertTrue(hand.is_three_of_a_kind())

    def test_is_flush(self):
        hand = Hand()
        # False
        hand.set_up("C2 D12 C1 C10 C9")   # 12 high
        self.assertFalse(hand.is_flush())
        hand.set_up("S1 D2 H4 C4 S5")     # one pair
        self.assertFalse(hand.is_flush())
        hand.set_up("S9 D9 H1 H9 C8")     # Three of a kind
        self.assertFalse(hand.is_flush())
        hand.set_up("S1 D2 H4 C4 H1")     # two pair
        self.assertFalse(hand.is_flush())
        hand.set_up("C2 D12 C1 C11 C13")  # 13 high not straight
        self.assertFalse(hand.is_flush())
        # True
        hand.set_up("S13 S2 S4 S8 S9")     # flush
        self.assertTrue(hand.is_flush())

    def test_is_straight(self):
        hand = Hand()
        hand.set_up("C2 D12 C1 C11 C13")  # 13 high not straight
        self.assertFalse(hand.is_straight())
        hand.set_up("C2 D12 C1 C10 C9")
        self.assertFalse(hand.is_straight())
        hand.set_up("S1 D2 H4 C4 S5")
        self.assertFalse(hand.is_straight())
        hand.set_up("S1 D12 C10 H9 C1")   # one pair
        self.assertFalse(hand.is_straight())
        hand.set_up("S9 D9 H1 H9 C8")     # Three of a kind
        self.assertFalse(hand.is_straight())
        hand.set_up("S1 D1 H1 H9 C1")     # four of a kind
        self.assertFalse(hand.is_straight())
        hand.set_up("S1 D2 H4 C4 H1")     # two pair
        self.assertFalse(hand.is_straight())
        hand.set_up("S1 D2 H2 C4 H4")     # two pair
        self.assertFalse(hand.is_straight())
        hand.set_up("S1 D1 C10 H10 C1")   # full house
        self.assertFalse(hand.is_straight())
        hand.set_up("D3 C2 H3 S2 S3")     # full house
        self.assertFalse(hand.is_straight())
        # True
        hand.set_up("S12 D9 C11 D8 H10") # straight
        self.assertTrue(hand.is_straight())
        hand.set_up("S2 D3 H4 S1 S5")     # straight
        self.assertTrue(hand.is_straight())
        hand.set_up("S10 D11 H12 S13 S1") # straight
        self.assertTrue(hand.is_straight())
        
    def test_is_straight_flush(self):
        hand = Hand()
        hand.set_up("C2 D12 C1 C10 C9")   # 12 high
        self.assertFalse(hand.is_straight_flush())
        hand.set_up("S13 S2 S4 S8 S9")    # flush
        self.assertFalse(hand.is_straight_flush())
        hand.set_up("S2 D3 H4 S1 S5")     # straight
        self.assertFalse(hand.is_straight_flush())
        # True
        hand.set_up("D1 D5 D2 D4 D3")     # straight flush
        self.assertTrue(hand.is_straight_flush())
        hand.set_up("S1 S11 S10 S13 S12")  # royal straight flush
        self.assertTrue(hand.is_straight_flush())

        
    def test_is_two_pair(self):
        hand = Hand()
        hand.set_up("S2 D3 H4 S1 S5")
        self.assertFalse(hand.is_two_pair())
        hand.set_up("S1 D2 H4 C4 S5")
        self.assertFalse(hand.is_two_pair())
        # True
        hand.set_up("S1 D2 H4 C4 H1")
        self.assertTrue(hand.is_two_pair())
        hand.set_up("S1 D1 H4 C4 H10")
        self.assertTrue(hand.is_two_pair())
        hand.set_up("S1 D2 H2 C4 H4")
        self.assertTrue(hand.is_two_pair())

    def test_is_one_pair(self):
        hand = Hand()
        hand.set_up("C2 D12 C1 C10 C9")   # 12 high
        self.assertFalse(hand.is_one_pair())
        hand.set_up("S2 D3 H4 S1 S5")     # straight
        self.assertFalse(hand.is_one_pair())
        hand.set_up("S13 S2 S4 S8 S9")    # flush
        self.assertFalse(hand.is_one_pair())
        # True
        hand.set_up("S1 D2 H4 C4 S5")     # one pair
        self.assertTrue(hand.is_one_pair())
        hand.set_up("S1 D12 C10 H9 C1")   # one pair
        self.assertTrue(hand.is_one_pair())

        
'''
        hand.set_up("C2 D12 C1 C10 C9")   # 12 high
        hand.set_up("S1 D2 H4 C4 S5")     # one pair
        hand.set_up("S1 D12 C10 H9 C1")   # one pair
        hand.set_up("S9 D9 H1 H9 C8")     # Three of a kind
        hand.set_up("H12 S1 D12 S3 C12")  # Three of a kind
        hand.set_up("S1 D1 H1 H9 C1")     # four of a kind
        hand.set_up("S9 D9 H1 H9 C9")     # four of a kind
        hand.set_up("S1 D2 H4 C4 H1")     # two pair
        hand.set_up("S1 D1 H4 C4 H10")    # two pair
        hand.set_up("S1 D2 H2 C4 H4")     # two pair
        hand.set_up("S1 D1 C10 H10 C9")   # two pair
        hand.set_up("S1 D1 C10 H10 C1")   # full house
        hand.set_up("D3 C2 H3 S2 S3")     # full house
        hand.set_up("C2 D12 C1 C11 C13")  # 13 high not straight
        hand.set_up("S2 D3 H4 S1 S5")     # straight
        hand.set_up("S12 D9 C11 D8 H10")  # straight
        hand.set_up("S10 D11 H12 S13 S1") # straight
        hand.set_up("S13 S2 S4 S8 S9")    # flush
        hand.set_up("S1 S11 S10 S13 S12") # royal straight flush
        hand.set_up("D1 D5 D2 D4 D3")     # straight flush
'''

if __name__ == "__main__":
    unittest.main()
