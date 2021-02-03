# Chelcea Claudiu Marian

# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -lm
OBJ=Program.o Commands.o Memory.o
NAME=image_editor

# define targets
TARGETS=Program Commands Memory link_objects

# execute
build: 	$(TARGETS) 

# create binary files
Program: Program.c
	$(CC) $(CFLAGS) -c Program.c

Commands: Commands.c
	$(CC) $(CFLAGS) -c Commands.c

Memory: Memory.c
	$(CC) $(CFLAGS) -c Memory.c

# link the files, create executable
link_objects: Program.o Commands.o Memory.o
	gcc -o $(NAME) $(OBJ) $(CFLAGS)
	rm $(OBJ)

# remove executables
clean:
	rm -f $(TARGETS)

.PHONY: clean
