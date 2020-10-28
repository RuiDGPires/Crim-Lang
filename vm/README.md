
# CRIM-VIRTUAL MACHINE BY RUI PIRES 


### CRIM-VM instructions

_All names start with a lowercase 'v' meaning VIRTUAL_

### VM Registers

| Registers   | Use    |
|:-----------:|:------:|
| R1          | Normal use
| R2          | Normal use
| R3          | Normal use
| R4          | Normal use
| R5          | Program Counter storing

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
| | |
| vADD          |                   | Adds the last two values from the stack (pop) and pushes the result. Updates flags         |
| vSUB          |                   | Same as vADD but substracts the first popped value from the last                           |
| vMUL          |                   | Same as vADD but multiplies                                                                |
| vDIV          |                   | Same as vSUB but divides                                                                   |
| | |
| vPUSH         | register          | Push the value in _register_ to the stack                                                  |
| vPOP          | register          | Pop from the stack to _register_                                                           |
| | |
| vMVI          | reg               | Pushes and stores value in _reg_                                                           |
| vMOV          | reg1, reg2        | Sets _reg1_ to the value of _reg2_                                                         |
| | |
| vLOAD         | reg1, reg2        | Set _reg1_ to the value stored in adress _reg2_                                            |
| vSTR          | reg1, reg2        | Stores the value of _reg2_ to adress _reg1_ in memory                                      |
| | |
| vPRINT        | register          | Prints the value in adress _register_                                                      |
| vPRINTN       | reg1, reg2        | Prints _reg2_ charaters in memory starting from adress _reg1_                              |
| | |
| vAND          |                   | Same as vADD but performs logical and                                                      |
| vOR           |                   | Same as vAND but performs logical or                                                       |
| vXOR          |                   | Same as vAND but performs logical xor                                                      |
| vNOT          |                   | Pops the stack and pushes logical not'ed value                                             |
| | |
| vRSHIFT       |                   | Pops the stack and pushes right-shifted value                                              |
| vLSHIFT       |                   | Same as vRSHIFT but left-shift                                                             |