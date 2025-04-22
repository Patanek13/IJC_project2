// htab_erase.c
// Řešení IJC-DU2, příklad 2), 22.4.2025
// Autor: Patrik Lošťák, FIT
// Přeloženo: gcc 13.3.0

#include "htab.h"
#include "htab_item_t.h"
#include "htab_t.h"

#include <stdbool.h>

bool htab_erase(htab_t *t, htab_key_t key) {
    // Calculate the hash index for the key
    size_t index = htab_hash_function(key) % t->arr_size;

    htab_item_t *curr_item = t->arr_of_ptr[index];
    htab_item_t *prev_item = NULL;

    // Traverse the linked list at the index
    while (curr_item != NULL) {
        // Check if the key matches
        if (strcmp(curr_item->pair.key, key) == 0) {
            // Key found, remove the item from the linked list
            if (prev_item == NULL) {
                // If it's the first item in the list
                t->arr_of_ptr[index] = curr_item->next;
            } else {
                // If it's not the first item
                prev_item->next = curr_item->next;
            }

            // Free the key and the item itself
            // Cast to char* to free the key, because it's a const char*
            free((char *)curr_item->pair.key);
            free(curr_item);

            // Decrease the size of the table
            t->size--;
            return true; // Item removed successfully
        }
        // Move to the next item in the list
        prev_item = curr_item;
        curr_item = curr_item->next;
    }
    // Key not found, nothing to remove
    return false;
}