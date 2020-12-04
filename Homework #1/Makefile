# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra

# targets
TARGETS=nineL

# make's
build: $(TARGETS)

ninel: ninel.c
	$(CC) $(CFLAGS) -o ninel ninel.c 
	
clean:
	rm -f $(TARGETS)

.PHONY: clean
