CC=icc -std=c99 -g -w -fopenmp
CFLAGS=-I include/
OBJS=prime
SRC=src/

all:	primeOMP

primeOMP:	$(SRC)primeOMP.c
	$(CC) -o primeOMP $(CFLAGS) $(SRC)primeOMP.c -lm
	
clean:
	rm -rf primeOMP
