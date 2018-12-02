C=gcc
CFLAGS=-std=c11 -g -pedantic-errors -Wall -Werror

clean:
	rm *.o

all: lab7

lab7: *.s *.c
		nasm -f elf64 image_sepia_sse.s
			$(CC) $(CFLAGS) -c *.c
				$(CC) -o lab7  *.o -no-pie
