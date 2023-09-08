#include "ConnectionManager.h"

//
// Created by Gerdzio21 on 2023-09-08.
//
int ConnectionManager::startServerGame() {
    if(selectedConnectionMember != UNDEFINED){
        std::cout<< "THROW EXCEPTION HERE!";
    }
    server.StartListening(12345);
    selectedConnectionMember = SERVER;
    CONSOLE_SET_TEXT_COLOR_BLUE
    std::cout << "[log] STATUS --- Server started" << std::endl;
    CONSOLE_RESET_TEXT_COLOR
    return 0;
}

int ConnectionManager::startClientGame(const char *ipAddress, int port) {
    if(selectedConnectionMember != UNDEFINED){
        std::cout<< "THROW EXCEPTION HERE!";
    }
    client.Connect(ipAddress, port);
    selectedConnectionMember = CLIENT;
    CONSOLE_SET_TEXT_COLOR_BLUE
    std::cout << "[log] STATUS --- Server started" << std::endl;
    CONSOLE_RESET_TEXT_COLOR
    return 0;
}

std::string ConnectionManager::receiveMessage(TcpInterface *tcpInterface) {
    char buffer[bufferSize];
    CONSOLE_SET_TEXT_COLOR_BLUE
    std::cout << "[log] STATUS --- Waiting to receive a message..." << std::endl;
    CONSOLE_RESET_TEXT_COLOR
    int bytesReceived = tcpInterface->messageReceive(buffer, bufferSize);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        std::cout << "Received: " << buffer << std::endl;
        return buffer;
    }else{
        CONSOLE_SET_TEXT_COLOR_RED
        std::cout << "Disconnected" << std::endl;
        CONSOLE_RESET_TEXT_COLOR
    }
    return "";
}

std::string ConnectionManager::receiveMessage() {
    if(selectedConnectionMember == SERVER){
        return receiveMessage( &server);
    }
    if(selectedConnectionMember == CLIENT){
        return receiveMessage( &client);
    }
    return "";
}

void ConnectionManager::sendMessage(std::string message) {
    if(selectedConnectionMember == SERVER){
        sendMessage(message, &server);
    }
    if(selectedConnectionMember == CLIENT){
        sendMessage(message, &client);
    }
}

void ConnectionManager::sendMessage(std::string message, TcpInterface *tcpInterface) {
    CONSOLE_SET_TEXT_COLOR_BLUE
    std::cout << "[log] STATUS --- Sending a message..." << std::endl;
    CONSOLE_RESET_TEXT_COLOR
    tcpInterface->messageSend(message.c_str());
}

ConnectionManager::~ConnectionManager() {
    if(selectedConnectionMember == SERVER){
        server.closeConnection();
    }
    if(selectedConnectionMember == CLIENT){
        client.closeConnection();
    }
}
