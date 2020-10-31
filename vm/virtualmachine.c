#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "virtualmachine.h"
#include "hashtable/hashtable.h"
#include "env.h"


#define STACK_SIZE 100
#define MEM_SIZE 500
#define TABLE_SIZE 200

#define FLAG_E (i8) 0x10
#define FLAG_O (i8) 0x08
#define FLAG_C (i8) 0x04
#define FLAG_Z (i8) 0x02
#define FLAG_N (i8) 0x01


typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;


typedef enum registers{vR1, vR2, vR3, vR4, vR5, vPC, vRE}Register;

typedef struct vm_op{
    i8 op;
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

void vmAddOp(VM_t vm, char *label, int op, char *arg1, char *arg2){
    int n;
    int length;
    vm->mem[vm->ic].op = op;

    if (label != NULL){
        length = strlen(label);
        if (label[length -1] = ':'){
            label[length -1] = '\0';
            envAdd(vm->env, label, vm->ip);
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

