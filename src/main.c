#include <stdio.h>

int main(int argc, char **argv)
{
	if(argc < 2)
	{
		printf("No input file specified. Exiting...\n");
		return 0;
	}
    
	printf("Using input file %s \n", argv[1]);

    return 0;
}
