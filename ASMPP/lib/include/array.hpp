#ifndef UTILITIES_ARRAY
#define UTILITIES_ARRAY

#define GET_ARRAY_LENGTH(ARRAY,LENVARNAME) int LENVARNAME=sizeof(ARRAY)/sizeof(ARRAY[0]);

#include <malloc.h>
#include <iostream>
#include <fstream>

namespace utilities
{
    namespace array
    {
        template<typename E,bool delete_array_when_destruct=false>
        struct Array
        {
        private:
            bool delete_flag=delete_array_when_destruct;
        public:
            int length;
            E *arr_ptr;
            Array()
            {
                this->length=0;
                this->arr_ptr=nullptr;
            }
            Array(int number)
            {
                this->length=number;
                this->arr_ptr=new E[number];
            }
            Array(const Array<E> &arr)
            {
                this->arr_ptr=arr.arr_ptr;
                this->length=arr.length;
            }
            Array(Array<E> &&arr)
            {
                this->arr_ptr=arr.arr_ptr;
                this->length=arr.length;
                arr.setDeleteFlag(false);
            }
            Array(E *arr,int len)
            {
                this->arr_ptr=arr;
                this->length=len;
            }
            template<int L>
            Array(E (&arr)[L])
            {
                this->arr_ptr=arr;
                this->length=sizeof(arr)/sizeof(arr[0]);
            }
            ~Array()
            {
                if(delete_flag)
                    deleteArray();
            }
            void deleteArray()
            {
                delete []arr_ptr;
                length=0;
            }
            Array<E> & copyAs(Array<E> &arr)
            {
                if(delete_flag)
                    deleteArray();
                arr_ptr=new E[arr.length];
                length=arr.length;
                for(int pos=0; pos<arr.length; ++pos)
                    *(arr_ptr+pos)=*(arr.arr_ptr+pos);
                return *this;
            }
            Array<E> & copyAs(Array<E> &&arr)
            {
                if(delete_flag)
                    deleteArray();
                arr_ptr=arr.arr_ptr;
                length=arr.length;
                arr.setDeleteFlag(false);
                return *this;
            }
            void setDeleteFlag(bool delete_array_when_destruct_)
            {
                delete_flag=delete_array_when_destruct_;
            }
            E &getElement(int index)
            {
                return *(arr_ptr+index);
            }
            void setElement(int index,E &e)
            {
                *(arr_ptr+index)=e;
            }
            void setElement(int index,E &&e)
            {
                *(arr_ptr+index)=e;
            }
            E & operator [](int index)
            {
                return *(arr_ptr+index);
            }
            Array<E> & operator + (Array<E> &arr)
            {
                Array<E> *res=new Array<E>(this->length+arr.length);
                for(int pos=0; pos<this->length; ++pos)
                    res->getElement(pos)=*this[pos];
                for(int pos=0; pos<arr.length; ++pos)
                    res->getElement(this->length+pos)=arr[pos];
                return *res;
            }
            Array<E> & operator + (Array<E> &&arr)
            {
                Array<E> *res=new Array<E>(this->length+arr.length);
                for(int pos=0; pos<this->length; ++pos)
                    res->getElement(pos)=*this[pos];
                for(int pos=0; pos<arr.length; ++pos)
                    res->getElement(this->length+pos)=arr[pos];
                arr.setDeleteFlag(true);
                return *res;
            }
            Array<E> & operator = (Array<E> &arr)
            {
                this->arr_ptr=arr.arr_ptr;
                this->length=arr.length;
                return *this;
            }
            Array<E> & operator = (Array<E> &&arr)
            {
                this->arr_ptr=arr.arr_ptr;
                this->length=arr.length;
                arr.setDeleteFlag(false);
                return *this;
            }
            int numberOf(E &element)
            {
                int num=0;
                for(int pos=0; pos<length; ++pos)
                {
                    if(arr_ptr[pos]==element)
                        ++num;
                }
                return num;
            }
            int numberOf(E &&element)
            {
                int num=0;
                for(int pos=0; pos<length; ++pos)
                {
                    if(arr_ptr[pos]==element)
                        ++num;
                }
                return num;
            }
            bool contains(E &e)
            {
                for(int pos=0; pos<length; ++pos)
                    if(this->getElement(pos)==e)
                        return true;
                return false;
            }
            bool contains(E &&e)
            {
                for(int pos=0; pos<length; ++pos)
                    if(this->getElement(pos)==e)
                        return true;
                return false;
            }
            Array<E> subArray(int start_pos,int len)
            {
                Array<E> res(length);
                for(int pos=0; pos<len; ++pos)
                    res[pos]=this->getElement(start_pos+pos);
                return res;
            }
        };
        template<typename E,bool delete_array_when_destruct=false>
        using Array=struct Array<E,delete_array_when_destruct>;
        /*
        template<typename E>
        class Array{
        private:
            E *elements;
            int array_length;
        public:
            Array(int length){
                this->array_length=length;
                elements=(E *)malloc(length*sizeof(E)+sizeof(E *));
            }
            ~Array(){
                free(elements);
            }
            E operator [](int index){
                return *(elements+index);
            }
            E get(int index){
                return *(elements+index);
            }
            void set(int index,E element){
                *(elements+index)=element;
            }
            int length(void){
                return this->array_length;
            }
        };

        template<typename E>
        class ArrayList{
        private:
            E [][]elementsList;
            int array_length;
            int list_length=0;
            int elements_number=0;

            void extendElementsList(void){
                ++list_length;
                E [][]tmp=elementsList;
                elementsList=new E[list_length][array_length];
                for(int pos=0;pos<list_length;++pos)elementsList[array_index][pos]=0;
            }

            void extendElementsArray(int array_index){
                elementsList[array_index]=new E[array_length];
                for(int pos=0;pos<array_length;++pos)elementsList[array_index][pos]=0;
            }
        public:
            ArrayList(int length){
                this->array_length=length;
                extendElementsList();
            }

            int length(void){
                return list_length*array_length;
            }

            void add(E element){
                ++elements_number;
            }
        };
        */

        template<typename E>
        class DataBuffer
        {
        protected:
            int buffer_capcity;
            int position=-1;
            E *head;
        public:
            DataBuffer(int capcity)
            {
                this->buffer_capcity=capcity;
                head=(E *)malloc(capcity*sizeof(E));
            }
            ~DataBuffer()
            {
                free(head);
            }
            DataBuffer(DataBuffer<E> &&buffer)
            {
                this->buffer_capcity=buffer.buffer_capcity;
                this->head=buffer.head;
                buffer.head=nullptr;
            }
            DataBuffer<E> & append(E &value)
            {
                *(head+(++position))=value;
                return *this;
            }
            DataBuffer<E> & append(E &&value)
            {
                *(head+(++position))=value;
                return *this;
            }
            DataBuffer<E> & append(Array<E> &values)
            {
                for(int pos=0; pos<values.length; ++pos)
                    *(head+(++position))=values[pos];
                return *this;
            }
            DataBuffer<E> & append(Array<E> &&values)
            {
                for(int pos=0; pos<values.length; ++pos)
                    *(head+(++position))=values[pos];
                return *this;
            }
            DataBuffer<E> & operator <<(E &value)
            {
                *(head+(++position))=value;
                return *this;
            }
            DataBuffer<E> & operator <<(E &&value)
            {
                *(head+(++position))=value;
                return *this;
            }
            DataBuffer<E> & operator <<(Array<E> &values)
            {
                for(int pos=0; pos<values.length; ++pos)
                    *(head+(++position))=values[pos];
                return *this;
            }
            DataBuffer<E> & operator <<(Array<E> &&values)
            {
                for(int pos=0; pos<values.length; ++pos)
                    *(head+(++position))=values[pos];
                return *this;
            }
            DataBuffer<E> & operator <<(std::basic_istream<char> &vstream)
            {
                vstream.seekg(0,std::ios::end);
                int size=vstream.tellg();
                vstream.seekg(0,std::ios::beg);
                for(; size>-1; --size)
                    *(head+(++position))=vstream.get();
                return *this;
            }
            DataBuffer<E> & operator <<(std::basic_istream<char> &&vstream)
            {
                vstream.seekg(0,std::ios::end);
                int size=vstream.tellg();
                vstream.seekg(0,std::ios::beg);
                for(int pos=0; pos<size; ++pos)
                    *(head+(++position))=vstream.get();
                return *this;
            }
            inline E * toArrayPointer()
            {
                int length=getLength();
                E *arr=new E[length];
                for(register int pos=0; pos<length; ++pos)
                    arr[pos]=*(head+pos);
                return arr;
            }
            inline Array<E> toArray()
            {
                int length=getLength();
                E *arr=new E[length];
                for(register int pos=0; pos<length; ++pos)
                    arr[pos]=*(head+pos);
                return Array<E>(arr,length);
            }
            void clear()
            {
                position=-1;
            }
            E & getElement(int index)
            {
                return *(head+index);
            }
            E & operator [] (int index)
            {
                return *(head+index);
            }
            void deleteData(int number)
            {
                position-=number;
                if(position<-1)
                    position=-1;
            }
            void deleteData()
            {
                deleteData(1);
            }
            ///The return value of remove() is dangerous because it's the reference of the element which was removed just now.\
            it might be covered with a new value after a while.So just use it to check the last element of this buffer.
            E & remove()
            {
                return *(head+1+--position);
            }
            void removeUntil(E &e)
            {
                if(*(head+position)==e)return;
                while(position>-1&&*(head+--position)!=e);
            }
            void removeUntil(E &&e)
            {
                if(*(head+position)==e)return;
                while(position>-1&&*(head+--position)!=e);
            }
            ///This function is dangerous,too.
            E & removeBack()
            {
                return *(head+++position);
            }
            E & lastElement()
            {
                return *(head+position);
            }
            inline int getCapcity()
            {
                return this->buffer_capcity;
            }
            inline int getPosition()
            {
                return this->position;
            }
            inline int getLength()
            {
                return position+1;
            }
            inline bool isEmpty()
            {
                return position==-1;
            }
            inline E * getArrayPointer()
            {
                return head;
            }
            DataBuffer<E> & operator = (DataBuffer<E> &&buffer)
            {
                this->buffer_capcity=buffer.buffer_capcity;
                this->head=buffer.head;
                buffer.head=nullptr;
                return *this;
            }
        };

        template<typename E>
        int liner_search(Array<E> arr,E dest)
        {
            for(int pos=0; pos<arr.length; ++pos)
            {
                if(arr[pos]==dest)
                    return pos;
            }
            return -1;
        }
    }
}

#endif // UTILITIES_ARRAY
