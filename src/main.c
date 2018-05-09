#include <stdio.h>
#include "grid.h"

#define MAXFILESIZE 1000

int main(int argc, char **argv)
{
	if(argc < 2)
	{
		printf("No input file specified. Exiting...\n");
		return 0;
	}
    
	printf("Using input file %s \n", argv[1]);

	FILE *infile = fopen(argv[1], "r");

	char buf[MAXFILESIZE];
	int inbyte;

	unsigned char grid[GRIDSIZE];

	while(fgets(buf, MAXFILESIZE, infile))
	{
		sscanf(buf, "%2x", &inbyte);
		unsigned int row = (inbyte & 0xF0) >> 4;
		unsigned int col = (inbyte & 0xF);

		printf("row: %x col: %x\n", row, col);

		grid_setBitAtCoords(1, grid, row, col);
		unsigned char val = grid_getBitAtCoords(grid, row, col);

		printf("lauraa: %d\n", val);
	}

    return 0;
}
