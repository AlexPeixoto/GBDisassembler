#include "header.h"
#include <cstring>

using namespace Memory::Cartridge;

void Header::processHeader(){
    setTitleName();
    setType();
    setCatridgeType();
    setRomBankCount();
    setRamBankCount();
    setDestination();
}
void Header::setTitleName(){
    std::memcpy(romName, ptr + TITLE_START, 16);
}
void Header::setType(){
    if(*(ptr + TYPE_START) == 0x80)
        type=GB_TYPE::CGB;
    else
        type=GB_TYPE::OGB;
}
void Header::setFunctions(){
    if(*(ptr + FUNCTIONS_START) == 0x00)
        functions=GB_FUNCTIONS::GB;
    else if(*(ptr + FUNCTIONS_START) == 0x00)
        functions=GB_FUNCTIONS::SGB;
}
void Header::setCatridgeType(){
    //This should come from cartridge type class
}
void Header::setRomBankCount(){
    uint8_t code = (*(ptr + ROM_BANK_COUNT_START));
    //0 - 2, 1 - 4... so shift the bits by 2
    if(code >= 0x00 && code < 0x06){
        romBankCount = (1 << (code + 2));
    }
    switch(code){
        case 0x52:
            ramBankCount = 72;
            break;
        case 0x53:
            romBankCount = 80;
            break;
        case 0x54:
            romBankCount = 96;
            break;
    }
}
void Header::setRamBankCount(){
    uint8_t code = (*(ptr + RAM_BANK_COUNT_START));
    if(code == 0x01 || code == 0x02)
        ramBankCount = 1;
    else if(code == 0x03)
        ramBankCount = 4;
    else if(code == 0x04)
        ramBankCount = 16;
}
void Header::setDestination(){
    uint8_t destination = (*(ptr + DESTINATION_CODE_START));
    if(destination == 0x00)
        destinationCode = GB_DESTINATION::JAPANESE;
    else if(destination == 0x01)
        destinationCode = GB_DESTINATION::NONJAPANESE;
}