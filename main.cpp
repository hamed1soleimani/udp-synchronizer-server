#include "utils.h"
#include "UDPServer.h"
#include "Consumer.h"

int main(int argc, char *argv[]) {
    unsigned short port;
    if (argc != 2) {
        return utils::print_usage();
    }

    std::istringstream iss(argv[1]);
    if (!(iss >> port)) {
        return utils::print_usage();
    }

    try {
        std::shared_ptr<std::queue<Message>> queue = std::make_shared<std::queue<Message>>();
        std::shared_ptr<std::mutex> mutex = std::make_shared<std::mutex>();
        std::shared_ptr<std::condition_variable> condition = std::make_shared<std::condition_variable>();
        Consumer consumer(queue, mutex, condition);
        boost::asio::io_service io_service;
        UDPServer server(io_service, port, queue, mutex, condition);
        io_service.run();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}