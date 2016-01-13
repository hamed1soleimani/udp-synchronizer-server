#include "utils.h"
#include "UDPServer.h"
#include "MessageConsumer.h"
#include "ChunkConsumer.h"

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
        std::shared_ptr<std::queue<Message>> message_queue = std::make_shared<std::queue<Message>>();
        std::shared_ptr<std::mutex> message_mutex = std::make_shared<std::mutex>();
        std::shared_ptr<std::condition_variable> message_condition = std::make_shared<std::condition_variable>();
        std::shared_ptr<std::queue<Chunk>> chunk_queue = std::make_shared<std::queue<Chunk>>();
        std::shared_ptr<std::mutex> chunk_mutex = std::make_shared<std::mutex>();
        std::shared_ptr<std::condition_variable> chunk_condition = std::make_shared<std::condition_variable>();
        MessageConsumer messageConsumer(message_queue, message_mutex, message_condition);
        ChunkConsumer chunkConsumer(chunk_queue, chunk_mutex, chunk_condition);
        boost::asio::io_service io_service;
        UDPServer server(io_service, port, message_queue, message_mutex, message_condition,
                         chunk_queue, chunk_mutex, chunk_condition);
        io_service.run();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}