#include <stdio.h>
#include <string.h>

void main(){
	FILE *f = fopen ("input", "rt");
	int valid = 0;
	char str[200];
	char *token;
	while(fgets(str, 200, f)){
		printf("%s", str);
		token = strtok(str, " ");
		if (token) valid++;
		while(token) {
			int toklen = strlen(token);
			printf("%s %i\n", token, toklen);
			printf(">%s\n", str+toklen+1);
			char *found = strstr(token + toklen + 1, token); 
			if (found){
				char nextc = found[toklen];
				printf("%s _%c_\n", found, nextc);
				if (nextc == ' ' || nextc == '\n'){
					valid--;
					printf("--invalid--\n");
					break;
				}
			}
			token = strtok(NULL, " ");
		}
	}

	printf("valid: %i\n", valid);
}
