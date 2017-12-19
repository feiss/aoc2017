#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>
#include <time.h>

#define REG(x) (registers[(x) - 'a'])
#define VAL1(x) ((x).usereg1 ? REG((x).reg1) : (x).val1)
#define VAL2(x) ((x).usereg2 ? REG((x).reg2) : (x).val2)

#define SND 1
#define SET 2
#define ADD 3
#define MUL 4
#define MOD 5
#define JGZ 6
#define RCV 7



struct Op{
	int opcode;
	int usereg1;
	int usereg2;
	int reg1;
	int reg2;
	int val1;
	int val2;
} ops[50];

int numops = 0;

void addOp(char *op, char *p1, char *p2){
	struct Op *o = &(ops[numops]);
	if(strcmp(op, "snd") == 0) o->opcode = SND;
	else if(strcmp(op, "set") == 0) o->opcode = SET;
	else if(strcmp(op, "add") == 0) o->opcode = ADD;
	else if(strcmp(op, "mul") == 0) o->opcode = MUL;
	else if(strcmp(op, "mod") == 0) o->opcode = MOD;
	else if(strcmp(op, "jgz") == 0) o->opcode = JGZ;
	else if(strcmp(op, "rcv") == 0) o->opcode = RCV;

	if (isalpha(p1[0])){
		o->usereg1 = 1;
		o->reg1 = p1[0];
	}
	else{
		o->usereg1 = 0;
		o->val1 = atoi(p1);
	}

	if (isalpha(p2[0])){
		o->usereg2 = 1;
		o->reg2 = p2[0];
	}
	else{
		o->usereg2 = 0;
		o->val2 = atoi(p2);
	}

	numops ++;
}

void printop(int i){
	struct Op *o = &(ops[i]);
	printf("%i ", o->opcode);
	if (o->usereg1) printf("%c ", o->reg1); else printf("%i ", o->val1);
	if (o->opcode != SND && o->opcode != RCV && o->usereg2) printf("%c", o->reg2); else printf("%i", o->val2);
	printf("\n");
}


#define MAX_QUEUE 100000

struct Queue{
	int values[MAX_QUEUE];
	int start, end;
	pthread_mutex_t *mutex;
	pthread_cond_t *ready;
} qa = {start : 0, end : 0}, qb = {start : 0, end : 0};


void *task(void *pid){
	int id = *(int*)pid;
	long int registers[24];
	for (int i = 0; i < 24; i++) { registers[i] = 0; }
	int pc = 0;
	REG('p') = id;
	int sends = 0;
	printf("starting thread %i\n", id);

	struct Queue *q;

	while(1)
	{
		//printop(pc);

		switch(ops[pc].opcode){
			case SND:
				q = id == 0 ? &qa : &qb;
				pthread_mutex_lock(q->mutex);
				q->values[q->end++] = VAL1(ops[pc]);
				if (q->end >= MAX_QUEUE) { printf("EEERROR: queue full\n"); exit(-1); }
				pthread_mutex_unlock(q->mutex);
				pthread_cond_signal(q->ready);

				sends++;
				pc++;
			break;
			case RCV:
				q = id == 0 ? &qb : &qa;
				pthread_mutex_lock(q->mutex);
				if (q->start >= q->end){
					struct timespec ts;
					clock_gettime(CLOCK_REALTIME, &ts);
					ts.tv_sec += 5;
					int err = pthread_cond_timedwait(q->ready, q->mutex, &ts);
					if (err != 0){
						printf("thread %i se cansa de esperar (%i).", id, err);
						goto end;
					}
				}
				REG(ops[pc].reg1) = q->values[q->start++];
				pthread_mutex_unlock(q->mutex);

				pc++;
			break;
			case SET:
				REG(ops[pc].reg1) = VAL2(ops[pc]);
				pc++;
			break;
			case ADD:
				REG(ops[pc].reg1) += VAL2(ops[pc]);
				pc++;
			break;
			case MUL:
				REG(ops[pc].reg1) *= VAL2(ops[pc]);
				pc++;
			break;
			case MOD:
				REG(ops[pc].reg1) = REG(ops[pc].reg1) % VAL2(ops[pc]);
				pc++;
			break;
			case JGZ:
				if(VAL1(ops[pc]) > 0) { pc += VAL2(ops[pc]); }
				else pc++;
			break;
		}
		if (pc < 0 || pc >= numops) break;
	}
end:
	printf("end thread %i.\n", id);
	if (id == 1) printf("sends: %i\n", sends);
}




int main(int argc, char const *argv[])
{
	FILE *f = fopen("input", "rt");
	char op[4], p1[8], p2[8]; 
	int p1i;

	while (fscanf(f, "%s %s ", op, p1) != EOF){
		if (strcmp(op, "snd") != 0 && strcmp(op, "rcv") != 0){
			fscanf(f, "%s", p2);	
		}
		addOp(op, p1, p2);
		fscanf(f, "\n");
		//printop(numops - 1);
	};

	qa.mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
	qb.mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(qa.mutex, NULL);
	pthread_mutex_init(qb.mutex, NULL);
	qa.ready = (pthread_cond_t*)malloc(sizeof(pthread_cond_t));
	qb.ready = (pthread_cond_t*)malloc(sizeof(pthread_cond_t));
	pthread_cond_init(qa.ready, NULL);
	pthread_cond_init(qb.ready, NULL);

	pthread_t ta, tb;
	int id_a = 0, id_b = 1;
	pthread_create(&ta, NULL, task, &id_a);
	pthread_create(&tb, NULL, task, &id_b);

	pthread_join(ta, NULL);
	pthread_join(tb, NULL);

	fclose(f);
	return 0;
}