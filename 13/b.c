#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	int firewall[] = {3,2,4,0,4,0,5,0,6,0,6,0,8,0,6,0,6,0,9,0,8,0,8,0,8,0,12,0,8,0,12,0,12,0,12,0,10,0,14,0,12,0,10,0,8,0,12,0,14,0,12,0,14,0,14,0,14,0,12,0,0,0,14,0,12,0,12,0,14,0,14,0,14,0,17,0,14,0,18,0,0,0,0,0,14,0,0,0,0,0,20,0,14};
	int n = sizeof(firewall) / sizeof(firewall[0]);
	int *scanner = (int*)calloc(n, sizeof(int));
	int *direction = (int*)calloc(n, sizeof(int));
	int i;
	int severity, layer, delay = 0;
	int scannerpos[93][20];

	for (i = 0; i < n; i++) {
		int p = 0, dir = 1;
		for (int j = 0; j < firewall[i]; j++) {
			scannerpos[i][j] = j;
			if (j < firewall[i] - 1 ) scannerpos[i][firewall[i] * 2 - 2 - j] = j;
		}
	}

	int time = 0;
	do{
		severity = 0;
		layer = 0;
		time = delay;

		while (layer < n){
			if (layer >= 0 && firewall[layer] > 0 && scannerpos[layer][time % (firewall[layer] * 2 - 2)] == 0 ) severity += (layer + 1) * firewall[layer];
			time ++;
			layer++;
		}

		if (delay % 1000 == 0) {printf("\rdelay %i", delay); fflush(stdout);}
		if (severity > 0) delay += 2;
	}
	while (severity > 0 );


	printf("\nseverity %i on delay %i\n", severity, delay);
	free(scanner);
	free(direction);
	return 0;
}