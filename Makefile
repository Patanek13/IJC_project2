# Makefile
# Řešení IJC-DU2, příklad 1), 2), 16.4.2025
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
zip: 
	zip xlostap00.zip *.c *.h Makefile

# Clean up object files and the executable
clean:
	rm -f $(OBJECTS) tail maxwordcount-cpp.o maxwordcount-cpp *.zip

# Create the executable	
tail: tail.o
	$(CC) $(CFLAGS) $^ -o $@

maxwordcount-cpp: maxwordcount-cpp.o
	g++ -O2 $^ -o $@





# Compile the source files into object files
tail.o: tail.c
	$(CC) $(CFLAGS) $(DBFLAGS) -c $^ -o $@

maxwordcount-cpp.o: maxwordcount-cpp.cc
	g++ -O2 -c $^ -o $@


