#include <iostream>

using namespace std;
using namespace utilities::io;
using namespace asmpp::decompiler;

int main(int argc,char *argv[]){
    ASMPPDecompiler asmpp_decompiler(__InstructionSet__(ASMPP));
    for(int i=1;i<argc;++i)
        asmpp_decompiler.decompile(argv[i]);
    return 0;
}
