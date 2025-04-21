// htab_t.h
// Řešení IJC-DU2, příklad 2), 21.4.2025
// Autor: Patrik Lošťák, FIT
// Přeloženo: gcc 13.3.0

#include "htab.h"
#include "htab_item_t.h"
#include <stdlib.h>

typedef struct htab {
    size_t size; // Number of records in the table
    size_t arr_size; // Number of elements next array of pointers
    htab_item_t **arr; // Array of pointers to the items
} htab_t;