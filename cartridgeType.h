#pragma once

#include <cstdint>

namespace Memory{
    namespace Cartridge{
        enum class MBC{
            NONE, //ROM ONLY
            MBC1,
            MBC2,
            MMM01,
            MBC3,
            MBC5,
            OTHER //Some proprietary camera, hudson HuC-3.... not being even checked at this stage
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
            MBC mbc=MBC::OTHER;
            RAM ram=RAM::NONE;
            BATTERY battery=BATTERY::NONE;
            RUMBLE rumble=RUMBLE::NONE;
            TIMER timer=TIMER::NONE;
            //This basically maps 1F,FD,FE as cartridge type
            bool isSpecial(){
                return mbc == MBC::OTHER;
            }

            void identifyCartridgeType(uint8_t type){
                if(type == 0x00 || type == 0x08 || type == 0x09){
                    mbc=MBC::NONE;
                   setNoControllerFeatures(type);
                }
                else if(type >= 0x01 && type <= 0x03){
                    mbc=MBC::MBC1;
                    setMBC1Features(type);
                }
                else if(type == 0x05 || type == 0x06){
                    mbc=MBC::MBC2;
                    setMBC2Features(type);
                }
                else if(type >= 0x0B && type <= 0x0D){
                    mbc=MBC::MMM01;
                    setMMM01Features(type);
                }
                else if(type == 0x0F || type == 0x13){
                    mbc=MBC::MBC3;
                    setMBC3Features(type);
                }
                else if(type >= 0x19 && type <= 0x1E){
                    mbc=MBC::MBC5;
                    setMBC5Features(type);
                }
                else
                    mbc=MBC::OTHER;
            }

            //Those methods have a strong assumption that the controller was already identified
            void setNoControllerFeatures(uint8_t type){
                 if(type != 0x01){
                    ram = RAM::RAM;
                }
                if(type == 0x09){
                    battery = BATTERY::PRESENT;
                }
            }
            void setMBC1Features(uint8_t type){
                if(type != 0x01){
                    ram = RAM::RAM;
                }
                if(type == 0x03){
                    battery=BATTERY::PRESENT;
                }
            }
            void setMBC2Features(uint8_t type){
                if(type == 0x06){
                    battery=BATTERY::PRESENT;
                }
            }
            void setMMM01Features(uint8_t type){
                if(type != 0x0B){
                    ram=RAM::SRAM;
                }
                if(type == 0x0D){
                    battery=BATTERY::PRESENT;
                }
            }
            void setMBC3Features(uint8_t type){
                //Battery
                if(type == 0x0F || type == 0x10 || type == 0x13)
                    battery=BATTERY::PRESENT;
                //Timer
                if(type == 0x0F || type == 0x10)
                    timer=TIMER::PRESENT;
                //Ram
                if(type == 0x10 || type == 0x12 || type == 0x13)
                    ram=RAM::RAM;
            }
            void setMBC5Features(uint8_t type){
                //Ram
                if(type == 0x1A || type == 0x1B){
                    ram=RAM::RAM;
                }
                //SRam
                else if(type == 0x1D || type == 0x1E){
                    ram=RAM::SRAM;
                }
                //Battery
                if(type == 0x1B || type == 0x1E){
                    battery=BATTERY::PRESENT;
                }
                //Rumble
                if(type >= 0x1C && type <= 0x1E){
                    rumble=RUMBLE::PRESENT;
                }
            }
        };
    }
}