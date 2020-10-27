#include "linkedlistint.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct llinode{
    int val;
    char *name;
    lliNode next;
};


lliNode lliCreate(){
    return NULL;
}

void lliAdd(lliNode *head, int val, char *name){
    if (*head == NULL){
        *head = (lliNode) malloc(sizeof(struct llinode));
        (*head)->next = NULL;
        (*head)->name = strdup(name);
        (*head)->val = val;
    }else{
        lliAdd(&((*head)->next), val, name);
    }
}

void lliFree(lliNode head){
    if (head != NULL){
        lliFree(head->next);    
        free(head->name);
        free(head);
    }
}

void lliPrint(lliNode head){
    if (head != NULL){
        printf("%d->",head->val);
        lliPrint(head->next);
    }
}

int lliGetByName(int *val, lliNode head, char *name){
    if (head == NULL)
        return 0;
    if (strcmp(head->name,name) == 0){
        *val = head->val;
        return 1;
    }
    return lliGetByName(val,head->next, name);
}

int lliSetByName(lliNode head, char *name, int val){
    if (head == NULL)
        return 0;
    if (strcmp(head->name,name) == 0){
        head->val = val;
        return 1;
    }
    return lliSetByName(head->next,name, val);
}