// htab_find.c
// Řešení IJC-DU2, příklad 2), 21.4.2025
// Autor: Patrik Lošťák, FIT
// Přeloženo: gcc 13.3.0

#include "htab.h"
#include "htab_t.h"
#include "htab_item_t.h"

htab_pair_t * htab_find(const htab_t * t, htab_key_t key) {
    // Calculate the hash value for the key
    size_t hash = htab_hash_function(key);
    // point to the first item in the linked list at the index
    // hash % t->arr_size gives the index in the array of pointers
    htab_item_t *item = t->arr_of_ptr[hash % t->arr_size];
    // Traverse the linked list at the index
    while (item != NULL) {
        // Check if the key matches
        if (strcmp(item->pair.key, key) == 0) {
            return &item->pair; // Return the found item
        }
        item = item->next; // Move to the next item in the list
    }
    return NULL; // Key not found
}