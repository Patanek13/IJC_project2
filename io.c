// io.c
// Řešení IJC-DU2, příklad 2), 22.4.2025
// Autor: Patrik Lošťák, FIT
// Přeloženo: gcc 13.3.0

#include "io.h"

int read_word(unsigned max, char s[max], FILE *f) {
  int character;
  unsigned int idx = 0;

  if (max == 0) {
    return 0; // Return 0 if max length is 0
  }

  // Skip leading whitespace
  while (isspace(character = getc(f)) && character != EOF) {
    ; // Do nothing, just skip
  }

  // If EOF is reached after skipping whitespace, return EOF
  if (character == EOF) {
    return EOF; // Return EOF if no characters were read
  }

  while (character != EOF && !isspace(character)) {
    if (idx < max - 1) {
      s[idx++] = character; // Store the character in the string
    } else {
      break; // Stop if the string is full
    }
    character = getc(f); // Read the next character
  }

  s[idx] = '\0'; // Null-terminate the string

  return (int)idx; // Return the length of the word read
}