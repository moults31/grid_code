#ifndef GRID_H
#define GRID_H

#define GRIDSIZE 32
#define BITSINROW 16
#define SIZEOFBYTE 8

unsigned int grid_getIdxFromRowCol(unsigned int row, unsigned int col);
unsigned int grid_getOffsetFromRowCol(unsigned char row, unsigned char col);
unsigned char grid_getBitAtCoords(unsigned char *grid, unsigned char row, unsigned char col);
unsigned int grid_setBitAtCoords(unsigned char val, unsigned char *grid, unsigned char row, unsigned char col);



#endif // GRID_H