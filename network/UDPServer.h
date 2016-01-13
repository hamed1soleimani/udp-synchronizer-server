//
// Created by hamed on 1/7/16.
//

#ifndef ZAEIMCO_SERVER_UDPSERVER_H
#define ZAEIMCO_SERVER_UDPSERVER_H

#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <string>
#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>

#include "../data/Message.h"
#include "../data/Chunk.h"

using boost::asio::ip::udp;

class UDPServer {
public:
    UDPServer(boost::asio::io_service &io_service, unsigned short port,
              std::shared_ptr<std::queue<Message>> message_queue,
              std::shared_ptr<std::mutex> message_mutex,
              std::shared_ptr<std::condition_variable> message_condition,
              std::shared_ptr<std::queue<Chunk>> chunk_queue,
              std::shared_ptr<std::mutex> chunk_mutex,
              std::shared_ptr<std::condition_variable> chunk_condition);

private:
    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    boost::array<char, 1500> receive_buffer_;
    std::shared_ptr<std::queue<Message>> message_queue_;
    std::shared_ptr<std::mutex> message_mutex_;
    std::shared_ptr<std::condition_variable> message_condition_;
    std::shared_ptr<std::queue<Chunk>> chunk_queue_;
    std::shared_ptr<std::mutex> chunk_mutex_;
    std::shared_ptr<std::condition_variable> chunk_condition_;

    void start_receive();

    void handle_receive(const boost::system::error_code &error,
                        std::size_t size);
};


#endif //ZAEIMCO_SERVER_UDPSERVER_H
