#ifndef UTILITIES_IO
#define UTILITIES_IO

#define GET_FILE_LENGTH(IOSTREAM,LENVARNAME) IOSTREAM.seekg(0,ios::end);\
        int LENVARNAME=IOSTREAM.tellg();\
        IOSTREAM.seekg(0,ios::beg);

#include <fstream>
#include <malloc.h>
#include "array.hpp"
#include "string_utilities.hpp"

using namespace std;
using namespace utilities::array;
using namespace utilities::string;

namespace utilities{
    namespace io{
        String<false> readTextAsArray(const char* filename){
            ifstream file(filename,ios::in);
            String<> text;
            if(file.is_open()){
                GET_FILE_LENGTH(file,length)
                StringBuffer buffer(length);
                for(char ch;!file.eof();buffer<<ch)file.get(ch);
                file.close();
                buffer.deleteData();
                text=buffer.toString();
            }
            return text;
        }

        void writeCharsArray(const char* filename,Array<char> text){
            ofstream file(filename,ios::out);
            for(int pos=0;pos<text.length;++pos)file<<text[pos];
            file.close();
        }

        void writeBytes(const char* filename,void *data,long int length){
            ofstream file(filename,ios::out|ios::binary);
            file.write((const char*)data,length);
            file.close();
        }

        void writeIntBytesArray(const char* filename,Array<int> bytes){
            ofstream file(filename,ios::out|ios::binary);
            file.write((char*)bytes.arr_ptr,bytes.length*sizeof(int));
            file.close();
        }

        char * readBytes(const char* filename){
            ifstream file(filename,ios::in|ios::binary);
            char *bytes=nullptr;
            if(file.is_open()){
                GET_FILE_LENGTH(file,length)
                bytes=new char[length];
                file.read(bytes,length);
                file.close();
            }
            return bytes;
        }

        Array<char> readBytesAsArray(const char* filename){
            ifstream file(filename,ios::in|ios::binary);
            char *bytes=nullptr;
            Array<char> bytesarray;
            if(file.is_open()){
                GET_FILE_LENGTH(file,length)
                bytes=new char[length];
                file.read(bytes,length);
                file.close();
                Array<char>(bytes,length);
            }
            return bytesarray;
        }
    }
}

#endif // UTILITIES_IO
