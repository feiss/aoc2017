#include <stdio.h>
#include <string.h>


int main(int argc, char const *argv[])
{
	FILE *f = fopen("input", "rt");
	char str[17]  = "abcdefghijklmnop";
	char str2[17] = "                ";
	char c, aux;
	int a,b;
	char x, y;
	char *xp, *yp;

	struct Step{
		char type, from, to;
	} steps[10000];
	int s=0;

	while((c = fgetc(f)) != EOF){
		switch(c){
			case 's': 
				fscanf(f, "%i,", &a);
				memcpy(str2, str + (16 - a), a);
				memcpy(str2 + a, str, 16 - a);
				memcpy(str, str2, 16);
				steps[s].type = c;
				steps[s].from = a;
				s++;
			break;
			case 'x':
				fscanf(f, "%i/%i,", &a, &b);
				aux = str[a]; str[a] = str[b]; str[b] = aux;
				steps[s].type = c;
				steps[s].from = a;
				steps[s].to = b;
				s++;
			break;
			case 'p':
				fscanf(f, "%c/%c,", &x, &y);
				xp = strchr(str, x);
				yp = strchr(str, y);
				aux = *xp; *xp = *yp; *yp = aux;
				steps[s].type = c;
				steps[s].from = x;
				steps[s].to = y;
				s++;
			break;
		}
	}

	int dances = 1;
	fclose(f);
	unsigned long j;
	for (j = 0; j < 1000000000; j++) {
		for (s = 0; s < 10000; s++) {
			a = steps[s].from;
			b = steps[s].to;
			switch(steps[s].type){
				case 's':
					//printf("s %i %s", a, str);
					memcpy(str2, str + (16 - a), a);
					memcpy(str2 + a, str, 16 - a);
					memcpy(str, str2, 16);
					//printf(" -> %s\n", str);
				break;
				case 'x':
					//printf("s %i %i %s", a, b, str);
					aux = str[a]; str[a] = str[b]; str[b] = aux;
					//printf(" -> %s\n", str);
				break;
				case 'p':
					//printf("p %c %c %s", a, b, str);
					xp = strchr(str, a);
					yp = strchr(str, b);
					aux = *xp; *xp = *yp; *yp = aux;
					//printf(" -> %s\n", str);
				break;
			}
		}
		dances++;
		if (j > 0 && j % 100000 == 0) printf("%lu\n", j);
		if (strcmp(str, "abcdefghijklmnop") == 0) {
			printf("same as original in %i dances\n", dances);
		}
	}
	printf("=== %s\n", str);
	return 0;
}
