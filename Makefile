CFLAGS = -Wall -Wextra -g -O0

all: main

main: btn.o btn-delegate.o main.o

clean:
	rm -f btn.o btn-delegate.o main.o

.PHONY: all clean
