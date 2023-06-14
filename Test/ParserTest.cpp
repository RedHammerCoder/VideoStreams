#include "../Inc/Parser.h"
#include "string.h"
#include <iostream>
using namespace std;
int main()
{
    string arx("hello:world:ma  preduc:  func:tion");
    Splite<':'>spt ( arx.c_str() , arx.length());
    for(auto & [begin , end] : spt._Content)
    {
        if(begin==end)continue;
        std::cout<<"beg is ["<<begin<<"] endis ["<<end<<']'<<endl;
        std::cout<<arx.substr(begin,end-begin)<<endl;
    }
    return 0;
}