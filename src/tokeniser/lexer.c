#include <stdio.h>
#include <stdlib.h>
#include "tokenlib.h"

#define MAX_TOKEN_CHARS 200

int isLetter(char c){
    return (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')) || (c == '_'));
}

int isNumber(char c){
    return ((c >= '0') && (c <= '9'));
}

int isOperation(char c){
    return ((c == '+') || (c == '-') || (c == '*') || (c == '>') || (c == '<') || (c == '=') || (c == '!') || (c == '/') || (c == '&') || (c == '|'));
}

int isSymbol(char c){
    return ((c == '(') || (c == ')') || (c == '{') || (c == '}') || (c == ';') || (c == ',') || (c == '$') || (c == '.') || (c == ':'));
}

int isString(char c){
    return (c == '\"');
}

int isImplicitParagraph(char c){
    return (c == '\n');
}

int isSpecial(char c){
    return (c == '\\');
}

void clearBuffer(char *buffer, int *pointer){
    int i,p;
    p = *pointer;
    for (i = 0; i < p; i++){
        buffer[i] = '\0';
    }
    *pointer = 0;
}

void dumpBuffer(Link *token_list, int *state, char *buffer, int *pointer){
    tokenListAddLast(token_list,tokenCreate(*state,buffer));
    clearBuffer(buffer,pointer);
    *state = NONE;
}

Link tokenParse(char code[]){
    int i, bpoint, state;
    char buffer[MAX_TOKEN_CHARS];
    int special = 0;

    bpoint = 0;
    state = NONE;
    
    
    for (i = 0; i < MAX_TOKEN_CHARS; i++)
        buffer[i] = '\0';
    
    i = 0;
    Link token_list = tokenListCreate();

    while (code[i] != '\0'){
        if (bpoint < MAX_TOKEN_CHARS){

            switch (state){
                case NONE:
                    if (isLetter(code[i])){
                        state = ID;
                        buffer[bpoint++] = code[i];
                    }else if (isNumber(code[i])){
                        state = NUM;
                        buffer[bpoint++] = code[i];
                    }else if (isOperation(code[i])){
                        state = OP;
                        buffer[bpoint++] = code[i];
                    }else if (isSymbol(code[i])){
                        state = SYMB;
                        buffer[bpoint++] = code[i];
                        dumpBuffer(&token_list,&state,buffer,&bpoint);
                    }else if (isString(code[i])){
                        state = STR;
                    }
                    i++;
                    break;
                case ID:
                    if ((isLetter(code[i])) || (isNumber(code[i]))){
                        buffer[bpoint++] = code[i++];
                    }else{
                        dumpBuffer(&token_list,&state,buffer,&bpoint);
                    }
                    break;
                case NUM:
                    if (isNumber(code[i])){
                        buffer[bpoint++] = code[i++];
                    }else if ((isLetter(code[i]))){
                        printf( "An error ocurred while lexing, letter following number\n");
                        tokenListFree(token_list);
                        free(code);
                        exit(EXIT_FAILURE);
                    }else{
                        dumpBuffer(&token_list,&state,buffer,&bpoint);
                    }
                    break;
                case OP:
                    /* Check if it is a comment */
                    if ((code[i] == '*') && (buffer[bpoint - 1] == '/')){
                            buffer[bpoint - 1] == '\0';
                            printf("%d\n",bpoint);
                            if (bpoint > 2)
                                dumpBuffer(&token_list,&state,buffer,&bpoint);
                            else
                                clearBuffer(buffer,&bpoint);
                            i++;
                            state = CMNT;
                    /********************/
                    } else if (isOperation(code[i])){
                        buffer[bpoint++] = code[i++];
                    }else{
                        dumpBuffer(&token_list,&state,buffer,&bpoint);
                    }
                    break;
                case STR:
                    if (special){
                        special = 0;
                        if (code[i] == 'n'){
                            buffer[bpoint++] = '\n';
                        }
                        if (code[i] == '\\'){
                            buffer[bpoint++] = '\\';
                        }
                        i++;
                        break;
                    }
                    
                    if (isString(code[i])){
                        dumpBuffer(&token_list,&state,buffer,&bpoint);
                    }else if (isSpecial(code[i])){
                        special = 1;
                    }else if (!isImplicitParagraph(code[i])){
                        buffer[bpoint++] = code[i];
                    }
                    i++;
                    break;
                case CMNT:
                    if ((code[i] == '/') && (buffer[0] == '*')){
                        clearBuffer(buffer,&bpoint);
                        state = NONE;
                    }else{
                        buffer[0] = code[i];
                    }
                    i++;
                    break;
            }
        }else{
            printf("TOKEN IS TOO LARGE\n");
            tokenListFree(token_list);
            free(code);
            exit(EXIT_FAILURE);
        }
    }   

    return token_list;
}