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
    Server() {
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            throw std::runtime_error("Failed to initialize Winsock");
        }
    }

    ~Server() {
        WSACleanup();
    }

    void StartListening(int port) {
        listenSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (listenSocket == INVALID_SOCKET) {
            throw std::runtime_error("Failed to create socket");
        }

        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_port = htons(port);

        if (bind(listenSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            throw std::runtime_error("Failed to bind socket");
        }

        if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
            throw std::runtime_error("Listen failed");
        }
        char localIP[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(serverAddr.sin_addr), localIP, INET_ADDRSTRLEN);

        std::cout << "Server listening on IP "<< localIP << ":" << port << std::endl;

        sockaddr_in clientAddr;
        int clientAddrSize = sizeof(clientAddr);
        clientSocket = accept(listenSocket, (sockaddr*)&clientAddr, &clientAddrSize);
        if (clientSocket == INVALID_SOCKET) {
            throw std::runtime_error("Accept failed");
        }
    }
    void closeConnection() {
        if (clientSocket != INVALID_SOCKET) {
            closesocket(clientSocket);
            clientSocket = INVALID_SOCKET;
        }

        if (listenSocket != INVALID_SOCKET) {
            closesocket(listenSocket);
            listenSocket = INVALID_SOCKET;
        }
    }


    void messageSend(const char* message) override{
        send(clientSocket, message, strlen(message), 0);
    }

    int messageReceive(char* buffer, int bufferSize) override {
        return recv(clientSocket, buffer, bufferSize, 0);
    }
private:
    WSADATA wsaData;
    SOCKET listenSocket;
    SOCKET clientSocket;
};


#endif //UNTITLED_SERVER_H
