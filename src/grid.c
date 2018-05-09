#include "grid.h"
#include "stdio.h"

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
 * @param grid grid to use
 * @param row row to access
 * @param val value to set (must be 0 or 1)
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

	return prevVal == val;
}