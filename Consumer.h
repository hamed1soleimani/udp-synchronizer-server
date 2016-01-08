//
// Created by hamed on 1/8/16.
//

#ifndef ZAEIMCO_SERVER_CONSUMER_H
#define ZAEIMCO_SERVER_CONSUMER_H

#include <mutex>
#include <queue>
#include <memory>
#include <iostream>
#include <thread>
#include <tuple>

#include "Message.h"

class Consumer {
public:
    Consumer(std::shared_ptr<std::queue<Message>> queue, std::shared_ptr<std::mutex> mutex);
    void start();
    void consume(Message message);
private:
    std::shared_ptr<std::queue<Message>> queue_;
    std::shared_ptr<std::mutex> mutex_;
};

#endif //ZAEIMCO_SERVER_CONSUMER_H
