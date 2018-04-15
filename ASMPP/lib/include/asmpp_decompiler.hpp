#ifndef ASMPP_DECOMPILER
#define ASMPP_DECOMPILER

#include <iostream>
#include "array.hpp"
#include "string_utilities.hpp"
#include "io_utilities.hpp"
#include "asmpp_instruction_set.hpp"

using namespace utilities::array;
using namespace utilities::string;
using namespace utilities::io;
using namespace asmpp::is;

namespace asmpp{
    namespace decompiler{
        typedef struct StringInstruction
        {
            String<> lable;
            MachineInstruction *ins;
            Array<String<>> args;
            StringInstruction()
            {
            }
            StringInstruction(int &byte_code,int *data_address,Array<StringInstruction *> arr,InstructionSet &is)
            {
                ins=is.getInstructionByByteCode(byte_code);
                args=Array<String<>>(ins->arg_number);
                StringBuffer sb(ins->arg_number*32);
                for(int pos=0;pos<ins->arg_number;++pos)
                {
                    switch(ins->para_types[pos])
                    {
                        case 'R':
                            sb<<'R'<<(String<>::intParseToString(*(data_address+pos)));
                            break;
                        case 'M':
                            sb<<(String<>::intParseToString_Hex_0x(*(data_address+pos)));
                            break;
                        case 'N':
                            sb<<(String<>::intParseToString(*(data_address+pos)));
                            break;
                        case 'L':
                            sb<<'L'<<(String<>::intParseToString(*(data_address+pos)));
                            arr.getElement(*(data_address+pos))->lable=sb.toString();
                            break;
                    }
                    args.setElement(pos,sb.toString());
                    sb.clear();
                }
            }
            String<> toString()
            {
                StringBuffer sb(lable.length+ins->name.length+ins->arg_number*32);
                if(lable.length)sb<<lable<<':';
                sb<<ins->name<<' ';
                for(int pos=0;pos<args.length;++pos)
                {
                    sb<<args.getElement(pos).arr_ptr;
                    sb<<(pos!=args.length-1?',':'\0');
                }
                sb.deleteData();
                return sb.toString();
            }
        } StringInstruction;

        class ASMPPDecompiler
        {
        private:
            InstructionSet ins_set;
        public:
            ASMPPDecompiler(InstructionSet &is);
            Array<StringInstruction *> decompile(Array<int> machine_code);
            void decompile(const char *exec,const char *dest);
            void decompile(const char *exec);
        };
    }
}

#endif //ASMPP_DECOMPILER
