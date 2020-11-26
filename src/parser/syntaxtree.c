#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "syntaxtree.h"

struct stnode{
    char *name;
    NodeType type;
    NodeSubType subtype;
    stLink *children;
    stLink parent;
    int n;
};

void printTabs(int n){
    for (int i = 0; i < n; i++){
        printf("   ");
    }
}

char *stringType( NodeType type, NodeSubType subtype){
    char *ret;
    switch (type){
        case PROGRAM:
            ret = strdup("Program");
            break;
        case STATEMENT:
            ret = strdup("Statement");
            break;
        case ASSIGNMENT:
            ret = strdup("Assignment");
            break;
        case CALL:
            ret = strdup("Call");
            break;
        case EXPRESSION:
            ret = strdup("Expression");
            break;
        case FUNC:
            ret = strdup("Function declaration");
            break;
        case TERM:
            ret = strdup("Term");
            break;
        case FACTOR:
            ret = strdup("Factor");
            break;
        case BLOCK:
            ret = strdup("Block");
            break;
        case FUNCARGS:
            ret = strdup("Function arguments");
            break;
        case stIF:
            ret = strdup("If");
            break;
        case stELSE:
            ret = strdup("Else");
            break;
        case LEAF:
            switch(subtype){
                case stID:
                    ret = strdup("Identifier");
                    break;
                case stNUM:
                    ret = strdup("Number");
                    break;
                case stOP:
                    ret = strdup("Operation");
                    break;
                case stSYSCALL:
                    ret = strdup("System call");
                    break;
                case stSTRING:
                    ret = strdup("String");
                    break;
                default:
                    ret = strdup("Unkown Leaf");
                    break;
            }
            break;
        default:
            ret = strdup("Unkown");
            break;
    }
    return ret;
}


stLink stnodeCreate(char *name, NodeType nodetype, NodeSubType nodesubtype){
    stLink node = (stLink) malloc(sizeof(struct stnode));
    if (name != NULL)
        node->name = strdup(name);
    else
        node->name = NULL;
    node->type = nodetype;
    node->subtype = nodesubtype;
    node->children = NULL;
    node->n = 0;
    node->parent = NULL;
}

void stnodeFree(stLink link){
    free(link->name);
    free(link->children);
    free(link);
}

void stnodeAddChild(stLink parent, stLink child){
    if (parent->children == NULL)
        parent->children = (stLink *) malloc(sizeof(stLink));
    else
        parent->children = (stLink *) realloc(parent->children, sizeof(stLink)*(parent->n + 1));
    parent->children[parent->n] = child;
    child->parent = parent;
    parent->n += 1;
}

stLink sTreeCreate(){
    return stnodeCreate(NULL, PROGRAM, NOSUBTYPE);
}

stLink sTreeGetParent(stLink head){
    return head->parent;
}

void sTreeFree(stLink head){
    for (int i = 0; i < head->n; i++){
        sTreeFree((head->children)[i]);
    }
    stnodeFree(head);
}

void sTreePrintAux(stLink head, int n){
    char *string = NULL;
    if (head == NULL) return;
    string = stringType(head->type, head->subtype);
    if (string == NULL)
        return;
    printTabs(n);
    printf("%s {\n", string);
    free(string);

    if ((head->type == LEAF) && (head->name != NULL)){
            printTabs(n + 1);
            printf("%s\n", head->name);
    }else{
        for (int i = 0; i < head->n; i++)
            sTreePrintAux(head->children[i],n + 1);
    }
    printTabs(n);
    printf("}\n");
}

void sTreePrint(stLink head){
    sTreePrintAux(head, 0);
}