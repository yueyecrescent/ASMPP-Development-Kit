#ifndef ASMPP_INSTRUCTION_DECLARATION
#define ASMPP_INSTRUCTION_DECLARATION

IS_DEF(ASMPP,16)

/*寄存器操作*/
        //加载立即数进寄存器
        INS_BEGIN(ASMPP,LDRIV,0x00000000,RN)
            REG_VAL(0)=NUM_VAL(1);
        INS_END(LDRIV)
        //从内存加载到寄存器
        INS_BEGIN(ASMPP,LD2RFM,0x00000001,RM)
            REG_VAL(0)=MEM_VAL(1);
        INS_END(LD2RFM)
        //从寄存器加载到内存
        INS_BEGIN(ASMPP,LD2MFR,0x00000002,MR)
            MEM_VAL(0)=REG_VAL(1);
        INS_END(LD2MFR)
/*内存操作*/
        //移动数据
        INS_BEGIN(ASMPP,MOV,0x00000003,MM)
            MEM_VAL(0)=MEM_VAL(1);
        INS_END(MOV)
/*数据操作*/
        //定义int型变量

        //定义boolean型变量

/*算数操作*/
        //加法保存结果至寄存器
        INS_BEGIN(ASMPP,ADDR,0x00000004,RRR)
            REG_VAL(0)=REG_VAL(1)+REG_VAL(2);
        INS_END(ADDR)
        //减法
        INS_BEGIN(ASMPP,SUBR,0x00000005,RRR)
            REG_VAL(0)=REG_VAL(1)-REG_VAL(2);
        INS_END(SUBR)
        //乘法
        INS_BEGIN(ASMPP,MULR,0x00000006,RRR)
            REG_VAL(0)=REG_VAL(1)*REG_VAL(2);
        INS_END(MULR)
        //除法
        INS_BEGIN(ASMPP,DIVR,0x00000007,RRR)
            REG_VAL(0)=REG_VAL(1)/REG_VAL(2);
        INS_END(DIVR)
        //求余
        INS_BEGIN(ASMPP,MODR,0x00000008,RRR)
            REG_VAL(0)=REG_VAL(1)%REG_VAL(2);
        INS_END(MODR)
        //自增int
        INS_BEGIN(ASMPP,INC,0x00000009,R)
            REG_VAL(0)++;
        INS_END(INC)
/*内置便捷函数*/
        INS_BEGIN(ASMPP,PRINTR,0x0000000A,R)
            std::cout<<REG_VAL(0);
        INS_END(PRINTR)

        INS_BEGIN(ASMPP,PRINTRLN,0x0000000B,R)
            std::cout<<REG_VAL(0)<<std::endl;
        INS_END(PRINTRLN)

        INS_BEGIN(ASMPP,PRINTM,0x0000000C,M)
            std::cout<<MEM_VAL(0);
        INS_END(PRINTM)

        INS_BEGIN(ASMPP,PRINTMLN,0x0000000D,M)
            std::cout<<MEM_VAL(0)<<std::endl;
        INS_END(PRINTMLN)

        INS_BEGIN(ASMPP,PRINTN,0x0000000E,N)
            std::cout<<NUM_VAL(0);
        INS_END(PRINTN)

        INS_BEGIN(ASMPP,PRINTNLN,0x0000000F,N)
            std::cout<<NUM_VAL(0)<<std::endl;
        INS_END(PRINTNLN)

#endif //ASMPP_INSTRUCTION_DECLARATION
