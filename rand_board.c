#include "main.h"

void main(int argc, char  *argv[])
{
	/* code */
	srand(time(NULL));
	int num = rand() % 21;
	printf("First number: %d\n", num);
}
