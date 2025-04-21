// htab_init.c
// Řešení IJC-DU2, příklad 2), 21.4.2025
// Autor: Patrik Lošťák, FIT
// Přeloženo: gcc 13.3.0

#include <stdio.h>

#include "htab.h"
#include "htab_t.h"


htab_t *htab_init(size_t n) {
    htab_t *table = malloc(sizeof(htab_t));
    if (table == NULL) {
        return NULL; // Memory allocation failed
    }

    // Initialize the table
    table->size = 0; // Number of records in the table
    table->arr_size = n; // Number of elements in the array of pointers

    // Allocate memory for the array of pointers
    table->arr_of_ptr = malloc(n * sizeof(htab_item_t *));
    if (table->arr_of_ptr == NULL) {
        free(table); // Free the table if allocation fails
        return NULL; // Memory allocation failed
    }

    // Initialize the array of pointers to NULL
    for (size_t i = 0; i < n; i++) {
        table->arr_of_ptr[i] = NULL;
    }

    return table;
} 