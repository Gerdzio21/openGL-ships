//
// Created by gerdzio21 on 23.05.2023.
//

#ifndef SHIPS_ATTACKEXCEPTION_H
#define SHIPS_ATTACKEXCEPTION_H

#include <exception>
#include <string>

class AttackException : public std::exception {
private:
    std::string message;
public:
    explicit AttackException(const char* msg) : message(msg) {}

    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif //SHIPS_ATTACKEXCEPTION_H
