//
// Created by Gerdzio21 on 2023-09-09.
//
#include "Response.h"
ResponseType mapStringToResponseType(const std::string &input) {
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

Response::Response(std::string response) {
    size_t colonPos = response.find(':');
    if (colonPos != std::string::npos) {
        type = mapStringToResponseType(response.substr(0, colonPos));
        body = response.substr(colonPos + 1);
    }else{
        type = ResponseType::RESPONSE_ERROR;
        body = "Response error - please disconnect";
    }
}
