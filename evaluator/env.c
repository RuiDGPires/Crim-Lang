#include <stdio.h>
#include <stdlib.h>
#include "hashtable/hashtable.h"
#include "env.h"

struct env{
    Env parent;
    HTable table;
};

Env envCreate(Env parent){
    Env new = (Env) malloc(sizeof(struct env));
    new->parent = parent;
    new->table = htCreate();
    return new;
}

void envFree(Env env){
    htFree(env->table);
    free(env);
}

int envGet(int *val, Env env, char *name){
    if (htGet(val,env->table,name))
        return 1;
    else{
        if (env->parent != NULL)
            return envGet(val,env->parent, name);
        else
            return 0;
    }
}

void envAdd(Env env, char *name, int val){
    htAdd(env->table,name, val);
}

void envSet(Env env, char *name, int val){
    if (htSet(env->table, name, val) == 0){
        fprintf(stderr,"Error setting variable: not initialized\n");
        exit(EXIT_FAILURE);
    }
}

Env envGetParent(Env env){
    return env->parent;
}