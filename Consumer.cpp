//
// Created by hamed on 1/8/16.
//

#include "Consumer.h"
#include "utils.h"

Consumer::Consumer(std::shared_ptr<std::queue<Message>> queue, std::shared_ptr<std::mutex> mutex,
                   std::shared_ptr<std::condition_variable> condition) :
        queue_{queue}, mutex_{mutex}, condition_{condition} {
    std::thread t1{&Consumer::start, this};
    t1.detach();
}

void Consumer::start() {
    while (true) {
        std::unique_lock<std::mutex> lck{*mutex_};
        while(queue_->size() == 0) condition_->wait(lck);
        Message message = queue_->front();
        queue_->pop();
        lck.unlock();
        consume(message);
    }
}

void Consumer::consume(Message message) {
    if(message.operation.compare("CREATE_DIR") == 0)
        utils::create_dir(message.filename);
    else if(message.operation.compare("REMOVE_DIR") == 0)
        utils::remove_dir(message.filename);
    else if(message.operation.compare("REMOVE_FILE") == 0)
        utils::remove_file(message.filename);
    else if(message.operation.compare("CREATE_FILE") == 0)
        std::cerr << "dose not implemented yet!" << std::endl;
}