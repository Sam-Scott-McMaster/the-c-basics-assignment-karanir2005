main: main.c convert.c convert.h
	gcc -o convert main.c convert.c
coverage: main.c convert.c convert.h
	gcc --coverage -o convert main.c convert.c
