CC=gcc -std=c99 -g
CFLAGS=-I include/
OBJS=prime
SRC=src/

all:	primeSEQ

primeSEQ:	$(SRC)primGen.c
	$(CC) -o primeSEQ $(CFLAGS) $(SRC)primGen.c -lm
	
clean:
	rm -rf primeSEQ
