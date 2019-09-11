#pragma once

#include <iostream>
#include <stack>
#include <vector>

#include "CPU.h"

using namespace CPU;

namespace Disassembly{
    class Tracer{
        private:
        //This can probably be optimied, there is an "idea", that this is 32KB of intructions (no parameters) (32*1024+1)
        //This code is not that concerned with memory usage.
        const int count = 32*1024+1;
        //This is a workaround on a compiler bug....
        std::vector<std::pair<bool, CPU::Operation>> operationList { std::vector<std::pair<bool, CPU::Operation>>(count, {false, {}}) };

        bool addJump(std::stack<unsigned char*>& addressList, unsigned char* begin, const CPU::Operation& op);
        //Return the pointer to the call
        unsigned char* addCall(unsigned char* begin, const CPU::Operation& op);

        public:
        void decodeTracing(unsigned char* begin, size_t fileSize);

        const std::vector<std::pair<bool, CPU::Operation>> getOperationList();

    };
}