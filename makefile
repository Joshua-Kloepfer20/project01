shell: project01.o functions.o
	gcc -o shell project01.o functions.o
project01.o:
	gcc project01.c -c
functions.o:
	gcc functions.c -c
run:
	./shell
