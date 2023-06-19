#pragma once
#include <string>
#include <iostream>
#include <stddef.h>
#include <utility>
#include <deque>
#include <memory>
#include <array>
#include <assert.h>
#include <string.h>
#include <unordered_map>
#include <math.h>
#include <string_view>
#include "./Core.h"
#include "../Utilly.h"
#include "../StrBindtoStru.h"
#include "./Method.h"
#include "../Parser.h"
using namespace std;
using namespace VideoStreams::rtsp::method;
using namespace BinaryOps;

namespace VideoStreams::rtsp
{
// void MemCover(char** Dest , char *src, int src_len ,siz)
#define CRLF          \
    *(BUFF++) = '\r'; \
    *(BUFF++) = '\n';

    const int Buffsize = 256;
    #if 0
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

    #endif
    // array<char,2> CRLF{'\r','\n'};
    size_t Port = 554;
    struct RTSP_VERSION
    {
        string V1 = "RTSP/1.0";
    };

    // Checker is used to check the element of req or resp;
    class Checker
    {
    public:
        virtual bool Check(){};
        virtual ~Checker() {}
    };
#if 0
    struct ReqHeaderFields
    {
        using RequestHeaderFieldsMap = unordered_map<string, string>;
        using RHF_KeyVal = pair<string,string>;
        // int en_serial(RequestHeaderFieldsMap,char* buff ,size_t buf_sz);
    };
#endif

    // template T is used for
    //  template<typename T>
    //  concept DEEPCLONE = requires (T t){t.DeepClone()};

    // template <typename T>
    class rtsp_req : private Checker ,public BasicMethod<rtsp_req>
    {
        using CONTAIN = MemaryBlock;
    private:

        Base_Method_t *MethodOfRequest;
        int MaxSiz;          // 序列化时最大空间
        weak_ptr< MemaryBlock> Content; // 需要直接拷贝到目标内存
        ReqHeaderFields::RequestHeaderFieldsMap RHMap;
        unique_ptr<string> ReqHeader;
        // 用于保存head除了方法意外的字符串
        unique_ptr<string> ReqHeaderBody;
        string _ipaddr;
        string _Version;
        Base_Method_t *Method;

        //------Method
        bool Check() override { return true; }

    public:
        rtsp_req& operator<<(ReqHeaderFields::RHF_KeyVal  Param) override
        {
            auto && [key , val]=Param;
            this->add_header_pair(  std::move(key),std::move( val));
            return *this;
        }


        void HDParser(string_view str_v)
        {

            size_t pos = str_v.find(' ', 0);
            MethodOfRequest = (method::Base_Method_t *)(*Register_Method_t::GetByStr(str_v.substr(0, pos).data())).second;
        }
        void HDParser()
        {
            auto Uptr = this->ReqHeader.get();
            size_t siz = Uptr->find(' ', 0);
            MethodOfRequest = (method::Base_Method_t *)(*Register_Method_t::GetByStr(Uptr->substr(0, siz).data())).second;
            std::cout << "HDParser  " << MethodOfRequest->GetID() << endl;
        }
        ~rtsp_req() {}
        // 将所有数据转变成MemBlock
        // 返回值指定写入长度
        int imp_Serialize(char *Buff, int Buffsiz)
        {
            if (Check() != true)
                throw exception();
            else
            {
                char *BUFF = Buff; // 避免修改Buff
                memcpy((void *)BUFF, (const void *)this->ReqHeader.get()->c_str(), ReqHeader.get()->length());
                BUFF += ReqHeader.get()->length();
                CRLF;
                for (auto &[key, tail] : this->RHMap)
                {
                    memcpy(BUFF, key.c_str(), key.length());
                    BUFF += key.length();
                    *(BUFF++) = ':';
                    memcpy(BUFF, tail.c_str(), tail.length());
                    BUFF += tail.length();
                    CRLF
                }
                CRLF
                    // TODO:将序列化的数据memcpy到空间中
                    if (Content.expired() == false)
                {
                    // todo : copy to dest
                    auto srcp = Content.lock().get();
                    int RL = srcp->DeepClone(BUFF, Buffsiz - (size_t)(BUFF - Buff));
                }
                // return make_unique<MemaryBlock>((void*)Buff,(int)(BUFF-Buff));
                return (int)(BUFF - Buff);
            }
        }
        void imp_Parser(const char *Buffbase, size_t len)
        { // TODO: 将Parser转变成string_view
            string_view _BackGround(Buffbase, len);
            vector<string_view> ParamList;
            size_t div_ptr = 0;
            do
            {
                size_t tail = _BackGround.find("\r\n", div_ptr);
                if (tail == _BackGround.npos)
                    break;
                ParamList.push_back(_BackGround.substr(div_ptr, tail - div_ptr));
                div_ptr = tail + 2;
                // std::cout<<"tail is "<<tail<<" divptr  "<<div_ptr<<endl;
            } while (div_ptr < Buffsize and div_ptr - 2 != _BackGround.npos);
#if 1
            for (auto str : ParamList)
            {
                std::cout << "line  [" << str << ']' << " and size is " << str.size() << endl;
            }

#endif
            for (int i = 0; i < ParamList.size(); i++)
            {
                if (i == 0)
                {
                    Splite<' '> tmp(ParamList[i].data(), ParamList[i].size());
                    assert(tmp._Content.size() == 3);
                    const int bias = tmp._Content[0].second - tmp._Content[0].first;
                    Method = (Base_Method_t *)Register_Method_t::GetByStr(
                                 string(ParamList[0].substr(tmp._Content[0].first, bias)))
                                 ->second;
                    _ipaddr = std::move(ParamList[0].substr(tmp._Content[1].first, tmp._Content[1].second - tmp._Content[1].first));
                    _Version = std::move(ParamList[0].substr(tmp._Content[2].first, tmp._Content[2].second - tmp._Content[2].first));
                }
                else // 处理request head
                {
                    auto &ref = ParamList[i];
                    Splite<':'> tmp(ref.data(), ref.size());
                    std::cout << "splite by : [" << tmp._Content.size() << endl;
                    if (tmp._Content.size() == 2)
                    {
                        // std::cout << "splite by : [" << tmp._Content.size() << endl;
                        auto &[key_beg, key_end] = tmp._Content[0];
                        auto &[arg_beg, arg_end] = tmp._Content[1];

                        auto keyref = Register_ReqHeadField_Key_t::GetByStr(string(ref.substr(key_beg, key_end - key_beg)));
                        // auto& keyref=Register_ReqHeadField_Key_t::GetByStr( string(ref.substr(arg_beg,arg_end-arg_beg) )  );
                        RHMap.insert({keyref->first, std::move(string(ref.substr(arg_beg, arg_end - arg_beg)))});
                    }
                }
            }
#if 1
            for (auto &[key, value] : RHMap)
            {
                std::cout << "Req head [" << key << "]   arg val [" << value << endl;
            }
#endif

            // return *this;
        }

        void setsiz(int siz = 1480) { MaxSiz = siz; }
        rtsp_req(unique_ptr<string> &&header)
        {
            ReqHeader = std::move(header);
        }
        rtsp_req(int siz = 0) : MaxSiz(siz){};
        rtsp_req(const char *chr, size_t len)
        {
            imp_Parser(chr, len);
        }
        template <typename... C>
        void add_header_pair(string key, C... args)
        {
            char buf[Buffsize];
            memset(buf, 0, Buffsize);
            int Length = sprintf(buf, args...);
            string strl(buf, Length);
#if defined _Debug
            cout << strl << endl;
#endif
            this->RHMap.insert({key, strl});
        }
        void add_header_pair(string key, string ss)
        {
            RHMap.insert({key, ss});
        }
        template <typename... C>
        void InitHead(C... args)
        {
            char buf[Buffsize];
            memset(buf, 0, Buffsize);
            int Length = sprintf(buf, args...);
            string strl(buf, Length);
            ReqHeader = make_unique<string>(strl);
        }
        // rtsp_req& operator<<(pair<string,string){
        //     add_header_pair(std::forword<string>,)
        // }
        // 将负载装入当前东西中
        void LoadContent(weak_ptr<rtsp_req::CONTAIN> Load)
        {
            Content = Load; // 多个实体共享文件共享
        }
    };
    // template class rtsp_req<MemaryBlock>; // 初始
    class rtsp_resp:public BasicMethod<rtsp_resp>{
        public:
        // void HDParser()override{}
        rtsp_resp(char* base_addr , size_t length){}
        rtsp_resp(rtsp_resp&  _src){}
        void HDParser(string_view str_v)override {}
        rtsp_resp& operator<<(ReqHeaderFields::RHF_KeyVal Param)override
        {

        }
        void add_header_pair(string key, string val)override
        {

        }
        virtual void LoadContent(weak_ptr<MemaryBlock> T)override {}


    } ;










}