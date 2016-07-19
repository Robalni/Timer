#pragma once

#include "object.hpp"
#include "time.hpp"
#include "text.hpp"

class Segment : public Object {
public:
    Segment(const char* name);
    Segment(const char* name, Time time_best_run);

    Text name;
    Time time_best_run;
    bool time_exists;
    Time this_time;
    Text time_text;

private:
    void update_time_text();
};
