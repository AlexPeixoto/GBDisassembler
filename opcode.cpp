#include "opcode.h"

Opcode::Opcode(){
    operationListTop = 
    {
        {0x00, INSTRUCTION::NOP}, 
        {0x01, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::D16, static_cast<int>(REG::BC)}, 
        {0x02, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::REG, static_cast<int>(REG::BC), static_cast<int>(REG::A)}, 
        {0x03, INSTRUCTION::INC, PARAMETER_TYPE::REG, PARAMETER_TYPE::NONE, static_cast<int>(REG::BC)}, 
        {0x04, INSTRUCTION::INC, PARAMETER_TYPE::REG, PARAMETER_TYPE::NONE, static_cast<int>(REG::B)}, 
        {0x05, INSTRUCTION::DEC, PARAMETER_TYPE::REG, PARAMETER_TYPE::NONE, static_cast<int>(REG::B)}, 
        {0x06, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::D8, static_cast<int>(REG::B)}, 
        {0x07, INSTRUCTION::RLCA}, 
        {0x08, INSTRUCTION::LD, PARAMETER_TYPE::A16, PARAMETER_TYPE::REG, 0, static_cast<int>(REG::SP)}, 
        {0x09, INSTRUCTION::ADD, PARAMETER_TYPE::REG, PARAMETER_TYPE::REG, static_cast<int>(REG::HL), static_cast<int>(REG::BC)}, 
        {0x0A, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::REG, static_cast<int>(REG::A), static_cast<int>(REG::BC)}, 
        {0x0B, INSTRUCTION::DEC, PARAMETER_TYPE::REG, PARAMETER_TYPE::NONE, static_cast<int>(REG::BC)}, 
        {0x0C, INSTRUCTION::INC, PARAMETER_TYPE::REG, PARAMETER_TYPE::NONE, static_cast<int>(REG::C)}, 
        {0x0D, INSTRUCTION::DEC, PARAMETER_TYPE::REG, PARAMETER_TYPE::NONE, static_cast<int>(REG::C)}, 
        {0x0E, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::D8, static_cast<int>(REG::C)}, 
        {0x0F, INSTRUCTION::RRCA},  


        {0x10, INSTRUCTION::STOP}, 
        {0x11, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::D16, static_cast<int>(REG::DE)}, 
        {0x12, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::REG, static_cast<int>(REG::DE), static_cast<int>(REG::A)}, 
        {0x13, INSTRUCTION::INC, PARAMETER_TYPE::REG, PARAMETER_TYPE::NONE, static_cast<int>(REG::DE)}, 
        {0x14, INSTRUCTION::INC, PARAMETER_TYPE::REG, PARAMETER_TYPE::NONE, static_cast<int>(REG::D)}, 
        {0x15, INSTRUCTION::DEC, PARAMETER_TYPE::REG, PARAMETER_TYPE::NONE, static_cast<int>(REG::D)}, 
        {0x16, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::D8, static_cast<int>(REG::D)}, 
        {0x17, INSTRUCTION::RLA}, 
        {0x18, INSTRUCTION::JR, PARAMETER_TYPE::R8}, 
        {0x19, INSTRUCTION::ADD, PARAMETER_TYPE::REG, PARAMETER_TYPE::REG, static_cast<int>(REG::HL), static_cast<int>(REG::DE)}, 
        {0x1A, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::REG, static_cast<int>(REG::A), static_cast<int>(REG::DE)}, 
        {0x1B, INSTRUCTION::DEC, PARAMETER_TYPE::REG, PARAMETER_TYPE::NONE, static_cast<int>(REG::DE)}, 
        {0x1C, INSTRUCTION::INC, PARAMETER_TYPE::REG, PARAMETER_TYPE::NONE, static_cast<int>(REG::E)}, 
        {0x1D, INSTRUCTION::DEC, PARAMETER_TYPE::REG, PARAMETER_TYPE::NONE, static_cast<int>(REG::E)}, 
        {0x1E, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::D8, static_cast<int>(REG::E)}, 
        {0x1F, INSTRUCTION::RRA},  

        {0x20, INSTRUCTION::JR, PARAMETER_TYPE::JMP, PARAMETER_TYPE::R8, static_cast<int>(JMP::NZ)}, 
        {0x21, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::D16, static_cast<int>(REG::HL)}, 
        {0x22, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::REG, static_cast<int>(REG::HLP), static_cast<int>(REG::A)}, 
        {0x23, INSTRUCTION::INC, PARAMETER_TYPE::REG, PARAMETER_TYPE::NONE, static_cast<int>(REG::HL)}, 
        {0x24, INSTRUCTION::INC, PARAMETER_TYPE::REG, PARAMETER_TYPE::NONE, static_cast<int>(REG::H)}, 
        {0x25, INSTRUCTION::DEC, PARAMETER_TYPE::REG, PARAMETER_TYPE::NONE, static_cast<int>(REG::H)}, 
        {0x26, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::D8, static_cast<int>(REG::H)}, 
        {0x27, INSTRUCTION::DAA}, 
        {0x28, INSTRUCTION::JR, PARAMETER_TYPE::JMP, PARAMETER_TYPE::R8, static_cast<int>(JMP::Z)}, 
        {0x29, INSTRUCTION::ADD, PARAMETER_TYPE::REG, PARAMETER_TYPE::REG, static_cast<int>(REG::HL), static_cast<int>(REG::HL)}, 
        {0x2A, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::REG, static_cast<int>(REG::A), static_cast<int>(REG::HLP)}, 
        {0x2B, INSTRUCTION::DEC, PARAMETER_TYPE::REG, PARAMETER_TYPE::NONE, static_cast<int>(REG::HL)}, 
        {0x2C, INSTRUCTION::INC, PARAMETER_TYPE::REG, PARAMETER_TYPE::NONE, static_cast<int>(REG::L)}, 
        {0x2D, INSTRUCTION::DEC, PARAMETER_TYPE::REG, PARAMETER_TYPE::NONE, static_cast<int>(REG::L)}, 
        {0x2E, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::D8, static_cast<int>(REG::L)}, 
        {0x2F, INSTRUCTION::CPL},  

        {0x30, INSTRUCTION::JR, PARAMETER_TYPE::JMP, PARAMETER_TYPE::R8, static_cast<int>(JMP::NC)}, 
        {0x31, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::D16, static_cast<int>(REG::SP)}, 
        {0x32, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::REG, static_cast<int>(REG::HLM), static_cast<int>(REG::A)}, 
        {0x33, INSTRUCTION::INC, PARAMETER_TYPE::REG, PARAMETER_TYPE::NONE, static_cast<int>(REG::SP)}, 
        {0x34, INSTRUCTION::INC, PARAMETER_TYPE::REG, PARAMETER_TYPE::NONE, static_cast<int>(REG::HL)}, 
        {0x35, INSTRUCTION::DEC, PARAMETER_TYPE::REG, PARAMETER_TYPE::NONE, static_cast<int>(REG::HL)}, 
        {0x36, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::D8, static_cast<int>(REG::HL)}, 
        {0x37, INSTRUCTION::SCF}, 
        {0x38, INSTRUCTION::JR, PARAMETER_TYPE::JMP, PARAMETER_TYPE::R8, static_cast<int>(JMP::C)}, 
        {0x39, INSTRUCTION::ADD, PARAMETER_TYPE::REG, PARAMETER_TYPE::REG, static_cast<int>(REG::HL), static_cast<int>(REG::SP)}, 
        {0x3A, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::REG, static_cast<int>(REG::A), static_cast<int>(REG::HLM)}, 
        {0x3B, INSTRUCTION::DEC, PARAMETER_TYPE::REG, PARAMETER_TYPE::NONE, static_cast<int>(REG::SP)}, 
        {0x3C, INSTRUCTION::INC, PARAMETER_TYPE::REG, PARAMETER_TYPE::NONE, static_cast<int>(REG::A)}, 
        {0x3D, INSTRUCTION::DEC, PARAMETER_TYPE::REG, PARAMETER_TYPE::NONE, static_cast<int>(REG::A)}, 
        {0x3E, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::D8, static_cast<int>(REG::A)}, 
        {0x3F, INSTRUCTION::CCF}
    };
}

//Uses https://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html as a basis
unsigned char* Opcode::generateInstruction(unsigned char* PC){
    unsigned char op = *PC;

    //Those are simple instructions that I only print and return incrementing (those do not affect any register or need parameter)
    switch(op){
        case 0x00:
            //NOP
            return PC++;
        case 0xCB:
            PC++;
            getCBInstruction(PC);
            return PC++;
        case 0x10:
            //STOP 0
            return PC++;
        case 0x76:
            //HALT
            return PC++;
        case 0xF3:
            //DI
            return PC++;
    }
    
    //LD
    if(op >= 0x40 && op <= 0x7F){
        std::string op1, op2;
        
        //On the opcode table there is a pattern where the 8 registers repeat [B,C,D,E,H,L,HL]
        //Instead of checking all the possible operations I can map the range per instructions on specific cases and then "calculate" the registers based on the lower 4 bits
        int op2Val = getRegisterFromLast4Bits<int>(op);
        op2 = regToString(op2Val);
        
        //A similar rule applies for the first 4 bits, but I have to divide it by 8 assuming that it starts from 0x00
        int normalizedOp = op - 0x40; 
        //I know that after every 8 elements I move to the next register (normalized B starts at 0x00, c at 0x08, d at 0x10)
        int op1Val = normalizedOp/8;
        op2 = regToString(op2Val);
        //LD op1, op2
        return PC++;
    }
    else if(op >= 0x80 && op <= 0xBF){
        //Tries to map ADD, ADC, SUB, SBC, AND, XOR, OR, CP as a "sequential" range of instructions between 0x80 and 0xBF
        int normalizedOp = (op - 0x80)/8;
        switch(op){
            case 0:
                //ADD
                break;
            case 1:
                //ADC
                break;
            case 2:
                //SUB
                break;
            case 3:
                //SBC
                break;
            case 4:
                //AND
                break;
            case 5:
                //XOR
                break;
            case 6:
                //OR
                break;
            case 7:
                //CP
                break;
            default:
                throw std::runtime_error("INCORRECT OPCODE SUPPLIED");
        }
        return PC++;
    }
    //Others
    else{
        //Use OperationList
    }
    
}

void Opcode::getCBInstruction(unsigned char *PC){}