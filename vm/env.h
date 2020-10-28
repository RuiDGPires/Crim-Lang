#ifndef __ENV__
#define __ENV__

typedef struct env *Env;

Env envCreate(Env parent);

void envFree(Env env);

int envGet(int *val, Env env, char *name);

void envSet(Env env, char *name, int val);

void envAdd(Env env, char *name, int val);

Env envGetParent(Env env);

#endif