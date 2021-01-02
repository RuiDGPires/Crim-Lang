<Program> ::= <Instructions>

<Instructions> ::= <Instruction> | <Instruction> "\n" <Instructions>

<Instruction> ::= <Opcode> " " <Register> " " <IntegerOp>

<Opcode> ::= <Letter> | <Letter> <Opcode>

<Letter> ::= "a" | ... | "z" | "A" | ... "Z"

<Register> ::= "R" | <Number>

<Number> ::= <Digit> | <Digit> <Number>

<Digit> ::= "0" | ... | "9"

<IntegerOp> ::= "#" | <Number>





