//
// Created by gerdzio21 on 05.08.2023.
//

#ifndef UNTITLED_CONNECTIONMANAGER_H
#define UNTITLED_CONNECTIONMANAGER_H

#define CONSOLE_SET_TEXT_COLOR_BLUE  SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
#define CONSOLE_SET_TEXT_COLOR_RED SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
#define CONSOLE_SET_TEXT_COLOR_YELLOW SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
#define CONSOLE_RESET_TEXT_COLOR SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

#include "Server.h"
#include "Client.h"
#include <windows.h>
#include <asptlb.h>

enum ConnectionMember{
    SERVER,
    CLIENT,
    UNDEFINED
};
class ConnectionManager {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
public:
    int startServerGame() {
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

    int startClientGame(const char* ipAddress, int port) {
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
    std::string receiveMessage(TcpInterface* tcpInterface){
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
    std::string receiveMessage(){
        if(selectedConnectionMember == SERVER){
           return receiveMessage( &server);
        }
        if(selectedConnectionMember == CLIENT){
           return receiveMessage( &client);
        }
        return "";
    }

    void sendMessage(std::string message){
        if(selectedConnectionMember == SERVER){
            sendMessage(message, &server);
        }
        if(selectedConnectionMember == CLIENT){
            sendMessage(message, &client);
        }
    }

    void sendMessage(std::string message,TcpInterface* tcpInterface){
        CONSOLE_SET_TEXT_COLOR_BLUE
        std::cout << "[log] STATUS --- Sending a message..." << std::endl;
        CONSOLE_RESET_TEXT_COLOR
        tcpInterface->messageSend(message.c_str());
    }

    ConnectionManager()= default;
    ~ConnectionManager(){
        if(selectedConnectionMember == SERVER){
            server.closeConnection();
        }
        if(selectedConnectionMember == CLIENT){
            client.closeConnection();
        }
    }


private:
    Server server;
    Client client;
ConnectionMember selectedConnectionMember = UNDEFINED;
    const int bufferSize = 1024;
    bool isListener = false;

//    void handleCommunication(TcpInterface* tcpInterface) {
//        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//        std::string message;
//        char buffer[bufferSize];
//            if (isListener) {
//                CONSOLE_SET_TEXT_COLOR_BLUE
//                std::cout << "[log] STATUS --- Waiting to receive a message..." << std::endl;
//                CONSOLE_RESET_TEXT_COLOR
//                int bytesReceived = tcpInterface->messageReceive(buffer, bufferSize);
//                if (bytesReceived > 0) {
//                    buffer[bytesReceived] = '\0';
//                    std::cout << "Received: " << buffer << std::endl;
//                    /*
//                    message = std::string(buffer);
//                    tcpInterface->messageSend(message.c_str());
//                    */
//                }else{
//                    CONSOLE_SET_TEXT_COLOR_RED
//                    std::cout << "Disconnected" << std::endl;
//                    CONSOLE_RESET_TEXT_COLOR
//                }
//            }else{
//                CONSOLE_SET_TEXT_COLOR_YELLOW
//                std::cout << "Enter message to send (or type 'exit' to quit):";
//                CONSOLE_RESET_TEXT_COLOR
//                std::cin >> message;
//                if (message == "exit") {
//                }
//                CONSOLE_SET_TEXT_COLOR_BLUE
//                std::cout << "[log] STATUS --- Sending a message..." << std::endl;
//                CONSOLE_RESET_TEXT_COLOR
//                tcpInterface->messageSend(message.c_str());
//                /* int bytesReceived = tcpInterface->messageReceive(buffer, bufferSize);
//                if (bytesReceived > 0) {
//                    buffer[bytesReceived] = '\0';
//                    if (message == buffer) {
//                        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
//                        std::cout << "[log] OK ------- ";
//                    } else {
//                        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
//                        std::cout << "[log] ERROR ---- ";
//                    }
//                    std::cout << "Recipient got: " << buffer << std::endl;
//                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
//                }
//*/
//            }
//            isListener = !isListener;
//    }
};


#endif //UNTITLED_CONNECTIONMANAGER_H
