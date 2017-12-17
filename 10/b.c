#include <stdio.h>
#include <string.h>

#define N 256

void convertCode(int *code, int len, int *result, int *resultlength){
	char c[20];
	char str[1024];
	int i;
	str[0] = 0;
	for (i = 0; i < len; ++i)
	{
		sprintf(c, "%i,", code[i]);
		strcat(str, c);
	}
	str[strlen(str) - 1] = 0;
	for (i = 0; i < strlen(str); i++){
		result[i] = (int)str[i];
	}
	result[i++] = 17;
	result[i++] = 31;
	result[i++] = 73;
	result[i++] = 47;
	result[i] = 23;
	*resultlength = i;
}


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
	int input[2048], il;
	int lengths[2048] = {63,144,180,149,1,255,167,84,125,65,188,0,2,254,229,24};
	int ln = 16;
	int list[N], i;
	int pos = 0, skip = 0;
	for (i = 0; i < N; ++i) { list[i] = i; }

	convertCode(lengths, ln, input, &il);

	for (int j = 0; j < 64; j++)
	{
		for (i = 0; i < il; i++) {
			flip(list, input[i], pos, skip);
			pos += input[i] + skip;
			skip++;
		}
	}

	int res;
	for (i = 0; i < 16; ++i)
	{
		res  = list[i * 16 + 0];
		res ^= list[i * 16 + 1];
		res ^= list[i * 16 + 2];
		res ^= list[i * 16 + 3];
		res ^= list[i * 16 + 4];
		res ^= list[i * 16 + 5];
		res ^= list[i * 16 + 6];
		res ^= list[i * 16 + 7];
		res ^= list[i * 16 + 8];
		res ^= list[i * 16 + 9];
		res ^= list[i * 16 + 10];
		res ^= list[i * 16 + 11];
		res ^= list[i * 16 + 12];
		res ^= list[i * 16 + 13];
		res ^= list[i * 16 + 14];
		res ^= list[i * 16 + 15];
		printf("%02x", res);
	}
	printf("\n");

	return 0;
}