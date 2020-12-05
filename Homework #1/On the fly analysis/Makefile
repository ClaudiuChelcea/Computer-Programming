# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra

# targets
TARGETS=nineL

# make
build: $(TARGETS)

ninel: ninel.c
	$(CC) $(CFLAGS) -o ninel ninel.c 
	
clean:
	rm -f $(TARGETS)

.PHONY: clean
