CC=mpiicc -std=c99 -g -w -fopenmp
CFLAGS=-I include/
SRC=src/

all:	primeMPI_OMP

primeMPI_OMP:	$(SRC)primeMPI_OMP.c
	$(CC) -o primeMPI_OMP $(CFLAGS) $(SRC)primeMPI_OMP.c -lm
	
clean:
	rm -rf primeMPI_OMP

