#pragma once

#include <string>
#include <vector>
#include "CPU.h"
#include "header.h"

namespace Disassembly{
class Stringify{
    public:
        static std::string headerToString(Memory::Cartridge::Header& header);
        static std::string operationToString(const CPU::Operation& op);
    private:
        static std::string opcodeToString(CPU::INSTRUCTION instruction);
        static std::string parameterToString(CPU::PARAMETER_TYPE type, uint16_t parameter);

        static std::string generateComment(const CPU::Operation& op);

        //This is a direct table of the enum on the CPU.h file, this has to be updated with that file
        static const std::vector<std::string> instructionStrTable;
        static const std::vector<std::string> regStrTable;
        static const std::vector<std::string> jmpStrTable;
        static const std::vector<std::string> rstStrTable;


        //Cartridge header table
        static const std::vector<std::string> cartridgeTypeTable;
        static const std::vector<std::string> cartridgeFunctionTable;
        static const std::vector<std::string> cartridgeDestinationTable;

        static const std::vector<std::string> cartridgeMbcTable;
        static const std::vector<std::string> cartridgeRamTable;
        static const std::vector<std::string> cartridgeBatteryTable;
        static const std::vector<std::string> cartridgeRumbleTable;
        static const std::vector<std::string> cartridgeTimerTable;
};
}