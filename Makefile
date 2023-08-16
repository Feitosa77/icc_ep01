all: IR.o main.c 
	gcc main.c IR.o -Wall -lm -Wno-parentheses

IR.o: IR.h IR.c 
	gcc -c IR.c

purge:
	rm -f *.o a.out

