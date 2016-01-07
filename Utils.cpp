//
// Created by hamed on 1/7/16.
//

#include <iostream>
#include "Utils.h"

std::string make_daytime_string()
{
    using namespace std;
    time_t now = time(0);
    return ctime(&now);
}

int print_usage(){
    std::cerr << "Usage: client <port number>" << std::endl;
    return 1;
}