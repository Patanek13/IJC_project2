// htab_item_t.h
// Řešení IJC-DU2, příklad 2), 21.4.2025
// Autor: Patrik Lošťák, FIT
// Přeloženo: gcc 13.3.0

#include "htab.h"
#ifndef HTAB_ITEM_T 
#define HTAB_ITEM_T 

typedef struct htab_item {
    htab_pair_t pair; // Key-value pair
    htab_item_t *next; // Pointer to the next item in the linked list
} htab_item_t;

#endif // HTAB_ITEM_T