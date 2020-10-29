
# CRIM-VIRTUAL MACHINE BY RUI PIRES 

### VM Registers

| Registers   | Use    |
|:-----------:|:------:|
| R1          | Normal use |
| R2          | Normal use |
| R3          | Normal use |
| R4          | Normal use |
| R5          | Program Counter storing |
| PC (R6)     | Program Counter         |

_All names start with a lowercase 'v' meaning VIRTUAL_

### Conditions
| Conditions   | Meaning      |
|:------------:|:------------:|
| N            | Negative     |
| ZERO         | Zero         |
| NZ           | Not Zero     |
| NN           | Not Negative |
| P            | Positive     |
| NP           | Not Positive |
| T            | True         |
| F            | False        |

_Everytime a condition is used, the compared value is popped_

### VM instructions

| Instructions  | Arguments         | Behaviour                                                                                  | 
| :-----------: |:-----------------:| :-----------------------------------------------------------------------------------------:|
| | |
| vNAME         | name              | Initializes a named value in the memory of the current environment                         |
| vTAB          | n                 | Reserves _n_ spaces in memory and pushes the adress of the first                           |
| vGETN         | name              | Pushes the value stored in the env. named _name_. This value will be a pointer to memory   |
| vSETN         | name              | Sets the named value in env to popped value                                                |
| | |
| vBR           | name, cond        | Brances to _name_                                                                          |
| vJMP          | name, cond        | Jumps tp _name_, creates a new environment                                                 |
| vJAL          | name, cond        | Same as jump but saves current PC                                                          |
| vRET          |                   | Returns to previous env and previous PC                                                    |
| | |
| vADD          | reg1, reg2        | Adds the values from both registers and stores the result in the first                     |
| vSUB          | reg1, reg2        | Same as vADD but substracts _reg2_ from _reg1_                                             |
| vMUL          | reg1, reg2        | Same as vADD but multiplies                                                                |
| vDIV          | reg1, reg2        | Same as vSUB but divides                                                                   |
| | |
| vPUSH         | register          | Push the value in _register_ to the stack                                                  |
| vPOP          | register          | Pop from the stack to _register_                                                           |
| | |
| vMVI          | reg ,val          | Stores _val_ in _reg_                                                           |
| vMOV          | reg1, reg2        | Sets _reg1_ to the value of _reg2_                                                         |
| | |
| vLOAD         | reg1, reg2        | Set _reg1_ to the value stored in adress _reg2_                                            |
| vSTR          | reg1, reg2        | Stores the value of _reg2_ to adress _reg1_ in memory                                      |
| | |
| vPRINT        | register          | Prints the value in adress _register_                                                      |
| vPRINTN       | reg1, reg2        | Prints _reg2_ charaters in memory starting from adress _reg1_                              |
| | |
| vAND          | reg1, reg2        | Same as vADD but performs logical and                                                      |
| vOR           | reg1, reg2        | Same as vAND but performs logical or                                                       |
| vXOR          | reg1, reg2        | Same as vAND but performs logical xor                                                      |
| vNOT          | reg1              |                                                                                            |
| | |
| vRSHIFT       | register          | right shifts the value in _register_                                                       |
| vLSHIFT       | register          | Same as vRSHIFT but left-shift                                                             |