#include <stdio.h>

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

	while(fgets(buf, MAXFILESIZE, infile))
	{
		sscanf(buf, "%2x", &inbyte);
	}

    return 0;
}
