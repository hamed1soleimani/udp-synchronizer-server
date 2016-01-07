#include "Utils.h"
#include "UDPServer.h"

#include <iostream>

int main()
{
    try
    {
        boost::asio::io_service io_service;
        UDPServer server(io_service);
        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}