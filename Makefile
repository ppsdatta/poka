CC = gcc

all : src/poka.c
	$(CC) -o poka src/poka.c

.PHONY: clean clobber

clean:
	rm -fr ./poka

