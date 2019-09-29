#!/usr/bin/env python3

import unittest
from pcard import *
from hand import *
from poker import *
import ex2

class TestPlayingCard(unittest.TestCase):
    """test PlayingCard class"""

    def test_is_royal_straight_flush(self):
        hand = Hand()
        # False
        hand.set_up("S1 D2 H4 C4 S5")     # one pair
        self.assertFalse(hand.is_royal_straight_flush())
        hand.set_up("S1 D12 C10 H9 C1")   # one pair
        self.assertFalse(hand.is_royal_straight_flush())
        hand.set_up("S1 D2 H4 C4 H1")     # two pair
        self.assertFalse(hand.is_royal_straight_flush())
        hand.set_up("S1 D1 H4 C4 H10")    # two pair
        self.assertFalse(hand.is_royal_straight_flush())
        hand.set_up("S1 D2 H2 C4 H4")     # two pair
        self.assertFalse(hand.is_royal_straight_flush())
        hand.set_up("S1 D1 C10 H10 C9")   # two pair
        self.assertFalse(hand.is_royal_straight_flush())
        hand.set_up("S2 D3 H4 S1 S5")     # straight
        self.assertFalse(hand.is_royal_straight_flush())
        hand.set_up("D1 S11 S10 S13 S12") # straight
        self.assertFalse(hand.is_royal_straight_flush())
        hand.set_up("S9 D9 H1 H9 C9")   # four of a kind
        self.assertFalse(hand.is_royal_straight_flush())
        hand.set_up("S1 D1 H1 H9 C1")   # four of a kind
        self.assertFalse(hand.is_royal_straight_flush())
        hand.set_up("S1 D1 H1 H9 C1")   # four of a kind
        self.assertFalse(hand.is_royal_straight_flush())
        hand.set_up("D1 D5 D2 D4 D3")     # straight flush
        self.assertFalse(hand.is_royal_straight_flush())
        hand.set_up("H13 H9 H10 H11 H12")     # straight flush
        self.assertFalse(hand.is_royal_straight_flush())
        # True
        hand.set_up("S1 S11 S10 S13 S12") # 
        self.assertTrue(hand.is_royal_straight_flush())
        hand.set_up("D13 D12 D11 D1 D10")   # 
        self.assertTrue(hand.is_royal_straight_flush())

if __name__ == "__main__":
    unittest.main()
