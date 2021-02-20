# Chelcea Claudiu Marian
# Contact at: claudiuchelcea01@gmail.com

# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra
OBJ=stardust.o Input-Output.o Modify_matrix.o
NAME=map

# define targets
TARGETS: main input-output modify_matrix link_objects

# execute
main: stardust.c
	$(CC) $(CFLAGS) -c stardust.c

input-output: Input-Output.c
	$(CC) $(CFLAGS) -c Input-Output.c

modify_matrix:  Modify_matrix.c
	$(CC) $(CFLAGS)  -c Modify_matrix.c

# link the created object files
link_objects: stardust.o Input-Output.o Modify_matrix.o
		gcc -o $(NAME) $(OBJ) $(CFLAGS)
		rm $(OBJ)

# remove executables
clean:
	rm -f $(NAME)

.PHONY: clean
