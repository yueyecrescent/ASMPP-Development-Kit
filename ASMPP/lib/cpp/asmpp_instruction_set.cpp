#include "../include/asmpp_instruction_set.hpp"

using namespace asmpp::is;
using namespace utilities::string;
using namespace utilities::array;

InstructionSet::InstructionSet()
{
}

InstructionSet::InstructionSet(int ins_number)
{
    instruction_number=ins_number;
    instruction_set=Array<MachineInstruction *>(ins_number);
}

InstructionSet::InstructionSet(InstructionSet &&is)
{
    instruction_number=is.instruction_number;
    instruction_set=is.instruction_set;
}

MachineInstruction * InstructionSet::getInstructionByName(String<> ins_name)
{
    for(int i=0; i<instruction_set.length; ++i)
    {
        if(instruction_set.getElement(i)->name.equals(ins_name))
            return instruction_set.getElement(i);
    }
    return nullptr;
}

MachineInstruction & InstructionSet::operator [] (int index)
{
    return *instruction_set.getElement(index);
}

InstructionSet & InstructionSet::operator = (InstructionSet &is)
{
    instruction_number=is.instruction_number;
    instruction_set=is.instruction_set;
    return *this;
}

InstructionSet & InstructionSet::operator = (InstructionSet &&is)
{
    instruction_number=is.instruction_number;
    instruction_set=is.instruction_set;
    return *this;
}

MachineInstruction * InstructionSet::getInstructionByByteCode(int byte_code)
{
    return instruction_set.getElement(byte_code);
}
