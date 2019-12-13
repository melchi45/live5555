#ifndef LIVE5555_RTSPCLIENTBASE_H
#define LIVE5555_RTSPCLIENTBASE_H

#include "common.h"

class RTSPClientBase : public RTSPClient {
private:
    MediaSession *session;
    // 事件循环监控变量，不为零时事件循环退出
    // event loop monitor variable, the event loop exits when it is not zero
    volatile char eventLoopWatchVariable;
    char *rtspURL;
    volatile int acceptedSubSessionCount;
    volatile int preparedSubSessionCount;

    static void onDescribeResponse( RTSPClient *client, int resultCode, char *resultString );

    static void onSetupResponse( RTSPClient *client, int resultCode, char *resultString );

    static void onPlayResponse( RTSPClient *client, int resultCode, char *resultString );

    static void onSubSessionClose( void *clientData );

protected:
    RTSPClientBase( UsageEnvironment &env, const char *rtspURL );

    // 处理RTSP命令DESCRIBE的响应
    // Handle RTSP command response to DESCRIBE
    virtual void onDescribeResponse( int resultCode, const char *sdp );

    // 处理RTSP命令SETUP的响应
    // Handling the response of the RTSP command SETUP
    virtual void onSetupResponse( int resultCode, const char *resultString );

    virtual void onPlayResponse( int resultCode, char *resultString );

    // 是否初始化指定的子会话
    // Whether to initialize the specified child session
    virtual bool acceptSubSession( const char *mediumName, const char *codec )=0;

    virtual MediaSink *createSink( const char *mediumName, const char *codec, MediaSubsession *subSession )=0;

    // 处理子会话关闭事件
    // Handling child session close events
    virtual void onSubSessionClose( MediaSubsession *subsess );

public:
    virtual void start();

    virtual void stop();
};

#endif //LIVE5555_RTSPCLIENTBASE_H
