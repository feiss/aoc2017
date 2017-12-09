#include <stdio.h>


int main(int argc, char const *argv[])
{
	FILE *f = fopen("input", "rt");

	char stream[25000];
	int len;
	char c;
	int ongarbage = 0;
	int depth = 0;
	int num_groups = 0;
	int garbage_chars = 0;


	len = fread(stream, 1, 25000, f);

	printf("%i bytes read\n", len);

	for (int i = 0; i < len; i++) {
		c = stream[i];
		switch(c){
			case '{': if (!ongarbage) depth ++; else garbage_chars ++;
			break;
			case '}': if (!ongarbage) { depth --; num_groups ++; } else garbage_chars ++;
			break;
			case '!': i++;
			break;
			case '<': if (!ongarbage) ongarbage = 1; else garbage_chars ++;
			break;
			case '>': ongarbage = 0;
			break;
			default: if (ongarbage) garbage_chars ++;
		}
	}

	printf("garbage characters: %i\n", garbage_chars);
	fclose(f);
	return 0;
}