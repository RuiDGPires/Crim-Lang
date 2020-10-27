#ifndef __HASHTABLE__
#define __HASHTABLE__

typedef struct htable *HTable;

HTable htCreate();

void htFree(HTable table);

void htAdd(HTable table, char *name, int val);

void htPrint(HTable table);

int htGet(int *val, HTable table, char *name);

int htSet(HTable talbe, char *name, int val);

#endif