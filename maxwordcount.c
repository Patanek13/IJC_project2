// maxwordcount.c
// Řešení IJC-DU2, příklad 2), 22.4.2025
// Autor: Patrik Lošťák, FIT
// Přeloženo: gcc 13.3.0

#include "htab.h"
#include "io.h"

#include <stdio.h>
#include <stdlib.h>

#define MAX_WORD_LENGTH 256 // Maximum length of a word + 1 for null terminator
#define HASH_TABLE_SIZE 12000 // Size of the hash table

// Function to print the word and its count
void print_word_count(htab_pair_t *data) {
    printf("%s\t%u\n", data->key, data->value);
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
    // Print the words and their counts
    htab_for_each(htab, &print_word_count);

    htab_free(htab); // Free the hash table
}