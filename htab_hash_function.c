// htab_hash_function.c
// Řešení IJC-DU2, příklad 2), 21.4.2025
// Autor: Patrik Lošťák, FIT
// Přeloženo: gcc 13.3.0

#include "htab.h"
#include <stdint.h>    // uint32_t

// Hash function for strings
// This function computes a hash value for a given string using the 65599 hash algorithm.
size_t htab_hash_function(const char *str) {
    uint32_t h = 0;     // musí mít 32 bitů
    const unsigned char *p;
    for(p = (const unsigned char*)str; *p != '\0'; p++)
        h = 65599 * h + *p;
    return h;
  }