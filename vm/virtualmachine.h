#ifndef __VIRTUALMACHINE__
#define __VIRTUALMACHINE__


typedef enum vm_operation_code{vNAME, vTAB, vGETN, vSETN, vBR, vJMP, vJAL, vRET, vADD, vSUB, vMUL, vDIV, vMVI, vMOV, vPUSH, vPOP, vLOAD, vSTR, vPRINT, vPRINTN, vAND, vOR, vXOR, vNOT, vEXIT} VM_op_code;

typedef struct vm *VM_t;

#endif
