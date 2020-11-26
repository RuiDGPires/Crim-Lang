#ifndef __DEFS__
#define __DEFS__
#include <stdint.h>

typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;

#define FLAG_E (i8) 0x10
#define FLAG_O (i8) 0x08
#define FLAG_C (i8) 0x04
#define FLAG_Z (i8) 0x02
#define FLAG_N (i8) 0x01

typedef enum vm_operation_code{vNOP, vEQU, vWORD, vTAB, vGETN, vSETN, vBR, vJMP, vJAL, vRET, vADD, vSUB, vMUL, vDIV, vMVI, vMOV, vPUSH, vPOP, vLOAD, vSTR, vPRINT, vPRINTN, vAND, vOR, vXOR, vNOT, vEXIT} VM_op_code;


#endif