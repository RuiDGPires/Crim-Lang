#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tokeniser/tokenlib.h"
#include "tokeniser/lexer.h"
#include "parser/parser.h"
#include "parser/syntaxtree.h"

#include <stdint.h>

#define MAXCHARS 100
#define false 0
#define true 1

FILE *file;
char nameout[MAXCHARS+1] = "a.out";
char *raw_code = NULL;
const char USAGE[] = "crim [-option] <filename> [-option]\nOptions:\n\t-t <type>: option for debugging type: s (syntax); o (other)\n";

int test_syntax = false;


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
    int i;

    if (argc == 1){
        printf("crim v0.1 | Rui Pires\n%s", USAGE);
        exit(EXIT_SUCCESS);
    }

    for(i = 1; i < argc; i++){
        if (argv[i][0] != '-'){
            if (raw_code == NULL) raw_code = readFile(argv[i]); 
            else{
                printf("Error, wrong argument\n");
            }
        } else if (strcmp(argv[i],"-t") == 0 && (i < argc)){
            switch(argv[++i][0]){
                case 's':
                    test_syntax = true;
                    break;
                case 'o':
                default:
                    break;
            }
        }
    }
    if (raw_code == NULL){
        printf("crim v0.1 | Rui Pires\n%s", USAGE);
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

    sTreeFree(syntax_tree);
}