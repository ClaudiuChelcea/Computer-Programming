# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra

# targets
TARGETS=vectsecv 

# make
build: $(TARGETS)

vectsecv: vectsecv.c
	$(CC) $(CFLAGS) -o vectsecv vectsecv.c 

clean:
	rm -f $(TARGETS)

.PHONY: clean
