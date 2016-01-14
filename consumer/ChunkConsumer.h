//
// Created by hamed on 1/13/16.
//

#ifndef ZAEIMCO_SERVER_CHUNKCONSUMER_H
#define ZAEIMCO_SERVER_CHUNKCONSUMER_H

#include "../data/Chunk.h"

#include <queue>
#include <mutex>
#include <condition_variable>

class ChunkConsumer {
public:
    ChunkConsumer(std::shared_ptr<std::queue<Chunk>> queue, std::shared_ptr<std::mutex> mutex,
                  std::shared_ptr<std::condition_variable> condition);

    void start();

    void consume(Chunk message);

private:
    std::shared_ptr<std::queue<Chunk>> queue_;
    std::shared_ptr<std::mutex> mutex_;
    std::shared_ptr<std::condition_variable> condition_;
    int c;
};


#endif //ZAEIMCO_SERVER_CHUNKCONSUMER_H
