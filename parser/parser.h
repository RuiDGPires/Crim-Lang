#ifndef __PARSER__
#define __PARSER__

#include "syntaxtree.h"
#include "../tokeniser/tokenlib.h"

/* Gets the next symbol from the token list */
void nextSym();

void error(const char msg[]);

void parserSetList(Link new_token_list);

int accept(Symbol s);

int expect(Symbol s);

void arguments();

void varOrFunc();

void factor();

void term();

void expression();

void block(Symbol endsym);

void statement();

stLink program(Link new_token_list);

#endif