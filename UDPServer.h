//
// Created by hamed on 1/7/16.
//

#ifndef ZAEIMCO_SERVER_UDPSERVER_H
#define ZAEIMCO_SERVER_UDPSERVER_H

#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

#include "Utils.h"

using boost::asio::ip::udp;

class UDPServer
{
public:
    UDPServer(boost::asio::io_service& io_service);

private:

    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    boost::array<char, 1> recv_buffer_;

    void start_receive();
    void handle_receive(const boost::system::error_code& error,
                        std::size_t);

    void handle_send(boost::shared_ptr<std::string>,
                     const boost::system::error_code&,
                     std::size_t);

};


#endif //ZAEIMCO_SERVER_UDPSERVER_H
