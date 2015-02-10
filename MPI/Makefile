CC = mpiicc
FLAGS = -std=c99 -DMAX_SIZE=100
SRC=src/

primeMPI:$(SRC)primeMPI.c
	$(CC) $(FLAGS) $(SRC)primeMPI.c -lm -o primeMPI

.phony: clean
clean:
	rm -f primeMPI
