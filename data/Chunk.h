//
// Created by hamed on 1/13/16.
//

#ifndef ZAEIMCO_SERVER_CHUNCK_H
#define ZAEIMCO_SERVER_CHUNCK_H

#include <string>
#include <memory>
#include <boost/array.hpp>

class Chunk {
public:
    Chunk(std::string filename, unsigned long start, std::string contents);

    static Chunk toChunk(std::string message);

    std::string filename;
    unsigned long start;
    std::string contents;

};


#endif //ZAEIMCO_SERVER_CHUNCK_H
