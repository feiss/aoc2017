#include <stdio.h>
#include <stdlib.h>

#define N 50000000

int main(int argc, char const *argv[])
{
	int jump = 355;
	int *buf = (int*)calloc(N, sizeof(int));
	int pos = 1;
	buf[0] = 0;
	buf[1] = 1;

	for (int i = 2; i < N; i++)
	{
		pos = (pos + jump) % i + 1;
		printf("pos %i\n", pos);
		for (int j = i; j > pos; j--) {
			buf[j] = buf[j-1];
		}
		buf[pos] = i;
	
		for (int k = 0; k < i + 1; k++) {
			printf("%i ", buf[k]);
		}
		printf("\n");
	}
	
	printf("result: %i\n", buf[pos+1]);
	free(buf);
	return 0;
}