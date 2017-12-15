#include <stdio.h>

#define MASK 0xFFFF
typedef unsigned long int lint;

void printBinary(lint a){
	for (int i = 63; i >= 0; i--)
	{
		printf("%i", (a >> i) & 1 > 0 ? 1 : 0);
	}
	printf("\n");
}

int main(int argc, char const *argv[])
{
	lint a = 873, b = 583;
	lint factor_a = 16807, factor_b = 48271;
	lint div = 2147483647;
	int judge = 0;
	for (lint i = 0; i < 40000000; i++)
	{
		a = (a * factor_a) % div;
		b = (b * factor_b) % div;
		if ((a & MASK) == (b & MASK)) judge++;
		/*
		printf("%lu \t", a);
		printBinary(a & MASK);
		printf("%lu \t", b);
		printBinary(b & MASK);
		printf("\n");
		*/
	}

	printf("%i coincidences\n", judge);
	return 0;
}