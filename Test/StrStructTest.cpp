#include "../Inc/StrBindtoStru.h"
#include <iostream>
using namespace std;
Register(myvaf)
Str2Struct(request , myvaf)
Str2Struct(Download , myvaf)
Str2Struct(Manage, myvaf)
Str2Struct(mavel , myvaf)
Str2StructWithIllVerb(hello,myvaf,hell-ooooo)




int main(){
    for(auto & [KeyString ,  ID] : Register_myvaf_t::KV)
    {
     std::cout<<"start to print key is "<<KeyString<<" and ID's Key and addris "\
     <<((Base_myvaf_t*)ID)->GetID()<<endl;  
    }
    std::cout<<"end of all"<<endl;
    std::cout<<"Test Get by str"<<endl;
    std::cout<<"Download is "<<(*Register_myvaf_t::GetByStr("DownLoad")).first<<endl;
    std::cout<<" and addr is "<<hex<<(*Register_myvaf_t::GetByStr("DownLoad")).second<< endl;

    return 0;
}