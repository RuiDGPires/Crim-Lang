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
#define pc 5
#define R5 4

typedef 

typedef struct vm_op{
    VM_op_code op;
    char *arg1;
    char *arg2;
}VM_op_t;


struct vm{

}