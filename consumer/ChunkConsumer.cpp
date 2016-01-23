//
// Created by hamed on 1/13/16.
//

#include "ChunkConsumer.h"
#include "../utilities/utils.h"

#include <boost/filesystem.hpp>
#include <thread>

using namespace boost::filesystem;

ChunkConsumer::ChunkConsumer(std::shared_ptr<std::queue<Chunk>> queue, std::shared_ptr<std::mutex> mutex,
                             std::shared_ptr<std::condition_variable> condition) :
        queue_{queue}, mutex_{mutex}, condition_{condition}{
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
    path p{chunk.filename};
    if(!exists(p)){
        utils::create_file(chunk.filename);
    }
    utils::write_chunk(chunk.filename, chunk.start, chunk.contents.size(), chunk.contents);
    if(chunk.contents.size())
        std::cout << "receiving last chunks" << std::endl;
}