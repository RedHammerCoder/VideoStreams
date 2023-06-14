#ifndef  _PARSER_
#define  _PARSER_
#include <vector>
#include <utility>
#pragma once

// shrink is used to remove the ' 'space
template<bool>
class shrink{
    public : 
    shrink(){}
};

using Scope = std::pair<size_t,size_t>;

template<char divd , char endc='\0' ,typename Container=std::vector<Scope> >
class Splite
{
    const char* _beg=nullptr;
    size_t _len;
public: //data
Container _Content;
public: //Func
    Splite(){};
    Splite(const char* chr ,size_t len):_beg(chr),_len(len)
    {
        Run();
    }
    void Run(){
        size_t ptr=0;
        size_t Last=0;
        while(ptr<_len)
        {
            if(_beg[ptr] != endc)
            {
                if(_beg[ptr] == divd)
                {
                    _Content.push_back({Last,ptr});
                    Last=ptr;
                    Last++;
                }
            }else{
                if(Last!=ptr){_Content.push_back({Last,ptr}); }
                return ;
            }
            ptr++;
        }
            if(Last!=ptr){_Content.push_back({Last,ptr}); }

    }
    void Run(const char * beg, size_t len)
    {
        _beg=beg;
        _len=len;
        Run();
    }
    
    virtual ~Splite(){}
};






















#endif