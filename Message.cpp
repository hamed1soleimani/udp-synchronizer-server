//
// Created by hamed on 1/8/16.
//

#include "Message.h"

Message::Message(std::string operation, std::string filename): operation{operation}, filename{filename} { }

Message Message::toMessage(std::string message) {
    unsigned long loc = message.find(";;");
    std::string operation = message.substr(0, loc);
    std::string filename = message.substr(loc + 2);
    return Message(operation, filename);
}

