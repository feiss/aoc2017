#include <stdio.h>

#define N 256

void flip(int *list, int len, int pos, int skip){
	int aux;
	for (int i = 0; i < len / 2; ++i)
	{
		aux = list[(pos + i) % N];
		list[(pos + i) % N] = list[(pos + len - i - 1) % N];
		list[(pos + len - i - 1) % N] = aux;
	}
}


int main(int argc, char const *argv[])
{
	int lengths[] = {63,144,180,149,1,255,167,84,125,65,188,0,2,254,229,24};
	int ln = sizeof(lengths) / sizeof(lengths[0]);
	int list[N], i;
	int pos = 0, skip = 0;
	for (i = 0; i < N; ++i) { list[i] = i; }

	for (i = 0; i < ln; ++i) {
		flip(list, lengths[i], pos, skip);
		pos += lengths[i] + skip;
		skip++;
	}

	printf("result: %i\n", list[0] * list[1]);
	return 0;
}