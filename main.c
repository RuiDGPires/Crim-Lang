#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tokeniser/tokenlib.h"
#include "tokeniser/lexer.h"
#include "parser/parser.h"
#include "parser/syntaxtree.h"
#include "vm/hashtable/hashtable.h"
#include "vm/hashtable/linkedlistint.h"

#define MAXCHARS 100

FILE *file;
char nameout[MAXCHARS+1] = "a.out";
char *raw_code;

/* Reads a file and returns it's contents in a malloc'd string */
char *readFile(char *file_name){
    char *dot = strrchr(file_name, '.');
    if (dot == NULL){
        fprintf(stderr,"Error opening file:\nFile as no extension\n");
        exit(EXIT_FAILURE);
    }

    dot = &(dot[1]);

    if (strcmp(dot,"crim") != 0){
        fprintf(stderr,"Error opening file:\nFile as wrong extension\n");
        exit(EXIT_FAILURE);
    }
    
    file = fopen(file_name, "r");
    if (file == NULL){
        fprintf(stderr,"Failed to open file\n");
        exit(EXIT_FAILURE);
    }
    fseek(file,0, SEEK_END);
    long fsize = ftell(file);
    fseek(file,0, SEEK_SET);
    char *file_contents = (char *) malloc(sizeof(char)*(fsize + 1 ));
    file_contents[fsize] = '\0';
    fread(file_contents, sizeof(char), fsize, file);
    fclose(file);
    return file_contents;
}

/* Parses the main function arguments */
void parseArgs(int argc, char *argv[]){
    if ((argc > 3)){
        fprintf(stderr,"WRONG NUMBER OF ARGUMENTS\n");
        exit(EXIT_FAILURE);
    }
    
    if (argc == 3){
        if (strlen(argv[2]) >= MAXCHARS){
            printf("Warning, filename exceeds character limit\n");
        }
        strncpy(nameout,argv[2], MAXCHARS);
    }

    if (argc == 2)
        raw_code = readFile(argv[1]); 
    
    if (argc == 1){
        printf("crim v0.1 | Rui Pires\n");
        exit(EXIT_SUCCESS);
    }

}

int main(int argc,char *argv[]){    
    parseArgs(argc, argv);

    /* Create a token list from the raw code */
    Link token_list = tokenParse(raw_code);
    free(raw_code);
    /* Create a syntax tree with the token list */
    stLink syntax_tree = program(token_list);
    tokenListFree(token_list);
    sTreePrint(syntax_tree);
    sTreeFree(syntax_tree);

}