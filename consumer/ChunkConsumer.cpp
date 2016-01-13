//
// Created by hamed on 1/13/16.
//

#include "ChunkConsumer.h"

#include <thread>
#include <iostream>

ChunkConsumer::ChunkConsumer(std::shared_ptr<std::queue<Chunk>> queue, std::shared_ptr<std::mutex> mutex,
                             std::shared_ptr<std::condition_variable> condition) :
        queue_{queue}, mutex_{mutex}, condition_{condition} {
    std::thread t1{&ChunkConsumer::start, this};
    t1.detach();
}

void ChunkConsumer::start() {
    while (true) {
        std::unique_lock<std::mutex> lck{*mutex_};
        while (queue_->size() == 0) condition_->wait(lck);
        Chunk chunk = queue_->front();
        queue_->pop();
        lck.unlock();
        consume(chunk);
    }
}

void ChunkConsumer::consume(Chunk chunk) {
    std::cout << "chunk consumed" << std::endl;
}