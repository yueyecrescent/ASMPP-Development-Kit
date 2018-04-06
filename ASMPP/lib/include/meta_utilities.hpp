#ifndef UTILITIES_META
#define UTILITIES_META

namespace utilities{
    namespace meta{
        template<typename ...Types>
        inline int getTypeNumber(){
            return sizeof...(Types);
        }
    }
}
#endif // UTILITIES_META
