#ifndef __LINKEDLISTINT__
#define __LINKEDLISTINT__



typedef struct llinode *lliNode;

lliNode lliCreate();

void lliAdd(lliNode *head, int val, char *name);

void lliFree(lliNode head);

void lliPrint(lliNode head);

int lliGetByName(int *val, lliNode head, char *name);

int lliSetByName(lliNode head, char *name, int val);

#endif