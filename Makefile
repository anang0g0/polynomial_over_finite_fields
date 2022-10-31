all:
		gcc -Wall -O3 -g -pg ben-or.c debug.c chash.c 

clang:
		clang  -O3 ven-or.c debug.c chash.c 

fast:
		gcc -O3 ven-or.c debug.c chash.c 

slow:
		gcc -O3 o-hikaku.c debug.c chash.c 

clean:
	rm -f a.out

