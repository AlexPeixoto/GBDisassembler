#include <vector>
#include <functional>
#include <string>

//As of now, this class simulates the opcode execution
//This class implements the logic to process the opcode, but it will only print the opcode to a device.
//This is an initial work for a GB Emulator and an experimentation.
class Opcode
{
    private:
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
        A
    };
    //Reg to string
    const std::vector<std::string> registers = {"B", "C", "D", "E", "H", "L", "HL", "A"};

    
    //This can, in theory, be initialized in compile time
    struct Operations{
        Operations(uint8_t opcode, std::string description, PARAMETER_TYPE type = PARAMETER_TYPE::NONE){
            this->opcode=opcode;
            this->description=description;
            this->type = type;
        }
        uint16_t opcode;
        std::string description;
        
        //There is only a single parameter
        PARAMETER_TYPE type;
        uint16_t parameter;
        bool invalid;

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