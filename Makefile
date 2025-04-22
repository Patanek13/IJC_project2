# Makefile
# Řešení IJC-DU2, příklad 1), 2), 16.4.2025
# Autor: Patrik Lošťák, FIT

# Compiler
CC = gcc
# Compiler flags
CFLAGS = -std=c11 -Wall -Wextra -pedantic -O2
LD_LIBRARY_PATH = "."
# Library flags
LDFLAGS += -fsantize=address
# Add sanitizer flags to the CFLAGS
#CFLAGS += -fsanitize=address
# Debug flags
DBFLAGS = -g
# Source files
SRC = $(wildcard htab*.c) # List all source files that start with htab
# Object files
OBJECTS = $(patsubst %.c, %.o, $(SRC)) # Replace .c with .o in the source files
LIBS =-L. -lhtab

.PHONY: all clean zip check

all: tail maxwordcount maxwordcount-dynamic

check: all
	./tail -n 10 check.txt
	export LD_LIBRARY_PATH="." && ./maxwordcount-dynamic < check.txt
	./maxwordcount < check.txt

# Create a zip file with the source code
zip: 
	zip xlostap00.zip *.c *.h Makefile check.txt maxwordcount-cpp.cc

# Clean up object files and the executable
clean:
	rm -f *.o *.so *.a tail maxwordcount-cpp maxwordcount maxwordcount-dynamic *.zip 

# Create the executable	
tail: tail.o
	$(CC) $(CFLAGS) $^ -o $@

maxwordcount-cpp: maxwordcount-cpp.o
	g++ -O2 $^ -o $@

io: io.o
	$(CC) $(CFLAGS) $^ -o $@

maxwordcount: maxwordcount.o io.o libhtab.a
	$(CC) $(CFLAGS) -static maxwordcount.o io.o $(LIBS) -o $@ 

maxwordcount-dynamic: maxwordcount.o io.o libhtab.so
	$(CC) $(CFLAGS) maxwordcount.o io.o -o $@ $(LIBS)


# Compile the source files into object files
tail.o: tail.c 
	$(CC) $(CFLAGS) $(DBFLAGS) -c $^ -o $@

maxwordcount-cpp.o: maxwordcount-cpp.cc
	g++ -O2 -c $^ -o $@

io.o: io.c
	$(CC) $(CFLAGS) $(DBFLAGS) -c $^ -o $@

maxwordcount.o: maxwordcount.c
	$(CC) $(CFLAGS) $(DBFLAGS) -c $^ -o $@

# Create the shared library and static library
# The shared library will be named libhtab.so and the static library will be named libhtab.a
libhtab.so: $(OBJECTS)
	$(CC) -shared -o $@ $^

libhtab.a: $(OBJECTS)
	ar crs $@ $^

htab_init.o: htab_init.c
	$(CC) $(CFLAGS) $(DBFLAGS) -c $^ -o $@
htab_bucket_count.o: htab_bucket_count.c
	$(CC) $(CFLAGS) $(DBFLAGS) -c $^ -o $@
htab_size.o: htab_size.c
	$(CC) $(CFLAGS) $(DBFLAGS) -c $^ -o $@
htab_find.o: htab_find.c
	$(CC) $(CFLAGS) $(DBFLAGS) -c $^ -o $@
htab_lookup_add.o: htab_lookup_add.c
	$(CC) $(CFLAGS) $(DBFLAGS) -c $^ -o $@
htab_free.o: htab_free.c
	$(CC) $(CFLAGS) $(DBFLAGS) -c $^ -o $@
htab_for_each.o: htab_for_each.c
	$(CC) $(CFLAGS) $(DBFLAGS) -c $^ -o $@
htab_erase.o: htab_erase.c
	$(CC) $(CFLAGS) $(DBFLAGS) -c $^ -o $@
htab_clear.o: htab_clear.c
	$(CC) $(CFLAGS) $(DBFLAGS) -c $^ -o $@
htab_hash_function.o: htab_hash_function.c
	$(CC) $(CFLAGS) $(DBFLAGS) -c $^ -o $@

