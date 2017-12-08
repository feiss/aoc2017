#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 16

struct Config{
	int a[N]; 
	struct Config *next;
};

int arrayMax(int a[]){
	int max = -1, maxi = -1;
	for (int i = 0; i < N; i++) {
		if (a[i] > max) { max = a[i]; maxi = i; }
	}
	return maxi;
}

int findHistory(struct Config *list, struct Config *c){
	struct Config *p = list;
	int it = 0;
	while (p && p!=c){
		int found = 1;
		for (int i = 0; i < N; i++) {
			if (p->a[i] != c->a[i]) { found = 0; break; }
		}
		if (found) return it;
		it++;
		p = p->next;
	}
	return 0;
}

struct Config * redistribute(struct Config *c){
	struct Config* n = (struct Config *)malloc(sizeof(struct Config));
	c->next = n;
	int m = arrayMax(c->a);
	int count = c->a[m];

	memcpy(n->a, c->a, N * sizeof(int));
	n->a[m] = 0;
	for (int i = (m + 1) % N; count > 0; i = (i+1) % N)	{
		n->a[i]++;
		count--;
	}
	return n;
}

void debugConfig(struct Config *c){
	for (int i = 0; i < N; ++i)
	{
		printf("%i ", c->a[i]);
	}
	printf("%p\n", c->next);
}


void main(void){
 	struct Config configs = {{4, 10, 4, 1, 8, 4, 9, 14, 5, 1, 14, 15, 0, 15, 3, 5}, NULL };
	struct Config *last = &configs, *list = &configs;
	int steps = 0, loopsize = 0;
	debugConfig(list);
	do {
		last = redistribute(last);
		//debugConfig (last);
		steps ++;
	}
	while ((loopsize = findHistory(list, last)) == 0);

	printf("%i steps, %i loopsize\n", steps, steps - loopsize);
}

