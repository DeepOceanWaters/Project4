#include <stdio.h>
#include <stdlib.h>

int main (int argc, const char * argv[])
{
	unsigned char a;
	unsigned char b;
	unsigned char c;
	int i;
	
	a = 85; // 01010101
	b = 1;
	
	for(i = 0; i < 8; i++){
	    c = a & b;
	    printf("c: %u <---> b: %u\n", c, b);
	    b = b << 1;
	}
	
	return 0;
}