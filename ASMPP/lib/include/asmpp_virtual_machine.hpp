#ifndef ASMPP_VIRTUAL_MACHINE
#define ASMPP_VIRTUAL_MACHINE

#include <malloc.h>
#include <fstream>
#include "io_utilities.hpp"
#include "asmpp_instruction_set.hpp"

using namespace asmpp::is;

namespace asmpp
{
    namespace vm
    {
        class Executable;

        class ASMPPVirtualMachine
        {
        friend class Executable;
        private:
            InstructionSet ins_set;
            int *reg_ptr,*m_ptr;
            int register_number,heap_capcity;

            inline void allocateMemory();
        public:
            ASMPPVirtualMachine(InstructionSet &is,int reg_num,int heap_cap);
            ~ASMPPVirtualMachine();
            void bootUp();
            void shutDown();
            void exec(const char *file_path);
        };

        class Executable
        {
        private:
            ASMPPVirtualMachine *vm;
            int *text_field_head;
            int *data_field_head;
        public:
            Executable(ASMPPVirtualMachine *vm_)
            {
                vm=vm_;
            }
            Executable(ASMPPVirtualMachine *vm_,const char *file_path)
            {
                vm=vm_;
                load(file_path);
            }
            void load(const char *file_path)
            {
                ifstream file(file_path,ios::in|ios::binary);
                GET_FILE_LENGTH(file,length)
                text_field_head=(int*)malloc(length-sizeof(int));
                if(file.is_open()){
                    file.read((char*)text_field_head,sizeof(int));
                    file.seekg(sizeof(int),ios::beg);
                    data_field_head=text_field_head+*text_field_head-1;
                    file.read((char*)text_field_head,length-sizeof(int));
                    file.close();
                }
            }
            void execute(){
                int ins_len=(data_field_head-text_field_head)/2;
                for(int ins_pos=0;ins_pos<ins_len;++ins_pos)
                    vm->ins_set.instruction_set.getElement(*(text_field_head+2*ins_pos))->exec(vm->reg_ptr,vm->m_ptr,text_field_head,data_field_head,ins_pos,*(text_field_head+2*ins_pos+1));
            }
        };
    }
}
#endif // ASMPP_VIRTUAL_MACHINE
