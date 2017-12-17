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



	while((c = fgetc(f)) != EOF){
		switch(c){
			case 's': 
			fscanf(f, "%i,", &a);
			memcpy(str2, str + (16 - a), a);
			memcpy(str2 + a, str, 16 - a);
			memcpy(str, str2, 16);
			break;
			case 'x':
			fscanf(f, "%i/%i,", &a, &b);
			aux = str[a]; str[a] = str[b]; str[b] = aux;
			break;
			case 'p':
			fscanf(f, "%c/%c,", &x, &y);
			xp = strchr(str, x);
			yp = strchr(str, y);
			aux = *xp; *xp = *yp; *yp = aux;
			break;
		}
	}
	printf("%s\n", str);
	fclose(f);
	return 0;
}