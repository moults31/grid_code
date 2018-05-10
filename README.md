# grid_code

# Usage:
From project root:

`mkdir bin && make`
`bin/grid_code data/<input file name>`

Please note that updating to the commit labelled 0e9ab6f4c17 will produce a verbose output (printing the entire grid after every byte read from input file). Running on HEAD will run the same program, but only output the number of zeros remaining after the run (as specified in the problem definition).

# Description:
A C program that manipulates a 16x16 square grid according to the contents of a file specified on the command line.  

On program startup, this grid is initialized to all zeroes. Subsequently, for each byte read from the file, a coordinate will be formed: the first 4 bits will refer to a row offset within this grid, and the second 4 bits will refer to a column offset within this grid.  

Examining the grid at the decoded coordinate, if the grid’s content at that location is zero, all entries within the grid located in the same row or column shall be set to one. Alternatively, if the content at the decoded location is non-zero (ie: one), all entries within the grid located on the associated diagonals shall be set to zero.  

When the file is finished being processed, your program will print out a single decimal number indicating the number of entries in the grid that are set to zero.