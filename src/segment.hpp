#pragma once

#include "object.hpp"
#include "time.hpp"
#include "text.hpp"

class Segment : public Object {
public:
    Segment(const char* name);
    Segment(const char* name, Time time_best_run);
    void set_this_time(Time new_time);
    void set_name(const char* new_name);
    void update_time_text();

    Text name;
    Time time_best_run;
    bool best_time_exists;
    bool this_time_exists;
    Time this_time;
    bool this_best_time_exists;
    Time this_best_time;
    Text time_text;
};
