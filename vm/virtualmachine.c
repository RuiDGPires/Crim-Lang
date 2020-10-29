#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "virtualmachine.h"
#include "hashtable/hashtable.h"
#include "env.h"


#define STACK_SIZE 100
#define MEM_SIZE 500
#define TABLE_SIZE 200
#define pc 5
#define R5 4

typedef struct vm_op{
    VM_op_code op;
    char *arg1;
    char *arg2;
}VM_op_t;


const VM_op_t PROGRAM_END = {vEXIT, NULL,NULL};

struct vm{
    int sp; // Stack pointer
    int *stack; // Stack memory
    Env env;  // Environment
    int *table; // Memory table
    int tp; // Table pointer
    VM_op_t *mem; // Instruction memory
    int ic; // Instruction counter
    int running;
    int regs[pc+1];
};

int isStringNumber(char *string){
    int len = strlen(string);
    for (int i = 0; i < len; i++){
        if ((string[i] < '0') || (string[i] > '9'))
            return 0;
    }
    return 1;
}

VM_t vmCreate(){
    VM_t vm = (VM_t) malloc(sizeof(struct vm));
    vm->sp = 0;
    vm->ic = 0;
    vm->tp = 0;
    for (int i = 0; i < pc + 1; i++)
        vm->regs[i] = 0;
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
    if (arg1 != NULL)
        vm->mem[vm->ic].arg1 = strdup(arg1);
    else 
        vm->mem[vm->ic].arg1 = NULL;
    if (arg2 != NULL)
        vm->mem[vm->ic].arg2 = strdup(arg2);
    else 
        vm->mem[vm->ic].arg2     = NULL;
    vm->ic++;
}

VM_op_t vmGetOp(VM_t vm){
    if (vm->regs[pc] == vm->ic ){
        vm->running = 0;
        return PROGRAM_END;
    }
    return vm->mem[vm->regs[pc]++];
}

void vmStackPush(VM_t vm, int val){
    vm->stack[vm->sp++] = val;
}

int vmStackPop(VM_t vm){
    return vm->stack[--vm->sp];
}

int vmRegTrans(char *string){
    if (strlen(string) != 2){
        fprintf(stderr, "INVALID REGISTER\n");
        exit(EXIT_FAILURE);
    }
    if ((string[0] == 'R') && (string[1] >= '1' && string[1] <= '5')){
        return (int) string[1] - (int)'1';
    }else if (strcmp(string, "PC") == 0){
        return pc;
    }else {
        fprintf(stderr, "INVALID REGISTER\n");
        exit(EXIT_FAILURE);
    }
}

void vmRun(VM_t vm){
    int n;
    VM_op_t current_op;
    vm->running = 1;
    while (vm->running){
        current_op = vmGetOp(vm);
        switch (current_op.op){
            case vNAME:
                vm->table[vm->tp] = vmStackPop(vm);
                envAdd(vm->env,current_op.arg1, vm->tp++);
                break;
            case vSETN:
                envGet(&n, vm->env,current_op.arg1);
                vm->table[n] = vmStackPop(vm);
                break;
            case vGETN:
                envGet(&n, vm->env, current_op.arg1);
                vmStackPush(vm, vm->table[n]);
                break;
            case vBR: // Missing conditional jumps
                envGet(&n, vm->env, current_op.arg1); // Get named instruction adress from memory
                vm->regs[pc] = n;
                break;
            case vJAL:
                vm->regs[R5] = vm->regs[pc];
            case vJMP: // Missing conditional jumps
                envGet(&n, vm->env, current_op.arg1); // Get named instruction adress from memory
                vm->regs[pc] = n;
                vm->env = envCreate(vm->env);
                break;
            case vRET:
                vm->env = envGetParent(vm->env);
                vm->regs[pc] = vm->regs[R5];
                break;
            case vPUSH:
                vmStackPush(vm,vm->regs[vmRegTrans(current_op.arg1)]);
                break;
            case vPOP:
                vm->regs[vmRegTrans(current_op.arg1)] = vmStackPop(vm);
                break;
            case vADD:
                vmStackPush(vm, vmStackPop(vm) + vmStackPop(vm));
                break;
            case vMVI:
                vm->regs[vmRegTrans(current_op.arg1)] = atoi(current_op.arg2);
                break;
            case vMOV:
                vm->regs[vmRegTrans(current_op.arg1)] = vm->regs[vmRegTrans(current_op.arg2)];
                break;
            case vLOAD:
                vm->regs[vmRegTrans(current_op.arg1)] = vm->table[vm->regs[vmRegTrans(current_op.arg2)]];
                break;
            case vSTR:
                vm->table[vm->regs[vmRegTrans(current_op.arg1)]] = vm->regs[vmRegTrans(current_op.arg2)];
                break;
            case vPRINT:
                printf("%x\n",vm->regs[vmRegTrans(current_op.arg1)]);
                break;
            case vEXIT:
                break;
            default:
                fprintf(stderr,"UNKOWN OPERATION %d\n", current_op.op);
                exit(EXIT_FAILURE);
                break;
        }
    }
}

void vmPrint(VM_t vm){
    printf("######################\n# INSTRUCTION MEMORY #\n######################\n");
    for (int i = 0; i < vm->ic; i++){
        printf("== %03d == | %d ", i, vm->mem[i].op);
        if (vm->mem[i].arg1  != NULL)
            printf("%s ", vm->mem[i].arg1);
        if (vm->mem[i].arg2 != NULL)
            printf("%s", vm->mem[i].arg2);
        printf("\n");
    }

    printf("\n######################\n#     REGISTERS      #\n######################\n");
    for (int i = 0; i < pc; i++){
        printf("== R%d == | %d\n", i+1, vm->regs[i]);
    }
    printf("== PC == | %d\n", vm->regs[pc]);

    printf("\n######################\n#    TABLE MEMORY    #\n######################\n");
    for (int i = 0; i < vm->tp; i++){
        printf("== %03d == | %d\n", i, vm->table[i]);
    }

    printf("\n######################\n#       STACK        #\n######################\n");
    for (int i = vm->sp - 1; i >= 0 ; i--){
        printf("[ %03d ]\n", vm->stack[i]);
    }
    
    printf("\n######################\n#    ENVIRONMENT     #\n######################\n");
    envPrint(vm->env);

}