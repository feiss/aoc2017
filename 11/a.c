#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max(x,y) ((x) > (y) ? (x) : (y))

int main(int argc, char const *argv[])
{
	FILE *f = fopen("input", "rt");
	char *b, dir[3] = {0,0,0};
	int i = 0, x = 0, y = 0;

	fseek(f, 0, SEEK_END); int size = ftell(f); rewind(f);
	b = (char*) malloc (size);
	fread(b, size, 1, f);
	fclose(f);
	
	while (i < size){
		dir[0] = b[i++];
		if (b[i] != ',') dir[1] = b[i++];
		else dir[1] = 0;
		i++;

		if      (strcmp(dir, "n") == 0) { y++; }
		else if (strcmp(dir, "s") == 0) { y--; }
		else if (strcmp(dir, "nw") == 0){ x--; }
		else if (strcmp(dir, "se") == 0){ x++; }
		else if (strcmp(dir, "ne") == 0){ x++; y++; }
		else if (strcmp(dir, "sw") == 0){ x--; y--; }

		//printf("%s -> %i, %i\n", dir, x, y);
	}
	printf("%i + %i = %i\n", x, y, max( max( abs(x) , abs(y)), abs(x-y)) );
	free(b);
	return 0;
}