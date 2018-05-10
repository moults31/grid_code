#include "grid.h"
#include "stdio.h"
#include <stdlib.h>

/**
 * Returns the corresponding index into the bitpacked linear array
 * representation of a 2D grid for the given row and column pair
 *
 * @param row row to access
 * @param col column to access
 */
unsigned int grid_getIdxFromRowCol(unsigned int row, unsigned int col)
{
	unsigned int idx;

	idx = (row * 2) + (col / (BITSINROW/2));

	return idx;
}

/**
 * Returns the corresponding offset into a char entry in the bitpacked 
 * linear array representation of a 2D grid for the given row and column pair
 *
 * @param row row to access
 * @param col column to access
 */
unsigned int grid_getOffsetFromRowCol(unsigned char row, unsigned char col)
{
	if(col >= (BITSINROW/2))
	{
		col -= (BITSINROW/2);
	}

	return SIZEOFBYTE - col - 1;
}

/**
 * Returns the value in a given bit of a bitpacked 2D grid
 *
 * @param grid grid to use
 * @param row row to access
 * @param col column to access
 */
unsigned char grid_getBitAtCoords(unsigned char *grid, unsigned char row, unsigned char col)
{
	unsigned int idx = grid_getIdxFromRowCol(row, col);
	unsigned int offset = grid_getOffsetFromRowCol(row, col);

	return (grid[idx] & (1 << offset)) != 0;
}

/**
 * Sets the specified value in a given bit of a bitpacked 2D grid.
 * Returns 1 if the value changed, 0 if remained unchanged.
 *
 * @param val value to set (must be 0 or 1)
 * @param grid grid to use
 * @param row row to access
 * @param col column to access
 */
unsigned int grid_setBitAtCoords(unsigned char val, unsigned char *grid, unsigned char row, unsigned char col)
{
	unsigned int idx = grid_getIdxFromRowCol(row, col);
	unsigned int offset = grid_getOffsetFromRowCol(row, col);

	unsigned char prevVal = grid[idx] & (1 << offset);

	if(val == 1)
	{
		grid[idx] |= (val << offset);
	}
	else
	{
		grid[idx] &= ~(1 << offset);
	}

	return ((prevVal != 0) != val);
}

/**
 * Primary API for this module.
 * Checks bit at given coords. If bit is 0, all entries in same row
 * and in same col get set to 1.
 * If bit is 1, all entries on shared diagonal set to 0.
 * Returns current number of entries with value 0 in grid.
 *
 * @param grid grid to use
 * @param row row to access
 * @param col column to access
 */
unsigned int grid_updateGrid(unsigned char *grid, unsigned int row, unsigned int col, unsigned int numzeros)
{
	unsigned int val = grid_getBitAtCoords(grid, row, col);

	if(val == 0)
	{
		/* set entries sharing this row and col to 1 */
		int i,j;
		for(i=0; i<BITSINROW; i++)
		{
			if(grid_setBitAtCoords(1, grid, row, i) == 1)
			{
				numzeros--;
			}
		}

		for(j=0; j<BITSINCOL; j++)
		{
			if(grid_setBitAtCoords(1, grid, j, col) == 1)
			{
				numzeros--;
			}
		}
	}
	else
	{
		/* each iteration will attempt to set 2 entries on the same row */
		/* which both share a diagonal with the specified entry */

		int r;
		int c1, c2;

		for(r=0; r<BITSINCOL; r++)
		{
			int distance = abs((int)row - r);

			c1 = (int)col - distance;
			c2 = (int)col + distance;

			if(c1 >= 0)
			{
				if(grid_setBitAtCoords(0, grid, r, c1) == 1)
				{
					numzeros++;
				}
			}

			if(c2 < BITSINCOL)
			{
				if(grid_setBitAtCoords(0, grid, r, c2) == 1)
				{
					numzeros++;
				}
			}
		}
	}

	return numzeros;
}

/**
 * For Debug/testing purposes.
 * prints entire grid contents to console
 *
 * @param grid grid to use
 */
void grid_printGrid(unsigned char *grid)
{
	int i,j;
	for(i=0; i<BITSINROW; i++)
	{
		for(j=0; j<BITSINROW; j++)
		{
			printf("%d ", grid_getBitAtCoords(grid, i, j));
		}
		printf("\n");
	}

	printf("\n\n");
}