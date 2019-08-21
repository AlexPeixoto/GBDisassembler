#pragma once

#include <cstdint>

namespace Memory{
    namespace Cartridge{
        enum GB_TYPE{
            CGB,
            OGB //Its either gameboy color or "another gameboy"
        };
        enum GB_FUNCTIONS{ //tells if the rom has super gameboy features
            GB,
            SGB
        };

        class Header{
            private:
                //START OF EACH SECTION
                const uint16_t TITLE_START = 0x134;
                const uint16_t TYPE_START = 0x143;
                const uint16_t FUNCTIONS_START = 0x146;
                const uint16_t CARTRIDGE_TYPE_START = 0x147;
                const uint16_t ROM_BANK_COUNT_START = 0x148;
                const uint16_t RAM_BANK_COUNT_START = 0x149;
                const uint16_t DESTINATION_CODE_START = 0x14A;
                //END
                
                unsigned char* ptr;
                
                char romName[16];
                //16KB bank size
                uint8_t romBankCount;
                uint8_t ramBankCount;
                uint8_t destinationCode;


                void processHeader();
                void setTitleName();
                void setType();
                void setFunctions();
                void setCatridgeType();
                void setRomBankCount();
                void setRamBankCount();
                void setDestination();
            public:
            Header(unsigned char* ptr){
                this->ptr = ptr;
            }

            const char* getRomName();
            uint16_t getLicense();

            
        
        };
    }
}