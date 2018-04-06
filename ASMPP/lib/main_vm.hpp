using namespace std;
using namespace asmpp::vm;

int main(int argc,char *argv[]){
    ASMPPVirtualMachine vm(__InstructionSet__(ASMPP),512,1024*1024*64);
    vm.bootUp();
    for(int i=1;i<argc;++i)
        vm.exec(argv[i]);
    return 0;
}
