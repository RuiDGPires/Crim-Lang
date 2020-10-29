#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashtable.h"
#include "superfasthash.h"
#include "linkedlistint.h"

#define HT_INIT_SIZE 53


struct htable{
    lliNode *vals;
    int size;
};

int hashFunc(char *string, int len){
    //return SuperFastHash(string,len);
    int sum = 0;
    int s_len = strlen(string);
    for (int i = 0; i < s_len; i++)
        sum += string[i];
    return sum % len;
}

HTable htCreate(){
    HTable table = (HTable) malloc(sizeof(struct htable));
    table->vals = (lliNode *) malloc(sizeof(lliNode) * HT_INIT_SIZE);
    for (int i= 0; i < HT_INIT_SIZE ; i++)
        table->vals[i] = NULL;
    table->size = HT_INIT_SIZE;
    return table;
}

void htFree(HTable table){
    for (int i = 0; i < table->size; i++)
        lliFree(table->vals[i]);
    free(table->vals);
    free(table);
}

void htAdd(HTable table, char *name, int val){
    int n = hashFunc(name,table->size);
    lliAdd(&(table->vals[n]), val, name);    
}

void htPrint(HTable table){
    for (int i = 0; i< table->size ; i++){
        printf("< %d >\t | ", i);
        lliPrint(table->vals[i]);
        printf("\n");
    }
}

int htGet(int *val, HTable table, char *name){
    int n = hashFunc(name,table->size);
    return lliGetByName(val, table->vals[n], name);
}

int htSet(HTable table, char *name, int val){
    int n = hashFunc(name,table->size);
    return lliSetByName(table->vals[n], name, val);
}