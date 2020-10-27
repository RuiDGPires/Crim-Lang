
# CRIM-VIRTUAL MACHINE BY RUI PIRES 


### CRIM-VM instructions

_All names start with a lowercase 'v' meaning VIRTUAL_

### VM Registers

| Registers   |
|:-----------:|
| vR1 |
| vR2 |
| vR3 |
| vR4 |


### VM instructions

| Instructions  | Arguments         | Behaviour                                                                  | 
| :-----------: |:-----------------:| :-------------------------------------------------------------------------:|
|
| vADD          |                   | Adds the last two values from the stack (pop) and pushes the result        |
| vSUB          |                   | Same as vADD but substracts the first popped value from the last           |
| vMUL          |                   | Same as vADD but multiplies                                                |
| vDIV          |                   | Same as vSUB but divides                                                   |
| 
| vPUSH         | register          | Push the value in _register_ to the stack                                  |
| vPOP          | register          | Pop from the stack to _register_                                           |
| 
| vMVI          | reg, val          | Sets _reg_ to _val_                                                        |
| vMOV          | reg1, reg2        | Sets _reg1_ to the value of _reg2_                                         |
|
| vLOAD         | reg1, reg2        | Set _reg1_ to the value stored in adress _reg2_                            |
| vSTR          | reg1, reg2        | Stores the value of _reg2_ to adress _reg1_ in memory                      |
|
| vPRINT        | register          | Prints the value in adress _register_                                      |
| vPRINTN       | reg1, reg2        | Prints _reg2_ charaters in memory starting from adress _reg1_              |