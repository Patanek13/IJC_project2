// htab_free.c
// Řešení IJC-DU2, příklad 2), 22.4.2025
// Autor: Patrik Lošťák, FIT
// Přeloženo: gcc 13.3.0

#include "htab.h"
#include "htab_item_t.h"
#include "htab_t.h"

void htab_free(htab_t *t) {
    // Clear the hash table to free all items
    htab_clear(t);
    // Free the array of pointers
    free(t->arr_of_ptr);
    // Free the hash table structure itself
    free(t);
}