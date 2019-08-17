#include <iostream>
#include <iomanip>
#include <fstream>

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
    //Read as 16 bits
    /*uint16_t* data16 = reinterpret_cast<uint16_t*>(data);
    for(uint16_t *byte = data16; byte != data16+fileSize; byte++){
        std::cout << std::setfill('0') << std::setw(4) << std::hex << *byte << std::endl;
    }*/
    unsigned char* udata = reinterpret_cast<unsigned char*>(data);
    for(unsigned char* byte = udata; byte != udata+fileSize; byte++){
        std::cout << std::setfill('0') << std::setw(2) << std::hex << (int)(*byte) << std::endl;
    }

    delete[] data;
    
    return 0;
}