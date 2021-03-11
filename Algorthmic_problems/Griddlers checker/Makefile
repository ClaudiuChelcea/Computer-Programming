# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra

# targets
TARGETS=griddlers

# make
build: $(TARGETS)

griddlers: griddlers.c
	$(CC) $(CFLAGS) -o griddlers griddlers.c 

clean:
	rm -f $(TARGETS)

.PHONY: clean
