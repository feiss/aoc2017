#include <stdio.h>
#include <string.h>

void sortString(char *s){
	int len = strlen(s);
	char c;
	for(int i = 1; i < len; i++){
		int j = i;
		while (j > 0 && s[j-1] > s[j]){
			c = s[j-1];
			s[j-1] = s[j];
			s[j] = c;
			j--;
		}
	}
}

void main(){
	FILE *f = fopen ("input", "rt");
	int valid = 0, nwords;
	char str[200], sorted[200];
	char *tokens[30], *tokens2[30];
	int ok;
	while(fgets(str, 200, f)){

		//tokenize str and get pointers to tokens
		nwords = 0;
		if (tokens[nwords] = strtok(str, " \n")) {
			tokens2[nwords] = sorted + (tokens[nwords] - str);
			nwords++; 
		}
		else continue;
		while(tokens[nwords] = strtok(NULL, " \n")) {
			tokens2[nwords] = sorted + (tokens[nwords] - str);
			nwords++;
		}

		//copy string and sort
		memcpy(sorted, str, 200);
		for (int i = 0; i < nwords; i++) { sortString(tokens2[i]); }

		ok = 1;
		for (int i = 0; i < nwords && ok; i++){
			for (int j = i + 1; j < nwords && ok; j++)
			{
				if (strcmp(tokens[i], tokens[j]) == 0 || strcmp(tokens2[i], tokens2[j]) == 0){
					ok = 0;
				}
			}
		}
		if (ok) valid++;
	}

	printf("valid: %i\n", valid);
	fclose(f);
}