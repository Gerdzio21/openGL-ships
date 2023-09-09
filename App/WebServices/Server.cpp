#include "Server.h"

//
// Created by Gerdzio21 on 2023-09-09.
//
Server::Server() {
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        throw std::runtime_error("Failed to initialize Winsock");
    }
}

Server::~Server() {
    WSACleanup();
}

void Server::StartListening(int port) {
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

void Server::closeConnection() {
    if (clientSocket != INVALID_SOCKET) {
        closesocket(clientSocket);
        clientSocket = INVALID_SOCKET;
    }

    if (listenSocket != INVALID_SOCKET) {
        closesocket(listenSocket);
        listenSocket = INVALID_SOCKET;
    }
}

void Server::messageSend(const char *message) {
    send(clientSocket, message, strlen(message), 0);
}

int Server::messageReceive(char *buffer, int bufferSize) {
    return recv(clientSocket, buffer, bufferSize, 0);
}
