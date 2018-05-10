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
    
	printf("Using input file %s \n", argv[1]);

	FILE *infile = fopen(argv[1], "r");

	char buf[MAXFILESIZE];
	int inbyte;

	unsigned char grid[GRIDSIZE];
	grid_printGrid(grid);

	unsigned int numzeros = BITSINROW * BITSINCOL;

	int i,j;
	for(i=0; i<BITSINROW; i++)
	{
		for(j=0; j<BITSINROW; j++)
		{
			grid_setBitAtCoords(0, grid, j, i);
		}
		printf("\n");
	}

	while(fgets(buf, MAXFILESIZE, infile))
	{
		sscanf(buf, "%2x", &inbyte);
		unsigned int row = (inbyte & 0xF0) >> 4;
		unsigned int col = (inbyte & 0xF);

		printf("row: %x col: %x\n", row, col);

		numzeros = grid_updateGrid(grid, row, col, numzeros);
		grid_printGrid(grid);
		printf("numzeros: %d\n", numzeros);
	}

    return 0;
}
