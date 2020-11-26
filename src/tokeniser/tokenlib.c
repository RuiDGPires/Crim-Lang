#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tokenlib.h"

struct token{
    Symbol sym;
    int type;
    char *string;
};  

struct node{
    Token token;
    Link next, previous;
    int size;
};



/* Create a token */
Token tokenCreate(int type, const char string[]){
    Token token = (Token) malloc(sizeof(struct node));
    Symbol sym = ODDSYM;
    switch (type){
        case ID:
            sym = IDENT;
            if (strcmp(string, "var") == 0)
                sym = VARSYM;
            else if (strcmp(string, "const") == 0)
                sym = CONSTSYM;
            else if (strcmp(string, "if") == 0)
                sym = IFSYM;
            else if (strcmp(string, "else") == 0)
                sym = ELSESYM;
            else if (strcmp(string, "while") == 0)
                sym = WHILESYM;
            else if (strcmp(string, "for") == 0)
                sym = FORSYM;
            else if (strcmp(string, "Func") == 0)
                sym = PROCSYM; // Procedure Symbol
            break;
        case NUM:
            sym = NUMBER;
            break;
        case STR:
            sym = STRING;
            break;
        case OP:
            if (strcmp(string,"+") == 0)
                sym = PLUS;
            else if (strcmp(string,"-") == 0)
                sym = MINUS;
            else if (strcmp(string, "*") == 0)
                sym = TIMES;
            else if (strcmp(string, "**") == 0)
                sym = POW;
            else if (strcmp(string, "/") == 0)
                sym = SLASH;
            else if (strcmp(string, "=") == 0){
                sym = BECOMES;
                type = SYMB;
            }else if (strcmp(string, "==") == 0)
                sym = EQL;
            else if (strcmp(string, ">=") == 0)
                sym = GEQ;
            else if (strcmp(string, "<=") == 0)
                sym = LEQ;
            else if (strcmp(string, ">") == 0)
                sym = GTR;
            else if (strcmp(string, "<") == 0)
                sym = LSS;
            else if (strcmp(string, "!=") == 0)
                sym = NEQ;
            else if (strcmp(string, "&") == 0)
                sym = BINAND;
            else if (strcmp(string, "|") == 0)
                sym = BINOR;
            else if (strcmp(string, "||") == 0)
                sym = OR;
            else if (strcmp(string, "&&") == 0)
                sym = AND;
            else if (strcmp(string, "!") == 0)
                sym = NOTSYM;
            break;
        case SYMB:
            if (strcmp(string,"{") == 0)
                sym = BEGINSYM;
            else if (strcmp(string,"}") == 0)
                sym = ENDSYM;
            else if (strcmp(string, "(") == 0)
                sym = LPAREN;
            else if (strcmp(string, ")") == 0)
                sym = RPAREN;
            else if (strcmp(string, ".") == 0)
                sym = PERIOD;
            else if (strcmp(string, ";") == 0)
                sym = SEMICLN;
            else if (strcmp(string, ",") == 0)
                sym = COMMA;
            else if (strcmp(string, ":") == 0)
                sym = CLN;
            else if (strcmp(string, "$") == 0)
                sym = SYSTEMCALL;
            break;
    }

    if (sym == ODDSYM){
        fprintf(stderr,"********\nInvalid token found\n********\n");
        exit(EXIT_FAILURE);
    }

    token->sym = sym;
    token->type = type;
    token->string = strdup(string);
     
    if (token->string == NULL){
        fprintf(stderr,"ERROR: MEMMORY ALOCATION ERROR\n");
        exit(EXIT_FAILURE);
    }

    return token;
}

char *tokenGetString(Token token){
    if (token == NULL)
        return NULL;
    return token->string;
}

int tokenGetType(Token token){
    return token->type;
}

int tokenGetSym(Token token){
    return token->sym;
}

/* Prints the information of a token */
void tokenPrint(Token token){
    char string[10];
    memset(string, '\0', sizeof(string));
    switch (token->type){
        case ID:
            strcpy(string, "ID");
            break;
        case SYMB:
            strcpy(string, "SYMB");
            break;
        case OP:
            strcpy(string, "OP");
            break;
        case NUM:
            strcpy(string, "NUM");
            break;
        case STR:
            strcpy(string, "STR");
            break;
        case CMNT:
            strcpy(string, "CMNT");
            break;
    }
    printf("Type: %s | Symb: %d | Val: %s\n", string, token->sym, token->string);
}

/* Frees a token */
void tokenFree(Token token){
    free(token->string);
    free(token);
}

/* Create a token list */
Link tokenListCreate(){
    return NULL;
}

/* Creates a node to a list */
Link tokenListNewNode(Token token){
    Link link = (Link) malloc(sizeof(struct node));
    if (link == NULL){
        fprintf(stderr,"ERROR: MEMMORY ALOCATION ERROR\n");
        exit(EXIT_FAILURE);
    }
    link->token = token;
    link->next = NULL;
    link->previous = NULL;
    link->size = 1;
    return link;
}

void tokenListFreeNode(Link node){
    tokenFree(node->token);
    free(node);
}

void tokenListFree(Link head){
    if (head == NULL)
        return;
    tokenListFree(head->next);
    tokenListFreeNode(head);
}

void tokenListAddLast(Link *head, Token token){
    if (*head == NULL){
        *head = tokenListNewNode(token);
        return;
    }
    (*head)->size += 1;
    if ((*head)->next == NULL){
        Link node = tokenListNewNode(token);
        (*head)->next = node;
        node->previous = *head;
    }else{
        tokenListAddLast(&((*head)->next),token);
    }
}

void tokenListAddFirst(Link *head, Token token){
    if (*head == NULL){
        *head = tokenListNewNode(token);
        return;
    }
    Link node = tokenListNewNode(token);
    node->next = *head;
    node->size += (*head)->size;


    (*head)->previous = node;
    *head = node;
}


void tokenListApply(Link head,void (*func)(Token)){
    if (head == NULL)
        return;
    else{
        func(head->token);
        tokenListApply(head->next,func);
    }
}

void tokenListPrint(Link head){
    tokenListApply(head,tokenPrint);
}

int tokenListSize(Link head){
    if (head == NULL)
        return 0;
    return head->size;
}

Token tokenListGetTokenAtPosition(Link head,int position){
    int n = 0;
    Link current_head = head;

    while ((n++ != position) && (current_head != NULL)){
        current_head = current_head->next;
    }

    if (current_head == NULL)
        return NULL;
    return current_head->token;
}

Token tokenListGetToken(Link head){
    return head->token;
}

Link tokenListGetNextLink(Link head){
    if (head == NULL)
        return NULL;
    return head->next;
}

Link tokenListGetPreviousLink(Link head){
    if (head == NULL)
        return NULL;
    return head->previous;
}


/* ----------------------------------------------------------------- */
