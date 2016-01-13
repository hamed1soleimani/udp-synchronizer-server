//
// Created by hamed on 1/7/16.
//

#include "utils.h"

#include <boost/filesystem.hpp>

using namespace boost::filesystem;

int utils::print_usage() {
    std::cerr << "Usage: server <port number>" << std::endl;
    return 1;
}

bool utils::create_dir(std::string dir) {
    path p{dir};
    bool result = false;
    try {
        result = create_directory(p);
    } catch (filesystem_error &e) {
        std::cout << e.what() << std::endl;
        result = false;
    }
    if (result)
        std::cout << "successfully created directory: " << dir << std::endl;
    else
        std::cout << "failed to create directory: " << dir << std::endl;
    return result;
}

bool utils::remove_dir(std::string dir) {
    path p{dir};
    bool result = false;
    try {
        result = remove_all(p) > 0;
    } catch (filesystem_error &e) {
        std::cout << e.what() << std::endl;
        result = false;
    }
    if (result)
        std::cout << "successfully removed directory: " << dir << std::endl;
    else
        std::cout << "failed to remove directory: " << dir << std::endl;
    return result;
}

bool utils::remove_file(std::string file) {
    path p{file};
    bool result = false;
    try {
        result = remove(p);
    } catch (filesystem_error &e) {
        std::cout << e.what() << std::endl;
        result = false;
    }
    if (result)
        std::cout << "successfully removed file: " << file << std::endl;
    else
        std::cout << "failed to remove file: " << file << std::endl;
    return result;
}

std::string utils::hash_message(std::string message) {
    return std::to_string(std::hash<std::string>()(message));
}