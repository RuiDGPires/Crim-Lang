#ifndef __VIRTUALMACHINE__
#define __VIRTUALMACHINE__


typedef enum vm_operation_code{vSTR, vADD, vSUB, vPRNT, vPUSH, vPOP, vBR, vBRE, vBRG, vBRGE, vJMP, vINC, vEXIT} VM_op_code;
typedef struct vm *VM_t;

#endif
