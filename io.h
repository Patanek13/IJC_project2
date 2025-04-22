// io.h
// Řešení IJC-DU2, příklad 2), 22.4.2025
// Autor: Patrik Lošťák, FIT
// Přeloženo: gcc 13.3.0

#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <ctype.h>

// Function to read one word from a file
// Reads a word from the file stream f and stores it in the string s
// Returns the length of the word read
int read_word(unsigned max, char s[max], FILE * f);

#endif // IO_H