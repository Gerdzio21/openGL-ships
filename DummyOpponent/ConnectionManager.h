//
// Created by gerdzio21 on 05.08.2023.
//

#ifndef UNTITLED_CONNECTIONMANAGER_H
#define UNTITLED_CONNECTIONMANAGER_H


#include "Server.h"
#include "Client.h"
#include <windows.h>

class ConnectionManager {
public:
    int startServerGame() {
        server.StartListening(12345);
        isListener = true;
        handleCommunication(&server);
        return 0;
    }

    int startClientGame(const char* ipAddress, int port) {
        client.Connect(ipAddress, port);
        handleCommunication(&client);
        return 0;
    }

private:
    Server server;
    Client client;
    bool isListener = false;

    void handleCommunication(TcpInterface* tcpInterface) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        std::string message;
        const int bufferSize = 1024;
        char buffer[bufferSize];
        while (true) {
            if (isListener) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                std::cout << "[log] STATUS --- Waiting to receive a message..." << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                int bytesReceived = tcpInterface->messageReceive(buffer, bufferSize);
                if (bytesReceived > 0) {
                    buffer[bytesReceived] = '\0';
                    std::cout << "Received: " << buffer << std::endl;
                    /*
                    message = std::string(buffer);
                    tcpInterface->messageSend(message.c_str());
                    */
                }else{
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                    std::cout << "Disconnected: " << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    break;
                }
            }else{
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                std::cout << "Enter message to send (or type 'exit' to quit):";
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                std::cin >> message;
                if (message == "exit") {
                    break;
                }
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                std::cout << "[log] STATUS --- Sending a message..." << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                tcpInterface->messageSend(message.c_str());
                /* int bytesReceived = tcpInterface->messageReceive(buffer, bufferSize);
                if (bytesReceived > 0) {
                    buffer[bytesReceived] = '\0';
                    if (message == buffer) {
                        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                        std::cout << "[log] OK ------- ";
                    } else {
                        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                        std::cout << "[log] ERROR ---- ";
                    }
                    std::cout << "Recipient got: " << buffer << std::endl;
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                }
*/
            }
            isListener = !isListener;
        }
    }
};


#endif //UNTITLED_CONNECTIONMANAGER_H
