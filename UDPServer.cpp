//
// Created by hamed on 1/7/16.
//

#include "UDPServer.h"
#include "utils.h"

#include <thread>
#include <iostream>

UDPServer::UDPServer(boost::asio::io_service &io_service, unsigned short port,
                     std::shared_ptr<std::queue<Message>> message_queue,
                     std::shared_ptr<std::mutex> message_mutex,
                     std::shared_ptr<std::condition_variable> message_condition,
                     std::shared_ptr<std::queue<Chunk>> chunk_queue,
                     std::shared_ptr<std::mutex> chunk_mutex,
                     std::shared_ptr<std::condition_variable> chunk_condition)
        : socket_{io_service, udp::endpoint(udp::v4(), port)},
          message_queue_{message_queue}, message_mutex_{message_mutex}, message_condition_{message_condition},
          chunk_queue_{chunk_queue}, chunk_mutex_{chunk_mutex}, chunk_condition_{chunk_condition} {
    start_receive();
}

void UDPServer::start_receive() {
    socket_.async_receive_from(
            boost::asio::buffer(receive_buffer_), remote_endpoint_,
            boost::bind(&UDPServer::handle_receive, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
}

void UDPServer::handle_receive(const boost::system::error_code &error,
                               std::size_t size) {
    if (!error || error == boost::asio::error::message_size) {
        std::string message(receive_buffer_.data(), receive_buffer_.data() + size);
        std::string hash = message.substr(0, 20);
        std::string bare_message = message.substr(24);
        std::string code = message.substr(21, 2);
        if (hash.compare(utils::hash_message(bare_message)) == 0) {
            if (code.compare("OP") == 0) {
                Message m = Message::toMessage(bare_message);
                std::unique_lock<std::mutex> lck{*message_mutex_};
                message_queue_->push(m);
                lck.unlock();
                message_condition_->notify_all();
            }else if(code.compare("CH") == 0){
                Chunk c = Chunk::toChunk(bare_message);
                std::unique_lock<std::mutex> lck{*chunk_mutex_};
                chunk_queue_->push(c);
                lck.unlock();
                chunk_condition_->notify_all();
            }else{
                std::cout << "corrupted message!" << std::endl;
                std::cout << " 321 hash is :" << hash << std::endl;
            }
        } else {
            std::cout << "corrupted message!" << std::endl;
            std::cout << " 123 hash is :" << hash << std::endl;
        }
        start_receive();
    }
}