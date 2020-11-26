#ifndef __VIRTUALMACHINE__
#define __VIRTUALMACHINE__



typedef struct vm *VM_t;

VM_t vmCreate();

void vmFree(VM_t vm);

void vmAddOp(VM_t vm, char *label, VM_op_code op, char *arg1, char *arg2);

void vmRun(VM_t vm);

void vmPrintMem(VM_t vm);

void vmLoadCommands(VM_t vm, char *string);

#endif
