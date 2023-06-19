#include "../Inc/RTSP/rtsp.h"
#include <memory.h>
#include <iostream>

const int bufsiz=40000;
char BUFFER[bufsiz];
using namespace std;
using namespace VideoStreams::rtsp;

int main(int argc, char* argv[])
{
    std::cout<<"stage0"<<endl;
    memset(BUFFER,0,bufsiz);
    std::cout<<"stage1"<<endl;
    rtsp_req rtspreq;
    rtspreq.InitHead("%s rtsp://211.94.164.227/3.3gp RTSP/1.0",method::struct_OPTIONS.ID.c_str());
    std::cout<<"stageX"<<endl;
    rtspreq.HDParser();
    std::cout<<"stageX2"<<endl;
    rtspreq.add_header_pair("From","zhejiangquzhou");
    rtspreq.add_header_pair("User-Agent","WebRTC");
    rtspreq<< make_pair<string,string>("Accept-Encoding","UTF-8");
    rtspreq.add_header_pair("Authorization","%s  is  %d","helloword",24);
    std::cout<<"stage"<<endl;
    int lens= rtspreq.imp_Serialize(BUFFER,bufsiz);
    std::cout<<string(BUFFER,lens)<<endl;
    rtsp_req temp(BUFFER,lens);
    
    return 0;
}