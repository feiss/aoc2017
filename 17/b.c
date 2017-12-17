#include <stdio.h>
#include <stdlib.h>

#define N 50000000

struct node{
	struct node *next;
	int value;
};

struct node* append(struct node *n, int value){
	struct node *a = (struct node*)calloc(1, sizeof(struct node));
	a->value = value;
	a->next = n == NULL ? NULL : n->next;
	if (n != NULL) n->next = a;
	return a;
}

int main(int argc, char const *argv[])
{
	int jump = 355;

	struct node* pos = NULL;
	struct node* buf = NULL;
	struct node* zero = NULL;

	buf = pos = zero = append(NULL, 0);
	pos = append(buf, 1);

	for (int i = 2; i < N; i++)
	{
		for (int j = 0; j < jump; j++) {
			pos = pos->next == NULL ? buf : pos->next;
		}
		pos = append(pos, i);

		if (i%100000 == 0) { printf("\r%i", i); fflush(stdout);}
	}
	
	printf("\nresult: %i\n", zero->next->value);
	return 0;
}