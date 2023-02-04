all:
		gcc -Wall -g -pg vc3000.c debug.c chash.c 

clang:
		clang -O3 -pg -mtune=znver2 -march=znver2 vc3000.c debug.c shuffle.c 

fast:
		gcc -O3 -Ofast -ftree-vectorize -msse4.2 -mtune=native -march=native vc3000.c debug.c chash.c 

clean:
	rm -f a.out

