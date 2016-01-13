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
#include <condition_variable>

#include "../data/Message.h"

class MessageConsumer {
public:
    MessageConsumer(std::shared_ptr<std::queue<Message>> queue, std::shared_ptr<std::mutex> mutex,
                    std::shared_ptr<std::condition_variable> condition);

    void start();

    void consume(Message message);

private:
    std::shared_ptr<std::queue<Message>> queue_;
    std::shared_ptr<std::mutex> mutex_;
    std::shared_ptr<std::condition_variable> condition_;
};

#endif //ZAEIMCO_SERVER_CONSUMER_H
