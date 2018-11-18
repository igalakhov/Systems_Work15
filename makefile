all main.out: main.c
	gcc -o main.out main.c

run: main.out
	./main.out
