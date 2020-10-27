#ifndef __SYNTAXTREE__
#define __SYNTAXTREE__

typedef enum applyorder {PRE,IN,POST} ApplyOrder;
typedef enum nodetype {NOTYPE, PROGRAM, BLOCK, STATEMENT, ASSIGNMENT, FUNC, stIF, stELSE, CALL, FUNCARGS, EXPRESSION, TERM, FACTOR, LEAF} NodeType;
typedef enum nodesubtype {NOSUBTYPE, stID, stNUM, stOP, stSTRING, stCONST, stSYSCALL} NodeSubType;

typedef struct stnode *stLink;


stLink stnodeCreate(char *name, NodeType nodetype, NodeSubType nodesubtype);

void stnodeAddChild(stLink parent, stLink child);

stLink sTreeCreate();

void sTreeFree(stLink head);

stLink sTreeGetParent(stLink head);

void sTreePrint(stLink head);

#endif