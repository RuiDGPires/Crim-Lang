#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "virtualmachine.h"
#include "hashtable/hashtable.h"
#include "env.h"


#define STACK_SIZE 100
#define MEM_SIZE 500
#define TABLE_SIZE 200

typedef struct vm_op{
    VM_op_code op;
    char *arg1;
    char *arg2;
}VM_op_t;


const VM_op_t PROGRAM_END = {vEXIT, NULL,NULL};

struct vm{
    int ip; // Instruction pointer
    int sp; // Stack pointer
    int *stack; // Stact memory
    Env env;  // Environment
    int *table; // Memory table
    VM_op_t *mem; // Instruction memory
    int ic; // Instruction counter
    int running;
    int r1, r2, r3, r4, r5;
};

int isStringNumber(char *string){
    int len = strlen(string);
    for (int i = 0; i < len; i++){
        if ((string[i] < '0') || (string[i] > '9'))
            return 0;
    }
    return 1
}

VM_t vmCreate(){
    VM_t vm = (VM_t) malloc(sizeof(struct vm));
    vm->ip = -1;
    vm->sp = 0;
    vm->ic = 0;
    vm->running = 0;
    vm->stack = (int *) malloc(sizeof(int) * STACK_SIZE);
    vm->table = (int *) malloc(sizeof(int) * TABLE_SIZE);
    vm->mem = (VM_op_t *) malloc(sizeof(VM_op_t) * MEM_SIZE);
    vm->env = envCreate(NULL);
}

void vmFree(VM_t vm){
    envFree(vm->env);
    free(vm->stack);
    for (int i = 0; i < vm->ic ;i++){
        free(vm->mem[i].arg1);
        free(vm->mem[i].arg2);
    }
    free(vm->mem);
    free(vm->table);
    free(vm);
}

void vmAddOp(VM_t vm, VM_op_code op, char *arg1, char *arg2){
    if (vm->ic == MEM_SIZE){
        fprintf(stderr,"vmAddOp: instruction count exceeds memory size");
        exit(EXIT_FAILURE);
    }
    vm->mem[vm->ic].op = op;
    vm->mem[vm->ic].arg1 = strdup(arg1);
    vm->mem[vm->ic].arg1 = strdup(arg2);
    vm->ic++;
}

VM_op_t vmGetOp(VM_t vm){
    vm->ip++;
    if (vm->ip == vm->ic)
        vm->running = 0;
        return PROGRAM_END;
    return vm->mem[vm->ip];
}

void vmStackPush(VM_t vm, int val){
    vm->stack[vm->sp++] = val;
}

int vmStackPop(VM_t vm){
    return vm->stack[vm->sp--];
}

void vmRun(VM_t vm){
    VM_op_t current_op;
    vm->running = 1;
    while (vm->running){
        current_op = vmGetOp(vm);
        switch (current_op.op){
            default:
                fprintf(stderr,"UNKOWN OPERATION");
                exit(EXIT_FAILURE);
                break;
            case vADD:
                
                break;
            case vSUB:
                vm->r1 = vmStackPop(vm);
                vm->r2 = vmStackPop(vm);
                vmStackPush(vm->r2 - vm->r1);
                break;
            case vSTR:
                if (!(isStringNumber(current_op.arg1)))
                    fprintf(stderr,"STORE: ")
            
        }
    }
}