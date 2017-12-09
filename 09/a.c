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
	int score = 0;

	len = fread(stream, 1, 25000, f);

	printf("%i bytes read\n", len);

	for (int i = 0; i < len; i++) {
		c = stream[i];
		switch(c){
			case '{': if (!ongarbage) depth ++;
			break;
			case '}': if (!ongarbage) { score += depth; depth --; num_groups ++; }
			break;
			case '!': i++;
			break;
			case '<': if (!ongarbage) ongarbage = 1;
			break;
			case '>': ongarbage = 0;
			break;

		}
	}

	printf("score: %i\n", score);
	fclose(f);
	return 0;
}