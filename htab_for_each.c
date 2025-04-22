// htab_for_each.c
// Řešení IJC-DU2, příklad 2), 22.4.2025
// Autor: Patrik Lošťák, FIT
// Přeloženo: gcc 13.3.0

#include "htab.h"
#include "htab_item_t.h"
#include "htab_t.h"

#include <stdio.h>

void htab_for_each(const htab_t *t, void (*f)(htab_pair_t *data)) {
    // Iterate through each bucket in the hash table
    for (size_t i = 0; i < t->arr_size; i++) {
        htab_item_t *curr_item = t->arr_of_ptr[i];
        // Iterate through each item in the linked list at the bucket
        while (curr_item != NULL) {
            f(&curr_item->pair); // Call the function on the current item
            curr_item = curr_item->next; // Move to the next item
        }
    }
}