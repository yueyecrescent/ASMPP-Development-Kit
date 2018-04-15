#ifndef ASMPP_INSTRUCTION_DECLARATION
#define ASMPP_INSTRUCTION_DECLARATION

IS_DEF(ASMPP,64)

/*寄存器操作*/
        //加载立即数进寄存器
        INS_BEGIN(ASMPP,LDRIV,1,RN)
            REG_VAL(0)=NUM_VAL(1);
        INS_END(LDRIV)
        //从内存加载到寄存器
        INS_BEGIN(ASMPP,LD2RFM,2,RM)
            REG_VAL(0)=MEM_VAL(1);
        INS_END(LD2RFM)
        //移动寄存器值
        INS_BEGIN(ASMPP,MOVR,3,RR)
            REG_VAL(0)=REG_VAL(1);
        INS_END(MOVR)
        //从寄存器加载到内存
        INS_BEGIN(ASMPP,LD2MFR,4,MR)
            MEM_VAL(0)=REG_VAL(1);
        INS_END(LD2MFR)
/*内存操作*/
        //移动数据
        INS_BEGIN(ASMPP,MOV,5,MM)
            MEM_VAL(0)=MEM_VAL(1);
        INS_END(MOV)
/*控制流操作*/
        INS_BEGIN(ASMPP,JMP,6,N)
            INS_POS=NUM_VAL(0);
        INS_END(JMP)

/*算数操作*/
        //加法保存结果至寄存器
        INS_BEGIN(ASMPP,ADDR,7,RRR)
            REG_VAL(0)=REG_VAL(1)+REG_VAL(2);
        INS_END(ADDR)
        //减法
        INS_BEGIN(ASMPP,SUBR,8,RRR)
            REG_VAL(0)=REG_VAL(1)-REG_VAL(2);
        INS_END(SUBR)
        //乘法
        INS_BEGIN(ASMPP,MULR,9,RRR)
            REG_VAL(0)=REG_VAL(1)*REG_VAL(2);
        INS_END(MULR)
        //除法
        INS_BEGIN(ASMPP,DIVR,10,RRR)
            REG_VAL(0)=REG_VAL(1)/REG_VAL(2);
        INS_END(DIVR)
        //求余
        INS_BEGIN(ASMPP,MODR,11,RRR)
            REG_VAL(0)=REG_VAL(1)%REG_VAL(2);
        INS_END(MODR)
        //自增int
        INS_BEGIN(ASMPP,INC,12,R)
            REG_VAL(0)++;
        INS_END(INC)
/*内置便捷函数*/
        INS_BEGIN(ASMPP,PRINTR,13,R)
            std::cout<<REG_VAL(0);
        INS_END(PRINTR)

        INS_BEGIN(ASMPP,PRINTRLN,14,R)
            std::cout<<REG_VAL(0)<<std::endl;
        INS_END(PRINTRLN)

        INS_BEGIN(ASMPP,PRINTM,15,M)
            std::cout<<MEM_VAL(0);
        INS_END(PRINTM)

        INS_BEGIN(ASMPP,PRINTMLN,16,M)
            std::cout<<MEM_VAL(0)<<std::endl;
        INS_END(PRINTMLN)

        INS_BEGIN(ASMPP,PRINTN,17,N)
            std::cout<<NUM_VAL(0);
        INS_END(PRINTN)

        INS_BEGIN(ASMPP,PRINTNLN,18,N)
            std::cout<<NUM_VAL(0)<<std::endl;
        INS_END(PRINTNLN)

        INS_BEGIN(ASMPP,IFREQLJMP,19,NRR)
            if(REG_VAL(1)==REG_VAL(2))
                INS_POS=NUM_VAL(0);
        INS_END(IFREQLJMP)

        INS_BEGIN(ASMPP,IFMEQLJMP,20,NMM)
            if(MEM_VAL(1)==MEM_VAL(2))
                INS_POS=NUM_VAL(0);
        INS_END(IFMEQLJMP)

        INS_BEGIN(ASMPP,IFRLESJMP,21,NRR)
            if(REG_VAL(1)<REG_VAL(2))
                INS_POS=NUM_VAL(0);
        INS_END(IFRLESJMP)

        INS_BEGIN(ASMPP,IFMLESJMP,22,NMM)
            if(MEM_VAL(1)<MEM_VAL(2))
                INS_POS=NUM_VAL(0);
        INS_END(IFMLESJMP)

        INS_BEGIN(ASMPP,IFRMORJMP,23,NRR)
            if(REG_VAL(1)>REG_VAL(2))
                INS_POS=NUM_VAL(0);
        INS_END(IFRMORJMP)

        INS_BEGIN(ASMPP,IFMMORJMP,24,NMM)
            if(MEM_VAL(1)>MEM_VAL(2))
                INS_POS=NUM_VAL(0);
        INS_END(IFMMORJMP)

        INS_BEGIN(ASMPP,GOTO,25,L)
            INS_POS=LAB_VAL(0);
        INS_END(GOTO)

        INS_BEGIN(ASMPP,SVLB2R,26,RL)
            REG_VAL(0)=LAB_VAL(1);
        INS_END(SVLB2R)

        INS_BEGIN(ASMPP,SVLB2M,27,ML)
            MEM_VAL(0)=LAB_VAL(1);
        INS_END(SVLB2M)

        INS_BEGIN(ASMPP,IFREQLGOTO,28,LRR)
            if(REG_VAL(1)==REG_VAL(2))
                INS_POS=LAB_VAL(0);
        INS_END(IFREQLGOTO)

        INS_BEGIN(ASMPP,IFMEQLGOTO,29,LMM)
            if(MEM_VAL(1)==MEM_VAL(2))
                INS_POS=LAB_VAL(0);
        INS_END(IFMEQLGOTO)

        INS_BEGIN(ASMPP,IFRLESGOTO,30,LRR)
            if(REG_VAL(1)<REG_VAL(2))
                INS_POS=LAB_VAL(0);
        INS_END(IFRLESGOTO)

        INS_BEGIN(ASMPP,IFMLESGOTO,31,LMM)
            if(MEM_VAL(1)<MEM_VAL(2))
                INS_POS=LAB_VAL(0);
        INS_END(IFMLESGOTO)

        INS_BEGIN(ASMPP,IFRMORGOTO,32,LRR)
            if(REG_VAL(1)>REG_VAL(2))
                INS_POS=LAB_VAL(0);
        INS_END(IFRMORGOTO)

        INS_BEGIN(ASMPP,IFMMORGOTO,33,LMM)
            if(MEM_VAL(1)>MEM_VAL(2))
                INS_POS=LAB_VAL(0);
        INS_END(IFMMORGOTO)

#endif //ASMPP_INSTRUCTION_DECLARATION
