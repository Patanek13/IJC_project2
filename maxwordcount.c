// maxwordcount.c
// Řešení IJC-DU2, příklad 2), 22.4.2025
// Autor: Patrik Lošťák, FIT
// Přeloženo: gcc 13.3.0

#include "htab.h"
#include "io.h"
#include "htab_t.h"

#include <stdio.h>
#include <stdlib.h>

#define MAX_WORD_LENGTH 256 // Maximum length of a word + 1 for null terminator
#define HASH_TABLE_SIZE 12007 // Size of the hash table

static htab_value_t max_count = 0; // Global variable to store the maximum count

// Fucntion to find the maximum count of words
void find_max_count(htab_pair_t *data) {
    if (data->value > max_count) {
        max_count = data->value; // Update the maximum count
    }
}

// Function to print the word and its count if it matches the maximum count
// This function is called for each item in the hash table
void print_word_count(htab_pair_t *data) {
    if (data->value == max_count && max_count > 0) {
        printf("%s\t%u\n", data->key, data->value); 
    }
}

int main() {
    htab_t *htab = htab_init(HASH_TABLE_SIZE);
    if (htab == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    char word[MAX_WORD_LENGTH];
    // Read words from stdin and add them to the hash table
    while (read_word(MAX_WORD_LENGTH, word, stdin) > 0) {
        if (htab_lookup_add(htab, word) == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            htab_free(htab);
            return 1;
        }
        // Increment the count for the word
        htab_lookup_add(htab, word)->value++;
    }
    htab_for_each(htab, &find_max_count); // Find the maximum count
    htab_for_each(htab, &print_word_count); // Print the words with the maximum count

    htab_free(htab); // Free the hash table
}