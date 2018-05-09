bin/grid_code: bin/main.o bin/grid.o
	gcc -Wall bin/main.o bin/grid.o -o bin/grid_code

bin/main.o: src/main.c
	gcc -Wall -c src/main.c -o bin/main.o

bin/grid.o: src/grid.c
	gcc -Wall -c src/grid.c -o bin/grid.o