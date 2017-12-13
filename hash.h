#pragma once

#define HASH_CHAR 0
#define HASH_INT 1
#define HASH_FLOAT 2
#define HASH_STRING 3
#define HASH_POINTER 4

union HashType{
  char c;
  int i;
  float f;
  char *s;
  void *p;
};

struct HashNode{
  char *key;
  struct HashNode *next;
  union HashType value;
  char value_type;
  int value_size;
};

struct Hash{
  struct HashNode **table;
  int length;
  int size;
};

struct Hash* hnew(int size);
void hdelete(struct Hash **hash);

void hsetc(struct Hash *hash, char *key, char value);
void hseti(struct Hash *hash, char *key, int value);
void hsetf(struct Hash *hash, char *key, float value);
void hsets(struct Hash *hash, char *key, char *value);
void hsetp(struct Hash *hash, char *key, void *value);

struct HashNode* hget(struct Hash *hash, char *key);
char  hgetc(struct Hash *hash, char *key, char default_value);
int   hgeti(struct Hash *hash, char *key, int default_value);
float hgetf(struct Hash *hash, char *key, float default_value);
char* hgets(struct Hash *hash, char *key, char *default_value);
void* hgetp(struct Hash *hash, char *key, void *default_value);

void  hunset(struct Hash *hash, char *key);

void hashDebug(struct Hash *hash, int full_debug);

