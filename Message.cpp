//
// Created by hamed on 1/8/16.
//

#include "Message.h"
#include "utils.h"

Message::Message(std::string operation, std::string filename) : operation{operation}, filename{filename} { }

Message Message::toMessage(std::string message) {
    unsigned long loc = message.find(";;");
    std::string hash = message.substr(0, loc);
    std::string m = message.substr(loc + 2);
    if(utils::hash_message(m).compare(hash) == 0) {
        loc = m.find(";;");
        std::string operation = m.substr(0, loc);
        std::string filename = m.substr(loc + 2);
        return Message(operation, filename);
    }else{
        throw std::invalid_argument("Message does not received correctly!");
    }
}

