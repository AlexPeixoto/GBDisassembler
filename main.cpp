#include <iostream>
#include <fstream>
#include <iomanip>

#include "stringify.h"
#include "tracer.h"

using namespace Disassembly;

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

    if(header.getCartridgeType().mbc != Memory::Cartridge::MBC::NONE){
        std::cerr << "Only roms without memory controller are supported!";
    }

    Tracer tracer;
    tracer.decodeTracing(begin, fileSize);
    auto operationList = tracer.getOperationList();

    for(int addr=0; addr<operationList.size(); ++addr){
        if(operationList[addr].first){
            std::cout << "0x" << std::setfill('0') << std::setw(2) << std::hex << (addr) << "  ";
            std::cout << Disassembly::Stringify::operationToString(operationList[addr].second) << std::endl;
        }
    }

    delete[] data;
    
    return 0;
}

