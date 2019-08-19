#pragma once

#include <vector>
#include <functional>
#include <string>

#include "CPU.h"

namespace CPU{
//As of now, this class simulates the decofing step
//This class implements the logic to process the opcode, and retrieve the necessary parameters for the opcode (if any).
//This is an initial work for a GB Emulator and an experimentation.
class Decoder
{
    private:
    //Maps between 0x00 and 0x3F (direct access)
    std::vector<Operation> operationListBottom;
    //Maps between 0xC0 and 0XFF
    std::vector<Operation> operationListTop;

    //Decode CB instructions only
    Operation getCBInstruction(unsigned char **PC);
    //Fills the necessary parameters on the Operation data structure
    void fillNecessaryParameters(unsigned char **PC, Operation& operationToExecute);
    //Get the type of the necessary parameter and advance the PC flag to retrieve the bytes to fill the parameter (passed by reference)
    void setParameterPerType(unsigned char **PC, PARAMETER_TYPE type, uint16_t& parameter);

    //Basically on several cases the first register B and the last one HL is mapped between x0 and x7)s,e for x8 and xf.
    //Because of that we can feed the 4 lower bits to this function and it will give the registers, this helps a lot, as its used between the 0x40 and 0xBF opcodes
    template <typename T>
    inline T getRegisterFromLast4Bits(uint8_t _v){
        return static_cast< T>((_v & 0x0F) % 0x08);
    }


    public:
    Decoder();

    Operation generateInstruction(unsigned char **PC);;
};

}