use crate::instruction::Opcode;

#[derive(Debug)]
pub struct VM{
    pub registers: [i32; 32],
    pc: usize,
    pub program: Vec<u8>,
    remainder: u32,
    zero_flag: bool,
    negative_flag: bool,
}

impl VM {
    pub fn new() -> VM{
        VM {
            registers: [0; 32],
            program: vec![],
            pc: 0,
            remainder: 0,
            zero_flag: false,
            negative_flag: false,
        }
    }

    pub fn run(&mut self){
        let mut is_done = false;
        while !is_done {
            is_done = self.execute_intruction();
        }
    }

    pub fn run_once(&mut self) {
        self.execute_intruction();
    }

    fn execute_intruction(&mut self) -> bool {
        if self.pc >= self.program.len() {
            return true;
        }
        match self.decode_opcode() {
            Opcode::HLT => {
                println!("HLT");
                return true;
            },
            Opcode::LOAD => {
                let register = self.next_8_bits() as usize;
                let value = self.next_16_bits() as usize;
                self.registers[register] = value as i32;
            }
            Opcode::ADD => {
                let register1 = self.next_8_bits() as usize;
                let register2 = self.registers[self.next_8_bits() as usize];
                let register3 = self.registers[self.next_8_bits() as usize];
                self.registers[register1] = register2 + register3;
            },
            Opcode::SUB => {
                let register1 = self.next_8_bits() as usize;
                let register2 = self.registers[self.next_8_bits() as usize];
                let register3 = self.registers[self.next_8_bits() as usize];
                self.registers[register1] = register2 - register3;
            },
            Opcode::MUL => {
                let register1 = self.next_8_bits() as usize;
                let register2 = self.registers[self.next_8_bits() as usize];
                let register3 = self.registers[self.next_8_bits() as usize];
                self.registers[register1] = register2 * register3;
            },
            Opcode::DIV => {
                let register1 = self.next_8_bits() as usize;
                let register2 = self.registers[self.next_8_bits() as usize];
                let register3 = self.registers[self.next_8_bits() as usize];
                self.registers[register1] = register2 / register3;
                self.remainder = (register2 % register3) as u32;
            },
            Opcode::JMP => {
                let target = self.registers[self.next_8_bits() as usize];
                self.pc = target as usize;
            },
            Opcode::JMPF => {
                let value = self.registers[self.next_8_bits() as usize];
                self.pc += value as usize;
            },
            Opcode::JMPB => {
                let value = self.registers[self.next_8_bits() as usize];
                self.pc -= value as usize;
            },
            Opcode::CMP => {
                /* CMP V1 V2 */
                let v1 = self.registers[self.next_8_bits() as usize];
                let v2 = self.registers[self.next_8_bits() as usize];
                self.zero_flag = v1 == v2;
                self.negative_flag = v2 > v1;
                self.next_8_bits();
            },
            Opcode::JEQ => {
                let value = self.registers[self.next_8_bits() as usize];
                if self.zero_flag {
                    self.pc = value as usize;
                }
            },
            Opcode::JNEQ => {
                let value = self.registers[self.next_8_bits() as usize];
                if !self.zero_flag {
                    self.pc = value as usize;
                }
            },
            _ => {
                println!("Unkown opcode");
               return true;
            }
        }
        false
    }
    
    fn decode_opcode(&mut self) -> Opcode {
        let opcode = Opcode::from(self.program[self.pc]);
        self.pc += 1;
        return opcode;
    }

    fn next_8_bits(&mut self) -> u8 {
        let result = self.program[self.pc];
        self.pc += 1;
        return result;
    }
    
    fn next_16_bits(&mut self) -> u16 {
        let result = ((self.program[self.pc] as u16) << 8) | self.program[self.pc + 1] as u16;
        self.pc += 2;
        return result;
    }

    pub fn add_byte(&mut self, b: u8) {
        self.program.push(b);
    }

}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_create_vm() {
        let test_vm = VM::new();
        assert_eq!(test_vm.registers[0],0)
    }

    #[test]
    fn test_opcode_hlt() {
      let mut test_vm = VM::new();
      let test_bytes = vec![0,0,0,0];
      test_vm.program = test_bytes;
      test_vm.run();
      assert_eq!(test_vm.pc, 1);
    }

    #[test]
    fn test_opcode_igl() {
      let mut test_vm = VM::new();
      let test_bytes = vec![200,0,0,0];
      test_vm.program = test_bytes;
      test_vm.run();
      assert_eq!(test_vm.pc, 1);
    }

    #[test]
    fn test_jmp_opcode() {
        let mut test_vm = VM::new();
        test_vm.registers[0] = 1;
        test_vm.program = vec![6, 0, 0, 0];
        test_vm.run_once();
        assert_eq!(test_vm.pc, 1);
    }

    #[test]
    fn test_jmpf_opcode() {
        let mut test_vm = VM::new();
        test_vm.registers[0] = 2;
        test_vm.program = vec![7, 0, 0, 0, 5, 0, 0, 0];
        test_vm.run_once();
        assert_eq!(test_vm.pc, 4);
    }

    #[test]
    fn test_eq_opcode() {
        let mut test_vm = VM::new();
        test_vm.registers[0] = 10;
        test_vm.registers[1] = 10;
        test_vm.program = vec![9, 0, 1, 0, 9, 0, 1, 0];
        test_vm.run_once();
        assert_eq!(test_vm.zero_flag, true);
        test_vm.registers[1] = 20;
        test_vm.run_once();
        assert_eq!(test_vm.zero_flag, false);
    }

    #[test]
    fn test_jeq_opcode() {
        let mut test_vm = VM::new();
        test_vm.registers[0] = 7;
        test_vm.zero_flag = true;
        test_vm.program = vec![10, 0, 0, 0, 17, 0, 0, 0, 17, 0, 0, 0];
        test_vm.run_once();
        assert_eq!(test_vm.pc, 7);
    }
    #[test]
    fn test_jneq_opcode() {
        let mut test_vm = VM::new();
        test_vm.registers[0] = 7;
        test_vm.zero_flag = false;
        test_vm.program = vec![11, 0, 0, 0, 17, 0, 0, 0, 17, 0, 0, 0];
        test_vm.run_once();
        assert_eq!(test_vm.pc, 7);
    }
}