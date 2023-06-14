#pragma once
#ifndef _UTILLY_T_
#define _UTILLY_T_
#include <utility>
#include <memory.h>
#include <stdlib.h>
#include "./StrBindtoStru.h"
using namespace std;
namespace VideoStreams
{

    struct BinaryBlock
    {
        virtual ~BinaryBlock()=default ;
        // return value is 返回拷贝了多少 siz为需要拷贝多少
        virtual int DeepClone(char *dest, int siz){};
        /* data */
    };

    

}

namespace BinaryOps {
    using MemAddr = std::pair<char*,size_t>;
    class StrSplit {
        private:
        // _begin + _maxlength指向分配的内存空间最大值的后一个
        const char* _Begin;
        const size_t _MaxLength;
        char* _CurrPtr;

//------



        public:
        StrSplit(const char* begin , size_t length ):_Begin(begin),_MaxLength(length){_CurrPtr=const_cast<char*>(begin); }
        StrSplit()=delete;
        ~StrSplit()=default;
        // splite will return the first char addr  of _split_sym;
        MemAddr Splite(const char* _split_sym , size_t len){
            while (_CurrPtr<(_Begin+_MaxLength))
            {
                auto flg = strncmp(_CurrPtr,_split_sym,len);
                if(flg==0){
                    size_t _len = (size_t)(_CurrPtr-_Begin);
                    // return make_pair<char*,size_t>(_CurrPtr,_len );
                    MemAddr ret(_CurrPtr,_len );
                    _CurrPtr+=_len;
                    return ret;
                }else
                {
                    if((_Begin+_MaxLength-_CurrPtr)<len)
                    {
                        return MemAddr(nullptr,0);
                    }
                    _CurrPtr++;
                }
                

            }
        }
        void Release(){
            //TODO:释放内存  手动释放 避免内存
            free((void*)_Begin);
        }
    };

}

#endif