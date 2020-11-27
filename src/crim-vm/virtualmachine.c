#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "virtualmachine.h"
#include "hashtable/hashtable.h"
#include "env.h"
#include "defs.h"

#define STACK_SIZE 100
#define MEM_SIZE 100
#define TABLE_SIZE 200
#define MAX_LINE_SIZE 120
#define MAX_WORD_SIZE 50

i16 PC_START = 0x3000;

typedef enum registers{vR0 = 0, vR1, vR2, vR3, vR4, vR5, R6, R7, vPC, vRE, REGISTER_COUNT}Reg_t;
typedef enum flags{ vPOS = 1 << 0, vZERO = 1 << 1, vNEG = 1 << 2}Flag_t;

struct vm{
    i16 running;
    i16 mem[MEM_SIZE];       // Instruction memory
    i16 reg[REGISTER_COUNT]; // Register
};

VM_t vmCreate(){
    VM_t vm = (VM_t) malloc(sizeof(struct vm));
    vm->reg[vPC] = 0;
    vm->running = 0;
    return vm;
}

void vmFree(VM_t vm){
    free(vm);
}

void vmSetPc(VM_t vm, i16 pc){
    vm->reg[vPC] = pc;
}

i16 vmIncPc(VM_t vm){
    return vm->reg[vPC]++;
}

i16 vmMemRead(VM_t vm, i16 i){
    return vm->mem[i];
}

void vmStart(VM_t vm){
    vm->running = 1;
    i16 inst = vmMemRead(vm, vmIncPc(vm));
}

int main(int argc, char* argv[]){
    VM_t vm = vmCreate();
    vmSetPc(vm, PC_START);
    vmStart(vm);
}