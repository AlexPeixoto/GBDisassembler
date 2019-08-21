#pragma once

#include <cstdint>

namespace Memory{
    namespace Cartridge{
        enum class MBC{
            NONE,
            MBC1,
            MBC2,
            MMM01,
            MBC3,
            MBC5
        };

        enum class RAM{
            NONE,
            RAM,
            SRAM
        };

        enum class BATTERY{
            NONE,
            PRESENT
        };

        enum class RUMBLE{
            NONE,
            PRESENT
        };

        enum class TIMER{
            NONE,
            PRESENT
        };

        struct CartridgeType{
            MBC mbc=MBC::NONE;
            RAM ram=RAM::NONE;
            BATTERY battery=BATTERY::NONE;
            RUMBLE rumble=RUMBLE::NONE;
            TIMER timer=TIMER::NONE;
            //This basically maps 1F,FD,FE as cartridge type
            bool isSpecial();

            void identifyCartridgeType(uint8_t type){
                if(type >= 0x01 && type <=0x05){
                    mbc=MBC::MBC1;
                }
            }
        };
    }
}