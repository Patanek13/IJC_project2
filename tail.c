// tail.c
// Řešení IJC-DU2, příklad 1), 16.4.2025
// Autor: Patrik Lošťák, FIT
// Přeloženo: gcc 13.3.0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_LINE_LENGTH 4096
#define MAX_LINES 1000
#define PRINT_DEFAULT 10

typedef struct cmd_args {
    long lines_to_print;
    char *filename;
};

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

    int optidx = 1;
    while (optidx < argc) {
        if (argv[optidx][0] == '-') {
            if (strcmp(argv[optidx], "--help") == 0) {
                print_usage();
                fprintf(stderr, "Print the last lines of each FILE to standard output.\n");
                fprintf(stderr, "With no FILE, or when FILE is -, read standard input.\n");
                return 0;
            } else if (strcmp(argv[optidx], "-n") == 0) {
                optidx++;

                if (optidx < argc) {
                    char *endptr;
                    errno = 0;
                    long lines = strtol(argv[optidx], &endptr, 10);

                    if (errno != 0 || *endptr != '\0' || argv[optidx] == endptr) {
                        print_error("Invalid number of lines", argv[optidx]);
                        print_usage();
                        return -1;
                    }

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
        } else {
            if (args->filename != NULL) {
                print_error("Multiple files not supported", argv[optidx]);
                print_usage();
                return -1;
            }
            args->filename = argv[optidx];
        }
        optidx++;
    }
    return 0;
}


int main (int argc, char *argv[]) {
    struct cmd_args args;
    if (validate_args(argc, argv, &args) != 0) {
        return EXIT_FAILURE;
    }
}