#ifndef _METHOD_
#define _METHOD_
#include "../StrBindtoStru.h"
namespace VideoStreams::rtsp::method
{
    /**
     * @brief  需要实现方法如下
     * rtsp中定义的方法有：OPTIONS, DESCRIBE, SETUP, 
     * TEARDOWN, PLAY, PAUSE, SCALE,
     *  GET_PARAMETER SET_PARAMETER
     */
    Register(Method)
    Str2Struct(OPTIONS,Method)
    Str2Struct(DESCRIBE,Method)
    Str2Struct(TEARDOWN,Method)
    Str2Struct(PLAY,Method)
    Str2Struct(SCALE,Method)
    Str2Struct(GET_PARAMETER,Method)
    Str2Struct(SET_PARAMETER,Method)
    /**
     * @brief 
     * request-header  =      Accept            ; Section 12.1
                |      Accept-Encoding          ; Section 12.2
                |      Accept-Language          ; Section 12.3
                |      Authorization            ; Section 12.5
                |      From                     ; Section 12.20
                |      If-Modified-Since        ; Section 12.23
                |      Range                    ; Section 12.29
                |      Referer                  ; Section 12.30
                |      User-Agent               ; Section 12.41
     */


    Register(ReqHeadField_Key)
    // Str2Struct(Accept-Encoding,ReqHeadField_Key)
    // Str2Struct(Accept-Language,ReqHeadField_Key)
    Str2Struct(Authorization,ReqHeadField_Key)
    Str2Struct(Accept,ReqHeadField_Key)
    Str2Struct(From,ReqHeadField_Key)
    Str2Struct(From,ReqHeadField_Key)
    Str2Struct(Accept,ReqHeadField_Key)
    Str2StructWithIllVerb(Accept_Encoding,ReqHeadField_Key,Accept-Encoding)
    Str2StructWithIllVerb(Accept_Language,ReqHeadField_Key,Accept-Language)
    Str2StructWithIllVerb(User_Agent,ReqHeadField_Key,User-Agent)



    


}






#endif