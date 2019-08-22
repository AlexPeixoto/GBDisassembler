#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <endian.h>

#include "decoder.h"
#include "stringify.h"
#include "cartridgeType.h"

using namespace CPU;

int main(int argc, char** argv){
    if(argc != 2)
        return 1;
    //Assumes that the first parameter is the name of the file
    std::string filename = argv[1];
    std::cout << "File opened:" << filename << std::endl;
    std::ifstream file(filename, std::ios::in |std::ios::binary | std::ios::ate);
    if(!file.good()){
        std::cerr << "Failed to open the file: " << filename << std::endl;
        return 2;
    }
    size_t fileSize = file.tellg();
    char* data = new char[fileSize];
    file.seekg (0, std::ios::beg);
	file.read (data, fileSize);//copy file into memory


    unsigned char* begin = reinterpret_cast<unsigned char*>(data);
    unsigned char* udata = reinterpret_cast<unsigned char*>(data+0x100);
    std::vector<CPU::Operation> operationList;
    
    //This will be used later to implement the tracing mechanism
    //32KB, 8 byte per instruction (assuming that there is no operand and data segment)
    operationList.reserve(32 * 1000 / 8);
    CPU::Decoder decoder;
    while(udata < begin+0x100+fileSize){
        //Print current address
        std::cout << "0x" << std::setfill('0') << std::setw(2) << std::hex << (int)(udata-begin) << "  ";
        Operation op = decoder.generateInstruction(&udata);
        std::cout << Disassembly::Stringify::operationToString(op) << std::endl;
        if(op.instruction == INSTRUCTION::JP){
            if(op.type[1] == PARAMETER_TYPE::NONE){
                if(begin + op.parameter[0] < udata)
                    break;
                udata = begin + op.parameter[0];
            }
        }

    }

    delete[] data;
    
    return 0;
}