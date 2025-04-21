// tail.c
// Řešení IJC-DU2, příklad 1), 16.4.2025
// Autor: Patrik Lošťák, FIT
// Přeloženo: gcc 13.3.0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#define MAX_LINE_LENGTH 4096 // Maximum length of a line + 1 for null terminator
#define PRINT_DEFAULT 10 // Default number of lines to print

// Structure to hold command line arguments
typedef struct cmd_args {
    long lines_to_print;
    char *filename;
} cmd_args_t;

// Structure to hold a circular buffer
typedef struct {
    char **lines; // Array of strings to hold lines
    size_t count; // Number of lines currently in the buffer
    size_t capacity; // Maximum capacity of the buffer
    size_t head; // Index of the head of the buffer
    size_t tail; // Index of the tail of the buffer
} cbuf_t;

void print_error(const char *message, const char *details) {
    fprintf(stderr, "tail: "); // Program name prefix
    if (message) {
        fprintf(stderr, "%s", message);
    }
    if (details) {
        fprintf(stderr, ": %s", details); // Add colon only if details exist
    }
    fprintf(stderr, "\n");
}

void print_usage() {
    fprintf(stderr, "Usage: tail [-n NUMLINES]... [FILE]...\n");
}

int validate_and_parse_args(int argc, char *argv[], struct cmd_args *args) {
    args->lines_to_print = PRINT_DEFAULT;
    args->filename = NULL;

    int optidx = 1; // Skip program name
    while (optidx < argc) {
        // Check if the argument starts with '-'
        // and is not a single dash (which indicates stdin)
        if (argv[optidx][0] == '-') {
            if (strcmp(argv[optidx], "--help") == 0) {
                print_usage();
                fprintf(stderr, "Print the last lines of each FILE to standard output.\n");
                fprintf(stderr, "With no FILE, or when FILE is -, read standard input.\n");
                return 0;
            // Process the -n option
            } else if (strcmp(argv[optidx], "-n") == 0) {
                optidx++;
                // Check if the next argument is present
                if (optidx < argc) {
                    char *endptr;
                    errno = 0;
                    long lines = strtol(argv[optidx], &endptr, 10);
                    // Check if the conversion was successful
                    if (errno != 0 || *endptr != '\0' || argv[optidx] == endptr) {
                        print_error("Invalid number of lines", argv[optidx]);
                        print_usage();
                        return -1;
                    }
                    // Check if the number of lines is non-negative
                    if (lines < 0) {
                        print_error("Number of lines has to be non-negative", argv[optidx]);
                        print_usage();
                        return -1;
                    }
                    args->lines_to_print = lines;

                } else {
                    print_error("Missing number of lines", "-n");
                    return -1;
                }

            } else {
                print_error("Unknown option", argv[optidx]);
                print_usage();
                return -1;
            }
        // If the argument does not start with '-', it is a filename
        } else {
            // Check if a filename has already been set
            if (args->filename != NULL) {
                print_error("Multiple files not supported", argv[optidx]);
                print_usage();
                return -1;
            }
            args->filename = argv[optidx]; // Set the filename
        }
        optidx++; // Move to the next argument
    }
    return 0;
}

FILE *open_file(const char *filename) {
    //If the filename is NULL, use stdin
    if (filename == NULL) {
        return stdin;
    }
    // Open the file
    FILE *file = fopen(filename, "r");
    // Check if the file was opened successfully
    if (file == NULL) {
        print_error("Cannot open file", filename);
        return NULL;
    }
    return file;
}

cbuf_t *cbuf_create(size_t capacity) {
    // Allocate memory for the circular buffer
    cbuf_t *buffer = malloc(sizeof(cbuf_t));
    if (buffer == NULL) {
        print_error("Memory allocation failed", NULL);
        return NULL;
    }
    // Allocate memory for the lines array
    buffer->lines = malloc(capacity * sizeof(char *));
    if (buffer->lines == NULL) {
        free(buffer);
        print_error("Memory allocation failed", NULL);
        return NULL;
    }
    // Initialize the buffer
    buffer->capacity = capacity;
    buffer->count = 0;
    buffer->head = 0;
    buffer->tail = 0;

    // Initialize each line to NULL
    for (size_t i = 0; i < capacity; i++) {
        buffer->lines[i] = NULL;
    }

    return buffer;
}

// Function to add a line to the circular buffer
void cbuf_put(cbuf_t *buffer, const char *line) {
    if (buffer->count == buffer->capacity) {
        // If the buffer is full, free the oldest line
        free(buffer->lines[buffer->head]);
        buffer->lines[buffer->head] = NULL; // Set the old line to NULL
        buffer->head = (buffer->head + 1) % buffer->capacity; // Move head forward
        buffer->count--; // Decrease the count
    }
    // Add the new line to the buffer
    buffer->lines[buffer->tail] = malloc(strlen(line) + 1); // +1 for null terminator
    if (buffer->lines[buffer->tail] == NULL) {
        print_error("Memory allocation failed", NULL);
        return;
    }
    strcpy(buffer->lines[buffer->tail], line); // Copy the line into the buffer
    buffer->tail = (buffer->tail + 1) % buffer->capacity; // Move tail forward
    buffer->count++; // Increase the count
}

// Function to get a line from the circular buffer
 const char *cbuf_get (cbuf_t *buffer, size_t idx) {
    if (idx >= buffer->count) {
        return NULL; // Index out of bounds
    }
    // Calculate the actual index in the circular buffer
    size_t actual_idx = (buffer->head + idx) % buffer->capacity;
    return buffer->lines[actual_idx];
 }

 // Function to read a line from the file and handle line overflow
 int read_line(FILE *file, char *buffer, size_t buffer_size) {
    if (!fgets(buffer, buffer_size, file)) {
        return false; // Error or EOF
    }

    // Check if the line is too long
    if (strchr(buffer, '\n') == NULL && !feof(file)) {
        bool line_overflow = false;

        if (!line_overflow) {
            fprintf(stderr, "Line too long, truncated\n");
            line_overflow = true;
        }
        // Skip the rest of the line
        int c;
        while ((c = fgetc(file)) != '\n' && c != EOF) {
            // Do nothing, just skip
        }
    }
    return true;
 }

 void cbuf_free (cbuf_t *buffer) {
    // Free each line in the buffer
    for (size_t idx = 0; idx < buffer->count; idx++) {
        free(buffer->lines[idx]);
    }
    // Free the lines array and the buffer itself
    free(buffer->lines);
    free(buffer);
 }


int main (int argc, char *argv[]) {
    cmd_args_t args;
    // Check arguments and parse them
    if (validate_and_parse_args(argc, argv, &args) != 0) {
        return EXIT_FAILURE;
    }

    if (args.lines_to_print == 0) {
        // If no lines to print, exit successfully
        return EXIT_SUCCESS;
    }

    // Open the file (or stdin)
    FILE *file = open_file(args.filename);
    // Check if the file was opened successfully
    if (file == NULL) {
        return EXIT_FAILURE;
    }

    cbuf_t *buffer = cbuf_create(args.lines_to_print);
    if (buffer == NULL) {
        if (args.filename != NULL) {
            fclose(file); // Close the file only if it is not stdin
        }
        return EXIT_FAILURE;
    }

    char line[MAX_LINE_LENGTH];
    // Read lines from the file and store them in the circular buffer
    while (read_line(file, line, sizeof(line))) {
        line[strcspn(line, "\n")] = '\0'; // Remove the newline character
        cbuf_put(buffer, line);
    }

    // Print the last lines from the circular buffer
    for (size_t i = 0; i < buffer->count; i++) {
        const char *line_to_print = cbuf_get(buffer, i);
        if (line_to_print != NULL) {
            printf("%s\n", line_to_print);
        }
    }
    // Free the circular buffer
    cbuf_free(buffer);
    // Close the file if it was opened
    if (args.filename != NULL) {
        fclose(file);
    }

    return EXIT_SUCCESS;
}