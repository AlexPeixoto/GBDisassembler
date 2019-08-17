#include <vector>
#include <functional>
#include <string>

//As of now, this class simulates the opcode execution
//This class implements the logic to process the opcode, but it will only print the opcode to a device.
//This is an initial work for a GB Emulator and an experimentation.
class Opcode
{
    private:
    enum class OP{
        NOP, LD, INC, DEC, RLCA, ADD, RRCA, STOP, RLA, JR, RRA, CPL, SCF, DAA, CCF, HALT, ADD, SUB, ADC, SBC, AND, XOR, OR, CP, RET, POP, JP, PUSH, RST, CB, CALL, RETI, LDH, DI, EI
    };

    enum class PARAMETER_TYPE{
        NONE,
        D8,
        D16,
        A8,
        A16,
        R8,
        REG
    };
    enum class REG{
        B,
        C,
        D,
        E,
        H,
        L,
        HL,
        A,
        BC,
        SP
    };
    //Reg to string
    const std::vector<std::string> registers = {"B", "C", "D", "E", "H", "L", "HL", "A"};

    
    //This can, in theory, be initialized in compile time
    struct Operations{
        Operations(OP opcode, std::string description, 
                   PARAMETER_TYPE type_1 = PARAMETER_TYPE::NONE, PARAMETER_TYPE type_2 = PARAMETER_TYPE::NONE,
                    uint16_t parameter_1 = 0, uint16_t parameter_2 =0){
            this->opcode=opcode;
            this->description=description;
            this->type[0] = type_1;
            this->type[1] = type_2;
            this->parameter[0] = parameter_1;
            this->parameter[1] = parameter_2;
        }
        OP opcode;
        std::string description;
        
        //I will pass the reg as a parameter as well
        PARAMETER_TYPE type[2];
        uint16_t parameter[2];
        bool invalid;

        //Can always pass 2 parameters, but the functor only might use one or 2
        std::function<void(int16_t*)> executeOpcode;
    };
    //Maps between 0x00 and 0x3F (direct access)
    std::vector<Operations> operationListBottom;
    //Maps between 0xC0 and 0XFF
    std::vector<Operations> operationListTop;
    std::vector<Operations> CBOperationList;

    Opcode();

    unsigned char* generateInstruction(unsigned char *PC);
    void getCBInstruction(unsigned char *PC);

    //Basically on several cases the first register B and the last one HL is mapped between x0 and x7)s,e for x8 and xf.
    //Because of that we can feed the 4 lower bits to this function and it will give the registers, this helps a lot, as its used between the 0x40 and 0xBF opcodes
    template <typename T>
    inline T getRegisterFromLast4Bits(uint8_t _v){
        return static_cast< T>((_v & 0x0F) % 0x08);
    }

    std::string regToString(int _r) const{
        return registers[_r];
    }
};