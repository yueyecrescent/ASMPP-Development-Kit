#ifndef ASMPP_COMPILER
#define ASMPP_COMPILER

//For lexer
#define flush_token(type) {\
                        if(!string_buffer.isEmpty()){\
                            token_buffer.append(Token(type,string_buffer.toString()));\
                            string_buffer.clear();\
                            token_end=false;\
                            last_type=type;\
                        }\
                    }

#define flush_lable {\
                        if(!string_buffer.isEmpty()){\
                            lable_buffer.append(Lable(string_buffer.toString(),ins_pos));\
                            string_buffer.clear();\
                            token_end=false;\
                            last_type=lable;\
                        }\
                    }
//For syntaxer
#define flush_singleins {\
                        sigins_buffer.append(SingleInstruction(this_keyword,arg_buffer.toArray(),this,table.Lables));\
                        arg_buffer.clear();\
                    }

#define abort_error(num,token,info,cpler) {\
                        std::cout<<"Error : at the "<<num<<" token '"<<(token.value.getCharArray())<<"' : ";\
                        std::cout<<info<<std::endl;\
                        cpler->has_error=true;\
                    }

#define abort_error_this(info) abort_error(tokennum,this_token,info,this)

#define abort_error_last(info) abort_error((tokennum-1),tokens[tokennum-2],info,this)

#define abort_error_flushing(info) {\
                        std::cout<<"Error : at the instruction the token '"<<(ins.getCharArray())<<"' : ";\
                        std::cout<<info<<std::endl;\
                        compiler->has_error=true;\
                    }

#include <iostream>
#include "array.hpp"
#include "string_utilities.hpp"
#include "io_utilities.hpp"
#include "asmpp_instruction_set.hpp"

using namespace utilities::io;
using namespace utilities::array;
using namespace utilities::string;
using namespace asmpp::is;

namespace asmpp
{
    namespace compiler
    {
        struct SingleInstruction;
        struct Token;
        struct Lable;
        struct TokenTable;
        class ASMPPCompiler
        {
            friend struct SingleInstruction;
        private:
            bool has_error=false;
            InstructionSet ins_set;
        public:
            ASMPPCompiler(InstructionSet &is);
            ~ASMPPCompiler();
            //Lexer
            TokenTable lex(String<> src);
            void debug_lexer(const char* file,const char* dest);
            //Syntaxer
            Array<SingleInstruction> syntax(TokenTable table);
            void debug_syntaxer(const char* file,const char* dest);
            //Generator
            Array<int> generate(Array<SingleInstruction> ins);
            void debug_compiler(const char* file,const char* dest);
            //Compiler
            void compile(const char *src_file,const char *dest_file);
            void compile(const char *src_file);
        };

        enum TokenType
        {
            null=0,unknown,error,lable,keyword,arg
        };

        template<typename T>
        void print_(T info)
        {
            std::cout<<info;
        }
        template<typename T,typename ...Ts>
        void print_(T info,Ts ...infos)
        {
            print_<T>(info);
            print_<Ts...>(infos...);
        }
        template<typename T,typename ...Ts>
        void print(T info,Ts ...infos)
        {
            print_(info,infos...);
            std::cout<<std::endl;
        }

        typedef struct Token
        {
            TokenType type;
            String<> value;
            Token()
            {
            }
            explicit Token(const Token &token)
            {
                this->type=token.type;
                this->value=String<>(token.value);
            }
            Token(Token &&token)
            {
                this->type=token.type;
                this->value=token.value;
            }
            Token(String<> v)
            {
                this->type=TokenType::unknown;
                this->value=v;
            }
            Token(TokenType t,String<> v)
            {
                this->type=t;
                this->value=v;
            }
            Token & operator = (Token &token)
            {
                this->type=token.type;
                this->value=token.value;
                return *this;
            }
            Token & operator = (Token &&token)
            {
                this->type=token.type;
                this->value=token.value;
                return *this;
            }
            void print()
            {
                std::cout<<
                "<"<<value.arr_ptr<<","<<
                    (type==keyword?"keyword":"")<<
                    (type==arg?"arg":"")<<
                    (type==null?"null":"")<<
                    (type==unknown?"unknown":"")<<
                    (type==error?"error":"")<<
                ">"<<std::endl;
            }
        } Token;

        typedef struct Lable
        {
            String<> name;
            int line;
            Lable()
            {
            }
            Lable(String<> name_,int line_)
            {
                name=name_;
                line=line_;
            }

            void print()
            {
                std::cout<<
                "<"<<name.arr_ptr<<","<<line<<">"<<std::endl;
            }
        } Lable;

        typedef struct TokenTable
        {
            Array<Token> Tokens;
            Array<Lable> Lables;
            TokenTable(Array<Token> tokens,Array<Lable> lables){
                Tokens=tokens;
                Lables=lables;
            }
            TokenTable(TokenTable &&t){
                Tokens=t.Tokens;
                Lables=t.Lables;
            }
            TokenTable& operator= (TokenTable &t){
                Tokens=t.Tokens;
                Lables=t.Lables;
                return *this;
            }
            TokenTable& operator= (TokenTable &&t){
                Tokens=t.Tokens;
                Lables=t.Lables;
                return *this;
            }
        } TokenTable;

        typedef struct SingleInstruction
        {
        public:
            int keyword_bytecode;
            Array<int> arguments;
            SingleInstruction()
            {
            }
            SingleInstruction(String<> ins,Array<String<>> args,ASMPPCompiler *compiler_,Array<Lable> lables)
            {
                this->compiler=compiler_;
                arguments=Array<int>(args.length);
                keyword_bytecode=getByteCodeAndCheckArgNumber(ins,args.length);
                for(int i=0; i<args.length; ++i)
                    arguments.setElement(i,getArgumentValueAndCheckArgType(keyword_bytecode,i,args[i],lables));
            }
        private:
            ASMPPCompiler *compiler;

            inline int getByteCodeAndCheckArgNumber(String<> ins,int num)
            {
                MachineInstruction *mi=compiler->ins_set.getInstructionByName(ins);
                if(mi==nullptr)
                {
                    abort_error_flushing("No such a instruction.")
                }
                else
                {
                    if(mi->arg_number==num)
                    {
                        return mi->byte_code;
                    }
                    else
                    {
                        print("Error : The instruction '",ins.arr_ptr,"' need ",mi->arg_number," arguments.");
                        compiler->has_error=true;
                    }
                }
                return 0;
            }

            inline int getArgumentValueAndCheckArgType(int ins_code,int arg_pos,String<> arg,Array<Lable> lables)
            {
                switch(String<>::charToUpperCase(arg[0]))
                {
                case 'R':
                    if(*(compiler->ins_set.getInstructionByByteCode(ins_code)->para_types+arg_pos)=='R')
                        return arg.parseToInt(1,arg.length-1);
                        //abort_error()
                        return -1;
                case '0':
                    if(String<>::charToUpperCase(arg[1])=='X')
                    {
                        if(*(compiler->ins_set.getInstructionByByteCode(ins_code)->para_types+arg_pos)=='M')
                            return arg.parseToInt_Hex(2,arg.length-1);
                        //abort_error()
                        return -1;
                    }
                }
                if(arg.isNumber())
                {
                    if(*(compiler->ins_set.getInstructionByByteCode(ins_code)->para_types+arg_pos)=='N')
                        return arg.parseToInt();
                }else{
                    if(*(compiler->ins_set.getInstructionByByteCode(ins_code)->para_types+arg_pos)=='L')
                        for(int i=0;i<lables.length;++i)
                            if(lables.getElement(i).name.equals(arg))return lables.getElement(i).line;
                }
                //abort_error()
                return 0;
            }
        } SingleInstruction;
    }
}
#endif // ASMPP_COMPILER
