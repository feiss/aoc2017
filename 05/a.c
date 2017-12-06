#include <stdio.h>

void main(void){
	FILE *f = fopen("input", "rt");
	int jumps[2000], steps = 0, numjumps = 0, pos = 0, offset;
	while(fscanf(f, "%i\n", &(jumps[numjumps++])) > 0 );
	numjumps--;
	while (pos >= 0 && pos < numjumps){
		offset = jumps[pos] >= 3? -1 : 1;
		jumps[pos]+= offset;
		pos += jumps[pos] - offset;
		steps++;
	}
	printf("%i steps\n", steps);
	fclose(f);
}