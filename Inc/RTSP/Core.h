#ifndef _RTSP_CORE_
#define _RTSP_CORE_
#pragma once
#include "../Parser.h"
#include "../StrBindtoStru.h"
#include "../Utilly.h"
#include <string_view>
#include <memory>
using namespace std;
namespace VideoStreams::rtsp
{
#if 0
    template<typename G>
    class BasicMethod {
        public:
        /// @brief 序列化以及反序列化
        template<typename ... T>
        void Parser(T...args)
        {
            static_cast<G*>(this)->imp_Parser(args...);
        }
        template<typename ... T>
        int Serialize(T...args)
        {
            int ret= static_cast<G*>(this)->imp_Serialize(args...);
            return ret;
        }
    };
#endif
    struct ReqHeaderFields
    {
        using RequestHeaderFieldsMap = unordered_map<string, string>;
        using RHF_KeyVal = pair<string, string>;
        // int en_serial(RequestHeaderFieldsMap,char* buff ,size_t buf_sz);
    };


      struct MemaryBlock : public BinaryBlock
    {
        void *begin;
        size_t Length;
        MemaryBlock(void *_beg, size_t Len) : begin(_beg), Length(Len) {}
        int DeepClone(char *dest, int siz) override
        {
            memcpy(dest, begin, Length);
            return min((int)Length, siz);
        }
        ~MemaryBlock() {}
    };



    template <typename G>
    class BasicMethod
    {
        using IS_ENABLE_BASIC_BLOCK = TRUE_T;
    public:
        // virtual void HDParser()=0;
        virtual void HDParser(string_view str_v) = 0;
        virtual G &operator<<(ReqHeaderFields::RHF_KeyVal Param) = 0;
        virtual void add_header_pair(string key, string val) = 0; // 只使用这个 避免头文件过于重复
        virtual void LoadContent(weak_ptr<MemaryBlock> T) = 0;
    };

}

#endif