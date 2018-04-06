#include "../include/asmpp_virtual_machine.hpp"
#include "../include/asmpp_instruction_declaration.hpp"
#include "../main_vm.hpp"

using namespace asmpp::vm;

inline void ASMPPVirtualMachine::allocateMemory()
{
    reg_ptr=(int *)malloc(register_number);
    m_ptr=(int *)malloc(heap_capcity);
}

ASMPPVirtualMachine::ASMPPVirtualMachine(InstructionSet &is,int reg_num,int heap_cap)
{
    this->register_number=reg_num;
    this->heap_capcity=heap_cap;
    ins_set=is;
}

ASMPPVirtualMachine::~ASMPPVirtualMachine()
{
    shutDown();
}

void ASMPPVirtualMachine::bootUp()
{
    allocateMemory();
}

void ASMPPVirtualMachine::shutDown()
{
    free(reg_ptr);
    free(m_ptr);
}

void ASMPPVirtualMachine::exec(const char *file_path)
{
    Executable exe(this,file_path);
    exe.execute();
}
