#pragma once
#include <string>
#include <iostream>
#include <stddef.h>
#include <utility>
#include <deque>
#include <memory>
#include <array>
#include <string.h>
#include <unordered_map>
#include <math.h>
#include <string_view>
#include "../Utilly.h"
#include "../StrBindtoStru.h"
#include "./Method.h"
using namespace std;
using namespace VideoStreams::rtsp::method;
using namespace BinaryOps;

namespace VideoStreams::rtsp
{
    // void MemCover(char** Dest , char *src, int src_len ,siz)
    #define CRLF        *(BUFF++)='\r';*(BUFF++)='\n';

    const int Buffsize=256;
    struct MemaryBlock :public BinaryBlock {
        void* begin;
        size_t Length;
        MemaryBlock(void* _beg,size_t Len):begin(_beg),Length(Len){}
        int DeepClone(char* dest,int siz)override
        {
            memcpy(dest,begin,Length);
            return min((int)Length,siz);
        }
        ~MemaryBlock(){}
    };
    // array<char,2> CRLF{'\r','\n'}; 
    size_t Port = 554 ;
    struct RTSP_VERSION{
        string V1 = "RTSP/1.0";
    };
  
    // Checker is used to check the element of req or resp;
    class Checker{
        public:
        virtual bool Check(){};
        virtual ~Checker(){}
    };
    
    struct ReqHeaderFields {
        using  RequestHeaderFieldsMap =unordered_map<string,string>;
        // int en_serial(RequestHeaderFieldsMap,char* buff ,size_t buf_sz);
    };

//template T is used for
// template<typename T>
// concept DEEPCLONE = requires (T t){t.DeepClone()};


template<typename T>
    class rtsp_req: private Checker {
        private:
        Base_Method_t* MethodOfRequest;
        int MaxSiz;//序列化时最大空间
        weak_ptr<T> Content;//需要直接拷贝到目标内存
ReqHeaderFields::RequestHeaderFieldsMap RHMap;
        unique_ptr<string> ReqHeader;
        //用于保存head除了方法意外的字符串
        unique_ptr<string> ReqHeaderBody;



//------Method
        bool Check()override{
            return true;
        }
        
        
        public:
        void HDParser(string_view str_v )
        {
            size_t pos=str_v.find(' ',0);
            MethodOfRequest =(method::Base_Method_t*)(*Register_Method_t::GetByStr(str_v.substr(0,pos).data())).second ;
    
        }
        void HDParser()
        {
            auto & Uptr = this->ReqHeader;
            size_t siz=(Uptr.get())->find('\r\n',0);
            MethodOfRequest =(method::Base_Method_t*)(*Register_Method_t::GetByStr(Uptr.substr(0,pos).data())).second ;

        }

        ~rtsp_req(){}

        //将所有数据转变成MemBlock
        //返回值指定写入长度
        int serialize(char* Buff , int Buffsiz){
            if(Check()!=true)throw exception();
            else{
                
                //Done: 检查空间或者建立空间
                // if(nullptr==Buff && Buffsiz==0)
                // {
                //     Buff=(char*)malloc(MaxSiz);//单位是字节
                //     Buffsiz=MaxSiz;
                //     memset(Buff,-1,Buffsiz);//全部初始化为-1 方便后续检验错误
                // }
                char* BUFF=Buff;//避免修改Buff

                memcpy((void*)BUFF,(const void*)this->ReqHeader.get()->c_str(),ReqHeader.get()->length());
                BUFF+=ReqHeader.get()->length();
                CRLF;
                for(auto &[ key , tail ]: this->RHMap)
                {
                    memcpy(BUFF,key.c_str(),key.length() );
                    BUFF+=key.length();
                    *(BUFF++)=':';
                    memcpy(BUFF,tail.c_str(),tail.length() );
                    BUFF+=tail.length();
                    CRLF

                }
                CRLF

                //TODO:将序列化的数据memcpy到空间中
                if(Content.expired()==false){
                    //todo : copy to dest
                    auto srcp=Content.lock().get();
                    int RL =srcp->DeepClone(BUFF, Buffsiz-(size_t)(BUFF-Buff));
                }
                // return make_unique<MemaryBlock>((void*)Buff,(int)(BUFF-Buff));
                return (int)(BUFF-Buff);
            }
        }
        rtsp_req& Parser(const char* Buffbase , size_t len)
        {//TODO: 将Parser转变成可查询
        string_view Str_BackGround(Buffbase , len);
        size_t CRLF_line_beg = Str_BackGround.find("\r\n") ;
            return *this;
        }





        
        void setsiz(int siz=1480){MaxSiz=siz;}
        rtsp_req(unique_ptr<string>&& header)
        {
            ReqHeader=std::move(header);
        }
        rtsp_req(int siz=0):MaxSiz(siz){};
        template<typename ...C>
        void addReqHeaderFields(string key,C...args)
        {
            char buf[Buffsize];
            memset(buf,0,Buffsize);
            int Length = sprintf(buf,args...);
            string strl(buf,Length);
#if defined _Debug
            cout<<strl<<endl;
#endif
            this->RHMap.insert({key,strl});
            
        }
        void addReqHeaderFields(string key ,string ss)
        {
            RHMap.insert({key,ss});

        }
        template< typename ...C>
        void InitHead(C ...args){
            char buf[Buffsize];
            memset(buf,0,Buffsize);
            int Length = sprintf(buf,args...);
            string strl(buf,Length);
            ReqHeader=make_unique<string>(strl);
        }
        // rtsp_req& operator<<(pair<string,string){
        //     addReqHeaderFields(std::forword<string>,)
        // }
        //将负载装入当前东西中
        void LoadContent(weak_ptr<T> Load){
            Content=Load;//多个实体共享文件共享
        }
    };
template class rtsp_req<MemaryBlock>;// 初始化 

}