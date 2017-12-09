#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node{
	int parent;
	int children[16];
	int num_children;
	int weight;
	int accum_weight;
	char name[32];
} Node;

Node nodes[3000];
int num_nodes = 0;

int calcAccumWeights(struct Node *n){
	if (n->num_children == 0) {
		n->accum_weight = n->weight;
		return n->accum_weight;
	}
	int a = n->weight;
	for (int i = 0; i < n->num_children; i++){
		a += calcAccumWeights(&(nodes[n->children[i]]));
	}
	n->accum_weight = a;
	return a;
}

int checkBadBalance(int ni){
	struct Node *n = &(nodes[ni]);
	if (n->num_children < 2) return 0;

	int w = nodes[n->children[0]].accum_weight;
	for (int i = 1; i < n->num_children; i++){
		if (w != nodes[n->children[i]].accum_weight){
			return nodes[n->children[i]].weight - (nodes[n->children[i]].accum_weight - nodes[n->children[0]].accum_weight);
		}
	}

	int bad = 0;
	for (int i = 0; i < n->num_children; i++){
		bad = checkBadBalance(n->children[i]);
		if (bad) return bad;
	}
	return 0;
}


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

void printdebug(int depth, struct Node *n){
	char indent[50] = "";
	int d = depth;
	indent[d + 1] = 0;
	while(d > 0){
		indent[d] = ' ';
		d--;
	}
	printf("%s%s %i (%i)\n", indent, n->name, n->weight, n->accum_weight);
	for (int i = 0; i < n->num_children; i++) {
		printf("--- %s\n", nodes[n->children[i]].name);
		printdebug(depth + 1, &(nodes[n->children[i]]));
	}
}

void main(void){
	FILE *f = fopen("input", "rt");
	char line[1024];
	while(fgets(line, 1024, f)){
		addNode(line);
	}
	int root = 0;

	printf(" (%i nodes) only parents----\n", num_nodes);
	for (int i = 0; i < num_nodes; i++)
	{
		if (nodes[i].parent == -1) root = i;
	}


	calcAccumWeights(&(nodes[root]));
	printdebug(0, &(nodes[root]));
	//printf("%s weight: %i, accum: %i\n", nodes[root].name, nodes[root].weight, nodes[root].accum_weight);
	
	int correct_balance = checkBadBalance(root);

	printf("correct balance %i\n", correct_balance);
	fclose(f);
}