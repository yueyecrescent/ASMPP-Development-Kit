#ifndef ASMPP_INSTRUCTION_SET
#define ASMPP_INSTRUCTION_SET

#define REG_VAL(OFFSET) (*(register_field_address+*(data_field_address+data_address_offset+OFFSET)))
#define MEM_VAL(OFFSET) (*(memory_field_address+*(data_field_address+data_address_offset+OFFSET)))
#define NUM_VAL(OFFSET) (*(data_field_address+data_address_offset+OFFSET))
#define LAB_VAL(OFFSET) (*(data_field_address+data_address_offset+OFFSET))

#define IS_DEF(ISNAME,NUM) asmpp::is::InstructionSet Is_##ISNAME(NUM);

#define INS_BEGIN(IS,INSNAME,BYTECODE,TYPES) void Ins_exec_##INSNAME(int* register_field_address,int* memory_field_address,int* text_field_address,int* data_field_address,int& ins_pos,int& data_address_offset);\
        class Ins_def_##INSNAME:public asmpp::is::MachineInstruction{\
        public:\
            Ins_def_##INSNAME(){\
                byte_code=BYTECODE;\
                name=String<>(#INSNAME);\
                para_types=#TYPES;\
                arg_number=getLengthOfCharArray(#TYPES);\
                exec=Ins_exec_##INSNAME;\
                Is_##IS.instruction_set.setElement(byte_code,this);\
            }\
        };\
        void Ins_exec_##INSNAME(int* register_field_address,int* memory_field_address,int* text_field_address,int* data_field_address,int& ins_pos,int& data_address_offset){

#define INS_END(INSNAME) }\
        Ins_def_##INSNAME Ins_##INSNAME;

#define __InstructionSet__(NAME) Is_##NAME
#define __InstructionDef__(NAME) Is_def_##NAME
#define __InstructionExec__(NAME) Ins_exec_##NAME
#define __InstructionInstance__(NAME) Ins_##NAME

#include "array.hpp"
#include "string_utilities.hpp"

using namespace utilities::string;
using namespace utilities::array;

typedef void (*insexecptr)(int*,int*,int*,int*,int&,int&);
namespace asmpp
{
    namespace is
    {
        class MachineInstruction;
        class InstructionSet
        {
        public:
            Array<MachineInstruction *> instruction_set;
            int instruction_number;
            InstructionSet();
            InstructionSet(int ins_number);
            InstructionSet(InstructionSet &&is);
            MachineInstruction * getInstructionByName(String<> name);
            MachineInstruction & operator [] (int index);
            InstructionSet & operator = (InstructionSet &is);
            InstructionSet & operator = (InstructionSet &&is);
            MachineInstruction * getInstructionByByteCode(int byte_code);
        };

        class MachineInstruction
        {
        public:
            String<> name;
            char *para_types;
            int byte_code;
            int arg_number;
            insexecptr exec;
            MachineInstruction()
            {
            }
        };
    }
}

#endif // ASMPP_INSTRUCTION_SET

