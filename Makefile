zelda: main.o
	gcc -o zelda main.o -lncurses
main.o:main.c
	gcc -c main.c
