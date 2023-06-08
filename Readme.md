rtsp  实时流传输协议
rtp / rtcp 实时传输协议  互联网上传递音频和视频的标准数据包格式
RTSP协议：负责服务器与客户端之间的请求与响应  传递命令
RTP协议：负责传输媒体数据 传递数据 以UDP方式
RTCP协议：在RTP传输过程中提供传输信息 传递数据包 以TCP方式

RTP 流媒体数据进行封包并实现媒体流的实时传输
RTP默认端口号5004，所以RTCP端口号默认为5005 RTCP 使用RTP的下一个端口
RTSP 基本端口为554

RTP封装： 多媒体数据块  压缩编码后 封装为 RTP报文 然后使用UDP 发送数据报文

TSP传输的一般是TS、MP4格式的流，其传输一般需要2~3个通道，命令和数据通道分离。使用RTSP协议传输流媒体数据需要有专门的媒体播放器和媒体服务器，也就是需要支持RTSP协议的客户端和服务器。

RTSP负责定义具体的控制信息、操作方法、状态码，以及描述与RTP之间的交互操作

## 基础流程
一次基本的RTSP操作过程:
首先，客户端连接到流服务器并发送一个RTSP描述命令（DESCRIBE）。
流服务器通过一个SDP描述来进行反馈，反馈信息包括流数量、媒体类型等信息。
客户端再分析该SDP描述，并为会话中的每一个流发送一个RTSP建立命令(SETUP)，RTSP建立命令告诉服务器客户端用于接收媒体数据的端口。流媒体连接建立完成后，
客户端发送一个播放命令(PLAY)，服务器就开始在UDP上传送媒体流（RTP包）到客户端。在播放过程中客户端还可以向服务器发送命令来控制快进、快退和暂停等。
最后，客户端可发送一个终止命令(TERADOWN)来结束流媒体会话

##
RTSP 为每个对话保留状态

## RTSP 报文结构：
line 0 : 方法‘ ’URL‘ ’版本\R\F
line 1-n : 首部字段名‘:’值\R\F
\R\F
实体主体

## RTSP请求报文方法：
exp: DESCRIBE rtsp://211.94.164.227/3.3gp RTSP/1.0

### Request Header Fields
在消息头中除了第一行的内容外，还有一些需求提供附加信息。
- CSeq : 请求报文和它的响应报文的序列号一致  重传的报文和原始报文的CSeq一致
- User-Agent 允许向服务器传送客户端的自身信息   
Request-header      =   Accept
              |   Accept-Encoding
              |   Accept-Language
              |   Authorization
              |   From
              |   If-Modified-Since
              |   Range
              |   Referer
              |   User-Agent   



## RTSP 响应报文
line 0 : Status-Line = RTSP-Version 空格Status-Code 空格Reason-Phrase CRLF
### 状态码 
1XX: Informational – 请求被接收到，继续处理
2XX: Success – 请求被成功的接收，解析并接受
3XX: Redirection – 为完成请求需要更多的操作
4XX: Client Error – 请求消息中包含语法错误或是不能够被有效执行
5XX: Server Error – 服务器响应失败，无法处理正确的有效的请求消息
### Response Header Fields   
Response-header    =   Location
              |   Proxy-Authenticate
              |   Public
              |   Retry-After
              |   Server
              |   Vary
              |   WWW-Authenticate   
### RTSP的主要方法
Options : 获取服务器主要方法
Describe ： 得到会话描述信息
setup ： 客户端建立会话 并且确立传输模式
Teardown 客户端 发起关闭会话请求
play 客户端发起播放请求
