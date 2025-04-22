// htab_lookup_add.c
// Řešení IJC-DU2, příklad 2), 22.4.2025
// Autor: Patrik Lošťák, FIT
// Přeloženo: gcc 13.3.0

#include "htab.h"
#include "htab_item_t.h"
#include "htab_t.h"

#include <stdio.h>

htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key) {
    // Calculate the hash index for the key
    size_t index = htab_hash_function(key) % t->arr_size;

    // Check if the key already exists in the table
    htab_item_t *curr_item = t->arr_of_ptr[index];
    htab_item_t *prev_item = NULL;

    // Traverse the linked list at the index
    while (curr_item != NULL) {
        if (strcmp(curr_item->pair.key, key) == 0 ) {
            // Key found, return the existing item
            return &curr_item->pair;
        }
        prev_item = curr_item;
        curr_item = curr_item->next;
    }

    // Key not found, create a new item
    htab_item_t *new_item = malloc(sizeof(htab_item_t));
    if (new_item == NULL) {
        return NULL; // Memory allocation failed
    }

    // Allocate memory for the key and copy it
    char *key_copy = malloc(strlen(key) + 1); // +1 for null terminator
    if (key_copy == NULL) {
        free(new_item);
        return NULL; // Memory allocation failed
    }

    // Copy the key into the new item
    strcpy(key_copy, key);

    // Initialize the new item
    new_item->pair.key = key_copy;
    new_item->pair.value = 0; // Initialize value to 0
    new_item->next = NULL;

    //Add th new item to the linked list
    if (prev_item == NULL) {
        // If the list was empty, insert at the head
        t->arr_of_ptr[index] = new_item;
    } else {
        // Otherwise, insert at the end of the list
        prev_item->next = new_item;
    }
    // Increase the size of the table
    t->size++;

    return &new_item->pair; // Return the new item
}

