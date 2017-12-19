#include <stdio.h>
#include <string.h>

#define W 200
#define H 200

int main(int argc, char const *argv[])
{
	char map[H][W], buf[300];

	FILE *f = fopen("input", "rt");
	for (int i = 0; i < H; i++) {
		fgets(buf, 1000, f);
		memcpy(map[i], buf, W);
	}
	fclose(f);

	int x = 0, y = 0, dir = 2; // like css: 0 up, 1 right, 2 down, 3 left
	char str[30] = "", stri = 0;

	while(map[0][x++] != '|');
	x--;

	while(1){
		if (dir % 2 == 1) x += dir == 1 ? 1 : -1; 
		if (dir % 2 == 0) y += dir == 0 ? -1 : 1; 
		switch(map[y][x]){
			case '|':
			break;
			case '-':
			break;
			case '+':
				if (dir == 0 || dir == 2) {
					if (map[y][x - 1] != ' ') dir = 3; 
					else if (map[y][x + 1] != ' ') dir = 1;
					else goto exit;
				}
				else {
					if (map[y - 1][x] != ' ') dir = 0; 
					else if (map[y + 1][x] != ' ') dir = 2;
					else goto exit;
				}
			break;
			case ' ':
				printf("UPS! blankspace reached at %i, %i\n", x, y); 
				goto exit;
			break;
			default:
				str[stri++] = map[y][x];
			break;
		}
		printf("%i %i %i\n", x, y, dir);
	}
exit:

	str[stri] = 0;
	printf("%s\n", str);
	return 0;
}