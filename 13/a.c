#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	int firewall[] = {3,2,4,0,4,0,5,0,6,0,6,0,8,0,6,0,6,0,9,0,8,0,8,0,8,0,12,0,8,0,12,0,12,0,12,0,10,0,14,0,12,0,10,0,8,0,12,0,14,0,12,0,14,0,14,0,14,0,12,0,0,0,14,0,12,0,12,0,14,0,14,0,14,0,17,0,14,0,18,0,0,0,0,0,14,0,0,0,0,0,20,0,14};
	int n = sizeof(firewall) / sizeof(firewall[0]);
	int severity = 0, layer = 0;
	int *scanner = (int*)calloc(n, sizeof(int));
	int *direction = (int*)calloc(n, sizeof(int));
	int i;
	for (i = 0; i < n; i++) direction[i] = -1;

	while (layer < n){
		if (scanner[layer] == 0 && firewall[layer] > 0) severity += layer * firewall[layer];
		for (i = 0; i < n; i++){
			if (firewall[i] > 0) {
				if (scanner[i] == firewall[i] - 1 || scanner[i] == 0){ direction[i] *= -1; }
				scanner[i] += direction[i];
			}
		}
		layer++;
	}

	printf ("severity: %i\n", severity);
	free(scanner);
	free(direction);
	return 0;
}