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
    Client() {
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            throw std::runtime_error("Failed to initialize Winsock");
        }
    }

    ~Client() {
        WSACleanup();
    }

    void Connect(const char* ipAddress, int port) {
        clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (clientSocket == INVALID_SOCKET) {
            throw std::runtime_error("Failed to create socket");
        }

        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(port);
        inet_pton(AF_INET, ipAddress, &serverAddr.sin_addr);

        if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            throw std::runtime_error("Failed to connect to server");
        }

        std::cout << "Connected to server" << std::endl;
    }

    void messageSend(const char* message) override{
        send(clientSocket, message, strlen(message), 0);
    }

    int messageReceive(char* buffer, int bufferSize) override {
        return recv(clientSocket, buffer, bufferSize, 0);
    }

private:
    WSADATA wsaData;
    SOCKET clientSocket;
};


#endif //UNTITLED_CLIENT_H
