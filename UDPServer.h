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

#include "Utils.h"

using boost::asio::ip::udp;

class UDPServer
{
public:
    UDPServer(boost::asio::io_service& io_service, unsigned short port);

private:

    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    boost::array<char, 1024> receive_buffer_;

    void start_receive();
    void handle_receive(const boost::system::error_code& error,
                        std::size_t size);
};


#endif //ZAEIMCO_SERVER_UDPSERVER_H
