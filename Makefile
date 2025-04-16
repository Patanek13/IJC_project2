# Makefile
# Řešení IJC-DU2, Makefile 1), 2), 16.4.2025
# Autor: Patrik Lošťák, FIT

# Compiler
CC = gcc
# Compiler flags
CFLAGS = -std=c11 -Wall -Wextra -pedantic -O2
# Library flags
LDFLAGS += -fsantize=address
# Add sanitizer flags to the CFLAGS
#CFLAGS += -fsanitize=address
# Debug flags
DBFLAGS = -g
# Source files
SRC = tail.c
HEADERS =
# Object files
OBJECTS = $(SRC:.c=.o)

.PHONY: all clean zip

all: tail
# Create a zip file with the source code
zip: clean
	zip xlostap00.zip *.c *.h Makefile

# Clean up object files and the executable
clean:
	rm -f $(OBJECTS) tail *.zip
# Create the executable	
tail: tail.o
	$(CC) $(CFLAGS) $^ -o $@





# Compile the source files into object files
tail.o: tail.c
	$(CC) $(CFLAGS) $(DBFLAGS) -c $^ -o $@


