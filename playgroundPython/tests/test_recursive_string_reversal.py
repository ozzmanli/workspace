import os
import sys
import unittest

sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))

from recursiveStringReversal import reverse_string


class TestRecursiveStringReversal(unittest.TestCase):
    def test_basic_word(self):
        self.assertEqual(reverse_string("hej"), "jeh")

    def test_empty_string(self):
        self.assertEqual(reverse_string(""), "")

    def test_single_character(self):
        self.assertEqual(reverse_string("a"), "a")

    def test_palindrome(self):
        self.assertEqual(reverse_string("aba"), "aba")


if __name__ == "__main__":
    unittest.main()
