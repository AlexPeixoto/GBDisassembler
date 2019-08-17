#include "opcode.h"

Opcode::Opcode(){
    operationListTop = 
    {
        {0x00, "NOP "}, 
        {0x01, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x02, "LD (BC), A"}, 
        {0x03, "INC BC"}, 
        {0x04, "INC B"}, 
        {0x05, "DEC B"}, 
        {0x06, "LD B", PARAMETER_TYPE::D8}, 
        {0x07, "RLCA"}, 
        //TRICK TO SUBSTITUTE THE %% FOR THE PARAMETER
        {0x08, "LD %%, SP", PARAMETER_TYPE::A16}, 
        {0x09, "ADD HL, BC"}, 
        {0x0A, "LD A, (BC)"}, 
        {0x0B, "DEC BC"}, 
        {0x0C, "INC C"}, 
        {0x0D, "DEC C"}, 
        {0x0E, "LD C, ", PARAMETER_TYPE::D8}, 
        {0x0F, "RRCA"}, 
       
        {0x10, "NOP "}, 
        {0x11, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x12, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x13, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x14, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x15, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x16, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x17, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x18, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x19, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x1A, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x1B, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x1C, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x1D, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x1E, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x1F, "LD BC, ", PARAMETER_TYPE::D16}, 

        {0x20, "NOP "}, 
        {0x21, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x22, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x23, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x24, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x25, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x26, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x27, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x28, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x29, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x2A, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x2B, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x2C, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x2D, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x2E, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x2F, "LD BC, ", PARAMETER_TYPE::D16}, 

        {0x30, "NOP "}, 
        {0x31, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x32, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x33, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x34, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x35, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x36, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x37, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x38, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x39, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x3A, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x3B, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x3C, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x3D, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x3E, "LD BC, ", PARAMETER_TYPE::D16}, 
        {0x3F, "LD BC, ", PARAMETER_TYPE::D16}

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