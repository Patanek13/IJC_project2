// htab_size.c
// Řešení IJC-DU2, příklad 2), 21.4.2025
// Autor: Patrik Lošťák, FIT
// Přeloženo: gcc 13.3.0

#include "htab.h"
#include "htab_t.h"

// Returns the number of records in the hash table
size_t htab_size (const htab_t *table) {
    return table->size;
}