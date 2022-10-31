all:
		gcc -Wall -O3 -g -pg ben-or.c debug.c chash.c 

clang:
		clang-13 -O3 -Ofast -ftree-vectorize -msse4.2 -mtune=znver2 -march=znver2 ven-or.c debug.c chash.c 

fast:
		gcc -O3 -Ofast -pg -ftree-vectorize -msse4.2 -mtune=znver2 -march=znver2 ven-or.c debug.c chash.c 

slow:
		gcc -O3 -Ofast -ftree-vectorize -msse4.2 -mtune=znver2 -march=znver2 o-hikaku.c debug.c chash.c 

clean:
	rm -f a.out

