#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hash.h"



// from https://github.com/jhallen/joe-editor/blob/master/joe/hash.c
#define _hnext(accu, c) (((accu) << 4) + ((accu) >> 28) + (c))
static int _hashFunc(char *key)
{
  unsigned long accu = 0;
  while (*key) {
    accu = _hnext(accu, *key++);
  }
  return accu;
}

struct Hash* hnew(int size){
  struct Hash *h = (struct Hash*) malloc(sizeof(struct Hash));
  h->length = 0;
  h->size = size;
  h->table = (struct HashNode**) malloc(sizeof(struct HashNode*) * size);
  memset((void*)h->table, 0, sizeof(struct HashNode*) * size);
  return h;
}

void hdelete(struct Hash **hash){
  if (hash == NULL || *hash == NULL) return;
  struct Hash *h = *hash;
  for (int i = 0; i < h->size; i++) {
    if (h->table[i] != NULL){
      struct HashNode *n = h->table[i], *next;
      while (n){
        next = n->next;
        free(n->key);
        free(n);
        n = next;
      }
    }
  }
  free(*hash);
  *hash = NULL;
}

static struct HashNode* _hashSet(struct Hash *hash, char *key){
  int idx = _hashFunc(key) % hash->size;
  struct HashNode *node = malloc(sizeof(struct HashNode));
  node->key = (char*) malloc(sizeof(char) * (strlen(key) + 1) );
  strcpy(node->key, key);
  node->next = NULL;
  //colision! search last node
  if (hash->table[idx]){
    struct HashNode *ni = hash->table[idx];
    while (ni->next) ni = ni->next;
    ni->next = node;
  }
  else{
    hash->table[idx] = node;
  }

  hash->length++;
  return node;
}

void hsetc(struct Hash *hash, char *key, char value){
  struct HashNode *node = _hashSet(hash, key);
  node->value.c = value;
  node->value_type = HASH_CHAR;
  node->value_size = sizeof(char);
}
void hseti(struct Hash *hash, char *key, int value){
  struct HashNode *node = _hashSet(hash, key);
  node->value.i = value;
  node->value_type = HASH_INT;
  node->value_size = sizeof(int);
}
void hsetf(struct Hash *hash, char *key, float value){
  struct HashNode *node = _hashSet(hash, key);
  node->value.f = value;
  node->value_type = HASH_FLOAT;
  node->value_size = sizeof(float);
}
void hsets(struct Hash *hash, char *key, char *value){
  struct HashNode *node = _hashSet(hash, key);
  node->value.s = value;
  node->value_type = HASH_STRING;
  node->value_size = sizeof(char) * strlen(value);
}
void hsetp(struct Hash *hash, char *key, void *value){
  struct HashNode *node = _hashSet(hash, key);
  node->value.p = value;
  node->value_type = HASH_POINTER;
  node->value_size = sizeof(void*);
}

void hunset(struct Hash *hash, char *key){
  int idx = _hashFunc(key) % hash->size;
  struct HashNode *n = hash->table[idx], *p = NULL;
  for(; n && strcmp(n->key, key) != 0; p = n, n = n->next);
  if (n){
    if (!p) { hash->table[idx] = n->next; }
    else { p->next = n->next; };
    free(n->key);
    free(n);
    hash->length--;
  }    
}

struct HashNode* hget(struct Hash *hash, char *key){
  int idx = _hashFunc(key) % hash->size;
  struct HashNode *n = hash->table[idx];
  for(; n && strcmp(n->key, key) != 0; n = n->next);
  return n;
}

char hgetc(struct Hash *hash, char *key, char default_value){
  struct HashNode *n = hget(hash, key);
  return n == NULL ? default_value: n->value.c;
}
int hgeti(struct Hash *hash, char *key, int default_value){
  struct HashNode *n = hget(hash, key);
  return n == NULL ? default_value: n->value.i;
}
float hgetf(struct Hash *hash, char *key, float default_value){
  struct HashNode *n = hget(hash, key);
  return n == NULL ? default_value: n->value.f;
}
char* hgets(struct Hash *hash, char *key, char *default_value){
  struct HashNode *n = hget(hash, key);
  return n == NULL ? default_value: n->value.s;
}
void* hgetp(struct Hash *hash, char *key, void *default_value){
  struct HashNode *n = hget(hash, key);
  return n == NULL ? default_value: n->value.p;
}

void hashDebug(struct Hash *hash, int full_debug){
  char *TYPES[] = {"char", "int", "float", "string", "pointer"};
  struct HashNode *n;
  for (int i = 0; i < hash->size; i++)
  {
    if (hash->table[i]){
      int count = 0;
      printf("%i:", i);
      n = hash->table[i];
      while(n){
        if (full_debug){
          printf("\t\"%s\": (%s) ", n->key, TYPES[n->value_type]);
          switch(n->value_type){
            case HASH_CHAR: printf("\'%c\'\n", n->value.c); break;
            case HASH_INT : printf("%i\n", n->value.i); break;
            case HASH_FLOAT: printf("%f\n", n->value.f); break;
            case HASH_STRING: printf("\"%s\"\n", n->value.s); break;
            case HASH_POINTER: printf("%p\n", n->value.p); break;
          }
        }
        n = n->next;
        count++;
      }
      printf(" %i items\n", count);
    }
    else printf("%i: 0 items\n", i);
  }
  printf("%i items in hash.\n", hash->length);
}