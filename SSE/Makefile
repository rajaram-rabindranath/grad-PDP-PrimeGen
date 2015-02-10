CC=gcc -O3 -std=c99 -g -msse2 -w
CFLAGS=-I include/
OBJS=prime
SRC=src/

all:	primeSSE

primeSSE:	$(SRC)primeSSE.c
	icc -std=c99 -O3 -g -msse2 -w -o primeSSE $(CFLAGS) $(SRC)primeSSE.c -lm
		
clean:
	rm -rf primeSSE 

