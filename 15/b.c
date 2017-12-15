#include <stdio.h>
#include <stdlib.h>

#define MASK 0xFFFF
typedef unsigned long int lint;

void printBinary(lint a){
	for (int i = 63; i >= 0; i--)
	{
		printf("%i", (a >> i) & 1 > 0 ? 1 : 0);
	}
	printf("\n");
}

#define STACKSIZE 9000000

struct Stack{
	int count;
	int head;
	unsigned int *values;
};

void init(struct Stack *s){
	s->count = 0; 
	s->head = 0;
	s->values = (unsigned int*)malloc(sizeof(unsigned int) * STACKSIZE);
}

void defrag(struct Stack *s){
	for (int i = 0; i < s->count; i++) {
		s->values[i] = s->values[s->head + i];
	}
	s->head = 0;
}

void push(struct Stack *s, lint v){
	if (s->head + s->count >= STACKSIZE) { printf("STACK OVERFLOW!\n"); exit(-1);} 
	if (s->head + s->count > STACKSIZE - 2) defrag(s);
	s->values[s->head + s->count] = v;
	s->count++;
}

lint pop(struct Stack *s){
	if (s->count <= 0) return 0;
	lint a = s->values[s->head];
	s->count--;
	s->head++;
	return a;
}

int main(int argc, char const *argv[])
{
	struct Stack stack_a, stack_b;
	lint a = 873, b = 583;
	lint aa, bb;
	lint factor_a = 16807, factor_b = 48271;
	lint div = 2147483647;
	int judge = 0;
	
	init (&stack_a);
	init (&stack_b);

	int i = 0;
	do
	{
		a = (a * factor_a) % div;
		b = (b * factor_b) % div;
		if (a % 4 == 0) push(&stack_a, a);
		if (b % 8 == 0) push(&stack_b, b);
		
		if (stack_a.count > 0 && stack_b.count > 0){
			aa = pop(&stack_a);
			bb = pop(&stack_b);
			if ((aa & MASK) == (bb & MASK)) judge++;
			i++;
		}
	}
	while (i < 5000000);

	printf("%i coincidences\n", judge);
	free(stack_a.values);
	free(stack_b.values);
	return 0;
}