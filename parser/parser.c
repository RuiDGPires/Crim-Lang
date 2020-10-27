#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "parser.h"

Symbol sym;
Link token_list, head;
stLink syntax_tree;

/* Gets the next symbol from the token list */
void nextSym(){
    token_list = tokenListGetNextLink(token_list);
    if (token_list == NULL)
        sym = ENDCODE;
    else
        sym = tokenGetSym(tokenListGetToken(token_list));
}

/* Get's the previous token's string */
char *prevValue(){
    return tokenGetString(tokenListGetToken(tokenListGetPreviousLink(token_list)));
}

/* Raise Error */
void error(const char msg[]){
    fprintf(stderr,"%s\n",msg);
    tokenListFree(head);
    exit(EXIT_FAILURE);
}

/* Sets a new token list to parse */
void parserSetList(Link new_token_list){
    token_list = new_token_list;
    head = new_token_list;
}

/* Create the syntax tree... */
void syntaxTreeInit(){
    syntax_tree = sTreeCreate(PROGRAM, NOSUBTYPE, NULL);
}

/* Goes up on the syntax tree, to the parent of the current node */
void syntaxTreeBack(){
    stLink parent = sTreeGetParent(syntax_tree);
    if (parent == NULL){
        fprintf(stderr, "SYNTAX TREE ERROR: TOO MANY BACKS");
        sTreeFree(syntax_tree);
        exit(EXIT_FAILURE);
    }else
        syntax_tree = parent;
}

/* Adds a new node to the syntax tree. Always jumps to the created node unless it's a leaf */
void syntaxTreeAdd(NodeType type, NodeSubType subtype, char *name){
    stLink node = stnodeCreate(name,type,subtype);
    stnodeAddChild(syntax_tree,node);
    if (type != LEAF)
        syntax_tree = node;
}

/* Accept a symbol */
int accept(Symbol s){
    if (sym == s){
        nextSym();
        return 1;
    }
    return 0;
}

/* Expect a symbol */
int expect(Symbol s){
    if (accept(s))
        return 1;
    error("expect: unexpected symbol");
    return 0;
}

/* Accept all arguments of a function call */
void arguments(){
    syntaxTreeAdd(FUNCARGS,NOSUBTYPE,NULL);
    if (accept(IDENT)){
        syntaxTreeAdd(LEAF,stID,prevValue());
        while(accept(COMMA)){
            expect(IDENT);
            syntaxTreeAdd(LEAF,stID,prevValue());
        }
    }
    syntaxTreeBack();
}

void factor(){
    char *holder;
    syntaxTreeAdd(FACTOR,NOSUBTYPE,NULL);
    if (accept(IDENT)) {
        holder = prevValue();
        if (accept(LPAREN)){
            syntaxTreeAdd(CALL,NOSUBTYPE,NULL);
            syntaxTreeAdd(LEAF,stID,holder);
            if (accept(RPAREN)){
                ;
            }else{
                expression();
                while(accept(COMMA))
                    expression();
                expect(RPAREN);
            }
            syntaxTreeBack();
        }else
            syntaxTreeAdd(LEAF,stID,prevValue());
    } else if (accept(NUMBER)) {
        syntaxTreeAdd(LEAF,stNUM,prevValue());
    } else if (accept(STRING)) {
        syntaxTreeAdd(LEAF,stSTRING,prevValue());
    } else if (accept(LPAREN)) {
        expression();
        expect(RPAREN);
    } else {
        error("factor: syntax error");
        nextSym();
    }
    syntaxTreeBack();
}

void term(){
    syntaxTreeAdd(TERM,NOSUBTYPE,NULL);
    factor();
    while (sym == TIMES || sym == SLASH) {
        nextSym();
        syntaxTreeAdd(LEAF,stOP,prevValue());
        factor();
    }
    syntaxTreeBack();
}

void expression(){
    syntaxTreeAdd(EXPRESSION,NOSUBTYPE,NULL);
    if (accept(MINUS)){
        syntaxTreeAdd(LEAF,stNUM,"0");
        syntaxTreeAdd(LEAF,stOP,"-");
    }
    term();
    
    while (sym == PLUS || sym == MINUS || sym == EQL || sym == NEQ || sym == LSS || sym == LEQ || sym == GTR || sym == GEQ) {
        nextSym();
        syntaxTreeAdd(LEAF,stOP,prevValue());
        term();
    }
    syntaxTreeBack();
}

void block(Symbol endsymbol) {
    syntaxTreeAdd(BLOCK,NOSUBTYPE,NULL);
    while (accept(VARSYM)) {
        do {
            syntaxTreeAdd(ASSIGNMENT,NOSUBTYPE,NULL);
            expect(IDENT);
            syntaxTreeAdd(LEAF,stID,prevValue());
            if (accept(BECOMES)){
                syntaxTreeAdd(LEAF,stOP,prevValue());
                if (accept(PROCSYM)){
                    syntaxTreeAdd(FUNC,NOSUBTYPE,NULL);
                    expect(LPAREN);
                    arguments();
                    expect(RPAREN);
                    expect(BEGINSYM);
                    block(ENDSYM);
                    syntaxTreeBack();
                }else{
                    expression();
                }
            }
            syntaxTreeBack();
        } while (accept(COMMA));
        expect(SEMICLN);
    }

    while (sym != endsymbol)
        statement();
    nextSym();
    syntaxTreeBack();
}

void statement() {
    char *holder;
    if (accept(SYSTEMCALL)){
        expect(STRING);
        syntaxTreeAdd(LEAF,stSYSCALL,prevValue());
        expect(SEMICLN);
    }else if (accept(IDENT)) {
        holder = prevValue();
        if (accept(BECOMES)){
            syntaxTreeAdd(ASSIGNMENT,NOSUBTYPE,NULL);
            syntaxTreeAdd(LEAF,stID,holder);
            syntaxTreeAdd(LEAF,stOP,prevValue());
            expression();
            syntaxTreeBack();
        }else if (accept(LPAREN)){
            syntaxTreeAdd(CALL,NOSUBTYPE,NULL);
            syntaxTreeAdd(LEAF,stID,holder);
            if (accept(RPAREN)){
                ;
            }else{
                expression();
                while(accept(COMMA))
                    expression();
                expect(RPAREN);
            }
            syntaxTreeBack();
        }else
            error("factor: syntax error");
        expect(SEMICLN);
    } else if (accept(IFSYM)) {
        syntaxTreeAdd(stIF,NOSUBTYPE, NULL);
        expect(LPAREN);
        expression();
        expect(RPAREN); 
        expect(BEGINSYM);
        block(ENDSYM);
        if (accept(ELSESYM)){
            syntaxTreeAdd(stELSE,NOSUBTYPE, NULL);
            expect(BEGINSYM);
            block(ENDSYM);
            syntaxTreeBack();
        }
        syntaxTreeBack();
    } else if (accept(WHILESYM)) {
        expect(LPAREN);
        expression();
        expect(RPAREN);
        expect(BEGINSYM);
        block(ENDSYM);
    }
    else {
        error("statement: syntax error");
    }
}

stLink program(Link new_token_list) {
    parserSetList(new_token_list);
    syntaxTreeInit();
    if (token_list != NULL){
        sym = tokenGetSym(tokenListGetToken(token_list));
        
        if (accept(CONSTSYM)) {
            do {
                syntaxTreeAdd(ASSIGNMENT,stCONST,NULL);
                expect(IDENT);
                syntaxTreeAdd(LEAF,stID,prevValue());
                expect(BECOMES);
                syntaxTreeAdd(LEAF,stOP,prevValue());
                expect(NUMBER);
                syntaxTreeAdd(LEAF,stNUM,prevValue());
                syntaxTreeBack();
            } while (accept(COMMA));
            expect(SEMICLN);
        }
        block(ENDCODE);
    }
    return syntax_tree;
}


