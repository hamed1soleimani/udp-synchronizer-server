//
// Created by hamed on 1/7/16.
//

#include "Utils.h"

std::string make_daytime_string()
{
    using namespace std;
    time_t now = time(0);
    return ctime(&now);
}