all:
	gcc -Wall -g -pg -mtune=native -march=native -ffast-math -funroll-loops  -fopenmp  ben-or.c debug.c chash.c 

clang:
	clang  -O3 -g -pg -mtune=native -march=native -ffast-math -funroll-loops  -fopenmp  ben-or.c debug.c chash.c 

fast:
		gcc -Wall -g -pg -mtune=native -march=native -ffast-math -funroll-loops  -fopenmp  ven-or.c debug.c chash.c 

slow:
		gcc -Wall -g -pg -mtune=native -march=native -ffast-math -funroll-loops  -fopenmp  o-hikaku.c debug.c chash.c 

clean:
	rm -f a.out

