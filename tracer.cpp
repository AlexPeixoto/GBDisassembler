#include <iomanip>

#include "tracer.h"
#include "decoder.h"

using namespace Disassembly;

bool Tracer::addJump(std::stack<unsigned char*>& addressList, unsigned char* begin, const CPU::Operation& op){
    if(op.instruction == INSTRUCTION::JP){
        if(op.type[1] == PARAMETER_TYPE::NONE){
            addressList.push(static_cast<unsigned char*>(begin + op.parameter[0]));
            return true;
        }
    }
    else if(op.instruction == INSTRUCTION::JP){
        if(op.type[0] == PARAMETER_TYPE::A16)
            addressList.push(static_cast<unsigned char*>(begin + op.parameter[0]));
        else if(op.type[1] == PARAMETER_TYPE::A16)
            addressList.push(static_cast<unsigned char*>(begin + op.parameter[1]));
        return true;
    }

    return false;
}

unsigned char* Tracer::addCall(unsigned char* begin, const CPU::Operation& op){
     if(op.instruction == INSTRUCTION::CALL || op.instruction == INSTRUCTION::RST){
        if(op.type[0] == PARAMETER_TYPE::A16){
            return static_cast<unsigned char*>(begin + op.parameter[0]);
        }
        else if(op.type[1] == PARAMETER_TYPE::A16){
            return static_cast<unsigned char*>(begin + op.parameter[1]);
        }
    }
    return nullptr;
}

/*
 * This is by far the most "complex" and messy part of the code.
 * What we do here is, we set a starting point (as 0x100 as the gameboy cartridge documentation indicates)
 * The staring point is put inside a stack, we pop it and start decoding those instructions.
 * If we find a jump we add to the addressList and then stop decoding the next instruction, this way creating a "fake" jump
 * if its a conditional jump that WE CAN FIGURE OUT (does not depend on registers) we put on the stack but we do not stop the next instruction.
 * This will be stored on a vector that is big enough to store 32KB program and this will be used later to generate the output code.
 */
void Tracer::decodeTracing(unsigned char* begin, size_t fileSize){
    //Mark the end
    const unsigned char* end = begin+0x100+fileSize;
    //Pointer that will hold the current address being processed
    unsigned char* udata;
    //Will start from here
    std::stack<unsigned char*> addressList, callReturnList;
    addressList.push(begin+0x100);

    //Decode instructions
    CPU::Decoder decoder;
    //While there is a "starting point" jump list
    //I have to "correct" the addresses here, everything is stored as it is on cartridge, but if I want to "jump" I have to add the begin back because it is a real pointer
    while(!addressList.empty()){
        udata = addressList.top();
        addressList.pop();
        while(udata < end){
            const uint16_t cartAddr = udata-begin;
            //If we already passed by this part of the code we just skip it
            if(operationList[cartAddr].first)
                break;

            //Decode instruction
            Operation op = decoder.generateInstruction(&udata);
            //Store on vector
            operationList[cartAddr] = {true, op};

            /*unsigned char* addr = addCall(begin, op);
            if(addr){
                callReturnList.push(udata);
                udata=addr;
            }
            if(op.instruction == INSTRUCTION::RET || op.instruction == INSTRUCTION::RETI){
                udata = callReturnList.top();
                callReturnList.pop();
            }*/
            //handle jump instructions, if it returns true it means that we have to jump now (AKA not a conditional jump or an "non jump instruction")
            if(addJump(addressList, begin, op)){
                break;
            }
        }
    }
}

const std::vector<std::pair<bool, CPU::Operation>> Tracer::getOperationList(){
    return operationList;
}