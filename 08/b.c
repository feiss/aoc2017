#include <stdio.h>
#include <string.h>

struct Reg{
	char name[10];
	int value;
} registers[2048];

int num_registers = 0;

struct Reg *getRegister(char *name){
	for (int i = 0; i < num_registers; ++i) {
		if (strcmp(name, registers[i].name) == 0) return &(registers[i]);
	}
	return NULL;
}

int checkVal(char *r, char *comp, int val){
	struct Reg *reg = getRegister(r);
	if (reg == NULL) return 0;
	if (strcmp(comp, ">") == 0) return reg->value > val;
	if (strcmp(comp, ">=") == 0) return reg->value >= val;
	if (strcmp(comp, "<") == 0) return reg->value < val;
	if (strcmp(comp, "<=") == 0) return reg->value <= val;
	if (strcmp(comp, "==") == 0) return reg->value == val;
	if (strcmp(comp, "!=") == 0) return reg->value != val;
	return 0;
}

int setVal(char *r, char *op, int val){
	struct Reg *reg = getRegister(r);
	if (reg == NULL) return 0;
	if (strcmp(op, "inc") == 0) reg->value += val;
	else if (strcmp(op, "dec") == 0) reg->value -= val;
	return reg->value;
}

void main (void){
	FILE *f = fopen("input", "rt");
	char r[10], op[4], rc[10], comp[3];
	int val, cval; 

	while(fscanf(f, "%s %s %i if %s %s %i\n", r, op, &val, rc, comp, &cval) > 0){
		if (getRegister(r) == NULL) {
			strcpy(registers[num_registers].name, r);
			registers[num_registers].value = 0;
			num_registers++;
			strcpy(registers[num_registers].name, rc);
			registers[num_registers].value = 0;
			num_registers++;
		}
	}

	rewind(f);

	int max = -9999999, v;
	while(fscanf(f, "%s %s %i if %s %s %i\n", r, op, &val, rc, comp, &cval) > 0){
		if (checkVal(rc, comp, cval)){
			v = setVal(r, op, val);
			if (v > max) max = v;
		}
	}

	printf("\nmax: %i\n", max);

	fclose(f);
}