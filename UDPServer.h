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

#include "Message.h"

using boost::asio::ip::udp;

class UDPServer {
public:
    UDPServer(boost::asio::io_service &io_service, unsigned short port,
              std::shared_ptr<std::queue<Message>> queue,
              std::shared_ptr<std::mutex> mutex,
              std::shared_ptr<std::condition_variable> condition);

private:
    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    boost::array<char, 1024> receive_buffer_;
    std::shared_ptr<std::queue<Message>> queue_;
    std::shared_ptr<std::mutex> mutex_;
    std::shared_ptr<std::condition_variable> condition_;

    void start_receive();

    void handle_receive(const boost::system::error_code &error,
                        std::size_t size);
};


#endif //ZAEIMCO_SERVER_UDPSERVER_H
