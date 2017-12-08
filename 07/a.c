#include <stdio.h>
#include <string.h>

typedef struct Node{
	int parent;
	int children[16];
	int num_children;
	int weight;
	char name[32];
} Node;

Node nodes[3000];
int num_nodes = 0;


int findNode(char *name){
	for (int i = 0; i < num_nodes; ++i) {
		if (strcmp(nodes[i].name, name) == 0) return i;
	}
	return -1;
}

int addNode(char *line){
	if (!line) return 0;
	char name[32];
	int weight;
	int i;
	if (sscanf(line, "%s (%i) -->", name, &weight) != 2) return 0;
	i = findNode(name);
	if (i == -1) {
		i = num_nodes;
		strcpy(nodes[i].name, name);
		nodes[i].num_children = 0;
		nodes[i].parent = -1;
		num_nodes++;
	}

	nodes[i].weight = weight;
	//printf("%i %s %i\n", i, nodes[i].name, nodes[i].weight);

	// children
	char *chpos = strstr(line, "->");
	char *child;
	if (chpos == NULL) return 1;
	//printf("\t-");
	child = strtok(chpos, " ,->\n");
	int c;
	while (child){
		c = findNode(child);
		if (c == -1) {
			c = num_nodes++;
			strcpy(nodes[c].name, child);
			nodes[c].parent = -1;
			nodes[c].num_children = 0;
		}
		nodes[c].parent = i;
		nodes[i].children[nodes[i].num_children++] = c;

		//printf("[%s] ", child);
		child = strtok(NULL, " ,->\n");
	}
	//printf("\n");
	return 1;
}

void main(void){
	FILE *f = fopen("input", "rt");
	char line[1024];
	while(fgets(line, 1024, f)){
		addNode(line);
	}

	printf(" (%i nodes) only parents----\n", num_nodes);
	for (int i = 0; i < num_nodes; i++)
	{
		if (nodes[i].parent == -1) printf("%s\n", nodes[i].name);
	}

	fclose(f);
}