# ASMPP-Development-Kit
## <Project Info>
<br>A assembly language's compiler and virtual machine.You can remade it and put it into your own project.＜/br＞
<br>All the source code are in folder "ASMPP/lib/".The C++ standard is C++14.＜/br＞
<br>If you use Code::Blocks IDE,then you can import the project directly.＜/br＞
<br>This is an open source project.And **you can use it for commercial use**.＜/br＞
## <How to use>
<br>There is a file named "ASMPP/lib/include/asmpp_instruction_declaration.hpp",you can define your code there.＜/br＞
  <br>Example:＜/br＞
  <br>INS_BEGIN(ASMPP,LDRIV,0x00000000,RN)＜/br＞
      <br>REG_VAL(0)=NUM_VAL(1);＜/br＞
  <br>INS_END(LDRIV)＜/br＞
  <br>"ASMPP" is the name of instruction set.＜/br＞
  <br>"LDRIV" is the name of instruction.＜/br＞
  <br>"0x00000000" is the bytecode of the instruction.＜/br＞
  <br>"RN" is the parameters' types of the instruction.＜/br＞
  <br>"R" is short for register,"M" is short for memory,"N" is short for number(immediate value).＜/br＞
  <br>In the macro "INS_END",just input the name of the instruction again.＜/br＞
<br>When you define a new instruction,don't forget to extend the instruction set.＜/br＞
  <br>Example:＜/br＞
  <br>IS_DEF(ASMPP,16)＜/br＞
  <br>"ASMPP" is the name of instruction set.＜/br＞
  <br>"16" is the max number of instructions.＜/br＞
  <br>This macro can define a instruction set.In the file "ASMPP/lib/include/asmpp_instruction_declaration.hpp",
  There is a default instruction set named ASMPP.＜/br＞
<br>When you create a instance of compiler,you need to give a instruction set to the constructor.＜/br＞
  <br>Example:＜/br＞
  <br>ASMPPCompiler compiler(__InstructionSet__(ASMPP));＜/br＞
  <br>__InstructionSet__(IS_NAME) is a macro.It references to the instruction set "IS_NAME".＜/br＞
<br>When you create a instance of compiler,you need to give a instruction set,the number of register and the capcity of memory to the constructor.＜/br＞
  <br>Example:＜/br＞
  <br>ASMPPVirtualMachine vm(__InstructionSet__(ASMPP),32,1024);＜/br＞
  <br>"32" is the number of register.It means you can use R0~R31.＜/br＞
  <br>"1024" is the capcity of memory.It means you cna use 0x0000 to 0x0400＜/br＞
