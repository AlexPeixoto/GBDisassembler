#include "stringify.h"
#include <sstream>
#include <iomanip>

using namespace Disassembly;
using namespace CPU;

#define COMMENT

const std::vector<std::string> Stringify::instructionStrTable = {"NOP", "LD", "INC", "DEC", "RLCA", "ADD", "RRCA", "STOP", "RLA", "JR", "RRA", "CPL", "SCF", "DAA", "CCF", "HALT", "SUB", "ADC", "SBC", "AND", "XOR", "OR", "CP", "RET", "POP", "JP", "PUSH", "RST", "CB", "CALL", "RETI", "LDH", "DI", "EI",
                                                   "RLC", "RRC", "RL", "RR", "SLA", "SRA", "SWAP", "SRL", "BIT", "RES", "SET"};
const std::vector<std::string> Stringify::regStrTable = {"B", "C", "D", "E", "H", "L", "HL", "A", "BC", "DE", "HL+", "HL-", "F", "AF", "Z", "SP"};
const std::vector<std::string> Stringify::jmpStrTable = {"NZ", "Z", "NC", "C"};
const std::vector<std::string> Stringify::rstStrTable = {"00H", "10H", "20H", "30H", "08H", "18H", "28H", "38H"};

std::string Stringify::operationToString(const CPU::Operation& op){
    std::stringstream line;
    line << opcodeToString(op.instruction);

    if(op.type[0] != PARAMETER_TYPE::NONE)
        line  << " " << parameterToString(op.type[0], op.parameter[0]);
    if(op.type[1] != PARAMETER_TYPE::NONE)
        line << ", " << parameterToString(op.type[1], op.parameter[1]);
    
    #ifdef COMMENT
        line << generateComment(op);
    #endif

    return line.str();
}

std::string Stringify::opcodeToString(CPU::INSTRUCTION instruction){
    return instructionStrTable[static_cast<int>(instruction)];
}

std::string Stringify::parameterToString(CPU::PARAMETER_TYPE type, uint16_t parameter){
    std::stringstream ss;
    ss << "0x" << std::setfill('0') << std::setw(2);
    switch(type){
        case PARAMETER_TYPE::A16:
        case PARAMETER_TYPE::A8:
        case PARAMETER_TYPE::D16:
        case PARAMETER_TYPE::D8:
        case PARAMETER_TYPE::R8:
            ss << std::hex << parameter;
            break;
        case PARAMETER_TYPE::BIT:
            return std::to_string(parameter);
        case PARAMETER_TYPE::JMP:
            return jmpStrTable[parameter];
        case PARAMETER_TYPE::REG:
            return regStrTable[parameter];
        case PARAMETER_TYPE::RST:
            return rstStrTable[parameter];

        default:
            return "";
    }
    return ss.str();
}

std::string Stringify::generateComment(const CPU::Operation& op){
    std::stringstream line;
    line << "   ;" << std::hex << op.opcode;
    for(int idx=0; idx<=1; idx++){
        switch(op.type[idx]){
            case PARAMETER_TYPE::A16:
            case PARAMETER_TYPE::A8:
            case PARAMETER_TYPE::D16:
            case PARAMETER_TYPE::D8:
                if(idx)
                    line << ", ";
                else
                    line << " ";
                line << std::hex << static_cast<int16_t>(op.parameter[idx]);
                break;
        }
        
    }
    return line.str();
}

const std::vector<std::string> Stringify::cartridgeTypeTable = {"NONE", "CGB", "OGB"};
const std::vector<std::string> Stringify::cartridgeFunctionTable = {"NONE", "GB", "SGB"};
const std::vector<std::string> Stringify::cartridgeDestinationTable = {"JAPANESE", "NON-JAPANESE"};

const std::vector<std::string> Stringify::cartridgeMbcTable = {"NONE", "MBC1", "MBC2", "MMM01", "MBC3", "MBC5", "OTHER"};
const std::vector<std::string> Stringify::cartridgeRamTable = {"NONE", "RAM", "SRAM"};
const std::vector<std::string> Stringify::cartridgeBatteryTable = {"NONE", "PRESENT"};
const std::vector<std::string> Stringify::cartridgeRumbleTable = {"NONE", "PRESENT"};
const std::vector<std::string> Stringify::cartridgeTimerTable = {"NONE", "PRESENT"};

std::string Stringify::headerToString(Memory::Cartridge::Header& header){
    std::stringstream headerString;
    headerString << "===========Cartridge heaeder information===========" << std::endl;
    headerString << "Title: " << header.getRomName() << std::endl;
    headerString << "Type: " << cartridgeTypeTable[static_cast<int>(header.getType())] << std::endl;
    headerString << "Function: " << cartridgeFunctionTable[static_cast<int>(header.getFunction())] << std::endl;
    headerString << "Destination: " << cartridgeDestinationTable[static_cast<int>(header.getDestination())] << std::endl;
    
    headerString << "Rom bank count: " << (int)header.getRomBankCount() << std::endl;
    headerString << "Ram bank count: " << (int)header.getRamBankCount() << std::endl;

    headerString << "Memory bank controller: " << cartridgeMbcTable[static_cast<int>(header.getCartridgeType().mbc)] << std::endl;
    headerString << "Ram type: " << cartridgeRamTable[static_cast<int>(header.getCartridgeType().ram)] << std::endl;
    headerString << "Battery: " << cartridgeBatteryTable[static_cast<int>(header.getCartridgeType().battery)] << std::endl;
    headerString << "Rumble: " << cartridgeRumbleTable[static_cast<int>(header.getCartridgeType().rumble)] << std::endl;
    headerString << "Timer: " << cartridgeTimerTable[static_cast<int>(header.getCartridgeType().timer)] << std::endl;

    return headerString.str();
}