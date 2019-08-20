#include "decoder.h"
#include <sstream>
#include <iostream>

using namespace CPU;
using CPU::INSTRUCTION;

Decoder::Decoder(){
    operationListTop = 
    {
        {0x00, INSTRUCTION::NOP}, 
        {0x01, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::D16, static_cast<int>(REG::BC)}, 
        {0x02, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::REG, static_cast<int>(REG::BC), static_cast<int>(REG::A)}, 
        {0x03, INSTRUCTION::INC, PARAMETER_TYPE::REG, static_cast<int>(REG::BC)}, 
        {0x04, INSTRUCTION::INC, PARAMETER_TYPE::REG, static_cast<int>(REG::B)}, 
        {0x05, INSTRUCTION::DEC, PARAMETER_TYPE::REG, static_cast<int>(REG::B)}, 
        {0x06, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::D8, static_cast<int>(REG::B)}, 
        {0x07, INSTRUCTION::RLCA}, 
        {0x08, INSTRUCTION::LD, PARAMETER_TYPE::A16, PARAMETER_TYPE::REG, 0, static_cast<int>(REG::SP)}, 
        {0x09, INSTRUCTION::ADD, PARAMETER_TYPE::REG, PARAMETER_TYPE::REG, static_cast<int>(REG::HL), static_cast<int>(REG::BC)}, 
        {0x0A, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::REG, static_cast<int>(REG::A), static_cast<int>(REG::BC)}, 
        {0x0B, INSTRUCTION::DEC, PARAMETER_TYPE::REG, static_cast<int>(REG::BC)}, 
        {0x0C, INSTRUCTION::INC, PARAMETER_TYPE::REG, static_cast<int>(REG::C)}, 
        {0x0D, INSTRUCTION::DEC, PARAMETER_TYPE::REG, static_cast<int>(REG::C)}, 
        {0x0E, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::D8, static_cast<int>(REG::C)}, 
        {0x0F, INSTRUCTION::RRCA},  


        {0x10, INSTRUCTION::STOP}, 
        {0x11, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::D16, static_cast<int>(REG::DE)}, 
        {0x12, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::REG, static_cast<int>(REG::DE), static_cast<int>(REG::A)}, 
        {0x13, INSTRUCTION::INC, PARAMETER_TYPE::REG, static_cast<int>(REG::DE)}, 
        {0x14, INSTRUCTION::INC, PARAMETER_TYPE::REG, static_cast<int>(REG::D)}, 
        {0x15, INSTRUCTION::DEC, PARAMETER_TYPE::REG, static_cast<int>(REG::D)}, 
        {0x16, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::D8, static_cast<int>(REG::D)}, 
        {0x17, INSTRUCTION::RLA}, 
        {0x18, INSTRUCTION::JR, PARAMETER_TYPE::R8}, 
        {0x19, INSTRUCTION::ADD, PARAMETER_TYPE::REG, PARAMETER_TYPE::REG, static_cast<int>(REG::HL), static_cast<int>(REG::DE)}, 
        {0x1A, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::REG, static_cast<int>(REG::A), static_cast<int>(REG::DE)}, 
        {0x1B, INSTRUCTION::DEC, PARAMETER_TYPE::REG, static_cast<int>(REG::DE)}, 
        {0x1C, INSTRUCTION::INC, PARAMETER_TYPE::REG, static_cast<int>(REG::E)}, 
        {0x1D, INSTRUCTION::DEC, PARAMETER_TYPE::REG, static_cast<int>(REG::E)}, 
        {0x1E, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::D8, static_cast<int>(REG::E)}, 
        {0x1F, INSTRUCTION::RRA},  

        {0x20, INSTRUCTION::JR, PARAMETER_TYPE::JMP, PARAMETER_TYPE::R8, static_cast<int>(JMP::NZ)}, 
        {0x21, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::D16, static_cast<int>(REG::HL)}, 
        {0x22, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::REG, static_cast<int>(REG::HLP), static_cast<int>(REG::A)}, 
        {0x23, INSTRUCTION::INC, PARAMETER_TYPE::REG, static_cast<int>(REG::HL)}, 
        {0x24, INSTRUCTION::INC, PARAMETER_TYPE::REG, static_cast<int>(REG::H)}, 
        {0x25, INSTRUCTION::DEC, PARAMETER_TYPE::REG, static_cast<int>(REG::H)}, 
        {0x26, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::D8, static_cast<int>(REG::H)}, 
        {0x27, INSTRUCTION::DAA}, 
        {0x28, INSTRUCTION::JR, PARAMETER_TYPE::JMP, PARAMETER_TYPE::R8, static_cast<int>(JMP::Z)}, 
        {0x29, INSTRUCTION::ADD, PARAMETER_TYPE::REG, PARAMETER_TYPE::REG, static_cast<int>(REG::HL), static_cast<int>(REG::HL)}, 
        {0x2A, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::REG, static_cast<int>(REG::A), static_cast<int>(REG::HLP)}, 
        {0x2B, INSTRUCTION::DEC, PARAMETER_TYPE::REG, static_cast<int>(REG::HL)}, 
        {0x2C, INSTRUCTION::INC, PARAMETER_TYPE::REG, static_cast<int>(REG::L)}, 
        {0x2D, INSTRUCTION::DEC, PARAMETER_TYPE::REG, static_cast<int>(REG::L)}, 
        {0x2E, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::D8, static_cast<int>(REG::L)}, 
        {0x2F, INSTRUCTION::CPL},  

        {0x30, INSTRUCTION::JR, PARAMETER_TYPE::JMP, PARAMETER_TYPE::R8, static_cast<int>(JMP::NC)}, 
        {0x31, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::D16, static_cast<int>(REG::SP)}, 
        {0x32, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::REG, static_cast<int>(REG::HLM), static_cast<int>(REG::A)}, 
        {0x33, INSTRUCTION::INC, PARAMETER_TYPE::REG, static_cast<int>(REG::SP)}, 
        {0x34, INSTRUCTION::INC, PARAMETER_TYPE::REG, static_cast<int>(REG::HL)}, 
        {0x35, INSTRUCTION::DEC, PARAMETER_TYPE::REG, static_cast<int>(REG::HL)}, 
        {0x36, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::D8, static_cast<int>(REG::HL)}, 
        {0x37, INSTRUCTION::SCF}, 
        {0x38, INSTRUCTION::JR, PARAMETER_TYPE::JMP, PARAMETER_TYPE::R8, static_cast<int>(JMP::C)}, 
        {0x39, INSTRUCTION::ADD, PARAMETER_TYPE::REG, PARAMETER_TYPE::REG, static_cast<int>(REG::HL), static_cast<int>(REG::SP)}, 
        {0x3A, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::REG, static_cast<int>(REG::A), static_cast<int>(REG::HLM)}, 
        {0x3B, INSTRUCTION::DEC, PARAMETER_TYPE::REG, static_cast<int>(REG::SP)}, 
        {0x3C, INSTRUCTION::INC, PARAMETER_TYPE::REG, static_cast<int>(REG::A)}, 
        {0x3D, INSTRUCTION::DEC, PARAMETER_TYPE::REG, static_cast<int>(REG::A)}, 
        {0x3E, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::D8, static_cast<int>(REG::A)}, 
        {0x3F, INSTRUCTION::CCF}
    };

    operationListBottom =
    {
        {0xC0, INSTRUCTION::RET, PARAMETER_TYPE::JMP, static_cast<int>(JMP::NZ)}, 
        {0xC1, INSTRUCTION::POP, PARAMETER_TYPE::REG, PARAMETER_TYPE::D16, static_cast<int>(REG::BC)}, 
        {0xC2, INSTRUCTION::JP, PARAMETER_TYPE::REG, PARAMETER_TYPE::A16, static_cast<int>(JMP::NZ)}, 
        {0xC3, INSTRUCTION::JP, PARAMETER_TYPE::A16}, 
        {0xC4, INSTRUCTION::CALL, PARAMETER_TYPE::REG, PARAMETER_TYPE::A16, static_cast<int>(JMP::NZ)}, 
        {0xC5, INSTRUCTION::PUSH, PARAMETER_TYPE::REG, PARAMETER_TYPE::NONE, static_cast<int>(REG::BC)}, 
        {0xC6, INSTRUCTION::ADD, PARAMETER_TYPE::REG, PARAMETER_TYPE::D8, static_cast<int>(REG::A)}, 
        {0xC7, INSTRUCTION::RST, PARAMETER_TYPE::RST, static_cast<int>(RST::H00)}, 
        {0xC8, INSTRUCTION::RET, PARAMETER_TYPE::REG, static_cast<int>(REG::Z)}, 
        {0xC9, INSTRUCTION::RET}, 
        {0xCA, INSTRUCTION::JP, PARAMETER_TYPE::REG, PARAMETER_TYPE::A16, static_cast<int>(REG::Z)}, 
        {0xCB}, //INVALID //CB MAPPED SOMEWHERE ELSE
        {0xCC, INSTRUCTION::CALL, PARAMETER_TYPE::REG, PARAMETER_TYPE::A16, static_cast<int>(REG::Z)}, 
        {0xCD, INSTRUCTION::CALL, PARAMETER_TYPE::A16}, 
        {0xCE, INSTRUCTION::ADC, PARAMETER_TYPE::REG, PARAMETER_TYPE::D8, static_cast<int>(REG::A)}, 
        {0xCF, INSTRUCTION::RST, PARAMETER_TYPE::RST, static_cast<int>(RST::H08)}, 

        {0xD0, INSTRUCTION::RET, PARAMETER_TYPE::JMP, static_cast<int>(JMP::NC)}, 
        {0xD1, INSTRUCTION::POP, PARAMETER_TYPE::REG, PARAMETER_TYPE::D16, static_cast<int>(REG::DE)}, 
        {0xD2, INSTRUCTION::JP, PARAMETER_TYPE::REG, PARAMETER_TYPE::A16, static_cast<int>(JMP::NZ)}, 
        {0xD3}, //INVALID 
        {0xD4, INSTRUCTION::CALL, PARAMETER_TYPE::REG, PARAMETER_TYPE::A16, static_cast<int>(JMP::NC)}, 
        {0xD5, INSTRUCTION::PUSH, PARAMETER_TYPE::REG, static_cast<int>(REG::DE)}, 
        {0xD6, INSTRUCTION::SUB, PARAMETER_TYPE::D8}, 
        {0xD7, INSTRUCTION::RST, PARAMETER_TYPE::RST, static_cast<int>(RST::H10)}, 
        {0xD8, INSTRUCTION::RET, PARAMETER_TYPE::REG, static_cast<int>(REG::C)}, 
        {0xD9, INSTRUCTION::RETI}, 
        {0xDA, INSTRUCTION::JP, PARAMETER_TYPE::REG, PARAMETER_TYPE::A16, static_cast<int>(REG::C)}, 
        {0xDB}, //INVALID
        {0xDC, INSTRUCTION::CALL, PARAMETER_TYPE::REG, PARAMETER_TYPE::A16, static_cast<int>(REG::C)}, 
        {0xDD},  //INVALID
        {0xDE, INSTRUCTION::SBC, PARAMETER_TYPE::REG, PARAMETER_TYPE::D8, static_cast<int>(REG::A)}, 
        {0xDF, INSTRUCTION::RST, PARAMETER_TYPE::RST, static_cast<int>(RST::H18)},   

        {0xE0, INSTRUCTION::LDH, PARAMETER_TYPE::A8, PARAMETER_TYPE::REG, 0, static_cast<int>(REG::A)}, 
        {0xE1, INSTRUCTION::POP, PARAMETER_TYPE::REG, PARAMETER_TYPE::D16, static_cast<int>(REG::HL)}, 
        {0xE2, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::REG, static_cast<int>(REG::C), static_cast<int>(REG::A)}, 
        {0xE3}, //INVALID 
        {0xE4}, //INVALID 
        {0xE5, INSTRUCTION::PUSH, PARAMETER_TYPE::REG, static_cast<int>(REG::HL)}, 
        {0xE6, INSTRUCTION::AND, PARAMETER_TYPE::D8}, 
        {0xE7, INSTRUCTION::RST, PARAMETER_TYPE::RST, static_cast<int>(RST::H20)}, 
        {0xE8, INSTRUCTION::ADD, PARAMETER_TYPE::REG, PARAMETER_TYPE::R8, static_cast<int>(REG::SP)}, 
        {0xE9, INSTRUCTION::JP, PARAMETER_TYPE::REG, static_cast<int>(REG::HL)}, 
        {0xEA, INSTRUCTION::LD, PARAMETER_TYPE::A16, PARAMETER_TYPE::REG, 0, static_cast<int>(REG::A)}, 
        {0xEB}, //INVALID
        {0xEC}, //INVALID 
        {0xED}, //INVALID
        {0xEE, INSTRUCTION::XOR, PARAMETER_TYPE::D8}, 
        {0xEF, INSTRUCTION::RST, PARAMETER_TYPE::RST, static_cast<int>(RST::H28)},

        {0xF0, INSTRUCTION::LDH, PARAMETER_TYPE::REG, PARAMETER_TYPE::A8, static_cast<int>(REG::A)}, 
        {0xF1, INSTRUCTION::POP, PARAMETER_TYPE::REG, PARAMETER_TYPE::D16, static_cast<int>(REG::AF)}, 
        {0xF2, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::REG, static_cast<int>(REG::A), static_cast<int>(REG::C)}, 
        {0xF3, INSTRUCTION::DI},
        {0xF4}, //INVALID 
        {0xF5, INSTRUCTION::PUSH, PARAMETER_TYPE::REG, static_cast<int>(REG::AF)}, 
        {0xF6, INSTRUCTION::OR, PARAMETER_TYPE::D8}, 
        {0xF7, INSTRUCTION::RST, PARAMETER_TYPE::RST, static_cast<int>(RST::H30)},
        //LD HL, SP+r8 (implicit from opcode), probably will be handled on a separate if 
        {0xF8, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::R8, static_cast<int>(REG::HL)}, 
        {0xF9, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::REG, static_cast<int>(REG::SP), static_cast<int>(REG::HL)}, 
        {0xFA, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::A16, static_cast<int>(REG::A)}, 
        {0xFB, INSTRUCTION::EI},
        {0xFC}, //INVALID 
        {0xFD}, //INVALID
        {0xFE, INSTRUCTION::CP, PARAMETER_TYPE::D8}, 
        {0xFF, INSTRUCTION::RST, PARAMETER_TYPE::RST, static_cast<int>(RST::H38)}
    };
}

//Uses https://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html as a basis
Operation Decoder::generateInstruction(unsigned char** PC){
    unsigned char op = **PC;
    Operation operationToExecute;

    if(op == 0xCB){
        *PC+=1;
        getCBInstruction(PC);
    }
    else if(op >= 0x00 && op <= 0x3F){
        operationToExecute=operationListTop.at(op);
    }
    else if(op >=0xC0 && op <= 0xFF){
        int idx = op - 0xC0;
        operationToExecute=operationListBottom.at(idx);
    }
    
    //LD
    if(op >= 0x40 && op <= 0x7F){
        std::string op1, op2;
        
        //On the opcode table there is a pattern where the 8 registers repeat [B,C,D,E,H,L,HL]
        //Instead of checking all the possible operations I can map the range per instructions on specific cases and then "calculate" the registers based on the lower 4 bits
        uint16_t op2Val = getRegisterFromLast4Bits<uint16_t>(op);
        
        //A similar rule applies for the first 4 bits, but I have to divide it by 8 assuming that it starts from 0x00.
        uint16_t normalizedOp = op - 0x40; 
        //I know that after every 8 elements I move to the next register (normalized B starts at 0x00, c at 0x08, d at 0x10)
        uint16_t op1Val = normalizedOp/8;
        //LD op1, op2
        operationToExecute = {op, INSTRUCTION::LD, PARAMETER_TYPE::REG, PARAMETER_TYPE::REG, 
                              op1Val, op2Val};
    }
    else if(op >= 0x80 && op <= 0xBF){
        //Tries to map ADD, ADC, SUB, SBC, AND, XOR, OR, CP as a "sequential" range of instructions between 0x80 and 0xBF
        int normalizedOp = (op - 0x80)/8;
        uint16_t reg = getRegisterFromLast4Bits<uint16_t>(op);
        switch(normalizedOp){
            case 0:
                operationToExecute = {op, INSTRUCTION::ADD, PARAMETER_TYPE::REG, PARAMETER_TYPE::REG, static_cast<int>(REG::A), reg};
                break;
            case 1:
                operationToExecute = {op, INSTRUCTION::ADC, PARAMETER_TYPE::REG, PARAMETER_TYPE::REG, static_cast<int>(REG::A), reg};
                break;
            case 2:
                operationToExecute = {op, INSTRUCTION::SUB, PARAMETER_TYPE::REG,  reg};
                break;
            case 3:
                operationToExecute = {op, INSTRUCTION::SBC, PARAMETER_TYPE::REG, PARAMETER_TYPE::REG, static_cast<int>(REG::A), reg};
                break;
            case 4:
                operationToExecute = {op, INSTRUCTION::AND, PARAMETER_TYPE::REG,  reg};
                break;
            case 5:
                operationToExecute = {op, INSTRUCTION::XOR, PARAMETER_TYPE::REG,  reg};
                break;
            case 6:
                operationToExecute = {op, INSTRUCTION::OR, PARAMETER_TYPE::REG,  reg};
                break;
            case 7:
                operationToExecute = {op, INSTRUCTION::CP, PARAMETER_TYPE::REG,  reg};
                break;
        }
    }
    if(operationToExecute.invalid){
        std::stringstream err;
        err << "Could not match the opcode "<< std::hex << static_cast<uint16_t>(op) << std::endl;
        throw std::runtime_error(err.str());
    }

    //IF operation + opcode is valid, I fill the parameters and return the data structure that defines this operation
    fillNecessaryParameters(PC, operationToExecute);
    *PC+=1; //Increment program counter pointer
    return operationToExecute;
}

Operation Decoder::getCBInstruction(unsigned char **PC){
    Operation operationToExecute;
    unsigned char op = **PC;
    uint16_t reg = getRegisterFromLast4Bits<uint16_t>(op);
    //Used from 0x40 up to 0xff. It always loops from 0 to 7, hence the /8. Also because it covers 0x40 and 0xff I use mod 8 on top of it, so it always stays betwen 0 and 7.
    //The original intention here was to dublicate this line for each of the 3 if statements 0x40, 0x80, 0xc0 and subtract for each ne of those.
    uint16_t bit = ((op - 0x40) / 8) % 8;
    if(op <= 0x3F){
        int _op = op/8;
        uint16_t reg = getRegisterFromLast4Bits<uint16_t>(op);
        switch(_op){
            case 0:
                operationToExecute = {op, INSTRUCTION::RLC, PARAMETER_TYPE::REG, reg};
            case 1:
                operationToExecute = {op, INSTRUCTION::RRC, PARAMETER_TYPE::REG, reg};
            case 2:
                operationToExecute = {op, INSTRUCTION::RL, PARAMETER_TYPE::REG, reg};
            case 3:
                operationToExecute = {op, INSTRUCTION::RL, PARAMETER_TYPE::REG, reg};
            case 4:
                operationToExecute = {op, INSTRUCTION::SLA, PARAMETER_TYPE::REG, reg};
            case 5:
                operationToExecute = {op, INSTRUCTION::SRA, PARAMETER_TYPE::REG, reg};
            case 6:
                operationToExecute = {op, INSTRUCTION::SWAP, PARAMETER_TYPE::REG, reg};
            case 7:
                operationToExecute = {op, INSTRUCTION::SRL, PARAMETER_TYPE::REG, reg};
        }
    }
    else if(op >= 0x40 && op <= 0x7F){
        operationToExecute = {op, INSTRUCTION::BIT, PARAMETER_TYPE::BIT, PARAMETER_TYPE::REG, bit, reg};
    }
    else if(op >= 0x80 && op <= 0xBF){
        operationToExecute = {op, INSTRUCTION::RES, PARAMETER_TYPE::BIT, PARAMETER_TYPE::REG, bit, reg};
    }
    else if(op >= 0xC0 && op <= 0xFF){
        operationToExecute = {op, INSTRUCTION::RES, PARAMETER_TYPE::BIT, PARAMETER_TYPE::REG, bit, reg};
    }

    return operationToExecute;

}

void Decoder::fillNecessaryParameters(unsigned char **PC, Operation& operationToExecute){
    setParameterPerType(PC, operationToExecute.type[0], operationToExecute.parameter[0]);
    setParameterPerType(PC, operationToExecute.type[1], operationToExecute.parameter[1]);
}

void Decoder::setParameterPerType(unsigned char **PC, PARAMETER_TYPE type, uint16_t& parameter){
    //Start_Number = (Start_Number_High << 8) | (Start_Number_Low & 0xff);
    if(type >= PARAMETER_TYPE::D8 && type <= PARAMETER_TYPE::R8){
        *PC+=1;
        parameter = static_cast<uint16_t>(**PC);
    }
    else if(type >= PARAMETER_TYPE::D16 && type <= PARAMETER_TYPE::A16){
        //Generate 16 bits variable
        *PC+=1;
        parameter = **PC;
        *PC+=1;
        parameter |= **PC<<8;
    }
}