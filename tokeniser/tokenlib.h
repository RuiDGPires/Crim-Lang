#ifndef __TOKENLIB__
#define __TOKENLIB__

enum TokenTypes{NONE, ID, OP, SYMB, NUM, STR, CMNT};

typedef enum {IDENT, NUMBER, LPAREN, RPAREN, TIMES, SLASH, PLUS, STRING, NOTSYM, SYSTEMCALL,
    MINUS, POW, EQL, NEQ, LSS, LEQ, GTR, GEQ, CALLSYM, BEGINSYM, SEMICLN, 
    ENDSYM, BECOMES, CONSTSYM, IFSYM, ELSESYM, WHILESYM, FORSYM, VARSYM, COMMA, PROCSYM, PERIOD, BINOR, BINAND, OR, AND, ODDSYM, CLN, ENDCODE} Symbol;


typedef struct token *Token;
typedef struct node *Link;

Token tokenCreate(int type,const char string[]);

char *tokenGetString(Token token);

int tokenGetType(Token token);

int tokenGetSym(Token token);

void tokenPrint(Token token);

void tokenFree(Token token);

Link tokenListCreate();

void tokenListFree(Link head);

void tokenListAddLast(Link *head, Token token);

void tokenListAddFirst(Link *head, Token token);

void tokenListApply(Link head,void (*func)(Token));

void tokenListPrint(Link head);

int tokenListSize(Link head);

Token tokenListGetAtPosition(Link head,int position);

Token tokenListGetToken(Link head);

Link tokenListGetNextLink(Link head);

Link tokenListGetPreviousLink(Link head);

#endif