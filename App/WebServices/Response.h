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
ResponseType mapStringToResponseType(const std::string& input) {
    if (input == "ATTACK") {
        return ResponseType::ATTACK;
    } else if (input == "RESULT") {
        return ResponseType::RESULT;
    } else if (input == "STATUS") {
        return ResponseType::STATUS;
    }else if (input == "WRONG_MOVE") {
        return ResponseType::WRONG_MOVE;
    }
    return ResponseType::RESPONSE_ERROR;
}
class Response{
public:
    ResponseType type;
    std::string body;

    Response(std::string response) {
        size_t colonPos = response.find(':');
        if (colonPos != std::string::npos) {
            type = mapStringToResponseType(response.substr(0, colonPos));
            body = response.substr(colonPos + 1);
        }else{
            type = ResponseType::RESPONSE_ERROR;
            body = "Response error - please disconnect";
        }
    }
};
#endif //UNTITLED_RESPONSE_H
