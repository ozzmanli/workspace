#include <iostream>
#include "recursiveStringReversal.h"

void sayHello() {
    std::cout << "Hello, World! (C++)" << std::endl;
}

// Recursive String Reversal:
// Write a recursive function to reverse a given string without using additional data structures.

std::string recursiveFunction(std::string* value)
{
    if (value->empty())
    {
        return "";                              // bas-fallet du redan hade
    }
    char firstChar = (*value)[0];               // 'h' i "hej"
    std::string newValue = value->substr(1);     // "ej" i "hej"

    std::string reversedRest = recursiveFunction(&newValue);  // FÅNGAR UPP svaret ("je")
    return reversedRest + firstChar;             // "je" + 'h' = "jeh"
}

int main() {
    sayHello();
    std::string word = "hej";
    std::string reversed = recursiveFunction(&word);
    std::cout << reversed << std::endl;   // skriver ut "jeh"
    return 0;
}