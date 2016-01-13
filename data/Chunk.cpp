//
// Created by hamed on 1/13/16.
//

#include "Chunk.h"
#include "../utilities/utils.h"

Chunk::Chunk(std::string filename, unsigned long start, std::vector<char> content) :
        filename{filename}, start{start}, contents{std::move(content)} {
}

Chunk Chunk::toChunk(std::string message) {
    unsigned long loc_file = message.find(";");
    unsigned long loc_start = message.find(";", loc_file + 1);
    std::string filename = message.substr(0, loc_file);
    unsigned long start = std::stoul(message.substr(loc_file + 1, loc_start - loc_file - 1));
    const char *cstr = message.substr(loc_start + 1).c_str();
    std::vector<char> chunk{cstr, cstr + sizeof(cstr)};
    return Chunk(filename, start, chunk);
}