#include <iostream>
#include <winsock2.h>
#include "ConnectionManager.h"

int menu(){
    ConnectionManager connectionManager;

    char choice;
    int STATUS_CODE = 0;
    std::cout << "Choose an option:\n";
    std::cout << "1. Start as server\n";
    std::cout << "2. Start as client\n";
    std::cout << "3. Exit\n";
    std::cout << "Choice:";
    std::cin >> choice;

    if (choice == '1') {
        STATUS_CODE = connectionManager.startServerGame();
    } else if (choice == '2') {
        STATUS_CODE = connectionManager.startClientGame("127.0.0.1", 12345);
    } else {
        STATUS_CODE = 1;
    }
    return STATUS_CODE;
}
int main() {

    std::cout << "Uposledzone statki!" << std::endl;
    while(true) {
        int STATUS_CODE = menu();
        if (STATUS_CODE){
            break;
        }
    }
    return 0;
}
