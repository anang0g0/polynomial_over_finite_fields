all:
	gcc -Wall -g -pg -mtune=native -march=native -ffast-math -funroll-loops  -fopenmp  ben-or.c debug.c chash.c 


clean:
	rm -f a.out

