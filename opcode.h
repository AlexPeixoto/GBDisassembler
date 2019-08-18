#include <vector>
#include <functional>
#include <string>

//As of now, this class simulates the decofing step
//This class implements the logic to process the opcode, and retrieve the necessary parameters for the opcode (if any).
//This is an initial work for a GB Emulator and an experimentation.
class Decoder
{
    private:
    enum class INSTRUCTION{
        NOP, LD, INC, DEC, RLCA, ADD, RRCA, STOP, RLA, JR, RRA, CPL, SCF, DAA, CCF, HALT, SUB, ADC, SBC, AND, XOR, OR, CP, RET, POP, JP, PUSH, RST, CB, CALL, RETI, LDH, DI, EI
    };
    enum class CBINSTRUCTIONS{
        RLC = static_cast<int>(INSTRUCTION::EI) + 1,
        RRC,
        RL, RR,
        SLA, SRA,
        SWAP, SRL,
        BIT,/* BIT,
        BIT, BIT,
        BIT, BIT,
        BIT, BIT,*/
        RES,/* RES,
        RES, RES,
        RES, RES,
        RES, RES,*/
        SET/*, SET,
        SET, SET,
        SET, SET, 
        SET, SET*/
    };

    enum class PARAMETER_TYPE{
        NONE,
        D8,
        D16,
        A8,
        A16,
        R8,
        REG,
        JMP,
        RST
    };
    enum class REG{
        B, C,
        BC,
        D, E,
        DE,
        H, L,
        HL,
        HLP,
        HLM,

        A, F, //F IS NOT ALWAYS USED, IT CONTAINS ALL THE FLAGS (ZNHC)
        AF,
        Z,
        SP
    };

    //It is passed as a parameter (type JUMP)
    enum class JMP{
        NZ = (static_cast<int>(REG::DE) + 1),
        Z,
        NC,
        C
    };

    //Maps parameters for RST calls
    enum class RST{
        H00 = (static_cast<int>(JMP::C) + 1),
        H10,
        H20,
        H30,
        H08,
        H18,
        H28,
        H38
    };
    //Reg to string
    const std::vector<std::string> registers = {"B", "C", "D", "E", "H", "L", "HL", "A"};

    
    //This can, in theory, be initialized in compile time
    struct Operations{
        Operations(uint16_t opcode, INSTRUCTION instruction,
                   PARAMETER_TYPE type_1 = PARAMETER_TYPE::NONE, PARAMETER_TYPE type_2 = PARAMETER_TYPE::NONE,
                   uint16_t parameter_1 = 0, uint16_t parameter_2 = 0){
            this->opcode=opcode;
            this->instruction = instruction;
            this->type[0] = type_1;
            this->type[1] = type_2;
            this->parameter[0] = parameter_1;
            this->parameter[1] = parameter_2;
            this->invalid = false;
        }

        Operations(uint16_t opcode, INSTRUCTION instruction,
                   PARAMETER_TYPE type_1,  uint16_t parameter_1) : Operations(opcode, instruction, type_1, PARAMETER_TYPE::NONE, parameter_1, 0) {};
        
        //When only opcode is supplied, its marked as invalid operation
        Operations(uint16_t opcode){
            this->opcode = opcode;
            this->invalid = true;
        }

        uint16_t opcode;
        INSTRUCTION instruction;
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

    Decoder();

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