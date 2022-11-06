all:
		gcc -Wall -O3 -g -pg ben-or.c debug.c chash.c 

clang:
		clang -O3 -pg -g -Ofast -ftree-vectorize -msse4.2 -mtune=znver2 -march=znver2 vc3000.c debug.c chash.c 

fast:
		gcc -O3 -Ofast -ftree-vectorize -msse4.2 -mtune=znver2 -march=znver2 ven-or.c debug.c chash.c 

slow:
		gcc -O3 -Ofast -ftree-vectorize -msse4.2 -mtune=znver2 -march=znver2 o-hikaku.c debug.c chash.c 

dev:
		gcc -O3 -Ofast -ftree-vectorize -msse4.2 -mtune=znver2 -march=znver2 pen-or.c debug.c chash.c 

clean:
	rm -f a.out

