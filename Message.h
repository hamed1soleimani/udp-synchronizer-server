//
// Created by hamed on 1/8/16.
//

#ifndef ZAEIMCO_SERVER_MESSAGE_H
#define ZAEIMCO_SERVER_MESSAGE_H

#include <string>

class Message{
public:
    Message(std::string operation, std::string filename);
    std::string operation;
    std::string filename;
    static Message toMessage(std::string message);
};

#endif //ZAEIMCO_SERVER_MESSAGE_H
