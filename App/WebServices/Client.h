//
// Created by gerdzio21 on 05.08.2023.
//

#ifndef UNTITLED_CLIENT_H
#define UNTITLED_CLIENT_H

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "TcpInterface.h"

class Client : public TcpInterface {
public:
    Client();

    ~Client();

    void Connect(const char* ipAddress, int port);

    void closeConnection();
    void messageSend(const char* message) override;

    int messageReceive(char* buffer, int bufferSize) override;

private:
    WSADATA wsaData;
    SOCKET clientSocket;
};


#endif //UNTITLED_CLIENT_H
