#pragma once

#include "time.hpp"
#include <string>

class Segment {
public:
    Segment(const char* name);
    Segment(const char* name, Time time_best_run);

    std::string name;
    Time time_best_run;
    bool time_exists;
    Time this_time;
};
