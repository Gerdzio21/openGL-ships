//
// Created by gerdzio21 on 31.08.2023.
//

#ifndef UNTITLED_RESPONSE_H
#define UNTITLED_RESPONSE_H


#include <string>

enum ResponseType{
    ATTACK,
    RESULT,
    STATUS,
    WRONG_MOVE,
    RESPONSE_ERROR,
};
ResponseType mapStringToResponseType(const std::string& input);
class Response{
public:
    ResponseType type;
    std::string body;

    Response(std::string response);
};
#endif //UNTITLED_RESPONSE_H
