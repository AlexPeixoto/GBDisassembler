#pragma once

#include <string>
#include <vector>
#include "CPU.h"

namespace Disassembly{
class Stringify{
    public:
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
};
}