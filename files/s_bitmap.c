#include <stdio.h>
#include <stdlib.h>

// 200 million => 200,000,000
#define MAXSIZE 200000000

int main (int argc, const char * argv[])
{
	unsigned char a;
	unsigned char b;
	unsigned char c;
	int i;
	unsigned int j;
	unsigned char *bitmap;
	unsigned int num_bytes;
	unsigned int cur_byte;
	int cur_bit;
	int check_bit;
	unsigned int k;
	
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
		a |= b;
		printf("a: %u <---> b: %u\n", a, b);
		b = b << 1;
	}
	
	/* test bitmap by getting primes */
	num_bytes = MAXSIZE / 8 + 1;
	
	bitmap = (unsigned char *) malloc(num_bytes * sizeof(unsigned char));
	printf("Primes\n______\n");
	printf("1");
	for(i = 2; i < MAXSIZE; i++){
		cur_byte = (i - 1) / 8;
		cur_bit = (i - 1) % 8;
		check_bit = 1;
		if(!(bitmap[cur_byte] & (check_bit << cur_bit))) {
			printf("%u\n", i);
			for(j = i; j < MAXSIZE; j += i) {
				cur_byte = (j - 1) / 8;
				cur_bit = (j - 1) % 8;
				check_bit = 1;
				check_bit = check_bit << cur_bit;
				bitmap[cur_byte] |= check_bit;
			}
		}
	}
	
	printf("done\n");
	
	
	free(bitmap);
	return 0;
}