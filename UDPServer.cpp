//
// Created by hamed on 1/7/16.
//

#include "UDPServer.h"

UDPServer::UDPServer(boost::asio::io_service& io_service, unsigned short port)
        : socket_(io_service, udp::endpoint(udp::v4(), port))
{
    start_receive();
}

void UDPServer::start_receive()
{
    socket_.async_receive_from(
            boost::asio::buffer(receive_buffer_), remote_endpoint_,
            boost::bind(&UDPServer::handle_receive, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
}

void UDPServer::handle_receive(const boost::system::error_code& error,
                    std::size_t size)
{
    if (!error || error == boost::asio::error::message_size)
    {
        std::string message(receive_buffer_.data(), receive_buffer_.data() + size);
        std::cout << message << std::endl;
        receive_buffer_.empty();
        start_receive();
    }
}