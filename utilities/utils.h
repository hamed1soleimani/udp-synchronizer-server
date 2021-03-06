//
// Created by hamed on 1/7/16.
//

#ifndef ZAEIMCO_SERVER_UTILS_H
#define ZAEIMCO_SERVER_UTILS_H

#include <iostream>

namespace utils {
    int print_usage();

    bool remove_dir(std::string dir);

    bool remove_file(std::string file);

    bool create_dir(std::string dir);

    bool create_file(std::string file);

    std::string hash_message(std::string message);

    void write_chunk(std::string filename, unsigned long pos, int size, std::string content);
}

#endif //ZAEIMCO_SERVER_UTILS_H
