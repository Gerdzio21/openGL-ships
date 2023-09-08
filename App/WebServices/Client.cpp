#include "Client.h"

//
// Created by Gerdzio21 on 2023-09-08.
//
Client::Client() {
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        throw std::runtime_error("Failed to initialize Winsock");
    }
}

Client::~Client() {
    WSACleanup();
}

void Client::Connect(const char *ipAddress, int port) {
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

    std::cout << "[log] STATUS --- Connected to server" << std::endl;
}

void Client::closeConnection() {
    if (clientSocket != INVALID_SOCKET) {
        closesocket(clientSocket);
        clientSocket = INVALID_SOCKET;
    }
}

void Client::messageSend(const char *message) {
    send(clientSocket, message, strlen(message), 0);
}

int Client::messageReceive(char *buffer, int bufferSize) {
    return recv(clientSocket, buffer, bufferSize, 0);
}
