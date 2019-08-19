#pragma once

#include <cstdint>

//This file maps all instructions, paarmeters, registers and jump conditions. It also defines the Operation struct that will store the instruction + parameters in a way that is easier to use in order to process.
namespace CPU{
    enum class INSTRUCTION{
        NOP, LD, INC, DEC, RLCA, ADD, RRCA, STOP, RLA, JR, RRA, CPL, SCF, DAA, CCF, HALT, SUB, ADC, SBC, AND, XOR, OR, CP, RET, POP, JP, PUSH, RST, CB, CALL, RETI, LDH, DI, EI,
        //CB
        RLC,
        RRC,
        RL, RR,
        SLA, SRA,
        SWAP, SRL,
        BIT,/* BIT,
        BIT, BIT,
        BIT, BIT,
        BIT, BIT,*/
        RES,/* RES,
        RES, RES,
        RES, RES,
        RES, RES,*/
        SET/*, SET,
        SET, SET,
        SET, SET, 
        SET, SET*/
    };

    enum class PARAMETER_TYPE{
        NONE,

        D8,
        A8,
        R8,

        D16,
        A16,

        REG,
        JMP,
        RST,
        BIT
    };
    enum class REG{
        //Preserve this order from B to A as this is the order seen for several instructions
        B, C,
        D, E,
        H, L,
        HL,
        A,

        BC,
        DE,
        HLP,
        HLM,
        F, //F IS NOT ALWAYS USED, IT CONTAINS ALL THE FLAGS (ZNHC)
        AF,
        Z,
        SP
    };

    //It is passed as a parameter (type JUMP)
    enum class JMP{
        NZ,
        Z,
        NC,
        C
    };

    //Maps parameters for RST calls
    enum class RST{
        H00,
        H10,
        H20,
        H30,
        H08,
        H18,
        H28,
        H38
    };
    
    //This can, in theory, be initialized in compile time
    struct Operation{
        uint16_t opcode;
        INSTRUCTION instruction;
        
        //I will pass the reg as a parameter as well
        PARAMETER_TYPE type[2];
        uint16_t parameter[2];
        bool invalid;
        
        Operation(){
            this->invalid=true;
        }

        Operation(uint16_t opcode, INSTRUCTION instruction,
                   PARAMETER_TYPE type_1 = PARAMETER_TYPE::NONE, PARAMETER_TYPE type_2 = PARAMETER_TYPE::NONE,
                   uint16_t parameter_1 = 0, uint16_t parameter_2 = 0){
            this->opcode=opcode;
            this->instruction = instruction;
            this->type[0] = type_1;
            this->type[1] = type_2;
            this->parameter[0] = parameter_1;
            this->parameter[1] = parameter_2;
            this->invalid = false;
        }
        Operation(uint16_t opcode, INSTRUCTION instruction,
                   PARAMETER_TYPE type_1,  uint16_t parameter_1) : Operation(opcode, instruction, type_1, PARAMETER_TYPE::NONE, parameter_1, 0) {};

        
        //When only opcode is supplied, its marked as invalid operation
        Operation(uint16_t opcode){
            this->opcode = opcode;
            this->invalid = true;
        }
    };
}