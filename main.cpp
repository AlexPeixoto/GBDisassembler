#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <endian.h>
#include <stack>

#include "decoder.h"
#include "stringify.h"
#include "cartridgeType.h"

using namespace CPU;

int loadFileTo(std::string filename, char** data)
{
    //Assumes that the first parameter is the name of the file
    std::cout << "File opened:" << filename << std::endl;
    std::ifstream file(filename, std::ios::in |std::ios::binary | std::ios::ate);
    if(!file.good()){
        std::cerr << "Failed to open the file: " << filename << std::endl;
        return 0;
    }

    //All the cartridge data is stored on a file
    size_t fileSize = file.tellg();
    *data = new char[fileSize];
    file.seekg (0, std::ios::beg);
	file.read (*data, fileSize);//copy file into memory

    return fileSize;
}

bool addJump(std::stack<unsigned char*>& addressList, unsigned char* begin, const CPU::Operation& op){
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
    }
    /*
    CALL IS NOT PROPERLY HANDLED AS IT HAS TO HANDLE RET TO GO BACK TO ORIGINAL ADDRESS
    else if(op.instruction == INSTRUCTION::CALL){
        if(op.type[0] == PARAMETER_TYPE::A16)
            addressList.push(static_cast<unsigned char*>(begin + op.parameter[0]));
        else if(op.type[1] == PARAMETER_TYPE::A16)
            addressList.push(static_cast<unsigned char*>(begin + op.parameter[1]));

    }
    */
    return false;
}

/*
 * This is by far the most "complex" and messy part of the code.
 * What we do here is, we set a starting point (as 0x100 as the gameboy cartridge documentation indicates)
 * The staring point is put inside a stack, we pop it and start decoding those instructions.
 * If we find a jump we add to the addressList and then stop decoding the next instruction, this way creating a "fake" jump
 * if its a conditional jump that WE CAN FIGURE OUT (does not depend on registers) we put on the stack but we do not stop the next instruction.
 * This will be stored on a vector that is big enough to store 32KB program and this will be used later to generate the output code.
 */
void decodeTracing(unsigned char* begin, size_t fileSize, std::vector<std::pair<bool, CPU::Operation>>& operationList){
    
    //Mark the end
    const unsigned char* end = begin+0x100+fileSize;
    //Pointer that will hold the current address being processed
    unsigned char* udata;
    //Will start from here
    std::stack<unsigned char*> addressList;
    addressList.push(begin+0x100);

    //Decode instructions
    CPU::Decoder decoder;
    //While there is a "starting point" jump list
    //I have to "correct" the addresses here, everything is stored as it is on cartridge, but if I want to "jump" I have to add the begin back because it is a real pointer
    while(!addressList.empty()){
        //std::cout << "Pop jump" << std::endl;
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

            //handle jump instructions, if it returns true it means that we have to jump now (AKA not a conditional jump or an "non jump instruction")
            if(addJump(addressList, begin, op)){
                break;
            }
        }
    }
}

//This can be heavily improved, as of now this is a simple code to initialize what is needed and generate the disassembly
int main(int argc, char** argv){
    if(argc != 2)
        return 1;

    std::string filename = argv[1];
    char* data;
    size_t fileSize = loadFileTo(filename, &data);

    if(!fileSize)
        return 2;

    unsigned char* begin = reinterpret_cast<unsigned char*>(data);

    //Generate header
    Memory::Cartridge::Header header(begin);
    std::cout << Disassembly::Stringify::headerToString(header) << std::endl;

    //32KB)
    constexpr uint32_t count = 32 * 1024 + 1;
    std::vector<std::pair<bool, CPU::Operation>> operationList(count, {false, {}});
    decodeTracing(begin, fileSize, operationList);

    for(int addr=0; addr<operationList.size(); ++addr){
        if(operationList[addr].first){
            std::cout << "0x" << std::setfill('0') << std::setw(2) << std::hex << (addr) << "  ";
            std::cout << Disassembly::Stringify::operationToString(operationList[addr].second) << std::endl;
        }
    }

    delete[] data;
    
    return 0;
}

