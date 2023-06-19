#include <cstdio>
#include <utility>
#include <iostream>
#include <string>
#include <sys/stat.h>

#include "../Inc/RTSP/rtsp.h"
using namespace std;
using namespace VideoStreams::rtsp;
char BUFF[4096];
#define MK_STR_STR(CHR, CHL) make_pair<string, string>((CHR), (CHL))
#define STR_PAIR(CHL, CHR) make_pair<string, string>((CHL), (CHR))

int main(int argc, char *argv[])
{
    memset((void *)BUFF, 0, 4096);
    if (argc != 2)
    {
        exit(-1);
    }
    int val = atoi(argv[1]);
    if (val == 0)
    {
        FILE *FD = fopen("./TXT/rtsp_rw", "w+");
        rtsp_req req;
        req.InitHead("%s rtsp://211.94.164.227/3.3gp RTSP/1.0", method::str_DESCRIBE_t::ID.c_str());
        req << MK_STR_STR("From", "zhejianghangzhou") << STR_PAIR("User-Agent", "WebRTC");
        req.HDParser();
        int len = req.imp_Serialize(BUFF, 4096);
        int Fwlen = fwrite((void *)BUFF, len, 1, FD);
        if (Fwlen == len)
        {
            std::cout << "write is down" << endl;
            fclose(FD);
            return 0;
        }
    }
    else if (val == 1)
    {

        // rtsp_req req;
        auto FD = fopen("./TXT/rtsp_rw", "r");
        struct stat buff;
        stat("./TXT/rtsp_rw", &buff);
        if (buff.st_size == 0)
            return -1;
        int siz = buff.st_size;
        int len= fread((void*)BUFF,4096,1,FD);
        rtsp_req req(BUFF,len);
        printf("%s",BUFF);
        std::cout<<"\n    BUFF  PRINT DONE   "<<endl;
        
            }

    return 0;
}