#include <stdio.h>
#include <stdlib.h>

int main (int argc, const char * argv[])
{
	unsigned char a;
	unsigned char b;
	unsigned char c;
	int i;
	
	/* test AND operator */
	printf("Testing AND (&) operator\n");
	a = 85; // 01010101
	b = 1;
	
	for(i = 0; i < 8; i++){
		c = a & b;
		printf("c: %u <---> b: %u\n", c, b);
		b = b << 1;
	}
	
	/* test OR operator */
	printf("Testing OR (|) operator\n");
	a = 0; // 0
	b = 1; // 1
	
	for(i = 0; i < 8; i++){
		printf("Adding %u...\n", b);
		a = a | b;
		printf("a: %u <---> b: %u\n", a, b);
		b = b << 1;
	}
	
	return 0;
}