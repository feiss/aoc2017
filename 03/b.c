#include <stdio.h>
#include <stdlib.h>

#define N 10

void main(){
	int *matrix = (int*) calloc(N*N, sizeof(int));
	int radius = 1;
	int sum;
	int dx = 0, dy = -1, side = 0, step = 1, steps = 2;
	int x = N/2, y = N/2;
	matrix[y * N + x] = 1;
	matrix[y * N + x + 1] = 1;
	x++;
	do{
		x += dx;
		y += dy;
		sum = 0; 
		sum += matrix[(y + 1) * N + x - 1];
		sum += matrix[(y + 1) * N + x + 0];
		sum += matrix[(y + 1) * N + x + 1];
		sum += matrix[(y - 1) * N + x - 1];
		sum += matrix[(y - 1) * N + x + 0];
		sum += matrix[(y - 1) * N + x + 1];
		sum += matrix[(y + 0) * N + x - 1];
		sum += matrix[(y + 0) * N + x + 1];
		matrix[y * N + x] = sum;
		step++;
		if (step == steps) {
			step = 0;
			side ++;
			switch(side){
				case 1: dx = -1; dy = 0; break;
				case 2: dx = 0; dy = 1; break;
				case 3: dx = 1; dy = 0; step--; break;
				case 4: dx = 0; dy = -1; 
								steps += 2;
								side = 0;
								step = 1;
				break;
			}
		}
		printf("%i,%i = %i\n", x-N, y-N, sum);
	} while(sum < 361527);

	printf("result: %i\n", sum);

}
