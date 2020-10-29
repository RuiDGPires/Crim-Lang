#ifndef __VIRTUALMACHINE__
#define __VIRTUALMACHINE__


typedef enum vm_operation_code{vWORD, vTAB, vGETN, vSETN, vBR, vJMP, vJAL, vRET, vADD, vSUB, vMUL, vDIV, vMVI, vMOV, vPUSH, vPOP, vLOAD, vSTR, vPRINT, vPRINTN, vAND, vOR, vXOR, vNOT, vEXIT} VM_op_code;

typedef struct vm *VM_t;

VM_t vmCreate();

void vmFree(VM_t vm);

void vmAddOp(VM_t vm, VM_op_code op, char *arg1, char *arg2);

void vmRun(VM_t vm);

void vmPrint(VM_t vm);

#endif
