#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "virtualmachine.h"
#include "hashtable/hashtable.h"
#include "env.h"


#define STACK_SIZE 100
#define MEM_SIZE 500
#define TABLE_SIZE 200

#define STACK            0xC0000000
#define INSTRUCTION_BYTE 0x3F000000
#define ARG1_BYTE        0x00FFF000
#define ARG2_BYTE        0x00000FFF
typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;




struct vm{
    int pc; // Program Counter
    int sp; // Stack Pointer
    i64 mem[MEM_SIZE]; // Instruction memory
    int ip;            // Instruction pointer
    i64 stack[STACK_SIZE]; // stack memory
    int sp;                // Stack pointer


};