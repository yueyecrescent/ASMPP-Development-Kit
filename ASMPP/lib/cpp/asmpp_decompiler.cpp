#include "../include/asmpp_decompiler.hpp"
#include "../include/asmpp_instruction_declaration.hpp"
#include "../main_dc.hpp"

using namespace utilities::array;
using namespace utilities::string;
using namespace utilities::io;
using namespace asmpp::is;
using namespace asmpp::decompiler;

ASMPPDecompiler::ASMPPDecompiler(InstructionSet &is)
{
    ins_set=is;
}

Array<StringInstruction *> ASMPPDecompiler::decompile(Array<int> machine_code)
{
    int data_field_head=machine_code.getElement(0);
    int ins_pos=0;
    Array<StringInstruction *> sia((data_field_head-1)/2);
    for(register int int_pos=1;int_pos<data_field_head;++int_pos,++ins_pos){
        sia.setElement(ins_pos,new StringInstruction(machine_code.getElement(int_pos),&(machine_code.getElement(machine_code.getElement(++int_pos)+data_field_head)),sia,ins_set));
    }
    machine_code.setDeleteFlag(true);
    return sia;
}

void ASMPPDecompiler::decompile(const char *exec,const char *dest)
{
    std::ofstream fs(dest,std::ios::out);
    if(fs.is_open()){
        try{
            Array<StringInstruction *> sia=decompile(readBinaryAsArray<int>(exec));
            for(int pos=0;pos<sia.length;++pos){//std::cout<<pos<<std::endl;
                fs<<(sia.getElement(pos)->toString().arr_ptr);
                fs<<(pos!=sia.length-1?'\n':'\0');
            }
        }catch(...){
            std::cout<<"Decompile the file \'"<<exec<<"\' failed."<<std::endl;
        }
        fs.close();
    }
}

void ASMPPDecompiler::decompile(const char *exec_file)
{
    StringBuffer sb(getLengthOfCharArray(exec_file));
    sb<<exec_file;
    sb.removeUntil('.');
    sb<<"asmpp";
    decompile(exec_file,sb.toString().arr_ptr);
}
