// htab_clear.c
// Řešení IJC-DU2, příklad 2), 22.4.2025
// Autor: Patrik Lošťák, FIT
// Přeloženo: gcc 13.3.0

#include "htab.h"
#include "htab_item_t.h"
#include "htab_t.h"


void htab_clear(htab_t *t) {
    // Iterate through each bucket in the hash table
    for (size_t idx = 0; idx < t->arr_size; idx++) {
        htab_item_t *curr_item = t->arr_of_ptr[idx];
        // Iterate through each item in the linked list at the bucket
        while (curr_item != NULL) {
            htab_item_t *next_item = curr_item->next; // Store the next item
            // Free the key and the item itself
            free((char *)curr_item->pair.key); // Cast to char* to free the key
            free(curr_item); // Free the current item
            curr_item = next_item; // Move to the next item
        }
        t->arr_of_ptr[idx] = NULL; // Set the bucket to NULL after clearing
    }
    t->size = 0; // Reset the size of the hash table
}