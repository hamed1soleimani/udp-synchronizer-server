//
// Created by hamed on 1/7/16.
//

#include "utils.h"

#include <boost/filesystem.hpp>
#include <fstream>

using namespace boost::filesystem;

int utils::print_usage() {
    std::cerr << "Usage: server <port number>" << std::endl;
    return 1;
}

bool utils::create_dir(std::string dir) {
    path p{dir};
    bool result = false;
    try {
        result = create_directories(p);
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

bool utils::create_file(std::string file) {
    path p{file};
    bool result = false;
    bool exist = false;
    try {
        exist = exists(p);
        if (!exist && p.has_branch_path() && !exists(p.parent_path())) {
            create_directories(p.parent_path());
        }
    } catch (filesystem_error &e) {
        std::cout << e.what() << std::endl;
        result = false;
    }
    if (!exist) {
        std::ofstream f(file);
        if (f.is_open()) {
            result = true;
            f.close();
        } else {
            result = false;
        }
    }
    if (result)
        std::cout << "successfully created file: " << file << std::endl;
    else
        std::cout << "failed to create file: " << file << std::endl;
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
    std::string h = std::to_string(std::hash<std::string>()(message));
    if (h.size() > 20)
        return h.substr(0, 20);
    else {
        std::string t = "";
        for (int i = 0; i < 20 - h.size(); i++)
            t += " ";
        h += t;
        return h;
    }
}

void utils::write_chunk(std::string filename, unsigned long pos, int size, char *content) {
    std::streampos file_size;
    std::ofstream file(filename, std::ios::out | std::ios::binary | std::ios::ate);
    file_size = file.tellp();
    if(file_size >= pos + size){
        file.seekp(pos, std::ios::beg);
        file.write(content, size);
    }else{
        unsigned long dif = size - pos;
        file.seekp(0, std::ios::end);
        std::string buf{dif, '\0' - 1};
        file.write(buf.c_str(), dif);
        file.write(content, size);
    }
    file.close();
}