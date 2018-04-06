#include <iostream>

using namespace std;
using namespace asmpp::compiler;

int main(int argc,char *argv[]){
    ASMPPCompiler asmpp_compiler(__InstructionSet__(ASMPP));
    for(int i=1;i<argc;++i)
        asmpp_compiler.compile(argv[i]);
    return 0;
}

