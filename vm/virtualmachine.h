#ifndef __VIRTUALMACHINE__
#define __VIRTUALMACHINE__


typedef enum vm_operation_code{vADD, vSUB, vMUL, vDIV, vMVI, vMOV, vEXIT} VM_op_code;
typedef struct vm *VM_t;

#endif
