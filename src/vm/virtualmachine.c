#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "virtualmachine.h"
#include "hashtable/hashtable.h"
#include "env.h"
#include "defs.h"

#define STACK_SIZE 100
#define MEM_SIZE 500
#define TABLE_SIZE 200
#define MAX_LINE_SIZE 120
#define MAX_WORD_SIZE 50

typedef enum registers{vR1, vR2, vR3, vR4, vR5, vPC, vRE}Register;

typedef struct vm_op{
    VM_op_code op;
    i32 arg1;
    i32 arg2;
}VM_op_t;

struct vm{
    int pc;                // Program Counter
    VM_op_t mem[MEM_SIZE]; // Instruction memory
    int ic;                // Instruction counter
    int ip;                // Instruction pointer
    i32 stack[STACK_SIZE]; // stack memory
    int sp;                // Stack pointer
    Env env;        // Hashtable for global keywords
    i32 table[TABLE_SIZE]; // Table memory
    int tp;                // Table pointer
    i32 regs[7];           // Registers
};

void vmClearFlags(VM_t vm){
    vm->regs[6] = 0;
}

void vmSetFlag(VM_t vm, i8 flag){
    vm->regs[6] = vm->regs[6] | flag;
}

VM_t vmCreate(){
    VM_t vm = (VM_t) malloc(sizeof(struct vm));
    vm->pc = 0;
    vm->ic = 0;
    vm->ip = 0;
    vm->sp = -1;
    vm->env = envCreate(NULL);
    vm->tp = 0;
    for (int i = 0; i < 7; i++)
        vm->regs[i] = 0;
    return vm;
}

void vmFree(VM_t vm){
    envFree(vm->env);
    free(vm);
}

int vmStackPop(VM_t vm){
    return vm->stack[vm->sp--];
}

int vmStackPush(VM_t vm){
    return vm->stack[++vm->sp];
}

void vmPrintOp(VM_op_t op){
    printf("%d",(int) op.op);
    if (op.arg1 != NULL)
        printf(" %s",op.arg1);
    if (op.arg2 != NULL)
        printf(" %s",op.arg2);
    printf("\n");
}

void vmPrintMem(VM_t vm){
    int i;
    for(i = 0; i < vm->ic; i++){
        vmPrintOp(vm->mem[i]);
    }
}


int hexToDec(char c){
    if (c >= '0' && c <= '9')
        return (int)c - (int)'0';
    if (c >= 'A' && c <= 'F')
        return (int)c - (int)'A' + 10;
    if (c >= 'a' && c <= 'f')
        return (int)c - (int)'a' + 10;  
    return -1;
}

int vmIsNumber(char *string, int *n){
    int len = strlen(string);
    int i = 0;
    int ret = 0;
    if (string[0] == '-') i++; 
    if (len > 2)
        if (string[0] == '0' && string[1] == 'x'){
            int a;
            for (i = 2 ; i < len; i++){
                a = hexToDec(string[i]);
                if (a == -1)
                    return 0;
                ret += ((int) pow(16, len - i -2))*a;
            }
            if (n != NULL)
                *n = ret;
            return 1;
        }
    for (; i < len; i++){
        if (string[i] >= '0' && string[i] <= '9'){
            ret += ((int) pow(10, len - i -2))*((int)string[i]- (int)'0');
        }else{
            return 0;
        }
        
    }
    if (n != NULL)
        *n = ret;
    return 1;
}

void vmAddOp(VM_t vm, char *label, VM_op_code op, char *arg1, char *arg2){
    int n;
    int length;
    vm->mem[vm->ic].op = op;

    if (label != NULL){
        length = strlen(label);
        if (label[length -1] = ':'){
            label[length -1] = '\0';
            envAdd(vm->env, label, vm->ip);
        }else{
            //if (op == vEQU || op == vWORD)
        }
    }

    if (arg1 != NULL){
        if (vmIsNumber(arg1, &n)){
            ;
        }else{
            if (envGet(&n,vm->env, arg1) == 0){
                fprintf(stderr, "Nothing is alocated named %s\n", arg1);
            }
        }
        vm->mem[vm->ic].arg1 = n;
    }else{
        vm->mem[vm->ic].arg1 = -1;
    }

    if (arg2 != NULL){
        if (vmIsNumber(arg1, &n)){
            ;
        }else{
            if (envGet(&n,vm->env, arg2) == 0){
                fprintf(stderr, "Nothing is alocated named %s\n", arg2);
            }   
        }
        vm->mem[vm->ic].arg2 = n;
    }else{
        vm->mem[vm->ic].arg2 = -1;
    }
    vm->ic++;
}

int stringToOp(char *string, VM_op_code *n){
    if (strcmp(string, "WORD")){
        if (n != NULL) *n = vWORD;
    }else if (strcmp(string, "EQU")){
        if (n != NULL) *n = vEQU;
    }else if (strcmp(string, "TAB")){
        if (n != NULL) *n = vTAB;
    }else if (strcmp(string, "MVI")){
        if (n != NULL) *n = vMVI;
    }else if (strcmp(string, "MOV")){
        if (n != NULL) *n = vMOV;
    }else if (strcmp(string, "ADD")){
        if (n != NULL) *n = vADD;
    }else if (strcmp(string, "PRINT")){
        if (n != NULL) *n = vPRINT;
    }else{
        return 0;
    }
    return 1;
}

int opNumArgs(VM_op_code op){
    switch(op){
        case vWORD:
            return 1;
        case vEQU:
            return 1;
        case vTAB:
            return 1;
        case vMVI:
            return 2;
        case vMOV:
            return 2;
        case vADD:
            return 2;
        case vPRINT:
            return 1;
    }
    return 0;
}

void vmLoadCommands(VM_t vm, char *string){
    char buffer[4][MAX_WORD_SIZE];
    int i, j;
    char* line;
    char* token; 
    char* rest_b = strdup(string); 
    char* rest = rest_b;

    char* label = NULL;
    VM_op_code n;
    char* args[2] = {NULL, NULL};
  
    while ((line = strtok_r(rest, "\n", &rest))){
        j = 0;
        while ((token = strtok_r(line, " ", &line))){
            strcpy(buffer[j++], token);
        }
        if (stringToOp(buffer[0], &n)){
            label = NULL;
            for (i = 0; i< opNumArgs(n); i++)
                args[i] = buffer[i+1];
        }else if (stringToOp(buffer[1], &n)){
            label = NULL;
            for (i = 0; i< opNumArgs(n); i++)
                args[i] = buffer[i+2];
        }else{
            continue;
        }
        vmAddOp(vm,label,n,args[0], args[1]);
    }
    
    free(token);
    free(rest_b);
    exit (0); 
}