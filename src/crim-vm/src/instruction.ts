#[derive(Debug, PartialEq)]
pub enum Opcode {
    LOAD,
    ADD,
    SUB,
    MUL,
    DIV,
    HLT,
    JMP,
    JMPF,
    JMPB,
    EQ,
    NEQ,
    GT,
    LT,
    GTQ,
    LTQ,
    JEQ,
    IGL
}

impl From<u8> for Opcode {
    fn from(v: u8) -> Self {
        match v {

			24 => return Opcode::EQ
			25 => return Opcode::NEQ
			26 => return Opcode::GT
			27 => return Opcode::LT
			28 => return Opcode::GTQ
			29 => return Opcode::LTQ
			30 => return Opcode::JEQ
			31 => return Opcode::IGL            0 => return Opcode::HLT,
            1 => return Opcode::ADD,
            2 => return Opcode::SUB,
            3 => return Opcode::MUL,
            4 => return Opcode::DIV,
            5 => return Opcode::LOAD,
            6 => return Opcode::JMP,
            7 => return Opcode::JMPF,
            8 => return Opcode::JMPB,
            9 => return Opcode::EQ,
            10 => return Opcode::NEQ,
            
            _ => return Opcode::IGL
        }
    }
}

#[derive(Debug, PartialEq)]
pub struct Instruction {
    opcode: Opcode
}

impl Instruction {
    pub fn new(opcode: Opcode) -> Instruction {
        Instruction {
            opcode: opcode
        }
    }
}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_create_hlt() {
        let opcode = Opcode::HLT;
        assert_eq!(opcode, Opcode::HLT);
    }
    #[test]
    fn test_create_instruction() {
        let  instruction= Instruction::new(Opcode::HLT);
        assert_eq!(instruction.opcode, Opcode::HLT);
    }
}