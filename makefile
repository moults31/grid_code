bin/grid_code: bin/main.o
	gcc -Wall bin/main.o -o bin/grid_code

bin/main.o: src/main.c
	gcc -Wall -c src/main.c -o bin/main.o