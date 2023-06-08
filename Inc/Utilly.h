#pragma once
#ifndef _UTILLY_T_
#define _UTILLY_T_

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

#endif