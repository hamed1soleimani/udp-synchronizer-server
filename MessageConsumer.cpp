//
// Created by hamed on 1/8/16.
//

#include "MessageConsumer.h"
#include "utils.h"

MessageConsumer::MessageConsumer(std::shared_ptr<std::queue<Message>> queue, std::shared_ptr<std::mutex> mutex,
                                 std::shared_ptr<std::condition_variable> condition) :
        queue_{queue}, mutex_{mutex}, condition_{condition} {
    std::thread t1{&MessageConsumer::start, this};
    t1.detach();
}

void MessageConsumer::start() {
    while (true) {
        std::unique_lock<std::mutex> lck{*mutex_};
        while (queue_->size() == 0) condition_->wait(lck);
        Message message = queue_->front();
        queue_->pop();
        lck.unlock();
        consume(message);
    }
}

void MessageConsumer::consume(Message message) {
    if (message.operation.compare("CREATE_DIR") == 0)
        utils::create_dir(message.filename);
    else if (message.operation.compare("REMOVE_DIR") == 0)
        utils::remove_dir(message.filename);
    else if (message.operation.compare("REMOVE_FILE") == 0)
        utils::remove_file(message.filename);
    else if (message.operation.compare("CREATE_FILE") == 0)
        utils::create_file(message.filename);
    else
        std::cout << "Invalid operation: " << message.operation << std::endl;
}