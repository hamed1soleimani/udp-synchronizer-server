//
// Created by hamed on 1/8/16.
//

#include "Consumer.h"
#include "utils.h"

Consumer::Consumer(std::shared_ptr<std::queue<Message>> queue, std::shared_ptr<std::mutex> mutex) :
        queue_{queue}, mutex_{mutex} {
    std::thread t1{&Consumer::start, this};
    t1.detach();
}

void Consumer::start() {
    while (true) {
        std::unique_lock<std::mutex> lck{*mutex_};
        if(queue_->size() > 0) {
            Message message = queue_->front();
            queue_->pop();
            lck.unlock();
            consume(message);
        }
    }
}

void Consumer::consume(Message message) {
    std::cout << "consumed" << std::endl;
}