#include <assert.h>
#include <stdio.h>
#include <string.h>

// Reuse the implementation straight from recursiveStringReversal.c instead
// of duplicating it here. RECURSIVE_TESTING suppresses that file's own
// main() (see the #ifndef guard there) so this binary has exactly one
// main() - the one below.
#define RECURSIVE_TESTING
#include "../recursiveStringReversal.c"

int main(void) {
    char basic[] = "hej";
    reverseString(basic);
    assert(strcmp(basic, "jeh") == 0);

    char empty[] = "";
    reverseString(empty);
    assert(strcmp(empty, "") == 0);

    char single[] = "a";
    reverseString(single);
    assert(strcmp(single, "a") == 0);

    char palindrome[] = "aba";
    reverseString(palindrome);
    assert(strcmp(palindrome, "aba") == 0);

    printf("All C tests passed.\n");
    return 0;
}
