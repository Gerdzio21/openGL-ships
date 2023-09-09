//
// Created by gerdzio21 on 05.08.2023.
//

#ifndef UNTITLED_SERVER_H
#define UNTITLED_SERVER_H

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "TcpInterface.h"


class Server : public TcpInterface{
public:
    Server();

    ~Server();

    void StartListening(int port);
    void closeConnection();


    void messageSend(const char* message) override;

    int messageReceive(char* buffer, int bufferSize) override;
private:
    WSADATA wsaData;
    SOCKET listenSocket;
    SOCKET clientSocket;
};


#endif //UNTITLED_SERVER_H
