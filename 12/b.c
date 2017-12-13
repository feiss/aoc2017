#include <stdio.h>
#include <string.h>
int connections[2000][10];
int connected[2000];

void spread(int n){
	for (int i = 0; connections[n][i] >= 0; i++){
		int c = connections[n][i];
		if (connected[c] == 0) {
			connected[c] = 1;
			spread(c);
		}
	}
}

int main(int argc, char const *argv[])
{
	int a, b, c;
	FILE *f = fopen("input", "rt");
	memset(connected, 0, 2000);

	for(int i = 0; i < 2000; i++){
		c = 0;
		fscanf(f, "%i <-> %i", &a, &b);
		connections[a][c++] = b;
		while(fscanf(f, ", %i", &b) == 1) connections[a][c++] = b;
		connections[a][c] = -1;
	}
	fclose(f);

	int count = 0;
	for (int i = 0; i < 2000; ++i) {
		if (connected[i] == 0) {
			count ++;
			spread(i);
		}
	}

	printf("%i groups\n", count);
	return 0;
}