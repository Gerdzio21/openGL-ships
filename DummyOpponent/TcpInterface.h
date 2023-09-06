//
// Created by gerdzio21 on 05.08.2023.
//

#ifndef UNTITLED_TCPINTERFACE_H
#define UNTITLED_TCPINTERFACE_H


class TcpInterface {
public:
    virtual void messageSend(const char* message) = 0;
    virtual int messageReceive(char* buffer, int bufferSize) = 0;
};


#endif //UNTITLED_TCPINTERFACE_H
