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

int checkBadBalance(int ni, int &correct_balance){
	struct Node *n = &(nodes[ni]);
	int *w = (int*)calloc(n->num_children, sizeof(int));
	int *nw= (int*)calloc(n->num_children, sizeof(int));

	int w0 = nodes[n->children[0]].accum_weight;
	int w1 = nodes[n->children[1]].accum_weight;
	int w2 = nodes[n->children[2]].accum_weight;

	if (w0 != w1 &&  w1 == w2){

	}

	for (int i = 0; i < n->num_children; i++){
		w[i] = nodes[n->children[0]].accum_weight;
		nw[i]++;
	}
	
	if (nodes[n->children[i]].accum_weight != w) {
			*correct_balance = nodes[n->children[i]].accum_weight - w;
			return n->children[i];
		}
	}
	free(w);
	free(nw);

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
	//printf("%s weight: %i, accum: %i\n", nodes[root].name, nodes[root].weight, nodes[root].accum_weight);
	
	int correct_balance = 0;
	int unbalanced_node = checkBadBalance(root, &correct_balance);
	printf("unbalanced %s: %i -> %i\n", nodes[unbalanced_node].name, nodes[unbalanced_node].accum_weight, correct_balance);
	fclose(f);
}