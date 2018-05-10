#include <stdio.h>
#include "grid.h"

#define MAXFILESIZE 1000

int main(int argc, char **argv)
{
	if(argc < 2)
	{
		printf("No input file specified. Valid example run from project root:\n");
		printf("bin/grid_code data/infile1\n");
		printf("Exiting..\n");
		return 0;
	}

	unsigned char grid[GRIDSIZE];
	unsigned int numzeros = BITSINROW * BITSINCOL;

	FILE *infile = fopen(argv[1], "r");

	char buf[MAXFILESIZE];
	int inbyte;

	while(fgets(buf, MAXFILESIZE, infile))
	{
		sscanf(buf, "%2x", &inbyte);
		unsigned int row = (inbyte & 0xF0) >> 4;
		unsigned int col = (inbyte & 0xF);

		numzeros = grid_updateGrid(grid, row, col, numzeros);		
	}

	printf("%d\n", numzeros);

    return 0;
}
