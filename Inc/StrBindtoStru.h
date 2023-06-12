#ifndef _STR2STRU_
#define _STR2STRU_
#include <string>
#include <unordered_map>
using namespace std;
/**
 * @brief Str2Struct is map from string to struct
 * 使用宏 自动化构建 名字中涵盖 str的标准化struct 并且自动注册到register
 * 避免了序列化以及反序列化过程中的过多字符串拷贝 优化程序效率
 * Register_str Str2Struct的注册器
 */

// template<typename T>
// struct KGetID {
//     string& GetID(){return  static_assert<T*>this->ID; }
//     virtual KGetID(){}
//     virtual ~KGetID(){}
// }

#define Register(str)                             \
    struct Register_##str##_t                     \
    {                                             \
        static unordered_map<string, void *> KV;  \
        template <typename T>                     \
        static void Log2Register(T *str_t)        \
        {                                         \
            KV.insert({str_t.ID, (void *)str_t};) \
        }                                         \
        static Register_##str##_t &GetInstance()  \
        {                                         \
            static Register_##str##_t ret;        \
            return ret;                           \
        }                                         \
                                                  \
    private:                                      \
        Register_##str##_t() {}                   \
    } register_##str;

// 在构造函数内部 会自动register到reg中
#define Str2Struct(Str, Reg)                     \
    struct str_##Str##_t                         \
    {                                            \
        \ 
 str_##Str##_t()                                 \
        {                                        \
            (register_##Reg).Log2Register(this); \
        }                                        \
        static inline const string ID = #Str;    \
                                                 \
    } str_##Str;

#define Str2StructWithIllVerb(Tname, Reg, Tvalue) \
    struct str_##Tname##_t                        \
    {                                             \
        str_##Tname##_t()                         \
        {                                         \
            (register_##Reg).Log2Register(this);  \
        }                                         \
        static inline string ID = #Tvalue;        \
    } str_##Tname;

#define ToStrType(str) str_##str##_t
#define ToStrClass(str) str_##str

Register(Kreg);
Str2Struct(helloworld, Kreg);

#endif