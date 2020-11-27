#ifndef __VIRTUALMACHINE__
#define __VIRTUALMACHINE__



typedef struct vm *VM_t;


typedef enum vm_operation_code{
    vBR = 0, /* branch */
    vADD,    /* add  */
    vLOAD,   /* load */
    vSTR,    /* store */
    vJAL,    /* jump register */
    vAND,    /* bitwise and */
    vLDR,    /* load register */
    vSTR,    /* store register */
    vRTI,    /* unused */
    vNOT,    /* bitwise not */
    vLDI,    /* load indirect */
    vSTI,    /* store indirect */
    vJMP,    /* jump */
    vRES,    /* reserved (unused) */
    vLEA,    /* load effective address */
    vTRAP    /* execute trap */
} VM_opcode_t;


#endif
