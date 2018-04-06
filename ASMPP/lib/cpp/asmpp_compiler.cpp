#include "../include/asmpp_compiler.hpp"
#include "../include/asmpp_instruction_declaration.hpp"
#include "../main_c.hpp"

using namespace asmpp::compiler;
using namespace utilities::string;
using namespace utilities::array;

ASMPPCompiler::ASMPPCompiler(InstructionSet &is)
{
    ins_set=is;
}

ASMPPCompiler::~ASMPPCompiler()
{
}
//Lexer
TokenTable ASMPPCompiler::lex(String<> src)
{
    bool token_end=false;
    bool is_comment=false;
    bool is_error=false;
    TokenType last_type=null;
    register int linenum=0;
    int ins_pos=0;
    char this_char=' ';
    DataBuffer<Token> token_buffer(src.length);
    DataBuffer<Lable> lable_buffer(src.length);
    StringBuffer string_buffer(src.length);
    for(int pos=-1; pos<src.length; this_char=src[++pos])
    {
        if(this_char=='\n')
        {
            is_comment=false;
            token_end=false;
            linenum++;
            switch(last_type)
            {
            case null:
            case lable:
                ++ins_pos;
                flush_token(keyword)
                break;
            case keyword:
            case arg:
                if(is_error)
                    flush_token(error)
                else
                    flush_token(arg)
                    break;
            }
            last_type=null;
            is_error=false;
            continue;
        }
        if(is_comment)
            continue;
        if(this_char==' '||this_char=='\t')
        {
            if(!string_buffer.isEmpty())
                token_end=true;
            continue;
        }

        switch(this_char)
        {
        case ':':
            flush_lable
            continue;
        case ',':
            flush_token(arg)
            continue;
        case '#':
            is_comment=true;
            continue;
        default:
            if(token_end)
            {
                switch(last_type)
                {
                case null:
                    ++ins_pos;
                    flush_token(keyword)
                    break;
                case lable:
                    ++ins_pos;
                    flush_token(keyword)
                    break;
                case arg:
                    flush_token(arg)
                    is_error=true;
                    break;
                }
            }
            string_buffer.append(this_char);
        }
    }
    switch(last_type)
    {
    case null:
    case lable:
        ++ins_pos;
        flush_token(keyword)
        break;
    case keyword:
    case arg:
        if(is_error)
            flush_token(error)
            else
                flush_token(arg)
                break;
    }
    src.setDeleteFlag(true);
    return TokenTable(token_buffer.toArray(),lable_buffer.toArray());
}

void ASMPPCompiler::debug_lexer(const char* file,const char* dest)
{
    ofstream fs(dest,ios::out);
    String<> src(readTextAsArray(file));
    fs<<"Source Code:"<<'\n'<<src.arr_ptr<<'\n'<<"Tokens:"<<std::endl;
    TokenTable table(lex(src));
    Array<Token> tokens=table.Tokens;
    Array<Lable> lables=table.Lables;
    for(int pos=0; pos<tokens.length; ++pos)
        fs<<'<'<<tokens.getElement(pos).value.arr_ptr<<','<<
          (tokens.getElement(pos).type==keyword?"keyword":"")<<
          (tokens.getElement(pos).type==arg?"arg":"")<<
          (tokens.getElement(pos).type==null?"null":"")<<
          (tokens.getElement(pos).type==unknown?"unknown":"")<<
          (tokens.getElement(pos).type==error?"error":"")<<
          '>';
    if(lables.length!=0)
    {
        fs<<'\n'<<"Lables:"<<std::endl;
        for(int pos=0; pos<lables.length; ++pos)
            fs<<'<'<<(lables.getElement(pos).name.getCharArray())<<','<<(lables.getElement(pos).line)<<'>';
    }
    fs.close();
    src.setDeleteFlag(true);
    tokens.setDeleteFlag(true);
    lables.setDeleteFlag(true);
}
//Syntaxer
Array<SingleInstruction> ASMPPCompiler::syntax(TokenTable table)
{
    DataBuffer<SingleInstruction> sigins_buffer(table.Tokens.length);
    String<> this_keyword;
    DataBuffer<String<>> arg_buffer(table.Tokens.length);
    register int tokennum=0;
    Token this_token;
    TokenType last_type=null;
    for(int pos=0; pos<table.Tokens.length; ++pos)
    {
        ++tokennum;
        this_token=table.Tokens[pos];
        switch(this_token.type)  //Check the syntax errors
        {
        case keyword:
            switch(last_type)
            {
            case arg:
                flush_singleins
                break;
            case keyword:
                abort_error_this("Redundant keyword.")
                continue;
            default:
                if(last_type==null)
                        break;
                abort_error_this("The order of instruction is illegal.")
                continue;
            }
            last_type=keyword;
            this_keyword=this_token.value;
            continue;
        case arg:
            switch(last_type)
            {
            case keyword:
            case arg:
                break;
            default:
                if(last_type==null)
                    break;
                abort_error_this("Incomplete statement.")
                continue;
            }
            last_type=arg;
            arg_buffer.append(this_token.value);
            continue;
        case error:
            abort_error_this("Redundant token.")
            continue;
        }
    }
    flush_singleins
    if(has_error)
        exit(0);
    table.Tokens.setDeleteFlag(true);
    table.Lables.setDeleteFlag(true);
    return sigins_buffer.toArray();
}

void ASMPPCompiler::debug_syntaxer(const char* file,const char* dest)
{
    ofstream fs(dest,ios::out);
    String<> src(readTextAsArray(file));
    fs<<"Source Code:"<<'\n'<<src.arr_ptr<<'\n'<<"Instructions:"<<'\n';
    Array<SingleInstruction> sigins=syntax(lex(src));
    for(int pos=0; pos<sigins.length; ++pos)
    {
        fs<<'<'<<sigins.getElement(pos).keyword_bytecode<<':';
        for(int i=0;i<sigins.getElement(pos).arguments.length;++i)
            fs<<(sigins.getElement(pos).arguments.getElement(i))<<(i<sigins.getElement(pos).arguments.length-1?",":"");
        fs<<'>'<<std::endl;
    }
}
//Generator
Array<int> ASMPPCompiler::generate(Array<SingleInstruction> sigins)
{
    DataBuffer<int> bytecode_buffer(sigins.length*16);
    bytecode_buffer<<sigins.length*2+1;
    int data_index=0;
    for(int pos=0; pos<sigins.length; data_index+=sigins.getElement(pos).arguments.length,++pos)
        bytecode_buffer<<sigins.getElement(pos).keyword_bytecode<<data_index;
    for(int pos=0; pos<sigins.length; ++pos)
        for(int i=0;i<sigins.getElement(pos).arguments.length;++i)
            bytecode_buffer<<sigins.getElement(pos).arguments.getElement(i);
    return bytecode_buffer.toArray();
}
//Compiler
void ASMPPCompiler::compile(const char *src_file,const char *dest_file)
{
    Array<int> bytes=generate(syntax(lex(readTextAsArray(src_file))));
    writeIntBytesArray(dest_file,bytes);
    bytes.setDeleteFlag(true);
}

void ASMPPCompiler::compile(const char *src_file)
{
    StringBuffer sb(getLengthOfCharArray(src_file));
    sb<<src_file;
    sb.removeUntil('.');
    sb<<"ape";
    compile(src_file,sb.toString().arr_ptr);
}

void debug_compiler(const char* file,const char* dest)
{

}
