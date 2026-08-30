#include <stdio.h>
#include <string.h>

// Recursive String Reversal:
// Write a recursive function to reverse a given string without using additional data structures.
//
// Unlike the C++ version (which builds a new std::string on each call via
// substr), this reverses the char array in place: swap the first and last
// character, then recurse inward on the range between them. No extra
// buffer/array is allocated - just index bookkeeping and one temp char.

void reverseHelper(char *str, int start, int end) {
    if (start >= end) {
        return; // base case: pointers have met or crossed
    }

    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;

    reverseHelper(str, start + 1, end - 1);
}

void reverseString(char *str) {
    reverseHelper(str, 0, (int)strlen(str) - 1);
}

// RECURSIVE_TESTING is defined by tests/test_recursiveStringReversal.c
// before it #includes this file, so the test binary (which has its own
// main()) doesn't end up with two main() functions in one link.
#ifndef RECURSIVE_TESTING
int main(void) {
    char word[] = "hej";

    printf("Original: %s\n", word);
    reverseString(word);
    printf("Reversed: %s\n", word);

    return 0;
}
#endif
