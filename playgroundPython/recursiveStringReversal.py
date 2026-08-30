"""
Recursive String Reversal:
Write a recursive function to reverse a given string without using additional data structures.

Note: Python strings are immutable, so true in-place swapping (like the C
version) isn't possible here. This mirrors the C++ approach instead: peel
off the first character, recurse on the rest, then append it at the end.
"""


def reverse_string(s: str) -> str:
    if len(s) <= 1:
        return s
    first_char = s[0]
    rest = s[1:]
    return reverse_string(rest) + first_char


if __name__ == "__main__":
    word = "hej"
    print(f"Original: {word}")
    print(f"Reversed: {reverse_string(word)}")
