# ASMPP-Development-Kit
<Project Info>
A assembly language's compiler and virtual machine.You can remade it and put it into your own project.
All the source code are in folder "ASMPP/lib/".The C++ standard is C++14.
If you use Code::Blocks IDE,then you can import the project directly.
This is an open source project.And you CAN use it for commercial use.
<How to use>
There is a file named "ASMPP/lib/include/asmpp_instruction_declaration.hpp",you can define your code there.
  Example:
  INS_BEGIN(ASMPP,LDRIV,0x00000000,RN)
      REG_VAL(0)=NUM_VAL(1);
  INS_END(LDRIV)
  "ASMPP" is the name of instruction set.
  "LDRIV" is the name of instruction.
  "0x00000000" is the bytecode of the instruction.
  "RN" is the parameters' types of the instruction.
  "R" is short for register,"M" is short for memory,"N" is short for number(immediate value).
  In the macro "INS_END",just input the name of the instruction again.
When you define a new instruction,don't forget to extend the instruction set.
  Example:
  IS_DEF(ASMPP,16)
  "ASMPP" is the name of instruction set.
  "16" is the max number of instructions.
  This macro can define a instruction set.In the file "ASMPP/lib/include/asmpp_instruction_declaration.hpp",
  There is a default instruction set named ASMPP.
When you create a instance of compiler,you need to give a instruction set to the constructor.
  Example:
  ASMPPCompiler compiler(__InstructionSet__(ASMPP));
  __InstructionSet__(IS_NAME) is a macro.It references to the instruction set "IS_NAME".
When you create a instance of compiler,you need to give a instruction set,the number of register and the capcity of memory to the constructor.
  Example:
  ASMPPVirtualMachine vm(__InstructionSet__(ASMPP),32,1024);
  "32" is the number of register.It means you can use R0~R31.
  "1024" is the capcity of memory.It means you cna use 0x0000 to 0x0400
