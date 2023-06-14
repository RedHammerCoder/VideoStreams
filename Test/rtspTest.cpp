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
    rtsp_req<MemaryBlock> rtspreq;
    rtspreq.InitHead("%s rtsp://211.94.164.227/3.3gp RTSP/1.0",method::struct_OPTIONS.ID.c_str());
    std::cout<<"stageX"<<endl;
    rtspreq.HDParser();
    std::cout<<"stageX2"<<endl;
    rtspreq.addReqHeaderFields("From","zhejiangquzhou");
    rtspreq.addReqHeaderFields("User-Agent","WebRTC");
    rtspreq<< make_pair<string,string>("Accept-Encoding","UTF-8");
    rtspreq.addReqHeaderFields("Authorization","%s  is  %d","helloword",24);
    std::cout<<"stage"<<endl;
    int lens= rtspreq.serialize(BUFFER,bufsiz);
    std::cout<<string(BUFFER,lens)<<endl;
    rtsp_req<MemaryBlock> temp(BUFFER,lens);
    
    return 0;
}